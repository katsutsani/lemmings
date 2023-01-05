#include "Entity.h"
USING_NS_CC;
void Entity::changeDirection()
{
	if (this->direction == 1) {
		this->direction = -1;
	}
	else if (this->direction == -1) {
		this->direction = 1;
	}
}
void Entity::OnContact()
{
	if (this->contact == 0){
		this->contact = 1;
		this->changeDirection();
	}
	else if (this->contact == 1) {
		this->contact = 0;
	}

}
Entity::Entity() {
	this->Spawned = false;
	this->Lemmings = Sprite::create("HelloWorld.png");
	this->contact = 0;
	this->direction = 1;
}

Entity::~Entity() {

}
