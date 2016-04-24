# C Driver and Node Binding for HX711 Load Cell Amp

## Prerequisities

- ```g++-4.8``` node-gyp needs to compile with g++ v4.8 due to the version of v8 node uses since some versions. However aspian comes with v4.6 preinstalled. Install it via ```sudo apt-get install g++-4.8```
- ```WiringPi``` for the native GPIO handling this libary uses [WiringPi](http://wiringpi.com). Install it using the instructions on the Website.

## API

This library exposes a class with Name ```HX711``` that gives you access to all functions you need to interface.

### Constructor(Number clockPin, Number dataPin)
	const sensor = new HX711(clockPin, dataPin);

 create a new Sensor instance. The pin Numbers should represent the [WiringPi Pins](http://wiringpi.com/wp-content/uploads/2013/03/gpio1.png) the Sensor is connected to. You can have as many HX711 Chips connected as long as they all are connected to a different set of pins.

### read()
	sensor.read();
	
Read the raw value as returned from the Sensor. You normally don't call this Method directly, but you may find it useful so I exported it.

### getUnits([Number times = 10])
	let units = sensor.getUnits();

Read the sensor ```times``` times and calculate the average. This returns a scaled value with the offset removed.

### tare([Number times = 10])
	sensor.tare();

Read the sensor ```times``` times and save the average Offset via ```setOffset()```.

### setOffset([Number offset = 0])
	sensor.setOffset(-1000);

set or reset the offset for the sensor

### getOffset()
	let offset = sensor.getOffset();

get the current offset of the sensor

### setScale([Number scale = 1.0])
	sensor.setScale(3543.26);

set or reset the scale for the sensor

### getScale()
	let scale = sensor.getScale();

get the current scale of the sensor

## Troubleshooting

It sometimes can happen that the HX711 chip gets in a state where it does not recover itself. 
This can result in an endless loop while the library waits for the chip to notify a new data set.

If you ever run in a problem where the library does not give you new values, just power cycle the sensor.

