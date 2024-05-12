#include "Dheap.h"
#include <gtest.h>


TEST(Dheap, Dheap_Default_Constructor) {
	EXPECT_NO_THROW(Dheap<int> h(3));
}

TEST(Dheap, Dheap_Init_Value_Constructor) {
	EXPECT_NO_THROW(Dheap<int>(123, 3));
}

TEST(Dheap, Dheap_Init_Vec_Constructor) {
	std::vector<int> vec = { 10,9,7,6,3,9,8,6 };
	EXPECT_NO_THROW(Dheap<int> h(vec, 3));
}

TEST(Dheap, Dheap_Copy_Constructor) {
	Dheap<int> h(123, 1);
	EXPECT_NO_THROW(Dheap<int>heap(h));
}

//TEST(Dheap, Dheap_Get_Level_Size_Ratio) {
//	Dheap<int> h(2);
//	EXPECT_NO_THROW(h.getLevelSizeRatio());
//	std::vector<int> ratio = *(h.getLevelSizeRatio());
//	for (int i = 0; i < ratio.size(); i++) {
//		std::cout << ratio[i] << " ";
//	}
//	std::cout << std::endl;
//}

TEST(Dheap, Dheap_Insert) {
	Dheap<int> h(3);
	for (int i = 0; i < 40; i++) {
		EXPECT_NO_THROW(h.insert(i));
	}
}

TEST(Dheap, Dheap_Find) {
	Dheap<int> h(3);
	for (int i = 0; i < 100; i++) {
		h.insert(i);
	}
	EXPECT_NO_THROW(h.find(5));
	EXPECT_EQ(true, -1 != h.find(5));
}

TEST(Dheap, Dheap_Pop) {
	Dheap<int> h(3);
	for (int i = 0; i <= 100; i++) {
		h.insert(i);
	}
	EXPECT_NO_THROW(h.pop());
	for (int i = 99; i >= 0; i--) {
		EXPECT_EQ(true, i == h.pop());
	}
	EXPECT_EQ(true, h.isEmpty());
}

TEST(Dheap, Dheap_Is_Empty) {
	Dheap<int> h(3);
	EXPECT_EQ(true, h.isEmpty());
	for (int i = 0; i < 100; i++) {
		h.insert(i);
	}
	EXPECT_NO_THROW(h.isEmpty());
	EXPECT_EQ(false, h.isEmpty());
	for (int i = 99; i >= 0; i--) {
		EXPECT_EQ(true, i == h.pop());
	}
	EXPECT_EQ(true, h.isEmpty());
}

//TODO: fix memory issue
//TEST(Dheap, Dheap_Is_Full) {
//	Dheap<int> h(10);
//	h.maxSize(1000);
//	for (int i = 0; i < 1000; i++) {
//		h.insert(i);
//		//1000<->2000: макс для int (??? утечка/избыточное использование памяти ???)
//	}
//	Dheap<int> heap(10);
//	EXPECT_NO_THROW(h.isFull());
//	EXPECT_EQ(true, h.isFull());
//	h.pop();
//	EXPECT_EQ(false, h.isFull());
//}

TEST(Dheap, Dheap_EQ_Operator) {
	Dheap<int> h(3), heap(3), b(2);
	EXPECT_NO_THROW(h == heap);
	EXPECT_EQ(true, h == heap);
	EXPECT_EQ(false, h == b);

	for (int i = 0; i < 100; i++) {
		h.insert(i);
	}
	EXPECT_EQ(false, h == heap);
	for (int i = 99; i >= 0; i--) {
		h.pop();
	}
	EXPECT_EQ(true, h == heap);
}

TEST(Dheap, Dheap_NE_Operator) {
	Dheap<int> h(3), heap(3), b(2);
	EXPECT_NO_THROW(h != heap);
	EXPECT_EQ(false, h != heap);
	EXPECT_EQ(true, h != b);

	for (int i = 0; i < 100; i++) {
		h.insert(i);
	}
	EXPECT_EQ(true, h != heap);
	for (int i = 99; i >= 0; i--) {
		h.pop();
	}
	EXPECT_EQ(false, h != heap);
}

TEST(Dheap, Dheap_Assignment_Operator) {
	Dheap<int> h(3), heap(3, 3), b(2);
	EXPECT_NO_THROW(h = heap);
	EXPECT_EQ(true, h == heap);

	for (int i = 0; i < 100; i++) {
		h.insert(i);
	}
	EXPECT_EQ(true, h != heap);
	heap = h;
	EXPECT_EQ(true, h == heap);
}