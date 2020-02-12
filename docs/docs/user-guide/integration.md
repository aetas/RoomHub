This page describes how to configure home automation applications (like Home Assistant and OpenHab) to integrate them and control devices connected to RoomHub.

## General communication

RoomHub works as a MQTT gateway. This means you can integrate it to any home automation platform which supports MQTT devices. Both Home Assistant and RoomHub have solid support for MQTT.

RoomHub follows [Homie convention](https://homieiot.github.io/) 3.0.1 for MQTT communication. 
Homies MQTT topic layout follows the pattern **homie/device/node/property**.

**Device** is a name of your RoomHub (see how to set name in [configuration](configuration.md)).

**Node** is a unique number identifier of the sensor/controller connected to RoomHub (*id* in [configuration](configuration.md)).

**Property** can be a "temperature" when reading value from BME280 module or "state" in case of PIR motion sensor.

Examples:

- `homie/MyRoomHub/2/temperature` for reading temperature from BME280 on id = 2
- `homie/MyRoomHub/5/humidity` for reading humidity from BME280 on id = 5
- `homie/MyRoomHub/7/state` for reading motion sensor state on id = 7 (`1` if motion has been captured, `0` otherwise)

When device supports setting a value (e.g. relay), desired value should be send to *homie/device/node/property/set* topic 

Example:

- send `ON` to `homie/MyRoomHub/3/state/set` to switch on light connected to relay on id = 3



## OpenHab

Although RoomHub follows Homie convention 3.0.1 and OpenHab claims to support auto-discovery of devices following this convention, there are some incompatibilities. As of OpenHab 2.4.0 using MQTT Homie Binding is not recommended.

For now - recommended way is to use [MQTT Binding 1.x](https://www.openhab.org/addons/bindings/mqtt1/) and configure all devices in text files.  
You need to add OpenHab items in the configuration files with proper MQTT topic to send/receive messages to/from RoomHub.

Example below shows configuration of relay module (with id = 1) connected to RoomHub which enables you to control the light.

```
Switch light_Bedroom_Main "Bedroom light" <light> {mqtt=">[mymqtt:homie/MyRoomHub/1/state/set:command:ON:ON],>[mymqtt:homie/MyRoomHub/1/state/set:command:OFF:OFF]"}
```

Example below shows configuration of motion sensor (with id = 14) connected to RoomHub.

```
Switch motionSensor_Corridor "Motion sensor in corridor" {mqtt="<[mymqtt:homie/MyRoomHub/14/state:command:ON:1],<[mymqtt:homie/MyRoomHub/14/state:command:OFF:0"}
```

## Home Assistant

Home Assistant 0.104.3 does not support Homie convention with discovery feature. That means you need to manually configure devices connected to RoomHub. Fortunately, this is quite easy.

Example below shows configuration of relay module (with id = 1) connected to RoomHub which enables you to control the light.

```yaml
switch:
  - platform: mqtt
    name: "Bedroom Light"
    state_topic: "homie/MyRoomHub/1/state"
    command_topic: "homie/MyRoomHub/1/state/set"
    retain: true
```

Example below shows configuration of motion sensor (with id = 14) connected to RoomHub.

```yaml
binary_sensor:
  - platform: mqtt
    name: "Motion sensor in corridor"
    state_topic: "homie/MyRoomHub/14/state"
    payload_on: 1
    payload_off: 0
```