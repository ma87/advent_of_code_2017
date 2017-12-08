#include <string>
#include <vector>
#include <iterator>
#include <sstream>
#include <fstream>
#include <iostream>
#include <algorithm>
#include <stdlib.h>
#include <math.h>

int adc_1_1(std::string input)
{
  int sum = 0;
  std::vector<int> inputs;
  for(std::string::iterator it = input.begin(); it != input.end(); ++it)
  {
    int i = (int)(*it) - (int)'0';
    inputs.push_back(i);
  }

  for (int i = 0 ; i < inputs.size() - 1 ; i++)
  {
    if (inputs[i] == inputs[i+1])
    {
      sum += inputs[i];
    }
  }

  if (inputs[inputs.size() - 1] == inputs[0])
  {
    sum += inputs[0];
  }

  return sum;
}

int adc_1_2(std::string input)
{
  int sum = 0;
  std::vector<int> inputs;
  for(std::string::iterator it = input.begin(); it != input.end(); ++it)
  {
    int i = (int)(*it) - (int)'0';
    inputs.push_back(i);
  }

  int neg_shift = inputs.size() / 2;
  for (int i = 0 ; i < inputs.size() / 2; i++)
  {
    if (inputs[i] == inputs[i- neg_shift + inputs.size()])
    {
      sum += inputs[i];
    }
  }
  for (int i = inputs.size() / 2 ; i < inputs.size(); i++)
  {
    if (inputs[i] == inputs[i-neg_shift])
    {
      sum += inputs[i];
    }
  }
  return sum;
}

typedef enum
{
  UP = 0,
  DOWN,
  LEFT,
  RIGHT
} DIRECTION;

int get_shift(DIRECTION dir, int size_square)
{
  switch (dir)
  {
    case LEFT:
      return -size_square;
    case RIGHT:
      return size_square;
    case UP:
      return -1;
    case DOWN:
      return 1;
  }
}

void fill_mem_array(int * mem_array, int size_square, int data, int & pos_i, int & pos_j)
{
  int pos = size_square / 2;
  std::cout << "int pos : " << pos << std::endl;

  for (int i = 0 ; i < size_square ; i++)
  {
    for (int j = 0 ; j < size_square ; j++)
    {
      mem_array[i + size_square * j] = 0;
    }
  }

  int * p_mem = &mem_array[pos + size_square * pos];
  pos_i = pos;
  pos_j = pos;
  int counter = 1;
  *p_mem = counter++;

  DIRECTION dir = RIGHT;

  while ((counter - 1) != data)
  {
    switch (dir)
    {
      case LEFT:
        pos_j--;
        break;
      case RIGHT:
        pos_j++;
        break;
      case UP:
        pos_i--;
        break;
      case DOWN:
        pos_i++;
        break;
    }
    int shift = get_shift(dir, size_square);
    std::cout << "counter: " << counter << " goes dir " << dir << " and shift " << shift << std::endl;
    std::cout << "current pos = " << pos_i << " , " << pos_j << std::endl;
    p_mem += shift;
    *p_mem = counter++;
    switch(dir)
    {
      case LEFT:
        if (mem_array[pos_i + 1 + pos_j * size_square] == 0)
        {
          dir = DOWN;
        }
        break;
      case RIGHT:
        if (mem_array[pos_i - 1 + pos_j * size_square] == 0)
        {
          dir = UP;
        }
        break;
      case UP:
        std::cout << "nen_array[ " << (pos_i + (pos_j - 1) * size_square) << "] = " << mem_array[pos_i + (pos_j - 1) * size_square] << std::endl;
        if (mem_array[pos_i + (pos_j - 1) * size_square] == 0)
        {
          dir = LEFT;
        }
        break;
      case DOWN:
        if (mem_array[pos_i + (pos_j + 1) * size_square] == 0)
        {
          dir = RIGHT;
        }
        break;
    }
  }
}

void print_mem_array(int * mem_array, int size_square)
{
  for (int i = 0 ; i < size_square ; i++)
  {
    for (int j = 0 ; j < size_square ; j++)
    {
      std::cout << mem_array[i + size_square * j] << " ";
    }
    std::cout << std::endl;
  }
}

