#include "CMap.h";


template <class TKey, class TValue>
CMap<TKey, TValue>::CMap()
{
	mLimit = 10;    //Assume the user will have at least ten value.
	mSize = 0;

	mpKey = new TKey[mLimit];          //Create the array for key will be crate and will have ten values to start with.
	mpValue = new TValue[mLimit];      //Also create he array for values. both for these make of the map itself.
}

template <class TKey, class TValue>
CMap<TKey, TValue>::~CMap()   //clean up the map by freeing the pointers of the arrays. 
{
	mSize = 0;  //Reset the sise to 0 although this is not really need. it just a reminder the map is now empty
	delete[] mpKey;  //Destroy the map key array
	delete[] mpValue; //Destroy the map value array 
	//This should now be memory safe
}

template <class TKey, class TValue>
void CMap<TKey, TValue>::AddElement(TKey key, TValue value)
{

	for (int i = 0; i < mSize; i++)  //Test to see if the key or value is in the map.
	{
		if (mpKey[i] == key && mpValue[i] == value)
		{
			cout << "This value and key already exits in the map\nkey:" << key << " value: " << value << " not inserted" << endl;
			return;
		}
		else if (mpKey[i] == key)
		{
			cout << "This key already exits in the map" << endl;
			return;
		}
		else if (mpValue[i] == value)
		{
			cout << "This value already exits in the map" << endl;
			return;
		}
	}
	//No duplcates found, insert the value.

	if (mSize >= mLimit)  //This will not be used in the final version if possible 
	{
		//	cout << "The map is full" << endl;

		TKey* tmpPKey = new TKey[mLimit + 1];          //Creating the new arrays with size less than the current array map.
		TValue* tmpPValue = new TValue[mLimit + 1];
		mLimit++;  //Update the limit to include the new value.

		for (int i = 0; i < mSize; i++)
		{
			tmpPKey[i] = mpKey[i];         //Copy the main map to the temp map
			tmpPValue[i] = mpValue[i];
		}
		delete[] mpKey;     //Destroy the old map
		delete[] mpValue;
		mpKey = 0;
		mpValue = 0;

		tmpPKey[mSize] = key;    //Add the new element to the top of the temp map.
		tmpPValue[mSize] = value;

		mpKey = new TKey[mLimit];   //Recreate the main map array with the new limit. 
		mpValue = new TValue[mLimit];

		for (int i = 0; i < (mSize + 1); i++)
		{
			mpKey[i] = tmpPKey[i];         //Copy the temp map to the main map with the new value. 
			mpValue[i] = tmpPValue[i];
		}

		delete[] tmpPKey;  //Clear the temp map
		delete[] tmpPValue;
		tmpPKey = 0;
		tmpPValue = 0;
		mSize++;
		return;
	}
	else
	{
		mpKey[mSize] = key;    //The insertion works like a stack 
		mpValue[mSize] = value;
		mSize++;
		return;
	}
}

template <class TKey, class TValue>
void CMap<TKey, TValue>::DeleteElement(TKey key, TValue value)
{
	bool isElementInMap = false;
	for (int i = 0; i < mSize; i++)    //Check to see if the element passed by the user is on the map.
	{
		if (mpKey[i] == key && mpValue[i] == value)
		{
			isElementInMap = true;
			break;   //The value is found, stop the search!!!
		}
	}

	if (isElementInMap == true)  //If the element is on the map then remove it.
	{
		TKey* tmpPKey = new TKey[mSize - 1];          //Creating the new arrays with size less than the current array map.
		TValue* tmpPValue = new TValue[mSize - 1];

		//Change over
		bool isSkip = false;

		for (int i = 0; i < mSize - 1; i++)
		{
			if (mpKey[i] == key || isSkip == true)
			{
				//skip an index element to compensate 
				tmpPKey[i] = mpKey[i + 1];   //Add the next element on instead of the current element.
				tmpPValue[i] = mpValue[i + 1];
				cout << "\n" << mpKey[i] << ", ";
				cout << "\n" << mpValue[i] << endl;
				cout << "\nTmp" << tmpPKey[i] << ",";
				cout << "\nTmp" << tmpPValue[i] << endl;
				cout << "index: " << i << endl;
				isSkip = true;

			}
			else
			{
				tmpPKey[i] = mpKey[i];         //Copy the main map to the temp map
				tmpPValue[i] = mpValue[i];
				cout << "\n" << mpKey[i] << ",";
				cout << "\n" << mpValue[i] << endl;
				cout << "\nTmp" << tmpPKey[i] << ",";
				cout << "\nTmp" << tmpPValue[i] << endl;
				cout << "index: " << i << endl;
			}
		}

		for (int i = 0; i < mSize - 1; i++)
		{
			cout << "index " << i << " " << tmpPKey[i] << " : " << tmpPValue[i];
		}

		delete[] mpKey;     //Destroy the old map
		delete[] mpValue;
		mpKey = 0;
		mpValue = 0;

		mpKey = new TKey[mLimit - 1];    //update the map size
		mpValue = new TValue[mLimit - 1];

		for (int i = 0; i < mSize - 1; i++)
		{
			mpKey[i] = tmpPKey[i];         //Copy the temp map to the main map
			mpValue[i] = tmpPValue[i];
		}

		delete[] tmpPKey;  //Clear the temp map
		delete[] tmpPValue;
		tmpPKey = 0;
		tmpPValue = 0;
		mSize--; //Set the size to match the map which should be one less than before.
		mLimit--; //Set the the site of the limit.
		return;
	}
	else  //The element is not on the map, no modifcation to the map.
	{
		cout << "Key" << key << " value: " << value << " is not on the map\nNothing has been deleted" << endl;
		return;
	}
}

template <class TKey, class TValue>
void CMap<TKey, TValue>::DisplayAllElements()
{
	if (mSize != 0)   //As one key to value must be in the list before this can be performed.
	{
		for (int i = 0; i < mSize; i++)
		{
			cout << "Key: " << mpKey[i] << " Value: " << mpValue[i] << endl;
		}
	}
	else
	{
		cout << "This list is empty" << endl;
	}

}

template <class TKey, class TValue>
TValue CMap<TKey, TValue>::Find(TKey searchKey) //look for a elememnt in the map.
{
	for (int i = 0; i < mSize; i++)
	{
		if (mpKey[i] == searchKey)
		{
			cout << "value: " << mpValue[i] << " found! key is " << mpKey[i] << " at postion: " << i << endl;
			return mpValue[i];
		}
	}//Cannot find the key
	cout << "your key " << searchKey << " it not in the map" << endl;
	return mpValue[0];
}

template <class TKey, class TValue>
void CMap<TKey, TValue>::ChangeValue(TKey key, TValue insertValue)
{
	for (int i = 0; i < mSize; i++)
	{
		if (mpKey[i] == key)
		{
			mpValue[i] = insertValue;
			return;
		}
	}
	cout << "Value " << key << " it not in the map" << endl;
}

template <class TKey, class TValue>
int CMap<TKey, TValue>::CountSize()
{
	return mSize;
}