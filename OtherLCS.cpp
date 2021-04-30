#include <iostream>
#include <random>
#include <algorithm>
#include <chrono>

using namespace std;
using namespace std::chrono;

int LCSLength2(int* x, int xLen, int* y, int yLen) {
    if (xLen == 0 || yLen == 0)  {
        return 0;
    }
    else if (x[xLen - 1] == y[yLen - 1]) {
		return LCSLength2(x, xLen-1, y, yLen-1) + 1;
	}
    else {
		return max(LCSLength2(x, xLen, y, yLen-1), LCSLength2(x, xLen-1, y, yLen));
	}
}

void PrintArray(int* arr, const int size) {
    cout << arr[0];
    for (int i = 1; i < size; i++)
        cout << "," << arr[i];
    cout << endl;
}


int main()
{
    const int m = 15;
    const int n = 15;
    // 40x40
    // int X[] = {9,12,11,5,8,10,6,16,3,18,13,3,14,4,6,12,7,9,12,9,2,3,14,21,4,15,3,20,20,18,14,14,4,19,12,5,18,9,5,6};
    // int Y[] = {16,2,5,16,6,16,7,8,6,7,1,12,4,14,8,10,1,7,5,4,19,10,13,2,14,6,14,18,11,16,5,17,3,4,11,16,7,21,13,4};

    // 25x25
    // int X[] = {21,4,1,2,4,21,14,1,14,8,12,9,2,18,3,1,12,17,21,11,6,21,16,21,21};
    // int Y[] = {20,13,13,7,9,5,16,16,15,17,5,19,21,3,17,6,9,10,18,11,4,19,10,18,3};

    // 22x22
    // int X[] = {4,21,14,1,14,8,12,9,2,18,3,1,12,17,21,11,6,21,16,21,21};
    // int Y[] = {9,5,14,16,14,17,5,19,21,3,17,6,9,10,18,11,4,19,10,18,3};

    // 20x15
    // int X[] = {5,7,10,6,8,3,4,14,16,13,7,13,21,12,20,18,8,2,1,4};
    // int Y[] = {10,6,1,6,17,13,2,17,21,12,15,11,8,3,16};

    // 15x15
    int X[] = {3,4,14,16,13,7,13,21,12,20,18,8,2,1,4};
    int Y[] = {10,6,1,6,17,13,2,17,21,12,15,11,8,3,16};

    // 30x30
    // int X[] = {13,3,14,4,6,12,7,9,12,9,2,3,14,21,4,15,3,20,20,18,14,14,4,19,12,5,18,9,5,6};
    // int Y[] = {1,12,4,14,8,10,1,7,5,4,19,10,13,2,14,6,14,18,11,16,5,17,3,4,11,16,7,21,13,4};

    // 20x20
    // int X[] = {2,3,14,21,4,15,3,20,20,18,14,14,4,19,12,5,18,9,5,6};
    // int Y[] = {19,10,13,2,14,6,14,18,11,16,5,17,3,4,11,16,7,21,13,4};

    // 20x10
    // int X[] = {11,20,18,11,10,19,19,9,6,13,10,17,20,1,18,15,18,7,13,12};
    // int Y[] = {4,8,11,20,8,5,16,2,21,12};

    // 10x10
    // int X[] = {10,17,20,1,18,15,18,7,13,12};
    // int Y[] = {4,8,11,20,8,5,16,2,21,12};

    cout << "First array:" << endl;
    PrintArray(X, m);
    cout << "Second array:" << endl;
    PrintArray(Y, n);

    auto start = high_resolution_clock::now();
    int out = LCSLength2(X, m, Y, n);
    auto timed = duration_cast<milliseconds>(
            high_resolution_clock::now() - start).count();

    cout << "*Recursive* Time taken: " << timed << "ms" << endl;
    cout << endl;
    cout << out << endl;

    return 0;
}
