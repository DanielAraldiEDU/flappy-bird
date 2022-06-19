#include <iostream>

using namespace std;

struct Score
{
  int score;
  int speed;
};

Score setScore(int birdX, int obstacleX, int currentScore, int currentSpeed)
{
  Score scoreIndicators;

  scoreIndicators.score = currentScore;
  scoreIndicators.speed = currentSpeed;

  if (birdX == obstacleX + 1)
  {
    currentScore++;
    scoreIndicators.score = currentScore;

    if (currentScore != 0 && currentScore % 5 == 0 && currentSpeed > 40)
    {
      currentSpeed -= 20;
    }

    scoreIndicators.speed = currentSpeed;
  }

  return scoreIndicators;
}