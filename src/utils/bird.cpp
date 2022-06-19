#include <iostream>
#include <windows.h>

using namespace std;

HANDLE out = GetStdHandle(STD_OUTPUT_HANDLE);
CONSOLE_CURSOR_INFO cursorInfo;

COORD setBirdPosition(int birdX, int birdY)
{
  cursorInfo.bVisible = false;
  SetConsoleCursorInfo(out, &cursorInfo);
  COORD coordenates;

  coordenates.X = birdX;
  coordenates.Y = birdY;
  SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), coordenates);
  cout << char(190);

  return coordenates;
}

void checkBirdCollisionVertically(COORD coordenates)
{
  cursorInfo.bVisible = false;
  SetConsoleCursorInfo(out, &cursorInfo);

  SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), coordenates);
  if (coordenates.Y != 1 || coordenates.Y != 19)
  {
    cout << " ";
  }
}
