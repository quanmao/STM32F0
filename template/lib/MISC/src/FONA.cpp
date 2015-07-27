#include "FONA.h"
#include <stdio.h>
#include <string.h>

FONA :: FONA(Serial* serialx, GPIO_common status, GPIO_common key, GPIO_common reset): m_status(status), m_key(key), m_reset(reset)
{
	m_serial = serialx;
	
	// Set serial baudrate and timeout (20ms)
 	m_serial->baud(9600);
	m_serial->timeout(20);
	
	m_key = 1;
	m_reset = 1;
}

char FONA :: on(void)
{
	// Switch OFF if it's already ON ?
	if(this->off() == 0)
	{
		// Switch ON
		m_key = 0;
		Delay(1200);
		m_key = 1;
		Delay(2400);
	}
	
	return m_status;
}

char FONA :: off(void)
{
	if(m_status)
	{
		m_key = 0;
		Delay(1200);
		m_key = 1;
		Delay(1900);
	}
	
	return m_status;
}

char FONA :: echo(char state)
{
	char buffer[256] = {0};
	
	state = (state != 0) ? 1 : 0;
	
	sprintf(buffer, "ATE%d", (int)state);
	
	return (this->write(buffer, (char*)"OK\0"));
}
				
char FONA :: pin(char* code)
{
	char buffer[256] = {0};
	
	sprintf(buffer, "AT+CPIN=%s", code);
	
	return (this->write(buffer, (char*)"OK\0"));
}

char FONA :: send(char* number, char* message)
{
	char buffer[256] = {0};
	char result = 0;
	
	// Enter in text mode
	strcpy(buffer, "AT+CMGF=1");
	
	result = this->write(buffer, (char*)"OK\0");
	
	if(!result) return 0;
	
	// Enter phone number
	sprintf(buffer, "AT+CMGS=\"%s\"", number);
	
	result = this->write(buffer, (char*)">\0");
	
	if(!result) return 0;
	
	// Reset buffer
	memset(buffer, 0x00, sizeof(buffer));
	
	// Send message
	sprintf(buffer, "%s", message);
	
	result = this->write(buffer, (char*)"\0");
	
	if(!result) return 0;
	
	buffer[0] = CTRLZ;
	
	// Send ctrl+z
	m_serial->write_b(buffer, 1);
	
	return 1;
}

char FONA :: recv(char index, char* number, char* message)
{
	char buffer[256] = {0};
	char tmp[256] = {0};
	char result = 0;
	
	char* ptr;
	
	// Enter in text mode
	strcpy(buffer, "AT+CMGF=1");
	
	result = this->write(buffer, (char*)"OK\0");
	
	if(!result) return 0;
	
	memset(buffer, 0x00, 256);
	
	// Read sms from SIM800
	sprintf(buffer, "AT+CMGR=%d", index);
	
	result = this->read(buffer, tmp);
	
	if(!result) return 0;
	
	// Search for CMGR
	ptr = strstr(tmp, "CMGR");
	
	if(ptr != 0)
	{
		strncpy(tmp, ptr, strlen(tmp));
	}
	else
	{
		return 0;
	}
	
	// Get number
	result = this->find(3, tmp, number, '"');
	
	if(!result) return 0;
	
	// Get message
	result = this->find(1, tmp, message, '\r');
	
	if(!result) return 0;
	
	// Remove first character
	strncpy(message, message+1, strlen(message));
	
	return 1;
}

char FONA :: clear(char index)
{
	char buffer[256] = {0};
	char result = 0;
	
	// Enter in text mode
	strcpy(buffer, "AT+CMGF=1");
	
	result = this->write(buffer, (char*)"OK\0");
	
	if(!result) return 0;
	
	memset(buffer, 0x00, 256);
	
	if(index > 0)
	{
		// Delete sms from SIM800
		sprintf(buffer, "AT+CMGD=%d", index);
	}
	else
	{
		// Delete all sms
		strcpy(buffer, "AT+CMGD=1,4");
	}
	
	return this->write(buffer, (char*)"OK\0");
}

