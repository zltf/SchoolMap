#ifndef PATH_LIST_H_
#define PATH_LIST_H_

#include"MapGraph.h"

struct ListNode
{
	MapNode* node;

	float distance;

	float time;

	bool finished;
};

class PathList:public MyGraph<ListNode*, GraphNode<MapNode*, MapEdge*>*>
{
public:
	PathList() { startNode = nullptr; trafficType = -1; }

	void createPathList(GraphNode<MapNode*, MapEdge*>* startNode, MapGraph* mapGraph, int trafficType);

	GraphNode<ListNode*, GraphNode<MapNode*, MapEdge*>*>* checkPath(GraphNode<MapNode*, MapEdge*>* endNode);

private:

	GraphNode<MapNode*, MapEdge*>* startNode;
	int trafficType;
};

#endif // !PATH_LIST_H_