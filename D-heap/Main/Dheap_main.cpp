#include "Dheap.h"
#include <iostream>
using namespace std;

int main() {
    Dheap<int> dHeap(3);

    for (int i = 1; i <= 10; i++) {
        dHeap.insert(i);
    }

    std::cout << dHeap << std::endl;

    std::cout << "Extracted max element: " << dHeap.pop() << std::endl;

    std::cout << dHeap << std::endl;
}
