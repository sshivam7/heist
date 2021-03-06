/**
* path_map.h
* Description: Tile Map logic required for path finding
* @author Shivam Sood
* @version 1.0
*/

#ifndef PATHMAP_H
#define PATHMAP_H

#include <glad/glad.h>
#include <glm/glm.hpp>
#include <vector>

// Tile class used to store data for path finding
class Tile {
public:
	Tile();
	Tile(glm::vec2 pos, unsigned int mRow, unsigned int mCol, bool isValidLoc);

	bool isValidLoc();
	glm::vec2 getPos();

	bool operator<(const Tile& rhs) const noexcept;

private:
	glm::vec2 m_pos;
	unsigned int m_row, m_col;
	bool m_isValidLoc;

	friend class PathMap;
};

// Grid class used in path finding algorithm(s)
class PathMap {
public:
	// Constructors
	PathMap();
	PathMap(std::vector<Tile> pathGrid, unsigned int rowSize, unsigned int colSize);

	// Get all tile neighbours
	void getNeighbours(Tile tile, std::vector<Tile> &neighbours);

	// Methods to access array by row and column
	Tile getByArrLoc(unsigned int row, unsigned int col);
	void setByArrLoc(unsigned int row, unsigned int col, Tile tile);
	
	// Getter methods
	std::vector<Tile> getTiles();
	unsigned int getRowSize();
	unsigned int getColSize();

private:
	std::vector<Tile> m_pathGrid;
	unsigned int m_rowSize, m_colSize;

	static inline const std::vector<std::pair<int, int>> dirs = { {0,1},{1,0},{0,-1},{-1,0} };
	bool inRange(int row, int col);
};

#endif


