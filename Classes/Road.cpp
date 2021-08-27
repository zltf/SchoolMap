#include"Road.h"
#include"MapGraph.h"
#include"Tools.h"

bool Road::init()
{
	DrawNode::init();

	return true;
}

void Road::drawRoad(MapGraph* graph)
{
	for (GraphNode<MapNode*, MapEdge*>* gNode = graph->getHead()->nextNode; gNode != nullptr; gNode = gNode->nextNode)
	{
		for (GraphADJ<MapNode*, MapEdge*>* adj = gNode->firstADJ; adj != nullptr; adj = adj->nextADJ)
		{
			int rodeWidth = 5;
			Color4F color = Color4F::WHITE;

			switch (adj->info->level)
			{
			case 1://汽车可走
				color = Color4F::Color4F(1, 0.8f, 0.5f, 1);
				break;
			case 2://汽车不可走，自行车可走
				break;
			case 3://自行车不可走
				rodeWidth = 3;
				break;
			case 4://台阶
				color = Color4F::GRAY;
				rodeWidth = 4;
				break;
			}

			drawSegment(gNode->data->position, adj->graphNode->data->position, rodeWidth, color);

			if (adj->info->name != "")
			{
				Label * name = Label::createWithTTF(Tools::TFChinese(adj->info->name), "fonts/msyh.ttc", 20);
				name->setColor(Color3B::BLACK);
				name->setPosition(adj->info->namePosition);

				addChild(name);
			}
		}
	}
}