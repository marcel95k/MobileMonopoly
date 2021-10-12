#include <vector>
#include <iostream>
#include <string>
#include <stdlib.h>
#include <math.h>
#include <chrono>
#include <thread>
#include <time.h>

#include "classPlayer.h"
#include "classBank.h"
#include "classGameField.h"
#include "classTrade.h"

using namespace std;

void setUpGameField(vector <string>* gameFieldStringsValue);
void setUpPlayerStats(vector <classGameField>* classGameFieldVector, vector <classPlayer>* classPlayerVector);
void gameRound(vector <classGameField>* classGameFieldVector, vector <classPlayer>* classPlayerVector);
void nonPurchasAbleFields(vector <classGameField>* classGameFieldVector, vector <classPlayer>* classPlayerVector, int* thisPlayer);
void purchasAbleFields(vector <classGameField>* classGameFieldVector, vector <classPlayer>* classPlayerVector, int* thisPlayer);
void eventsAndCommunityFields(vector <classGameField>* classGameFieldVector, vector <classPlayer>* classPlayerVector, int* thisPlayer);
void doubleRentOnFullGroup(vector <classGameField>* classGameFieldVector, vector <classPlayer>* classPlayerVector);
void calcPortRent(vector <classGameField>* classGameFieldVector, vector <classPlayer>* classPlayerVector);
bool sellHouse(vector <classGameField>* classGameFieldVector, vector <classPlayer>* classPlayerVector, int* thisPlayer);
int rollDice();

int main() {

	/*First declaration of all fieldnames as strings in a vector.*/
	vector <string> gameFieldStrings = {
		/*LINE 1*/	"START", "\x1B[1;30mBREMEN\033[0m", "COMMUNITY FIELD", "\x1B[1;30mMUSCAT\033[0m", "INCOME TAX", "PORT 1", "\x1B[36mATHENS\033[0m", "EVENT FIELD", "\x1B[36mHELSINKI\033[0m", "\x1B[36mKIEW\033[0m",

		/*LINE 2*/	"VISIT/JAIL", "\x1B[35mCOPENHAGEN\033[0m", "BANK", "\x1B[35mAMSTERDAM\033[0m", "\x1B[35mLUXEMBURG\033[0m", "PORT 2", "\x1B[2;33mJAKARTA\033[0m", "COMMUNITY FIELD", "\x1B[2;33mCOLOMBO\033[0m", "\x1B[2;33mDOHA\033[0m",

		/*LINE 3*/	"FREE PARKING", "\x1B[31mNEW DELHI\033[0m", "EVENT FIELD", "\x1B[31mKATHMANDU\033[0m", "\x1B[31mKUALA LUMPUR\033[0m", "PORT 3", "\x1B[1;33mNICOSIA\033[0m", "\x1B[1;33mSKOPJE\033[0m", "BANK", "\x1B[1;33mBRUSSELS\033[0m",

		/*LINE 4*/	"JAIL", "\x1B[32mSAN MARINO\033[0m", "\x1B[32mMONACO\033[0m", "COMMUNITY FIELD", "\x1B[32mVALLETTA\033[0m", "PORT 4", "EVENT FIELD", "\x1B[34mSZEGED\033[0m", "ADDITIONAL TAX", "\x1B[34mVIENNA\033[0m"
	};

	/*Call the function setUpGameField() and hand over the vector gameFieldStrings.*/
	setUpGameField(&gameFieldStrings);
}


void setUpGameField(vector <string>* gameFieldStringsValue) {

	vector <classGameField> gameFieldVector;
	vector <classPlayer> playerVector;

	/*Here, a for-loop iterates through the vector and creates an object of classGameField.
	This object is the pushed to a new vector from type classGameField.
	 At this moment all objects are treated as purchasable with a price of 0.*/
	for (int fieldPos = 0; fieldPos < gameFieldStringsValue->size(); fieldPos++) {
		classGameField fieldObj(gameFieldStringsValue->at(fieldPos), 0, true);
		gameFieldVector.push_back(fieldObj);
	}

	/*Reset the purchasability of certain fields.*/

	gameFieldVector.at(0).setIsPurchasable(false);	/*SET START NOT PURCHASABLE*/
	gameFieldVector.at(2).setIsPurchasable(false);	/*SET FIRST COMMUNITY FIELD NOT PURCHASABLE*/
	gameFieldVector.at(4).setIsPurchasable(false);	/*SET INCOME TAX NOT PURCHASABLE*/
	gameFieldVector.at(7).setIsPurchasable(false);	/*SET FIRST EVENT FIELD NOT PURCHASABLE*/
	gameFieldVector.at(10).setIsPurchasable(false);	/*SET VISIT NOT PURCHASABLE*/
	gameFieldVector.at(12).setIsPurchasable(false);	/*SET FIRST BANK NOT PURCHASABLE*/
	gameFieldVector.at(17).setIsPurchasable(false);	/*SET SECOND COMMUNITY FIELD NOT PURCHASABLE*/
	gameFieldVector.at(20).setIsPurchasable(false);	/*SET FREE PARKING NOT PURCHASABLE*/
	gameFieldVector.at(22).setIsPurchasable(false);	/*SET SECOND EVENT FIELD NOT PURCHASABLE*/
	gameFieldVector.at(28).setIsPurchasable(false); /*SET SECOND BANK NOT PURCHASABLE*/
	gameFieldVector.at(30).setIsPurchasable(false);	/*SET JAIL NOT PURCHASABLE*/
	gameFieldVector.at(33).setIsPurchasable(false);	/*SET THIRD COMMUNITY FIELD NOT PURCHASABLE*/
	gameFieldVector.at(36).setIsPurchasable(false);	/*SET THIRD EVENT FIELD NOT PURCHASABLE*/
	gameFieldVector.at(38).setIsPurchasable(false);	/*SET ADDITIONAL TAX NOT PURCHASABLE*/

	/*Set field stats for purchasable fields.  */
	/*(Handover takes place in the following order :*/
	/*Price, Price Per House, Base Rent, Rent, Group Position, Field Type)*/
																												/**************************************************************/
	gameFieldVector.at(1).setFieldStats(600, 500, 20, 20, 1, "2group");			/*BREMEN*/						/*					Group1: BREMEN							  */
	gameFieldVector.at(3).setFieldStats(600, 500, 40, 40, 1, "2group");			/*MUSCAT*/						/*							MUSCAT				              */
	gameFieldVector.at(5).setFieldStats(2000, 0, 250, 250, 0, "Port");			/*PORT 1*/						/*                                                            */
	gameFieldVector.at(6).setFieldStats(1000, 500, 60, 60, 2, "3group");		/*ATHENS*/						/*					Group2: ATHENS							  */
	gameFieldVector.at(8).setFieldStats(1000, 500, 60, 60, 2, "3group");		/*HELSINKI*/					/*							HELSINKI				          */
	gameFieldVector.at(9).setFieldStats(1200, 500, 80, 80, 2, "3group");		/*KIEW*/						/*							KIEW				              */
	gameFieldVector.at(11).setFieldStats(1400, 1000, 100, 100, 3, "3group");	/*COPENHAGEN*/					/*					Group3: COPENHAGEN						  */
	gameFieldVector.at(13).setFieldStats(1400, 1000, 100, 100, 3, "3group");	/*AMSTERDAM*/					/*							HELSINKI				          */
	gameFieldVector.at(14).setFieldStats(1600, 1000, 120, 120, 3, "3group");	/*LUXEMBURG*/					/*							LUXEMBURG				          */
	gameFieldVector.at(15).setFieldStats(2000, 0, 250, 250, 0, "Port");			/*PORT 2*/						/*                                                            */
	gameFieldVector.at(16).setFieldStats(1800, 1000, 140, 140, 4, "3group");	/*JAKARTA*/						/*					Group4:	JAKARTA							  */
	gameFieldVector.at(18).setFieldStats(1800, 1000, 140, 140, 4, "3group");	/*COLOMBO*/						/*							COLOMBO							  */
	gameFieldVector.at(19).setFieldStats(2000, 1000, 160, 160, 4, "3group");	/*DOHA*/						/*							DOHA					          */
	gameFieldVector.at(21).setFieldStats(2200, 1500, 180, 180, 5, "3group");	/*NEW DELHI*/					/*					Group5:	NEW DELHI						  */
	gameFieldVector.at(23).setFieldStats(2200, 1500, 180, 180, 5, "3group");	/*KATHMANDU*/					/*							KATHMANDU					      */
	gameFieldVector.at(24).setFieldStats(2400, 1500, 200, 200, 5, "3group");	/*KUALA LUMPUR*/				/*							KUALA LUMPUR					  */
	gameFieldVector.at(25).setFieldStats(2000, 0, 250, 250, 0, "Port");			/*PORT 3*/						/*                                                            */
	gameFieldVector.at(26).setFieldStats(2600, 1500, 220, 220, 6, "3group");	/*NICOSIA*/						/*					Group6:	NICOSIA					     	  */
	gameFieldVector.at(27).setFieldStats(2600, 1500, 220, 220, 6, "3group");	/*SKOPJE*/						/*							SKOPJE						      */
	gameFieldVector.at(29).setFieldStats(2800, 1500, 240, 240, 6, "3group");	/*BRUSSELS*/					/*							BRUSSELS						  */
	gameFieldVector.at(31).setFieldStats(3000, 2000, 260, 260, 7, "3group");	/*SAN MARINO*/					/*					Group7:	SAN MARINO					      */
	gameFieldVector.at(32).setFieldStats(3000, 2000, 260, 260, 7, "3group");	/*MONACO*/						/*							MONACO			     			  */
	gameFieldVector.at(34).setFieldStats(3200, 2000, 280, 280, 7, "3group");	/*VALLETTA*/					/*							VALLETTA					      */
	gameFieldVector.at(35).setFieldStats(2000, 0, 250, 250, 0, "Port");			/*PORT 4*/						/*                                                            */
	gameFieldVector.at(37).setFieldStats(3500, 2000, 350, 350, 8, "2group");	/*SZEGED*/						/*					Group8:	SZEGED					     	  */
	gameFieldVector.at(39).setFieldStats(4000, 2000, 500, 500, 8, "2group");	/*VIENNA*/						/*							VIENNA					     	  */
																												/**************************************************************/

	/*Call the function setUpPlayerStats() and hand over the vectors gameFieldVector and playerVector.*/
	setUpPlayerStats(&gameFieldVector, &playerVector);
}

