#include <iostream>
#include "Q1.h"
#include "Q2.h"
using namespace std;

//int main() {
   // HashTable ht(10);
//
//    ht.insert(1, 100);
//    ht.insert(2, 200);
//    ht.insert(11, 300); 
//
//    ht.remove(1);  
//    ht.remove(11); 
//    ht.remove(5);  
//
//    cout<<ht.search(2);
//    return 0;
//}
//


int main() {
    int hashTable[10] = { 0 }; 

    insert(5, hashTable);
    insert(15, hashTable);
    insert(25, hashTable);
    insert(35, hashTable);
    insert(45, hashTable);

    print(hashTable);

    return 0;
}