#pragma once

union SW_STATUS
{
	struct
	{
		unsigned short PowerSW_1 : 1;
		unsigned short PowerSW_2 : 1;
		unsigned short PowerSW_3 : 1;
		unsigned short PowerSW_4 : 1;

		unsigned short a_Ready : 1;
		unsigned short Unused6 : 1;
		unsigned short Unused7 : 1;
		unsigned short Unused8 : 1;
	}status;
	byte Status;
};


enum PCStatus { p_Ready, p_PowerOff, p_PowerOn, p_Status };

enum PowerPins { PowerPin1, PowerPin2, PowerPin3, PowerPin4, PowerPinMax };

const int PowerPin[PowerPinMax] = { PowerPin1, PowerPin2, PowerPin3, PowerPin4 };

#define USART_BAUDRATE 9600

byte incomingByte = 0;
byte inputCmd = 0;
bool newLineReceived = false;
bool bSwStatus = false;
SW_STATUS m_SwStatus;