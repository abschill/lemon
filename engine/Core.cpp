#include "../app/App.hpp"

/**
 * @brief  HandleScope is a stack-allocated class that governs a number of local handles.
 * After a scope has been created, all local handles will be allocated within that handle scope until either the handle scope is deleted or another handle scope is created.
 * If there os already a handle scope and a new one is created, all allocations will take place in the new handle scope until it is deleted. After that, new handles will again be allocated
 * in the original handle scope.
 *
 * After the handle scope of a local handle has been deleted the gc will no longer track the object stored in the handle, and may dealloc it. The behavior of accessing
 * a handle for which the handle scope has been deleted, is undefined.
 *
 */
using v8::HandleScope;

int main(int argc, char* argv[]) {

	App app;

	app.CreatePlatform(argv);
	app.CreateVM();

	{

		// Enter isolate scope
		Isolate::Scope isolatescope(app.GetIsolate());

		// Enter handle scope
		HandleScope handlescope(app.GetIsolate());

		// Create global environment object
		app.CreateGlobalEnvironment();

		// Setup engine environment
		app.SetupEngineEnvironment();

		// Call app setup environment hook
		app.SetupEnvironment();

		// Call app start hook
		app.Start(argc, argv);

	}

	// Shutdown
	app.ShutdownVM();

	return 0;
	
}