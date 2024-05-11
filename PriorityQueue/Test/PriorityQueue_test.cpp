#include "PriorityQueue.h"
#include <gtest.h>
#include <string>
using namespace std;


/*                 PQNode Tests                      */
TEST(PQNode, PQNode_Default_constructor) {
	EXPECT_NO_THROW(PQNode<string> node);
}

TEST(PQNode, PQNode_Copy_constructor) {
	PQNode<string> node;
	EXPECT_NO_THROW(PQNode<string> n(node));
}

TEST(PQNode, PQNode_Init_constructor) {
	PQNode<string>* next = new PQNode<string>();
	EXPECT_NO_THROW(PQNode<string> n("data", 1, next));
}

TEST(PQNode, PQNode_GetNextPtr) {
	PQNode<string>* next = new PQNode<string>();
	PQNode<string> n("data", 1, next);
	EXPECT_EQ(next, n.getNextPtr());
}

TEST(PQNode, PQNode_SetNextPtr) {
	PQNode<string>* n = new PQNode<string>();
	PQNode<string>* next = new PQNode<string>();
	EXPECT_NO_THROW(n->setNextPtr(next));
	EXPECT_EQ(next, n->getNextPtr());
}

TEST(PQNode, PQNode_GetData) {
	PQNode<string> n("data", 1, nullptr);
	EXPECT_NO_THROW(n.getData());
	string data = "data";
	EXPECT_EQ(data, n.getData());
}

TEST(PQNode, PQNode_GetPriority) {
	PQNode<string> n("data", 1, nullptr);
	EXPECT_NO_THROW(n.getPriority());
	int p = 1;
	EXPECT_EQ(p, n.getPriority());
}

TEST(PQNode, PQNode_Set) {
	PQNode<string> n;
	EXPECT_NO_THROW(n.set("data", 1, nullptr));
	
	EXPECT_EQ("data", n.getData());
	EXPECT_EQ(1, n.getPriority());
	EXPECT_EQ(nullptr, n.getNextPtr());
}

TEST(PQNode, PQNode_EQ_Operator) {
	PQNode<string> n("data", 1, nullptr);
	PQNode<string> node("data", 1, nullptr);

	EXPECT_NO_THROW(n == node);

	EXPECT_EQ(true, n == node);
}

TEST(PQNode, PQNode_NE_Operator) {
	PQNode<string> n("data", 1, nullptr);
	PQNode<string> node("not data", 1, nullptr);

	EXPECT_NO_THROW(n != node);

	EXPECT_EQ(true, n != node);
}

TEST(PQNode, PQNode_Assignment_Operator) {
	PQNode<string> n("data", 1, nullptr);
	PQNode<string> node("not data", 1, nullptr);

	EXPECT_NO_THROW(n = node);

	EXPECT_EQ(true, n == node);
}

/*                 PriorityQueue Tests                   */

TEST(PriorityQueue, PriorityQueue_Default_Constructor) {
	EXPECT_NO_THROW(PriorityQueue<string> q);
}

TEST(PriorityQueue, PriorityQueue_Init_Constructor) {
	EXPECT_NO_THROW(PriorityQueue<string> q("data", 1));
}

TEST(PriorityQueue, PriorityQueue_Copy_Constructor) {
	PriorityQueue<string> q("data", 1);
	EXPECT_NO_THROW(PriorityQueue<string> queue(q));
}

TEST(PriorityQueue, PriorityQueue_Push) {
	PriorityQueue<string> q("data", 1);
	EXPECT_NO_THROW(q.push("abc", 2));
}

TEST(PriorityQueue, PriorityQueue_Peek) {
	PriorityQueue<string> q("data", 1);
	q.push("abc", 2);
	EXPECT_NO_THROW(q.peek());
	EXPECT_EQ("abc", q.peek());
}

TEST(PriorityQueue, PriorityQueue_Pop) {
	PriorityQueue<string> q("data", 1);
	q.push("abc", 2);
	EXPECT_NO_THROW(q.pop());
	EXPECT_EQ("data", q.peek());
}

TEST(PriorityQueue, PriorityQueue_IsEmpty) {
	PriorityQueue<string> q;
	EXPECT_NO_THROW(q.isEmpty());
	EXPECT_EQ(true, q.isEmpty());
	q.push("abc", 2);
	EXPECT_NO_THROW(q.isEmpty());
	EXPECT_EQ(false, q.isEmpty());
	q.pop();
	EXPECT_NO_THROW(q.isEmpty());
	EXPECT_EQ(true, q.isEmpty());
}

TEST(PriorityQueue, PriorityQueue_getSize) {
	PriorityQueue<string> q;
	EXPECT_NO_THROW(q.getSize());
	EXPECT_EQ(-1, q.getSize());
	q.push("abc", 2);
	EXPECT_NO_THROW(q.isEmpty());
	EXPECT_EQ(1, q.getSize());
	q.pop();
	EXPECT_NO_THROW(q.getSize());
	EXPECT_EQ(0, q.getSize());
}