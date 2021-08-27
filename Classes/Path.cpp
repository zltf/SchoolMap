#include"Path.h"

bool Path::init()
{
	DrawNode::init();

	return true;
}

void Path::drawPath(GraphADJ<ListNode*, GraphNode<MapNode*, MapEdge*>*>* pathRear, GraphNode<MapNode*, MapEdge*>* startNode)
{
	GraphADJ<ListNode*, GraphNode<MapNode*, MapEdge*>*>* lastADJ = nullptr;
	for (GraphADJ<ListNode*, GraphNode<MapNode*, MapEdge*>*>* adj = pathRear; adj != nullptr; adj = adj->nextADJ)
	{
		if (lastADJ != nullptr&&startNode == lastADJ->info)
		{
			break;
		}
		if (lastADJ != nullptr)
		{
			drawSegment(adj->info->data->position, lastADJ->info->data->position, 5, Color4F::BLUE);
		}
		lastADJ = adj;
	}
}