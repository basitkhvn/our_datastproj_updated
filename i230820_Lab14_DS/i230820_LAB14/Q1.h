#pragma once
#include <iostream>
using namespace std;


class Node {

public:
	int value;
	int key;
	Node* right;

	Node(int k , int v) {
		key = k;
		value = v;
		right = nullptr;

	}



};

class HashTable {
	int capacity;
	Node** arr_of_linkedlist;

	int hash_function(int key) {

		return key % capacity;
	}

public:

	HashTable(int c) {
		capacity = c;
		arr_of_linkedlist = new Node * [capacity];
		for (int i = 0; i < capacity; i++) {
			arr_of_linkedlist[i] = nullptr;
		}
	}


	void insert(int key, int value) {
		int index = hash_function(key);
		//return index

		Node* newnode = new Node(key, value);
		newnode->right = arr_of_linkedlist[index];
		arr_of_linkedlist[index] = newnode;

		return;
	}

	void remove(int key) {
		int index = hash_function(key);
		Node* temp = arr_of_linkedlist[index];
		Node* back = nullptr;


		while (temp != nullptr && temp->key != key) {
			back = temp;
			temp = temp->right;
		}


		if (temp == nullptr) {
			cout << "Key is not found , try again LMAO" << endl;
			return;
		}


		if (back == nullptr) {
			arr_of_linkedlist[index] = temp->right;
		}
		else {
			back->right = temp->right;
		}

		delete temp;
		cout << key << " is removed" << endl;
	}


	int search(int key) {
		int index = hash_function(key);
		Node* temp = arr_of_linkedlist[index];

		while (temp != nullptr) {
			//key is found
			if (temp->key == key)
				return temp->value;
			temp = temp->right; // Traverse to next
		}

		return -1; // Key not found
	}



};
