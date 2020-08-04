/*
 * DS1307.h
 *
 *  Created on: Aug 4, 2020
 *      Author: MCLEANS
 */

#ifndef DS1307_H_
#define DS1307_H_

#include "I2C.h"

namespace custom_libraries {

#define BUFFER_SIZE 7
#define RTC_ADDRESS 0xD0

struct RTC_Time{
public:
	uint8_t second;
	uint8_t minute;
	uint8_t hour;
	uint8_t day;
	uint8_t date;
	uint8_t month;
	uint8_t year;
};

class DS1307 : public I2C_{
private:
	uint8_t buffer[BUFFER_SIZE];
private:
public:
public:
	DS1307(I2C_TypeDef *_I2C,
			GPIO_TypeDef *GPIO,
			uint8_t SDA,
			uint8_t SCL);
	RTC_Time get_time();
	void set_time(RTC_Time rtc_time);
	~DS1307();
};

} /* namespace custom_libraries */

#endif /* DS1307_H_ */
