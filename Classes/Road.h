#pragma once
#include"cocos2d.h"
#include"MyQueue.h"
#include"MapGraph.h"

USING_NS_CC;

class Road : public cocos2d::DrawNode
{
public:
	virtual bool init();

	void drawRoad(MapGraph* graph);

	CREATE_FUNC(Road);
};
