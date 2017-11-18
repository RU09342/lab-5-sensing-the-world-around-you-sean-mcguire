# Sensors and Signal Conditioning
One of the biggest limitations of the microcontroller is the fact that it lives in a digital world. We need certain components to be able to translate the analog world to the digital world and vice-versa. In this lab, we need to be able to convert some electrical phenomena into something our microcontroller can understand. For this, we need a few building blocks to do this.

## Sensors
Sensors in a nutshell convert a physical phenomena into an electrical phenomena. For example, and accelerometer converts an acceleration into a change in capacitance (in the case of some MEMS devices). This electrical phenomena does not have to be a voltage, and as such, we need to be able to convert our sensor output to a voltage. From there, we can read in this voltage through our Analog to Digital Converter (ADC).

## Signal Conditioning
The signal conditioning chain can be broken up into a few main building blocks. In the beginning you have your sensor which converts something into the electrical world. We then need a block which can convert that resultant electrical phenomena into a voltage. From here, this voltage may be too small/large for our microcontroller, so we need to amplify the signal. From there, we may need to de-noise the signal by filtering. After all of this, we might be at a point where we are ready to read the signal into our processor.

## Photoresistor
The photoresistor is a simple device that varies its resistance with the amount of light on its surface. As the intensity of the light decreases, the resistance increases, and when the light intensity increases, the resistance decreases. In order to read data from this device, we created the following circuit.

<p align="center">
  <img src="https://github.com/RU09342/lab-5-sensing-the-world-around-you-sean-mcguire/blob/master/Sensors%20and%20Signal%20Conditioning/Photoresistor.JPG">
</p>

## Phototransistor
The phototransistor is very similar to the photoresistor in that it is a device used to sense light. Like any MOSFET, the photo transistor has 3 legs: gate, drain, and source. Likewise this device behaves similar to a MOSFET, in which current from drain to source (I<sub>DS</sub>) is a fuction of voltage from drain to source (V<sub>DS</sub>) and voltage from gate to source (V<sub>GS</sub>). Because V<sub>GS</sub> alters the VI curve of the device, the gate of the phototransistor is often left unconnected for many light sensing circuits. Otherwise, the gate can be used to bias the device. Our circuit for measuring light intensity with the phototransistor is show below.

<p align="center">
  <img src="https://github.com/RU09342/lab-5-sensing-the-world-around-you-sean-mcguire/blob/master/Sensors%20and%20Signal%20Conditioning/Phototransistor.JPG">
</p>

## LM35
Unlike the last two devices, the LM35 is a temperature sensor. The LM35 outputs a voltage proportional to the ambient temperature. It is calibrated to output 10 mV/<sup>o</sup>C. This allows for very easy voltage to temperature conversions because the relationship is linear. Further information on this device along with the follwoing circuit configuration can be found [here](http://www.ti.com/lit/ds/symlink/lm35.pdf).

<p align="center">
  <img src="https://github.com/RU09342/lab-5-sensing-the-world-around-you-sean-mcguire/blob/master/Sensors%20and%20Signal%20Conditioning/LM35.JPG">
</p>
  
