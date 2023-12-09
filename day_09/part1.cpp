#include <algorithm>
#include <cmath>
#include <fstream>
#include <iostream>
#include <sstream>
#include <string>
#include <vector>
#include <unordered_map>

using namespace std;

int GetHistoryValue(const std::vector<int>& aHistory)
{
  bool isArithmeticSequence = true;

  const auto& ratio = aHistory[1] - aHistory[0];
  for (int i = 0; i < aHistory.size() - 1; i++)
  {
    if (aHistory[i + 1] - aHistory[i] != ratio)
    {
      isArithmeticSequence = false;
      break;
    }
  }
  
  if (isArithmeticSequence)
    return aHistory.back() + ratio;

  std::vector<int> nextVec{};
  for (int i = 0; i < aHistory.size() - 1; i++)
    nextVec.push_back(aHistory[i + 1] - aHistory[i]);

  return aHistory.back() + GetHistoryValue(nextVec);
}

int main()
{
  std::ifstream f("input.in");
  std::ofstream g("output.out");

  unsigned long long sum = 0;

  while (!f.eof())
  {
    std::string line{};
    std::getline(f, line);

    std::stringstream ss(line);
    std::vector<int> nums{};

    while (!ss.eof())
    {
      std::string planeNum;;
      ss >> planeNum;

      if (planeNum.empty())
        break;

      nums.push_back(std::stoi(planeNum));
    }

    sum += GetHistoryValue(nums);
  }
  
  g << sum;

  return 0;
}
