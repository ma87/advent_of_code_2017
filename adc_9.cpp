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
  string stream;
  int counter = 0;
  int counter_garbage = 0;
  while(std::getline(f, stream))
  {
    string::iterator it;
    bool is_garbage = false;
    bool is_escape = false;
    int counter_group = 0;

    for (it = stream.begin(); it < stream.end(); it++)
    {
      if (is_escape)
      {
        is_escape = false;
        continue;
      }
      if (*it == '!')
      {
        is_escape = true;
        continue;
      }
      if (is_garbage && *it == '>')
      {
        is_garbage = false;
        continue;
      }
      if (!is_garbage && *it == '<')
      {
        is_garbage = true;
        continue;
      }
      if (!is_garbage)
      {
        if (*it == '{')
        {
          counter_group++;
        }
        if (*it == '}')
        {
          counter += counter_group;
          counter_group--;
        }
      }
      else
      {
        counter_garbage++;
      }
    }
  }

  cout << "score: " << counter << endl;
  cout << "counter_garbage: " << counter_garbage << endl;

  return 0;
}
