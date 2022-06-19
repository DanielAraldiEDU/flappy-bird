#include <iostream>
#include <windows.h>
#include "./utils/obstacle.cpp"
#include "./utils/terminal.cpp"
#include "./utils/bird.cpp"
#include "./utils/score.cpp"
#include "./utils/keyboardPress.cpp"

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

  int firstObstacleX = 130, firstObstacleY, secondObstacleX = 130, secondObstacleY, firstObstacleSpace, secondObstacleSpace, speed = 200, score = 0;
  bool isFlying = true;

  cout << "-----------------------------------------------------------------------------------------------------------------------------------";
  cout << "\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n";
  cout << "-----------------------------------------------------------------------------------------------------------------------------------";

  firstObstacleSpace = openSpace();
  secondObstacleSpace = openSpace();

  COORD birdCoordenates = setBirdPosition(15, 10);

  while (isFlying)
  {
    message(60, 1, "SCORE: ", score);

    firstObstacleY = 1;
    while (firstObstacleY < 20)
    {
      coord.X = firstObstacleX;
      coord.Y = firstObstacleY;
      SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), coord);

      if (firstObstacleY < firstObstacleSpace - 2 || firstObstacleY > firstObstacleSpace + 2)
      {
        cout << char(219);
      }
      else
      {
        cout << " ";
      }

      firstObstacleY++;

      coord.X = firstObstacleX + 1;
      SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), coord);
      cout << " ";
    }

    if (firstObstacleX <= 65 || secondObstacleX <= 65)
    {
      secondObstacleY = 1;
      while (secondObstacleY < 20)
      {
        coord.X = secondObstacleX;
        coord.Y = secondObstacleY;
        SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), coord);

        if (secondObstacleY < secondObstacleSpace - 2 || secondObstacleY > secondObstacleSpace + 2)
        {
          cout << char(219);
        }
        else
        {
          cout << " ";
        }

        secondObstacleY++;

        coord.X = secondObstacleX + 1;
        SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), coord);
        cout << " ";
      }
    }

    if ((birdCoordenates.Y <= 0 || birdCoordenates.Y >= 20) ||
        (firstObstacleX == birdCoordenates.X && (birdCoordenates.Y < firstObstacleSpace - 2 || birdCoordenates.Y > firstObstacleSpace + 2)) ||
        (secondObstacleX == birdCoordenates.X && (birdCoordenates.Y < secondObstacleSpace - 2 || birdCoordenates.Y > secondObstacleSpace + 2)))
    {
      system("cls");
      isFlying = false;

      message(50, 5, "GAME OVER");
      message(50, 7, "SCORE: ", score);
      message(35, 10);
      system("pause");
      return 0;
    }

    Score scoreIndicators;

    scoreIndicators = setScore(birdCoordenates.X, firstObstacleX + 1, score, speed);
    score = scoreIndicators.score;
    speed = scoreIndicators.speed;

    scoreIndicators = setScore(birdCoordenates.X, secondObstacleX + 1, score, speed);
    score = scoreIndicators.score;
    speed = scoreIndicators.speed;

    birdCoordenates = handleKeyboardPress(birdCoordenates);

    firstObstacleX--;

    if (firstObstacleX <= 65 || secondObstacleX <= 65)
    {
      secondObstacleX--;
    }

    Sleep(speed);

    SHORT birdY = 0;

    birdY = birdCoordenates.Y - 1;
    checkBirdCollisionVertically({X : birdCoordenates.X, Y : birdY});

    birdY = birdCoordenates.Y + 1;
    checkBirdCollisionVertically({X : birdCoordenates.X, Y : birdY});

    if (firstObstacleX < 0)
    {
      coord.X = firstObstacleX + 1;
      while (firstObstacleY > 0)
      {
        coord.Y = firstObstacleY;
        SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), coord);
        cout << " ";
        firstObstacleY--;
      }

      firstObstacleSpace = openSpace();
      firstObstacleX = 130;
    }
    else if (secondObstacleX < 0)
    {
      coord.X = secondObstacleX + 1;
      while (secondObstacleY > 0)
      {
        coord.Y = secondObstacleY;
        SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), coord);
        cout << " ";
        secondObstacleY--;
      }

      secondObstacleSpace = openSpace();
      secondObstacleX = 130;
    }
  }

  return 0;
}
