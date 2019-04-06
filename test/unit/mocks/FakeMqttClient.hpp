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
    void connect(const char* deviceName) {};

    bool publish(const char* topic, const char* payload) {
        cout << "MQTT: " << topic << "-> " << payload << " (FAKE)" << endl;
        values[topic] = payload;
        return true;
    }

    bool subscribe(const char* topic) {
        cout << "MQTT subscribe: " << topic << " (FAKE)" << endl;
        subscribedTopics.push_back(topic);
        return true;
    }

    void setWill(const char* topic, const char* payload) {
        cout << "MQTT will: " << topic << "-> " << payload << " (FAKE)" << endl;
        wills[topic] = payload; 
    }

    String getValuePublishedTo(String topic) {
        return values[topic];
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
    map<String, String> values;
    list<String> subscribedTopics;
    map<String, String> wills;

};