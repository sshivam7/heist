/**
* path_finding.h
* Description: Path finding logic implementation 
* @author Shivam Sood
* @version 1.0
*/

#ifndef PATHFINDING_H
#define PATHFINDING_H

#include <glad/glad.h>
#include <glm/glm.hpp>
#include <unordered_map>

#include "path_map.h"

typedef std::pair<double, Tile> PriorityElement;

void aStarPathFind(PathMap &pathMap, Tile start, Tile destination, std::vector<glm::vec2> &path);

double heuristic(Tile a, Tile b);

#endif