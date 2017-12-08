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

typedef bool (*comparator_operation)(int, int);

bool isGreater(int a, int b)
{
  return (a > b);
}

bool isGreaterOrEqual(int a, int b)
{
  return (a >= b);
}

bool isEqual(int a, int b)
{
  return (a == b);
}

bool isNotEqual(int a, int b)
{
  return (a != b);
}

bool isLessOrEqual(int a, int b)
{
  return (a <= b);
}

bool isLess(int a, int b)
{
  return (a < b);
}


class Condition
{
public:
  Condition(string variable, string comparator, int value)
  {
    variable_name = variable;

    if (comparator == ">")
    {
      pcomparator_operation = &isGreater;
    }
    else if (comparator == ">=")
    {
      pcomparator_operation = &isGreaterOrEqual;
    }
    else if (comparator == "==")
    {
      pcomparator_operation = &isEqual;
    }
    else if (comparator == "!=")
    {
      pcomparator_operation = &isNotEqual;
    }
    else if (comparator == "<=")
    {
      pcomparator_operation = &isLessOrEqual;
    }
    else if (comparator == "<")
    {
      pcomparator_operation = &isLess;
    }

    comparated_value = value;
  }

  bool isConditionTrue(int variable_value)
  {
    return pcomparator_operation(variable_value, comparated_value);
  }

  string variable_name;
  comparator_operation pcomparator_operation;
  int   comparated_value;
};

class Instruction
{
public:
  Instruction(string line, map<string, int> & registers)
  {
    std::istringstream iss(line);
    iss >> variable_name;

    // init registers
    registers[variable_name] = 0;

    string operation_name;
    iss >> operation_name;

    if (operation_name == "inc")
    {
      operation = 1;
    }
    else
    {
      operation = -1;
    }

    iss >> value;

    string dummy_if;
    iss >> dummy_if;

    string comparated_variable;
    string comparator;
    int comparated_value;
    iss >> comparated_variable;
    iss >> comparator;
    iss >> comparated_value;
    condition = new Condition(comparated_variable, comparator, comparated_value);
  }

  void print_instruction()
  {
    //cout << variable_name << " " << operation << " " << value << " if " << condition->variable_name << " " << condition->comparator_type << " " << condition->comparated_value << endl;
  }

  string variable_name;
  int    operation;
  int    value;
  Condition * condition;
};

class Processor
{
public:
  Processor()
  {
    maxValueDuringProcess = -100000;
  }
  void processInstruction(const Instruction & instruction)
  {
    if (instruction.condition->isConditionTrue(registers[instruction.condition->variable_name]))
    {
      registers[instruction.variable_name] += instruction.operation * instruction.value;
    }

    int maxValueInstruction = getMaxValue();
    if (maxValueInstruction > maxValueDuringProcess)
    {
      maxValueDuringProcess = maxValueInstruction;
    }
  }

  int getMaxValue()
  {
    int max = -1000000;
    for (std::map<string,int>::iterator it=registers.begin(); it!=registers.end(); ++it)
    {
      //cout << "register " << it->first << " = " << it->second << endl;
      if (it->second > max)
      {
        max = it->second;
      }
    }
    return max;
  }

  int getMaxValueDuringProcess()
  {
    return maxValueDuringProcess;
  }

  int maxValueDuringProcess;
  map<string, int> registers;
};


int main(int argc, char * argv[])
{
  Processor proc;
  vector<Instruction> instructions;
  std::ifstream f;
  f.open(argv[1]);
  for (std::string line; std::getline(f, line); )
  {
    instructions.push_back(Instruction(line, proc.registers));
  }

  for (vector<Instruction>::iterator it = instructions.begin(); it!=instructions.end(); it++)
  {
    proc.processInstruction(*it);
  }

  cout << proc.getMaxValue() << endl;
  cout << proc.getMaxValueDuringProcess() << endl;
}
