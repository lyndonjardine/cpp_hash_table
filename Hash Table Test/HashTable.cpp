#include "stdafx.h"
#include <string>
#include "HashTable.h"
#include <iostream>




HashTable::HashTable(int capacity)
{
	//define capacity
	this->capacity = capacity;
	//create the hashtable to hold the buckets
	//myHashTable = new std::list<TableEntry>[capacity];

	//attempting an array instead, this uses the default constructor
	bucketArray = new TableEntry[capacity];
	
	//bucketArray[3].setFirstName("Lyndon");
	//bucketArray[3].setLastName("Jardine");
	//std::cout << bucketArray[3].getFirstName() << std::endl;

}

//previousNode is used for recursion, counter is used to check how far into the linked list you are.
void HashTable::nodeInsert(std::string firstNameKey, std::string lastName)
{
	//put the key through the hash function
	//int hashIndex = hashFunction(firstNameKey);
	int hashIndex = 0;
	//use the hashed key as the index of the list
	//figure out why this doesnt work
	//myHashTable[hashIndex];

	//check for a collision, if getFirstName is empty, there is no collision
	if (bucketArray[hashIndex].getFirstName() == "")
	{

		//insert the values
		bucketArray[hashIndex].setFirstName(firstNameKey);
		bucketArray[hashIndex].setLastName(lastName);
	}
	else
	{

		//access the entry's linked list
		TableEntry* currentEntry = bucketArray[hashIndex].getAddress();

		if (currentEntry->getNext() == NULL)
		{
			//the next node is null, you can insert the new one there
			//create a new node with the values needed
			TableEntry *newEntry = new TableEntry(firstNameKey, lastName);
			//set the current node to point to the new node
			currentEntry->setNext(newEntry);
		}
		else
		{
			//loop to the end of the linked list
			while (currentEntry->getNext() != NULL)
			{
				currentEntry = currentEntry->getNext();
			}
			//at this point, current->next() == NULL, so we want to allocate a new node
			//create a new node with the values needed
			TableEntry *newEntry = new TableEntry(firstNameKey,lastName);
			//set the current node to point to the new node
			currentEntry->setNext(newEntry);
		}

	}

	

}

//might consider changing the return type
void HashTable::nodeSearch(std::string searchFirstName)
{

}
void HashTable::nodeDelete(std::string firstNameKey)
{

}

int HashTable::hashFunction(std::string key)
{
	//for this hash function,
	//1 sum up the ascii values for the string
	//multiply by 10?
	int keySum = 0;
	for (int i = 0; i < key.length(); i++)
	{
		//type cast to int
		keySum += key[i];
	}

	//add the length of the key string just for some extra randomness
	keySum += key.length();

	std::cout << "hash key generated: " << keySum << std::endl;
	//return the remainder of the sum divided by the capacity, 
	//this puts the key in the range to be an index of the table
	return (keySum % capacity);
}

