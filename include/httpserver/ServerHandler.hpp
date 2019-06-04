#pragma once

#include <functional>
#include "WString.h"
#include "HttpMethod.hpp"

class ServerHandler {
public:
    typedef std::function<void(const String&)> THandlerFunction;
    ServerHandler(HttpMethod _method, String _path, THandlerFunction _fn): method(_method), path(_path), handleFunction(_fn) {};
    HttpMethod getMethod() { return method; };
    String& getPath() { return path; };
    void handle(const String& body) { handleFunction(body); };
private:
    HttpMethod method;
    String path;
    THandlerFunction handleFunction;
};