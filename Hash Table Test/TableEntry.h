#pragma once
#include <string>

class TableEntry
{
	//firstName is the key
	std::string firstName;
	std::string lastName;
	TableEntry* nextEntry;



public:
	TableEntry();
	TableEntry(std::string firstName, std::string lastName);
	std::string getFirstName();
	std::string getLastName();
	void setFirstName(std::string tempFirstName);
	void setLastName(std::string tempLastName);
	
	TableEntry *getAddress();
	TableEntry *getNext();
	void setNext(TableEntry* nextEntry);
};