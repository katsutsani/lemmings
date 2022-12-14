#include "Entity.h"
USING_NS_CC;
Entity::Entity(int NbOfEntity) {
	auto visibleSize = Director::getInstance()->getVisibleSize();
	Vec2 origin = Director::getInstance()->getVisibleOrigin();

	for (int i = 0; i < NbOfEntity; i++) {
		auto sprite = Sprite::create("HelloWorld.png");

		sprite->setPosition(Vec2(visibleSize.width / 2 + origin.x+(i*300), visibleSize.height / 2 + origin.y));

		Lemmings.push_back(sprite);

		
	}
	
}

Entity::~Entity(){

}