void setUpPlayerStats(vector <classGameField>* classGameFieldVector, vector <classPlayer>* classPlayerVector) {
setUpPlayerStatsBegin:
	int inputPlayerAmount;
	int moneyAmount;
	int userInput;
	string name;
	system("cls");
	cout << "MONOPOLY\n\n";
	cout << "How many players?\nAmount: ";
	cin >> inputPlayerAmount;
	if (inputPlayerAmount < 2) {
		cout << "\nAtleast 2 players need to play!\n";
		system("pause");
		goto setUpPlayerStatsBegin;
	}
	else if (inputPlayerAmount > 6) {
		cout << "\nMaximum 6 players can play!\n";
		system("pause");
		goto setUpPlayerStatsBegin;
	}
	cout << "\n";
	system("cls");							/*Decide whether the players start with the default amount of money (15000)*/
	cout << "Money:\n\n";					/*or a custom amount.*/
	cout << "[1] Default";
	cout << "\n[2] Custom";
	cout << "\n\nOption: ";
	cin >> userInput;
	if (userInput == 1) {
		moneyAmount = 15000;
	}
	else {
		system("cls");
		cout << "How much money is each player going to have?";
		cout << "\n\nAmount: ";
		cin >> moneyAmount;
	}
	/*Players entering their names within a for-loop.
	 A second for-loop checks the availability of the typed in name.
	 After entering the names, an object of classPlayer is created,
	 which is pushed to a vector from type classPlayer each time at the
	 end of the outer for-loop.*/
	for (int playerPos = 0; playerPos < inputPlayerAmount; playerPos++) {
	typeInNames:
		system("cls");
		cout << "Player " << playerPos + 1 << ", enter your name: ";
		cin >> name;
		for (int checkForName = 0; checkForName < classPlayerVector->size(); checkForName++) {
			if (name == classPlayerVector->at(checkForName).getPlayerName()) {
				cout << "\nThere is already a player with this name!\n";
				cout << "Enter another one!\n\n";
				checkForName = classPlayerVector->size() - 1;
				system("pause");
				goto typeInNames;
			}
		}
		classPlayer playerObj(name, moneyAmount);				/*15000 is the default amount of money for each player.*/
		classPlayerVector->push_back(playerObj);				/*The new created playerObj is pushed to the vector playerVector.*/
	}

	/*Call the function gameRound() and hand over the vectors classGameFieldVector and classPlayerVector.*/
	gameRound(classGameFieldVector, classPlayerVector);
}

