# RoomHub

> :warning: This project is now deprecated in favor of [MqGateway](https://github.com/aetas/mqgateway) project.

[![Build Status](https://dev.azure.com/ManiekQ/mariusz/_apis/build/status/RoomHub?branchName=master)](https://dev.azure.com/ManiekQ/mariusz/_build/latest?definitionId=1&branchName=master)


## Installation

**WARNING: Make sure RoomHub is not connected to power supply before connecting it to USB. Connecting both will destroy RoomHub and may break you computer.**

1. Install [PlatformIO Core](https://docs.platformio.org/en/latest/installation.html) or [PlatformIO IDE](https://platformio.org/platformio-ide)
2. Download [latest release](https://github.com/aetas/RoomHub/releases/latest) source code (see "Assets" section)
3. Extract sources
4. Open command line in your OS and go to directory you've just extracted
5. Connect RoomHub ESP32 to your PC with USB cable
6. Run `platformio run --target upload`

You may need to uncomment and change `upload_port` in "platformio.ini" file if you get connection errors.

