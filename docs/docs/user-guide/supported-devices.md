
This is a list of devices currently supported by RoomHub. That means you can connect device either with digital, analog or PJON connection to RoomHub and configure it with RoomHub Configurator.

All supported devices need to be compatible with 5V power supply.

The name in the parenthesis in the header is used in configuration 

### Digital devices

#### Relay module (`RELAY`)
Relay module which allows to control turning on/off electrical devices and lights. Controlled with LOW signal.

- Additional configuration: NONE


#### Switch button (`SWITCH_BUTTON`) 
Switch button or push button.

- Additional configuration: 
    - `debounceMs` [default: 0] - number of milliseconds for debounce (helps to avoid flickering)


#### Emulated switch (`EMULATED_SWITCH`)
Emulates switch button press with changing digital output from HIGH to LOW for 500ms and back to HIGH state. It is useful for controlling devices which has possibility to connect switch button (e.g. garage gate opener).

- Additional configuration: NONE


#### Motion detector (`MOTION_DETECTOR`)
PIR Motion Sensor/Detector.

- Additional configuration:
    - `debounceMs` [default: 0] - number of milliseconds for debounce (helps to avoid flickering)


#### Digital input (`DIGITAL_INPUT`)
General purpose single digital input. Can be used for measuring state on any digital input. Works for devices like buttons (prefer `SWITCH_BUTTON`) or motion sensor (prefer `MOTION_DETECTOR`).

- Additional configuration:
    - `debounceMs` [default: 0] - number of milliseconds for debounce (helps to avoid flickering)

#### Digital output (`DIGITAL_OUTPUT`)
General purpose single digital output. Can be used for generating digital signal on single wire. Works for devices like relay (prefer `RELAY`).

- Additional configuration: NONE



### Analog devices

#### SCT013 (`SCT013`)
Non-invasive AC Current Sensor (SCT-013-000). It allows to measure current.

- Additional configuration: NONE


### PJON devices

This group of devices requires PJON controller on the side of the device for communication with RoomHub. 

PJON devices are not yet supported in current version of RoomHub ([see issue on Github](https://github.com/aetas/RoomHub/issues/6)).

#### BME280 (`BME280`) [GitHub issue #6](https://github.com/aetas/RoomHub/issues/6)
Temperature and humidity sensor. Requires PJON controller.

-  Additional configuration:
    - `pjonId` [default: 0] - PJON controller identifier on PJON bus (0 means it will be assigned automatically) [TODO: do we support automatic assignment in current version?]



## Support planned in the next version

#### DHT22 (`DHT22`) [GitHub issue #12](https://github.com/aetas/RoomHub/issues/12)
Temperature and humidity sensor.