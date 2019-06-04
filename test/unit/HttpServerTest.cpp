#include "../main/catch.hpp"
#include "httpserver/HttpServer.hpp"

#include "mocks/FakeHttpClient.hpp"
#include "mocks/ArduinoLog.h"

#include <typeinfo>
#include <iostream>
using namespace std;

TEST_CASE("HttpServer") {

    HttpServer server;
    FakeHttpClient client;

    SECTION("should call given 'on' function when called with specified method and path") {
        // given
        bool shouldNotBeHit = false;
        bool shouldHaveBeenHit = false;
        server.on(HttpMethod::GET, "/server/test", [&shouldNotBeHit](const String& body) { shouldNotBeHit = true; });
        server.on(HttpMethod::POST, "/server/test", [&shouldHaveBeenHit](const String& body) { shouldHaveBeenHit = true; });
        client.setReceived("POST", "/server/test", "blablabla", 9);
        // when
        server.handleClient(client);
        // then
        REQUIRE(shouldNotBeHit == false);
        REQUIRE(shouldHaveBeenHit == true);
    }

    SECTION("should respond to client with specified code and body") {
        // given
        server.on(HttpMethod::POST, "/testserver/createitem", [&server](const String& body) { 
            String responseString = "created item: " + body;
            server.send(201, "text/plain", responseString); 
        });
        client.setReceived("POST", "/testserver/createitem", "test 123", 8);
        // when
        server.handleClient(client);
        // then
        String expectedResponse = "HTTP/1.1 201 CREATED\n";
        expectedResponse += "Content-Type: text/plain\n";
        expectedResponse += "Connection: close\n\n";
        expectedResponse += "created item: test 123";
        REQUIRE(client.getSentMessage() == expectedResponse);
    }

    SECTION("should read content with length specified by Content-Length from client until client is connected") {
        // given
        String fullBody = "";
        server.on(HttpMethod::PUT, "/testserver/someupdate", [&server, &fullBody](const String& body) {
            fullBody = body;
            server.send(201, "text/plain", "some response");
        });
        client.setReceived("PUT", "/testserver/someupdate", "one", 11);
        client.appendToMessageBody("two");
        client.appendToMessageBody("three");
        // when
        server.handleClient(client);
        // then
        REQUIRE(fullBody == "onetwothree");
    }

     SECTION("should return 404 when there are no suitable handler for request") {
        // given
        server.on(HttpMethod::GET, "/testserver/endpoint", [&server](const String& body) {
            server.send(200, "text/plain", "some response");
        });
        client.setReceived("GET", "/testserver/unknownendpoint", "", 0);
        // when
        server.handleClient(client);
        // then
        REQUIRE(client.getSentMessage().startsWith("HTTP/1.1 404 NOT_FOUND"));
    }

    SECTION("should be able to read body when new-lines are with \\r\\n instead of \\n") {
        // given
        String readBody = "";
        server.on(HttpMethod::PUT, "/testserver/newlines", [&readBody](const String& body) { readBody = body; });
        client.setRawReceived("PUT /testserver/newlines HTTP/1.1\r\nAccept: */*\r\nContent-Length: 10\r\n\r\nsome value");
        // when
        server.handleClient(client);
        // then
        REQUIRE(readBody == "some value");
    }
}