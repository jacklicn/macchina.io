//
// SessionWrapper.h
//
// $Id: //poco/1.4/JS/Data/include/Poco/JS/Data/SessionWrapper.h#6 $
//
// Library: JSData
// Package: Data
// Module:  SessionWrapper
//
// Definition of the SessionWrapper class.
//
// Copyright (c) 2013-2014, Applied Informatics Software Engineering GmbH.
// All rights reserved.
//
// SPDX-License-Identifier: Apache-2.0
//


#ifndef JS_Data_SessionWrapper_INCLUDED
#define JS_Data_SessionWrapper_INCLUDED


#include "Poco/JS/Data/Data.h"
#include "Poco/JS/Core/Wrapper.h"
#include "Poco/Data/Session.h"


namespace Poco {
namespace JS {
namespace Data {


class JSData_API SessionHolder
{
public:
	SessionHolder(const std::string& connector, const std::string& connectionString);
		/// Creates the SessionHolder.
		
	~SessionHolder();
		/// Destroys the SessionHolder.

	const std::string& connector() const
	{
		return _connector;
	}
	
	const std::string& connectionString() const
	{
		return _connectionString;
	}
	
	Poco::Data::Session& session()
	{
		return _session;
	}
	
	unsigned getPageSize() const
	{
		return _pageSize;
	}
	
	void setPageSize(unsigned pageSize)
	{
		_pageSize = pageSize;
	}
	
private:
	std::string _connector;
	std::string _connectionString;
	unsigned _pageSize;
	Poco::Data::Session _session;
};


class JSData_API SessionWrapper: public JS::Core::Wrapper
	/// JavaScript wrapper for Poco::Data::Session.
{
public:
	SessionWrapper();
		/// Creates the SessionWrapper.
	
	~SessionWrapper();
		/// Destroys the SessionWrapper.

	v8::Handle<v8::FunctionTemplate> constructor(v8::Isolate* pIsolate);
		/// Creates and returns a V8 FunctionTemplate for the constructor function.

	static void construct(const v8::FunctionCallbackInfo<v8::Value>& args);
		/// Creates a JavaScript Session object.

	// Wrapper
	v8::Handle<v8::ObjectTemplate> objectTemplate(v8::Isolate* pIsolate);
		
protected:
	static void getConnector(v8::Local<v8::String> name, const v8::PropertyCallbackInfo<v8::Value>& info);
	static void getConnectionString(v8::Local<v8::String> name, const v8::PropertyCallbackInfo<v8::Value>& info);
	static void getIsConnected(v8::Local<v8::String> name, const v8::PropertyCallbackInfo<v8::Value>& info);
	static void getIsTransaction(v8::Local<v8::String> name, const v8::PropertyCallbackInfo<v8::Value>& info);
	static void getPageSize(v8::Local<v8::String> name, const v8::PropertyCallbackInfo<v8::Value>& info);
	static void setPageSize(v8::Local<v8::String> name, v8::Local<v8::Value> value, const v8::PropertyCallbackInfo<void>& info);

	static void begin(const v8::FunctionCallbackInfo<v8::Value>& args);
	static void commit(const v8::FunctionCallbackInfo<v8::Value>& args);
	static void rollback(const v8::FunctionCallbackInfo<v8::Value>& args);
	static void close(const v8::FunctionCallbackInfo<v8::Value>& args);
	static void execute(const v8::FunctionCallbackInfo<v8::Value>& args);
};


} } } // namespace Poco::JS::Data


#endif // JS_Data_SessionWrapper_INCLUDED
