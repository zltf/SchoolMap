#include "MapLayer.h"
#include"MyQueue.h"

bool MapLayer::init()
{
	Layer::init();

	scheduleUpdate();

	state = 0;
	type = 0;

	//允许接收触摸事件
	EventDispatcher* eventDispatcher = Director::getInstance()->getEventDispatcher();
	auto listen = EventListenerTouchAllAtOnce::create();
	listen->onTouchesMoved = CC_CALLBACK_2(MapLayer::onTouchesMoved, this);
	listen->onTouchesEnded = CC_CALLBACK_2(MapLayer::onTouchesEnded, this);
	eventDispatcher->addEventListenerWithSceneGraphPriority(listen, this);

	//获取参数
	auto visibleSize = Director::getInstance()->getVisibleSize();
	Vec2 origin = Director::getInstance()->getVisibleOrigin();

	//初始化成员
	map = MapSprite::create();//地图背景
	map->setPosition(map->getContentSize()/2);

	road = Road::create();//道路
	road->setPosition(map->convertToWorldSpace(Vec2::ZERO));

	placeNode = PlaceNode::create();//节点
	placeNode->setPosition(map->convertToWorldSpace(Vec2::ZERO));

	mapGraph = new MapGraph("MapNode.txt", "MapEdge.txt");

	placeNode->drawNode(mapGraph);
	road->drawRoad(mapGraph);

	startNode = nullptr;
	endNode = nullptr;

	path = nullptr;

	pathList = new PathList;

	startDrawNode = DrawNode::create();
	endDrawNode = DrawNode::create();

	this->addChild(map);
	this->addChild(road);
	this->addChild(placeNode);
	this->addChild(startDrawNode);
	this->addChild(endDrawNode);

	return true;
}

void MapLayer::onTouchesMoved(const std::vector<Touch*>& touches, cocos2d::Event  *event)
{
	Vec2 position = this->getPosition();
	Vec2 delta = touches[0]->getDelta();
	Vec2 visibleSize = Director::getInstance()->getVisibleSize();

	if (state == 0)
	{
		if ((position.x + delta.x) < 0 && (position.x + delta.x) > -map->getContentSize().width + visibleSize.x)
			this->setPositionX(position.x + delta.x);
		if ((position.y + delta.y) < 0 && (position.y + delta.y) > -map->getContentSize().height + visibleSize.y)
			this->setPositionY(position.y + delta.y);
	}

	//this->setPosition(position + delta);
}

void MapLayer::onTouchesEnded(const std::vector<Touch*>& touches, cocos2d::Event  *event)
{
	if (state != 0)
	{
		Vec2 touch = touches[0]->getLocation() - getPosition();

		GraphNode<MapNode*, MapEdge*>* nearNode = mapGraph->getHead()->nextNode;
		float nearDistance =
			(touch.x - nearNode->data->position.x)*(touch.x - nearNode->data->position.x)
			+ (touch.y - nearNode->data->position.y)*(touch.y - nearNode->data->position.y);

		for (GraphNode<MapNode*, MapEdge*>* gNode = mapGraph->getHead()->nextNode; gNode != nullptr; gNode = gNode->nextNode)
		{
			//按点找点
			float distance =
				(touch.x - gNode->data->position.x)*(touch.x - gNode->data->position.x)
				+ (touch.y - gNode->data->position.y)*(touch.y - gNode->data->position.y);

			if (distance < nearDistance)
			{
				nearNode = gNode;
				nearDistance = distance;
			}

			if (gNode->data->type == 1)//按楼名找点
			{
				float nameDistance =
					(touch.x - gNode->data->namePosition.x)*(touch.x - gNode->data->namePosition.x)
					+ (touch.y - gNode->data->namePosition.y)*(touch.y - gNode->data->namePosition.y);

				if (nameDistance < nearDistance)
				{
					nearNode = gNode;
					nearDistance = nameDistance;
				}
			}
		}

		if (state == 1)
		{
			startNode = nearNode;
			startDrawNode->drawDot(startNode->data->position, 10, Color4F::RED);
		}
		else if (state == 2)
		{
			endNode = nearNode;
			endDrawNode->drawDot(endNode->data->position, 10, Color4F::Color4F(0, 0.5f, 0, 1));
		}

		state = 0;
	}
}

void MapLayer::startFindPath(Label* info)
{
	if (startNode != nullptr && endNode != nullptr)
	{
		if (path != nullptr)
		{
			removeChild(path);
		}
		path = Path::create();

		pathList->createPathList(startNode, mapGraph, type);

		GraphNode<ListNode*, GraphNode<MapNode*, MapEdge*>*>* pathHeadNode = pathList->checkPath(endNode);

		GraphADJ<ListNode*, GraphNode<MapNode*, MapEdge*>*>* pathRear = pathHeadNode->firstADJ;

		path->drawPath(pathRear, startNode);

		addChild(path);

		if (pathHeadNode->firstADJ == nullptr)
		{
			info->setString(Tools::TFChinese("无法到达！"));
		}
		else
		{
			info->setString(Tools::TFChinese((string)"路程：" + Tools::formatDistance(int(pathHeadNode->data->distance)) + 
					"\n\n预计耗时：" + Tools::formatTime(int(pathHeadNode->data->time))));
		}
	}
	else if (startNode == nullptr)
	{
		info->setString(Tools::TFChinese("未选择起点！"));
	}
	else if (endNode == nullptr)
	{
		info->setString(Tools::TFChinese("未选择终点！"));
	}
}

void MapLayer::update(float dt)
{
	if (state == 1)
	{
		startDrawNode->clear();
	}
	else if (state == 2)
	{
		endDrawNode->clear();
	}
}