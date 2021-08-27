#pragma once
#include "cocos2d.h"
#include"MapSprite.h"
#include"Road.h"
#include"PlaceNode.h"
#include"MapGraph.h"
#include"PathList.h"
#include"Path.h"
#include<string>

USING_NS_CC;
using namespace std;

class MapLayer : public cocos2d::Layer
{
public:
	virtual bool init();

	virtual void update(float dt);

	void onTouchesMoved(const std::vector<Touch*>& touches, cocos2d::Event  *event);
	void onTouchesEnded(const std::vector<Touch*>& touches, cocos2d::Event  *event);
	void startFindPath(Label* info);

	CREATE_FUNC(MapLayer);

	int state;//0可移动地图 1选起点 2选终点
	int type;//0步行 1自行车 2汽车

private:
	MapSprite * map;
	Road* road;
	PlaceNode* placeNode;
	MapGraph* mapGraph;
	Path* path;
	PathList* pathList;

	DrawNode* startDrawNode;
	DrawNode* endDrawNode;

	GraphNode<MapNode*, MapEdge*>* startNode;
	GraphNode<MapNode*, MapEdge*>* endNode;
};
