#include <algorithm>
#include <iostream>
#include <vector>

int main(int /*argc*/, char* /*argv*/[])
{
	// get location id values
	std::vector<int> v1;
	std::vector<int> v2;
	int x1 = 0;
	int x2 = 0;
	while (std::cin >> x1 >> x2)
	{
		v1.push_back(x1);
		v2.push_back(x2);
	}
	auto n = v1.size();
	std::cout << n << " x 2 location ids read\n";

	// sort the values
	std::sort(v1.begin(), v1.end());
	std::sort(v2.begin(), v2.end());

	// calculate distance
	int distance = 0;
	for (size_t i = 0; i < n; ++i)
		distance += std::abs(v2[i] - v1[i]);
	std::cout << "Total distance is " << distance << '\n';

	// calculate similarity
	long long similarity = 0;
	for (int x : v1)
		similarity += x * std::count(v2.cbegin(), v2.cend(), x);
	std::cout << "Similarity score is " << similarity << '\n';

	return 0;
}