void gameRound(vector <classGameField>* classGameFieldVector, vector <classPlayer>* classPlayerVector) {
	system("cls");
	int userInput;
	vector <string> displayPlayers;
	displayPlayers.resize(classPlayerVector->size());
	for (int thisPlayer = 0; thisPlayer < classPlayerVector->size(); thisPlayer++) {
	gameRoundBegin:
		doubleRentOnFullGroup(classGameFieldVector, classPlayerVector);											/*Call the function doubleRentOnFullGroup() and hand over the vectors classGameFieldVector and classPlayerVector.*/
		calcPortRent(classGameFieldVector, classPlayerVector);													/*Call the function calcPortRent() and hand over the vectors classGameFieldVector and classPlayerVector.*/
		for (int listPlayers = 0; listPlayers < classPlayerVector->size(); listPlayers++) {
			displayPlayers.at(listPlayers) = classPlayerVector->at(listPlayers).getPlayerName();
			if (displayPlayers.at(listPlayers) == classPlayerVector->at(thisPlayer).getPlayerName()) {
				displayPlayers.at(listPlayers) = "\x1B[1;31m" + displayPlayers.at(listPlayers) + "\033[0m";		/*Make the drawing player colored for better visibility.*/
			}
			else { displayPlayers.at(listPlayers) = displayPlayers.at(listPlayers); }
		}
		system("cls");
		if (classPlayerVector->at(thisPlayer).getPlayerMoney() <= 0) {	/*Check if the current player has lost all money*/
			system("cls");												/*and erase the player from the vector.*/
			cout << classPlayerVector->at(thisPlayer).getPlayerName() << " has no money anymore!\n\n";
			system("pause");
			classPlayerVector->erase(classPlayerVector->begin() + thisPlayer);
		}
		if (classPlayerVector->at(thisPlayer).getIsInJail() == true) {	/*Check if the current player is in jail*/
			cout << "You are in jail!\nPay 500!\n\n";					/*and let the player pay.*/
			system("pause");
			cout << "\n";
			cout << classPlayerVector->at(thisPlayer).getPlayerMoney() << "\x1B[31m - 100\033[0m\n";
			classPlayerVector->at(thisPlayer).losePlayerMoney(500);
			cout << "NEW MONEY: " << classPlayerVector->at(thisPlayer).getPlayerMoney() << "\n\n";
			classPlayerVector->at(thisPlayer).setIsInJail(false);
			system("pause");
			system("cls");
		}
		for (int listPlayers = 0; listPlayers < classPlayerVector->size(); listPlayers++) {
			cout << displayPlayers.at(listPlayers) << ": " << classGameFieldVector->at(classPlayerVector->at(listPlayers).getCurrentPosition()).getFieldName() << "\n";
		}
		cout << "\n\n\n";
		cout << "NAME:\t" << classPlayerVector->at(thisPlayer).getPlayerName() << "\n";
		cout << "MONEY:\t" << classPlayerVector->at(thisPlayer).getPlayerMoney() << "\n";
		cout << "CURRENT FIELD:\t" << classGameFieldVector->at(classPlayerVector->at(thisPlayer).getCurrentPosition()).getFieldName() << "\n\n";
		cout << "[1] Roll Dice\n";
		cout << "[2] TRADE\n";
		cout << "[3] TRANSFER MONEY\n";
		cout << "[4] VIEW PLAYER INFO\n";
		cout << "[5] VIEW FIELD INFO\n";
		cout << "[6] SELL HOUSE\n";
		cout << "[7] RESIGN\n\n";
		cout << "Option: ";
		cin >> userInput;

		if (userInput == 1) {		/*ROLL DICE*/
			classPlayerVector->at(thisPlayer).setNewPosition(rollDice());															/*Sets the new position of the player by calling the function rollDice().*/
			if (classGameFieldVector->at(classPlayerVector->at(thisPlayer).getCurrentPosition()).getIsPurchasable() == false) {		/*Then it will be checked if the player landed on a purchasable field or not.*/
				nonPurchasAbleFields(classGameFieldVector, classPlayerVector, &thisPlayer);
			}
			else if (classGameFieldVector->at(classPlayerVector->at(thisPlayer).getCurrentPosition()).getIsPurchasable() == true) {
				purchasAbleFields(classGameFieldVector, classPlayerVector, &thisPlayer);
			}
		}

		//if (userInput == 1) {	/*ROLL DICE*/												/*Checks for doubles.*/
		//	int doublesCounter = 0;
		//	classDice rollDice;
		//rollDicesBegin:
		//	if (doublesCounter < 3) {															
		//		system("cls");																	/*Sets the new position of the player by addine the diceSum of classDice to*/
		//		cout << "Rolling Dices...\n";													/*the current position of the player.*/
		//		this_thread::sleep_for(chrono::seconds(1));										/*It will be checked if the player rolled doubles, if yes the variable*/
		//		rollDice.rollDice_1();															/*doublesCounter is increased.*/
		//		this_thread::sleep_for(chrono::seconds(1));										/*If the player did not roll doubles, it will be checked*/
		//		rollDice.rollDice_2();															/*if the player landed on a purchasable field or not.*/
		//		rollDice.setDiceSum(rollDice.getDice_1(), rollDice.getDice_2());				/*In case the variable doublesCounter is at 3, the player is put in the jail.*/
		//		classPlayerVector->at(thisPlayer).setNewPosition(rollDice.getDiceSum());
		//		if (rollDice.getDice_1() == rollDice.getDice_2()) {
		//			rollDice.setIsDouble(true);
		//			doublesCounter++;
		//		}
		//		else { rollDice.setIsDouble(false); }
		//		cout << "You rolled " << rollDice.getDice_1() << " and " << rollDice.getDice_2() << " (" << rollDice.getDiceSum() << ")\n\n";
		//		system("pause");
		//		if (rollDice.getIsDouble() == true) {
		//			system("cls");
		//			cout << "You rolled doubles!";
		//			cout << "\n\nRoll the dices again!\n\n";
		//			system("pause");
		//			goto rollDicesBegin;
		//		}
		//		else if (rollDice.getIsDouble() == false) {
		//			if (classGameFieldVector->at(classPlayerVector->at(thisPlayer).getCurrentPosition()).getIsPurchasable() == false) {	
		//				nonPurchasAbleFields(classGameFieldVector, classPlayerVector, &thisPlayer);
		//			}
		//			else if (classGameFieldVector->at(classPlayerVector->at(thisPlayer).getCurrentPosition()).getIsPurchasable() == true) {
		//				purchasAbleFields(classGameFieldVector, classPlayerVector, &thisPlayer);
		//			}
		//		}
		//	}
		//	else if (doublesCounter == 3) {
		//		system("cls");
		//		cout << "You rolled doubles 3 times in a row!\n\n";
		//		cout << "YOU HAVE TO GO TO JAIL!\n\n";
		//		system("pause");
		//		classPlayerVector->at(thisPlayer).setIsInJail(true);					/*Set the value of isInJail in classPlayer to TRUE. */
		//			for (int x = 0; x < 40; x++) {										/*Afterwards the player is put on the VISIT/JAIL field.*/
		//				classPlayerVector->at(thisPlayer).setNewPosition(1);
		//				if (classPlayerVector->at(thisPlayer).getCurrentPosition() == 10) {
		//					break;
		//				}
		//			}
		//	}
		//}
		else if (userInput == 2) {	/*TRADE*/
		tradeSection:
			int tradePartner;
			system("cls");
			cout << "With which player do you want to trade?\n\n";
			for (int listPlayers = 0; listPlayers < classPlayerVector->size(); listPlayers++) {
				cout << "[" << listPlayers + 1 << "] " << classPlayerVector->at(listPlayers).getPlayerName() << "\n";
			}
			cout << "\nChoose: ";
			cin >> userInput;
			if (userInput == thisPlayer + 1) {
				cout << "Trading with yourself wouldn't be adavntageous!\n\n";
				system("pause");
				goto tradeSection;
			}
			else if (userInput > classPlayerVector->size()) {
				cout << "\nNo player found at this position!\n";
				system("pause");
				goto tradeSection;
			}
			else {
				tradePartner = userInput - 1;
				classTrade trade;
				trade.trade(classGameFieldVector, classPlayerVector, &thisPlayer, &tradePartner);
				if (trade.getTradeAbort() == false) {
					system("cls");
					cout << "Trade completed!\n\n";
					system("pause");
				}
				else if (trade.getTradeAbort() == true) { goto gameRoundBegin; }	/*Check if the function getTradeAbort()*/
																					/*returns TRUE and make the same player continue*/
			}																		/*in this round.*/
		}
		else if (userInput == 3) {	/*TRANSFER MONEY*/
		transferSection:
			int transferAmount;
			int otherPlayer;
			system("cls");
			cout << "To whom do you want to transfer money?\n\n";
			for (int listPlayers = 0; listPlayers < classPlayerVector->size(); listPlayers++) {
				cout << "[" << listPlayers + 1 << "] " << classPlayerVector->at(listPlayers).getPlayerName() << "\n";
			}
			cout << "[";
			cout << "\nChoose: ";
			cin >> otherPlayer;
			if (otherPlayer == thisPlayer + 1) {
				cout << "You can't transfer money to yourself!\n\n";
				system("pause");
				goto transferSection;
			}
			else if (otherPlayer > classPlayerVector->size()) {
				cout << "\nNo player found at this position!\n";
				system("pause");
				goto transferSection;
			}
			else {
				otherPlayer -= 1;
				system("cls");
				cout << "How much do you want to transfer?\n\n";
				cout << "Amount: ";
				cin >> transferAmount;
				if (transferAmount >= classPlayerVector->at(thisPlayer).getPlayerMoney()) {
					cout << "You do not have this many financial possibilities!\n";
					system("pause");
					goto transferSection;
				}
				else {
					cout << classPlayerVector->at(thisPlayer).getPlayerName() << ":\n";
					cout << classPlayerVector->at(thisPlayer).getPlayerMoney() << "\x1B[31m - " << transferAmount << "\033[0m\n";
					classPlayerVector->at(thisPlayer).losePlayerMoney(transferAmount);
					cout << "NEW MONEY: " << classPlayerVector->at(thisPlayer).getPlayerMoney();
					cout << "\n\n";
					cout << classPlayerVector->at(otherPlayer).getPlayerName() << ":\n";
					cout << classPlayerVector->at(otherPlayer).getPlayerMoney() << "\x1B[32m + " << transferAmount << "\033[0m\n";
					classPlayerVector->at(otherPlayer).addPlayerMoney(transferAmount);
					cout << "NEW MONEY: " << classPlayerVector->at(otherPlayer).getPlayerMoney();
					cout << "\n\n";
					system("pause");
					goto gameRoundBegin;
				}
			}
		}
		else if (userInput == 4) {	/*VIEW PLAYER INFO*/																			/****************************************/
		playerInfoBegin:																													/*Viewing the info of a selected player.*/
			system("cls");																											/*Currently viewing:					*/
			cout << "Of which player do you want to see the info?\n\n";																/*				- Playername			*/
			for (int listPlayers = 0; listPlayers < classPlayerVector->size(); listPlayers++) {										/*				- Money					*/
				cout << "[" << listPlayers + 1 << "] " << classPlayerVector->at(listPlayers).getPlayerName() << "\n";				/*				- Current position		*/
			}																														/*				- Possessing fields		*/
			cout << "\nChoose: ";																									/*				  (Strings)				*/
			cin >> userInput;																										/****************************************/
			if (userInput <= classPlayerVector->size()) {
				cout << "\nNAME:\t\t" << classPlayerVector->at(userInput - 1).getPlayerName() << "\n";
				cout << "MONEY:\t\t" << classPlayerVector->at(userInput - 1).getPlayerMoney() << "\n";
				cout << "CURRENT FIELD:\t" << classGameFieldVector->at(classPlayerVector->at(userInput - 1).getCurrentPosition()).getFieldName() << "\n\n";
				cout << "POSSESSIONS: ";
				classPlayerVector->at(userInput - 1).getMyGroupStrings();
				cout << "\n";
				cout << "FREE FROM JAIL CARD:\t" << classPlayerVector->at(userInput - 1).getHasFreeJailCard();
				cout << "\n\n";
				system("pause");
				thisPlayer--;
			}
			else {
				cout << "\nPlayer not fond!\n\n";
				system("pause");
				goto playerInfoBegin;
			}
		}
		else if (userInput == 5) {	/*VIEW FIELD INFO*/
		displayFieldBegin:
			int userInput;
			string sold;
			system("cls");
			for (int displayFields = 0; displayFields < classGameFieldVector->size(); displayFields++) {
				if (classGameFieldVector->at(displayFields).getIsAvailable() == true) {
					sold = " ";
				}
				else { sold = "\x1B[31m - SOLD TO: \033[0m"; }
				cout << "[" << displayFields << "] " << classGameFieldVector->at(displayFields).getFieldName() << ": " << sold << classGameFieldVector->at(displayFields).getBelongsTo() << "\n";
			}
			cout << "\nOf which field do you want to see the info?\tChoose: ";
			cin >> userInput;
			if (userInput >= classGameFieldVector->size()) {
				cout << "\nField not found!\n";
				system("pause");
				goto displayFieldBegin;
			}
			if (classGameFieldVector->at(userInput).getGroupPosition() != 0 && classGameFieldVector->at(userInput).getIsPurchasable() == true) {		/*Displaying the info of the field when it is NOT a port.*/
				system("cls");
				cout << classGameFieldVector->at(userInput).getFieldName();
				cout << "\n\nBELONGS TO: " << classGameFieldVector->at(userInput).getBelongsTo();
				if (classGameFieldVector->at(userInput).getAmoutOfHouses() <= 4) {
					cout << "\n\nHOUSES:\t\t" << classGameFieldVector->at(userInput).getAmoutOfHouses();
				}
				else { cout << "\n\nHOUSES:\t\t1 HOTEL"; }
				cout << "\n\nRent:\t\t\tBase:\t\t" << classGameFieldVector->at(userInput).getBaseRent();
				cout << "\n\t\t\tFull group:\t" << classGameFieldVector->at(userInput).getBaseRent() * 2;
				cout << "\n\n\t\t\tWith 1 House:\t" << classGameFieldVector->at(userInput).getBaseRent() * 4;
				cout << "\n\t\t\tWith 2 Houses:\t" << classGameFieldVector->at(userInput).getBaseRent() * 12;
				cout << "\n\t\t\tWith 3 Houses:\t" << classGameFieldVector->at(userInput).getBaseRent() * 24;
				cout << "\n\t\t\tWith 4 Houses:\t" << classGameFieldVector->at(userInput).getBaseRent() * 36;
				cout << "\n\t\t\tWith HOTEL:\t" << classGameFieldVector->at(userInput).getBaseRent() * 48;
				cout << "\n\nCurrent Rent: " << classGameFieldVector->at(userInput).getRent();
				cout << "\n\n";
				system("pause");
			}
			else if (classGameFieldVector->at(userInput).getGroupPosition() == 0 && classGameFieldVector->at(userInput).getIsPurchasable() == true) {	/*Displaying the info of the field when it IS a port.*/
				system("cls");
				cout << classGameFieldVector->at(userInput).getFieldName();
				cout << "\n\nBELONGS TO: " << classGameFieldVector->at(userInput).getBelongsTo();
				cout << "\n\nRent:\t\t\t1 Port:\t\t" << classGameFieldVector->at(userInput).getBaseRent();
				cout << "\n\t\t\t2 Ports:\t" << classGameFieldVector->at(userInput).getBaseRent() * 2;
				cout << "\n\t\t\t3 Ports:\t" << classGameFieldVector->at(userInput).getBaseRent() * 4;
				cout << "\n\t\t\t4 Ports:\t" << classGameFieldVector->at(userInput).getBaseRent() * 8;
				cout << "\n\nCurrent Rent: " << classGameFieldVector->at(userInput).getRent();
				cout << "\n\n";
				system("pause");
			}
			else if (classGameFieldVector->at(userInput).getIsPurchasable() == false) {																	/*Displaying the info of the field when it is a nonpurchasable field.*/
				system("cls");
				cout << classGameFieldVector->at(userInput).getFieldName();
				cout << "\n\n";
				system("pause");
			}
			goto gameRoundBegin;
		}
		else if (userInput == 6) {	/*SELL HOUSE*/
			if (sellHouse(classGameFieldVector, classPlayerVector, &thisPlayer) == true) {
				system("cls");
				cout << "House sold!\n\n";
				system("pause");
			}
			else if (sellHouse(classGameFieldVector, classPlayerVector, &thisPlayer) == false) {
				goto gameRoundBegin;
			}
		}
		else if (userInput == 7) {	/*RESIGN*/
			int decision;
			system("cls");
			cout << "Are you sure?";
			cout << "\n\n[1] Yes";
			cout << "\n[2] No";
			cout << "\n\nOption: ";
			cin >> decision;
			if (decision == 1) {
				system("cls");
				cout << classPlayerVector->at(thisPlayer).getPlayerName() << " raged and flipped the game board over the table!\n\n";
				system("pause");
				classPlayerVector->erase(classPlayerVector->begin() + thisPlayer);
				thisPlayer--;
			}
			else { goto gameRoundBegin; }
		}
		else { goto gameRoundBegin; }

		if (thisPlayer == classPlayerVector->size() - 1) {		/*Check if the iteration through the vector classPlayerVector*/
			thisPlayer = -1;									/*is finished and reset the iterator.*/
		}
	}
}

