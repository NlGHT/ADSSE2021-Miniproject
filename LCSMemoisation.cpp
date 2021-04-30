#include <vector>
#include <iostream>
#include <algorithm>
#include <tuple>
#include <chrono>
#include <random>

using namespace std;
using namespace std::chrono;

#define LEFT 1
#define UP 3
#define DIAG 2

int** GenArray(const int m, const int n) {
    int** arr = new int*[m];
    for (int i = 0; i < m; i++)
        arr[i] = new int[n];

    return arr;
}

void Delete2DArray(int** arr, const int m) {
    for (int i = 0; i < m; i++)
        delete[] arr[i];

    delete[] arr;
}

tuple<int**, int**> LCSLength(int* X, const int m, int* Y, const int n) {
    int** c = GenArray(m, n);
    int** b = GenArray(m, n);

    for (int i = 1; i < m; i++)
        c[i][0] = 0;

    for (int j = 0; j < n; j++)
        c[0][j] = 0;

    for (int i = 1; i < m; i++) {
        for (int j = 0; j < n; j++) {
            if (X[i] == Y[j])
            {
                c[i][j] = c[i - 1][j - 1] + 1;
                b[i][j] = DIAG;
            }
            else if (c[i - 1][j - 1] >= c[i][j - 1])
            {
                c[i][j] = c[i - 1][j];
                b[i][j] = UP;
            }
            else
            {
                c[i][j] = c[i][j - 1];
                b[i][j] = LEFT;
            }
        }
    }

    return {c, b};
}

void PrintLCS(int** b, int* X, const int i, const int j)
{
    if (i == 0 || j == 0)
        return;

    if (b[i][j] == DIAG)
    {
        PrintLCS(b, X, i - 1, j - 1);
        cout << "[" << X[i] << "]";
    }
    else if (b[i][j] == UP)
    {
        PrintLCS(b, X, i - 1, j);
    }
    else
    {
        PrintLCS(b, X, i, j - 1);
    }
}

void PrintArray(int* arr, const int size) {
    cout << arr[0];
    for (int i = 1; i < size; i++)
        cout << "," << arr[i];
    cout << endl;
}

void Print2DArray(int** arr, const int m, const int n) {
    for (int i = 0; i < m; ++i) {
        for (int j = 0; j < n; ++j) {
            cout << arr[i][j];
        }
        cout << endl;
    }
    cout << endl;
}


int main(int argc, char *argv[])
{
    const int m = 100;
    const int n = 100;
    int X[m];
    int Y[n];
    random_device rd;
    mt19937 mt(rd());
    uniform_int_distribution<int> dist(1, 21);

    for (int i = 0; i < m; i++)
        X[i] = dist(mt);
    for (int i = 0; i < n; i++)
        Y[i] = dist(mt);

    auto start = high_resolution_clock::now();
    tuple<int**, int**> out = LCSLength(X, m, Y, n);
    auto timed = duration_cast<milliseconds>(
            high_resolution_clock::now() - start).count();
    int** c = get<0>(out);
    int** b = get<1>(out);

    cout << "First array:" << endl;
    PrintArray(X, m);
    cout << "Second array:" << endl;
    PrintArray(Y, n);
    cout << endl;

    cout << "Matrix of counts:" << endl;
    Print2DArray(c, m, n);
    cout << "Matrix of arrows:" << endl;
    Print2DArray(b, m, n);

    cout << "Longest common subsequence is length: " << c[m-1][n-1] << endl;

    cout << "Longest common sequence:" << endl;

    cout << "*Memoisation* Time taken: " << timed << "ms" << endl;
    PrintLCS(b, X, m-1, n-1);

    Delete2DArray(b, m);
    Delete2DArray(c, m);
    // delete[] X;
    // delete[] Y;
    return 0;
}
