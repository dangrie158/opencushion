# C Driver and Node Binding for HX711 Load Cell Amp

## Prerequisities

- ```g++-4.8``` node-gyp needs to compile with g++ v4.8 due to the version of v8 node uses since some versions. However aspian comes with v4.6 preinstalled. Install it via ```sudo apt-get install g++-4.8```
- ```WiringPi``` for the native GPIO handling this libary uses [WiringPi](http://wiringpi.com). Install it using the instructions on the Website.

## Troubleshooting

It sometimes can happen that the HX711 chip gets in a state where it does not recover itself. 
This can result in an endless loop while the library waits for the chip to notify a new data set.

If you ever run in a problem where the library does not give you new values, just power cycle the sensor.
