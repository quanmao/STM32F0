#include "main.h"
#include "DS3231.h"

I2C	i2c(I2C1, PB7, PB6);

DS3231 ds3231(&i2c);

Date date;
Time time;
float temp;

int main(void)
{	
	Systick_Init();
	
//	time.seconds = 30;
//	time.minutes = 45;
//	time.hours = 18;
//	
//	date.day = 22;
//	date.month = 5;
//	date.year = 2015;
//	
//	ds3231.set(time);
//	ds3231.set(date);
	
  while (1)
  {
		ds3231.get(&time);
		ds3231.get(&date);
		
		temp = ds3231.temperature();
  }
}