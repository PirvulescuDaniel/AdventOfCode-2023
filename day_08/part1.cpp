#include <algorithm>
#include <cmath>
#include <fstream>
#include <iostream>
#include <sstream>
#include <string>
#include <vector>
#include <unordered_map>

using namespace std;

int main()
{
  std::ifstream f("input.in");
  std::ofstream g("output.out");

  std::string directions{};
  std::getline(f, directions);

  std::string directionsCopy(directions);

  std::unordered_map<std::string, std::pair<std::string, std::string>> nodes{};

  //remove the space between directions line and nodes.

  while (!f.eof())
  {
    std::string nodePlaneText{};
    std::getline(f, nodePlaneText);

    const auto& equalSignPos = nodePlaneText.find('=');
    const auto& nodeName = nodePlaneText.substr(0, equalSignPos - 1);
    
    const auto& sep = nodePlaneText.find(',');
    const auto& left = nodePlaneText.substr(sep - 3, 3);
    const auto& right = nodePlaneText.substr(sep + 2, 3);

    nodes[nodeName] = std::make_pair(left, right);
  }

  auto steps = 0;
  auto currentNode = "AAA"s;

  while (currentNode != "ZZZ"s)
  {
    steps++;

    if (directions.empty())
      directions = directionsCopy;

    currentNode = (directions[0] == 'L') ? nodes[currentNode].first : nodes[currentNode].second;
    directions.erase(directions.begin());
  }

  g << steps;

  return 0;
}
