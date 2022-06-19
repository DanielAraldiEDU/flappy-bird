#include <iostream>
#include <windows.h>

using namespace std;

void message(int x, int y, string message = "", int value = -1)
{
  HANDLE out = GetStdHandle(STD_OUTPUT_HANDLE);
  CONSOLE_CURSOR_INFO cursorInfo;
  cursorInfo.bVisible = false;
  SetConsoleCursorInfo(out, &cursorInfo);
  COORD coordenates;

  coordenates.X = x;
  coordenates.Y = y;
  SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), coordenates);
  if (value < 0)
    cout << message;
  else
    cout << message << value;
}
