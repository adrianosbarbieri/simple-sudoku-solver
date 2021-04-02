#include <iostream>
#include <array>
#include <chrono>
#include <fstream>

using MatrizSudoku = std::array<std::array<int, 9>, 9>;

std::array<int, 2> FindNext(const MatrizSudoku& ms)
{
    for (int i = 0; i < 9; i++) {
        for (int j = 0; j < 9; j++) {
            if (ms[i][j] == 0) {
                return { i, j };
            }
        }
    }

    return { -1, -1 };
}

bool IsPossibleRow(const MatrizSudoku& ms, int row, int value)
{
    for (int i = 0; i < 9; i++) {
        if (ms[row][i] == value) {
            return false;
        }
    }

    return true;
}

bool IsPossibleCol(const MatrizSudoku& ms, int col, int value)
{
    for (int i = 0; i < 9; i++) {
        if (ms[i][col] == value) {
            return false;
        }
    }

    return true;
}

bool IsPossibleSquare(const MatrizSudoku& ms, int x, int y, int value)
{
    int sqx;
    if (x < 3) {
        sqx = 0;
    } else if (x < 6) {
        sqx = 1;
    } else {
        sqx = 2;
    }

    int sqy;
    if (y < 3) {
        sqy = 0;
    } else if (y < 6) {
        sqy = 1;
    } else {
        sqy = 2;
    }

    for (int i = 0; i < 3; i++) {
        for (int j = 0; j < 3; j++) {
            if (ms[3 * sqx + i][3 * sqy + j] == value) {
                return false;
            }
        }
    }

    return true;
}

bool IsPossible(const MatrizSudoku& ms, int x, int y, int value)
{
    return IsPossibleCol(ms, y, value)
        && IsPossibleRow(ms, x, value)
        && IsPossibleSquare(ms, x, y, value);
}

bool Solve(MatrizSudoku& ms)
{
    auto [x, y] = FindNext(ms);

    if (x == -1) {
        return true;
    }

    for (int v = 1; v <= 9; v++) {
        if (IsPossible(ms, x, y, v)) {
            ms[x][y] = v;

            if (Solve(ms)) {
                return true;
            }

            ms[x][y] = 0;
        }
    }

    return false;
}

MatrizSudoku ReadFile(const std::string& file)
{
    MatrizSudoku ms;
    std::ifstream f(file);

    for (int i = 0; i < 9; i++) {
        for (int j = 0; j < 9; j++) {
            char c;
            f >> c;
            ms[i][j] = c - '0';
        }
    }

    return ms;
}

int main()
{
    using namespace std::chrono;

    MatrizSudoku ms = ReadFile("input.txt");

    auto ini = steady_clock::now();

    Solve(ms);

    auto end = steady_clock::now();

    std::cout << (end - ini).count() << '\n';

    for (int i = 0; i < 9; i++) {
        for (int j = 0; j < 9; j++) {
            std::cout << ms[i][j] << " ";
        }

        std::cout << '\n';
    }
}