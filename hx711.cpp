#include <stdio.h>
#include <inttypes.h>
#include <wiringPi.h>

#include "hx711.h"

HX711::HX711() :
	mGainBits(1),
	mScale(1.0f),
	mOffset(0)
{
	this->initialize();
}

void HX711::initialize(){
	if(wiringPiSetup() == -1){
		printf("initialization failed");
	}
	pinMode(SCLK, OUTPUT);
	pinMode(DATA, INPUT);
}

bool HX711::isReady(){
	return digitalRead(DATA) == LOW;
}

void HX711::setGain(uint8_t gain){
	switch(gain){
		case GAIN_128:
			this->mGainBits = 1;
		break;
		case GAIN_64:
			this->mGainBits = 2;
		break;
		case GAIN_32:
			this->mGainBits = 3;
		break;
		default:
			//invalid gain, ignore
		break;
	}

	digitalWrite(SCLK, LOW);
	read();
}

uint32_t HX711::read() {
	// wait for the chip to become ready
	while (!this->isReady());

	uint8_t data[3] = {0};

	// pulse the clock pin 24 times to read the data
	for (uint8_t j = 3; j--;) {
		for (uint8_t i = 8; i--;) {
			digitalWrite(SCLK, HIGH);
			data[j] |= (digitalRead(DATA) << i);
			digitalWrite(SCLK, LOW);
		}
	}

	// set the channel and the gain factor for the next reading using the clock pin
	for (int i = 0; i < mGainBits; i++) {
		digitalWrite(SCLK, HIGH);
		digitalWrite(SCLK, LOW);
	}

	data[2] ^= 0x80;

	return ((uint32_t) data[2] << 16) | ((uint32_t) data[1] << 8) | (uint32_t) data[0];
}

uint32_t HX711::readAverage(uint8_t times) {
	uint64_t sum = 0;
	for (uint8_t i = 0; i < times; i++) {
		sum += read();
	}
	return sum / times;
}

int32_t HX711::getRawValue(uint8_t times) {
	return readAverage(times) - mOffset;
}

float HX711::getUnits(uint8_t times) {
	return getRawValue(times) / mScale;
}

void HX711::tare(uint8_t times) {
	uint64_t sum = readAverage(times);
	setOffset(sum);
}

void HX711::setScale(float scale) {
	mScale = scale;
}

void HX711::setOffset(int32_t offset) {
	mOffset = offset;
}

void HX711::powerDown() {
	digitalWrite(SCLK, LOW);
	digitalWrite(SCLK, HIGH);
}

void HX711::powerUp() {
	digitalWrite(SCLK, LOW);
}

int main(){
	HX711 sensor;
	sensor.tare(10);
	while(true){
		printf("%f\n", sensor.getUnits());
		//sensor.read();
	}
}

