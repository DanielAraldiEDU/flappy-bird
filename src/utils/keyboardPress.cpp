#include <iostream>
#include <conio.h>

using namespace std;

COORD handleKeyboardPress(COORD coordenates)
{
  int keyboardKey;

  if (kbhit())
  {
    keyboardKey = getch();
  }

  if (keyboardKey == 'w' || keyboardKey == 'W')
  {
    coordenates = setBirdPosition(15, coordenates.Y);
    coordenates.Y = coordenates.Y - 1;
    keyboardKey = '0';
  }
  else
  {
    coordenates = setBirdPosition(15, coordenates.Y);
    coordenates.Y = coordenates.Y + 1;
  }

  return coordenates;
}