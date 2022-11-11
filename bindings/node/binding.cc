#include "tree_sitter/parser.h"
#include <node.h>
#include "nan.h"

using namespace v8;

extern "C" TSLanguage * tree_sitter_javascript();

namespace {

NAN_METHOD(New) {}

NODE_MODULE_INIT(/* exports, module, context */) {
  Local<FunctionTemplate> tpl = Nan::New<FunctionTemplate>(New);
  tpl->SetClassName(Nan::New("Language").ToLocalChecked());
  tpl->InstanceTemplate()->SetInternalFieldCount(1);

  Local<Function> constructor = Nan::GetFunction(tpl).ToLocalChecked();
  Local<Object> instance = constructor->NewInstance(Nan::GetCurrentContext()).ToLocalChecked();
  Nan::SetInternalFieldPointer(instance, 0, tree_sitter_javascript());

  Nan::Set(instance, Nan::New("name").ToLocalChecked(), Nan::New("javascript").ToLocalChecked());

  Nan::MaybeLocal<v8::Object> moduleObj = Nan::To<v8::Object>(module);
  Nan::Set(moduleObj.ToLocalChecked(), Nan::New("exports").ToLocalChecked(), instance);
}

}  // namespace
