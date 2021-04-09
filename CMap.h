//#pragma once

#ifndef __CMap
#define __CMap
//The key and map could be anything type as I don’t what user will use the map for so this class will take templates types. 
template <class TKey, class TValue>
class CMap
{
private:
	int mSize;     //The current size of the map
	int mLimit;     //The current limit of the map capacity 
	TKey* mpKey;          //pointer for the map key.  
	TValue* mpValue;      //pointer for the map value.  
public:
	CMap(); //Assign the size and limit variables to 0 and create the map arrays for use
	~CMap();  //Clean up the map. Return array memory 
	void AddElement(TKey key, TValue value);
	void DeleteElement(TKey key, TValue value);
	void DisplayAllElements();  //Show the map to the user
	int CountSize();   //Return the current size of the list
	TValue Find(TKey searchKey);  //find a specfic value 
	void ChangeValue(TKey key, TValue Insertvalue);
};

#endif