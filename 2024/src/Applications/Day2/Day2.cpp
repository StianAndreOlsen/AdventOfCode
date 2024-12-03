#include <Sao/Mathematics.h>
#include <cmath>
#include <iostream>
#include <sstream>
#include <vector>

bool isReportSafe(const std::vector<int>& report)
{
	size_t n = report.size();
	if (n < 1)
		return false; // the task is unclear about this
	int prev = report[0];
	int prevDiff = 0;
	for (size_t i = 1; i < n; ++i)
	{
		int curr = report[i];
		int currDiff = curr - prev;
		if (currDiff == 0 || std::abs(currDiff) > 3 ||
			(prevDiff != 0 && Sao::sgn(currDiff) != Sao::sgn(prevDiff)))
			return false;
		prev = curr;
		prevDiff = currDiff;
	}
	return true;
}

std::vector<int> problemDampedReport(const std::vector<int>& report, size_t ierase)
{
	std::vector<int> pdreport(report);
	pdreport.erase(pdreport.cbegin()+ierase);
	return pdreport;
}

bool isProblemDampedReportSafe(const std::vector<int>& report)
{
	if (isReportSafe(report))
		return true;
	for (size_t i = 0; i < report.size(); ++i)
		if (isReportSafe(problemDampedReport(report, i)))
			return true;
	return false;
}

int main(int /*argc*/, char* /*argv*/[])
{
	// count safe and unsafe reports
	int safeReports = 0;
	int unsafeReports = 0;
	int safeProblemDampedReports = 0;
	int unsafeProblemDampedReports = 0;
	std::string line;
	while (std::getline(std::cin, line))
	{
		// get report levels
		std::vector<int> report;
		std::istringstream iss(line);
		int level = 0;
		while (iss >> level)
			report.push_back(level);

		// count safe and unsafe reports
		if (isReportSafe(report))
			++safeReports;
		else
			++unsafeReports;

		// count safe and unsafe problem damped reports
		if (isProblemDampedReportSafe(report))
			++safeProblemDampedReports;
		else
			++unsafeProblemDampedReports;
	}

	// print results
	std::cout << "There are " << safeReports << " safe reports and " << unsafeReports << " unsafe reports\n";
	std::cout << "There are " << safeProblemDampedReports << " safe problem damped reports and " << unsafeProblemDampedReports << " unsafe problem damped reports\n";
	return 0;
}
