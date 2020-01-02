### RoomHub cannot connect to MQTT, even when configured MQTT hostname is correct
Some ESP32 modules have problems with connection client, probably because of some previously stored data. See GitHub issue for more details https://github.com/espressif/arduino-esp32/issues/180 .
Currently the only proved workaround is to change firmware temporarily to call `Client.flush();`.


### RoomHub disconnects from MQTT from time to time
[TODO describe problem]

### Switch button doesn't work properly - sometimes it sends message once and sometimes multiple times
Debounce value is too low. See [Switch button in supported devices section](supported-devices.md) for details. 