#pragma once
#include <iostream>
#include <fstream>
using namespace std;

const int MAX_NAME_SIZE = 100; // Maximum size for names

class AVLTree {
public:
    char rootFile[MAX_NAME_SIZE]; // Path to the root node file

    AVLTree() {
        for (int i = 0; i < MAX_NAME_SIZE; i++) {
            rootFile[i] = '\0';
        }
    }

    void createTreeFromCSV(const char* csvFile) {
        ifstream file(csvFile);
        if (!file.is_open()) {
            cerr << "Error: Could not open file " << csvFile << endl;
            return;
        }

        char cell[MAX_NAME_SIZE] = { 0 };
        char ch;
        int charCount = 0;

        while (file.get(ch)) {
            if (ch == ',' || ch == '\n') {
                cell[charCount] = '\0'; // Null-terminate
                if (charCount > 0) {
                    insert(cell); // Insert the cell value into the tree
                }
                charCount = 0; // Reset for the next cell
            }
            else {
                if (charCount < MAX_NAME_SIZE - 1) {
                    cell[charCount++] = ch;
                }
                else {
                    cerr << "Error: Cell size exceeded!" << endl;
                    return;
                }
            }
        }

        if (charCount > 0) {
            cell[charCount] = '\0'; // Handle the last cell
            insert(cell);
        }

        file.close();
    }

    void printTree() const {
        if (rootFile[0] == '\0') {
            cout << "Tree is empty." << endl;
            return;
        }
        printFromFile(rootFile);
    }

private:
    void createNodeFile(const char* name, char* fileName) {
        // Generate the file name
        int i = 0;
        while (name[i] != '\0' && i < MAX_NAME_SIZE - 4) {
            fileName[i] = name[i];
            i++;
        }
        fileName[i++] = '.';
        fileName[i++] = 't';
        fileName[i++] = 'x';
        fileName[i++] = 't';
        fileName[i] = '\0';

        // Create the file with initial data
        ofstream outFile(fileName);
        if (outFile.is_open()) {
            outFile << name << '\n'; // Write the node name
            outFile << '\n'; // Placeholder for the left child
            outFile << '\n'; // Placeholder for the right child
            outFile.close();
        }
        else {
            cerr << "Error: Could not create file " << fileName << endl;
        }
    }

    void insert(const char* name) {
        if (rootFile[0] == '\0') {
            createNodeFile(name, rootFile);
        }
        else {
            insertIntoTree(name, rootFile);
        }
    }

    void insertIntoTree(const char* name, const char* currentFile) {
        ifstream inFile(currentFile);
        if (!inFile.is_open()) {
            cerr << "Error: Could not open file " << currentFile << endl;
            return;
        }

        // Read current node details
        char nodeName[MAX_NAME_SIZE];
        char leftFile[MAX_NAME_SIZE] = { 0 };
        char rightFile[MAX_NAME_SIZE] = { 0 };

        inFile.getline(nodeName, MAX_NAME_SIZE);
        inFile.getline(leftFile, MAX_NAME_SIZE);
        inFile.getline(rightFile, MAX_NAME_SIZE);
        inFile.close();

        // Compare and decide where to insert
        if (compareStrings(name, nodeName) < 0) { // Go to the left
            if (leftFile[0] == '\0') {
                createNodeFile(name, leftFile);
                updateFile(currentFile, nodeName, leftFile, rightFile);
            }
            else {
                insertIntoTree(name, leftFile);
            }
        }
        else { // Go to the right
            if (rightFile[0] == '\0') {
                createNodeFile(name, rightFile);
                updateFile(currentFile, nodeName, leftFile, rightFile);
            }
            else {
                insertIntoTree(name, rightFile);
            }
        }
    }

    void updateFile(const char* fileName, const char* nodeName, const char* leftFile, const char* rightFile) {
        ofstream outFile(fileName, ios::trunc);
        if (outFile.is_open()) {
            outFile << nodeName << '\n';
            outFile << leftFile << '\n';
            outFile << rightFile << '\n';
            outFile.close();
        }
        else {
            cerr << "Error: Could not update file " << fileName << endl;
        }
    }

    int compareStrings(const char* str1, const char* str2) const {
        int i = 0;
        while (str1[i] != '\0' && str2[i] != '\0') {
            if (str1[i] < str2[i]) return -1;
            if (str1[i] > str2[i]) return 1;
            i++;
        }
        if (str1[i] == '\0' && str2[i] == '\0') return 0;
        return (str1[i] == '\0') ? -1 : 1;
    }

    void printFromFile(const char* fileName) const {
        ifstream inFile(fileName);
        if (!inFile.is_open()) {
            cerr << "Error: Could not open file " << fileName << endl;
            return;
        }

        char nodeName[MAX_NAME_SIZE];
        char leftFile[MAX_NAME_SIZE];
        char rightFile[MAX_NAME_SIZE];

        inFile.getline(nodeName, MAX_NAME_SIZE);
        inFile.getline(leftFile, MAX_NAME_SIZE);
        inFile.getline(rightFile, MAX_NAME_SIZE);
        inFile.close();

        cout << "Node: " << nodeName << " (File: " << fileName << ")" << endl;
        if (leftFile[0] != '\0') {
            cout << " Left: ";
            printFromFile(leftFile);
        }
        if (rightFile[0] != '\0') {
            cout << " Right: ";
            printFromFile(rightFile);
        }
    }
};
