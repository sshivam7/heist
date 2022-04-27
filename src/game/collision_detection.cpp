#include "collision_detection.h"

// AABB Collision detection (rectangular)
bool rectCollision(GameObject& one, GameObject& two) {
	bool xCollision = one.getPos().x + one.getSize().x >= two.getPos().x &&
		two.getPos().x + two.getSize().x >= one.getPos().x;

	bool yCollision = one.getPos().y + one.getSize().y >= two.getPos().y &&
		two.getPos().y + two.getSize().y >= one.getPos().y;

	return xCollision && yCollision;
}

// AABB Collisions (circle collision detection)
CollisionInfo checkCollision(glm::vec2 pos, float radius, GameObject& two) {
	// Get circle center
	glm::vec2 center(pos + radius);

	// Calculate AABB center & half-extents
	glm::vec2 halfExtents(two.getSize().x / 2.0f, two.getSize().y / 2.0f);
	glm::vec2 boxCenter(two.getPos().x + halfExtents.x, two.getPos().y + halfExtents.y);

	// get difference vector between centers
	glm::vec2 difference = center - boxCenter;
	glm::vec2 clamped = glm::clamp(difference, -halfExtents, halfExtents);
	glm::vec2 closest = boxCenter + clamped;

	// Vector between circle center and closest point on box
	difference = closest - center;

	if (glm::length(difference) <= radius) {
		return std::make_tuple(true, getCollisionDirection(difference));
	}
	else {
		return std::make_tuple(false, UP);
	}
}

// Get direction of collision
Direction getCollisionDirection(glm::vec2 target) {
	glm::vec2 compass[] = {
		glm::vec2(0.0f, -1.0f), // DOWN
		glm::vec2(0.0f, 1.0f),  // UP
		glm::vec2(-1.0f, 0.0f), // LEFT
		glm::vec2(1.0f, 0.0f)   // RIGHT
	};

	float max = 0.0f;
	unsigned int bestMatch = -1;
	for (unsigned int i = 0; i < 4; ++i) {
		float dotProd = glm::dot(glm::normalize(target), compass[i]);
		if (dotProd > max) {
			max = dotProd;
			bestMatch = i;
		}
	}

	return (Direction)bestMatch;
}