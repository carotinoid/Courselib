#include "sort.h"
#include <fstream>
#include <iostream>
#include <string>

sortAlg::sortAlg()
{
    arr_size = 0;
    arr = new int[100]; // Each test case will be less than 100 values
}

using namespace std;

void sortAlg::printArray(ofstream &fout)
{
    string answer;
    for (int i = 0; i < arr_size - 1; i++)
        answer += to_string(arr[i]) + " ";
    answer += to_string(arr[arr_size - 1]);
    fout << answer << endl;
}

namespace customs
{
    template <typename T>
    static void swap(T &a, T &b)
    {
        T temp = a;
        a = b;
        b = temp;
    }
}


void sortAlg::bubbleSort(ofstream &fout)
{
    /////////////////////////////////////////////////////////
    //////////  TODO: Implement From Here      //////////////
    for(int i = 0; i < arr_size - 1; i++)
    {
        bool change = false;
        for(int j = arr_size - 1 - 1; j >= i; j--)
        {
            if(arr[j] > arr[j+1]) change = true, customs::swap(arr[j], arr[j + 1]);
        }
        if(change) printArray(fout);
    }
    ///////////      End of Implementation      /////////////
    /////////////////////////////////////////////////////////
}

void sortAlg::merge(int left, int middle, int right, bool &changed)
{
    /////////////////////////////////////////////////////////
    //////////  TODO: Implement From Here      //////////////
    // merge
    if(middle - left + 1 <= 0 or right- middle <= 0) return;
    int *left_arr = new int[middle - left + 1];
    int *right_arr = new int[right - middle];
    int left_num = middle - left + 1, right_num = right - middle;
    for(int i = 0; i < left_num; i++) left_arr[i] = arr[left + i];
    for(int i = 0; i < right_num; i++) right_arr[i] = arr[middle + 1 + i];
    int i = 0, j = 0, k = left;
    while(true)
    {
        if(k > right) break;
        if(i == left_num and j == right_num) break;
        else if(i == left_num and j != right_num) arr[k++] = right_arr[j++];
        else if(i != left_num and j == right_num) arr[k++] = left_arr[i++];
        else if(left_arr[i] < right_arr[j]) arr[k++] = right_arr[j++];
        else arr[k++] = left_arr[i++];
    }
    // check if the array has been changed
    for(int i = left; i <= middle; i++)
    {
        if(left_arr[i - left] != arr[i]) changed = true;
    }
    for(int i = middle + 1; i <= right; i++)
    {
        if(right_arr[i - (middle + 1)] != arr[i]) changed = true;
    }
    // delete
    delete[] left_arr;
    delete[] right_arr;

    ///////////      End of Implementation      /////////////
    /////////////////////////////////////////////////////////
}

void sortAlg::mergeSort(ofstream &fout, int left, int right)
{
    /////////////////////////////////////////////////////////
    //////////  TODO: Implement From Here      //////////////
    int size = 1;
    bool change = true;
    while(size < arr_size and change)
    {
        size *= 2;
        change = false;
        for(int i = left; i <= right; i += size)
        {
            merge(i, i + size / 2 - 1, min(i + size - 1, right), change);
        }
        if(change) printArray(fout);
    }
    ///////////      End of Implementation      /////////////
    /////////////////////////////////////////////////////////
}
