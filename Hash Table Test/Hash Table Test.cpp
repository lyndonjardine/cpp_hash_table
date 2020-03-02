// Hash Table Test.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include "HashTable.h"
#include <iostream>



int main()
{
	HashTable myHashTable(10);
	
	//int myKey = myHashTable.hashFunction("Lyndon");
	//std::cout << "My Key: " << myKey << std::endl;
	myHashTable.nodeInsert("First", "Second");
	myHashTable.nodeInsert("Third", "Fourth");
	myHashTable.nodeInsert("Fifth", "Sixth");

	myHashTable.nodeInsert("Lyndon", "Jardine");
	myHashTable.nodeInsert("rsdrvf", "omiuon");
	myHashTable.nodeInsert("nxe", "dwr53");

	myHashTable.nodeInsert("asdf", "qwerty");
	myHashTable.nodeInsert("zxcv", "hfdcads");
	myHashTable.nodeInsert("iuimk", "sdxd");

	myHashTable.nodeInsert("gsiufonfvuw", "qwerty");
	myHashTable.nodeInsert("uiujpn", "hfdcads");
	myHashTable.nodeInsert("oijpb", "sdxd");

	//the search function returns a pointer to the node, this ends up being NULL if a node is not found.
	std::cout << "Lyndon's last name is: " << myHashTable.nodeSearch("Lyndon")->getLastName() << std::endl;

	//testing a chained key
	std::cout << "searching for nxe, result: " << myHashTable.nodeSearch("nxe")->getLastName() << std::endl;


	TableEntry* searchNode = NULL;
	searchNode = myHashTable.nodeSearch("this will return null");
	if (searchNode == NULL)
	{
		std::cout << "no node was found" << std::endl;
	}



	//myHashTable.displayHash();
    return 0;
}

