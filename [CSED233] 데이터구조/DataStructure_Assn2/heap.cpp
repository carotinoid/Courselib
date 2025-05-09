#include "heap.h"
#include <iostream>
#include <string>

using namespace std;

string PriorityQueue::printPQ()
{
    string answer;
    for (int i = 0; i < size; i++)
        answer += to_string(heap[i].value) + " ";
    return answer;
}

bool PriorityQueue::insert(int priority, int value)
{
    /////////////////////////////////////////////////////////
    //////////  TODO: Implement From Here      //////////////
    for(int i = 0; i < size; i++) {
        if(heap[i].priority == priority) return 0;
    }
    heap[size].priority = priority;
    heap[size].value = value;
    int idx = size;
    while(heap[(idx-1)/2].priority < heap[idx].priority) {
        swap(heap[(idx-1)/2], heap[idx]);
        idx = (idx - 1) / 2;
    }
    size++;
    return 1;
    ///////////      End of Implementation      /////////////
    /////////////////////////////////////////////////////////
}

bool PriorityQueue::removeMax()
{
    /////////////////////////////////////////////////////////
    //////////  TODO: Implement From Here      //////////////
    if(empty()) return 0;
    if(size == 1) {
        size --;
        return 1;
    }
    else {
        size--;
        swap(heap[0], heap[size]);
        int idx = 0;
        // int num = 0;
        // while(size >= (1<<num)) num++;
        // num--; (1<<(num)) - 1
        while(idx < size) {
            int left_value = -999999;
            int right_value = -999999;
            bool left = 2*idx + 1 < size;
            bool right = 2*idx + 2 < size;
            left_value = heap[2*idx + 1].priority;
            right_value = heap[2*idx + 2].priority;
            if(left and right) { 
                if(left_value >= right_value)  {
                    swap(heap[idx], heap[2*idx+1]);
                    idx = 2*idx + 1;
                }
                else {
                    swap(heap[idx], heap[2*idx + 2]);
                    idx = 2*idx + 2;
                }
            } 
            else if(left and !right) {
                swap(heap[idx], heap[2*idx + 1]);
                idx = 2*idx + 1;
            }
            else if(!left and right) {
                swap(heap[idx], heap[2*idx + 2]);
                idx = 2*idx + 2;
            }
            else break;
        }
        return 1;
    }
    ///////////      End of Implementation      /////////////
    /////////////////////////////////////////////////////////
}

pq_element PriorityQueue::getMax()
{
    /////////////////////////////////////////////////////////
    //////////  TODO: Implement From Here      //////////////
    return heap[0];
    ///////////      End of Implementation      /////////////
    /////////////////////////////////////////////////////////
}

bool PriorityQueue::empty()
{
    /////////////////////////////////////////////////////////
    //////////  TODO: Implement From Here      //////////////
    return !size;
    ///////////      End of Implementation      /////////////
    /////////////////////////////////////////////////////////
}

bool PriorityQueue::changeMax(int target)
{
    /////////////////////////////////////////////////////////
    //////////  TODO: Implement From Here      //////////////
    if(empty()) return 0;
    int targetidx = 0;
    bool find = false;
    for(; targetidx < size; targetidx++) {
        if(heap[targetidx].value == target) {
            find = true;
            break;
        }
    }
    if(!find) return 0;
    heap[targetidx].priority = heap[0].priority + 1;
    heap[targetidx].value = heap[0].value + 1;
    int idx = targetidx;
    while(heap[(idx-1)/2].priority < heap[idx].priority) {
        swap(heap[(idx-1)/2], heap[idx]);
        idx = (idx - 1) / 2;
    }
    return 1;
    ///////////      End of Implementation      /////////////
    /////////////////////////////////////////////////////////
}

/////////////////////////////////////////////////////////
//////////  You can implement any other functions ////////

///////////      End of Implementation      /////////////
/////////////////////////////////////////////////////////