void nonPurchasAbleFields(vector <classGameField>* classGameFieldVector, vector <classPlayer>* classPlayerVector, int* thisPlayer) {		/*Nonpurchasable fields:*/
	int field = classPlayerVector->at(*thisPlayer).getCurrentPosition();																	/*The string of the nonpurchasable fields is checked*/
	system("cls");																															/*and make happen the event based on the name*/
	if (classGameFieldVector->at(field).getFieldName() == "START") {																		/*of the field.*/
		cout << "YOU LANDED EXACTLY ON START AND GOT 4000!\n\n";
		system("pause");
		cout << "\n" << classPlayerVector->at(*thisPlayer).getPlayerMoney() << "\x1B[32m + 4000\033[0m";
		classPlayerVector->at(*thisPlayer).addPlayerMoney(4000);
		cout << "\nNEW MONEY: " << classPlayerVector->at(*thisPlayer).getPlayerMoney() << "\n\n";
	}
	else if (classGameFieldVector->at(field).getFieldName() == "COMMUNITY FIELD") {
		cout << "YOU LANDED ON A COMMUNITY FIELD!\n\n";
		system("pause");
		eventsAndCommunityFields(classGameFieldVector, classPlayerVector, thisPlayer);
	}
	else if (classGameFieldVector->at(field).getFieldName() == "INCOME TAX") {
		cout << "YOU NEED TO PAY 2000 INCOME TAX!\n\n";
		system("pause");
		cout << "\n" << classPlayerVector->at(*thisPlayer).getPlayerMoney() << "\x1B[31m - 2000\033[0m";
		classPlayerVector->at(*thisPlayer).losePlayerMoney(2000);
		cout << "\nNEW MONEY: " << classPlayerVector->at(*thisPlayer).getPlayerMoney() << "\n\n";
	}
	else if (classGameFieldVector->at(field).getFieldName() == "EVENT FIELD") {
		cout << "YOU LANDED ON AN EVENT FIELD!\n\n";
		system("pause");
		eventsAndCommunityFields(classGameFieldVector, classPlayerVector, thisPlayer);
	}
	else if (classGameFieldVector->at(field).getFieldName() == "VISIT/JAIL") {
		cout << "You are at VISIT/JAIL!\n\n";
		for (int x = 0; x < classPlayerVector->size(); x++) {
			if (classPlayerVector->at(x).getIsInJail() == true) {
				cout << "Say HI to " << classPlayerVector->at(x).getPlayerName() << "\n";
			}
		}
		cout << "\n";
	}
	else if (classGameFieldVector->at(field).getFieldName() == "BANK") {
		cout << "You are at the bank.\n\n";
		cout << "Roll the dices and add as many percent to your money as shown on the dices!\n\n";
		system("pause");
		int perecent = rollDice();
		cout << "\n" << perecent << " percent were added to your money!\n";
		cout << "\n" << classPlayerVector->at(*thisPlayer).getPlayerMoney() << "\x1B[32m + " << perecent << " %\033[0m";
		classPlayerVector->at(*thisPlayer).addPlayerMoney(classPlayerVector->at(*thisPlayer).getPlayerMoney() * perecent / 100);
		cout << "\nNEW MONEY: " << classPlayerVector->at(*thisPlayer).getPlayerMoney() << "\n\n";
	}
	else if (classGameFieldVector->at(field).getFieldName() == "FREE PARKING") {
		cout << "FREE PARKING: Nothing happens here.\n\n";
	}
	else if (classGameFieldVector->at(field).getFieldName() == "JAIL") {
		cout << "YOU HAVE TO GO TO JAIL!\n\n";
		classPlayerVector->at(*thisPlayer).setIsInJail(true);				/*Set the value of isInJail in classPlayer to TRUE. */
		for (int x = 0; x < 40; x++) {										/*Afterwards the player is put on the VISIT/JAIL field.*/
			classPlayerVector->at(*thisPlayer).setNewPosition(1);
			if (classPlayerVector->at(*thisPlayer).getCurrentPosition() == 10) {
				break;
			}
		}
		if (classPlayerVector->at(*thisPlayer).getHasFreeJailCard() == true) {
			int userInput;
			cout << "You have a free from jail card!\n\n";
			cout << "Do you want to redeem?\n\n";
			cout << "[1] YES\n";
			cout << "[2] NO\n\n";
			cout << "Option: ";
			cin >> userInput;
			if (userInput == 1) {
				classPlayerVector->at(*thisPlayer).setIsInJail(false);
				classPlayerVector->at(*thisPlayer).setHasFreeJailCard(false);
				cout << "\n";
			}
		}
	}
	else if (classGameFieldVector->at(field).getFieldName() == "ADDITIONAL TAX") {
		cout << "YOU NEED TO PAY 1000 ADDITIONAL TAX!\n\n";
		system("pause");
		cout << "\n" << classPlayerVector->at(*thisPlayer).getPlayerMoney() << "\x1B[31m - 1000\033[0m";
		classPlayerVector->at(*thisPlayer).losePlayerMoney(1000);
		cout << "\nNEW MONEY: " << classPlayerVector->at(*thisPlayer).getPlayerMoney() << "\n\n";
	}
	system("pause");
}

