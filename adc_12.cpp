#include <vector>
#include <list>
#include <iterator>
#include <sstream>
#include <fstream>
#include <iostream>
#include <string>
#include <algorithm>
#include <stdlib.h>
#include <math.h>

using namespace std;

int group_id(int id, vector<vector<int> > & groups)
{
  int tmp_id_group = -1;
  for (vector<vector<int> >::iterator it = groups.begin(); it != groups.end(); it++)
  {
    tmp_id_group++;
    for (vector<int>::iterator it2 = it->begin(); it2 != it->end(); it2++)
    {
      if (*it2 == id)
      {
        return tmp_id_group;
      }
    }
  }

  return -1;
}

bool is_in_group(int id, vector<int> & group)
{
  for (int i = 0; i < group.size(); i++)
  {
    if (group[i] == id)
    {
      return true;
    }
  }
  return false;
}

void print_groups(vector<vector<int> > & groups)
{
  int tmp_id_group = -1;
  for (vector<vector<int> >::iterator it = groups.begin(); it != groups.end(); it++)
  {
    tmp_id_group++;
    std::cout << "group " << tmp_id_group << " contains program_ids ";
    for (vector<int>::iterator it2 = it->begin(); it2 != it->end(); it2++)
    {
      cout << *it2 << " ";
    }
    cout << endl;
  }
}

void add_program(string line, vector<vector<int> > & groups)
{
  std::istringstream iss(line);
  int program_id;
  iss >> program_id;

  int program_id_group = group_id(program_id, groups);
  if (program_id_group == -1)
  {
    groups.push_back(vector<int>());
    groups[groups.size() - 1].push_back(program_id);
    program_id_group = groups.size() - 1;
  }

  string tmp;
  iss >> tmp;

  int program_pipe;

  string str_pipe;
  while(std::getline(iss, str_pipe, ','))
  {
    int pipe = stoi(str_pipe);
    if (!is_in_group(pipe, groups[program_id_group]))
    {
      groups[program_id_group].push_back(pipe);
    }
  }

}

int main(int argc, char * argv[])
{

  // Get inspiration from http://keekerdc.com/2011/03/hexagon-grids-coordinate-systems-and-distance-calculations/

  std::ifstream f;
  f.open(argv[1]);

  vector<vector<int> > groups;
  groups.push_back(vector<int>());
  groups[0].push_back(0);

  string line;
  while(std::getline(f, line))
  {
    add_program(line, groups);
  }

  print_groups(groups);

  cout << "group 0 size: " << groups[0].size() << endl;
  return 0;
}
