#include <iostream>
#include <fstream>
#include <string>
#include <vector>


#define _CRTDBG_MAP_ALLOC  //Try to find any memory leaks
#include <crtdbg.h>

using namespace std;


const int TOTALSQUARES = 23;  //Include 0 as the first square 23 as the last but 24 in total
const int ALLSQUARES = 50;
const char POUND = 156;  //Displays the pound symbol during output
const int ONEOVERLIMIT = 24;  
const int FINAL_ROUND = 20;  //The maximum number of rounds per game.
const int SEED_RANDOM_NUMBER = 5;

void OpenInputFile(ifstream &infile);
void ReadTextFile(ifstream &infile, string arrCurrentSquare[]);   //Forward decs for reading in the text files


struct STempPlayer   //Temp holder To store the player information obatined form the GetPlayer methods
{
	string mPlayerName;    //This was meant to be replace with the CPlayer class but it kept for now
	int mPlayerCurrentBalance;
	int mCurrentBoardPostion;
	bool mArrOwnedProperty[TOTALSQUARES];
};

STempPlayer tempPlayer; 



void tempPlayerdata(STempPlayer& tempPlayer);

int Random()  //Used for the dice
{
	return static_cast<int>( static_cast<double> (rand()) / (RAND_MAX + 1) * 6.0f + 1 );
}

class CPlayer
{
private:
     string mPlayerName;
     int mCurrentBalance;
     int mCurrentBoardPostion;
	 bool mArrOwnedProperty[TOTALSQUARES];   //The can ether own or not own any of the properites on the board 
public:
     CPlayer();
     void SetPlayer(string playerName, int currentBlance, int currentBoardPostion, bool ArrOwnedProperty[]);
     void GetPlayer(string &playerName, int &currentBlance, int &currentBoardPostion, bool ArrOwnedProperty[]); 
	 void GetPlayer(STempPlayer &tempPlayer);
	 void SetPlayerName(string playerName); //Assign a name to the player
	 void SetCurrentBalance(int amount);  //Get rid of these!!!
	 void DisplayPlayerAfterTurn();
};

CPlayer::CPlayer()
{
	mPlayerName = "NoName";
	mCurrentBalance = 1500;
	mCurrentBoardPostion = 0;
	for (int i = 0; i < TOTALSQUARES; i++)
	{
		 mArrOwnedProperty[i] = false;   //The player does not own any of the properties (also includs the special squares!) to begin with
		 //Each Property may be set to true during the game.
	}

}

void CPlayer::SetPlayerName(string playerName) //Name will be set tocar or dog
{
	mPlayerName = playerName;
}


void CPlayer::SetPlayer(string playerName, int currentBalance, int currentBoardPostion, bool ArrOwnedProperty[])
{
   mPlayerName = playerName;
   mCurrentBalance = currentBalance;
   mCurrentBoardPostion = currentBoardPostion;
   mArrOwnedProperty[currentBoardPostion] = ArrOwnedProperty[currentBoardPostion];

}

void CPlayer::SetCurrentBalance(int amount)
{
	mCurrentBalance = amount;
}

void CPlayer::GetPlayer(string &playerName, int &currentBlance, int &currentBoardPostion, bool ArrOwnedProperty[])
{
	playerName = mPlayerName;
    currentBlance = mCurrentBalance;
    currentBoardPostion = mCurrentBoardPostion;
	for (int i = 0; i < TOTALSQUARES; i++)
	{
		ArrOwnedProperty[i] = mArrOwnedProperty[i];   //The player does not own any properties (including the special squares!) to begin with
	}
}

void CPlayer::GetPlayer(STempPlayer &tempPlayer)
{
	tempPlayer.mPlayerName = mPlayerName;
    tempPlayer.mPlayerCurrentBalance = mCurrentBalance;
    tempPlayer.mCurrentBoardPostion = mCurrentBoardPostion;
	for (int i = 0; i < TOTALSQUARES; i++)
	{
		tempPlayer.mArrOwnedProperty[i] = mArrOwnedProperty[i];   //The player does not own any properties (including the special squares!) to begin with
	}
}

void CPlayer::DisplayPlayerAfterTurn()
{
	cout << mPlayerName << " has " << POUND << mCurrentBalance << endl;
} 
 
