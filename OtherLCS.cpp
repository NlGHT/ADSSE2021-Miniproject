#include <iostream>
#include <random>
#include <algorithm>

using namespace std;

int LCSLength(int* x, int xLen, int* y, int yLen, int* result) {
    if (xLen == 0 || yLen == 0)  {
        return 0;
    }
    else if (x[xLen - 1] == y[yLen - 1]) {
		return LCSLength(x, xLen-1, y, yLen-1, result) + 1;
	}
    else {
		return max(LCSLength(x, xLen, y, yLen-1, result), LCSLength(x, xLen-1, y, yLen, result));
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
    const int m = 10;
    const int n = 10;
    int X[m];
    int Y[n];
    int Result[m];
    // int X[] = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10};
    // int Y[] = {11, 12, 13, 14, 15, 16, 17, 18, 19, 20};
    random_device rd;
    mt19937 mt(rd());
    uniform_int_distribution<int> dist(1, 8);

    for (int i = 0; i < m; i++)
        X[i] = dist(mt);
    for (int i = 0; i < n; i++)
        Y[i] = dist(mt);

    cout << "First array:" << endl;
    PrintArray(X, m);
    cout << "Second array:" << endl;
    PrintArray(Y, n);

    int out = LCSLength(X, m, Y, n, Result);
    cout << endl;
    cout << out << endl;

    for (int i = m-1; i > 0; i--) {
        if (Result[i] == 1)
            cout << X[i];
    }
    cout << endl;

    return 0;
}
