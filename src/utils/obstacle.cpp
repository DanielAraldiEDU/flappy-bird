#include <iostream>
#include <time.h>

using namespace std;

int openSpace()
{
  srand(time(NULL));

  return rand() % 15 + 3;
}