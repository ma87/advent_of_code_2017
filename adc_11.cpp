#include <vector>
#include <iterator>
#include <sstream>
#include <fstream>
#include <iostream>
#include <string>
#include <algorithm>
#include <stdlib.h>
#include <math.h>
#include <map>

using namespace std;

int main(int argc, char * argv[])
{
  std::ifstream f;
  f.open(argv[1]);
  string direction;

  double child_x = 0;
  double child_y = 0;
  double sqrt_3_over_2 = 1;
  cout << "pos child " << child_x << " , " << child_y << endl << endl;
  while(std::getline(f, direction, ','))
  {
    cout << direction << endl;
    if (direction == "n")
    {
      child_y += 1.0;
    }
    else if (direction == "ne")
    {
      child_y += 0.5;
      child_x += sqrt_3_over_2;
    }
    else if (direction == "se")
    {
      child_y -= 0.5;
      child_x += sqrt_3_over_2;
    }
    else if (direction == "s")
    {
      child_y -= 1.0;
    }
    else if (direction == "sw")
    {
      child_x -= sqrt_3_over_2;
      child_y -= 0.5;
    }
    else if (direction == "nw")
    {
      child_y += 0.5;
      child_x -= sqrt_3_over_2;
    }
    cout << "pos child " << child_x << " , " << child_y << endl << endl;
  }

  cout << "FINAL pos child " << child_x << " , " << child_y << endl;


  int step = 0;
  double cur_x = 0.0;
  double cur_y = 0.0;
  while ((cur_x != child_x) || (cur_y != child_y))
  {
    if (cur_x != child_x)
    {
      if ((child_x < 0) & (child_y > 0)) // GO nw
      {
        cur_y += 0.5;
        cur_x -= sqrt_3_over_2;
      }
      else if ((child_x < 0) & (child_y < 0)) // GO sw
      {
        cur_x -= sqrt_3_over_2;
        cur_y -= 0.5;
      }
      if ((child_x > 0) & (child_y > 0)) // GO ne
      {
        cur_y += 0.5;
        cur_x += sqrt_3_over_2;
      }
      else if ((child_x > 0) & (child_y < 0)) // GO se
      {
        cur_x += sqrt_3_over_2;
        cur_y -= 0.5;
      }
    }
    else
    {
      if (cur_y > child_y) // GO s
      {
        cur_y -= 1.0;
      }
      else // GO n
      {
        cur_y += 1.0;
      }
    }

    step++;
  }

  cout << "FINAL cur " << cur_x << " , " << cur_y << endl;

  cout << step << endl;

  int step2 = child_x / sqrt_3_over_2;
  step2 += abs(child_y) - (step2 * 0.5);
  cout << step2 << endl;
}
