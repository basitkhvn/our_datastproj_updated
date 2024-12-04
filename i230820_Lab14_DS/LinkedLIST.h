#pragma once
#include<iostream>
#include <fstream>
using namespace std;

const int max_FNameSize = 20;


class Node {
public:
	char next[max_FNameSize];// next stores path of next file node
	char** data; // data stores the char arrays of the data in columns
	int dataLimit;  // number of data elements
	Node(int n):dataLimit(n){
		if(dataLimit>0){	
			data=new char*[dataLimit]; // to initialize the data array for data elements
			for(int i=0;i<dataLimit;i++){
				data[i] = new char[dataLimit];
				for(int j=0;j<dataLimit;j++){
					data[i][j] = '\0';
				}
			}
		}
		else{
			data = nullptr;
		}
        // initializing the nullified next address
		for (int j = 0;j < dataLimit;j++) {	
			next[j] = '\0';
		}
	}

	void addNext(char* arr){
		if(!arr){
			return;
		}
		for (int i = 0;i < max_FNameSize;i++) {
			next[i] = arr[i];
		}

	}

	void Data1(char* arr){
		if (!arr) {
			return;
		}
		for (int i = 0;i < max_FNameSize;i++) {
			data[0][i] = arr[i];
		}
	}
	
};




void ReadInLinkedList(char*& root,const char*& filename){

	std::ifstream file(filename);     // Open the file

	if (!file.is_open()) {
		std::cerr << "Error: Could not open the file " << filename << std::endl;
		return;
	}

	char* prevfile = nullptr; char* thisfile = nullptr;

	//reading the file
	char ch;
	int col_count = 0;
	int char_count = 0;
	char table[max_FNameSize];

	if(root!=nullptr){
		prevfile = new char[max_FNameSize];
		//add the root file name to previous file
		for (int i = 0;i < max_FNameSize;i++)
			prevfile[i] = root[i];
	}
	while (file.get(ch)) { // Read the file character by character
		
		if (ch == ',' || ch == '\n'|| ch=='\0') {
			// End of a cell
			for (int i = char_count;i < max_FNameSize;i++)
				table[i] = '\0';
			table[char_count] = '\0'; // Null-terminate the cell
			col_count++;
			//Code for making the current file name
			if (!thisfile)
				delete[] thisfile;
			thisfile = new char[max_FNameSize];
			for (int i = 0;i < max_FNameSize;i++)
				thisfile[i] = '\0';
			for (int i = 0;i < char_count&& i<max_FNameSize-4;i++) {
				thisfile[i] = table[i];
			}
			thisfile[char_count] = '.';
			thisfile[char_count+1] = 't';
			thisfile[char_count+2] = 'x';
			thisfile[char_count+3] = 't';
			
			//here comes the code of a file creation i.e., we will write data in current and add the current file address in the previousdata
				//for this file
				ofstream thisoutFile(thisfile);

				// Check if the file is open
				if (thisoutFile.is_open()) {
				// Write data to the file
					thisoutFile << table;
				// Close the file
					thisoutFile.close();

				 //std::cout << "Data written to file successfully." << std::endl;
				}
				//now to open the previous file and add this file to it
				if(!prevfile){
					root = thisfile;
				}
				else{
					std::ofstream outprevFile(prevfile, std::ios::app);

					// Check if the file is open
					if (outprevFile.is_open()) {
						// Write additional data to the file
						outprevFile << " , "<<thisfile<<endl;

						// Close the file
						outprevFile.close();

						//std::cout << "Data appended to file successfully." << std::endl;
					}
				}
			//the code to run on next iteration
			if (!prevfile)
				delete[]prevfile;
			prevfile=thisfile;
			thisfile = nullptr;
			char_count = 0;
			for (int i = 0;i < max_FNameSize;i++) {
				table[i] = '\0';
			}
		}
		else {
			// Add the character to the current cell
			if (char_count < max_FNameSize - 1) {
				table[char_count++] = ch;
			}
			else {
				std::cerr << "Error: Cell size limit exceeded!" << std::endl;
				return;
			}
		}
	}


	file.close(); // Close the file


}