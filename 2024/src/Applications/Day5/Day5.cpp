#include <iostream>
#include <sstream>
#include <string>
#include <vector>

class Rules : public std::vector< std::pair<int,int> >
{
public:
	Rules(const std::vector<std::string>& rules);
};

Rules::Rules(const std::vector<std::string>& rules)
{
	for (const auto& rule : rules)
	{
		std::istringstream iss(rule);
		int page1 = 0;
		int page2 = 0;
		char c = 0;
		if (iss >> page1 >> c >> page2)
			push_back(std::make_pair(page1, page2));
	}
}

class Update : public std::vector<int>
{
public:
	Update(const std::string& update);
	bool isOrdered(const Rules& rules, size_t* pi = nullptr, size_t* pj = nullptr) const;
	void order(const Rules& rules);
	int middlePage() const;
};

Update::Update(const std::string& update)
{
	std::istringstream iss(update);
	int page = 0;
	while (iss >> page)
	{
		push_back(page);
		char c = 0;
		if (!(iss >> c))
			break;
	}
}

bool Update::isOrdered(const Rules& rules, size_t* pi, size_t* pj) const
{
	for (size_t i = 0; i < size()-1; ++i)
	for (size_t j = i+1; j < size(); ++j)
	{
		for (const auto& rule : rules)
		{
			if (at(i) == rule.second && at(j) == rule.first)
			{
				if (pi) *pi = i;
				if (pj) *pj = j;
				return false;
			}
		}
	}
	return true;
}

void Update::order(const Rules& rules)
{
	size_t i = 0;
	size_t j = 0;
	while (!isOrdered(rules, &i, &j))
		std::swap(at(i), at(j));
}

int Update::middlePage() const
{
	if (empty())
		return 0;
	return at(size() / 2);
}

int main(int /*argc*/, char* /*argv*/[])
{
	// get input
	std::vector<std::string> ruleStrings;
	std::vector<std::string> updateStrings;
	std::string line;
	while (std::getline(std::cin, line))
	{
		if (line.empty())
			break;
		ruleStrings.push_back(line);
	}
	while (std::getline(std::cin, line))
		updateStrings.push_back(line);

	// check updates
	int sumOrdered = 0;
	int sumUnordered = 0;
	Rules rules(ruleStrings);
	for (const auto& updateString : updateStrings)
	{
		Update update(updateString);
		if (update.isOrdered(rules))
			sumOrdered += update.middlePage();
		else
		{
			update.order(rules);
			sumUnordered += update.middlePage();
		}
	}
	std::cout << "The sum of middle pages from ordered updates is " << sumOrdered << std::endl;
	std::cout << "The sum of middle pages from unordered updates is " << sumUnordered << std::endl;

	return 0;
}
