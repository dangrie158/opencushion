#include "binding.h"

using v8::Exception;
using v8::Function;
using v8::FunctionCallbackInfo;
using v8::FunctionTemplate;
using v8::Isolate;
using v8::Local;
using v8::Number;
using v8::Null;
using v8::Object;
using v8::String;
using v8::Value;
using v8::Persistent;

Persistent<Function> HX711Wrapper::constructor;

HX711Wrapper::HX711Wrapper(uint8_t clockPin, uint8_t dataPin) :
	mSensor(new HX711(clockPin, dataPin))
{

}

HX711Wrapper::~HX711Wrapper(){
	delete mSensor;
}

void HX711Wrapper::InitModule(Local<Object> exports) {
	Isolate* isolate = exports->GetIsolate();

	// Prepare constructor template
	Local<FunctionTemplate> tpl = FunctionTemplate::New(isolate, New);
	tpl->SetClassName(String::NewFromUtf8(isolate, "HX711"));
	tpl->InstanceTemplate()->SetInternalFieldCount(1);

	// Prototype
	NODE_SET_PROTOTYPE_METHOD(tpl, "read", read);
	NODE_SET_PROTOTYPE_METHOD(tpl, "setScale", setScale);
	NODE_SET_PROTOTYPE_METHOD(tpl, "setOffset", setOffset);
	NODE_SET_PROTOTYPE_METHOD(tpl, "tare", tare);
	NODE_SET_PROTOTYPE_METHOD(tpl, "getUnits", getUnits);
	NODE_SET_PROTOTYPE_METHOD(tpl, "setGain", setGain);

	constructor.Reset(isolate, tpl->GetFunction());
	exports->Set(String::NewFromUtf8(isolate, "HX711"), tpl->GetFunction());
}

void HX711Wrapper::read(const FunctionCallbackInfo<Value>& args) {
	Isolate* isolate = args.GetIsolate();

	HX711Wrapper* obj = ObjectWrap::Unwrap<HX711Wrapper>(args.Holder());
	int32_t value = obj->mSensor->read();

	args.GetReturnValue().Set(Number::New(isolate, value));
}

void HX711Wrapper::setScale(const FunctionCallbackInfo<Value>& args) {
        Isolate* isolate = args.GetIsolate();

	float scaleArg = args[0]->IsUndefined() ? 1.0f : args[0]->NumberValue();

        HX711Wrapper* obj = ObjectWrap::Unwrap<HX711Wrapper>(args.Holder());
        obj->mSensor->setScale(scaleArg);

        args.GetReturnValue().Set(Null(isolate));
}

void HX711Wrapper::setOffset(const FunctionCallbackInfo<Value>& args) {
        Isolate* isolate = args.GetIsolate();

        int32_t offsetArg = args[0]->IsUndefined() ? 0 : args[0]->NumberValue();

        HX711Wrapper* obj = ObjectWrap::Unwrap<HX711Wrapper>(args.Holder());
        obj->mSensor->setOffset(offsetArg);

        args.GetReturnValue().Set(Null(isolate));
}

void HX711Wrapper::tare(const FunctionCallbackInfo<Value>& args) {
        Isolate* isolate = args.GetIsolate();

        uint8_t timesArg = args[0]->IsUndefined() ? 10 : args[0]->NumberValue();

        HX711Wrapper* obj = ObjectWrap::Unwrap<HX711Wrapper>(args.Holder());
        obj->mSensor->tare(timesArg);

        args.GetReturnValue().Set(Null(isolate));
}

void HX711Wrapper::getUnits(const FunctionCallbackInfo<Value>& args) {
        Isolate* isolate = args.GetIsolate();

        uint8_t timesArg = args[0]->IsUndefined() ? 10 : args[0]->NumberValue();

        HX711Wrapper* obj = ObjectWrap::Unwrap<HX711Wrapper>(args.Holder());
        float value = obj->mSensor->getUnits(timesArg);

        args.GetReturnValue().Set(Number::New(isolate, value));
}

void HX711Wrapper::setGain(const FunctionCallbackInfo<Value>& args) {
        Isolate* isolate = args.GetIsolate();

        uint8_t gainArg = args[0]->IsUndefined() ? 128 : args[0]->NumberValue();

        HX711Wrapper* obj = ObjectWrap::Unwrap<HX711Wrapper>(args.Holder());
        obj->mSensor->setGain(gainArg);

        args.GetReturnValue().Set(Null(isolate));
}

void HX711Wrapper::New(const FunctionCallbackInfo<Value>& args) {
  	Isolate* isolate = args.GetIsolate();

  	if (args.IsConstructCall()) {
    		// Invoked as constructor: `new HX711(...)`
    		if (args.Length() < 2) {
   			// Throw an Error that is passed back to JavaScript
    			isolate->ThrowException(Exception::TypeError(
        			String::NewFromUtf8(isolate, "You need to pass 2 arguments")));
    			return;
  		}

		uint8_t clockPinArg = (uint8_t)args[0]->NumberValue();
		uint8_t dataPinArg = (uint8_t)args[1]->NumberValue();

    		HX711Wrapper* obj = new HX711Wrapper(clockPinArg, dataPinArg);
    		obj->Wrap(args.This());
    		args.GetReturnValue().Set(args.This());
  	} else {
    		// Invoked as plain function `HX711(...)`, turn into construct call.
    		const int argc = 2;
    		Local<Value> argv[argc] = { args[0], args[1] };
    		Local<Function> cons = Local<Function>::New(isolate, constructor);
    		args.GetReturnValue().Set(cons->NewInstance(argc, argv));
  	}
}

NODE_MODULE(hx711, HX711Wrapper::InitModule)