void purchasAbleFields(vector <classGameField>* classGameFieldVector, vector <classPlayer>* classPlayerVector, int* thisPlayer) {
purchasAbleFieldsBegin:
	int field = classPlayerVector->at(*thisPlayer).getCurrentPosition();
	int userInput;
	/*If the field is still available to buy.*/
	if (classGameFieldVector->at(field).getIsAvailable() == true) {
		system("cls");
		cout << classGameFieldVector->at(field).getFieldName() << "\n\n";
		cout << "PRICE:\t" << classGameFieldVector->at(field).getPrice();
		cout << "\nMONEY:\t" << classPlayerVector->at(*thisPlayer).getPlayerMoney() << "\n\n";
		cout << "[1] BUY\n";
		cout << "[2] INFO\n";
		cout << "[3] CONTINUE\n";
		cout << "\nOption: ";
		cin >> userInput;
		if (userInput == 1) {
			if (classPlayerVector->at(*thisPlayer).getPlayerMoney() <= classGameFieldVector->at(field).getPrice()) {
				system("cls");
				cout << "You don't have enough money to purchase this field!\n\n";
				system("pause");
				goto purchasAbleFieldsBegin;
			}

			if (classGameFieldVector->at(field).getFieldType() != "Port") {												/*Execute this section if the bought field is NOT a port.*/
				cout << "\n";
				cout << classPlayerVector->at(*thisPlayer).getPlayerMoney() << "\x1B[31m - ";
				cout << classGameFieldVector->at(field).getPrice();
				cout << "\033[0m\n";
				classPlayerVector->at(*thisPlayer).losePlayerMoney(classGameFieldVector->at(field).getPrice());			/*Buying player loses money.*/
				cout << "NEW MONEY: " << classPlayerVector->at(*thisPlayer).getPlayerMoney();
				classGameFieldVector->at(field).setBelongsTo(classPlayerVector->at(*thisPlayer).getPlayerName());		/*Variable belongsTo from classGameField is set to the name of the buying player.*/
				classGameFieldVector->at(field).setIsAvailable(false);													/*Variable isAvailable from classGameField is set to false after buying the field.*/
				classGameFieldVector->at(field).setBelongingNumber(*thisPlayer);										/*Variable belongingNUmber from classGameField is set to the position of the buying player in the playerVector.*/
				classPlayerVector->at(*thisPlayer).addMyField(field);													/*Number of the field is pushed to the vector myField of classPlayer.*/
				classPlayerVector->at(*thisPlayer).addToMyGroupStrings(classGameFieldVector->at(field).getFieldName(), classGameFieldVector->at(field).getGroupPosition());
				classPlayerVector->at(*thisPlayer).addToMyGroup(1, classGameFieldVector->at(field).getGroupPosition());
				doubleRentOnFullGroup(classGameFieldVector, classPlayerVector);											/*Call the function doubleRentOnFullGroup() and hand over the vectors classGameFieldVector and classPlayerVector.*/
				cout << "\n\n";
				system("pause");
			}
			else if (classGameFieldVector->at(field).getFieldType() == "Port") {										/*Execute this section if the bought field IS a port.*/
				cout << "\n";
				cout << classPlayerVector->at(*thisPlayer).getPlayerMoney() << "\x1B[31m - ";
				cout << classGameFieldVector->at(field).getPrice();
				cout << "\033[0m\n";
				classPlayerVector->at(*thisPlayer).losePlayerMoney(classGameFieldVector->at(field).getPrice());			/*Buying player loses money.*/
				cout << "NEW MONEY: " << classPlayerVector->at(*thisPlayer).getPlayerMoney();
				classGameFieldVector->at(field).setBelongsTo(classPlayerVector->at(*thisPlayer).getPlayerName());		/*Variable belongsTo from classGameField is set to the name of the buying player.*/
				classGameFieldVector->at(field).setIsAvailable(false);													/*Variable isAvailable from classGameField is set to false after buying the field.*/
				classGameFieldVector->at(field).setBelongingNumber(*thisPlayer);										/*Variable belongingNUmber from classGameField is set to the position of the buying player in the playerVector.*/
				classPlayerVector->at(*thisPlayer).addMyField(field);													/*Number of the field is pushed to the vector myField of classPlayer.*/
				classPlayerVector->at(*thisPlayer).addToMyGroupStrings(classGameFieldVector->at(field).getFieldName(), classGameFieldVector->at(field).getGroupPosition());
				classPlayerVector->at(*thisPlayer).addToMyGroup(1, classGameFieldVector->at(field).getGroupPosition());
				classPlayerVector->at(*thisPlayer).addMyPort(1);														/*Call the function addMyPorts() and hand over the value 1.*/
				calcPortRent(classGameFieldVector, classPlayerVector);													/*Call the function calcPortRent() and hand over the vectors classGameFieldVector and classPlayerVector.*/
				cout << "\n\n";
				system("pause");
			}
		}
		else if (userInput == 2 && classGameFieldVector->at(field).getGroupPosition() != 0) {
			system("cls");																						/*Displaying the info of the field.*/
			cout << classGameFieldVector->at(field).getFieldName();
			cout << "\n\nPrice Per House:\t" << classGameFieldVector->at(field).getPricePerHouse();
			cout << "\n\nRent:\t\t\tBase:\t\t" << classGameFieldVector->at(field).getBaseRent();
			cout << "\n\t\t\tFull group:\t" << classGameFieldVector->at(field).getBaseRent() * 2;
			cout << "\n\n\t\t\tWith 1 House:\t" << classGameFieldVector->at(field).getBaseRent() * 4;
			cout << "\n\t\t\tWith 2 Houses:\t" << classGameFieldVector->at(field).getBaseRent() * 12;
			cout << "\n\t\t\tWith 3 Houses:\t" << classGameFieldVector->at(field).getBaseRent() * 24;
			cout << "\n\t\t\tWith 4 Houses:\t" << classGameFieldVector->at(field).getBaseRent() * 36;
			cout << "\n\t\t\tWith HOTEL:\t" << classGameFieldVector->at(field).getBaseRent() * 48;
			cout << "\n\n";
			system("pause");
			goto purchasAbleFieldsBegin;
		}
		else if (userInput == 2 && classGameFieldVector->at(field).getGroupPosition() == 0) {
			system("cls");																						/*Displaying the info of the field when it is a port.*/
			cout << classGameFieldVector->at(field).getFieldName();
			cout << "\n\nRent:\t\t\t1 Port:\t\t" << classGameFieldVector->at(field).getBaseRent();
			cout << "\n\t\t\t2 Ports:\t" << classGameFieldVector->at(field).getBaseRent() * 2;
			cout << "\n\t\t\t3 Ports:\t" << classGameFieldVector->at(field).getBaseRent() * 4;
			cout << "\n\t\t\t4 Ports:\t" << classGameFieldVector->at(field).getBaseRent() * 8;
			cout << "\n\n";
			system("pause");
			goto purchasAbleFieldsBegin;
		}
		else if (userInput == 3) { cout << "\n"; system("Pause"); }
		else { goto purchasAbleFieldsBegin; }
	}
	/*If the field is not available to buy and does NOT belong to the player who landed on it.*/
	else if (classGameFieldVector->at(field).getIsAvailable() == false && classGameFieldVector->at(field).getBelongsTo() != classPlayerVector->at(*thisPlayer).getPlayerName()) {
		system("cls");
		cout << classGameFieldVector->at(field).getFieldName() << "\n\n";
		cout << "BELONGS TO:\t" << classGameFieldVector->at(field).getBelongsTo();
		if (classGameFieldVector->at(field).getAmoutOfHouses() <= 4) {
			cout << "\nHOUSES: \t" << classGameFieldVector->at(field).getAmoutOfHouses() << "\n\n";
		}
		else { cout << "\nHOUSES: \t1 HOTEL\n"; }
		cout << "RENT:\t" << classGameFieldVector->at(field).getRent();
		cout << "\nMONEY:\t" << classPlayerVector->at(*thisPlayer).getPlayerMoney() << "\n\n";
		cout << "[1] PAY\n";
		cout << "Option: ";
		cin >> userInput;
		if (userInput != 1) { goto purchasAbleFieldsBegin; }
		if (classPlayerVector->at(classGameFieldVector->at(field).getBelongingNumber()).getIsInJail() == true) {									/*Check if the receiving player is in jail.*/
			cout << "\n\nThis player is in jail!\nYou don't need to pay rent!\n\n";
			system("pause");
		}
		else {
			cout << "\n";
			cout << classPlayerVector->at(*thisPlayer).getPlayerName() << ":\n";
			cout << classPlayerVector->at(*thisPlayer).getPlayerMoney() << "\x1B[31m - ";
			cout << classGameFieldVector->at(field).getRent();
			cout << "\033[0m\n";
			classPlayerVector->at(*thisPlayer).losePlayerMoney(classGameFieldVector->at(field).getRent());											/*Money is taken from the paying player.*/
			cout << "NEW MONEY: " << classPlayerVector->at(*thisPlayer).getPlayerMoney();
			cout << "\n\n";
			cout << classPlayerVector->at(classGameFieldVector->at(field).getBelongingNumber()).getPlayerName() << ":\n";
			cout << classPlayerVector->at(classGameFieldVector->at(field).getBelongingNumber()).getPlayerMoney() << "\x1B[32m + ";
			cout << classGameFieldVector->at(field).getRent();
			cout << "\033[0m\n";
			classPlayerVector->at(classGameFieldVector->at(field).getBelongingNumber()).addPlayerMoney(classGameFieldVector->at(field).getRent());	/*Money is added to the player who posseses the field.*/
			cout << "NEW MONEY: " << classPlayerVector->at(classGameFieldVector->at(field).getBelongingNumber()).getPlayerMoney();
			cout << "\n\n";
			system("pause");
		}
	}
	/*If the field is not available to buy and belongs to the player who landed on it.*/
	else if (classGameFieldVector->at(field).getIsAvailable() == false && classGameFieldVector->at(field).getBelongsTo() == classPlayerVector->at(*thisPlayer).getPlayerName()) {
		system("cls");
		cout << classGameFieldVector->at(field).getFieldName() << "\n\n";
		cout << "BELONGS TO:\t" << classGameFieldVector->at(field).getBelongsTo();
		if (classGameFieldVector->at(field).getAmoutOfHouses() <= 4) {
			cout << "\nHOUSES: \t" << classGameFieldVector->at(field).getAmoutOfHouses();
		}
		else { cout << "\nHOUSES: \t1 HOTEL"; }
		cout << "\nPrice Per House:\t" << classGameFieldVector->at(field).getPricePerHouse();
		cout << "\nMONEY:\t" << classPlayerVector->at(*thisPlayer).getPlayerMoney() << "\n\n";
		cout << "[1] BUY HOUSE/HOTEL\n";
		cout << "[2] INFO\n";
		cout << "[3] CONTINUE";
		cout << "\n\nOption: ";
		cin >> userInput;
		if (userInput == 1) {
			if (classPlayerVector->at(*thisPlayer).getPlayerMoney() <= classGameFieldVector->at(field).getPricePerHouse()) {
				system("cls");
				cout << "You don't have enough money to purchase a house!\n\n";
				system("pause");
				goto purchasAbleFieldsBegin;
			}
			if (classGameFieldVector->at(field).getAmoutOfHouses() == 5) {					/*Checking if all houses are already built*/
				system("cls");																/*on this field. If no, the player has the */
				cout << "All houses were built on this field!\n\n";							/*option to buy a house. Then the amount of*/
				system("pause");															/*houses and the rent will be increased.*/
				goto purchasAbleFieldsBegin;
			}
			else {
				/*Checking if the player posseses the full group and is able to build houses.*/
				if (classPlayerVector->at(*thisPlayer).checkforFullGroup(classGameFieldVector->at(field).getGroupPosition(), classGameFieldVector->at(field).getFieldType()) == true) {
					int amountOfHouses = classGameFieldVector->at(field).getAmoutOfHouses();
					int baseRent = classGameFieldVector->at(field).getBaseRent();
					cout << "\n";
					cout << classPlayerVector->at(*thisPlayer).getPlayerMoney() << "\x1B[31m - ";
					cout << classGameFieldVector->at(field).getPricePerHouse();
					cout << "\033[0m\n";
					classPlayerVector->at(*thisPlayer).losePlayerMoney(classGameFieldVector->at(field).getPricePerHouse());
					cout << "NEW MONEY: " << classPlayerVector->at(*thisPlayer).getPlayerMoney() << "\n";
					classGameFieldVector->at(field).increaseAmountOfHouses(1);
					if (classGameFieldVector->at(field).getAmoutOfHouses() == 1) {
						classGameFieldVector->at(field).increaseRent(classGameFieldVector->at(field).getBaseRent(), 4);				/*The rent will be increased,*/
						classPlayerVector->at(*thisPlayer).addHouses(1);															/*based on how many houses*/
					}																												/*are already built on the field.*/
					else if (classGameFieldVector->at(field).getAmoutOfHouses() == 2) {												/*Additionally the amount of */
						classGameFieldVector->at(field).increaseRent(classGameFieldVector->at(field).getBaseRent(), 12);			/*playerHouses in classPlayer will be*/
						classPlayerVector->at(*thisPlayer).addHouses(1);															/*increased for each built house.*/
					}																												/*If a hotel was built, 4 houses */
					else if (classGameFieldVector->at(field).getAmoutOfHouses() == 3) {												/*will be subtracted from playerHouses*/
						classGameFieldVector->at(field).increaseRent(classGameFieldVector->at(field).getBaseRent(), 24);			/*and the amount of playerHotels*/
						classPlayerVector->at(*thisPlayer).addHouses(1);															/*in classPlayer will be increased.*/
					}
					else if (classGameFieldVector->at(field).getAmoutOfHouses() == 4) {
						classGameFieldVector->at(field).increaseRent(classGameFieldVector->at(field).getBaseRent(), 36);
						classPlayerVector->at(*thisPlayer).addHouses(1);
					}
					else if (classGameFieldVector->at(field).getAmoutOfHouses() == 5) {
						classGameFieldVector->at(field).increaseRent(classGameFieldVector->at(field).getBaseRent(), 48);
						classPlayerVector->at(*thisPlayer).removeHouses(4);
						classPlayerVector->at(*thisPlayer).addHotels(1);
					}
					cout << "\nHOUSES\x1B[32m + 1\033[0m: " << classGameFieldVector->at(field).getAmoutOfHouses() << " now\n\n";
					cout << "\nNEW RENT: " << classGameFieldVector->at(field).getRent() << "\n\n";
					system("pause");
				}
				else if (classGameFieldVector->at(field).getFieldType() == "Port") {		/*Checking if the current field is a port.*/
					system("cls");
					cout << "You can't build on ports!\n\n";
					system("pause");
					goto purchasAbleFieldsBegin;
				}
				else {
					system("cls");
					cout << "You don't have all fields of this group!\n\n";
					system("pause");
					goto purchasAbleFieldsBegin;
				}
			}
		}
		else if (userInput == 2) {
			system("cls");																	/*Displaying the info of the field.*/
			cout << classGameFieldVector->at(field).getFieldName();
			if (classGameFieldVector->at(field).getAmoutOfHouses() <= 4) {
				cout << "\n\nHOUSES:\t\t" << classGameFieldVector->at(field).getAmoutOfHouses();
			}
			else { cout << "\n\nHOUSES:\t\t1 HOTEL"; }
			cout << "\n\nRent:\t\t\tBase:\t\t" << classGameFieldVector->at(field).getBaseRent();
			cout << "\n\t\t\tFull group:\t" << classGameFieldVector->at(field).getBaseRent() * 2;
			cout << "\n\n\t\t\tWith 1 House:\t" << classGameFieldVector->at(field).getBaseRent() * 4;
			cout << "\n\t\t\tWith 2 Houses:\t" << classGameFieldVector->at(field).getBaseRent() * 12;
			cout << "\n\t\t\tWith 3 Houses:\t" << classGameFieldVector->at(field).getBaseRent() * 24;
			cout << "\n\t\t\tWith 4 Houses:\t" << classGameFieldVector->at(field).getBaseRent() * 36;
			cout << "\n\t\t\tWith HOTEL:\t" << classGameFieldVector->at(field).getBaseRent() * 48;
			cout << "\n\nCurrent Rent: " << classGameFieldVector->at(field).getRent();
			cout << "\n\n";
			system("pause");
			goto purchasAbleFieldsBegin;
		}
		else if (userInput == 2 && classGameFieldVector->at(field).getGroupPosition() == 0) {
			system("cls");																	/*Displaying the info of the field when it is a port.*/
			cout << classGameFieldVector->at(field).getFieldName();
			cout << "\n\nRent:\t\t\t1 Port:\t\t" << classGameFieldVector->at(field).getBaseRent();
			cout << "\n\t\t\t2 Ports:\t" << classGameFieldVector->at(field).getBaseRent() * 2;
			cout << "\n\t\t\t3 Ports:\t" << classGameFieldVector->at(field).getBaseRent() * 4;
			cout << "\n\t\t\t4 Ports:\t" << classGameFieldVector->at(field).getBaseRent() * 8;
			cout << "\n\nCurrent Rent: " << classGameFieldVector->at(field).getRent();
			cout << "\n\n";
			system("pause");
			goto purchasAbleFieldsBegin;
		}
	}
}

