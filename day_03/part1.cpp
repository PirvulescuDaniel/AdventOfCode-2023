#include <algorithm>
#include <cmath>
#include <fstream>
#include <iostream>
#include <sstream>
#include <string>
#include <vector>

std::vector<int> GetNumbersAsVector(std::string aString)
{
    std::vector<int> res{};
    std::stringstream stream(aString);
    while (!stream.eof())
    {
        std::string number{};
        stream >> number;

        if (number.empty())
            return res;

        res.push_back(std::stoi(number));
    }
}

int main()
{
    // First, replace all double spaces with single space using a text editor.
    std::ifstream f("input.in");
    std::ofstream g("output.out");

    int cardNo = 0, points = 0;

    while (!f.eof())
    {
        std::string row{};
        std::getline(f, row);

        cardNo++;

        const auto &sep1 = row.find(':');
        const auto &sep2 = row.find('|');

        const auto &winningListPlane = row.substr(sep1 + 2, sep2 - sep1 - 2);
        const auto &myListPlane = row.substr(sep2 + 2, std::string::npos);

        auto winningListVector = GetNumbersAsVector(winningListPlane);
        auto myListVector = GetNumbersAsVector(myListPlane);

        std::sort(winningListVector.begin(), winningListVector.end());
        std::sort(myListVector.begin(), myListVector.end());

        std::vector<int> intersection{};

        std::set_intersection(winningListVector.begin(), winningListVector.end(), myListVector.begin(),
                              myListVector.end(), std::back_inserter(intersection));

        if (!intersection.empty())
            points += pow(2, intersection.size() - 1);
    }

    g << points;

    return 0;
}
