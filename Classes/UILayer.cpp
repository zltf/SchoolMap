#include"UILayer.h"
#include"Tools.h"

bool UILayer::init()
{
	Layer::init();

	scheduleUpdate();

	//获取参数
	auto visibleSize = Director::getInstance()->getVisibleSize();
	Vec2 origin = Director::getInstance()->getVisibleOrigin();

	title = Label::createWithTTF(Tools::TFChinese("校园导航"), "fonts/cuheiti.otf", 30);
	title->setColor(Color3B::BLACK);
	title->setPosition(100, visibleSize.height - 50);

	type = Label::createWithTTF(Tools::TFChinese("当前出行方式："), "fonts/cuheiti.otf", 30);
	type->setColor(Color3B::BLACK);
	type->setPosition(visibleSize.width - 200, visibleSize.height - 50);

	info = Label::createWithTTF(Tools::TFChinese(""), "fonts/cuheiti.otf", 30);
	info->setColor(Color3B::BLACK);
	info->setPosition(visibleSize.width - 200, visibleSize.height - 160);

	menu = Menu::create();
	menu->setPosition(0, 0);

	auto btn_add1 = MenuItemImage::create("btn_add1.png", "btn_add1_checked.png", CC_CALLBACK_1(UILayer::btn_add1_Callback, this));
	btn_add1->setPosition(visibleSize.width - 100, 200);
	menu->addChild(btn_add1);

	auto btn_add2 = MenuItemImage::create("btn_add2.png", "btn_add2_checked.png", CC_CALLBACK_1(UILayer::btn_add2_Callback, this));
	btn_add2->setPosition(visibleSize.width - 100, 130);
	menu->addChild(btn_add2);

	auto btn_start = MenuItemImage::create("btn_start.png", "btn_start_checked.png", CC_CALLBACK_1(UILayer::btn_start_Callback, this));
	btn_start->setPosition(visibleSize.width - 100, 60);
	menu->addChild(btn_start);

	auto btn_foot = MenuItemImage::create("btn_foot.png", "btn_foot_checked.png", CC_CALLBACK_1(UILayer::btn_foot_Callback, this));
	btn_foot->setPosition(visibleSize.width - 100, 440);
	menu->addChild(btn_foot);

	auto btn_bike = MenuItemImage::create("btn_bike.png", "btn_bike_checked.png", CC_CALLBACK_1(UILayer::btn_bike_Callback, this));
	btn_bike->setPosition(visibleSize.width - 100, 370);
	menu->addChild(btn_bike);

	auto btn_car = MenuItemImage::create("btn_car.png", "btn_car_checked.png", CC_CALLBACK_1(UILayer::btn_car_Callback, this));
	btn_car->setPosition(visibleSize.width - 100, 300);
	menu->addChild(btn_car);

	addChild(menu);
	addChild(title);
	addChild(type);
	addChild(info);

	return true;
}

void UILayer::initMapLayer(MapLayer* mapLayer)
{
	this->mapLayer = mapLayer;
}

void UILayer::update(float dt)
{
	string typeStr = "";
	switch (mapLayer->type)
	{
	case 0:
		typeStr = "步行";
		break;
	case 1:
		typeStr = "骑自行车";
		break;
	case 2:
		typeStr = "开车";
		break;
	}
	type->setString(Tools::TFChinese("当前出行方式：" + typeStr));
}

void UILayer::btn_add1_Callback(cocos2d::Ref* pSender)
{
	mapLayer->state = mapLayer->state == 1 ? 0 : 1;
}

void UILayer::btn_add2_Callback(cocos2d::Ref* pSender)
{
	mapLayer->state = mapLayer->state == 2 ? 0 : 2;
}

void UILayer::btn_start_Callback(cocos2d::Ref* pSender)
{
	mapLayer->startFindPath(info);

	mapLayer->state = 0;
}

void UILayer::btn_foot_Callback(cocos2d::Ref* pSender)
{
	mapLayer->type = 0;
}

void UILayer::btn_bike_Callback(cocos2d::Ref* pSender)
{
	mapLayer->type = 1;
}

void UILayer::btn_car_Callback(cocos2d::Ref* pSender)
{
	mapLayer->type = 2;
}