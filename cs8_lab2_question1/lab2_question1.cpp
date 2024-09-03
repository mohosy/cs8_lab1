//Mohammad Shirmohammadi 
//10404080 
//lab2 question 1


#include <iostream>
#include <fstream>
using namespace std;

void multi(int** m1, int m1_rows, int m1_cols, int** m2, int m2_rows, int m2_cols, int** &m3) {
//Precondition: the number of rows in sthe first matrix needs to be equal to the number of columns in the second
//Postcondition: m3 is created, which is the final result in matrix form
    if (m1_cols != m2_rows) {
        cout << "Matrices cannot be multiplied!" << endl;
        return;
    }

    // Initialize the result matrix
    m3 = new int*[m1_rows];
    for (int i = 0; i < m1_rows; ++i) {
        m3[i] = new int[m2_cols]();
    }

    for (int i = 0; i < m1_rows; ++i) {
        for (int j = 0; j < m2_cols; ++j) {
            for (int k = 0; k < m2_rows; ++k) {
                m3[i][j] += m1[i][k] * m2[k][j];
            }
        }
    }
}

void print(int** matrix, int rows, int cols) {
//Preconditon: the nmber of rows and the number of columbs > 0 
//Postcondition: the final result is printed in properly spaced format 
    for (int i = 0; i < rows; ++i) {
        for (int j = 0; j < cols; ++j) {
            cout << setw(2) << matrix[i][j] << " ";
        }
        cout << endl;
    }
}

int** readMatrix(const string &filename, int &rows, int &cols) {
//Precondition: the file cannot be NULL
//Postcondition: matrix 1 and matrix two are formed based on the two inputted files 
    ifstream file(filename);
    if (!file) {
        cerr << "Error opening file: " << filename << endl;
        exit(1);
    }

    // Read the dimensions of the matrix
    file >> rows >> cols;

    // Create the dynamic array for the matrix
    int** matrix = new int*[rows];
    for (int i = 0; i < rows; ++i) {
        matrix[i] = new int[cols];
    }

    // Read the matrix values
    for (int i = 0; i < rows; ++i) {
        for (int j = 0; j < cols; ++j) {
            file >> matrix[i][j];
        }
    }

    file.close();
    return matrix;
}

int main() {
    int m1_rows, m1_cols, m2_rows, m2_cols;
    string file1, file2;

    // Prompt user for file names
    cout << "Enter the file name for Matrix 1: ";
    cin >> file1;
    cout << "Enter the file name for Matrix 2: ";
    cin >> file2;

    // Read matrices from files
    int** m1 = readMatrix(file1, m1_rows, m1_cols);
    int** m2 = readMatrix(file2, m2_rows, m2_cols);

    // Matrix to store the multiplication result
    int** m3 = nullptr;

    // Perform multiplication
    multi(m1, m1_rows, m1_cols, m2, m2_rows, m2_cols, m3);

    // Print matrices and result
    cout << "< Matrix 1 >" << endl;
    print(m1, m1_rows, m1_cols);
    cout << endl;

    cout << "< Matrix 2 >" << endl;
    print(m2, m2_rows, m2_cols);
    cout << endl;

    if (m3 != nullptr) {
        cout << "< Multiplication Matrix >" << endl;
        print(m3, m1_rows, m2_cols);
    }

    // Clean up dynamic memory
    for (int i = 0; i < m1_rows; ++i) {
        delete[] m1[i];
    }
    delete[] m1;

    for (int i = 0; i < m2_rows; ++i) {
        delete[] m2[i];
    }
    delete[] m2;

    if (m3 != nullptr) {
        for (int i = 0; i < m1_rows; ++i) {
            delete[] m3[i];
        }
        delete[] m3;
    }

    return 0;
}

