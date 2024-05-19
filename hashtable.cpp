#include "hashtable.h"
#include <iostream>

using namespace std;

HashTable::HashTable(int size, double threshold, int methode):size(size),threshold_rehashing(threshold),m_sondierMethode(methode)
{
	elements = 0;
	collisionCount = 0;
	hashTable = new vector<int>(size,-1);

}

HashTable::~HashTable()
{
	delete hashTable;
}

int get_next_prime(int x)
{
	x = x + 1;
	bool found = true;
	while (true)
	{
		found = true;
		for (int i = 2; i <= sqrt(x); i++)
		{
			if (x % i == 0)
			{
				found = false;
				break;
			}
		}
		if (found)
		{
			return x;
		}
		x += 1;
	}
}

int get_last_prime(int x)
{
	x = x - 1;
	bool found = true;
	while (true)
	{
		found = true;
		for (int i = 2; i <= sqrt(x); i++)
		{
			if (x % i == 0)
			{
				found = false;
				break;
			}
		}
		if (found)
		{
			return x;
		}
		x -= 1;
	}
}

// Berechnung des Hashwertes 
int HashTable::hashValue(int item) 
{
	int hash = item % size;
	switch (m_sondierMethode)
	{
	case (1):
		// Lineares Sondieren
		if(at(hash) != -1)
		{
			collisionCount++;

			for(int i=0;at(hash)!=-1;i++)
			{
				hash = (item+i) % size;
			}
		}
		return hash;
	case (2):
		// Quadr. Sondieren
		if(at(hash) != -1)
		{
			collisionCount++;

			for(int i=0;at(hash)!=-1;i++)
			{
				hash = (item+i*i) % size;
			}
		}
		return hash;
	case (3):
		{
		// Doppeltes Hashing
		int R = get_last_prime(size);
		if(at(hash) != -1)
		{
			collisionCount++;

			for(int i=0;at(hash)!=-1;i++)
			{
				hash = (item+i*(R - item % R)) % size;
			}
		}
		}
		return hash;
	default:
		return hash;
	}
}
	

void HashTable::rehashing()
{
	collisionCount = 0;
	int oldSize = size;
	size = get_next_prime(2*size);

	vector<int>* oldTable = hashTable;
	vector<int>* newTable = new vector<int>(size,-1);
	hashTable = newTable;

	for(int i=0;i<oldSize;i++)
	{
		int item = oldTable->at(i);
		if(item != -1)
		{
			int hash = hashValue(item);
			hashTable->at(hash) = item;
		}
	}

	delete oldTable;
}

int HashTable::insert(int item) 
{
	double beta = (double)elements / (double)size;
	if(beta > threshold_rehashing)
		rehashing();

	int hash = hashValue(item);
	hashTable->at(hash) = item;
	elements++;

	return hash;
}


int HashTable::at(int i) 
{
	return hashTable->at(i);
}

int HashTable::getCollisionCount() 
{
	return this->collisionCount;
}

int HashTable::getSize() 
{
	return this->size;
}

int HashTable::getElements() 
{
	return this->elements;
}


void HashTable::print()
{
	for(int i=0;i<size;i++)
	{
		if(at(i) != -1)
			std::cout<<"["<<i<<"]"<<" -> "<<at(i)<<std::endl;
	}
}
