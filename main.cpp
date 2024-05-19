#define CATCH_CONFIG_RUNNER
#include "catch.h"
#include <iostream>
#include"hashtable.h"

int main() {
    Catch::Session().run();

	HashTable table(1000);

	for(int i=0;i<200;i++)
	{
		int num = rand() % 501 + 1000;
		table.insert(num);
	}

	std::cout<<"Kollisionen: "<<table.getCollisionCount()<<std::endl;
	table.print();
    system("pause");
    return 0;
}