int get_number_steps(int * mem_array, int size_square, int pos_i, int pos_j)
{
  int counter = 0;

  while (mem_array[pos_i + size_square * pos_j] != 1)
  {
    int min = 999999;
    int shift_min_i = 0;
    int shift_min_j = 0;

    //LEFT
    int left = mem_array[pos_i + (pos_j - 1) * size_square];
    if ((left > 0) && (left < min))
    {
      min = left;
      shift_min_i = 0;
      shift_min_j = -1;
    }

    //RIGHT
    int right = mem_array[pos_i + (pos_j + 1) * size_square];
    if ((right > 0) && (right < min))
    {
      min = right;
      shift_min_i = 0;
      shift_min_j = 1;
    }

    //UP
    int up = mem_array[pos_i - 1 + pos_j * size_square];
    if ((up > 0) && (up < min))
    {
      min = up;
      shift_min_i = -1;
      shift_min_j = 0;
    }


    //DOWN
    int down = mem_array[pos_i + 1 + pos_j * size_square];
    if ((down > 0) && (down < min))
    {
      min = down;
      shift_min_i = 1;
      shift_min_j = 0;
    }

    counter ++;
    pos_i += shift_min_i;
    pos_j += shift_min_j;
  }

  return counter;
}

int adc_3_1(int data)
{
  // Generate square
  int size_square = (int)floor(sqrt((float)data));
  std::cout << "size_square 1: " << size_square << std::endl;

  if (size_square % 2 == 0)
  {
    std::cout << "size even" << std::endl;
    size_square += 3;
  }
  else
  {
    size_square += 2;
  }
  std::cout << "size_square 2: " << size_square << std::endl;

  int * mem_array = (int *)malloc(size_square * size_square * sizeof(int));
  int pos_i;
  int pos_j;

  fill_mem_array(mem_array, size_square, data, pos_i, pos_j);

  print_mem_array(mem_array, size_square);

  return get_number_steps(mem_array, size_square, pos_i, pos_j);
}

int get_sum_near(int * mem_array, int size_square, int pos_i, int pos_j)
{
  int sum = 0;
  std::cout << "get sum near" << std::endl;
  for (int i = -1 ; i < 2 ; i++)
  {
    for (int j = -1 ; j < 2 ; j++)
    {
      std::cout << " i, j = " << i << " , " << j << std::endl;
      int value = mem_array[pos_i + i + (pos_j + j) * size_square];
      sum += value;
    }
  }
  return sum;
}

int fill_mem_array_2(int * mem_array, int size_square, int data, int & pos_i, int & pos_j)
{
  int value = 0;
  int pos = size_square / 2;
  std::cout << "int pos : " << pos << std::endl;

  for (int i = 0 ; i < size_square ; i++)
  {
    for (int j = 0 ; j < size_square ; j++)
    {
      mem_array[i + size_square * j] = 0;
    }
  }

  int * p_mem = &mem_array[pos + size_square * pos];
  pos_i = pos;
  pos_j = pos;
  int counter = 1;
  *p_mem = 1;

  DIRECTION dir = RIGHT;

  while ((counter - 1) != data)
  {
    switch (dir)
    {
      case LEFT:
        pos_j--;
        break;
      case RIGHT:
        pos_j++;
        break;
      case UP:
        pos_i--;
        break;
      case DOWN:
        pos_i++;
        break;
    }
    int shift = get_shift(dir, size_square);
    p_mem += shift;

    *p_mem = get_sum_near(mem_array, size_square, pos_i, pos_j);

    value = *p_mem;
    if (value > data)
    {
      return value;
    }
    counter++;
    switch(dir)
    {
      case LEFT:
        if (mem_array[pos_i + 1 + pos_j * size_square] == 0)
        {
          dir = DOWN;
        }
        break;
      case RIGHT:
        if (mem_array[pos_i - 1 + pos_j * size_square] == 0)
        {
          dir = UP;
        }
        break;
      case UP:
        if (mem_array[pos_i + (pos_j - 1) * size_square] == 0)
        {
          dir = LEFT;
        }
        break;
      case DOWN:
        if (mem_array[pos_i + (pos_j + 1) * size_square] == 0)
        {
          dir = RIGHT;
        }
        break;
    }
  }

  return value;
}

int adc_3_2(int data)
{
  // Generate square
  int size_square = (int)floor(sqrt((float)data));
  std::cout << "size_square 1: " << size_square << std::endl;

  if (size_square % 2 == 0)
  {
    std::cout << "size even" << std::endl;
    size_square += 3;
  }
  else
  {
    size_square += 2;
  }
  std::cout << "size_square 2: " << size_square << std::endl;

  int * mem_array = (int *)malloc(size_square * size_square * sizeof(int));
  int pos_i;
  int pos_j;

  int value = fill_mem_array_2(mem_array, size_square, data, pos_i, pos_j);

  //print_mem_array(mem_array, size_square);

  return value;
}

