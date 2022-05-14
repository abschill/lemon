#include "App.hpp"

using namespace v8;

static void println(const FunctionCallbackInfo<Value>& args) {
	HandleScope scope(args.GetIsolate());
	String::Utf8Value  str(args.GetIsolate(), args[0]);
	const char* cstr = StaticHelpers::ToCString(str);
	fprintf(stdout, "%s", cstr);
	fprintf(stdout, "\n");
	fflush(stdout);
}

void App::Start(int argc, char* argv[]) {
	for (int i = 1; i < argc; ++i) {
		// Get filename of the javascript file to run
		const char* filename = argv[i];

		// Create a new context for executing javascript code
		// A "Local" in the v8 is a stack allocated object handle
		Local<Context> context = this->CreateLocalContext();

		// Enter the new context
		// Context::Scope is a stack allocated class which sets the execution context for all operations executed within a local scope
		Context::Scope contextscope(context);

		this->CreateGlobalObject("console")
								.SetPropertyMethod("log", println)
								.Register();


		// Run the javascript file
		this->RunJsFromFile(filename);
		this->RunJsFromFile(filename);
	}
}