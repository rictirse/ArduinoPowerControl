
enum PCStatus { p_Ready, p_PowerOff, p_PowerOn, p_Status };

enum PowerPins { PowerPin1 = 2, PowerPin2 = 4, PowerPin3 = 6, PowerPin4 = 8, PowerPin5 = 10, PowerPin6 = 12, PowerPinMax = 6};

const int PowerPin[PowerPinMax] = { PowerPin1, PowerPin2, PowerPin3, PowerPin4, PowerPin5, PowerPin6 };

int SW_Array[PowerPinMax] = { 0, 0, 0, 0, 0, 0 };

#define USART_BAUDRATE 9600

byte incomingByte = 0;
byte inputCmd = 0;
String UartData = "";
bool uartStart = false;
bool newLineReceived = false;
bool bSwStatus = false;

void setup() 
{
	//setup Relay
	for (int i = 0; i < PowerPinMax; i++)
	{
		pinMode(PowerPin[i], OUTPUT);
		digitalWrite(PowerPin[i], HIGH);
	}
	//set uart
	Serial.begin(USART_BAUDRATE);
}

void loop() 
{
	if (Serial.available() > 0)
	{
		char Serial_Buffer = Serial.read();
		if (Serial_Buffer != '\n')
		{
			UartData = UartData + Serial_Buffer;
		}
		else
		{
			if (UartData.length() >= 7)
			{
				splitValue(UartData);
				CheckStatus();
				UartData = ""; //clean data
			}
		}
	}
}

void CheckStatus()
{
	String s = String(SW_Array[0]);

	for (int i = 1; i < PowerPinMax; i++)
	{
		s = s + ',' + String(SW_Array[i]);
	}
	Serial.println(s);
}

bool splitValue(String valueString)
{
	int Count = 0;
	int pos;
	int IntArr[PowerPinMax] = { 0, 0, 0, 0, 0, 0 };

	// split string
	for (int i = 0; i < PowerPinMax; i++)
	{
		pos = valueString.indexOf(',');
		if (pos == -1 && i < PowerPinMax -1)
		{
			return false;
		}
		else
		{
			pos = valueString.indexOf(',');
			IntArr[Count++] = valueString.substring(0, pos).toInt();
			valueString = valueString.substring(pos + 1, valueString.length());
		}
	}

	// set pin status
	for (int i = 0; i < PowerPinMax; i++)
	{
		if (IntArr[i] != SW_Array[i])
		{
			SW_Array[i] = IntArr[i];
			digitalWrite(PowerPin[i], (SW_Array[i] == 1 ? LOW : HIGH));
		}
	}

	return true;
}
