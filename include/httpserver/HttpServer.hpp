#pragma once

#include <Arduino.h>

class HttpServer {
public:
    void handleClient(Client& client);
    void on(const String& method, const String& path);
};

/**
POST /config/reset HTTP/1.1
Host: 10.0.88.42
User-Agent: curl/7.58.0
Accept: *\/*
Content-Type: text/plain
Content-Length: 25

test 12893712 kdjflksdjfs

 */