class CSquare
{
private:
	string mArrCurrentSquare[ALLSQUARES];
	ifstream infile;
public: 
	CSquare();
	CSquare(ifstream &infile);
    virtual ~CSquare();
	void GetSquare(string &squareValue, int currentSquareIndex); //These 2 methods look similar 
    virtual void DisplayCurrentSquare(CPlayer player[], int currentSquareIndex, int currentPlayerindex);
	void GetAllSquares(string ArrCurrentSquare[]);
};

CSquare::CSquare() //The data needed to set of the board are in the text file.
{ //This will invoke the methods needed
	OpenInputFile(infile);
	ReadTextFile(infile, mArrCurrentSquare);
}

CSquare::CSquare(ifstream &infile)
{     //Overloaded the constructor to take in an argument intead 
	OpenInputFile(infile);
	ReadTextFile(infile, mArrCurrentSquare);
}

CSquare::~CSquare()
{
	infile.close();
}

void CSquare::GetSquare(string &squareValue, int squareIndex)
{
	squareValue = mArrCurrentSquare[squareIndex];
}

void CSquare::DisplayCurrentSquare(CPlayer player[], int currentSquareIndex, int currentPlayerindex)
{
	cout << "This is a normal square of " << mArrCurrentSquare[currentSquareIndex] << endl;
}

void CSquare::GetAllSquares(string ArrCurrentSquare[])
{
	for(int i = 0; i < 50; i++)
	{
		ArrCurrentSquare[i] = mArrCurrentSquare[i];
	}
	return;
}

class CProperty : public CSquare
{
private:
	string ArrPropertyCurrentSquare[ALLSQUARES];  //create a tempoary array  
	string mName;
	int mPropertyNumber; 
	int mCost;
	int mRent;
	int mColourGroup;
	bool mIsOwned;
public:
	CProperty();
	CProperty(int propertyNumber ,int propertyCost, int propertyRent);
	void BuyProperty(CPlayer player[], int currentPlayerIndex);
	void PayRent(CPlayer player[], CPlayer allPlayers[], int currentPlayerIndex);
	void PropertyInteract(CPlayer player[], CPlayer allPlayers[], int currentPlayerIndex);
	void SetPropertyData(string name, int cost, int rent, bool isOwned);     //set the values of the property 
	virtual void DisplayCurrentSquare(CPlayer player[], int currentSquareIndex, int currentPlayerindex);
};

CProperty::CProperty(): CSquare()
{
	GetAllSquares(ArrPropertyCurrentSquare);
}

CProperty::CProperty(int propertyNumber, int propertyCost, int propertyRent): CSquare()
{
	mName = "property ";
	mPropertyNumber = propertyNumber;
	mCost = propertyCost;
	mRent = propertyRent;
	mIsOwned = false; //might changed this to just false
	mColourGroup = 0;
}


void CProperty::BuyProperty(CPlayer player[], int currentPlayerIndex)
{
	tempPlayerdata(tempPlayer);

	player[currentPlayerIndex].GetPlayer(tempPlayer.mPlayerName, tempPlayer.mPlayerCurrentBalance, tempPlayer.mCurrentBoardPostion, tempPlayer.mArrOwnedProperty);
	//for this version of the game it is assumed that the player will always want to buy property.
	if (tempPlayer.mPlayerCurrentBalance >= mCost)  
	{
		tempPlayer.mPlayerCurrentBalance -= mCost;
		mIsOwned = true;                                  //not ready still needs compensate for special squares 
		cout << tempPlayer.mPlayerName << " buys " << mName << mPropertyNumber << " for " << POUND << mCost << endl; 

		player[currentPlayerIndex].SetPlayer(tempPlayer.mPlayerName, tempPlayer.mPlayerCurrentBalance, tempPlayer.mCurrentBoardPostion, tempPlayer.mArrOwnedProperty);
		
	}
	else //The player cannot afford to buy the Property
	{
		cout << tempPlayer.mPlayerName << " does not have enough money to buy the property\n";
	}
}


