#include <iostream>
#include <string>
#include <vector>

size_t countForward(const std::string& str, const std::string& substr)
{
	size_t n = 0;
	for (auto p = str.find(substr); p != std::string::npos; p = str.find(substr, p+1))
		++n;
	return n;
}

size_t countBackward(const std::string& str, const std::string& substr)
{
	auto rsubstr(substr);
	std::reverse(rsubstr.begin(), rsubstr.end());
	return countForward(str, rsubstr);
}

size_t count(const std::string& str, const std::string& substr)
{
	return countForward(str, substr) + countBackward(str, substr);
}

class CharMatrix
{
	size_t ni = 0;
	std::vector<std::string> rows;
public:
	CharMatrix(const std::vector<std::string>& lines);
	size_t rowCount() const { return rows.size(); }
	size_t colCount() const { return ni; }
	char val(size_t i, size_t j) const { return rows[j][i]; }
	std::string row(size_t j) const { return rows.at(j); }
	std::string col(size_t i) const;
	std::string diag(size_t i0, size_t j0, size_t di, size_t dj) const;
	size_t countHorizontal(const std::string& substr) const;
	size_t countVertical(const std::string& substr) const;
	size_t countMajorDiagonal(const std::string& substr) const;
	size_t countMinorDiagonal(const std::string& substr) const;
	size_t countAll(const std::string& substr) const;
	size_t countCrossMAS() const;
};

CharMatrix::CharMatrix(const std::vector<std::string>& lines)
	: rows(lines)
{
	// get column count
	for (const auto& row : rows)
		ni = std::max(ni, row.size());

	// make sure all rows have the same number of columns
	for (auto& row : rows)
		row.resize(ni);
}

std::string CharMatrix::col(size_t i) const
{
	std::string col;
	col.resize(rowCount());
	for (size_t j = 0; j < rowCount(); ++j)
		col[j] = val(i,j);
	return col;
}

std::string CharMatrix::diag(size_t i0, size_t j0, size_t di, size_t dj) const
{
	std::string diag;
	auto ni = colCount();
	auto nj = rowCount();
	auto i = i0;
	auto j = j0;
	for (; i < ni && j < nj; i += di, j += dj)
		diag.push_back(val(i,j));
	return diag;
}

size_t CharMatrix::countHorizontal(const std::string& substr) const
{
	size_t n = 0;
	for (const auto& row : rows)
		n += count(row, substr);
	return n;
}

size_t CharMatrix::countVertical(const std::string& substr) const
{
	size_t n = 0;
	for (size_t i = 0; i < colCount(); ++i)
		n += count(col(i), substr);
	return n;
}

size_t CharMatrix::countMajorDiagonal(const std::string& substr) const
{
	size_t n = 0;
	auto ni = colCount();
	auto nj = rowCount();
	size_t i = 0;
	size_t j = nj-1;
	for (; j > 0; --j)
		n += count(diag(i, j, 1, 1), substr);
	for (; i < ni; ++i)
		n += count(diag(i, j, 1, 1), substr);
	return n;
}

size_t CharMatrix::countMinorDiagonal(const std::string& substr) const
{
	size_t n = 0;
	auto ni = colCount();
	auto nj = rowCount();
	size_t i = 0;
	size_t j = 0;
	for (; j < nj-1; ++j)
		n += count(diag(i, j, 1, -1), substr);
	for (; i < ni; ++i)
		n += count(diag(i, j, 1, -1), substr);
	return n;
}

size_t CharMatrix::countAll(const std::string& substr) const
{
	return
		countHorizontal(substr) +
		countVertical(substr) +
		countMajorDiagonal(substr) +
		countMinorDiagonal(substr)
	;
}

size_t CharMatrix::countCrossMAS() const
{
	size_t n = 0;
	auto ni = colCount();
	auto nj = rowCount();
	for (size_t i = 1; i < ni-1; ++i)
	for (size_t j = 1; j < nj-1; ++j)
	{
		if (val(i,j) == 'A' &&
			((val(i-1,j-1) == 'M' && val(i+1,j+1) == 'S') ||
			 (val(i-1,j-1) == 'S' && val(i+1,j+1) == 'M')) &&
			((val(i+1,j-1) == 'M' && val(i-1,j+1) == 'S') ||
			 (val(i+1,j-1) == 'S' && val(i-1,j+1) == 'M')))
			++n;
	}
	return n;
}

int main(int /*argc*/, char* /*argv*/[])
{
	// get file content
	std::vector<std::string> lines;
	std::string line;
	while (std::getline(std::cin, line))
		lines.push_back(line);
	CharMatrix matrix(lines);

	// part 1
	std::string substr("XMAS");
	std::cout << substr << " is found " << matrix.countAll(substr) << " times\n";

	// part 2
	std::cout << "X-MAS is found " << matrix.countCrossMAS() << " times\n";

	return 0;
}
