#include <iostream>
#include <vector>

using Matrix = std::vector<std::vector<int>>;

Matrix matrixMultiply(const Matrix& A, const Matrix& B) {
    int n = A.size();
    int m = A[0].size();
    int p = B[0].size();

    Matrix result(n, std::vector<int>(p, 0));

    if (m != B.size()) {
        std::cout << "No se pueden multiplicar las matrices. Dimensiones incorrectas." << std::endl;
        return result;
    }

    if (n == 1 && m == 1 && p == 1) {
        result[0][0] = A[0][0] * B[0][0];
        return result;
    }

    int halfSize = n / 2;

    Matrix A11(halfSize, std::vector<int>(halfSize));
    Matrix A12(halfSize, std::vector<int>(halfSize));
    Matrix A21(halfSize, std::vector<int>(halfSize));
    Matrix A22(halfSize, std::vector<int>(halfSize));
    Matrix B11(halfSize, std::vector<int>(halfSize));
    Matrix B12(halfSize, std::vector<int>(halfSize));
    Matrix B21(halfSize, std::vector<int>(halfSize));
    Matrix B22(halfSize, std::vector<int>(halfSize));

    for (int i = 0; i < halfSize; i++) {
        for (int j = 0; j < halfSize; j++) {
            A11[i][j] = A[i][j];
            A12[i][j] = A[i][j + halfSize];
            A21[i][j] = A[i + halfSize][j];
            A22[i][j] = A[i + halfSize][j + halfSize];
            B11[i][j] = B[i][j];
            B12[i][j] = B[i][j + halfSize];
            B21[i][j] = B[i + halfSize][j];
            B22[i][j] = B[i + halfSize][j + halfSize];
        }
    }

    Matrix C11 = matrixAdd(matrixMultiply(A11, B11), matrixMultiply(A12, B21));
    Matrix C12 = matrixAdd(matrixMultiply(A11, B12), matrixMultiply(A12, B22));
    Matrix C21 = matrixAdd(matrixMultiply(A21, B11), matrixMultiply(A22, B21));
    Matrix C22 = matrixAdd(matrixMultiply(A21, B12), matrixMultiply(A22, B22));

    for (int i = 0; i < halfSize; i++) {
        for (int j = 0; j < halfSize; j++) {
            result[i][j] = C11[i][j];
            result[i][j + halfSize] = C12[i][j];
            result[i + halfSize][j] = C21[i][j];
            result[i + halfSize][j + halfSize] = C22[i][j];
        }
    }

    return result;
}

Matrix matrixAdd(const Matrix& A, const Matrix& B) {
    int n = A.size();
    int m = A[0].size();
    Matrix result(n, std::vector<int>(m));

    for (int i = 0; i < n; i++) {
        for (int j = 0; j < m; j++) {
            result[i][j] = A[i][j] + B[i][j];
        }
    }

    return result;
}

int main() {
    Matrix A = {{1, 2, 3, 4},
                {5, 6, 7, 8},
                {9, 10, 11, 12},
                {13, 14, 15, 16}};

    Matrix B = {{17, 18, 19, 20},
                {21, 22, 23, 24},
                {25, 26, 27, 28},
                {29, 30, 31, 32}};

    Matrix C = matrixMultiply(A, B);

    std::cout << "Resultado:" << std::endl;
    for (const auto& row : C) {
        for (int element : row) {
            std::cout << element << " ";
        }
        std::cout << std::endl;
    }

    return 0;
}