void eventsAndCommunityFields(vector <classGameField>* classGameFieldVector, vector <classPlayer>* classPlayerVector, int* thisPlayer) {
	srand(time(NULL));
	int userInput;
	int getRandomEvent = rand() % 22 + 1;
	if (getRandomEvent == 1 || getRandomEvent == 2) {	/*SPPEDING TICKET*/
	event_1:
		system("cls");
		cout << "You got a speeding ticket!\n\n";
		cout << "Pay 150!\n\n";
		cout << "[1] PAY\n";
		cout << "Option: ";
		cin >> userInput;
		if (userInput == 1) {
			cout << "\n" << classPlayerVector->at(*thisPlayer).getPlayerMoney() << "\x1B[31m - 150\033[0m\n";
			classPlayerVector->at(*thisPlayer).losePlayerMoney(150);
			cout << "NEW MONEY: " << classPlayerVector->at(*thisPlayer).getPlayerMoney() << "\n\n";
		}
		else { goto event_1; }
	}
	if (getRandomEvent == 3 || getRandomEvent == 4) {	/*RENOVATE*/
	event_2:
		int priceForHouses = classPlayerVector->at(*thisPlayer).getPlayerHouses() * 250;
		int priceForHotels = classPlayerVector->at(*thisPlayer).getPlayerHotels() * 1000;
		int totalAmount = priceForHouses + priceForHotels;
		system("cls");
		cout << "Your buildings are being renovated!\n\n";
		cout << "Pay 250 per house and 1000 per hotel!\n";
		cout << "You have to pay a total amount of " << totalAmount << "!\n\n";
		cout << "[1] PAY\n";
		cout << "Option: ";
		cin >> userInput;
		if (userInput == 1) {
			cout << "\n" << classPlayerVector->at(*thisPlayer).getPlayerMoney() << "\x1B[31m - " << totalAmount;
			cout << "\033[0m\n";
			classPlayerVector->at(*thisPlayer).losePlayerMoney(totalAmount);
			cout << "NEW MONEY: " << classPlayerVector->at(*thisPlayer).getPlayerMoney() << "\n\n";
		}
		else { goto event_2; }
	}
	if (getRandomEvent == 5 || getRandomEvent == 6) {	/*MOVE TO COPENHAGEN*/
	event_3:
		system("cls");
		cout << "Move to \x1B[35mCOPENHAGEN\033[0m!\n\n";
		cout << "Take 2000 if you pass START!\n\n";
		cout << "[1] MOVE\n";
		cout << "Option: ";
		cin >> userInput;
		if (userInput == 1) {
			for (int x = 0; x < 40; x++) {
				classPlayerVector->at(*thisPlayer).setNewPosition(1);
				if (classPlayerVector->at(*thisPlayer).getCurrentPosition() == 0) {
					cout << "\nYou passed START and got 2000!\n\n";
					classPlayerVector->at(*thisPlayer).addPlayerMoney(2000);
				}
				if (classPlayerVector->at(*thisPlayer).getCurrentPosition() == 11) {
					break;
				}
			}
		}
		else { goto event_3; }
	}
	if (getRandomEvent == 7 || getRandomEvent == 8) {	/*FRIEND'S BIRTHDAY*/
	event_4:
		system("cls");
		cout << "You have to pay for your friend's birthday!\n\n";
		cout << "Pay 500!\n\n";
		cout << "[1] PAY\n";
		cout << "Option: ";
		cin >> userInput;
		if (userInput == 1) {
			cout << "\n" << classPlayerVector->at(*thisPlayer).getPlayerMoney() << "\x1B[31m - 500\033[0m\n";
			classPlayerVector->at(*thisPlayer).losePlayerMoney(500);
			cout << "NEW MONEY: " << classPlayerVector->at(*thisPlayer).getPlayerMoney() << "\n\n";
		}
		else { goto event_4; }
	}
	if (getRandomEvent == 9 || getRandomEvent == 10) {	/*COMPANY INTERNATIONAL SUCCESS*/
	event_5:
		system("cls");
		cout << "Your company is an international success!\n\n";
		cout << "You get 1000!\n\n";
		cout << "[1] GET\n";
		cout << "Option: ";
		cin >> userInput;
		if (userInput == 1) {
			cout << "\n" << classPlayerVector->at(*thisPlayer).getPlayerMoney() << "\x1B[32m + 1000\033[0m\n";
			classPlayerVector->at(*thisPlayer).addPlayerMoney(1000);
			cout << "NEW MONEY: " << classPlayerVector->at(*thisPlayer).getPlayerMoney() << "\n\n";
		}
		else { goto event_5; }
	}
	if (getRandomEvent == 11 || getRandomEvent == 12) {	/*GO BACK 3 FIELDS*/
	event_6:
		system("cls");
		cout << "Go 3 fields ahead!\n\n";
		cout << "[1] GO\n";
		cout << "Option: ";
		cin >> userInput;
		if (userInput == 1) {
			classPlayerVector->at(*thisPlayer).setNewPosition(3);
			cout << "You went 3 fields ahead!\n\n";
		}
		else { goto event_6; }
	}
	if (getRandomEvent == 13 || getRandomEvent == 14) {	/*GET FREE JAIL CARD*/
	event_7:
		system("cls");
		cout << "You get a free from jail card!\n\n";
		cout << "[1] GET\n";
		cout << "Option: ";
		cin >> userInput;
		if (userInput == 1) {
			classPlayerVector->at(*thisPlayer).setHasFreeJailCard(true);
			cout << "\n";
		}
		else { goto event_7; }
	}
	if (getRandomEvent == 15 || getRandomEvent == 16) {	/*GET 200 FROM EVERY PLAYER*/
	event_8:
		int getAmount = (classPlayerVector->size() - 1) * 200;
		system("cls");
		cout << "Every player gives you 200!\n\n";
		cout << "[1] GET\n";
		cout << "Option: ";
		cin >> userInput;
		if (userInput == 1) {
			cout << "\n";
			for (int x = 0; x < classPlayerVector->size(); x++) {
				if (classPlayerVector->at(x).getPlayerName() != classPlayerVector->at(*thisPlayer).getPlayerName()) {
					cout << classPlayerVector->at(x).getPlayerName() << ":\t\x1B[31m - 200\033[0m\n";
					classPlayerVector->at(x).losePlayerMoney(200);
				}
			}
			cout << "\n" << classPlayerVector->at(*thisPlayer).getPlayerMoney() << "\x1B[32m + " << getAmount;
			cout << "\033[0m\n";
			classPlayerVector->at(*thisPlayer).addPlayerMoney(getAmount);
			cout << "NEW MONEY: " << classPlayerVector->at(*thisPlayer).getPlayerMoney() << "\n\n";
		}
		else { goto event_8; }
	}
	if (getRandomEvent == 17 || getRandomEvent == 18) {	/*GO TO START*/
	event_9:
		system("cls");
		cout << "Move forward to START!\n\n";
		cout << "Draw 2000!\n\n";
		cout << "[1] GO\n";
		cout << "Option: ";
		cin >> userInput;
		if (userInput == 1) {
			for (int x = 0; x < 40; x++) {
				classPlayerVector->at(*thisPlayer).setNewPosition(1);
				if (classPlayerVector->at(*thisPlayer).getCurrentPosition() == 0) {
					cout << "\n" << classPlayerVector->at(*thisPlayer).getPlayerMoney() << "\x1B[32m + 2000\033[0m\n";
					classPlayerVector->at(*thisPlayer).addPlayerMoney(2000);
					cout << "NEW MONEY: " << classPlayerVector->at(*thisPlayer).getPlayerMoney() << "\n\n";
					break;
				}
			}
		}
		else { goto event_9; }
	}
	if (getRandomEvent == 19 || getRandomEvent == 20) {	/*BELLY DANCE*/
	event_10:
		system("cls");
		cout << "Your belly dance club in cairo caused an economic damage of 2000!\n\n";
		cout << "You have to pay 2000!\n\n";
		cout << "[1] PAY\n";
		cout << "Option: ";
		cin >> userInput;
		if (userInput == 1) {
			cout << "\n" << classPlayerVector->at(*thisPlayer).getPlayerMoney() << "\x1B[31m - 2000\033[0m\n";
			classPlayerVector->at(*thisPlayer).losePlayerMoney(2000);
			cout << "NEW MONEY: " << classPlayerVector->at(*thisPlayer).getPlayerMoney() << "\n\n";
		}
		else { goto event_10; }
	}
	if (getRandomEvent == 21 || getRandomEvent == 22) {	/*ECONOMIC SCAM*/
	event_11:
		system("cls");
		cout << "You got arrested for an economic scam!\n\n";
		cout << "Move to jail!\n\n";
		cout << "[1] MOVE\n";
		cout << "Option: ";
		cin >> userInput;
		if (userInput == 1) {
			for (int x = 0; x < 40; x++) {
				classPlayerVector->at(*thisPlayer).setNewPosition(1);
				if (classPlayerVector->at(*thisPlayer).getCurrentPosition() == 0) {
					classPlayerVector->at(*thisPlayer).setIsInJail(true);
					break;
				}
			}
			if (classPlayerVector->at(*thisPlayer).getHasFreeJailCard() == true) {
				int getFree;
				cout << "\n\nYou have a free from jail card!\n\n";
				cout << "Do you want to redeem?\n\n";
				cout << "[1] YES\n";
				cout << "[2] NO\n\n";
				cout << "Option: ";
				cin >> getFree;
				if (getFree == 1) {
					classPlayerVector->at(*thisPlayer).setIsInJail(false);
					classPlayerVector->at(*thisPlayer).setHasFreeJailCard(false);
					cout << "\n";
				}
			}
		}
		else { goto event_11; }
	}
}

