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

//void GameLayer::keyPressed(cocos2d::EventKeyboard::KeyCode keyCode, cocos2d::Event* event)
//{
//	if (keyCode == EventKeyboard::KeyCode::KEY_SPACE) {
//		log("keycode", keyCode);
//		auto moveBy = MoveBy::create(1, Vec2(0, 500));
//
//		/*this->Sprite1->runAction(moveBy);*/
//	}
//	if (keyCode == EventKeyboard::KeyCode::KEY_RIGHT_ARROW) {
//		this->Move = 1;
//		log("moove %d", Move);
//
//	}
//	if (keyCode == EventKeyboard::KeyCode::KEY_LEFT_ARROW) {
//		this->Move = -1;
//		log("moove %d", Move);
//
//	}
//}

// Update Function

void GameLayer::update(float delta) {
	
	if (this->Move == 1) {
		auto moveBy = MoveBy::create(1, Vec2(1, 0));
		for (int i = 0; i < this->Lemmings.size(); i++) {


			/*if (this->Lemmings[i]->getBoundingBox().getMaxX() == this->Border->getBoundingBox().getMinX()) {
				log("collide if move 1");
				this->Move = -1;
			}*/

			if (i == 0) {
				this->Lemmings[i]->runAction(moveBy);

			}
			else {
				this->Lemmings[i]->runAction(moveBy->clone());

			}

		}
	}
	else if (this->Move == -1) {
		auto moveBy = MoveBy::create(1, Vec2(-1, 0));
		for (int i = 0; i < this->Lemmings.size(); i++) {
			/*if (this->Lemmings[i]->getBoundingBox().getMinX() == this->Border->getBoundingBox().getMaxX()) {
				log("collide if move -1");
				this->Move = 1;
			}*/

			if (i == 0) {
				this->Lemmings[i]->runAction(moveBy);
			}
			else {
				this->Lemmings[i]->runAction(moveBy->clone());

			}

		}
	}

}

//Contact Function

bool GameLayer::onContactBegin(cocos2d::PhysicsContact& contact) {

	auto nodeA = contact.getShapeA()->getBody()->getNode();
	auto nodeB = contact.getShapeB()->getBody()->getNode();
	if (nodeA && nodeB)
	{
		log("%d, %d",nodeA->getTag(), nodeB->getTag());
	}
	return false;
}



void GameLayer::changeMoveDirection() {
	if (this->Move == 1) {
		this->Move = -1;
	}
	else {
		this->Move = 1;
	}
}


//void GameLayer::keyReleased(cocos2d::EventKeyboard::KeyCode keyCode, cocos2d::Event* event)
//{
//	if (keyCode == EventKeyboard::KeyCode::KEY_RIGHT_ARROW || keyCode == EventKeyboard::KeyCode::KEY_LEFT_ARROW) {
//		this->Move = 0;
//	}
//}

// Print useful error message instead of segfaulting when files are not there.
static void problemLoading(const char* filename)
{
	printf("Error while loading: %s\n", filename);
	printf("Depending on how you compiled you might have to add 'Resources/' in front of filenames in HelloWorldScene.cpp\n");
}
// on "init" you need to initialize your instance