void CProperty::PayRent(CPlayer player[], CPlayer allPlayers[], int currentPlayerIndex)
{
	player[currentPlayerIndex].GetPlayer(tempPlayer.mPlayerName, tempPlayer.mPlayerCurrentBalance, tempPlayer.mCurrentBoardPostion, tempPlayer.mArrOwnedProperty);

	tempPlayer.mPlayerCurrentBalance -= mRent;
    cout << tempPlayer.mPlayerName << " pays " << POUND << mRent << " Rent ";
	player[currentPlayerIndex].SetPlayer(tempPlayer.mPlayerName, tempPlayer.mPlayerCurrentBalance, tempPlayer.mCurrentBoardPostion, tempPlayer.mArrOwnedProperty);
	//What I need to know is where the money is going to 

	if (tempPlayer.mPlayerName == "dog")
	{
		player[1].GetPlayer(tempPlayer.mPlayerName, tempPlayer.mPlayerCurrentBalance, tempPlayer.mCurrentBoardPostion, tempPlayer.mArrOwnedProperty);
		tempPlayer.mPlayerCurrentBalance += mRent;
		player[1].SetPlayer(tempPlayer.mPlayerName, tempPlayer.mPlayerCurrentBalance, tempPlayer.mCurrentBoardPostion, tempPlayer.mArrOwnedProperty);
	}
	else
	{
		player[0].GetPlayer(tempPlayer.mPlayerName, tempPlayer.mPlayerCurrentBalance, tempPlayer.mCurrentBoardPostion, tempPlayer.mArrOwnedProperty);
		tempPlayer.mPlayerCurrentBalance += mRent;
		player[0].SetPlayer(tempPlayer.mPlayerName, tempPlayer.mPlayerCurrentBalance, tempPlayer.mCurrentBoardPostion, tempPlayer.mArrOwnedProperty);
	}

	player[currentPlayerIndex].GetPlayer(tempPlayer.mPlayerName, tempPlayer.mPlayerCurrentBalance, tempPlayer.mCurrentBoardPostion, tempPlayer.mArrOwnedProperty);

	return;
	
} 

void CProperty::PropertyInteract(CPlayer player[], CPlayer allPlayers[], int currentPlayerIndex)
{
	tempPlayerdata(tempPlayer);

	player[currentPlayerIndex].GetPlayer(tempPlayer);

	if (!mIsOwned)  
	{  //The player can buy the Property if it is not already owned
		BuyProperty(player, currentPlayerIndex);
	}  
	else
	{ 
		player[currentPlayerIndex].GetPlayer(tempPlayer.mPlayerName, tempPlayer.mPlayerCurrentBalance, tempPlayer.mCurrentBoardPostion, tempPlayer.mArrOwnedProperty);
		if (mIsOwned == tempPlayer.mArrOwnedProperty[tempPlayer.mCurrentBoardPostion])
		{
			cout << "nothing happens" << endl;//The player already owns the property 
		} 
		else
	    {   //The amount will be deducted to pay for the rent
			PayRent(player, allPlayers,currentPlayerIndex); 
		}   
	} 
}   

void CProperty::SetPropertyData(const string name, const int cost, const int rent, const bool isOwned)
{
   mName = name;
   mCost = cost;
   mRent = rent;
   mIsOwned = isOwned;
}

void CProperty::DisplayCurrentSquare(CPlayer player[], int currentSquareIndex, int currentPlayerindex)
{
	 GetAllSquares(ArrPropertyCurrentSquare);

	 player[currentPlayerindex].GetPlayer(tempPlayer); 
	 cout << tempPlayer.mPlayerName << " lands on " << mName << mPropertyNumber << endl;

    PropertyInteract(player, player, currentPlayerindex);
   
	player[currentPlayerindex].GetPlayer(tempPlayer);
	
}

class CSpecial : public CSquare
{
private:
	string ArrCurrentSpecialSquare[ALLSQUARES];  //Create an array to store all the squares
public:
	CSpecial();
    ~CSpecial();
	void DisplayCurrentSquare(CPlayer player[], int currentSquareIndex, int currentPlayerindex);
};

CSpecial::CSpecial() : CSquare()  //Call the preivous constructor
{
	GetAllSquares(ArrCurrentSpecialSquare); //cutting down on overheads 
}

CSpecial::~CSpecial() 
{

}
 
