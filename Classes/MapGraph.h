#ifndef MAP_GRAPH_H_
#define MAP_GRAPH_H_

#include<string>
#include<fstream>
#include"cocos2d.h"
#include"MyGraph.h"
#include"MyQueue.h"

using namespace std;

USING_NS_CC;

struct MapNode
{
	int type;

	string name;

	Vec2 position;

	Vec2 namePosition;
};

struct MapEdge
{
	int level;

	float distance;

	string name;

	Vec2 namePosition;
};

class MapGraph: public MyGraph<MapNode*, MapEdge*>
{
public:
	MapGraph(string nodeFilePath, string edgeFilePath);

	float getDistance(MapNode* node1, MapNode* node2);

	static float getSpeed(int roadLevel, int trafficType);
	static float getTime(int roadLevel, int trafficType, float distance) { return distance / getSpeed(roadLevel, trafficType); }
	static bool canTraffic(int roadLevel, int trafficType) { return getSpeed(roadLevel, trafficType) != -1; }

	int mapWidth;
	int mapHeight;

private:

	MapGraph * loadNode(string filePath);
	MapGraph* loadEdge(string filePath);
};

#endif // !MAP_GRAPH_H_