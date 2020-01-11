### RoomHub cannot connect to MQTT, even when configured MQTT hostname is correct
Some ESP32 modules have problems with connection client, probably because of some previously stored data.
Currently the only proved workaround is to change firmware temporarily to call `Client.flush();`.


### RoomHub disconnects from MQTT from time to time when RoomHub is connected via ethernet cable
This is a known issue with W5500. Currently there is not known solutions for that. If you have encountered this problem - please use WiFi instead.
We are tracking this problem in [GitHub issue](https://github.com/aetas/RoomHub/issues/9).

### Switch button doesn't work properly - sometimes it sends message multiple times even when pressed once
Debounce value is too low. See [Switch button in supported devices section](supported-devices.md) for details. 