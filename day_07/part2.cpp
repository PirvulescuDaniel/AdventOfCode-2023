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

enum HandType
{
    HIGH_CARD,
    ONE_PAIR,
    TWO_PAIR,
    THREE_OF_A_KIND,
    FULL_HOUSE,
    FOUR_OF_A_KIND,
    FIVE_OF_A_KIND
};

struct Hand
{
    std::string mHand;
    HandType mType;
    int bid;
};

std::vector<Hand> hands{};

HandType GetHandType(const std::string &aHand)
{
    std::map<char, int> cardFreqMap{};
    cardFreqMap['2'] = 0;
    cardFreqMap['3'] = 0;
    cardFreqMap['4'] = 0;
    cardFreqMap['5'] = 0;
    cardFreqMap['6'] = 0;
    cardFreqMap['7'] = 0;
    cardFreqMap['8'] = 0;
    cardFreqMap['9'] = 0;
    cardFreqMap['T'] = 0;
    cardFreqMap['J'] = 0;
    cardFreqMap['Q'] = 0;
    cardFreqMap['K'] = 0;
    cardFreqMap['A'] = 0;

    for (const auto &card : aHand)
        cardFreqMap[card]++;

    std::vector<int> cardFreq{};
    for (const auto &card : cardFreqMap)
        cardFreq.push_back(card.second);

    std::sort(cardFreq.begin(), cardFreq.end(), std::greater<int>());

    const auto &jCards = cardFreqMap['J'];

    if (cardFreq[0] == 5)
        return FIVE_OF_A_KIND;
    if (cardFreq[0] == 4)
    {
        if (jCards == 1 || jCards == 4)
            return FIVE_OF_A_KIND;

        return FOUR_OF_A_KIND;
    }
    if (cardFreq[0] == 3 && cardFreq[1] == 2)
    {
        if (jCards == 3 || jCards == 2)
            return FIVE_OF_A_KIND;

        return FULL_HOUSE;
    }
    if (cardFreq[0] == 3 && cardFreq[1] == 1 && cardFreq[2] == 1)
    {
        if (jCards == 3)
            return FOUR_OF_A_KIND;

        if (jCards == 1)
            return FOUR_OF_A_KIND;

        return THREE_OF_A_KIND;
    }
    if (cardFreq[0] == 2 && cardFreq[1] == 2)
    {
        if (jCards == 2)
            return FOUR_OF_A_KIND;

        if (jCards == 1)
            return FULL_HOUSE;

        return TWO_PAIR;
    }
    if (cardFreq[0] == 2 && cardFreq[1] == 1 && cardFreq[2] == 1 && cardFreq[3] == 1)
    {
        if (jCards == 2)
            return THREE_OF_A_KIND;

        if (jCards == 1)
            return THREE_OF_A_KIND;

        return ONE_PAIR;
    }

    // all different
    if (jCards == 0)
        return HIGH_CARD;
    if (jCards == 1)
        return ONE_PAIR;
}

bool CompareTwoHands(const Hand &aHand1, const Hand &aHand2)
{
    if (aHand1.mType != aHand2.mType)
        return aHand1.mType < aHand2.mType;

    std::map<char, int> charToRank = {
        {'A', 14}, {'K', 13}, {'Q', 12}, {'J', 1}, {'T', 10}, {'9', 9}, {'8', 8},
        {'7', 7},  {'6', 6},  {'5', 5},  {'4', 4}, {'3', 3},  {'2', 2},
    };

    for (int i = 0; i < aHand1.mHand.size(); i++)
    {
        if (aHand1.mHand[i] != aHand2.mHand[i])
            return charToRank[aHand1.mHand[i]] < charToRank[aHand2.mHand[i]];
    }
}

int main()
{
    std::ifstream f("input.in");
    std::ofstream g("output.out");

    while (!f.eof())
    {
        std::string line{};
        std::getline(f, line);

        const auto &spacePos = line.find_first_of(' ');

        const auto &planeHand = line.substr(0, spacePos);
        const auto &bid = std::stoi(line.substr(spacePos + 1, std::string::npos));
        const auto &type = GetHandType(planeHand);

        Hand hand;
        hand.mHand = planeHand;
        hand.bid = bid;
        hand.mType = type;

        hands.push_back(hand);
    }

    std::sort(hands.begin(), hands.end(), CompareTwoHands);

    unsigned long long sum = 0;
    for (int i = 0; i < hands.size(); i++)
        sum += (i + 1) * hands[i].bid;

    g << sum;

    return 0;
}
