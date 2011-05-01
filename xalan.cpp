#include <string>
#include <v8.h>
#include <node.h>

#include <xalanc/Include/PlatformDefinitions.hpp>
#include <xercesc/util/PlatformUtils.hpp>
#include <xalanc/XalanTransformer/XalanTransformer.hpp>

using namespace std;
using namespace v8;
using namespace node;
XALAN_USING_XERCES(XMLPlatformUtils)
XALAN_USING_XALAN(XalanTransformer)

#define REQ_ARGS(N)                                                     \
  if (args.Length() < (N))                                              \
    return ThrowException(Exception::TypeError(                         \
                             String::New("Expected " #N " arguments"))); 

#define REQ_STR_ARG(I, VAR)                                             \
  if (args.Length() <= (I) || !args[I]->IsString())                     \
    return ThrowException(Exception::TypeError(                         \
                  String::New("Argument " #I " must be a string"))); \
  String::Utf8Value VAR(args[I]->ToString());

static Handle<Value> initialize(const Arguments& args)
{
    XMLPlatformUtils::Initialize();
    XalanTransformer::initialize();
}

static Handle<Value> cleanup(const Arguments& rgs)
{
    XalanTransformer::terminate();
    XMLPlatformUtils::Terminate();
}

static Handle<Value> transform(const Arguments& args)
{
    REQ_ARGS(3);

    REQ_STR_ARG(0, xmlIn);
    REQ_STR_ARG(1, xslIn);
    REQ_STR_ARG(2, xmlOut);

    XalanTransformer theXalanTransformer;
    int Result = theXalanTransformer.transform(*xmlIn, *xslIn, *xmlOut);

    return Integer::New(Result);
}

extern "C" {
    static void init(Handle<Object> target) 
    {
        NODE_SET_METHOD(target, "transform", transform);
        NODE_SET_METHOD(target, "initialize", initialize);
        NODE_SET_METHOD(target, "cleanup", cleanup);
    }
    
    NODE_MODULE(xalan, init);
} 
