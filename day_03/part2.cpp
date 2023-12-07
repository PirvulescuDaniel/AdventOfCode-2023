#include <algorithm>
#include <cmath>
#include <fstream>
#include <iostream>
#include <sstream>
#include <string>
#include <vector>
#include <map>

constexpr int kLines = 140;
constexpr int kColumn = 140;

char charMap[kLines][kColumn];

int di[8] = { -1, -1, -1, 0, 0, 1, 1, 1 };
int dj[8] = { -1, 0, 1, -1, 1, -1, 0, 1 };

bool HasSymbolNeighbour(int line, int column, char& aSymbol, std::pair<int,int>& aSymbolPos)
{
  const std::string kSymbols = "#$%&*+-/=@";

  for (int k = 0; k < 8; k++)
  {
    int i = line + di[k];
    int j = column + dj[k];

    if (0 <= i && i < kLines && 0 <= j && j < kColumn)
      if (kSymbols.find(charMap[i][j]) != std::string::npos)
      {
        aSymbol = charMap[i][j];
        aSymbolPos = std::make_pair(i, j);
        return true;
      }
  }

  return false;
}

int main()
{
  std::ifstream f("input.in");
  std::ofstream g("output.out");

  int line = -1;
  while (!f.eof())
  {
    line++;

    std::string lineString{};
    std::getline(f, lineString);

    for (int i = 0; i < lineString.length(); i++)
      charMap[line][i] = lineString[i];
  }

  std::map< std::pair<int, int>, std::vector<int> > gears{};

  for (int i = 0; i < kLines; i++)
  {
    int j = 0;
    while (j < kColumn)
    {
      int num = 0;
      bool hasSymbolAsNeighbour = false;
      bool adjacentToGear = false;
      std::pair<int, int> gearPosition{};

      auto chr = charMap[i][j];
      while (std::isdigit(chr) && j < kColumn)
      {
        char symbol{};
        std::pair<int, int> symbolPosition{};
        hasSymbolAsNeighbour |= HasSymbolNeighbour(i, j,symbol, symbolPosition);
        num = (num * 10) + (charMap[i][j] - '0');
        j++;
        chr = charMap[i][j];

        if (symbol == '*')
        {
          adjacentToGear = true;
          gearPosition = symbolPosition;
        }
      }

      if (num != 0)
      {
        if (hasSymbolAsNeighbour && adjacentToGear)
            gears[gearPosition].push_back(num);
      }
      else
        j++;
    }
  }

  unsigned long long sum = 0;
  for (const auto& gear : gears)
  {
    const auto& partsVector = gear.second;
    if (partsVector.size() == 2)
      sum += (static_cast<unsigned long long>(partsVector[0]) * static_cast<unsigned long long>(partsVector[1]));
  }

  g << sum;

  return 0;
}
