#include "path_finding.h"

#include <vector>
#include <queue>
#include <iostream>

namespace std {
	/* hash function for glm::vec2 */
	template <> struct hash<glm::vec2> {
		std::size_t operator()(const glm::vec2& id) const noexcept {
			return std::hash<int>()((int)id.x ^ ((int)id.y << 16));
		}
	};
}

// Implement A* path finding algorithm (All graph tiles are given equal weight)
void aStarPathFind(PathMap& pathMap, Tile start, Tile destination, std::vector<glm::vec2>& path) {
	std::priority_queue<PriorityElement, std::vector<PriorityElement>, std::greater<PriorityElement>> frontier;
	std::vector<Tile> neighbours;
	frontier.emplace(0, start);

	std::unordered_map<glm::vec2, glm::vec2> cameFrom;
	cameFrom[start.getPos()] = start.getPos();

	while(!frontier.empty()) {
		Tile current = frontier.top().second;
		frontier.pop();

		if (current.getPos() == destination.getPos()) {
			break;
		}

		// Append valid neighbours to priority queue
		pathMap.getNeighbours(current, neighbours);
		for (Tile next : neighbours) {
			if (cameFrom.find(next.getPos()) == cameFrom.end()) {
				frontier.emplace(heuristic(next, destination), next);
				cameFrom[next.getPos()] = current.getPos();
			}
		}
	}

	// Get path to destination
	path.clear();
	glm::vec2 currentPos = destination.getPos();

	while (currentPos != start.getPos()) {
		path.push_back(currentPos);
		currentPos = cameFrom[currentPos];
	}

	// Reverse path (to point enemy to player)
	std::reverse(path.begin(), path.end());
}

double heuristic(Tile a, Tile b) {
	return std::abs(a.getPos().x - b.getPos().x) + std::abs(a.getPos().y - b.getPos().y);
}
