/**
* level_grid.h
* Description: Level grid to perform spatial partitioning 
* @author Shivam Sood
* @version 1.0
*/

#ifndef LEVELGRID_H
#define LEVELGRID_H

#include <glad/glad.h>
#include <glm/glm.hpp>
#include <vector>

template <typename T>
class LevelGrid {
public:
	LevelGrid(unsigned int gridSize, unsigned int width, unsigned int height);

	void addObject(T obj, glm::vec2 pos);
	void clear();
	std::vector<T> getGrid(glm::vec2 pos);
	std::vector<std::vector<T>> getGridSet(glm::vec2 pos);
	int getGridBlock(glm::vec2 pos);

	std::vector<std::vector<T>> getGridObjects();

private:
	unsigned int m_gridSize;
	unsigned int m_width, m_height;

	std::vector<std::vector<T>> m_gridObject;
};

template <typename T>
LevelGrid<T>::LevelGrid(unsigned int gridSize, unsigned int width, unsigned int height) :
	m_gridSize(gridSize), m_width(width), m_height(height) {
	for (int i = 0; i < std::pow(m_gridSize, 2); ++i) {
		std::vector<T> grid;
		m_gridObject.push_back(grid);
	}
}

template <typename T>
void LevelGrid<T>::addObject(T obj, glm::vec2 pos) {
	m_gridObject[this->getGridBlock(pos)].push_back(obj);
}

template <typename T>
void LevelGrid<T>::clear() {
	for (int i = 0; i < m_gridObject.size(); ++i) {
		m_gridObject[i].clear();
	}
}

template <typename T>
std::vector<std::vector<T>> LevelGrid<T>::getGridObjects() {
	return this->m_gridObject;
}

template <typename T>
std::vector<T> LevelGrid<T>::getGrid(glm::vec2 pos) {
	return m_gridObject[this->getGridBlock(pos)];
}

template <typename T>
std::vector<std::vector<T>> LevelGrid<T>::getGridSet(glm::vec2 pos) {
	std::vector<std::vector<T>> gridSet;
	int locations[4] = { 1, -1, m_gridSize * -1, m_gridSize };

	int currentGridBlock = getGridBlock(pos);
	gridSet.push_back(m_gridObject[currentGridBlock]);

	for (int& loc : locations) {
		int newGrid = loc + currentGridBlock;
		if (newGrid >= 0 && newGrid < std::pow(m_gridSize, 2)) {
			gridSet.push_back(m_gridObject[newGrid]);
		}
	}

	return gridSet;
}

template <typename T>
int LevelGrid<T>::getGridBlock(glm::vec2 pos) {
	for (int x = 1; x <= m_gridSize; ++x) {
		for (int y = 1; y <= m_gridSize; ++y) {
			if ((pos.x <= (x * m_width) / m_gridSize) && (pos.y <= (y * m_height) / m_gridSize)) {
				return x * m_gridSize + y - m_gridSize - 1;
			}
		}
	}

	return -1;
}

#endif