void CSpecial::DisplayCurrentSquare(CPlayer player[], int currentSquareIndex, int currentPlayerindex)
{
	 
	tempPlayerdata(tempPlayer);
	GetAllSquares(ArrCurrentSpecialSquare);
	  
	player[currentPlayerindex].GetPlayer(tempPlayer.mPlayerName, tempPlayer.mPlayerCurrentBalance, tempPlayer.mCurrentBoardPostion, tempPlayer.mArrOwnedProperty);
	player[currentPlayerindex].SetPlayer(tempPlayer.mPlayerName, tempPlayer.mPlayerCurrentBalance, currentSquareIndex, tempPlayer.mArrOwnedProperty); //set the players postion

	cout << tempPlayer.mPlayerName << " has landed on " << ArrCurrentSpecialSquare[currentSquareIndex] << endl;

	if (currentSquareIndex == 6)
	{
		cout << tempPlayer.mPlayerName << " is just visiting " << endl;
	}
	else
	{
		cout << tempPlayer.mPlayerName << " is resting " << endl;
	} 
}

class CPenalty : public CSpecial
{
private:	   
	string ArrPenaltyCurrentSquare[ALLSQUARES];
	vector <string> mPenaltyName;
	vector <int> mPenaltyAmountToPay;
public:
	 CPenalty();
	~CPenalty();
	void DisplayCurrentSquare(CPlayer player[], int currentSquareIndex, int currentPlayerindex);
};

CPenalty::CPenalty() : CSpecial()
{	
    //create a tempoary array 
	GetAllSquares(ArrPenaltyCurrentSquare);  //I had to use a full loop for each of the indidvidual elements to fix this

	mPenaltyName.push_back("food bill.");
	mPenaltyName.push_back("phone bill.");
	mPenaltyName.push_back("heating bill.");
	mPenaltyName.push_back("vehicle tax.");
	mPenaltyName.push_back("fuel bill.");
	mPenaltyName.push_back("windfall tax.");

	mPenaltyAmountToPay.push_back(20);
	mPenaltyAmountToPay.push_back(50);
	mPenaltyAmountToPay.push_back(100);
	mPenaltyAmountToPay.push_back(150);
	mPenaltyAmountToPay.push_back(200);
	mPenaltyAmountToPay.push_back(300);	
}

CPenalty::~CPenalty()
{

}

void CPenalty::DisplayCurrentSquare(CPlayer player[], int currentSquareIndex, int currentPlayerindex)
{
	int RandomNumber = 5; //The number chosen by the random number generator
	srand( 5 );
	RandomNumber = Random();

	tempPlayerdata(tempPlayer);

	player[currentPlayerindex].GetPlayer(tempPlayer.mPlayerName, tempPlayer.mPlayerCurrentBalance, tempPlayer.mCurrentBoardPostion, tempPlayer.mArrOwnedProperty);
	tempPlayer.mPlayerCurrentBalance -= mPenaltyAmountToPay[RandomNumber];     //Deduct the penalty amount from the player currentbalance

	//player[currentPlayerindex].SetCurrentBalance(tempPlayer.mPlayerCurrentBalance);
	player[currentPlayerindex].SetPlayer(tempPlayer.mPlayerName, tempPlayer.mPlayerCurrentBalance, currentSquareIndex, tempPlayer.mArrOwnedProperty);

	cout << tempPlayer.mPlayerName << " has landed on " << ArrPenaltyCurrentSquare[currentSquareIndex] << endl;
	cout << "Pay " << mPenaltyName[RandomNumber] << " " << tempPlayer.mPlayerName << " loses " << POUND << mPenaltyAmountToPay[RandomNumber] << endl;

}

class CBonus : public CSpecial
{
private:	   
	string ArrBonusCurrentSquare[ALLSQUARES];  //create a tempoary array 
	vector <string> mBonusName;
	vector <int> mBonusAmount;
public:
	 CBonus();
	~CBonus();
	void DisplayCurrentSquare(CPlayer player[], int currentSquareIndex, int currentPlayerindex);
};