char FONA :: network(char* provider)
{
	char buffer[256] = {0};
	char tmp[256] = {0};
	char result = 0;
	
	strcpy(buffer, "AT+COPS?");
	
	result = this->read(buffer, tmp);
	
	if(!result) return 0;
	
	return this->find(1, tmp, provider, '"');
}

int FONA :: battery(void)
{
	char buffer[256] = "";
	char tmp[256] = "";
	char result = 0;
	
	char level[4] = "";
	int value = 0;
	
	char* ptr;
	
	strcpy(buffer, "AT+CBC");
	
	result = this->read(buffer, tmp);
	
	if(!result) return 0;
	
	// Search for CMGR
	ptr = strstr(tmp, "CBC");
	
	if(ptr != 0)
	{
		strncpy(tmp, ptr, strlen(tmp));
	}
	else
	{
		return 0;
	}
	
	result = this->find(1, tmp, level, ','); 
	
	if(!result) return 0;
	
	sscanf(level, "%d", &value); 
	
	return value;
}

int FONA :: strength(void)
{
	char buffer[256] = {0};
	char tmp[256] = {0};
	char result = 0;
	
//	char level[4] = "";
	int value = 0;
	
	char* ptr;
	
	strcpy(buffer, "AT+CSQ");
	
	result = this->read(buffer, tmp);
	
	if(!result) return 0;
	
	// Search for CMGR
	ptr = strstr(tmp, "CSQ");
	
	if(ptr != 0)
	{
		strncpy(tmp, ptr, strlen(tmp));
	}
	else
	{
		return 0;
	}
	
	sscanf(tmp, "CSQ: %d", &value);
	
	return value;
}

char FONA :: write(char* command, char* reply)
{
	char buffer[256] = {0};
	int length = 0;
	
	m_serial->flush();
	
	strcpy(buffer, command);
	
	length = strlen(buffer);
	
	buffer[length++] = '\n';

	// Send command
	m_serial->write_b(buffer, length);
	
	// Load timeout
	m_timer = TIMEOUT;
	
	// Reset length and buffer
	length = 0;
	memset(buffer, 0x00, 256);
	
	// Wait for response
	while(m_timer)
	{
		length = m_serial->read(buffer);
		
		// Data received ?
		if(length > 0)
		{
			// Remove CR + LF
			sscanf(buffer, "\r\n%s\r\n", buffer);
			
			// Check reply ?
			if(reply[0] != 0x00)
			{
				// Reply expected ?
				if(strncmp(reply, buffer, length) == 0)
				{
					return 1; 
				}
				else
				{
					return 0;
				}
			}
		}
		else if(!reply[0])
		{
			return 1;
		}
	}
	
	return 0;
}

char FONA :: read(char* command, char* reply)
{
	char buffer[256] = {0};
	int length = 0;
	
	m_serial->flush();
	
	strcpy(buffer, command);
	
	length = strlen(buffer);
	
	buffer[length++] = '\n';

	// Send command
	m_serial->write_b(buffer, length);
	
	// Load timeout
	m_timer = TIMEOUT;
	
	// Reset length and buffer
	length = 0;
	memset(buffer, 0x00, 256);
	
	// Wait for response
	while(m_timer)
	{
		length = m_serial->read(buffer);
		
		// Data received ?
		if(length > 0)
		{
			strcpy(reply, buffer);
			
			return 1;
		}
	}
	
	return 0;
}

char FONA :: find(int number, char* buffer, char* output, char c)
{ 
	char i = 0;
	
	char* ptr[2];
	
	ptr[0] = buffer;
	
	while(number)
	{
		ptr[0] = strchr(ptr[0]+i, c);
		
		if(ptr[0] != 0)
		{
			i = 1;
			number--;
		}
		else
		{
			return 0;
		}
	}
	
	ptr[1] = strchr(ptr[0]+1, c);
		
	if(ptr[1] != 0)
	{			
		strncpy(output, ptr[0]+1, ptr[1]-ptr[0]-1);
			
		return 1;
	}
	
	return 0;
}

void FONA :: timer(void)
{
	if(m_timer) m_timer--;
}
