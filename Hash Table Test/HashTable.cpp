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

	//this uses an array of TableEntrys, each node has a null pointer for chaining
	bucketArray = new TableEntry[capacity];
	
	//bucketArray[3].setFirstName("Lyndon");
	//bucketArray[3].setLastName("Jardine");
	//std::cout << bucketArray[3].getFirstName() << std::endl;

}
HashTable::~HashTable()
{
	//loop through each index of the bucketArray
	for (int i = 0; i < capacity; i++)
	{
		//if a non-empty node exists at that index
		if (bucketArray[i].getFirstName() != "")
		{
			//loop through the chain, deleting each node
			TableEntry* currentNode = bucketArray[i].getAddress();
			TableEntry* nextNode = currentNode;
			while (currentNode != NULL)
			{
				//move the next pointer to the next index
				nextNode = currentNode->getNext();
				delete currentNode;
				//move the now null pointer to the next node
				currentNode = nextNode;
			}
		}
	}

	//finally, delete the bucketArray
	delete bucketArray;
}

//previousNode is used for recursion, counter is used to check how far into the linked list you are.
void HashTable::nodeInsert(std::string firstNameKey, std::string lastName)
{
	//put the key through the hash function
	int hashIndex = hashFunction(firstNameKey);

	//check for a collision, if getFirstName is empty, there is no collision, also a key should not be empty
	if (bucketArray[hashIndex].getFirstName() == "")
	{

		//insert the values
		bucketArray[hashIndex].setFirstName(firstNameKey);
		bucketArray[hashIndex].setLastName(lastName);
	}
	else
	{
		//create a new node and chain it to the last node

		//access the entry's linked list
		TableEntry* currentEntry = bucketArray[hashIndex].getAddress();

		//if the node at the index isnt already pointing to a next node
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
		//std::cout << "Expanding array: " << std::endl;
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

	//this throws an exception
	//delete oldArray;
}

//might consider changing the return type
TableEntry* HashTable::nodeSearch(std::string searchFirstName)
{
	//put the name you are searching for into the hash function
	int searchKey = hashFunction(searchFirstName);

	//check if the index the key matches contains the name you are searching for

	//pointer pointing to the node, default is NULL so if no node is found, NULL is returned
	TableEntry* foundNode = NULL;
	std::string test = bucketArray[searchKey].getFirstName();
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

void HashTable::editLastName(std::string firstNameKey, std::string newLastName)
{
	//use the search function
	TableEntry* nodeToEdit = nodeSearch(firstNameKey);
	nodeToEdit->setLastName(newLastName);
}


bool HashTable::nodeDelete(std::string firstNameKey)
{
	//repeat the same search process for finding the node
	
	TableEntry* nodeToDelete = NULL;
	//previousAddress is used if the node you want to delete is in a chain
	TableEntry* previousAddress = NULL;

	//hash what was passed in
	int deleteKey = hashFunction(firstNameKey);

	//check if the first node at the index is the node you are trying to delete
	if (bucketArray[deleteKey].getFirstName() == firstNameKey)
	{
		//have the delete pointer point to the first node
		nodeToDelete = bucketArray[deleteKey].getAddress();
	}
	//check if a second node at that index exists
	else if (bucketArray[deleteKey].getNext() != NULL)
	{
		TableEntry* currentNode = bucketArray[deleteKey].getAddress();
		while (currentNode != NULL && nodeToDelete == NULL)
		{
			if (currentNode->getFirstName() == firstNameKey)
			{
				nodeToDelete = currentNode;
			}
			//this is in an else so the previousNode pointer stays the same if a match was found
			else
			{
				//keep track of the previous node, it needs to point to the current node's next pointer
				previousAddress = currentNode;
				currentNode = currentNode->getNext();
			}
			
		}

	}


	//DELETING THE NODE
	//if a match was found, go through the process to delete the entry
	if (nodeToDelete != NULL)
	{
		//if a linked list is present, theres 3 possible delete cases 
		//1: you are deleting the first node - the bucketArray pointer needs to be updated to point to the deleted node's next address
		//2: you are deleting a middle node - the previous node's next address needs to be updated to point to the current node's next address
		//3: you are deleting an end node - the previous node's next address needs to be changed to NULL
		//(forgot this)4: deleting a first node with no next node
		
		//1: first node - there is a next node but no previous node
		if (nodeToDelete->getNext() != NULL && previousAddress == NULL)
		{
			//std::cout << "Deleting start node with a chain" << std::endl;
			//the way i am deleting a starting node with a next node is:
			//1: the values of the next node are copied into the starting node
			//2: the next node is deleted, this doesnt break the chain since the starting 
			
			//save the position of the starting node
			previousAddress = nodeToDelete;
			//mode the nodeToDelete pointer to the next node
			nodeToDelete = nodeToDelete->getNext();

			//manually copy the values, would be easier if the bucketArray was an array of pointers
			bucketArray[deleteKey].setFirstName(previousAddress->getNext()->getFirstName());
			bucketArray[deleteKey].setLastName(previousAddress->getNext()->getLastName());
			//have the starting node point to the node after the node you are deleting
			bucketArray[deleteKey].setNext(nodeToDelete->getNext());

			//delete the node
			delete nodeToDelete;
			
		}
		//2: middle node - there is a next address AND a previous address
		else if (nodeToDelete->getNext() != NULL && previousAddress != NULL)
		{
			//std::cout << "Deleting a middle node";
			//have the previous node point to the node after the node you are deleting
			previousAddress->setNext(nodeToDelete->getNext());
			delete nodeToDelete;

		}
		//3: last node - there is a previous address but no next address
		else if (nodeToDelete->getNext() == NULL && previousAddress != NULL)
		{
			//std::cout << "Deleting a end node" << std::endl;
			previousAddress->setNext(NULL);
			delete nodeToDelete;
		}
		//4: start node with no previous or next address
		else if (nodeToDelete->getNext() == NULL && previousAddress == NULL)
		{
			//std::cout << "Deleting a start node with no chain" << std::endl;
			//since this is an index in the array, you aren't able to delete it, so instead, its just resets everything to the default values
			bucketArray[deleteKey].setFirstName("");
			bucketArray[deleteKey].setLastName("");
			bucketArray[deleteKey].setNext(NULL);
			
		}

		//the delete succeeded
		return true;
	}
	else
	{
		//the delete failed
		return false;
	}
	
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

	//std::cout << "hash key generated: " << keySum << std::endl;
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
				
				//create pointer to move through the list
				TableEntry* currentNode = bucketArray[i].getNext();

				while (currentNode != NULL)
				{
					std::cout << " -> " << currentNode->getFirstName() << " " << currentNode->getLastName();
					currentNode = currentNode->getNext();
					//std::cout << "," << currentNode->getFirstName() << " " << currentNode->getLastName();
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