int adc_5_1(const char * filename)
{
  std::ifstream f;
  f.open(filename);
  std::vector<int> jumps;
  int jump;
  while (f >> jump)
  {
      jumps.push_back(jump);
  }

  int current_jump = 0;
  int number_jumps = jumps.size();
  int step = 0;
  while (current_jump < number_jumps)
  {
    jumps[current_jump]++;
    current_jump += jumps[current_jump] - 1;
    step++;
  }

  return step;
}

int adc_5_2(const char * filename)
{
  std::ifstream f;
  f.open(filename);
  std::vector<int> jumps;
  int jump;
  while (f >> jump)
  {
      jumps.push_back(jump);
  }

  int current_jump = 0;
  int number_jumps = jumps.size();
  int step = 0;
  int offset;
  while (current_jump < number_jumps)
  {
    if (jumps[current_jump] > 2)
    {
      offset = -1;
    }
    else
    {
      offset = 1;
    }
    jumps[current_jump] += offset;
    current_jump += jumps[current_jump] - offset;
    step++;
  }

  return step;
}

int adc_4_1(const char * filename)
{
  std::ifstream f;
  f.open(filename);
  int number_valid = 0;
  for (std::string line; std::getline(f, line); )
  {
      std::vector<std::string> words;
      std::istringstream iss(line);
      std::string word;
      int duplicated_words = 0;
      while(iss >> word)
      {
        for(int i = 0 ; i < words.size() ; i++)
        {
          if (!word.compare(words[i]))
          {
            duplicated_words = 1;
            break;
          }
        }

        if (duplicated_words > 0)
        {
          break;
        }
        else
        {
          words.push_back(word);
        }
      }

      if (duplicated_words == 0)
      {
        number_valid++;
      }

  }
  return number_valid;
}

bool are_words_anagram(std::string & word_a, std::string & word_b)
{
  int chars[26];
  for (int i = 0 ; i < 26 ; i++)
  {
    chars[i] = 0;
  }

  if (word_a.length() != word_b.length())
  {
    return false;
  }

  for (int i = 0 ; i < word_a.length() ; i++)
  {
    chars[word_a[i] - 'a']++;
    chars[word_b[i] - 'a']--;
  }

  for (int i = 0 ; i < 26 ; i++)
  {
    if (chars[i] != 0)
    {
      return false;
    }
  }

  return true;
}

bool is_word_anagram(std::string & word, std::vector<std::string> & words)
{
  for (int i = 0 ; i < words.size() ; i++)
  {
    if (are_words_anagram(word, words[i]))
    {
      return true;
    }
  }
  return false;
}

int adc_4_2(const char * filename)
{
  std::ifstream f;
  f.open(filename);
  int number_valid = 0;
  for (std::string line; std::getline(f, line); )
  {
      std::vector<std::string> words;
      std::istringstream iss(line);
      std::string word;
      bool is_anagram = false;
      while(iss >> word)
      {
        if (is_word_anagram(word, words))
        {
          is_anagram = true;
          break;
        }
        else
        {
          words.push_back(word);
        }
      }

      if (!is_anagram)
      {
        number_valid++;
      }

  }
  return number_valid;
}

int get_next_block(int idx, int size)
{
    if (idx < (size - 1))
    {
      return idx + 1;
    }
    else
    {
      return 0;
    }
}

int adc_6_1(const char * filename)
{
  std::ifstream f;
  f.open(filename);
  std::vector<int> mem_banks;
  int count;
  while (f >> count)
  {
      mem_banks.push_back(count);
  }
  int mem_banks_size = mem_banks.size();
  std::cout << "size of mem_banks " << mem_banks_size << std::endl;
  for(int i = 0 ; i < mem_banks_size ; i++)
  {
    std::cout << mem_banks[i] << " ";
  }
  std::cout << std::endl;

  int step = 0;
  bool infinite_loop_detected = false;
  std::vector<std::vector<int>> recorded_mem_banks;
  recorded_mem_banks.push_back(std::vector<int>(mem_banks));

  do
  {
    step++;
    int max_index = -1;
    int max_blocks = -1;

    for(int i = 0 ; i < mem_banks_size ; i++)
    {
      if (mem_banks[i] > max_blocks)
      {
        max_index = i;
        max_blocks = mem_banks[i];
      }
    }

    int redistribute_blocks = max_blocks;
    mem_banks[max_index] = 0;
    int current_block = get_next_block(max_index, mem_banks_size);
    while(redistribute_blocks > 0)
    {
        mem_banks[current_block]++;
        redistribute_blocks--;
        current_block = get_next_block(current_block, mem_banks_size);
    }

    for (int i = 0 ; i < recorded_mem_banks.size() ; i++)
    {
      if (std::equal(mem_banks.begin(), mem_banks.begin() + mem_banks_size, recorded_mem_banks[i].begin()))
      {
          infinite_loop_detected = true;
      }
    }

    recorded_mem_banks.push_back(std::vector<int>(mem_banks));

  } while (!infinite_loop_detected);

  return step;
}

