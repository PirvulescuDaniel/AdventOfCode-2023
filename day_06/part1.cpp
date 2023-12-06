#include <algorithm>
#include <cmath>
#include <deque>
#include <fstream>
#include <iostream>
#include <map>
#include <sstream>
#include <string>
#include <unordered_map>
#include <vector>

using ull = unsigned long long;

std::vector<ull> ToVector(std::string aString)
{
    std::vector<ull> res{};
    aString = aString.substr(aString.find_first_of(' ') + 1, std::string::npos);

    auto spacePos = aString.find_first_of(' ');
    while (spacePos != std::string::npos)
    {
        res.push_back(std::stoi(aString.substr(0, spacePos)));
        aString = aString.substr(spacePos + 1, std::string::npos);
        spacePos = aString.find_first_of(' ');
    }
    res.push_back(std::stoi(aString));

    return res;
}

int main()
{
    std::ifstream f("input.in");
    std::ofstream g("output.out");

    std::string timeString{};
    std::getline(f, timeString);

    std::string distanceString{};
    std::getline(f, distanceString);

    std::vector<ull> times = ToVector(timeString);
    std::vector<ull> distances = ToVector(distanceString);

    ull prod = 1;
    for (ull i = 0; i < times.size(); i++)
    {
        ull winningTimes = 0;
        ull distanceToBeat = distances[i];

        for (ull j = 0; j <= times[i]; j++)
        {
            ull distanceTraveld = j * (times[i] - j);
            winningTimes += distanceTraveld > distanceToBeat ? 1 : 0;
        }

        prod *= winningTimes;
    }

    g << prod;

    return 0;
}
