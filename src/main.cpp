#include <iostream>
#include <windows.h>
#include <conio.h>
#include <time.h>

using namespace std;

int main()
{
  HANDLE out = GetStdHandle(STD_OUTPUT_HANDLE);
  CONSOLE_CURSOR_INFO cursorInfo;
  GetConsoleCursorInfo(out, &cursorInfo);
  cursorInfo.bVisible = false;
  SetConsoleCursorInfo(out, &cursorInfo);
  COORD coord;

  system("cls");

  srand(time(NULL));

  int bird_x = 15, bird_y = 10, obstaculo1_x = 130, obstaculo1_y, obstaculo2_x = 130, obstaculo2_y, tecla, passagem1, passagem2, velocidade = 200, placar = 0;
  bool estaVoando = true;

  cout << "-----------------------------------------------------------------------------------------------------------------------------------";
  cout << "\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n";
  cout << "-----------------------------------------------------------------------------------------------------------------------------------";

  passagem1 = rand() % 15 + 3;
  passagem2 = rand() % 15 + 3;

  while (estaVoando)
  {
    coord.X = 60;
    coord.Y = 1;
    SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), coord);
    cout << "PLACAR: " << placar;

    coord.X = bird_x;
    coord.Y = bird_y;
    SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), coord);
    cout << char(190);

    obstaculo1_y = 1;
    while (obstaculo1_y < 20)
    {
      coord.X = obstaculo1_x;
      coord.Y = obstaculo1_y;
      SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), coord);

      if (obstaculo1_y < passagem1 - 2 || obstaculo1_y > passagem1 + 2)
      {
        cout << char(219);
      }
      else
      {
        cout << " ";
      }

      obstaculo1_y++;

      coord.X = obstaculo1_x + 1;
      SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), coord);
      cout << " ";
    }

    if (obstaculo1_x <= 65 || obstaculo2_x <= 65)
    {
      obstaculo2_y = 1;
      while (obstaculo2_y < 20)
      {
        coord.X = obstaculo2_x;
        coord.Y = obstaculo2_y;
        SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), coord);

        if (obstaculo2_y < passagem2 - 2 || obstaculo2_y > passagem2 + 2)
        {
          cout << char(219);
        }
        else
        {
          cout << " ";
        }

        obstaculo2_y++;

        coord.X = obstaculo2_x + 1;
        SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), coord);
        cout << " ";
      }
    }

    if ((bird_y <= 0 || bird_y >= 20) ||
        (obstaculo1_x == bird_x && (bird_y < passagem1 - 2 || bird_y > passagem1 + 2)) ||
        (obstaculo2_x == bird_x && (bird_y < passagem2 - 2 || bird_y > passagem2 + 2)))
    {
      system("cls");
      estaVoando = false;

      coord.X = 50;
      coord.Y = 10;
      SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), coord);
      cout << "GAME OVER";

      coord.Y = 12;
      SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), coord);
      cout << "PLACAR: " << placar;

      coord.X = 35;
      coord.Y = 14;
      SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), coord);
      system("pause");
    }

    if (bird_x == obstaculo1_x + 1 || bird_x == obstaculo2_x + 1)
    {
      placar++;

      if (placar != 0 && placar % 5 == 0 && velocidade > 40)
      {
        velocidade -= 20;
      }
    }

    if (kbhit())
    {
      tecla = getch();
    }

    if (tecla == 'w' || tecla == 'W')
    {
      bird_y--;
      tecla = '0';
    }
    else
    {
      bird_y++;
    }

    obstaculo1_x--;

    if (obstaculo1_x <= 65 || obstaculo2_x <= 65)
    {
      obstaculo2_x--;
    }

    Sleep(velocidade);

    coord.Y = bird_y - 1;
    coord.X = bird_x;
    SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), coord);
    if (bird_y != 1)
    {
      cout << " ";
    }

    coord.Y = bird_y + 1;
    coord.X = bird_x;
    SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), coord);
    if (bird_y != 19)
    {
      cout << " ";
    }

    if (obstaculo1_x < 0)
    {
      coord.X = obstaculo1_x + 1;
      while (obstaculo1_y > 0)
      {
        coord.Y = obstaculo1_y;
        SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), coord);
        cout << " ";
        obstaculo1_y--;
      }

      passagem1 = rand() % 15 + 3;
      obstaculo1_x = 130;
    }
    else if (obstaculo2_x < 0)
    {
      coord.X = obstaculo2_x + 1;
      while (obstaculo2_y > 0)
      {
        coord.Y = obstaculo2_y;
        SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), coord);
        cout << " ";
        obstaculo2_y--;
      }

      passagem2 = rand() % 15 + 3;
      obstaculo2_x = 130;
    }
  }

  return 0;
}
