#pragma once
#include "cocos2d.h"
#include"MapLayer.h"

USING_NS_CC;

class UILayer : public cocos2d::Layer
{
public:
	virtual bool init();

	virtual void update(float dt);

	void initMapLayer(MapLayer* mapLayer);

	void btn_add1_Callback(cocos2d::Ref* pSender);
	void btn_add2_Callback(cocos2d::Ref* pSender);
	void btn_start_Callback(cocos2d::Ref* pSender);
	void btn_foot_Callback(cocos2d::Ref* pSender);
	void btn_bike_Callback(cocos2d::Ref* pSender);
	void btn_car_Callback(cocos2d::Ref* pSender);

	CREATE_FUNC(UILayer);

private:
	Label* title;
	Label* type;
	Label* info;

	string infoStr;

	Menu* menu;

	MapLayer* mapLayer;
};
