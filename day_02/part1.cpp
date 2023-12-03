#include <fstream>
#include <string>
#include <vector>

constexpr unsigned int max_red = 12;
constexpr unsigned int max_green = 13;
constexpr unsigned int max_blue = 14;

using CubsTuple = std::tuple<int, int, int>; // red green blue

CubsTuple GetEachCube(std::string aSubSet)
{
	CubsTuple cubs = std::make_tuple(0, 0, 0);

	auto commaPos = aSubSet.find(',');
	while (commaPos != std::string::npos)
	{
		std::string cubeText = aSubSet.substr(0, commaPos);
		std::string cubsNo = cubeText.substr(0, cubeText.find(' '));

		if (cubeText.find("red") != std::string::npos)
			std::get<0>(cubs) = std::stoi(cubsNo);
		else if (cubeText.find("green") != std::string::npos)
			std::get<1>(cubs) = std::stoi(cubsNo);
		else if (cubeText.find("blue") != std::string::npos)
			std::get<2>(cubs) = std::stoi(cubsNo);

		aSubSet = aSubSet.substr(commaPos + 2, std::string::npos);
		commaPos = aSubSet.find(',');
	}

	std::string cubsNo = aSubSet.substr(0, aSubSet.find(' '));

	if (aSubSet.find("red") != std::string::npos)
		std::get<0>(cubs) = std::stoi(cubsNo);
	else if (aSubSet.find("green") != std::string::npos)
		std::get<1>(cubs) = std::stoi(cubsNo);
	else if (aSubSet.find("blue") != std::string::npos)
		std::get<2>(cubs) = std::stoi(cubsNo);

	return cubs;
}


int main()
{
	std::ifstream f("input.in");
	std::ofstream g("output.out");

	int gameId = 0, sum = 0;
	bool isValid;

	while (!f.eof())
	{
		gameId++;
		isValid = true;

		std::string set{};
		std::getline(f,set);

		set = set.substr(set.find(':') + 2 , std::string::npos);
		auto semicolonPos = set.find(';');
		while (semicolonPos != std::string::npos)
		{
			auto subSet = set.substr(0, semicolonPos);
			set = set.substr(semicolonPos + 2, std::string::npos);
			semicolonPos = set.find(';');

			const auto & [red,green,blue] = GetEachCube(subSet);
			if (!(red <= max_red && green <= max_green && blue <= max_blue))
				isValid = false;
		}

		const auto& [red, green, blue] = GetEachCube(set);
		if (!(red <= max_red && green <= max_green && blue <= max_blue))
			isValid = false;

		if (isValid)
			sum += gameId;
	}

	g << sum;

	return 0;
}
