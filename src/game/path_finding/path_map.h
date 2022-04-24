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

class Tile {
public:
	Tile();
	Tile(glm::vec2 pos, unsigned int mRow, unsigned int mCol, bool isValidLoc);

	bool isValidLoc();
	glm::vec2 getPos();

	void setCameFrom(glm::vec2 cameFrom);
	glm::vec2 getCameFrom();

	void markVisited(bool visited);
	bool checkVisited();

private:
	glm::vec2 m_pos;
	unsigned int m_row, m_col;
	bool m_isValidLoc;
	bool m_visited;
	glm::vec2 m_cameFrom;

	friend class PathMap;
};

class PathMap {
public:
	PathMap();
	PathMap(std::vector<Tile> pathGrid, unsigned int rowSize, unsigned int colSize);

	std::vector<Tile> getNeighbours(Tile tile);

	Tile getByArrLoc(unsigned int row, unsigned int col);
	void setByArrLoc(unsigned int row, unsigned int col, Tile tile);
	
	std::vector<Tile> getTiles();

private:
	std::vector<Tile> m_pathGrid;
	unsigned int m_rowSize, m_colSize;
	static inline const std::vector<std::pair<int, int>> dirs = { {0,1},{1,0},{0,-1},{-1,0} };

	bool inRange(int row, int col);
};

#endif


