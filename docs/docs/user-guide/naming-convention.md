**Homie device** - same as RoomHub - it is not the same as "device" (see below)

**Device** - sensor or controller connected to RoomHub (e.g. relay module or switch button)

**PJON Controller** - Additional controller (e.g. Arduino Pro Mini) used to provide communication with RoomHub, for devices which are using other communication channels than simple digital or analog wire (e.g. serial, I2C or 1-Wire).

**Point** - each place connected to RoomHub with single ethernet/UTP cable, can have many devices connected to it

**Room** - space containing multiple points, it helps divide configuration into logical parts, but has currently no other influence after configuration is send to RoomHub (e.g. kitchen which has multiple light switches)

**Wire** - single wire of UTP cable which may be use to connect one (digital/analog) or multiple (PJON) devices.
