#ifndef MY_GRAPH_H_
#define MY_GRAPH_H_

#include<iostream>

#include"MyQueue.h"

using namespace std;
//T为图节点存储数据类型，I为边存储数据类型
template<class T, class I>
struct GraphADJ;//声明存在

template<class T, class I>
struct GraphNode//顶点结构
{
	T data;//保存的数据
	int id;
	GraphNode<T, I>* nextNode;//下一个顶点，构成定点列表
	GraphADJ<T, I>* firstADJ;//第一个邻接点
};

template<class T, class I>
struct GraphADJ//邻接点结构
{
	I info;//边的信息
	GraphNode<T, I>* graphNode;//指向对应的邻接点
	GraphADJ<T, I>* nextADJ;//下一个邻接点
};

template<class T, class I>
class MyGraph
{
public:
	MyGraph();
	~MyGraph();

	GraphNode<T, I>* insertVertex(T t);
	void deleteVertex(GraphNode<T, I>* node);

	void insertEdge(GraphNode<T, I>* node1, GraphNode<T, I>* node2, I info);
	void deleteEdge(GraphNode<T, I>* node1, GraphNode<T, I>* node2);

	void traveDFS();//深度优先遍历
	void traveBFS();//广度优先遍历
	void DFSFrom(GraphNode<T, I>* node, bool* visited);//从某节点深度优先遍历
	void BFSFrom(GraphNode<T, I>* node, bool* visited);//从某节点广度优先遍历

	GraphNode<T, I>* findNodeById(int id);
	GraphNode<T, I>* findNodeByData(T data);
	GraphADJ<T, I>* firstADJ(GraphNode<T, I>* node);
	GraphADJ<T, I>* nextADJ(GraphNode<T, I>* node, GraphADJ<T, I>* lastAdj);

	int inDegree(GraphNode<T, I>* node);
	int outDegree(GraphNode<T, I>* node);
	int degree(GraphNode<T, I>* node);

	GraphNode<T, I>* getHead() { return head; }

	int getCount() { return count; }

protected:

	GraphNode<T, I>* head;

	int count;
};

template<class T, class I>
MyGraph<T, I>::MyGraph() :count(0)
{
	head = new GraphNode<T, I>;
	head->nextNode = nullptr;
}

template<class T, class I>
GraphNode<T, I>* MyGraph<T, I>::insertVertex(T t)
{
	GraphNode<T, I>* node = new GraphNode<T, I>;

	node->data = t;
	node->id = count+1;
	node->nextNode = head->nextNode;
	node->firstADJ = nullptr;

	head->nextNode = node;

	count++;

	return node;
}

template<class T, class I>
void MyGraph<T, I>::insertEdge(GraphNode<T, I>* node1, GraphNode<T, I>* node2, I info)
{
	GraphADJ<T, I>* adj = new GraphADJ<T, I>;

	adj->info = info;
	adj->graphNode = node2;
	adj->nextADJ = node1->firstADJ;

	node1->firstADJ = adj;
}

template<class T, class I>
void MyGraph<T, I>::traveDFS()
{
	bool* visited = new bool[count];

	for (int i = 0; i < count; i++)
	{
		visited[i] = false;
	}

	for (GraphNode<T, I>* node = head->nextNode; node != nullptr; node = node->nextNode)
	{
		if (visited[node->id] == false)
		{
			DFSFrom(node, visited);
		}
	}
}

template<class T, class I>
void MyGraph<T, I>::DFSFrom(GraphNode<T, I>* node, bool* visited)
{
	cout << node->data << ' ';
	visited[node->id] = true;

	for (GraphADJ<T, I>* adj = node->firstADJ; adj != nullptr; adj = adj->nextADJ)
	{
		if (visited[adj->graphNode->id] == false)
		{
			DFSFrom(adj->graphNode, visited);
		}
	}
}

template<class T, class I>
void MyGraph<T, I>::traveBFS()
{
	bool* visited = new bool[count];

	for (int i = 0; i < count; i++)
	{
		visited[i] = false;
	}

	BFSFrom(head->nextNode, visited);
}

template<class T, class I>
void MyGraph<T, I>::BFSFrom(GraphNode<T, I>* node, bool* visited)
{
	MyQueue<GraphNode<T, I>*> queue;

	cout << node->data << ' ';
	visited[node->id] = true;
	queue.append(node);

	while (!queue.isEmpty())
	{
		queue.getFront(node);
		queue.serve();
		for (GraphADJ<T, I>* adj = node->firstADJ; adj != nullptr; adj = adj->nextADJ)
		{
			if (visited[adj->graphNode->id] == false)
			{
				cout << adj->graphNode->data << ' ';
				visited[adj->graphNode->id] = true;
				queue.append(adj->graphNode);
			}
		}
	}
}