bool GameLayer::init()
{
	//////////////////////////////
	// 1. super init first
	if (!Layer::init())
	{
		return false;
	}

	this->Move = 1;
	// Keyboard Listener
	//auto listener = EventListenerKeyboard::create();
	//listener->onKeyPressed = CC_CALLBACK_2(GameLayer::keyPressed, this);
	//listener->onKeyReleased = CC_CALLBACK_2(GameLayer::keyReleased, this);
	//_eventDispatcher->addEventListenerWithSceneGraphPriority(listener, this);





	auto visibleSize = Director::getInstance()->getVisibleSize();
	Vec2 origin = Director::getInstance()->getVisibleOrigin();
	PhysicsMaterial material(1.0f, 0.0f, 0.0f);



	// Window Border 
	//auto edgeBody = PhysicsBody::createEdgeBox(visibleSize, material, 5);
	//auto edgeNode = Node::create();
	//edgeNode->setPosition(Point(origin.x + visibleSize.width / 2, origin.y + visibleSize.height / 2));
	//edgeNode->setPhysicsBody(edgeBody);
	//this->addChild(edgeNode);
	//edgeNode->getPhysicsBody()->setCategoryBitmask(0x03);    // 0011
	//edgeNode->getPhysicsBody()->setCollisionBitmask(0x03);   // 0011

	//this->Border = edgeNode;

	auto RightBorderBody = PhysicsBody::createEdgeBox(Size(5, visibleSize.height), material, 5);
	auto RightBorderNode = Sprite::create();
	RightBorderNode->setPosition(Point(origin.x + visibleSize.width, origin.y + visibleSize.height / 2));
	RightBorderNode->setPhysicsBody(RightBorderBody);
	this->addChild(RightBorderNode, 0);
	RightBorderBody->setTag(3);
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
	LeftBorderBody->setTag(3);
	LeftBorderNode->getPhysicsBody()->setContactTestBitmask(0xFFFFFFFF);
	

	//auto UpperBorderBody = PhysicsBody::createEdgeBox(Size(visibleSize.width, 1), material, 5);
	//auto UpperBorderNode = Node::create();
	//UpperBorderNode->setPosition(Point(origin.x + visibleSize.width / 2, origin.y + visibleSize.height));
	//UpperBorderNode->setPhysicsBody(UpperBorderBody);
	//this->addChild(UpperBorderNode);
	//UpperBorderNode->getPhysicsBody()->setCategoryBitmask(0x03);    // 0011
	//UpperBorderNode->getPhysicsBody()->setCollisionBitmask(0x03);   // 0011


	/*auto label = MenuItemFont::create("Start Game", CC_CALLBACK_1(GameLayer::menuChange, this));
	if (label == nullptr ||
		label->getContentSize().width <= 0 ||
		label->getContentSize().height <= 0)
	{
		problemLoading("'fonts/Marker Felt.ttf'");
	}
	else {
		float x = visibleSize.width / 2;
		float y = visibleSize.height / 2 - label->getContentSize().height * 5;
		label->setFontSize(24);
		label->setPosition(Vec2(x, y));
	}
	auto menu = Menu::create(label, NULL);
	menu->setPosition(Vec2::ZERO);
	this->addChild(menu, 1);*/

	auto s_centre = Vec2(visibleSize.width / 2, visibleSize.height / 2);


	// Lemmings and their Physics Body

	Entity lemmings(2);
	for (auto i = 0; i < lemmings.Lemmings.size(); i++) {
		auto physicsBody = PhysicsBody::createBox(Size(lemmings.Lemmings[i]->getContentSize().width, lemmings.Lemmings[i]->getContentSize().height), PhysicsMaterial(0.1f, 0.0f, 0.0f));
		physicsBody->setDynamic(true);
		lemmings.Lemmings[i]->addComponent(physicsBody);
		this->addChild(lemmings.Lemmings[i], 0);
		lemmings.Lemmings[i]->getPhysicsBody()->setContactTestBitmask(0xFFFFFFFF);
		lemmings.Lemmings[i]->setPosition(Vec2(Director::getInstance()->getVisibleSize().width / 2 + Director::getInstance()->getVisibleOrigin().x + (i * 300), Director::getInstance()->getVisibleSize().height / 2 + Director::getInstance()->getVisibleOrigin().y));
	}
	Lemmings = lemmings.Lemmings;

	// Contact Listener
	auto contactListener = EventListenerPhysicsContact::create();
	contactListener->onContactBegin = CC_CALLBACK_1(GameLayer::onContactBegin, this);
	_eventDispatcher->addEventListenerWithSceneGraphPriority(contactListener, this);

	this->scheduleUpdate();

	return true;
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