CBonus::CBonus() : CSpecial()
{	
	GetAllSquares(ArrBonusCurrentSquare);  //I had to use a full loop for each of the indidvidual elements to fix this

	mBonusName.push_back("Finds some money.");
	mBonusName.push_back("Win competition.");
	mBonusName.push_back("Tax rebate.");
	mBonusName.push_back("Win Lottery ");
	mBonusName.push_back("Bequest.");
	mBonusName.push_back("Birthday.");

	mBonusAmount.push_back(20);
	mBonusAmount.push_back(50);
	mBonusAmount.push_back(100);
	mBonusAmount.push_back(150);
	mBonusAmount.push_back(200);
	mBonusAmount.push_back(300);	
}

CBonus::~CBonus()
{

}

void CBonus::DisplayCurrentSquare(CPlayer player[], int currentSquareIndex, int currentPlayerindex)
{
	int RandomNumber = 5; //The number chosen by the random number generator
	srand( 5 );
	RandomNumber = Random();

	tempPlayerdata(tempPlayer);

	player[currentPlayerindex].GetPlayer(tempPlayer.mPlayerName, tempPlayer.mPlayerCurrentBalance, tempPlayer.mCurrentBoardPostion, tempPlayer.mArrOwnedProperty);
	tempPlayer.mPlayerCurrentBalance += mBonusAmount[RandomNumber];    

	player[currentPlayerindex].SetPlayer(tempPlayer.mPlayerName, tempPlayer.mPlayerCurrentBalance, currentSquareIndex, tempPlayer.mArrOwnedProperty);

	cout << tempPlayer.mPlayerName << " has landed on " << ArrBonusCurrentSquare[currentSquareIndex] << endl;
	cout << mBonusName[RandomNumber] << " " <<  tempPlayer.mPlayerName << " gains " << POUND << mBonusAmount[RandomNumber] << endl;
}

class CGoToJail : public CSpecial
{
private:
	string ArrGoToJailCurrentSquare[ALLSQUARES];  //create a tempoary array 
	int mFine;    //The amount the player has to pay
public:
	CGoToJail();
    ~CGoToJail();
	virtual void DisplayCurrentSquare(CPlayer player[], int currentSquareIndex, int currentPlayerindex);
};

CGoToJail::CGoToJail() : CSpecial()
{
	GetAllSquares(ArrGoToJailCurrentSquare);  //I had to use a full loop for each of the indidvidual elements to fix this
	mFine = 50;
}

CGoToJail::~CGoToJail()
{

}

void CGoToJail::DisplayCurrentSquare(CPlayer player[], int currentSquareIndex, int currentPlayerindex) //make sured that player has landed on the right square
{

	tempPlayerdata(tempPlayer);

    player[currentPlayerindex].GetPlayer(tempPlayer.mPlayerName, tempPlayer.mPlayerCurrentBalance, tempPlayer.mCurrentBoardPostion, tempPlayer.mArrOwnedProperty);

	tempPlayer.mPlayerCurrentBalance -= mFine; //Deduct the get out of jail amount from the player
	tempPlayer.mCurrentBoardPostion = 6;   //Will send player to jail square

	player[currentPlayerindex].SetPlayer(tempPlayer.mPlayerName, tempPlayer.mPlayerCurrentBalance, tempPlayer.mCurrentBoardPostion, tempPlayer.mArrOwnedProperty);

    cout << tempPlayer.mPlayerName  << " lands on " << ArrGoToJailCurrentSquare[currentSquareIndex] << endl << tempPlayer.mPlayerName << " goes to jail\n"; 
    cout << tempPlayer.mPlayerName << " pays " << POUND << mFine << endl;
}

void SetUpthePlayers(CPlayer players[]);

