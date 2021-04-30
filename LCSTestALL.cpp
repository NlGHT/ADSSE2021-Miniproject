#include <iostream>
#include <tuple>
#include <chrono>

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

// ----------- Recursive Implementation ----------- //
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

// ----------- Tabular Implementation ----------- //
tuple<int**, int**> LCSLength1(int* X, const int m, int* Y, const int n) {
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

// ----------- Print Longest Common Subsequence ----------- //
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

void runTest(const int m, const int n, int* X, int* Y, const int problem) {
    cout << "------ Problem " << problem << " ------" << endl;

    cout << "First array:" << endl;
    PrintArray(X, m);
    cout << "Second array:" << endl;
    PrintArray(Y, n);
    cout << endl;

    // Recursive Algorithm
    auto start = high_resolution_clock::now();
    int RecursiveResult = LCSLength2(X, m, Y, n);
    auto RecursiveTimed = duration_cast<milliseconds>(
            high_resolution_clock::now() - start).count();


    // Optimised algorithm
    start = high_resolution_clock::now();
    tuple<int**, int**> TabularResult = LCSLength1(X, m, Y, n);
    auto TabularTimed = duration_cast<milliseconds>(
            high_resolution_clock::now() - start).count();

    int** CountsTable = get<0>(TabularResult);
    int** ArrowTable  = get<1>(TabularResult);

    cout << "Matrix of counts:" << endl;
    Print2DArray(CountsTable, m, n);
    cout << "Matrix of arrows:" << endl;
    Print2DArray(ArrowTable, m, n);

    cout << "*Recursive* Longest common subsequence is length: " << RecursiveResult       << endl;
    cout << "*Recursive* Time taken: " << RecursiveTimed << "ms" << endl;
    cout << "*Tabular* Longest common subsequence is length: "   << CountsTable[m-1][n-1] << endl;
    cout << "*Tabular* Time taken: "   << TabularTimed   << "ms" << endl;

    cout << "Longest common sequence:" << endl;
    PrintLCS(ArrowTable, X, m-1, n-1);
    cout << endl;

    Delete2DArray(ArrowTable, m);
    Delete2DArray(CountsTable, m);

    cout << "------ End Problem " << problem << " ------" << endl;
}


int main(int argc, char *argv[])
{
    // ------ Shorter example ------
    int m = 20;
    int n = 12;
    int X[] = {11,20,18,11,10,19,19,9,6,13,10,17,20,1,18,15,18,7,13,12};
    int Y[] = {4,8,11,20,8,5,16,2,21,16,12,15};

    runTest(m, n, X, Y, 1);

    cout << endl;

    // ------ Longer example ------
    m = 20;
    n = 15;
    int X2[] = {11,20,18,11,10,19,19,9,6,13,10,17,20,1,18,15,18,7,13,12};
    int Y2[] = {4,20,19,20,8,5,16,18,21,15,13,15,14,12,12};

    runTest(m, n, X2, Y2, 2);

    cout << endl;

    // ------ 0 Example ------
    m = 10;
    n = 10;
    int X3[] = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10};
    int Y3[] = {11, 12, 13, 14, 15, 16, 17, 18, 19, 20};

    runTest(m, n, X3, Y3, 3);

    cout << endl;

    // ------ LONG example ------
    // m = 40;
    // n = 40;
    // int X4[] = {9,12,11,5,8,10,6,16,3,18,13,3,14,4,6,12,7,9,12,9,2,3,14,21,4,15,3,20,20,18,14,14,4,19,12,5,18,9,5,6};
    // int Y4[] = {16,2,5,16,6,16,7,8,6,7,1,12,4,14,8,10,1,7,5,4,19,10,13,2,14,6,14,18,11,16,5,17,3,4,11,16,7,21,13,4};

    // runTest(m, n, X4, Y4, 4);

    // cout << endl;


    return 0;
}
