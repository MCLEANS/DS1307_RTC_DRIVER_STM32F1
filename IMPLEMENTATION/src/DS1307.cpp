/*
 * DS1307.cpp
 *
 *  Created on: Aug 4, 2020
 *      Author: MCLEANS
 */

#include "DS1307.h"

namespace custom_libraries {

DS1307::DS1307(I2C_TypeDef *_I2C,
				GPIO_TypeDef *GPIO,
				uint8_t SDA,
				uint8_t SCL):I2C_(_I2C,
									GPIO,
									SDA,
									SCL,
									standard) {


}

void DS1307::set_time(RTC_Time rtc_time){
	uint8_t set_buffer[BUFFER_SIZE];

	set_buffer[0] = decimal_to_BCD(rtc_time.second);
	set_buffer[1] = decimal_to_BCD(rtc_time.minute);
	set_buffer[2] = decimal_to_BCD(rtc_time.hour);
	set_buffer[3] = decimal_to_BCD(rtc_time.day);
	set_buffer[4] = decimal_to_BCD(rtc_time.date);
	set_buffer[5] = decimal_to_BCD(rtc_time.month);
	set_buffer[6] = decimal_to_BCD(rtc_time.year);

	i2c.write_bytes(RTC_ADDRESS,0x00,set_buffer,BUFFER_SIZE);
}

RTC_Time DS1307::get_time(){
	RTC_Time rtc_time;

	i2c.write_memp(RTC_ADDRESS,0x00);
	i2c.read_bytes(RTC_ADDRESS,buffer,BUFFER_SIZE);
	rtc_time.second =i2c.BCD_to_decimal(buffer[0]);
	rtc_time.minute = BCD_to_decimal(buffer[1]);
	rtc_time.hour = BCD_to_decimal(buffer[2]);
	rtc_time.day = BCD_to_decimal(buffer[3]);
	rtc_time.date = BCD_to_decimal(buffer[4]);
	rtc_time.month = BCD_to_decimal(buffer[5]);
	rtc_time.year = BCD_to_decimal(buffer[6]);

	return rtc_time;
}

DS1307::~DS1307() {
	// TODO Auto-generated destructor stub
}

} /* namespace custom_libraries */
