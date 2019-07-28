// Touch screen library with X Y and Z (pressure) readings as well
// as oversampling to avoid 'bouncing'
// (c) ladyada / adafruit
// Code under MIT License

#pragma once
#include <stdint.h>

class TSPoint_kbv
{
public:
	TSPoint_kbv() = default;
	inline TSPoint_kbv(int16_t x0, int16_t y0, int16_t z0) : x{x0}, y{y0}, z{z0} {
	}

	inline bool operator==(const TSPoint_kbv& other) const {
		return x == other.x && y == other.y && z == other.z;
	}

	inline bool operator!=(const TSPoint_kbv& other) const {
		return !(*this == other);
	}

	int16_t x = 0, y = 0, z = 0;
};

class TouchScreen_kbv
{
public:
	TouchScreen_kbv(uint8_t xp, uint8_t yp, uint8_t xm, uint8_t ym);
	TouchScreen_kbv(uint8_t xp, uint8_t yp, uint8_t xm, uint8_t ym, uint16_t rx);

	uint16_t pressure();
	int readTouchY();
	int readTouchX();
	TSPoint_kbv getPoint();

	TSPoint_kbv getPointSafe() {
		const auto tp = getPoint();
		pinMode(_yp, OUTPUT); //restore shared pins
		pinMode(_xm, OUTPUT);
		digitalWrite(_yp, HIGH); //because TFT control pins
		digitalWrite(_xm, HIGH);

		return tp;
	}

private:
	uint8_t _yp, _ym, _xm, _xp;
	uint16_t _rxplate;
};
