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
using Interval = std::tuple<ull, ull, ull>;
using IntervalsMap = std::map<std::string, std::vector<Interval>>;

std::vector<int> seeds{};
IntervalsMap intervalsMap{};

Interval StringToInterval(const std::string &aString)
{
    Interval interval = std::make_tuple(0, 0, 0);
    std::stringstream ss(aString);
    const auto &firstSpace = aString.find_first_of(' ');
    const auto &lastSpace = aString.find_last_of(' ');

    std::get<0>(interval) = std::stoull(aString.substr(0, firstSpace));
    std::get<1>(interval) = std::stoull(aString.substr(firstSpace + 1, lastSpace));
    std::get<2>(interval) = std::stoull(aString.substr(lastSpace + 1, std::string::npos));

    return interval;
}

void GetSeeds(std::string aString)
{
    auto lastSpace = aString.find_last_of(' ');
    while (lastSpace != std::string::npos)
    {
        seeds.push_back(std::stoull(aString.substr(lastSpace + 1, std::string::npos)));
        aString = aString.substr(0, lastSpace);
        lastSpace = aString.find_last_of(' ');
    }
    std::reverse(seeds.begin(), seeds.end());
}

int main()
{
    std::ifstream f("input.in");
    std::ofstream g("output.out");

    std::string seedsLine{};
    std::getline(f, seedsLine);
    GetSeeds(seedsLine);

    std::string currentInterval{};

    while (!f.eof())
    {
        std::string line{};
        std::getline(f, line);

        if (line.empty())
            continue;

        if (line.find("seed-to-soil map:") != std::string::npos)
        {
            currentInterval = "seed-to-soil map:";
            continue;
        }
        else if (line.find("soil-to-fertilizer map:") != std::string::npos)
        {
            currentInterval = "soil-to-fertilizer map:";
            continue;
        }
        else if (line.find("fertilizer-to-water map:") != std::string::npos)
        {
            currentInterval = "fertilizer-to-water map:";
            continue;
        }
        else if (line.find("water-to-light map:") != std::string::npos)
        {
            currentInterval = "water-to-light map:";
            continue;
        }
        else if (line.find("light-to-temperature map:") != std::string::npos)
        {
            currentInterval = "light-to-temperature map:";
            continue;
        }
        else if (line.find("temperature-to-humidity map:") != std::string::npos)
        {
            currentInterval = "temperature-to-humidity map:";
            continue;
        }
        else if (line.find("humidity-to-location map:") != std::string::npos)
        {
            currentInterval = "humidity-to-location map:";
            continue;
        }
        intervalsMap[currentInterval].push_back(StringToInterval(line));
    }

    std::vector<std::string> intervalsOrder{
        "seed-to-soil map:",         "soil-to-fertilizer map:",      "fertilizer-to-water map:", "water-to-light map:",
        "light-to-temperature map:", "temperature-to-humidity map:", "humidity-to-location map:"};

    ull minLocation = std::numeric_limits<ull>::max();

    for (const auto &seed : seeds)
    {
        ull nextToSearch = seed;

        for (const auto &interval : intervalsOrder)
        {
            auto currentInterval = intervalsMap[interval];
            auto temp = nextToSearch;
            for (const auto &[destinationStart, sourceStart, length] : currentInterval)
            {
                if (sourceStart <= temp && temp <= sourceStart + length - 1)
                    nextToSearch = nextToSearch + (destinationStart - sourceStart);
            }

            if (interval == "humidity-to-location map:")
                minLocation = std::min(minLocation, nextToSearch);
        }
    }

    g << minLocation;

    return 0;
}
