#include "path_map.h"
#include <iostream>

// Tile Initialization ------------------------------------------------------------------
Tile::Tile() : m_pos(NULL), m_row(0), m_col(0), m_isValidLoc(false), m_cameFrom(glm::vec2(0)) {}

Tile::Tile(glm::vec2 pos, unsigned int mRow, unsigned int mCol, bool isValidLoc) :
	m_pos(pos), m_row(mRow), m_col(mCol), m_isValidLoc(isValidLoc), m_cameFrom(glm::vec2(0)) {

}

bool Tile::isValidLoc() {
	return this->m_isValidLoc;
}

glm::vec2 Tile::getPos() {
	return this->m_pos;
}

void Tile::setCameFrom(glm::vec2 cameFrom) {
	this->m_cameFrom = cameFrom;
}

glm::vec2 Tile::getCameFrom() {
	return this->m_cameFrom;
}

// PathMap Initialization ----------------------------------------------------------------
PathMap::PathMap() : m_pathGrid(NULL), m_rowSize(0), m_colSize(0) {}

PathMap::PathMap(std::vector<Tile> pathGrid, unsigned int rowSize, unsigned int colSize) :
	m_pathGrid(pathGrid), m_rowSize(rowSize), m_colSize(colSize) {

}

// Get all valid neighbouring tiles
std::vector<Tile> PathMap::getNeighbours(Tile tile) {
	std::vector<Tile> neighbours;

	// Check surrounding directions
	for (std::pair<int, int> dir : dirs) {
		int newRow = tile.m_col + dir.first;
		int newCol = tile.m_row + dir.second;

		// if valid direction add to list to return
		if (inRange(newRow, newCol) && getByArrLoc(newRow, newCol).isValidLoc()) {
			neighbours.push_back(getByArrLoc(newRow, newCol));
		}
	}

	// Make sure we consider different direction orders
	if ((tile.m_row + tile.m_col) % 2 == 0) {
		std::reverse(neighbours.begin(), neighbours.end());
	}

	return neighbours;
}

// Check if row col values fall within a valid range
bool PathMap::inRange(int row, int col) {
	return 0 <= (this->m_colSize * row + col) && (this->m_colSize * row + col) <= m_rowSize * m_colSize;
}

// Helper methods to access std::vector based on row & col
Tile PathMap::getByArrLoc(unsigned int row, unsigned int col) {
	return m_pathGrid[this->m_colSize * row + col];
}

void PathMap::setByArrLoc(unsigned int row, unsigned int col, Tile tile) {
	this->m_pathGrid[this->m_colSize * row + col] = tile;
}

std::vector<Tile> PathMap::getTiles() {
	return this->m_pathGrid;
}