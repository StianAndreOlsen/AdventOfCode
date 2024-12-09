#include <cmath>
#include <iostream>
#include <sstream>
#include <string>
#include <vector>

class Calibration
{
	size_t res = 0;
	std::vector<size_t> vals;
	size_t evaluate(size_t operators, int opcount) const;
public:
	Calibration(std::istream& is);
	size_t result() const { return res; }
	bool validate(int opcount) const;
};

size_t Calibration::evaluate(size_t operators, int opcount) const
{
	size_t re = vals[0];
	size_t op = operators % opcount;
	operators -= op;
	for (size_t i = 1; i < vals.size(); ++i)
	{
		switch (op)
		{
		case 0: re += vals[i]; break;
		case 1: re *= vals[i]; break;
		case 2:
			re *= static_cast<size_t>(std::pow(10, 1 + std::floor(std::log10(vals[i]))));
			re += vals[i];
			break;
		}
		operators /= opcount;
		op = operators % opcount;
		operators -= op;
	}
	return re;
}

Calibration::Calibration(std::istream& is)
{
	char c = 0;
	if (is >> res >> c)
	{
		size_t v = 0;
		while (is >> v)
			vals.push_back(v);
	}
}

bool Calibration::validate(int opcount) const
{
	if (vals.empty())
		return false;
	if (vals.size() == 1)
		return res == vals[0];
	size_t n = static_cast<size_t>(std::pow(opcount, vals.size() - 1));
	for (size_t i = 0; i < n; ++i)
		if (res == evaluate(i, opcount))
			return true;
	return false;
}

int main(int /*argc*/, char* /*argv*/[])
{
	// get calibration results and validate them
	size_t sum2 = 0;
	size_t sum3 = 0;
	std::string line;
	while (std::getline(std::cin, line))
	{
		std::istringstream iss(line);
		Calibration cal(iss);
		if (cal.validate(2))
			sum2 += cal.result();
		if (cal.validate(3))
			sum3 += cal.result();
	}
	std::cout << "The sum of all valid calibration results using 2 operators are " << sum2 << std::endl;
	std::cout << "The sum of all valid calibration results using 3 operators are " << sum3 << std::endl;
	return 0;
}
