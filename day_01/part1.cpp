#include <fstream>
#include <string>
#include <vector>

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
			const auto & first = text.find_first_of(digit);
			const auto & last = text.find_last_of(digit);

			if (first < firstPos && first != std::string::npos)
				firstPos = first;

			if (last > lastPos && last != std::string::npos)
				lastPos = last;
		}
		
		sum += int(text[firstPos] - '0') * 10 + int(text[lastPos] - '0');
	}

	g << sum;

	return 0;
}
