#include <iostream>
#include <set>
#include <string>
#include <vector>

struct Position
{
	size_t i = 0;
	size_t j = 0;
	Position(size_t x, size_t y) : i(x), j(y) {}
	bool operator==(const Position& rhs) const { return i == rhs.i && j == rhs.j; }
	bool operator!=(const Position& rhs) const { return !(*this == rhs); }
	bool operator<(const Position& rhs) const { return j < rhs.j || (j == rhs.j && i < rhs.i); }
};

struct Direction
{
	int di = 0;
	int dj = 0;
	Direction(int dx, int dy) : di(dx), dj(dy) {}
	bool operator==(const Direction& rhs) const { return di == rhs.di && dj == rhs.dj; }
	bool operator!=(const Direction& rhs) const { return !(*this == rhs); }
	bool operator<(const Direction& rhs) const { return dj < rhs.dj || (dj == rhs.dj && di < rhs.di); }
};

Direction turnRight(const Direction& dir)
{
	return Direction(-dir.dj, dir.di);
}

Position operator+(const Position& pos, const Direction& dir)
{
	return Position(pos.i + dir.di, pos.j + dir.dj);
}

struct Pose
{
	Position p;
	Direction d;
	Pose(const Position& pos, const Direction& dir) : p(pos), d(dir) {}
	bool operator==(const Pose& rhs) const { return p == rhs.p && d == rhs.d; }
	bool operator!=(const Pose& rhs) const { return !(*this == rhs); }
	bool operator<(const Pose& rhs) const { return p < rhs.p || (p == rhs.p && d < rhs.d); }
};

class Map
{
	size_t ncols = 0;
	std::vector<std::string> rows;
public:
	Map(const std::vector<std::string>& lines);
	size_t ni() const { return ncols; }
	size_t nj() const { return rows.size(); }
	bool isValid(size_t i, size_t j) const { return i < ni() && j < nj(); }
	char val(size_t i, size_t j) const { return rows[j][i]; }
	void setVal(size_t i, size_t j, char val) { rows[j][i] = val; }
	bool isValid(const Position& pos) const { return isValid(pos.i, pos.j); }
	char val(const Position& pos) const { return val(pos.i, pos.j); }
	void setVal(const Position& pos, char val) { setVal(pos.i, pos.j, val); }
	Position find(char val) const;
};

Map::Map(const std::vector<std::string>& lines)
	: rows(lines)
{
	// get column count
	for (const auto& row : rows)
		ncols = std::max(ncols, row.size());

	// make sure all rows have the same number of columns
	for (auto& row : rows)
		row.resize(ncols);
}

Position Map::find(char val) const
{
	for (size_t j = 0; j < nj(); ++j)
	{
		auto i = rows[j].find(val);
		if (i != std::string::npos)
			return Position(i, j);
	}
	return Position(std::string::npos, std::string::npos);
}

Position next(const Map& map, const Position& pos, Direction& dir)
{
	auto next = pos + dir;
	while (map.isValid(next) && map.val(next) == '#')
	{
		dir = turnRight(dir);
		next = pos + dir;
	}
	return next;
}

int main(int /*argc*/, char* /*argv*/[])
{
	// get input
	std::vector<std::string> lines;
	std::string line;
	while (std::getline(std::cin, line))
		lines.push_back(line);
	Map map(lines);

	// find start position and flag as a position without any obstructions
	Position p0 = map.find('^');
	if (!map.isValid(p0))
	{
		std::cout << "No start position found" << std::endl;
		return 0;
	}
	map.setVal(p0, '.');

	// part 1
	Direction dir(0, -1); // start towards north
	std::set<Position> positions;
	for (Position p = p0; map.isValid(p); p = next(map, p, dir))
		positions.insert(p);
	std::cout << "The guard will visit " << positions.size() << " distinct positions" << std::endl;

	// part 2
	size_t obstructions = 0;
	for (const auto& pos : positions)
	{
		if (pos != p0 && map.val(pos) == '.')
		{
			map.setVal(pos, '#');
			dir = Direction(0, -1); // start towards north
			std::set<Pose> poses;
			for (Position p = p0; map.isValid(p); p = next(map, p, dir))
			{
				Pose pose(p, dir);
				if (poses.count(pose) > 0)
				{
					++obstructions;
					break;
				}
				poses.insert(pose);
			}
			map.setVal(pos, '.');
		}
	}
	std::cout << "The obstruction can be placed in " << obstructions << " different positions" << std::endl;

	return 0;
}
