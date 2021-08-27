#pragma once
#include"cocos2d.h"
#include"MapGraph.h"
#include"Tools.h"

USING_NS_CC;

class PlaceNode : public cocos2d::DrawNode
{
public:
	virtual bool init();

	void drawNode(MapGraph* graph);

	CREATE_FUNC(PlaceNode);
};