template<class T, class I>
GraphNode<T, I>* MyGraph<T, I>::findNodeById(int id)
{
	for (GraphNode<T, I>* inode = head->nextNode; inode != nullptr; inode = inode->nextNode)
	{
		if (inode->id == id)
		{
			return inode;
		}
	}
	return nullptr;
}

template<class T, class I>
GraphNode<T, I>* MyGraph<T, I>::findNodeByData(T data)
{
	for (GraphNode<T, I>* inode = head->nextNode; inode != nullptr; inode = inode->nextNode)
	{
		if (inode->data == data)
		{
			return inode;
		}
	}
	return nullptr;
}

template<class T, class I>
GraphADJ<T, I>* MyGraph<T, I>::firstADJ(GraphNode<T, I>* node)
{
	return node->firstADJ;
}

template<class T, class I>
GraphADJ<T, I>* MyGraph<T, I>::nextADJ(GraphNode<T, I>* node, GraphADJ<T, I>* lastAdj)
{
	for (GraphADJ<T, I>* adj = node->firstADJ; adj != nullptr; adj = adj->nextADJ)
	{
		if (adj == lastAdj)
		{
			return adj->nextADJ;
		}
	}
}

template<class T, class I>
int MyGraph<T, I>::inDegree(GraphNode<T, I>* node)
{
	int i = 0;
	for (GraphNode<T, I>* inode = head->nextNode; inode != nullptr; inode = inode->nextNode)
	{
		for (GraphADJ<T, I>* adj = inode->firstADJ; adj != nullptr; adj = adj->nextADJ)
		{
			if (adj->graphNode == node)
			{
				i++;
			}
		}
	}
	return i;
}

template<class T, class I>
int MyGraph<T, I>::outDegree(GraphNode<T, I>* node)
{
	int i = 0;
	for (GraphADJ<T, I>* adj = node->firstADJ; adj != nullptr; adj = adj->nextADJ)
	{
		i++;
	}

	return i;
}

template<class T, class I>
int MyGraph<T, I>::degree(GraphNode<T, I>* node)
{
	return inDegree(node) + outDegree(node);
}

template<class T, class I>
void MyGraph<T, I>::deleteVertex(GraphNode<T, I>* node)
{
	for (GraphNode<T, I>* inode = head->nextNode; inode != nullptr; inode = inode->nextNode)//先删除指向node的所有边
	{
		for (GraphADJ<T, I>* adj = inode->firstADJ; adj != nullptr;)
		{
			GraphADJ<T, I>* tadj = adj->nextADJ;

			if (adj->graphNode == node)
			{
				deleteEdge(inode, node);
			}

			adj = tadj;
		}
	}

	for (GraphADJ<T, I>* adj = node->firstADJ; adj != nullptr;)//再删除node指向的所有边
	{
		GraphADJ<T, I>* tadj = adj->nextADJ;

		deleteEdge(node, adj->graphNode);

		adj = tadj;
	}

	for (GraphNode<T, I>* inode = head; inode->nextNode != nullptr; inode = inode->nextNode)//删除节点
	{
		if (inode->nextNode == node)
		{
			GraphNode<T, I>* tempNode = node;
			inode->nextNode = node->nextNode;
			delete tempNode;
			tempNode = nullptr;
			return;
		}
		inode->nextNode->id--;
	}

	count--;
}

template<class T, class I>
void MyGraph<T, I>::deleteEdge(GraphNode<T, I>* node1, GraphNode<T, I>* node2)
{
	for (GraphNode<T, I>* inode = head->nextNode; inode != nullptr; inode = inode->nextNode)
	{
		if (inode == node1)
		{
			if (inode->firstADJ->graphNode == node2)//删除第一个邻接点
			{
				GraphADJ<T, I>* tempADJ = inode->firstADJ;
				inode->firstADJ = inode->firstADJ->nextADJ;
				delete tempADJ;
				tempADJ = nullptr;
			}
			else
			{
				for (GraphADJ<T, I>* adj = inode->firstADJ; adj->nextADJ != nullptr; adj = adj->nextADJ)
				{
					if (adj->nextADJ->graphNode == node2)
					{
						GraphADJ<T, I>* tempADJ = adj->nextADJ;
						adj->nextADJ = adj->nextADJ->nextADJ;
						delete tempADJ;
						tempADJ = nullptr;
					}
				}
			}
		}
	}
}

template<class T, class I>
MyGraph<T, I>::~MyGraph()
{
	for (GraphNode<T, I>* inode = head; inode->nextNode != nullptr;)
	{
		deleteVertex(inode->nextNode);
	}

	delete head;
	head = nullptr;
}

#endif // !MY_GRAPH_H_