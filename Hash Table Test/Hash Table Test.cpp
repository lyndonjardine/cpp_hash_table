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

	myHashTable.nodeInsert("fsvdfv", "nhdf");
	myHashTable.nodeInsert("rsdrvf", "omiuon");
	myHashTable.nodeInsert("nxe", "dwr53");

	myHashTable.nodeInsert("asdf", "qwerty");
	myHashTable.nodeInsert("zxcv", "hfdcads");
	myHashTable.nodeInsert("iuimk", "sdxd");

	myHashTable.nodeInsert("gsiufonfvuw", "qwerty");
	myHashTable.nodeInsert("uiujpn", "hfdcads");
	myHashTable.nodeInsert("oijpb", "sdxd");

	myHashTable.displayHash();
    return 0;
}

