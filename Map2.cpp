#include <iostream>
#include <string>
#include "CMap.cpp";

#define _CRTDBG_MAP_ALLOC
#include <crtdbg.h>

using std::cout;
using std::string;
using std::endl;

int main()
{
	//The map will take strings as elements
	CMap <int, string> *myMap = new CMap<int, string>;

	myMap->AddElement(0,"one");
	myMap->DisplayAllElements();
	myMap->AddElement(0,"one");
	myMap->AddElement(0,"one");
	myMap->AddElement(1,"two");
	myMap->AddElement(2,"three");
	myMap->AddElement(4,"four");
	myMap->DisplayAllElements();
	cout << myMap->CountSize() << endl;
	myMap->Find(2);
	myMap->ChangeValue(4, "anotherfour");
	myMap->ChangeValue(10, "anotherten");
	myMap->DisplayAllElements();
	myMap->DeleteElement(2,"three");
	myMap->DisplayAllElements();
	myMap->AddElement(5, "five");
	myMap->AddElement(6, "six");
	myMap->DisplayAllElements();
	myMap->Find(10); //Find was is stored in index 10 which should be enmpty
	delete myMap; 
	cout << endl << "The old map has been destroyed a new map is now being created" << endl << endl;
	CMap <int, int> *myMap2 = new CMap<int, int>; 

	myMap2->AddElement(1, 11);
	myMap2->AddElement(3, 13);
	myMap2->AddElement(6, 16);
	myMap2->AddElement(4, 14);
	myMap2->AddElement(5, 15);
	myMap2->AddElement(9, 19);
	myMap2->AddElement(0, 00);
	myMap2->AddElement(2, 12);
	myMap2->AddElement(7, 17);
	myMap2->AddElement(20, 40);
	myMap2->AddElement(22, 42);
	myMap2->AddElement(30, 60);
	myMap2->DisplayAllElements();

	myMap2->Find(3);    //There should be the value of 11 displayed this time

	myMap2->DeleteElement(8,18);
	myMap2->DeleteElement(3, 13);
	myMap2->DisplayAllElements(); //check to see if the elements have been deleted 
	delete myMap2; 

	system("pause");
	_CrtDumpMemoryLeaks();
	return 0;
}

