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

#include "GameScene.h"
#include "HelloWorldScene.h"


USING_NS_CC;
Scene* GameScene::createScene()
{
	// create the scene with physics enabled
	auto scene = GameScene::createWithPhysics();
	// set gravity
	scene->getPhysicsWorld()->setGravity(Vec2(0, -900));

	// optional: set debug draw
	scene->getPhysicsWorld()->setDebugDrawMask(0xffff);

	auto layer = GameScene::create();
	scene->addChild(layer);

	return scene;
}

void GameScene::keyPressed(cocos2d::EventKeyboard::KeyCode keyCode, cocos2d::Event* event)
{
	if (keyCode == EventKeyboard::KeyCode::KEY_SPACE) {
		log("keycode", keyCode);
		auto moveBy = MoveBy::create(1, Vec2(0, 500));

		/*this->Sprite1->runAction(moveBy);*/
	}
	if (keyCode == EventKeyboard::KeyCode::KEY_RIGHT_ARROW) {
		Move = 1;
		log("moove %d", Move);

	}
	if (keyCode == EventKeyboard::KeyCode::KEY_LEFT_ARROW) {
		Move = -1;
		log("moove %d", Move);

	}
}

void GameScene::update() {
	if (this->Move = 1) {
		auto moveBy = MoveBy::create(1, Vec2(10, 0));
		for (int i = 0; i < this->Lemmings.size(); i++) {
			if (i == 0) {
				this->Lemmings[i]->runAction(moveBy);
			}
			else {
				this->Lemmings[i]->runAction(moveBy->clone());
			}

		}
	}
	else if (this->Move = -1) {
		auto moveBy = MoveBy::create(1, Vec2(-10, 0));
		for (int i = 0; i < this->Lemmings.size(); i++) {
			if (i == 0) {
				this->Lemmings[i]->runAction(moveBy);
			}
			else {
				this->Lemmings[i]->runAction(moveBy->clone());
			}

		}
	}
}


void GameScene::keyReleased(cocos2d::EventKeyboard::KeyCode keyCode, cocos2d::Event* event)
{
	if (keyCode == EventKeyboard::KeyCode::KEY_RIGHT_ARROW || keyCode == EventKeyboard::KeyCode::KEY_LEFT_ARROW) {
		Move = 0;
	}
}

// Print useful error message instead of segfaulting when files are not there.
static void problemLoading(const char* filename)
{
	printf("Error while loading: %s\n", filename);
	printf("Depending on how you compiled you might have to add 'Resources/' in front of filenames in HelloWorldScene.cpp\n");
}
// on "init" you need to initialize your instance
bool GameScene::init()
{
	//////////////////////////////
	// 1. super init first
	if (!Scene::initWithPhysics())
	{
		return false;
	}

	auto listener = EventListenerKeyboard::create();
	listener->onKeyPressed = CC_CALLBACK_2(GameScene::keyPressed, this);
	listener->onKeyReleased = CC_CALLBACK_2(GameScene::keyReleased, this);
	_eventDispatcher->addEventListenerWithSceneGraphPriority(listener, this);


	auto visibleSize = Director::getInstance()->getVisibleSize();
	Vec2 origin = Director::getInstance()->getVisibleOrigin();
	PhysicsMaterial material(1.0f, 0.0f, 0.0f);
	auto edgeBody = PhysicsBody::createEdgeBox(visibleSize, material, 5);
	auto edgeNode = Node::create();
	edgeNode->setPosition(Point(origin.x + visibleSize.width / 2, origin.y + visibleSize.height / 2));
	edgeNode->setPhysicsBody(edgeBody);
	this->addChild(edgeNode);

	auto label = MenuItemFont::create("Start Game", CC_CALLBACK_1(GameScene::menuChange, this));
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
	this->addChild(menu, 1);

	auto s_centre = Vec2(visibleSize.width / 2, visibleSize.height / 2);

	Entity lemmings(3);


	for (auto i = 0; i < lemmings.Lemmings.size(); i++) {
		auto physicsBody = PhysicsBody::createBox(Size(lemmings.Lemmings[i]->getContentSize().width, lemmings.Lemmings[i]->getContentSize().height), PhysicsMaterial(0.1f, 0.0f, 0.0f));
		physicsBody->setDynamic(true);
		lemmings.Lemmings[i]->addComponent(physicsBody);
		this->addChild(lemmings.Lemmings[i], 0);
	}
	Lemmings = lemmings.Lemmings;

	return true;
}


void GameScene::menuChange(Ref* pSender)
{
	//Change the cocos2d-x game scene
	auto scene = HelloWorld::createScene();
	Director::getInstance()->replaceScene(scene);

	/*To navigate back to native iOS screen(if present) without quitting the application  ,do not use Director::getInstance()->end() as given above,instead trigger a custom event created in RootViewController.mm as below*/

	//EventCustom customEndEvent("game_scene_close_event");
	//_eventDispatcher->dispatchEvent(&customEndEvent);


}
