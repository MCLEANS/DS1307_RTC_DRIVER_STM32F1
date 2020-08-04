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
#include "DS1307.h"

#define SDA 7
#define SCL 6

custom_libraries::DS1307 ds1307(I2C1,GPIOB,SDA,SCL);
custom_libraries::RTC_Time rtc_time;

int main(void)
{
	rtc_time.second = 0;
	rtc_time.minute = 10;
	rtc_time.hour = 14;
	rtc_time.day = 2;
	rtc_time.date = 4;
	rtc_time.month = 8;
	rtc_time.year = 20;

	//ds1307.set_time(rtc_time);

	while(1){

		rtc_time = ds1307.get_time();

	}
}
