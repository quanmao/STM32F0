#include "main.h"
#include "MCP9803.h"

//  MCP9803 address
#define TEMP_SENSOR_ADDRESS  (0x90)

float temperature = 0;

I2C	i2c(I2C1, PB7, PB6);
// I2C	i2c(I2C2, PB11, PB10);

MCP9803 mcp9803(&i2c, TEMP_SENSOR_ADDRESS);

int main(void)
{
  Systick_Init();
	
  while (1)
  {
		temperature = mcp9803.get();
		
		Delay(100);
  }
}
