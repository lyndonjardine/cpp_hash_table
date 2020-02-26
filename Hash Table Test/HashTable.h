#pragma once
#include "TableEntry.h"
#include <string>
#include<list>

class HashTable
{
private:

	//capacity is the maximum number of nodes that can be stored in the hashmap
	int capacity;
	
	//list containing each bucket
	//std::list<TableEntry> *myHashTable;
	TableEntry* bucketArray;

public:
	//function takes a string as a key and returns the hashed key to use as an index
	HashTable(int capacity);

	//standard hash table functions
	//insert takes in the firstName and lastName, the firstName is the key
	void nodeInsert(std::string firstNameKey, std::string lastName);

	//node search is void, might want to change it to string or TableEntry
	void nodeSearch(std::string searchFirstName);

	void nodeDelete(std::string firstNameKey);

	int hashFunction(std::string key);
};