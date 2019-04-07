#pragma once

#include <iostream>
#include <map>
#include <list>
#include "mqtt/MqttClient.hpp"
#include "WString.h"

using namespace std;

class FakeMqttClient: public MqttClient {

public:

    void begin(const char* hostname, uint16_t port, Client& connectionClient) {};
    void connect(const char* deviceName, const char* willTopic, uint8_t willQoS, bool willRetain, const char* willMessage) {
        setWill(willTopic, willMessage);
        connected = true;
    };

    bool publish(const char* topic, const char* payload, bool retained = false) {
        if (retained) {
            cout << "MQTT: " << topic << "-> " << payload << " [RETAINED]"  << " (FAKE)" << endl;
            retainedMessages[topic] = payload;
        } else {
            cout << "MQTT: " << topic << "-> " << payload << " (FAKE)" << endl;
            messages[topic] = payload;
        }
        return true;
    }

    bool subscribe(const char* topic) {
        cout << "MQTT subscribe: " << topic << " (FAKE)" << endl;
        subscribedTopics.push_back(topic);
        return true;
    }

    bool loop() {
        return connected;
    }


    void setConnected(bool _connected) {
        connected = _connected;
    }

    String getValuePublishedTo(String topic, bool shouldBeRetained = false) {
        if (shouldBeRetained) {
            return retainedMessages[topic];
        } else {
            return messages[topic];
        }
    }

    String getLastWillTo(String topic) {
        return wills[topic];
    }

    bool isSubscribedTo(String topic) {
        for (const String &subTopic : subscribedTopics) {
            if (subTopic == topic) {
                return true;
            }
        }
        
        return false;
    }


private:

    void setWill(const char* topic, const char* payload) {
        cout << "MQTT will: " << topic << "-> " << payload << " (FAKE)" << endl;
        wills[topic] = payload; 
    }

    bool connected = false;
    map<String, String> messages;
    map<String, String> retainedMessages;
    list<String> subscribedTopics;
    map<String, String> wills;

};