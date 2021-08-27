#pragma once
#include"cocos2d.h"
#include"MyQueue.h"
#include"PathList.h"

USING_NS_CC;

class Path : public cocos2d::DrawNode
{
public:
	virtual bool init();

	void drawPath(GraphADJ<ListNode*, GraphNode<MapNode*, MapEdge*>*>* pathRear, GraphNode<MapNode*, MapEdge*>* startNode);

	CREATE_FUNC(Path);
};
