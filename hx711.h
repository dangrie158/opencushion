#include <inttypes.h>

#define SCLK 7
#define DATA 0

//channel A, gain 128
#define GAIN_128 128

//channel A, gain 64
#define GAIN_64 64

//channel B, gain 32
#define GAIN_32 32

class HX711{
private:
	uint8_t mGainBits;
	float mScale;
	int32_t mOffset;

public:
	HX711();
	void initialize();
	bool isReady();
	void setGain(uint8_t gain);
	uint32_t read();
	uint32_t readAverage(uint8_t times = 10);
	int32_t getRawValue(uint8_t times = 10);
	float getUnits(uint8_t times = 10);
	void tare(uint8_t times = 10);
	void setScale(float scale);
	void setOffset(int32_t offset);
	void powerDown();
	void powerUp();
};
