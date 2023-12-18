#include <algorithm>
#include <cmath>
#include <fstream>
#include <iostream>
#include <queue>
#include <sstream>
#include <string>
#include <unordered_map>
#include <vector>
#include <set>

#define MAX_LINE_AND_COL 300
using Point = std::pair<int, int>;

std::vector<std::vector<char>> map{};
std::vector<Point> galaxies{};
std::vector<std::pair<Point, Point>> galaxiesMap{};

int emptyLines[MAX_LINE_AND_COL];
int emptyColums[MAX_LINE_AND_COL];

int main()
{
  std::ifstream f("input.in");
  std::ofstream g("output.out");

  int lineNo = 0;
  while (!f.eof())
  {
    std::string planeLine{};
    f >> planeLine;

    std::vector<char> line{};
    int columnNo = 0;
    bool isEmptyLine = true;
    for (const auto& chr : planeLine)
    {
      line.push_back(chr);

      if (chr == '#')
      {
        galaxies.push_back(std::make_pair(lineNo, columnNo));
        isEmptyLine = false;
      }

      columnNo++;
    }

    if (lineNo != 0)
      emptyLines[lineNo] = isEmptyLine ? (emptyLines[lineNo - 1] + 1) : emptyLines[lineNo - 1];


    map.push_back(line);
    lineNo++;
  }

  for (int j = 0; j < map[0].size(); j++)
  {
    bool isEmptyColumn = true;
    for (int i = 0; i < map.size(); i++)
    {
      if (map[i][j] != '.')
        isEmptyColumn = false;
    }

    if (j != 0)
      emptyColums[j] = isEmptyColumn ? (emptyColums[j - 1] + 1) : emptyColums[j - 1];
  }

  for (int i = 0; i < galaxies.size() - 1; i++)
  {
    for (int j = i + 1; j < galaxies.size(); j++)
    {
      Point p1(galaxies[i].first, galaxies[i].second);
      Point p2(galaxies[j].first, galaxies[j].second);

      galaxiesMap.push_back(std::make_pair(p1, p2));
    }
  }

  unsigned long long sum = 0;
  for (const auto& [p1, p2] : galaxiesMap)
  {
    const int emptyLinesNo = std::abs(emptyLines[p2.first] - emptyLines[p1.first]);
    const int emptyColsNo = std::abs(emptyColums[p2.second] - emptyColums[p1.second]);

    const int linesDistance = (std::abs(p1.first - p2.first) - emptyLinesNo) + (emptyLinesNo * 1000000);
    const int columnDistance = (std::abs(p1.second - p2.second) - emptyColsNo) + (emptyColsNo * 1000000);

    const int distance = linesDistance + columnDistance;
    //std::cout << "Distance between " << p1.first << " " << p1.second << " and " << p2.first << " " << p2.second << " is " << distance << std::endl;

    sum += distance;
  }

  g << sum;
  return 0;
}
