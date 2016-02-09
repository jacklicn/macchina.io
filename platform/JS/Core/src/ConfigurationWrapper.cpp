//
// ConfigurationWrapper.cpp
//
// $Id: //poco/1.4/JS/Core/src/ConfigurationWrapper.cpp#5 $
//
// Library: JSCore
// Package: JSCore
// Module:  ConfigurationWrapper
//
// Copyright (c) 2013-2014, Applied Informatics Software Engineering GmbH.
// All rights reserved.
//
// SPDX-License-Identifier: Apache-2.0
//


#include "Poco/JS/Core/ConfigurationWrapper.h"
#include "Poco/Util/AbstractConfiguration.h"


namespace Poco {
namespace JS {
namespace Core {


ConfigurationWrapper::ConfigurationWrapper()
{
}


ConfigurationWrapper::~ConfigurationWrapper()
{
}


v8::Handle<v8::ObjectTemplate> ConfigurationWrapper::objectTemplate(v8::Isolate* pIsolate)
{
	v8::EscapableHandleScope handleScope(pIsolate);
	v8::Local<v8::ObjectTemplate> configurationTemplate = v8::ObjectTemplate::New();
	configurationTemplate->SetInternalFieldCount(1);
	configurationTemplate->Set(v8::String::NewFromUtf8(pIsolate, "getInt"), v8::FunctionTemplate::New(pIsolate, getInt));
	configurationTemplate->Set(v8::String::NewFromUtf8(pIsolate, "getDouble"), v8::FunctionTemplate::New(pIsolate, getDouble));
	configurationTemplate->Set(v8::String::NewFromUtf8(pIsolate, "getBool"), v8::FunctionTemplate::New(pIsolate, getBool));
	configurationTemplate->Set(v8::String::NewFromUtf8(pIsolate, "getString"), v8::FunctionTemplate::New(pIsolate, getString));
	configurationTemplate->Set(v8::String::NewFromUtf8(pIsolate, "getObject"), v8::FunctionTemplate::New(pIsolate, getObject));
	configurationTemplate->Set(v8::String::NewFromUtf8(pIsolate, "has"), v8::FunctionTemplate::New(pIsolate, has));
	configurationTemplate->Set(v8::String::NewFromUtf8(pIsolate, "set"), v8::FunctionTemplate::New(pIsolate, set));
	configurationTemplate->Set(v8::String::NewFromUtf8(pIsolate, "keys"), v8::FunctionTemplate::New(pIsolate, keys));
	return handleScope.Escape(configurationTemplate);
}
	

void ConfigurationWrapper::getInt(const v8::FunctionCallbackInfo<v8::Value>& args)
{
	if (args.Length() < 1) return;
	v8::HandleScope scope(args.GetIsolate());
	Poco::Util::AbstractConfiguration* pConfig = Wrapper::unwrapNative<Poco::Util::AbstractConfiguration>(args);
	std::string key = toString(args[0]);
	try
	{
		if (args.Length() > 1 && args[1]->IsNumber())
		{
			args.GetReturnValue().Set(pConfig->getInt(key, args[1]->Int32Value()));
		}
		else 
		{
			args.GetReturnValue().Set(pConfig->getInt(key));
		}
	}
	catch (Poco::Exception& exc)
	{
		returnException(args, exc);
	}
}


void ConfigurationWrapper::getDouble(const v8::FunctionCallbackInfo<v8::Value>& args)
{
	if (args.Length() < 1) return;
	v8::HandleScope scope(args.GetIsolate());
	Poco::Util::AbstractConfiguration* pConfig = Wrapper::unwrapNative<Poco::Util::AbstractConfiguration>(args);
	std::string key = toString(args[0]);
	try
	{
		if (args.Length() > 1 && args[1]->IsNumber())
		{
			args.GetReturnValue().Set(pConfig->getDouble(key, args[1]->NumberValue()));
		}
		else 
		{
			args.GetReturnValue().Set(pConfig->getDouble(key));
		}
	}
	catch (Poco::Exception& exc)
	{
		returnException(args, exc);
	}
}


void ConfigurationWrapper::getBool(const v8::FunctionCallbackInfo<v8::Value>& args)
{
	if (args.Length() < 1) return;
	v8::HandleScope scope(args.GetIsolate());
	Poco::Util::AbstractConfiguration* pConfig = Wrapper::unwrapNative<Poco::Util::AbstractConfiguration>(args);
	std::string key = toString(args[0]);
	try
	{
		if (args.Length() > 1 && args[1]->IsBoolean())
		{
			args.GetReturnValue().Set(pConfig->getBool(key, args[1]->BooleanValue()));
		}
		else 
		{
			args.GetReturnValue().Set(pConfig->getBool(key));
		}
	}
	catch (Poco::Exception& exc)
	{
		returnException(args, exc);
	}
}


void ConfigurationWrapper::getString(const v8::FunctionCallbackInfo<v8::Value>& args)
{
	if (args.Length() < 1) return;
	v8::HandleScope scope(args.GetIsolate());
	Poco::Util::AbstractConfiguration* pConfig = Wrapper::unwrapNative<Poco::Util::AbstractConfiguration>(args);
	std::string key = toString(args[0]);
	try
	{
		if (args.Length() > 1)
		{
			returnString(args, (pConfig->getString(key, toString(args[1]))));
		}
		else 
		{
			returnString(args, (pConfig->getString(key)));
		}
	}
	catch (Poco::Exception& exc)
	{
		returnException(args, exc);
	}
}


void ConfigurationWrapper::getObject(const v8::FunctionCallbackInfo<v8::Value>& args)
{
	if (args.Length() < 1) return;
	v8::HandleScope scope(args.GetIsolate());
	Poco::Util::AbstractConfiguration* pConfig = Wrapper::unwrapNative<Poco::Util::AbstractConfiguration>(args);
	std::string key = toString(args[0]);
	try
	{
		if (args.Length() > 1 && !pConfig->has(key))
		{
			args.GetReturnValue().Set(args[1]);
		}
		else 
		{
			std::string json = pConfig->getString(key);
			v8::Local<v8::String> jsonString = v8::String::NewFromUtf8(args.GetIsolate(), json.c_str());
			v8::Local<v8::Value> value = v8::JSON::Parse(jsonString);
			if (!value.IsEmpty())
				args.GetReturnValue().Set(value);
			else
				throw Poco::DataFormatException(std::string("Invalid JSON in configuration property ") + key, json);
		}
	}
	catch (Poco::Exception& exc)
	{
		returnException(args, exc);
	}
}


void ConfigurationWrapper::has(const v8::FunctionCallbackInfo<v8::Value>& args)
{
	if (args.Length() < 1) return;
	v8::HandleScope scope(args.GetIsolate());
	Poco::Util::AbstractConfiguration* pConfig = Wrapper::unwrapNative<Poco::Util::AbstractConfiguration>(args);
	std::string key = toString(args[0]);
	try
	{
		args.GetReturnValue().Set(pConfig->has(key));
	}
	catch (Poco::Exception& exc)
	{
		returnException(args, exc);
	}
}


void ConfigurationWrapper::set(const v8::FunctionCallbackInfo<v8::Value>& args)
{
	if (args.Length() < 2) return;
	v8::HandleScope scope(args.GetIsolate());
	Poco::Util::AbstractConfiguration* pConfig = Wrapper::unwrapNative<Poco::Util::AbstractConfiguration>(args);
	std::string key = toString(args[0]);

	// use built-in JSON.stringify() 
	v8::Local<v8::Context> context = args.GetIsolate()->GetCurrentContext();
	v8::Local<v8::Object> global = context->Global();
	v8::Local<v8::Object> json = global->Get(v8::String::NewFromUtf8(args.GetIsolate(), "JSON"))->ToObject();
	v8::Local<v8::Function> stringify = v8::Handle<v8::Function>::Cast(json->Get(v8::String::NewFromUtf8(args.GetIsolate(), "stringify")));
	v8::Local<v8::Value> argv[1] = {args[1]};
	std::string value = toString(stringify->Call(json, 1, argv));

	try
	{
		pConfig->setString(key, value);
	}
	catch (Poco::Exception& exc)
	{
		returnException(args, exc);
	}
}


void ConfigurationWrapper::keys(const v8::FunctionCallbackInfo<v8::Value>& args)
{
	v8::HandleScope scope(args.GetIsolate());
	Poco::Util::AbstractConfiguration* pConfig = Wrapper::unwrapNative<Poco::Util::AbstractConfiguration>(args);
	std::string key;
	if (args.Length() > 0)
		key = toString(args[0]);
	try
	{
		Poco::Util::AbstractConfiguration::Keys keys;
		pConfig->keys(key, keys);
		v8::Local<v8::Array> keysArray = v8::Array::New(args.GetIsolate(), static_cast<int>(keys.size()));
		for (unsigned i = 0; i < static_cast<unsigned>(keys.size()); i++)
		{
			keysArray->Set(i, v8::String::NewFromUtf8(
				args.GetIsolate(), 
				keys[i].c_str(), 
				v8::String::kNormalString,
				static_cast<int>(keys[i].length())));
		}
		args.GetReturnValue().Set(keysArray);
	}
	catch (Poco::Exception& exc)
	{
		returnException(args, exc);
	}	
}


} } } // namespace Poco::JS::Core
