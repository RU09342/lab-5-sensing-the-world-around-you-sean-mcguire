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
  
## Analog to Digital Converter (ADC)
The ADC is the part of the microprocessor that converts analog data into digital data that can be processed by the microprocessor. It represents the analog voltage read as some fraction of V<sub>DD</sub>. Basically the voltage read in is equal to V<sub>DD</sub>(ADCxMEMy)/2<sup>x</sup> where x is the resolution (number of bits) of the ADC.

The code for the FR2311 is just simple code to transmit an ADC reading over UART. Basically, the ADC is set up to take continuous measurements. Every time the ADC is finished converting a measurement to its binary representation, the ADC triggers an interrupt. In the interrupt service routine for the ADC, the value in ADC10MEM0 is saved to an integer value in memory. Because UART can only transmit 8 bits at a time, the 10-bit ADC reading has to be sent out in parts. In order to send the most significant bits, we shift the number to the right by 8. To send the least sigificant bits, we AND the integer with 0xFF. Both of these values are then sent to the TX buffer. Lastly, the microprocessor goes back into low power mode until the ADC triggers another interrupt.

The code for the FR6989 is very similar except it uses a different method to view the data. For this code, upon each ADC interrupt, the ADC reading is saved and then split into 4 digits (this is the max number of digits for a 12-bit number). These four digits are then displayed on the LCD individually using the ```showChar(char, int)``` method provided in ```LCDDriver.h```. The processor is then delayed before going back into low power mode to await the next ADC reading. The delay is implemented using ```__delay_cycles()``` which isn't the most efficient in terms of power, but it is easily the simplest method in terms of lines of code to implement. If one were looking to optimize power efficiency, you could put implement a timer delay so that the processor could go back into low power mode while waiting through the delay.