int adc_6_2(const char * filename)
{
  std::ifstream f;
  f.open(filename);
  std::vector<int> mem_banks;
  int count;
  while (f >> count)
  {
      mem_banks.push_back(count);
  }
  int mem_banks_size = mem_banks.size();
  std::cout << "size of mem_banks " << mem_banks_size << std::endl;
  for(int i = 0 ; i < mem_banks_size ; i++)
  {
    std::cout << mem_banks[i] << " ";
  }
  std::cout << std::endl;

  int step = 0;
  bool first_infinite_loop_detected = false;
  bool second_infinite_loop_detected = false;
  std::vector<std::vector<int>> recorded_mem_banks;
  recorded_mem_banks.push_back(std::vector<int>(mem_banks));

  do
  {
    if (first_infinite_loop_detected)
    {
      step++;
    }
    int max_index = -1;
    int max_blocks = -1;

    for(int i = 0 ; i < mem_banks_size ; i++)
    {
      if (mem_banks[i] > max_blocks)
      {
        max_index = i;
        max_blocks = mem_banks[i];
      }
    }

    int redistribute_blocks = max_blocks;
    mem_banks[max_index] = 0;
    int current_block = get_next_block(max_index, mem_banks_size);
    while(redistribute_blocks > 0)
    {
        mem_banks[current_block]++;
        redistribute_blocks--;
        current_block = get_next_block(current_block, mem_banks_size);
    }

    for (int i = 0 ; i < recorded_mem_banks.size() ; i++)
    {
      if (std::equal(mem_banks.begin(), mem_banks.begin() + mem_banks_size, recorded_mem_banks[i].begin()))
      {
          if (!first_infinite_loop_detected)
          {
            first_infinite_loop_detected = true;
            recorded_mem_banks.clear();
          }
          else
          {
            second_infinite_loop_detected = true;
          }
      }
    }

    recorded_mem_banks.push_back(std::vector<int>(mem_banks));

  } while (!second_infinite_loop_detected);

  return step;
}

int main(int argc, char * argv[])
{
  std::string input = "29917128875332952564321392569634257121244516819997569284938677239676779378822158323549832814412597817651244117851771257438674567254146559419528411463781241159837576747416543451994579655175322397355255587935456185669334559882554936642122347526466965746273596321419312386992922582836979771421518356285534285825212798113159911272923448284681544657616654285632235958355867722479252256292311384799669645293812691169936746744856227797779513997329663235176153745581296191298956836998758194274865327383988992499115472925731787228592624911829221985925935268785757854569131538763133427434848767475989173579655375125972435359317237712667658828722623837448758528395981635746922144957695238318954845799697142491972626942976788997427135797297649149849739186827185775786254552866371729489943881272817466129271912247236569141713377483469323737384967871876982476485658337183881519295728697121462266226452265259877781881868585356333494916519693683238733823362353424927852348119426673294798416314637799636344448941782774113142925315947664869341363354235389597893211532745789957591898692253157726576488811769461354938575527273474399545366389515353657644736458182565245181653996192644851687269744491856672563885457872883368415631469696994757636288575816146927747179133188841148212825453859269643736199836818121559198563122442483528316837885842696283932779475955796132242682934853291737434482287486978566652161245555856779844813283979453489221189332412315117573259531352875384444264457373153263878999332444178577127433891164266387721116357278222665798584824336957648454426665495982221179382794158366894875864761266695773155813823291684611617853255857774422185987921219618596814446229556938354417164971795294741898631698578989231245376826359179266783767935932788845143542293569863998773276365886375624694329228686284863341465994571635379257258559894197638117333711626435669415976255967412994139131385751822134927578932521461677534945328228131973291962134523589491173343648964449149716696761218423314765168285342711137126239639867897341514131244859826663281981251614843274762372382114258543828157464392";
  // std::cout << ad  c_1_1(input) << std::endl;
  // std::cout << adc_1_2(input) << std::endl;
  // std::cout << adc_3_2(9) << std::endl;
  // 289326
  // std::cout << adc_3_2(289326) << std::endl;
  // std::cout << adc_5_2("adc_5.txt") << std::endl;
  //std::cout << adc_4_2("adc_4.txt") << std::endl;
  std::cout << adc_6_2("adc_6.txt") << std::endl;
}
