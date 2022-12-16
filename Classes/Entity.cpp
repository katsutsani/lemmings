#include "Entity.h"
USING_NS_CC;
Entity::Entity(int NbOfEntity) {
	auto visibleSize = Director::getInstance()->getVisibleSize();
	Vec2 origin = Director::getInstance()->getVisibleOrigin();

	for (int i = 0; i < NbOfEntity; i++) {

		Lemmings.push_back(Sprite::create("HelloWorld.png"));

		
	}
	
}

Entity::~Entity(){

}
