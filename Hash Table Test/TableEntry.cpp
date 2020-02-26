#include "stdafx.h"
#include "TableEntry.h"

TableEntry::TableEntry()
{
	firstName = "";
	lastName = "";
	nextEntry = NULL;
}



TableEntry::TableEntry(std::string firstNameTemp, std::string lastNameTemp)
{
	firstName = firstNameTemp;
	lastName = lastNameTemp;
	nextEntry = NULL;
}

std::string TableEntry::getFirstName()
{
	return firstName;
}
std::string TableEntry::getLastName()
{
	return lastName;
}


void TableEntry::setFirstName(std::string tempFirstName)
{
	firstName = tempFirstName;
}
void TableEntry::setLastName(std::string tempLastName)
{
	lastName = tempLastName;
}

TableEntry* TableEntry::getAddress()
{
	return this;
}
TableEntry* TableEntry::getNext()
{
	return this->nextEntry;
}
void TableEntry::setNext(TableEntry* next)
{
	this->nextEntry = next;
}