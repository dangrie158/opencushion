#include <node.h>
#include <node_object_wrap.h>
#include "hx711.h"

class HX711Wrapper : public node::ObjectWrap {

public:
	static void InitModule(v8::Local<v8::Object> exports);

private:
	explicit HX711Wrapper(uint8_t clockPin, uint8_t dataPin);
	~HX711Wrapper();
  	static void New(const v8::FunctionCallbackInfo<v8::Value>& args);
	static v8::Persistent<v8::Function> constructor;
	static void read(const v8::FunctionCallbackInfo<v8::Value>& args);
	static void setScale(const v8::FunctionCallbackInfo<v8::Value>& args);
	static void setOffset(const v8::FunctionCallbackInfo<v8::Value>& args);
	static void tare(const v8::FunctionCallbackInfo<v8::Value>& args);
	static void getUnits(const v8::FunctionCallbackInfo<v8::Value>& args);
	static void setGain(const v8::FunctionCallbackInfo<v8::Value>& args);
	static void getScale(const v8::FunctionCallbackInfo<v8::Value>& args);
	static void getOffset(const v8::FunctionCallbackInfo<v8::Value>& args);
	HX711* mSensor;
};

