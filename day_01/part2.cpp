#include <fstream>
#include <string>
#include <vector>
#include <map>
#include <optional>
#include <ranges>

using OptionalInt = std::optional<int>;
using OptionalIntPair = std::pair<OptionalInt, OptionalInt>;

std::map<std::string, int> stringToDigit =
{
	{"one",1},
	{"two",2},
	{"three",3},
	{"four",4},
	{"five",5},
	{"six",6},
	{"seven",7},
	{"eight",8},
	{"nine",9},
};

OptionalIntPair GetFirstAndLastWordNumber(const std::string& aString)
{
	OptionalIntPair res{ std::nullopt, std::nullopt };

	//find first word occurence
	std::string stringNumber{};
	for (const auto & character : aString)
	{
		if (std::isdigit(character))
			break;

		stringNumber += character;
		for (const auto& [word,number] : stringToDigit)
		{
			const auto& found = stringNumber.find(word);
			if (found != std::string::npos && !res.first.has_value())
				res.first = number;
		}
	}

	//find last word occurence
	stringNumber.clear();
	std::ranges::reverse_view reverseStringView{ aString };
	for (const auto & character : reverseStringView)
	{
		if (std::isdigit(character))
			break;

		stringNumber.insert(stringNumber.begin(), character);
		for (const auto& [word,number] : stringToDigit)
		{
			const auto& found = stringNumber.find(word);
			if (found != std::string::npos && !res.second.has_value())
				res.second = number;
		}
	}

	return res;
}


int main()
{

	std::ifstream f("input.in");
	std::ofstream g("output.out");

	int sum = 0;
	std::string text{};
	std::string digits = "0123456789";

	while (!f.eof())
	{
		f >> text;

		auto firstPos = text.length();
		auto lastPos = 0;

		for (const auto& digit : digits)
		{
			const auto& first = text.find_first_of(digit);
			const auto& last = text.find_last_of(digit);

			if (first < firstPos && first != std::string::npos)
				firstPos = first;

			if (last > lastPos && last != std::string::npos)
				lastPos = last;
		}

		const auto & firstAndLast = GetFirstAndLastWordNumber(text);
		int firstNo = firstAndLast.first.value_or(int(text[firstPos] - '0'));
		int lastNo = firstAndLast.second.value_or(int(text[lastPos] - '0'));

		sum += firstNo * 10 + lastNo;
	}

	g << sum;

	return 0;
}
