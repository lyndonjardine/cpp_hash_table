#pragma once
#include "TableEntry.h"
#include <string>
#include<list>

class HashTable
{
private:

	//capacity is the maximum number of nodes that can be stored in the hashmap
	int capacity;
	//size is the amount of elements stored in the table
	int size = 0;
	
	//list containing each bucket
	//std::list<TableEntry> *myHashTable;
	TableEntry* bucketArray;

public:
	//function takes a string as a key and returns the hashed key to use as an index
	HashTable(int capacity);

	//standard hash table functions
	//insert takes in the firstName and lastName, the firstName is the key
	void nodeInsert(std::string firstNameKey, std::string lastName);

	//for expanding the table when a size to capacity ratio is reached
	void expand(int capacity, int size);

	//for shrinking the table when a capacity to size ratio is reached
	void shrink(int capacity, int size);

	///Returns a pointer to the table entry, this probably isnt the best implementation of a search
	TableEntry* nodeSearch(std::string searchFirstName);

	void nodeDelete(std::string firstNameKey);

	int hashFunction(std::string key);

	//function loops through each index/chain displaying all data, probably shouldn't be run on a large hash table
	void displayHash();
};