#pragma once

#include <WString.h>
#include <Client.h>
#include <functional>

#include "HttpMethod.hpp"
#include "ServerHandler.hpp"

class HttpServer {
public:
    ~HttpServer();
    void handleClient(Client& client);
    void on(HttpMethod method, const String& path, ServerHandler::THandlerFunction fn);
    void send(int code, const String& content_type, const String& content);

private:
    ServerHandler* handlers[16];
    uint8_t handlersSize = 0;
    Client* currentClient;

    void handle(HttpMethod method, const String& path, const String& body);
    HttpMethod methodFromString(String& methodString);
};