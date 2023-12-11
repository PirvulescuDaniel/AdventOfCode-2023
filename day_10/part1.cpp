#include <algorithm>
#include <cmath>
#include <fstream>
#include <iostream>
#include <queue>
#include <sstream>
#include <string>
#include <unordered_map>
#include <vector>

using namespace std;

#define LINE_NUM 140
#define COLUMN_NUM 140

char map[LINE_NUM][COLUMN_NUM];
int distances[LINE_NUM][COLUMN_NUM];

std::pair<int, int> startingPos{};
std::unordered_map<char, std::string> pipes = {

    {'|', "north-south"}, {'-', "east-west"},  {'L', "north-east"},
    {'J', "north-west"},  {'7', "south-west"}, {'F', "south-east"}};

std::unordered_map<std::string, std::pair<int, int>> directions{
    {"north"s, {-1, 0}}, {"south"s, {1, 0}}, {"east"s, {0, 1}}, {"west"s, {0, -1}}};

int main()
{
    std::ifstream f("input.in");
    std::ofstream g("output.out");

    int line = -1;
    while (!f.eof())
    {
        line++;

        std::string lineText{};
        std::getline(f, lineText);

        int column = 0;
        for (const auto &chr : lineText)
        {
            if (chr == 'S')
                startingPos = std::make_pair(line, column);

            map[line][column++] = chr;
        }
    }

    std::queue<std::pair<int, int>> nodes{};
    nodes.push(std::make_pair(startingPos.first, startingPos.second));

    while (!nodes.empty())
    {
        auto pipeType = map[nodes.front().first][nodes.front().second];
        if (pipeType == 'S')
            pipeType = '|'; // hardcoded value:)

        const auto &flatDirections = pipes[pipeType];
        const auto &sep = flatDirections.find('-');
        const auto &direction1 = directions[flatDirections.substr(0, sep)];
        const auto &direction2 = directions[flatDirections.substr(sep + 1, std::string::npos)];

        // first node
        const auto &nextDir1X = nodes.front().first + direction1.first;
        const auto &nextDir1Y = nodes.front().second + direction1.second;

        // second node
        const auto &nextDir2X = nodes.front().first + direction2.first;
        const auto &nextDir2Y = nodes.front().second + direction2.second;

        auto nextPipe = map[nextDir1X][nextDir1Y];
        if (nextPipe != '.' && nextPipe != 'S' && distances[nextDir1X][nextDir1Y] == 0)
        {
            distances[nextDir1X][nextDir1Y] = distances[nodes.front().first][nodes.front().second] + 1;
            nodes.push(std::make_pair(nextDir1X, nextDir1Y));
        }

        nextPipe = map[nextDir2X][nextDir2Y];
        if (nextPipe != '.' && nextPipe != 'S' && distances[nextDir2X][nextDir2Y] == 0)
        {
            distances[nextDir2X][nextDir2Y] = distances[nodes.front().first][nodes.front().second] + 1;
            nodes.push(std::make_pair(nextDir2X, nextDir2Y));
        }

        nodes.pop();
    }

    auto maxSteps = std::numeric_limits<int>::min();
    for (int i = 0; i < LINE_NUM; i++)
    {
        for (int j = 0; j < COLUMN_NUM; j++)
        {
            maxSteps = std::max(maxSteps, distances[i][j]);
        }
    }

    g << maxSteps;

    return 0;
}
