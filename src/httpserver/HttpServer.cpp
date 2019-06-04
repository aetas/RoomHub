#include "httpserver/HttpServer.hpp"
#include "ArduinoLog.h"

void HttpServer::handleClient(Client& client) {
    if (!client) {
        return;
    }
    bool headersProcessed = false;
    String requestString;
    String method;
    String path;
    uint16_t contentLength = 0;
    uint16_t currentContentSize = 0;
    
    while (client.connected()) {
        while (client.available()) {
            char c = client.read();
            requestString += c;
        }
        
        int16_t headersEndIndex = requestString.indexOf("\n\n");
        uint16_t bodyStartIndex = headersEndIndex + 2;
        if (headersEndIndex < 0) {
            headersEndIndex = requestString.indexOf("\r\n\r\n");
            bodyStartIndex = headersEndIndex + 4;
        }
        currentContentSize = requestString.length() - bodyStartIndex;
        
        if (headersEndIndex > -1 && !headersProcessed) { // all headers in requestString
            uint8_t endline1Index = requestString.indexOf('\n');
            String firstLine = requestString.substring(0, endline1Index);
            uint8_t endOfMethodIndex = firstLine.indexOf(' ');
            method = firstLine.substring(0, endOfMethodIndex);
            uint8_t endOfPathIndex = firstLine.indexOf(' ', endOfMethodIndex+1);
            path = firstLine.substring(endOfMethodIndex+1, endOfPathIndex);
            uint16_t contentLengthIndex = requestString.indexOf("Content-Length:");
            if (contentLengthIndex > -1) {
                String contentLengthString = requestString.substring(contentLengthIndex + 15);
                contentLengthString.trim();
                contentLength = contentLengthString.toInt();
            }
            headersProcessed = true;
        }
        if (headersProcessed && (currentContentSize >= contentLength)) { // time to read body
            String body = requestString.substring(bodyStartIndex);

            // Log.trace(F("Full request:\n%s" CR), requestString.c_str());
            Log.notice(F("Request method=%s path=%s body=%s" CR), method.c_str(), path.c_str(), body.c_str());

            currentClient = &client;
            handle(methodFromString(method), path, body);
            client.stop();
        }   
    }
}

HttpMethod HttpServer::methodFromString(String& methodString) {
    if(methodString.equals("GET")) {
        return HttpMethod::GET;
    } else if(methodString.equals("POST")) {
        return HttpMethod::POST;
    } else if(methodString.equals("PUT")) {
        return HttpMethod::PUT;
    } else if(methodString.equals("DELETE")) {
        return HttpMethod::DELETE;
    }
    return HttpMethod::GET;
}

void HttpServer::handle(HttpMethod method, const String& path, const String& body) {
    bool handled = false;
    for (int i = 0; i < handlersSize; i++) {
        ServerHandler* handler = handlers[i];
        if (handler->getMethod() == method && handler->getPath().equals(path)) {
            handler->handle(body);
            handled = true;
        }
    }
    if (!handled) {
        send(404, "text/plain", "");
    }
}

void HttpServer::on(HttpMethod method, const String& path, ServerHandler::THandlerFunction fn) {
    handlers[handlersSize++] = new ServerHandler(method, path, fn);
}

void HttpServer::send(int code, const String& contentType, const String& content) {
    String codeString = String(code);
    if (code == 200) {
        codeString = String(code) + " OK";
    } else if (code == 201) {
        codeString = String(code) + " CREATED";
    } else if (code == 404) {
        codeString = String(code) + " NOT_FOUND";
    } else if (code > 399 && code < 500) {
        codeString = String(code) + " BAD_REQUEST";
    } else {
        codeString = String(code) + " INTERNAL_SERVER_ERROR";
    }
    String response = "HTTP/1.1 " + codeString + "\n"; 
    response += "Content-Type: " + contentType + "\n";
    response += "Connection: close\n\n";
    response += content;

    // Log.trace(F("Responding with:\n%s" CR), response.c_str());
    
    currentClient->write((const uint8_t*) response.c_str(), response.length());
}

HttpServer::~HttpServer() {
    for (int i = 0; i < handlersSize; i++) {
        delete handlers[i];
    }
}