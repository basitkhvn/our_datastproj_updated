#pragma once
#include <iostream>

const int HTSize = 10;

int quadraticProbe(int t, int k) {
    return (t + k*k)%HTSize;
}

void insert(int key, int hash[]) {
    int t = key % HTSize; // we will first do the hashfunction
    int k = 0;

    while (hash[t] != 0) { 
        t = quadraticProbe(t, ++k); // quadratic probe
    }
    // insert key if available
    hash[t] = key; 
}

void print(int hash[]) {
    for (int i = 0; i < HTSize; i++) {
       cout << i << ": " << hash[i] << std::endl;
    }
}

