# PCB Design

|Value|Quantity|Name|RefDes| Manufacturer | Supplier |
| :---: | :---: | :--- | :---: | :---: | :--- |
|1u|1|CAP_0805|C1| Vishay | https://www.mouser.com/ProductDetail/Vishay-Vitramon/VJ0805Y105KXQTW1BC/?qs=sGAEpiMZZMsh%252b1woXyUXj7IM2igjA789UFrvf0Kziow%3d |
|0.01u|1|CAP_0805|C2| Wurth Electronic | https://www.mouser.com/ProductDetail/Wurth-Electronics/885012207011/?qs=sGAEpiMZZMs0AnBnWHyRQEGbLOF2VP1iH7zxtaPhTpObVhmDSZ4o9Q%3d%3d |
|0.01u|1|CAP_0805|C3| Wurth Electronic | https://www.mouser.com/ProductDetail/Wurth-Electronics/885012207011/?qs=sGAEpiMZZMs0AnBnWHyRQEGbLOF2VP1iH7zxtaPhTpObVhmDSZ4o9Q%3d%3d |
||1|644456-8|J1| Omron Electonics | https://www.mouser.com/ProductDetail/Omron-Electronics/XG8V-0831/?qs=sGAEpiMZZMs%252bGHln7q6pm%252bv5BXf4QdrTUprKlfXrIZ0%3d |
||1|644456-8|J2| Omron Electonics | https://www.mouser.com/ProductDetail/Omron-Electronics/XG8V-0831/?qs=sGAEpiMZZMs%252bGHln7q6pm%252bv5BXf4QdrTUprKlfXrIZ0%3d |
|1k|1|RES_0805|R1| Yageo | https://www.mouser.com/ProductDetail/Yageo/RC0805FR-071KL/?qs=sGAEpiMZZMtlubZbdhIBINUJ4p5cMnF1Rv8sEVwr4ss%3d |
||1|MSP430FR2311PW16R|U1| Texas Instruments | https://www.mouser.com/ProductDetail/Texas-Instruments/MSP430FR2311IPW16R/?qs=sGAEpiMZZMvzNxwKcL67%252bslf58yKv5kzj7hMAPyboDs%3d |


## Deliverables 
This folder should contain the following files:
* BOARD.sch
* BOARD.pcb
* GERBERS (Folder)

The GERBERS folder should contain the Gerber files as listed in the ECE Department ordering guides for PCBs.

The README for this folder should also contain the Bill of Materials as well as (if possible) a link to a Digikey/Mouser cart that contains the parts you would want for this board.

## Board Details
Your board should be a 2 layer board which can conveniently fit on a breadboard and contains the required passives for this processor to work in a standalone implementation. This means that the board should contain bypass capacitors, and the proper reset circuitry as laid out in the MSP430FR2311 datasheet. As per PCBWAY manufacturing restrictions, you should not have any traces smaller than 6mil, and your board should be smaller than 4 inches per side (which is maybe 4 times larger than your board should be.)

It will be up to you to determine the capacitor brands, values, and sizes, as well as which package you want for your MSP430FR2311.
