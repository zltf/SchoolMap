#include"MapGraph.h"
#include<iostream>
#include"Tools.h"

using namespace std;

MapGraph::MapGraph(string nodeFilePath, string edgeFilePath)
{
	loadNode(nodeFilePath);
	loadEdge(edgeFilePath);
}

MapGraph* MapGraph::loadNode(string filePath)
{
	ifstream ifile(filePath);

	string str;
	MyQueue<string>* strs;

	getline(ifile, str);

	strs = Tools::splitString(str, '|');

	string mapWidthStr, mapHeightStr;

	strs->getFront(mapWidthStr);
	strs->serve();

	strs->getFront(mapHeightStr);
	strs->serve();

	mapWidth = Tools::stringToInt(mapWidthStr);
	mapHeight = Tools::stringToInt(mapHeightStr);

	while (!ifile.eof())
	{
		MyQueue<string>* strs;

		getline(ifile, str);
		strs = Tools::splitString(str, '|');

		if (strs->getCount() >= 6)
		{
			MapNode* node = new MapNode;
			string type, name, positionX, positionY, namePositionX, namePositionY;

			strs->getFront(type);
			strs->serve();

			strs->getFront(name);
			strs->serve();

			strs->getFront(positionX);
			strs->serve();

			strs->getFront(positionY);
			strs->serve();

			strs->getFront(namePositionX);
			strs->serve();

			strs->getFront(namePositionY);
			strs->serve();
			
			node->type = Tools::stringToInt(type);
			node->name = name;
			node->position = Vec2(Tools::stringToInt(positionX), mapHeight - Tools::stringToInt(positionY));
			node->namePosition = Vec2(Tools::stringToInt(namePositionX), mapHeight - Tools::stringToInt(namePositionY));

			insertVertex(node);
		}
	}

	ifile.close();

	return this;
}

MapGraph* MapGraph::loadEdge(string filePath)
{
	ifstream ifile(filePath);

	string str;

	while (!ifile.eof())
	{
		MyQueue<string>* strs;

		getline(ifile, str);
		strs = Tools::splitString(str, '|');

		if (strs->getCount() >= 7)
		{
			MapEdge* edge = new MapEdge;
			string level, id1, id2, name = "", namePositionX, namePositionY, doubleTraffic;

			strs->getFront(level);
			strs->serve();

			strs->getFront(id1);
			strs->serve();

			strs->getFront(id2);
			strs->serve();

			strs->getFront(name);
			strs->serve();

			strs->getFront(namePositionX);
			strs->serve();

			strs->getFront(namePositionY);
			strs->serve();

			strs->getFront(doubleTraffic);
			strs->serve();

			GraphNode<MapNode*, MapEdge*>* node1 = findNodeById(Tools::stringToInt(id1));
			GraphNode<MapNode*, MapEdge*>* node2 = findNodeById(Tools::stringToInt(id2));

			edge->level = Tools::stringToInt(level);
			edge->name = name;
			edge->namePosition = Vec2(Tools::stringToInt(namePositionX), mapHeight - Tools::stringToInt(namePositionY));
			edge->distance =
				sqrt((node1->data->position.x - node2->data->position.x) * (node1->data->position.x - node2->data->position.x)
				+ (node1->data->position.y - node2->data->position.y) * (node1->data->position.y - node2->data->position.y))
				* (1500.0 / mapWidth);

			insertEdge(node1, node2, edge);

			if (Tools::stringToInt(doubleTraffic) == 1)
			{
				insertEdge(findNodeById(Tools::stringToInt(id2)), findNodeById(Tools::stringToInt(id1)), edge);
			}
		}
	}

	ifile.close();

	return this;
}

float MapGraph::getDistance(MapNode* node1, MapNode* node2)
{
	for (GraphADJ<MapNode*, MapEdge*>* adj = findNodeByData(node1)->firstADJ; adj != nullptr; adj = adj->nextADJ)
	{
		if (adj->graphNode->data == node2)
		{
			return adj->info->distance;
		}
	}

	return -1;
}

float MapGraph::getSpeed(int roadLevel, int trafficType)
{
	switch (roadLevel)
	{
	case 1://大路

		switch (trafficType)
		{
		case 0:
			return 1.3f;
			break;
		case 1:
			return 5;
			break;
		case 2:
			return 10;
			break;
		}

		break;
	case 2://汽车禁止通行

		switch (trafficType)
		{
		case 0:
			return 1.3f;
			break;
		case 1:
			return 4;
			break;
		case 2:
			return -1;
			break;
		}

		break;
	case 3://小路

		switch (trafficType)
		{
		case 0:
			return 1.1f;
			break;
		case 1:
			return -1;
			break;
		case 2:
			return -1;
			break;
		}

		break;
	case 4://楼梯

		switch (trafficType)
		{
		case 0:
			return 0.8f;
			break;
		case 1:
			return -1;
			break;
		case 2:
			return -1;
			break;
		}

		break;
	}

	return -1;
}