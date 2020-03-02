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
	int hashIndex = hashFunction(firstNameKey);

	//use the hashed key as the index of the list

	//check for a collision, if getFirstName is empty, there is no collision, also a key should not be empty
	if (bucketArray[hashIndex].getFirstName() == "")
	{

		//insert the values
		bucketArray[hashIndex].setFirstName(firstNameKey);
		bucketArray[hashIndex].setLastName(lastName);
	}
	else
	{
		std::cout << "CHAINING THE KEY: " << firstNameKey << std::endl;
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

	//increase the size
	size++;

	//check if the size has reached 70% of the capacity, call the expand function, remember to typecast to float, otherwise the decimal for percentage will get rounded up/down
	if ((((float)size / (float)capacity) * 100) > 70)
	{
		std::cout << "EXPANDING, CAPACITY: " << capacity << " SIZE: " << size << std::endl;
		expand(capacity, size);
	}

}

void HashTable::expand(int oldCapacity, int oldSize)
{
	//double the capacity
	this->capacity = oldCapacity * 2;
	//reset size
	size = 0;

	//creates a pointer to hold the old array, YOU MAY NEED TO DELETE THIS
	TableEntry *oldArray = bucketArray;
	//have the original array pointer point to null
	bucketArray = NULL;
	//create a new table with the new capacity and have the bucketArray pointer point to it
	bucketArray = new TableEntry[capacity];
	
	
	int newHashKey = 0;
	//loop through each element of the old table
	for (int i = 0; i < oldCapacity; i++)
	{
		std::cout << "Index: " << i << " :   ";
		//if a first node exists, otherwise skip to next bucket
		if (oldArray[i].getFirstName() != "")
		{
			//hash the new key, this uses the new capacity when hashing
			//pass in the corrosponging
			//newHashKey = hashFunction(oldArray[i].getFirstName());
			
			//DONT DO THIS, IF THERE IS A (UNLIKLY) COLLISION, THE OLD DATA WOULD GET OVERWRITTEN!!!!
			//bucketArray[newHashKey].setFirstName(oldArray[i].getFirstName());
			//bucketArray[newHashKey].setLastName(oldArray[i].getLastName());

			//pass it through the nodeInsert function so collisions are handled
			nodeInsert(oldArray[i].getFirstName(), oldArray[i].getLastName());
			
			//check if there is a node chained to this index
			if (oldArray[i].getNext() != NULL)
			{
				//DONT DO THIS
				//bucketArray[newHashKey].setNext(oldArray->getNext());
				
				//have a pointer point to the next address
				TableEntry* currentNode = oldArray[i].getNext();

				//loop through the old chain, inserting the old keys into the new table, (nodes will chained if needed by the insert function)
				//not sure if both conditions are needed
				while (currentNode != NULL)
				{
					//insert the data as a new node
					nodeInsert(currentNode->getFirstName(), currentNode->getLastName());

					//move to the next pointer
					currentNode = currentNode->getNext();
				}

			}
			
		}
		else
		{
			std::cout << "Index " << i << " is Empty" << std::endl;
		}
	}
}

//might consider changing the return type
TableEntry* HashTable::nodeSearch(std::string searchFirstName)
{
	//put the name you are searching for into the hash function
	int searchKey = hashFunction(searchFirstName);

	//check if the index the key matches contains the name you are searching for

	//pointer pointing to the node, default is NULL so if no node is found, NULL is returned
	TableEntry* foundNode = NULL;
	if (bucketArray[searchKey].getFirstName() == searchFirstName)
	{
		// the node is found directly at the index
		foundNode = bucketArray[searchKey].getAddress();
	}
	else if (bucketArray[searchKey].getNext() != NULL)
	{
		//search the chained nodes for a matching key
		TableEntry* currentNode = bucketArray[searchKey].getNext();
		//search until the end is reached or a matching key is found
		while (currentNode != NULL && foundNode == NULL)
		{
			//if a matching key is found, this also exits the loop
			if (currentNode->getFirstName() == searchFirstName)
			{
				//this changes the null pointer
				foundNode = currentNode;
			}

			//move to the next node
			currentNode = currentNode->getNext();
		}
	}

	if (foundNode == NULL)
	{
		std::cout << "Error: no node with that key exists!" << std::endl;
	}

	//this is null if no matching key was found
	return foundNode;
}
void HashTable::nodeDelete(std::string firstNameKey)
{
	

	
}
//check if the size to capacity ratio is small enough to shrink, this means when the capacity is below 30%? it should be shrinked
void HashTable::shrink(int capacity, int size)
{

}

int HashTable::hashFunction(std::string key)
{
	//for this hash function,
	//1 sum up the ascii values for the string
	int keySum = 0;
	for (int i = 0; i < key.length(); i++)
	{
		//type cast to int
		keySum += (int)key[i];
	}

	//add the length of the key string just for some extra randomness
	
	keySum += key.length();
	//keySum = (keySum * 3) / 2;

	std::cout << "hash key generated: " << keySum << std::endl;
	//return the remainder of the sum divided by the capacity, 
	//this puts the key in the range to be an index of the table
	return (keySum % capacity);
}

void HashTable::displayHash()
{
	for (int i = 0; i < capacity; i++)
	{
		std::cout << "Index: " << i << " :   ";
		//if a first node exists, otherwise skip to next bucket
		if (bucketArray[i].getFirstName() != "")
		{
			std::cout << bucketArray[i].getFirstName() << " " << bucketArray[i].getLastName();
			//if a next node exists
			if (bucketArray[i].getNext() != NULL)
			{
				std::cout << "," << bucketArray[i].getNext()->getFirstName() << " " << bucketArray[i].getNext()->getLastName();
				//create pointer to move through the list
				TableEntry* currentNode = bucketArray[i].getNext();
				while (currentNode->getNext() != NULL)
				{
					currentNode = currentNode->getNext();
					std::cout << "," << currentNode->getFirstName() << " " << currentNode->getLastName();
				}
				std::cout << std::endl;
			}
			else
			{
				std::cout << std::endl;
			}
		}
		else
		{
			std::cout << "Index Empty" << std::endl;
		}
		
	}


}
