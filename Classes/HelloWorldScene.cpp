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

#include "HelloWorldScene.h"
#include "GameScene.h"
#include "ui/CocosGUI.h"

USING_NS_CC;

Scene* HelloWorld::createScene()
{
    return HelloWorld::create();
}

static void problemLoading(const char* filename)
{
    printf("Error while loading: %s\n", filename);
    printf("Depending on how you compiled you might have to add 'Resources/' in front of filenames in HelloWorldScene.cpp\n");
}

bool HelloWorld::init()
{

    if ( !Scene::init() )
    {
        return false;
    }

    auto visibleSize = Director::getInstance()->getVisibleSize();
    Vec2 origin = Director::getInstance()->getVisibleOrigin();

    /// ///////////////////////////////////////////// BACKGROUND MENU

    auto bg = Sprite::create("Lemmings.png");

    if (bg == nullptr)
    {
        problemLoading("Lemmings.png");
    }
    else
    {
        // position the sprite on the center of the screen
        bg->setPosition(Vec2(visibleSize.width / 2 + origin.x, visibleSize.height / 2 + origin.y));

        // add the sprite as a child to this layer
        this->addChild(bg, 0);
        bg->setScale(1);
    }

    /// ///////////////////////////////////////////// LEMMINGS TEXT


    auto Text = Sprite::create("LemmingsText.png");

    if (Text == nullptr)
    {
        problemLoading("LemmingsText.png");
    }
    else
    {
        // position the sprite on the center of the screen
        Text->setPosition(Vec2(visibleSize.width / 2 + origin.x, visibleSize.height / 1 - 100 + origin.y));

        // add the sprite as a child to this layer
        this->addChild(Text, 0);
        Text->setScale(1);
    }


    //////////////////////////////////////////////// START GAME BUTTON

    auto Play = MenuItemImage::create(
        "PlayRB.png",
        "PlayActRB.png",
        CC_CALLBACK_1(HelloWorld::menuCloseCallback, this));

    if (Play == nullptr ||
        Play->getContentSize().width <= 0 ||
        Play->getContentSize().height <= 0)
    {
        problemLoading("'Play Button image'");
    }
    else
    {
        Play->setPosition(Vec2(origin.x + visibleSize.width / 2,
                               origin.y + visibleSize.height - 250 - Play->getContentSize().height));
    }

    // create menu, it's an autorelease object
    auto playDisplay = Menu::create(Play, NULL);
    playDisplay->setPosition(Vec2::ZERO);

    this->addChild(playDisplay, 1);

    ////////////////////////////////////////////// QUIT GAME BUTTON

    auto Quit = MenuItemImage::create(
        "QuitGameRB.png",
        "QuitGameActRB.png",
        "QuitGameActRB.png",
        CC_CALLBACK_1(HelloWorld::menuCloseApp, this));

        if (Quit == nullptr ||
            Quit->getContentSize().width <= 0 ||
            Quit->getContentSize().height <= 0)
        {
            problemLoading("'Quit button image'");
        }
        else
        {
            Quit->setPosition(Vec2(origin.x + visibleSize.width / 2,
                origin.y + visibleSize.height - 450 - Quit->getContentSize().height));
        }

        // create menu, it's an autorelease object
        auto quitDisplay = Menu::create(Quit, NULL);
        quitDisplay->setPosition(Vec2::ZERO);

        this->addChild(quitDisplay, 1);
     

        ///////////////////////////// SKILLBAR 1

        //auto Skillbar = MenuItemImage::create(
        //    "SquareSlp.png",
        //    "SquareAct.png",
        //    CC_CALLBACK_1(HelloWorld::menuCloseApp, this));

        //if (Skillbar == nullptr ||
        //    Skillbar->getContentSize().width <= 0 ||
        //    Skillbar->getContentSize().height <= 0)
        //{
        //    problemLoading("'Skillbar'");
        //}
        //else
        //{
        //    Skillbar->setPosition(Vec2(origin.x + visibleSize.width / 10,
        //        origin.y + visibleSize.height/10));
        //}

        //auto skillbarDisplay = Menu::create(Skillbar, NULL);
        //skillbarDisplay->setPosition(Vec2::ZERO);

        //this->addChild(skillbarDisplay, 1);

        //////////////////////////////// SKILLBAR 2

        //auto Skillbar2 = MenuItemImage::create(
        //    "SquareSlp.png",
        //    "SquareAct.png",
        //    CC_CALLBACK_1(HelloWorld::menuCloseApp, this));

        //if (Skillbar2 == nullptr ||
        //    Skillbar2->getContentSize().width <= 0 ||
        //    Skillbar2->getContentSize().height <= 0)
        //{
        //    problemLoading("'Skillbar'");
        //}
        //else
        //{
        //    Skillbar2->setPosition(Vec2(origin.x + visibleSize.width / 10 + 150,
        //        origin.y + visibleSize.height / 10));
        //}

        //auto skillbarDisplay2 = Menu::create(Skillbar2, NULL);
        //skillbarDisplay2->setPosition(Vec2::ZERO);

        //this->addChild(skillbarDisplay2, 1);

        //////////////////////////////// SKILLBAR 3

        //auto Skillbar3 = MenuItemImage::create(
        //    "SquareSlp.png",
        //    "SquareAct.png",
        //    CC_CALLBACK_1(HelloWorld::menuCloseApp, this));

        //if (Skillbar3 == nullptr ||
        //    Skillbar3->getContentSize().width <= 0 ||
        //    Skillbar3->getContentSize().height <= 0)
        //{
        //    problemLoading("'Skillbar'");
        //}
        //else
        //{
        //    Skillbar3->setPosition(Vec2(origin.x + visibleSize.width / 10 + 300,
        //        origin.y + visibleSize.height / 10));
        //}

        //auto skillbarDisplay3 = Menu::create(Skillbar3, NULL);
        //skillbarDisplay3->setPosition(Vec2::ZERO);

        //this->addChild(skillbarDisplay3, 1);

        //////////////////////////////// SKILLBAR 4

        //auto Skillbar4 = MenuItemImage::create(
        //    "SquareSlp.png",
        //    "SquareAct.png",
        //    CC_CALLBACK_1(HelloWorld::menuCloseApp, this));

        //if (Skillbar4 == nullptr ||
        //    Skillbar4->getContentSize().width <= 0 ||
        //    Skillbar4->getContentSize().height <= 0)
        //{
        //    problemLoading("'Skillbar'");
        //}
        //else
        //{
        //    Skillbar4->setPosition(Vec2(origin.x + visibleSize.width / 10 + 450,
        //        origin.y + visibleSize.height / 10));
        //}

        //auto skillbarDisplay4 = Menu::create(Skillbar4, NULL);
        //skillbarDisplay4->setPosition(Vec2::ZERO);

        //this->addChild(skillbarDisplay4, 1);

        //////////////////////////////// SKILLBAR 5


        //auto Skillbar5 = MenuItemImage::create(
        //    "SquareSlp.png",
        //    "SquareAct.png",
        //    CC_CALLBACK_1(HelloWorld::menuCloseApp, this));

        //if (Skillbar5 == nullptr ||
        //    Skillbar5->getContentSize().width <= 0 ||
        //    Skillbar5->getContentSize().height <= 0)
        //{
        //    problemLoading("'Skillbar'");
        //}
        //else
        //{
        //    Skillbar5->setPosition(Vec2(origin.x + visibleSize.width / 10 + 600,
        //        origin.y + visibleSize.height / 10));
        //}

        //auto skillbarDisplay5 = Menu::create(Skillbar5, NULL);
        //skillbarDisplay5->setPosition(Vec2::ZERO);

        //this->addChild(skillbarDisplay5, 1);

        //////////////////////////////// SKILLBAR BIG

        //auto SkillbarBig = MenuItemImage::create(
        //    "BigSkillBar.png",
        //    "BigSkillBar.png",
        //    CC_CALLBACK_1(HelloWorld::menuCloseApp, this));

        //if (SkillbarBig == nullptr ||
        //    SkillbarBig->getContentSize().width <= 0 ||
        //    SkillbarBig->getContentSize().height <= 0)
        //{
        //    problemLoading("'Skillbar'");
        //}
        //else
        //{
        //    SkillbarBig->setPosition(Vec2(origin.x + visibleSize.width / 10 + 798,
        //        origin.y + visibleSize.height / 8 + 11));
        //}

        //auto skillbarDisplayBig = Menu::create(SkillbarBig, NULL);
        //skillbarDisplayBig->setPosition(Vec2::ZERO);

        //this->addChild(skillbarDisplayBig, 1);

}


void HelloWorld::menuCloseCallback(Ref* pSender)
{
    auto scene = GameScene::createScene();
    //Close the cocos2d-x game scene and quit the application
    Director::getInstance()->replaceScene(scene);

        /*To navigate back to native iOS screen(if present) without quitting the application  ,do not use Director::getInstance()->end() as given above,instead trigger a custom event created in RootViewController.mm as below*/

        //EventCustom customEndEvent("game_scene_close_event");
        //_eventDispatcher->dispatchEvent(&customEndEvent);
}


void HelloWorld::menuCloseApp(Ref* pSender)
{
    auto scene = GameScene::createScene();

    Director::getInstance()->end();

}

