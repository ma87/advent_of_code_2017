
#include <vector>
#include <iterator>
#include <sstream>
#include <fstream>
#include <iostream>
#include <string>
#include <algorithm>
#include <stdlib.h>
#include <math.h>

using namespace std;
class Program
{
public:
  Program(string iname, int iweight)
  {
    name = iname;
    weight = iweight;
  }

  string name;
  int weight;
};

class ProgramContainer
{
public:
  ProgramContainer(string name, int weight, vector<string> & sub_programs)
  : program(name, weight)
  , subprograms(sub_programs)
  {
    is_bottom = true;
  }

  ProgramContainer * get_program(std::vector<ProgramContainer> &list, string name)
  {
    for(int i=0 ; i < list.size() ; i++)
    {
      if (list[i].program.name == name)
      {
        return &list[i];
      }
    }
    cout << "program not found " << name << endl;
    return NULL;
  }

  int get_weight(std::vector<ProgramContainer> &list)
  {
    int weight = 0;
    int sub_weight = -1;
    int tmp_weight;
    // std::cout << "---- start of weight " << program.name << " = " << program.weight << endl;
    for (int i = 0 ; i < subprograms.size() ; i++)
    {
      // std::cout << "*** ";
      ProgramContainer * subprogram = get_program(list, subprograms[i]);
      tmp_weight = subprogram->get_weight(list);
      if (sub_weight > 0)
      {
        if (sub_weight != tmp_weight)
        {
          cout << "subprogram " << subprogram->program.name << " has not a good weight" << endl;
        }
      }
      sub_weight = tmp_weight;
    }

    int final_weight = program.weight + subprograms.size() * sub_weight;
    // std::cout << "---- end of weight " << program.name << "---- " << final_weight << endl;

    return final_weight;
  }

  std::vector<string> subprograms;

  Program program;
  bool is_bottom;
};

class Tower
{
public:
  Tower()
  : programs()
  {

  }

  void add(string line)
  {
      string name_program;
      std::istringstream iss(line);
      iss >> name_program;
      string str_weight;
      iss >> str_weight;
      string str_weight_2 = str_weight.substr(1, str_weight.length() - 2);
      std::string token;
      string str_sub_programs;
      std::getline(iss, token, '>');

      vector<string> sub_programs;
      while(std::getline(iss, str_sub_programs, ','))
      {
        sub_programs.push_back(str_sub_programs.substr(1, str_sub_programs.length()));
      }

      programs.push_back(ProgramContainer(name_program, stoi(str_weight_2), sub_programs));
  }

  void print()
  {
    for(int i=0 ; i < programs.size() ; i++)
    {
      cout << programs[i].program.name << " " << "has weight " << programs[i].program.weight << " and has " << programs[i].subprograms.size() << " subprograms" << endl;
    }
  }

  void print_bottom()
  {
    for(int i=0 ; i < programs.size() ; i++)
    {
      if (programs[i].is_bottom)
      {
        cout << programs[i].program.name << endl;
        bottom_program = programs[i].program.name;
      }
    }
  }

  ProgramContainer * get_program(string name)
  {
    for(int i=0 ; i < programs.size() ; i++)
    {
      if (programs[i].program.name == name)
      {
        return &programs[i];
      }
    }
    cout << "program not found " << name << endl;
    return NULL;
  }

  void compute_is_bottom()
  {
    ProgramContainer * container;
    for(int i=0 ; i < programs.size() ; i++)
    {
      for (int j = 0 ; j < programs[i].subprograms.size() ; j++)
      {
        container = get_program(programs[i].subprograms[j]);
        if (container)
        {
          container->is_bottom = false;
        }
      }
    }
  }

  void print_sub_tower_weight()
  {
    ProgramContainer * bottom = get_program(bottom_program);
    ProgramContainer * container;
    for (int j = 0 ; j < bottom->subprograms.size() ; j++)
    {
      container = get_program(bottom->subprograms[j]);
      std::cout << "sub tower " << container->program.name << " has weight " << container->get_weight(programs) << endl;
    }
  }

  string bottom_program;

  vector<ProgramContainer> programs;
};

int main(int argc, char * argv[])
{
  Tower tower;

  std::ifstream f;
  f.open(argv[1]);
  for (std::string line; std::getline(f, line); )
  {
    tower.add(line);
  }

  tower.compute_is_bottom();

  tower.print_bottom();

  tower.print_sub_tower_weight();
}
