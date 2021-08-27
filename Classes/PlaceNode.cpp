#include<PlaceNode.h>

bool PlaceNode::init()
{
	DrawNode::init();

	return true;
}

void PlaceNode::drawNode(MapGraph* graph)
{
	for (GraphNode<MapNode*, MapEdge*>* gNode = graph->getHead()->nextNode; gNode != nullptr; gNode = gNode->nextNode)
	{
		MapNode* node = gNode->data;
		
		if (node->type == 1)
		{
			drawDot(node->position, 8, Color4F::Color4F(0.54f, 0.38f, 0.22f, 1));

			Label * name = Label::createWithTTF(Tools::TFChinese(node->name), "fonts/msyh.ttc", 20);
			name->setColor(Color3B::BLACK);
			name->setPosition(node->namePosition);

			addChild(name);
		}

		if (node->type == 2)
		{
			//drawDot(node->position, 3, Color4F::BLUE);
		}
	}
}