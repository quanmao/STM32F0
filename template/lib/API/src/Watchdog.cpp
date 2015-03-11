#include "Watchdog.h"

Watchdog :: Watchdog(int timeout)
{
	// Enable watchdog write access
	IWDG_WriteAccessCmd(IWDG_WriteAccess_Enable);
	
	// Watchdog clock (LSI = 40kHz)
	IWDG_SetPrescaler(IWDG_Prescaler_256);
	
	// 40kHz / 256 = 156 Hz => 6.4 ms
	// Reload value can be 6.4ms to 6.4 x 4096 = 26.21s
	
	// Set reload value (ms)
	IWDG_SetReload(timeout / ((1000 * 256) / 40000));
	
	// Wait reload value flag
	while(IWDG_GetFlagStatus(IWDG_FLAG_RVU) != SET);
	
	// Disable watchdog write access
	IWDG_WriteAccessCmd(IWDG_WriteAccess_Enable);
	
	// Enable watchdog
	IWDG_Enable();
}

void Watchdog :: reload(void)
{
	IWDG_ReloadCounter();
}
