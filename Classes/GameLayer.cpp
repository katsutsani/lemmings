/****************************************************************************
 Copyright (c) 2017-2018 Xiamen Yaji Software Co., Ltd.

 http://www.cocos2d-x.org

 Permission is hereby granted, free of charge, to any person obtaining a copy
 of this software and associated documentation files (the "Software"), to deal
 in the Software without restriction, including without limitation the rights
 to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
 copies of the Software, and to permit persons to whom the Software is
 furnished to do so, subject to the following conditions:

 The above copyright notice and this permission notice shall be included in
 all copies or substantial portions of the Software.

 THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
 OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
 THE SOFTWARE.
 ****************************************************************************/

#include "GameLayer.h"
#include "HelloWorldScene.h"
#include "GameScene.h"
#include "physics/CCPhysicsContact.h"

USING_NS_CC;

// Update Function

void GameLayer::update(float delta) {
	time -= delta;
	if (time <= 0 && this->spawn < 5) {
		time = 1.5f;
		LemmingsSpawn();
	}
	for (int i = 0; i < this->Lemmings.size(); i++) {
		if (this->Lemmings[i]->direction == 1) {
			auto moveBy = MoveBy::create(1, Vec2(4, 0));
			if(i != 0)
				this->Lemmings[i]->Lemmings->runAction(moveBy->clone());
			else
				this->Lemmings[i]->Lemmings->runAction(moveBy);
		}
		else if (this->Lemmings[i]->direction == -1) {
			auto moveBy = MoveBy::create(1, Vec2(-4, 0));
			if (i != 0)
				this->Lemmings[i]->Lemmings->runAction(moveBy->clone());
			else
				this->Lemmings[i]->Lemmings->runAction(moveBy);
		}
	}
}

//Contact Function

bool GameLayer::onContactBegin(cocos2d::PhysicsContact& contact) {

	auto nodeA = contact.getShapeA()->getBody()->getNode();
	auto nodeB = contact.getShapeB()->getBody()->getNode();
	if (nodeA && nodeB)
	{
		if (nodeB->getTag() <= 0 && nodeA->getTag() == 3)
		{
			for (int i = 0; i < this->Lemmings.size(); i++) {
				if (this->Lemmings[i]->Lemmings->getTag() == nodeB->getTag()) {
					auto rotateTo = RotateTo::create(1.0f, 90.0f);
					this->Lemmings[i]->Lemmings->runAction(rotateTo);
					this->Lemmings[i]->OnContact();
					
					break;
				}
			}

			return true;
		}

	}
	return false;
}

// Print useful error message instead of segfaulting when files are not there.
static void problemLoading(const char* filename)
{
	printf("Error while loading: %s\n", filename);
	printf("Depending on how you compiled you might have to add 'Resources/' in front of filenames in HelloWorldScene.cpp\n");
}
// on "init" you need to initialize your instance

