#include"PathList.h"

void PathList::createPathList(GraphNode<MapNode*, MapEdge*>* startNode, MapGraph* mapGraph, int trafficType)
{
	if (this->startNode != startNode || this->trafficType != trafficType)
	{
		for (GraphNode<ListNode*, GraphNode<MapNode*, MapEdge*>*>* inode = head; inode->nextNode != nullptr;)
		{
			deleteVertex(inode->nextNode);
		}

		this->startNode = startNode;
		this->trafficType = trafficType;

		GraphNode<ListNode*, GraphNode<MapNode*, MapEdge*>*>* minDist;
		int finishedCount = 0;

		for (GraphNode<MapNode*, MapEdge*>* gNode = mapGraph->getHead()->nextNode; gNode != nullptr; gNode = gNode->nextNode)
		{
			ListNode* listNode = new ListNode;
			listNode->node = gNode->data;
			listNode->distance = -1;
			listNode->time = -1;
			listNode->finished = false;
			GraphNode<ListNode*, GraphNode<MapNode*, MapEdge*>*>* newNode= insertVertex(listNode);
			
			if (startNode == gNode)
			{
				listNode->finished = true;
				listNode->distance = 0;
				listNode->time = 0;
				insertEdge(newNode, newNode, gNode);

				minDist = newNode;
				finishedCount++;
			}
		}

		while (1)
		{
			if (finishedCount < count)//所有点都完成时跳出循环
			{
				GraphADJ<ListNode*, GraphNode<MapNode*, MapEdge*>*>* lastNode = minDist->firstADJ;

				for (GraphNode<ListNode*, GraphNode<MapNode*, MapEdge*>*>* node = head->nextNode; node != nullptr; node = node->nextNode)
				{
					if (!node->data->finished)//只处理未完成的节点
					{
						for (GraphADJ<MapNode*, MapEdge*>* gADJ = lastNode->info->firstADJ; gADJ != nullptr; gADJ = gADJ->nextADJ)
						{
							if (gADJ->graphNode->data == node->data->node && MapGraph::canTraffic(gADJ->info->level, trafficType))//如果 两个点之间有路，并且符合道路级别要求
							{
								float newDist = mapGraph->getDistance(node->data->node, lastNode->info->data) + minDist->data->distance;
								float newTime = minDist->data->time + MapGraph::getTime(gADJ->info->level, trafficType, mapGraph->getDistance(node->data->node, lastNode->info->data));

								if (newTime < node->data->time || node->data->time == -1)//如果新的路耗时更短
								{
									GraphADJ<ListNode*, GraphNode<MapNode*, MapEdge*>*>* minDistADJ = minDist->firstADJ;
									GraphADJ<ListNode*, GraphNode<MapNode*, MapEdge*>*>* nodeADJ = node->firstADJ;

									int count = 1;
									while (minDistADJ != nullptr)
									{
										minDistADJ = minDistADJ->nextADJ;
										count++;
									}

									if (nodeADJ == nullptr)
									{
										insertEdge(node, node, nullptr);
										nodeADJ = node->firstADJ;
										count--;
									}

									for (; count > 0; count--)
									{
										if (nodeADJ->nextADJ == nullptr)
										{
											insertEdge(node, node, nullptr);
										}
										else
										{
											nodeADJ = nodeADJ->nextADJ;
										}
									}

									minDistADJ = minDist->firstADJ;
									nodeADJ = node->firstADJ;

									nodeADJ->info = mapGraph->findNodeByData(node->data->node);
									nodeADJ = nodeADJ->nextADJ;

									while (minDistADJ != nullptr)
									{
										nodeADJ->info = minDistADJ->info;
										nodeADJ = nodeADJ->nextADJ;
										minDistADJ = minDistADJ->nextADJ;
									}

									node->data->time = newTime;
									node->data->distance = newDist;
								}
							}
						}
					}
				}

				for (GraphNode<ListNode*, GraphNode<MapNode*, MapEdge*>*>* node = head->nextNode; node != nullptr; node = node->nextNode)
				{
					if (!node->data->finished && node->data->time != -1)
					{
						minDist = node;
						break;
					}
				}

				for (GraphNode<ListNode*, GraphNode<MapNode*, MapEdge*>*>* node = head->nextNode; node != nullptr; node = node->nextNode)
				{
					if (!node->data->finished && node->data->time != -1)
					{
						if (node->data->time < minDist->data->time)
						{
							minDist = node;
						}
					}
				}

				minDist->data->finished = true;
				
				finishedCount++;
			}
			else
			{
				break;
			}
		}
	}
}

GraphNode<ListNode*, GraphNode<MapNode*, MapEdge*>*>* PathList::checkPath(GraphNode<MapNode*, MapEdge*>* endNode)
{
	for (GraphNode<ListNode*, GraphNode<MapNode*, MapEdge*>*>* node = getHead()->nextNode; node != nullptr; node = node->nextNode)
	{
		if (node->data->node == endNode->data)
		{
			return node;
		}
	}
}