# BomboPad

BomboPad is a macropad with 12 key, 2 encoders, display and, optionally, Li-Po battery and Bluetooth module.

This repository contains only one of the compatible firmware that can be installed on the BomboPad.

The electrical schematics an other hardware related files can be found in the main project repository [bombo82/bombopad](https://github.com/bombo82/bombopad) also has links to others compatible firmware supported directly.

## Description

TBD

## Getting Started

### Prerequisites

Hardware prerequisites are to own a version of assembled PCB or to handwire che necessary schematics using a solderless breadboard and/or a stripboard. For details see [bombo82/bombopad](https://github.com/bombo82/bombopad).

Software requirements are only this repository, please read the main README in the root directly for how to build firmware.

### Firmware features and hardware capabilities

TBD

## Help

Any bug reports or ideas for improvement are really welcome. For reports and discussions GitHub features are enabled in this repository and are the preferred way.

## Version History

Software versions does not exists because taking a _"rolling release"_ approach, so every commit on the main branch is working and usable.

Support for different versions of hardware is managed through layouts. The latest hardware version works with layouts without any version prefix in the name, earlier versions might have specific layouts e.g. _v0.0_.

|Hardware| Layout         |
|--------|----------------|
|**v0.3**| without prefix |
|  v0.2  | NOT compatible |
|  v0.1  | scrapped       |
|  v0.0  | prefix v0.0    |

Summary of hardware version history, details on [bombo82/bombopad](https://github.com/bombo82/bombopad):
* **v0.3 - PCB release**
    * First version with PCB
    * Wired build using ProMicro compatible microcontroller with QMK or VIAL firmware
    * Wireless build using Nice!Nano compatible microcontroller with ZMK firmware
    * Kailh choc low-profile switch
    * EC11 rotary encoders or EVQWGD001 encoders
    * Optional display: SSD1306 128x32 on ProMicro microcontroller or Nice!View on Nice!Nano
    * Optional Lipo battery and power switch, depends on microcontroller capabilities
* **v0.2 (not compatible with QMK)**
    * Prototype on a solderless breadboard and a stripboard
    * Use expensive microcontroller and display
    * Bluetooth module and battery management module are integrate inside microcontroller
    * Shares the switch and encoders stripboard with v0.0
    * Disassambled to reuse some parts (microcontroller and display) to my own build of v0.3
* **v0.1 (never built)**
    * Scrapped at the design stage and never built 
* **v0.0**
    * Initial prototype on a solderless breadboard and a stripboard
    * Low cost compoments
    * MX red switch, EC11 rotary encoders, SSD1306 OLED 128x64 Pixel I2C
    * External HC-06 Bluetooth serial UART module

## Authors

Main contributors names and contact info:
- [Gianni Bombelli (bombo82)](https://github.com/bombo82)

## Licenses

Documentation are licensed under GNU Free Documentation License as published by the Free Software Foundation, either version 1.3 of the License, or (at your option) any later version.

Source code are licensed under GNU General Public License as published by the Free Software Foundation, either version 3 of the License, or (at your option) any later version.

Hardware design and all related things are licensed under CERN Open Hardware License as published by the CERN, either version 2 of the License, or (at your option) any later version.

## License Disclaimer

Copyright (C) 2024 Gianni Bombelli <bombo82@giannibombelli.it>

Permission is granted to copy, distribute and/or modify this document
under the terms of the GNU Free Documentation License, Version 1.3
or any later version published by the Free Software Foundation;
with no Invariant Sections, no Front-Cover Texts, and no Back-Cover Texts.

You should have received a copy of the GNU Free Documentation License
along with this program.  If not, see <https://www.gnu.org/licenses/fdl-1.3.html>.

## Acknowledgments

Many thanks to all the people who supported and pushed me in various ways, and especially to [Arialdo](https://github.com/arialdomartini) who lured me into the well known "rabbit hole" of the custom mechanical keyboards. 
