/**
  ******************************************************************************
  * @file    main.c
  * @author  Ac6
  * @version V1.0
  * @date    01-December-2013
  * @brief   Default main function.
  ******************************************************************************
*/


#include "stm32f10x.h"
#include "I2C.h"

#define BUFFER_SIZE 7
#define RTC_ADDRESS 0xD0
custom_libraries::I2C_ i2c(I2C1,GPIOB,7,6,custom_libraries::standard);

uint8_t buffer[BUFFER_SIZE];


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

RTC_Time rtc_time;

RTC_Time get_time(){
	RTC_Time rtc_time;

	i2c.write_memp(RTC_ADDRESS,0x00);
	i2c.read_bytes(RTC_ADDRESS,buffer,BUFFER_SIZE);
	rtc_time.second = i2c.BCD_to_decimal(buffer[0]);
	rtc_time.minute = i2c.BCD_to_decimal(buffer[1]);
	rtc_time.hour = i2c.BCD_to_decimal(buffer[2]);
	rtc_time.day = i2c.BCD_to_decimal(buffer[3]);
	rtc_time.date = i2c.BCD_to_decimal(buffer[4]);
	rtc_time.month = i2c.BCD_to_decimal(buffer[5]);
	rtc_time.year = i2c.BCD_to_decimal(buffer[6]);

	return rtc_time;
}

void set_time(RTC_Time rtc_time){
	uint8_t set_buffer[BUFFER_SIZE];

	set_buffer[0] = i2c.decimal_to_BCD(rtc_time.second);
	set_buffer[1] = i2c.decimal_to_BCD(rtc_time.minute);
	set_buffer[2] = i2c.decimal_to_BCD(rtc_time.hour);
	set_buffer[3] = i2c.decimal_to_BCD(rtc_time.day);
	set_buffer[4] = i2c.decimal_to_BCD(rtc_time.date);
	set_buffer[5] = i2c.decimal_to_BCD(rtc_time.month);
	set_buffer[6] = i2c.decimal_to_BCD(rtc_time.year);

	i2c.write_bytes(RTC_ADDRESS,0x00,set_buffer,BUFFER_SIZE);
}

int main(void)
{
	rtc_time.second = 0;
	rtc_time.minute = 45;
	rtc_time.hour = 15;
	rtc_time.day = 2;
	rtc_time.date = 4;
	rtc_time.month = 8;
	rtc_time.year = 20;

	set_time(rtc_time);

	while(1){

		rtc_time = get_time();

	}
}