void doubleRentOnFullGroup(vector <classGameField>* classGameFieldVector, vector <classPlayer>* classPlayerVector) {	/*Checking if the player posseses the full group and double the rent.*/
	for (int y = 0; y < classPlayerVector->size(); y++) {
		for (int x = 0; x < classGameFieldVector->size(); x++) {
			if (classPlayerVector->at(y).checkforFullGroup(classGameFieldVector->at(x).getGroupPosition(), classGameFieldVector->at(x).getFieldType()) == true && classGameFieldVector->at(x).getRentWasDoubled() == false) {
				classGameFieldVector->at(x).setRent(classGameFieldVector->at(x).getBaseRent() * 2);
				classGameFieldVector->at(x).setRentWasDoubled(true);
			}
		}
	}
}

void calcPortRent(vector <classGameField>* classGameFieldVector, vector <classPlayer>* classPlayerVector) {
	for (int x = 0; x < classPlayerVector->size(); x++) {
		for (int y = 0; y < classGameFieldVector->size(); y++) {
			if (classGameFieldVector->at(y).getFieldType() == "Port" && classPlayerVector->at(x).getMyPort() > 0 && classGameFieldVector->at(y).getBelongsTo() == classPlayerVector->at(x).getPlayerName()) {
				classGameFieldVector->at(y).setRent(classGameFieldVector->at(y).getBaseRent() * classPlayerVector->at(x).getMyPort());
			}
			if (classGameFieldVector->at(y).getFieldType() == "Port" && classPlayerVector->at(x).getMyPort() == 3 && classGameFieldVector->at(y).getBelongsTo() == classPlayerVector->at(x).getPlayerName()) {
				classGameFieldVector->at(y).setRent(classGameFieldVector->at(y).getBaseRent() * classPlayerVector->at(x).getMyPort() + 250);
			}
			if (classGameFieldVector->at(y).getFieldType() == "Port" && classPlayerVector->at(x).getMyPort() == 4 && classGameFieldVector->at(y).getBelongsTo() == classPlayerVector->at(x).getPlayerName()) {
				classGameFieldVector->at(y).setRent(classGameFieldVector->at(y).getBaseRent() * classPlayerVector->at(x).getMyPort() * 2);
			}
		}
	}
}

