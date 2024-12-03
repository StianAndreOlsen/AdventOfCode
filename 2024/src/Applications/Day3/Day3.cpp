#include <iostream>
#include <regex>
#include <sstream>

int mul(const std::string& mulstr)
{
	std::istringstream iss(mulstr.substr(4));
	int m = 0;
	int x = 0;
	int y = 0;
	char c = 0;
	if (iss >> x >> c >> y)
		m = x * y;
//	std::cout << mulstr << " = " << m << '\n';
	return m;
}

long long sumMul(std::string::const_iterator begin, std::string::const_iterator end)
{
	long long sum = 0;
	const std::regex mulRegex("mul\\([0-9]{1,3},[0-9]{1,3}\\)");
	auto mulBegin = std::sregex_iterator(begin, end, mulRegex);
	auto mulEnd = std::sregex_iterator();
	for (auto i = mulBegin; i != mulEnd; ++i)
	{
		std::smatch match = *i;
		sum += mul(match.str());
	}
	return sum;
}

int main(int /*argc*/, char* /*argv*/[])
{
	// get file content
	std::ostringstream oss;
	oss << std::cin.rdbuf();
	std::string file = oss.str();

	// part 1
	long long sum = sumMul(file.cbegin(), file.cend());
	std::cout << "The sum of all valid mul instructions are " << sum << '\n';

	// part 2
	sum = 0;
	size_t i0 = 0;
	size_t in = 0;
	do
	{
		in = file.find("don't()", i0);
		sum += sumMul(file.cbegin() + i0, file.cbegin() + in);
	}
	while ((i0 = file.find("do()", in)) != std::string::npos);
	std::cout << "The sum of all valid mul instructions marked with do() are " << sum << '\n';

	return 0;
}
