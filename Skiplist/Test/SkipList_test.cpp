#include "SkipList.h"
#include <gtest.h>
using namespace std;

//    |--------------- SkipListNode tests -----------------|

TEST(SkipListNode, SkipListNode_Default_Constructor) {
	EXPECT_NO_THROW(SkipListNode<int> n);
}

TEST(SkipListNode, SkipListNode_Init_Constructor) {
	
	EXPECT_NO_THROW(SkipListNode<string> a("data", 1));
}


TEST(SkipListNode, SkipListNode_Copy_Constructor) {
	SkipListNode<string> a("data", 1);
	EXPECT_NO_THROW(SkipListNode<string> n(a));
}

TEST(SkipListNode, SkipListNode_Assignment_Operator) {
	SkipListNode<string> n;
	SkipListNode<string> a("data", 1);
	EXPECT_NO_THROW(n = a);
}

TEST(SkipListNode, SkipListNode_EQ_Operator) {
	SkipListNode<string> n("data", 1);
	SkipListNode<string> a(n);
	EXPECT_EQ(true, n == a);
}

TEST(SkipListNode, SkipListNode_NE_Operator) {
	SkipListNode<string> n("data", 1);
	SkipListNode<string> a("data", 2);
	EXPECT_EQ(true, n != a);
}

TEST(SkipListNode, SkipListNode_is_Last) {
	SkipListNode<int> a;
	SkipListNode<string> b("data", 123);
	EXPECT_EQ(true, a.isEnd());
	EXPECT_EQ(true, b.isEnd());
}

//    |---------------- SkipList tests --------------------|

TEST(SkipList, SkipList_Default_Constructor) {
	EXPECT_NO_THROW(SkipList<string> l);
}

TEST(SkipList, SkipList_Init_Constructor) {
	EXPECT_NO_THROW(SkipList<string> l("test"));
}

TEST(SkipList, SkipList_Copy_Constructor) {
	SkipList<int> a(12);
	a.insert(75);
	a.insert(33);
	EXPECT_NO_THROW(SkipList<int> l(a));
}

TEST(SkipList, SkipList_INSERT) {
	SkipList<int> l(2);
	EXPECT_NO_THROW(l.insert(3));
}

TEST(SkipList, SkipList_FIND) {
	SkipList<int> l;
	l.insert(3);
	l.insert(44);
	l.insert(72);
	EXPECT_NO_THROW(l.find(3));
	EXPECT_NO_THROW(l.find(88));
	EXPECT_EQ(true, l.find(3));
	EXPECT_EQ(false, l.find(88));
}

TEST(SkipList, SkipList_REMOVE) {
	SkipList<int> l(3);
	l.insert(44);
	l.insert(72);
	l.insert(45);
	int size = l.getSize();
	EXPECT_NO_THROW(l.remove(44));
	EXPECT_EQ(true, size - 1 == l.getSize());
	EXPECT_EQ(false, l.find(44));
	l.insert(44);
	EXPECT_NO_THROW(l.find(44));
	EXPECT_EQ(true, l.find(44));
	EXPECT_EQ(true, size == l.getSize());

}

TEST(SkipList, SkipList_Assignment_Operator) {
	SkipList<string> n;
	SkipList<string> a("data");
	EXPECT_NO_THROW(n = a);
}

TEST(SkipList, SkipList_EQ_Operator) {
	SkipList<string> n("data");
	SkipList<string> a(n);
	EXPECT_EQ(true, n == a);
	n.insert("abc");
	a = n;
	EXPECT_EQ(true, a == n);
}

TEST(SkipList, SkipList_NE_Operator) {
	SkipList<string> n("data");
	SkipList<string> a("not data");
	EXPECT_EQ(true, n != a);
	n.insert("abc");
	a = n;
	n.insert("abd");
	a.insert("zzz");
	EXPECT_EQ(true, n != a);
}

