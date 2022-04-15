#include "enemy_object.h"

EnemyObject::EnemyObject() :
	PlayerObject() {
}

EnemyObject::EnemyObject(glm::vec2 pos, glm::vec2 size, float velocity, Texture sprite) :
PlayerObject(pos, size, velocity, sprite) {

}