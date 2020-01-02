
!!! info
    This quick start guide assumes you have RoomHub hardware ready. If you are looking for how to prepare the hardware - look into [hardware section](../hardware/board-layout.md).



Quick start guide shows how to connect relay module and configure to work with it RoomHub. Connecting other types of devices is similar and can be done with the same steps.  


## What do you need
- Assembled Aetas RoomHub 3
- [PlatformIO](https://platformio.org/) installed
- WiFi network
- Mobile phone (Android or iOS)
- Running MQTT broker (e.g. Mosquitto)
- MQTT client installed on your computer (e.g. [MQTT.js](https://github.com/mqttjs/MQTT.js#readme))
- UTP cable
- relay module


## Connect and configure device

[TODO: this is only template add all needed elements and polish it]

!!! warning 
    Make sure RoomHub is never connected to power supply and USB port at the same time. This will destroy the device and may damage your computer.

1. Install RoomHub firmware (see [instruction](https://github.com/aetas/roomhub#installation))
2. Connect RoomHub to power supply (make sure it is not connected to USB)
3. Keep button 1 pressed on RoomHub and restart it by pressing "EN" button on ESP32 (keep button 1 pressed until blue LED will blink 3 times - around 5 seconds)
4. Use [ESP8266 SmartConfig](https://play.google.com/store/apps/details?id=com.cmmakerclub.iot.esptouch&hl=en) (on Android) or [EspTouch](https://apps.apple.com/us/app/espressif-esptouch/id1071176700) (on iOS) to connect RoomHub to your WiFi network
    1. connect with your phone to the WiFi network you want RoomHub to be connected
    2. Put your WiFi password in the application 
    3. Press "Confirm" in the app
    4. After some time you should get information about successful connection and IP address assigned to RoomHub (save this IP for later)

    [TODO: add photo with buttons to press shown and powers supply port]
    [TODO: add screenshots from mobile apps]

5. 

3. Prepare UTP cable with plug on one side (according to standard T568B)
[![cable termination](images/T568B.png){: style="height:150px; display: block; margin: 0 auto;transform: rotate(90deg)"}](images/T568B.png)

4. Connect module to UTP cable
    - VCC (orange wire)
    - ground (orange-white wire)
    - control (blue wire)
    - [TODO: photo with module connected to wires]

5. Connect module to RoomHub port 1
    - [TODO: photo with cable plugged into port 1]
6. Prepare configuration file in YAML - look into comments to find out which value to change<br>
```yaml
configVersion: "3.0"
name: "TestRoomHub"
destinationIpAddress: "192.168.1.66" # IP of RoomHub (see point 1.)
mqttHostname: "192.168.1.52" # IP of your MQTT broker
network: # only for Ethernet - leave as it is for WiFi connection
  macAddress: "6D:CB:54:AD:E9:93"
  ipAddress: "0.0.0.0"
rooms:
  - name: "workshop"
    points:
      - name: "point with test relay"
        portNumber: 1
        devices:
          - name: "test relay"
            id: 1
            wires: ["BLUE"]
            type: RELAY
```
<br>
For more details on configuration files see [Configuration with RoomHub Configurator](configuration.md#configuration-with-roomhub-configurator)
[TODO: add information which values to change and how]

7. Apply configuration with configurator
   - Download latest version of RoomHub Configurator from [GitHub release page](https://github.com/aetas/RoomHubConfigurator/releases)
   - Run Configurator CLI with command 
     - on Linux/MacOS `./rhc workshop.roomhub.yml`
     - on Windows `rhc.bat workshop.roomhub.yml`

8. Try to send MQTT message to RoomHub to turn switch relay
```

```
[TODO: more points?]

[TODO: go through points with device and check that everything is described - ask Piotr or Ania to do that]
