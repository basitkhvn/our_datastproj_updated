#include <iostream>
#include <fstream>
#include "LinkedLIST.h"
#include "AVL.h"



const int MAX_ROWS = 100;       // Maximum number of rows
const int MAX_COLUMNS = 10;     // Maximum number of columns per row
const int MAX_CELL_SIZE = 100;  // Maximum size of each cell

void readfile(const char* t) {

    const char* filename = t;  // Name of the CSV file
    std::ifstream file(filename);     // Open the file

    if (!file.is_open()) {
        std::cerr << "Error: Could not open the file " << filename << std::endl;
        return;
    }

    char table[MAX_ROWS][MAX_COLUMNS][MAX_CELL_SIZE] = { {{0}} }; // 3D array to store CSV cells
    int row_count = 0;
    int col_count = 0;
    int char_count = 0;

    char ch;
    while (file.get(ch)) { // Read the file character by character
        if (ch == ',' || ch == '\n') {
            // End of a cell
            table[row_count][col_count][char_count] = '\0'; // Null-terminate the cell
            col_count++;
            char_count = 0;

            // End of a row
            if (ch == '\n') {
                row_count++;
                col_count = 0;
                if (row_count >= MAX_ROWS) {
                    std::cerr << "Error: Row limit exceeded!" << std::endl;
                    return;
                }
            }
        }
        else {
            // Add the character to the current cell
            if (char_count < MAX_CELL_SIZE - 1) {
                table[row_count][col_count][char_count++] = ch;
            }
            else {
                std::cerr << "Error: Cell size limit exceeded!" << std::endl;
                return;
            }
        }
    }

    // Handle the last cell if the file does not end with a newline
    if (char_count > 0) {
        table[row_count][col_count][char_count] = '\0';
        row_count++;
    }

    file.close(); // Close the file

    // Output the parsed CSV content
    std::cout << "Parsed CSV content:\n";
    for (int i = 0; i < row_count; ++i) {
        for (int j = 0; j < MAX_COLUMNS && table[i][j][0] != '\0'; ++j) {
            std::cout << table[i][j];
            if (j < MAX_COLUMNS - 1 && table[i][j + 1][0] != '\0') {
                std::cout << " | ";
            }
        }
        std::cout << '\n';
    }

}
int main() {/*
   const char* t = "testset.csv";
    readfile(t);
    char* root = nullptr;
    ReadInLinkedList(root, t);
    cout << endl << root << endl;*/
    AVLTree avlTree;

    const char* csvFile = "testset.csv"; // Specify your CSV file
    avlTree.createTreeFromCSV(csvFile); // Build the AVL tree from CSV

    std::cout << "AVL Tree Structure:" << std::endl;
    avlTree.printTree(); // Print the AVL tree structure

    return 0;
}
