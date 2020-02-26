// Hash Table Test.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include "HashTable.h"
#include <iostream>



int main()
{
	HashTable myHashTable(5);
	
	//int myKey = myHashTable.hashFunction("Lyndon");
	//std::cout << "My Key: " << myKey << std::endl;
	myHashTable.nodeInsert("First", "Second");
	myHashTable.nodeInsert("Third", "Fourth");
	myHashTable.nodeInsert("Fifth", "Sixth");
    return 0;
}

