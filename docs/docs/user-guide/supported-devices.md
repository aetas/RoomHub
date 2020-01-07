
This is a list of devices currently supported by RoomHub. That means you can connect device either with digital, analog or PJON connection to RoomHub and configure it with RoomHub Configurator.

All supported devices need to be compatible with 5V power supply.

The name in the parenthesis in the header is used in configuration 

[TODO: add configuration examples to each device]

### Digital devices

#### Relay module
Relay module which allows to control turning on/off electrical devices and lights. Controlled with LOW signal.

- configuration type: `RELAY`
- additional configuration: NONE

<details>
  <summary>Example configuration</summary>
  ```yaml
  [...]
  rooms:
  - name: "workshop"
    points:
    - name: "point with relay"
      portNumber: 1
      devices:
      - name: "relay name"
        id: 1
        wires: ["BLUE"]
        type: RELAY
  ```
</details>


#### Switch button
Switch button or push button.

- configuration type: `SWITCH_BUTTON`
- additional configuration: 
    - `debounceMs` [default: 0] - number of milliseconds for debounce (helps to avoid flickering)


#### Emulated switch
Emulates switch button press with changing digital output from HIGH to LOW for 500ms and back to HIGH state. It is useful for controlling devices which has possibility to connect switch button (e.g. garage gate opener).

- configuration type: `EMULATED_SWITCH`
- additional configuration: NONE


#### Motion detector
PIR Motion Sensor/Detector.

- configuration type: `MOTION_DETECTOR`
- additional configuration:
    - `debounceMs` [default: 0] - number of milliseconds for debounce (helps to avoid flickering)


#### Digital input
General purpose single digital input. Can be used for measuring state on any digital input. Works for devices like buttons (prefer `SWITCH_BUTTON`) or motion sensor (prefer `MOTION_DETECTOR`).

- configuration type: `DIGITAL_INPUT`
- additional configuration:
    - `debounceMs` [default: 0] - number of milliseconds for debounce (helps to avoid flickering)

#### Digital output
General purpose single digital output. Can be used for generating digital signal on single wire. Works for devices like relay (prefer `RELAY`).

- configuration type: `DIGITAL_OUTPUT`
- additional configuration: NONE



### Analog devices

#### SCT013
Non-invasive AC Current Sensor (SCT-013-000). It allows to measure current.

- configuration type: `SCT013`
- additional configuration: NONE


### PJON devices

This group of devices requires PJON controller on the side of the device for communication with RoomHub. 

#### BME280
Temperature and humidity sensor. Requires PJON controller.

- configuration type: `BME280`
- additional configuration:
    - `pjonId` [default: 0] - PJON controller identifier on PJON bus (0 means it will be assigned automatically) [TODO: do we support automatic assignment in current version?]



## Support planned in the next version

#### DHT22 (`DHT22`) [GitHub issue #12](https://github.com/aetas/RoomHub/issues/12)
Temperature and humidity sensor.