bool GameLayer::init()
{
	time = 1.5f;
	//////////////////////////////
	// 1. super init first
	if (!Layer::init())
	{
		return false;
	}

	auto visibleSize = Director::getInstance()->getVisibleSize();
	Vec2 origin = Director::getInstance()->getVisibleOrigin();
	PhysicsMaterial material(1.0f, 0.0f, 0.0f);

	// Window Border 

	auto RightBorderBody = PhysicsBody::createEdgeBox(Size(1, visibleSize.height), material, 5);
	auto RightBorderNode = Node::create();
	RightBorderNode->setPosition(Point(origin.x + visibleSize.width, origin.y + visibleSize.height / 2));
	RightBorderNode->setPhysicsBody(RightBorderBody);
	this->addChild(RightBorderNode, 0);
	RightBorderNode->setTag(3);
	RightBorderNode->getPhysicsBody()->setContactTestBitmask(0xFFFFFFFF);


	auto GroundBorderBody = PhysicsBody::createEdgeBox(Size(visibleSize.width, 1), material, 5);
	auto GroundBorderNode = Node::create();
	GroundBorderNode->setPosition(Point(origin.x + visibleSize.width / 2, origin.y));
	GroundBorderNode->setPhysicsBody(GroundBorderBody);
	this->addChild(GroundBorderNode);
	GroundBorderNode->getPhysicsBody()->setCategoryBitmask(0x03);    // 0011
	GroundBorderNode->getPhysicsBody()->setCollisionBitmask(0x03);   // 0011

	auto LeftBorderBody = PhysicsBody::createEdgeBox(Size(1, visibleSize.height), material, 5);
	auto LeftBorderNode = Node::create();
	LeftBorderNode->setPosition(Point(origin.x, origin.y + visibleSize.height / 2));
	LeftBorderNode->setPhysicsBody(LeftBorderBody);
	this->addChild(LeftBorderNode, 0);
	LeftBorderNode->setTag(3);
	LeftBorderNode->getPhysicsBody()->setContactTestBitmask(0xFFFFFFFF);

	auto s_centre = Vec2(visibleSize.width / 2, visibleSize.height / 2);


	// Lemmings and their Physics Body

	this->Lemmings.push_back(new Entity);
	auto physicsBody = PhysicsBody::createBox(Size(this->Lemmings[spawn]->Lemmings->getContentSize().width, this->Lemmings[spawn]->Lemmings->getContentSize().height), PhysicsMaterial(0.1f, 0.0f, 0.0f));
	physicsBody->setDynamic(true);
	this->Lemmings[spawn]->Lemmings->addComponent(physicsBody);
	this->Lemmings[spawn]->Lemmings->setTag(-spawn);
	this->Lemmings[spawn]->Lemmings->getPhysicsBody()->setContactTestBitmask(0xFFFFFFFF);
	this->Lemmings[spawn]->Lemmings->setPosition(Vec2(Director::getInstance()->getVisibleSize().width / 2 + Director::getInstance()->getVisibleOrigin().x, Director::getInstance()->getVisibleSize().height / 2 + Director::getInstance()->getVisibleOrigin().y));
	this->addChild(this->Lemmings[spawn]->Lemmings, 1);
	spawn++;
	// Contact Listener
	auto contactListener = EventListenerPhysicsContact::create();
	contactListener->onContactBegin = CC_CALLBACK_1(GameLayer::onContactBegin, this);
	_eventDispatcher->addEventListenerWithSceneGraphPriority(contactListener, this);
	this->scheduleUpdate();
	return true;
}

void GameLayer::LemmingsSpawn()
{
	if (spawn < 5) {
		this->Lemmings.push_back(new Entity);
		auto physicsBody = PhysicsBody::createBox(Size(this->Lemmings[spawn]->Lemmings->getContentSize().width, this->Lemmings[spawn]->Lemmings->getContentSize().height), PhysicsMaterial(0.1f, 0.0f, 0.0f));
		physicsBody->setDynamic(true);
		this->Lemmings[spawn]->Lemmings->addComponent(physicsBody);
		this->Lemmings[spawn]->Lemmings->setTag(-spawn);
		this->Lemmings[spawn]->Lemmings->getPhysicsBody()->setContactTestBitmask(0xFFFFFFFF);
		this->Lemmings[spawn]->Lemmings->setPosition(Vec2(Director::getInstance()->getVisibleSize().width / 2 + Director::getInstance()->getVisibleOrigin().x, Director::getInstance()->getVisibleSize().height / 2 + Director::getInstance()->getVisibleOrigin().y));
		this->addChild(this->Lemmings[spawn]->Lemmings, 1);
	}
	spawn++;

	/*if (this->spawn < this->Lemmings.size() && this->Lemmings[this->spawn]->Spawned == false) {
		this->Lemmings[this->spawn]->Spawned = true;
		this->Lemmings[this->spawn]->Lemmings->getPhysicsBody()->setDynamic(true);
		this->Lemmings[this->spawn]->Lemmings->setOpacity(255);
		this->spawn = this->spawn + 1;
	}*/
}

void GameLayer::menuChange(Ref* pSender)
{
	//Change the cocos2d-x game scene
	auto scene = HelloWorld::createScene();
	Director::getInstance()->replaceScene(scene);

	/*To navigate back to native iOS screen(if present) without quitting the application  ,do not use Director::getInstance()->end() as given above,instead trigger a custom event created in RootViewController.mm as below*/

	//EventCustom customEndEvent("game_scene_close_event");
	//_eventDispatcher->dispatchEvent(&customEndEvent);


}
