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
	bool operator<(const Direction& rhs) const { return !(*this == rhs); }
};

Direction turnRight(Direction dir)
{
	return Direction(-dir.dj, dir.di);
}

Position operator+(Position p, Direction d)
{
	return Position(p.i + d.di, p.j + d.dj);
}

struct Pose
{
	Position pos;
	Direction dir;
	Pose(Position p, Direction d) : pos(p), dir(d) {}
	bool operator==(const Pose& rhs) const { return pos == rhs.pos && dir == rhs.dir; }
	bool operator!=(const Pose& rhs) const { return !(*this == rhs); }
	bool operator<(const Pose& rhs) const { return pos < rhs.pos || dir < rhs.dir; }
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
	bool isValid(Position p) const { return isValid(p.i, p.j); }
	char val(Position p) const { return val(p.i, p.j); }
	void setVal(Position p, char val) { setVal(p.i, p.j, val); }
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
			return Position(i,j);
	}
	return Position(std::string::npos, std::string::npos);
}

Position next(const Map& map, Position pos, Direction& dir)
{
	auto next = pos + dir;
	if (map.isValid(next) && map.val(next) == '#')
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
	map.setVal(p0, '.');

	// part 1
	Direction dir(0, -1); // start towards north
	std::set<Position> positions;
	for (Position p = p0; map.isValid(p); p = next(map, p, dir))
		positions.insert(p);
	std::cout << "The guard will visit " << positions.size() << " distinct positions" << std::endl;

	// part 2
	size_t obstructions = 0;
	for (auto pos : positions)
//	for (size_t j = 0; j < map.nj(); ++j)
//	for (size_t i = 0; i < map.ni(); ++i)
	{
//		Position pos(i, j);
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