bool sellHouse(vector <classGameField>* classGameFieldVector, vector <classPlayer>* classPlayerVector, int* thisPlayer) {
sellHouseBegin:
	int userInput;
	int chooseField;
	string isHotel;
	system("cls");
	cout << "On which field do you want to sell a house?\n\n";
	for (int displayFields = 0; displayFields < classGameFieldVector->size(); displayFields++) {
		if (classPlayerVector->at(*thisPlayer).getPlayerName() == classGameFieldVector->at(displayFields).getBelongsTo()) {
			if (classGameFieldVector->at(displayFields).getAmoutOfHouses() == 5) {
				isHotel = " (1 HOTEL)\t";
			}
			else {
				isHotel = "\t\t";
			}
			cout << "[" << displayFields << "] " << classGameFieldVector->at(displayFields).getFieldName() << "\tHouses: " << classGameFieldVector->at(displayFields).getAmoutOfHouses() << isHotel << "Price Per House: " << classGameFieldVector->at(displayFields).getPricePerHouse() << "\n";
		}
	}
	cout << "\nChoose: ";
	cin >> chooseField;
	if (chooseField > classGameFieldVector->size() || classGameFieldVector->at(chooseField).getBelongsTo() != classPlayerVector->at(*thisPlayer).getPlayerName()) {
		cout << "\nField not found!\n";
		system("pause");
		return false;
	}
	else if (classGameFieldVector->at(chooseField).getAmoutOfHouses() == 0) {
		cout << "\nNo houses are built on this field!\n";
		system("pause");
		return false;
	}
	else {
		cout << "\nAre you sure?";
		cout << "\n\n[1] Yes";
		cout << "\n[2] Abort";
		cout << "\n\nOption: ";
		cin >> userInput;
		if (userInput == 1) {
			classGameFieldVector->at(chooseField).lowerAmountOfHouses(1);
			cout << "\n" << classPlayerVector->at(*thisPlayer).getPlayerMoney() << "\x1B[32m + " << classGameFieldVector->at(chooseField).getPricePerHouse();
			cout << "\033[0m\n";
			classPlayerVector->at(*thisPlayer).addPlayerMoney(classGameFieldVector->at(chooseField).getPricePerHouse());
			cout << "NEW MONEY: " << classPlayerVector->at(*thisPlayer).getPlayerMoney() << "\n";
			cout << "\nHOUSES\x1B[31m - 1\033[0m: " << classGameFieldVector->at(chooseField).getAmoutOfHouses() << " now\n\n";
			if (classGameFieldVector->at(chooseField).getAmoutOfHouses() == 4) {
				classPlayerVector->at(*thisPlayer).removeHotels(1);
				classGameFieldVector->at(chooseField).increaseRent(classGameFieldVector->at(chooseField).getBaseRent(), 36);
			}
			if (classGameFieldVector->at(chooseField).getAmoutOfHouses() == 3) {
				classPlayerVector->at(*thisPlayer).removeHouses(1);
				classGameFieldVector->at(chooseField).increaseRent(classGameFieldVector->at(chooseField).getBaseRent(), 24);
			}
			if (classGameFieldVector->at(chooseField).getAmoutOfHouses() == 2) {
				classPlayerVector->at(*thisPlayer).removeHouses(1);
				classGameFieldVector->at(chooseField).increaseRent(classGameFieldVector->at(chooseField).getBaseRent(), 12);
			}
			if (classGameFieldVector->at(chooseField).getAmoutOfHouses() == 1) {
				classPlayerVector->at(*thisPlayer).removeHouses(1);
				classGameFieldVector->at(chooseField).increaseRent(classGameFieldVector->at(chooseField).getBaseRent(), 4);
			}
			if (classGameFieldVector->at(chooseField).getAmoutOfHouses() == 0) {
				classPlayerVector->at(*thisPlayer).removeHouses(1);
				classGameFieldVector->at(chooseField).increaseRent(classGameFieldVector->at(chooseField).getBaseRent(), 2);
			}
			cout << "\nNEW RENT: " << classGameFieldVector->at(chooseField).getRent() << "\n\n";
			system("pause");
			return true;
		}
		else if (userInput == 2) {
			system("pause");
			return false;
		}
	}
	system("pause");
}

int rollDice() {					/*This function is planned to be only used when rolling the dices at the bank-field.*/
	system("cls");
	cout << "Rolling Dices...\n";	/*Two variables are calculated randomly*/
	int dice_1;						/*and then added together to a new*/
	int dice_2;						/*variable which represents*/
	int diceSum;					/*the sum of both dices.*/
	srand(time(NULL));
	this_thread::sleep_for(chrono::seconds(1));
	dice_1 = rand() % 6 + 1;
	this_thread::sleep_for(chrono::seconds(1));
	dice_2 = rand() % 6 + 1;
	diceSum = dice_1 + dice_2;
	system("cls");
	cout << "You rolled " << dice_1 << " and " << dice_2 << " (" << diceSum << ")\n\n";
	system("pause");
	return diceSum;
}
