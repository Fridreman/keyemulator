#include "stdafx.h"

using namespace std;

HWND hwnd = FindWindow(0, L"");
HANDLE hSerial;
DWORD iSize;

void SendKey(HWND, BYTE);
char ReadCOM();
void RunComPort();

int main() {
	RunComPort();
	while (1)
	{
		//cout << ReadCOM() << endl;
		hwnd = GetActiveWindow();
		SendKey(hwnd, int(ReadCOM()));
	}
	return 0;
}

void SendKey(HWND hWndTargetWindow, BYTE virtualKey)
{
	switch (virtualKey)
	{
		case 4:
		{
			keybd_event(VK_RETURN, 0, 0, 0);
			keybd_event(VK_RETURN, 0, KEYEVENTF_KEYUP, 0);
			break;
		}
		case 23:
		{
			keybd_event(VK_BACK, 0, 0, 0);
			keybd_event(VK_BACK, 0, KEYEVENTF_KEYUP, 0);
			break;
		}
		case 31:
		{
			keybd_event(VK_SPACE, 0, 0, 0);
			keybd_event(VK_SPACE, 0, KEYEVENTF_KEYUP, 0);
			break;
		}
		default:
		{
			BYTE KeyOfNum[] = { 0, 73, 81, 65, 0, 74, 83, 68, 84, 77, 76, 70, 78, 90, 82, 72, 69, 67, 85, 87, 71, 89, 80, 0, 66, 86, 75, 88, 0, 81, 0, 0};

			virtualKey = KeyOfNum[virtualKey];
			cout << virtualKey << endl;
			keybd_event(virtualKey, 0, 0, 0);
			keybd_event(virtualKey, 0, KEYEVENTF_KEYUP, 0);
		}
	}
}

char ReadCOM()
{
	BYTE sReceivedChar;
	ReadFile(hSerial, &sReceivedChar, 1, &iSize, 0);
	return sReceivedChar;
}

void RunComPort()
{
	cout << "Enter number of COM port:";
	string str = "COM", Num;
	getline(cin, Num);
	str += Num;
	wstring NumPort(str.begin(), str.end());
	WCHAR * PortName = &NumPort[0];
	hSerial = ::CreateFile(PortName, GENERIC_READ | GENERIC_WRITE, 0, 0, OPEN_EXISTING, FILE_ATTRIBUTE_NORMAL, 0);
	if (hSerial == INVALID_HANDLE_VALUE)
		if (GetLastError() == ERROR_FILE_NOT_FOUND)
			cout << "Com port: empty.\n";
		cout << "Com port: Error.\n";
	DCB dcbSerialParams;								
	dcbSerialParams.DCBlength = sizeof(dcbSerialParams);
	if (!GetCommState(hSerial, &dcbSerialParams))		
		cout << "не сработал GetCommState\n";
	dcbSerialParams.BaudRate = CBR_9600;	
	dcbSerialParams.ByteSize = 8;			
	dcbSerialParams.StopBits = ONESTOPBIT;		
	dcbSerialParams.Parity = NOPARITY;		
	if (!SetCommState(hSerial, &dcbSerialParams))
		cout << "Unvalid SetCommState\n";
}
