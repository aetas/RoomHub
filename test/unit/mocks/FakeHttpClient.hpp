#pragma once

#include <iostream>
#include <Client.h>
#include <list>

using namespace std;

class FakeHttpClient: public Client {
public:
    int connect(const char *host, uint16_t port) { return 1; };
    size_t write(uint8_t val) {  sentMessage = String(val); return 1; };
    size_t write(const uint8_t *buf, size_t size) { sentMessage = String((const char*)buf); return size; };
    int available() { return currentReceivedMessage().length() - readPointer; };
    int read() { return currentReceivedMessage().charAt(readPointer++); };
    int read(uint8_t *buf, size_t size) {
        String message = currentReceivedMessage();
        message.substring(readPointer, readPointer + size);
        int toReturn = message.charAt(readPointer); 
        readPointer = readPointer + size;
        return toReturn;
    };
    int peek() { return currentReceivedMessage().charAt(readPointer); };
    void flush() { receivedMessageContent.clear(); };
    void stop() { _connected = 0; };
    uint8_t connected() { return _connected; };
    operator bool() { return true; };

    void setReceived(const String& method, const String& path, const String& body, const uint8_t contentLength) {
        String receivedMessage = method + " " + path + " HTTP/1.1\n";
        receivedMessage += "Host: 10.0.0.1\n";
        receivedMessage += "User-Agent: curl/7.58.0\n";
        receivedMessage += "Accept: */*\n";
        receivedMessage += "Content-Type: text/plain\n";
        receivedMessage += "Content-Length: " + String(contentLength, 10) + "\n";
        receivedMessage += "\n";
        receivedMessage += body;
        receivedMessageContent.push_back(receivedMessage);
    }

     void setRawReceived(const String& request) {
        receivedMessageContent.push_back(request);
    }

    void appendToMessageBody(const String& bodyToAppend) {
        receivedMessageContent.push_back(bodyToAppend);
    }

    String getSentMessage() { return sentMessage; }
private:
    list<String> receivedMessageContent;
    int readPointer = 0;
    uint8_t _connected = 1;

    String sentMessage = "";

    String currentReceivedMessage() {
        String currentReceivedMessage = "";
        for (const String &receivedMessagePart : receivedMessageContent) {
            currentReceivedMessage += receivedMessagePart;
        }
        return currentReceivedMessage;
    }
};
