#include"MainScreen.h"
#include"MapLayer.h"
#include"UILayer.h"

bool MainScene::init()
{
	Scene::init();

	MapLayer* mapLayer = MapLayer::create();
	mapLayer->setPosition(-1500, -2000);

	UILayer* uiLayer = UILayer::create();
	uiLayer->initMapLayer(mapLayer);

	this->addChild(mapLayer);

	this->addChild(uiLayer);

	return true;
}