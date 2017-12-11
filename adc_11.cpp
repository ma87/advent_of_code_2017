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

int get_max(int a, int b, int c)
{
    int max = a;
    if (b > max)
    {
      max = b;
    }
    if (c > max)
    {
      max = c;
    }
    return max;
}

int main(int argc, char * argv[])
{

  // Get inspiration from http://keekerdc.com/2011/03/hexagon-grids-coordinate-systems-and-distance-calculations/

  std::ifstream f;
  f.open(argv[1]);
  string direction;

  int child_x = 0;
  int child_y = 0;
  int child_z = 0;
  int furthest = 0;
  int tmp_distance;
  while(std::getline(f, direction, ','))
  {
    if (direction == "n")
    {
      child_y++;
    }
    else if (direction == "ne")
    {
      child_x++;
    }
    else if (direction == "se")
    {
      child_y--;
      child_x++;
    }
    else if (direction == "s")
    {
      child_y--;
    }
    else if (direction == "sw")
    {
      child_x--;
    }
    else if (direction == "nw")
    {
      child_y++;
      child_x--;
    }
    child_z = -child_x - child_y;
    tmp_distance = get_max(child_x, child_y, child_z);
    if (tmp_distance > furthest)
    {
      furthest = tmp_distance;
    }
  }

  cout << "distance = " << get_max(child_x, child_y, child_z) << endl;
  cout << "furthest = " << furthest << endl;

  return 0;
}
