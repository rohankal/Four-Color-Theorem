#include <iostream>
#include <stdexcept>
#include <vector>

template<class T>
class MinHeap {
public:
    MinHeap(int d) { this->D = d; }
    /* Constructor that builds a d-ary Min Heap
    This should work for any d >= 2,
    but doesn't have to do anything for smaller d.*/

    ~MinHeap() {}

    void add(T item, int priority) {
        heap.push_back(std::pair<T, int>(item, priority));
        trickleUp(heap.size() - 1);
    }
    /* adds the item to the heap, with the given priority. */

    const T& peek() const {
        if (this->heap.empty()) {
            throw std::out_of_range("Error");  // trying to peek when the heap is empty
        }
        return (this->heap).front().first;
    }
    /* returns the element with smallest priority.
    Break ties however you wish.
    Throws an exception if the heap is empty. */

    void remove() {
        if (this->isEmpty()) {
            throw std::out_of_range("Error");  // trying to remove when the heap is empty
        }
        heap[0] = heap.at(heap.size() - 1);
        heap.pop_back();
        trickleDown(0);
    }
    /* removes the element with smallest priority.
    Break ties however you wish.
    Throws an exception if the heap is empty. */

    bool isEmpty() { return this->heap.empty(); }
    /* returns true iff there are no elements on the heap. */

    void printHeap() {
        for (unsigned int i = 0; i < this->heap.size(); i++) {  // loop through entire heap and print each element
            std::cout << this->heap.at(i).second << " ";
        }
        std::cout << std::endl;
    }

    std::vector<std::pair<T, int>> vec() { return this->heap; }  // used for gtest provided on Piazza

private:
    int D;                                // d-ary heap
    std::vector<std::pair<T, int>> heap;  // vector to model a heap
    void trickleDown(int index) {
        std::vector<int> children;  // finding the children of a given index
        for (int i = 1; i <= this->D; i++) {
            if ((unsigned int)this->D * index + i >= heap.size()) {
                break;
            }
            children.push_back(this->D * index + i);
        }

        int minChild = index;

        int currentPriority;
        for (unsigned int i = 0; i < children.size();
             i++) {  // go through each of the children and determine the minimum child for swapping purposes
            currentPriority = this->heap[children[i]].second;
            if (currentPriority < this->heap[minChild].second) {
                minChild = children[i];
            }
        }
        if (minChild == index)
            return;
        if (minChild > 0
            && this->heap[index].second
                       > this->heap[minChild].second) {  // typical temp variable swap to maintain minheap structure
            std::pair<T, int> temp = this->heap[index];
            this->heap[index] = this->heap[minChild];
            this->heap[minChild] = temp;
            trickleDown(minChild);  // recursively trickle down from the location of the minimum child
        }
    }
    void trickleUp(int index) {
        int parent = (index - 1) / (this->D);  // finding the parent of a given index
        if (index == 0) {
            parent = -1;
        }
        if (index >= 0 && parent >= 0
            && this->heap[parent].second
                       > this->heap[index].second) {  // typical temp variable swap to maintain minheap structure
            std::pair<T, int> temp = this->heap[index];
            this->heap[index] = this->heap[parent];
            this->heap[parent] = temp;
            trickleUp(parent);
        }
    }
};