int main()
{

	CPlayer players[2]; //Create an array of players for car and dog
	
	SetUpthePlayers(players);

	CSquare* Squares[TOTALSQUARES + 1];

	Squares[0] = new CSpecial(); //Create the GO square
	Squares[1] = new CProperty(1,60,5);
	Squares[2] = new CProperty(2,80,10);
	Squares[3] = new CPenalty(); 
	Squares[4] = new CProperty(3,100,15);
	Squares[5] = new CProperty(4,120,15);
	Squares[6] = new CSpecial(); //Create the in Jail square
	Squares[7] = new CProperty(5,140,20);
	Squares[8] = new CProperty(6,160,20);
	Squares[9] = new CProperty(7,180,25); 
	Squares[10] = new CProperty(8,180,25);
	Squares[11] = new CProperty(9,200,25);
	Squares[12] = new CSpecial();  //Create the Free parking square
	Squares[13] = new CProperty(10,220,30);;
	Squares[14] = new CProperty(11,240,30);
	Squares[15] = new CBonus();  //Create the Bouns square
	Squares[16] = new CProperty(12,260,35);
	Squares[17] = new CProperty(13,280,35);
	Squares[18] = new CGoToJail();  //Go to jail square
	Squares[19] = new CProperty(14,300,45);
	Squares[20] = new CProperty(15,320,45);
	Squares[21] = new CProperty(16,400,50);
	Squares[22] = new CProperty(17,420,50);
	Squares[23] = new CProperty(18,440,50);  

	int round = 1;
	int dice = 5; 
	srand( SEED_RANDOM_NUMBER );
	dice = Random();

	tempPlayerdata(tempPlayer);

	cout << "Welcome to Monopoly\n";

	while (round <= FINAL_ROUND) //The game is run from here until the final round 
	{
		round++;
		for (int playerIndex = 0; playerIndex < 2; playerIndex++)
		{
			//Start of player turn
			players[playerIndex].GetPlayer(tempPlayer.mPlayerName, tempPlayer.mPlayerCurrentBalance, tempPlayer.mCurrentBoardPostion, tempPlayer.mArrOwnedProperty);

			cout << endl << tempPlayer.mPlayerName << " rolls " << dice << endl;  //Player roll dice and dice display a number form 1 to 6.
			int previousBoardPostion = tempPlayer.mCurrentBoardPostion;   // Record the last postion before moving 
			tempPlayer.mCurrentBoardPostion += dice;   //Add the dice number result to the player current postion
         	
			if (tempPlayer.mCurrentBoardPostion > TOTALSQUARES)  //The limit of the board;
			{ 
					int overPostion = ONEOVERLIMIT;     //To work how many squares over deduct the previouspostion from the player before hittng go and then take this number from the dice to compensate
					overPostion -= previousBoardPostion; //find the number squares need to move after the circuit 
					dice-= overPostion;
					tempPlayer.mCurrentBoardPostion = (0 + (dice));	//my special Algroithm 

					tempPlayer.mPlayerCurrentBalance += 200;
					cout << tempPlayer.mPlayerName  << " passes GO and collects " << POUND << "200" << endl;

					//end of turn so player is updated
			}  

				//end of turn so player is updated
			players[playerIndex].SetPlayer(tempPlayer.mPlayerName, tempPlayer.mPlayerCurrentBalance, tempPlayer.mCurrentBoardPostion, tempPlayer.mArrOwnedProperty);
			dice = Random(); //next through of the dice	

			Squares[tempPlayer.mCurrentBoardPostion]->DisplayCurrentSquare(players, tempPlayer.mCurrentBoardPostion, playerIndex);

			cout << tempPlayer.mPlayerName << " has " << POUND << tempPlayer.mPlayerCurrentBalance; //The player new balance 

		}
		cout << endl;
	}


	for (int i = 0; i < 24; i++)   //Clean up 
	{ 
		delete Squares[i];
	}  


	cout << endl;
	_CrtDumpMemoryLeaks();
	system("pause");
	return 0;
}


void OpenInputFile(ifstream &infile)
{
	infile.open("Monopoly.txt");

	if(!infile) //Error check if the file cannot be found
	{
		cout << "No file to read" << endl;
		infile.close();
		system("pause");
		exit(1);
	}
} 

void ReadTextFile(ifstream &infile, string arrCurrentSquare[])
{
	infile >> noskipws;
	int in = 0;    

	while (!infile.eof())     //Eead in the text file into an array
	{	
		getline(infile, arrCurrentSquare[in]);
		in++;
	}
}

//Assigned the names dog and car to the players
void SetUpthePlayers(CPlayer player[])
{
	player[0].SetPlayerName("dog");
	player[1].SetPlayerName("car");
} 

void tempPlayerdata(STempPlayer& tempPlayer)
{
	tempPlayer.mPlayerName = "";
	tempPlayer.mPlayerCurrentBalance = 0; //Put this in a functions
	tempPlayer.mCurrentBoardPostion = 0;
	tempPlayer.mArrOwnedProperty[TOTALSQUARES];
}

