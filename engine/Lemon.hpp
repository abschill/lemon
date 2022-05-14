#ifndef LEMON
#define LEMON

#include "Environment.hpp"
#include "ObjectCreator.hpp"

// try catch handler for runtime
using v8::TryCatch;
// message class for error handling to standard out
using v8::Message;
// locals for js objects
using v8::Local;
// superclass of all things in js
using v8::Value;
// a compiled javascript script
using v8::Script;
// origin, within a file, of a script
using v8::ScriptOrigin;
using v8::NewStringType;
using v8::MaybeLocal;
using v8::String;

class Lemon : public Environment {

	protected:
		// handle err from trycatch
		virtual void ReportException(TryCatch* try_catch) final;
		// run string as js
		virtual bool ExecuteString(Local<String> source, const char* filename) final;
		// a wrapper around local before being resolved
		virtual MaybeLocal<String> ReadFile(const char* filename) final;
		// run js from path
		virtual bool RunJsFromFile(const char* filename);
		// helper global to bind global method to the context
		virtual void CreateGlobalMethod(const char* methodname, void (*callback)(const FunctionCallbackInfo<Value>& args)) final;
		// helper global to bind global object to context
		virtual ObjectCreator CreateGlobalObject(const char* objectname) final;
};

#endif