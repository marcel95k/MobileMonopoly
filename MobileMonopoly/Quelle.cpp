#include <vector>
#include <iostream>
#include <Windows.h>
#include <stdio.h>
#include <string>
#include <stdlib.h>
#include <math.h>
#include <chrono>
#include <thread>
#include <time.h>

#include "classPlayer.h"
#include "classBank.h"
#include "classGameField.h"

using namespace std;

void setUpGameField(vector <string>* gameFieldStringsValue);
void setUpPlayerStats(vector <classGameField>* classGameFieldVector, vector <classPlayer>* classPlayerVector);
void gameRound(vector <classGameField>* classGameFieldVector, vector <classPlayer>* classPlayerVector);
void eventFields(vector <classGameField>* classGameFieldVector, vector <classPlayer>* classPlayerVector, int* thisPlayer);
void purchasAbleFields(vector <classGameField>* classGameFieldVector, vector <classPlayer>* classPlayerVector, int* thisPlayer);
void trade(vector <classGameField>* classGameFieldVector, vector <classPlayer>* classPlayerVector, int* thisPlayer, int* selectedPlayer);
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
		classPlayer playerObj(name, 15000);						/*15000 is the amount of money for each player (hardcoded for now).*/
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
			cout << "You are in jail!\nPay 100!\n\n";					/*and let the player pay.*/
			system("pause");											/*Afterwards the player is put on the VISIT field.*/
			cout << "\n";
			cout << classPlayerVector->at(thisPlayer).getPlayerMoney() << "\x1B[31m - 100\033[0m\n";
			classPlayerVector->at(thisPlayer).losePlayerMoney(100);
			cout << "NEW MONEY: " << classPlayerVector->at(thisPlayer).getPlayerMoney() << "\n\n";
			classPlayerVector->at(thisPlayer).goBackOnField(20);
			classPlayerVector->at(thisPlayer).setIsInJail(false);
			system("pause");
			system("cls");
		}
		for (int listPlayers = 0; listPlayers < classPlayerVector->size(); listPlayers++) {
			cout << displayPlayers.at(listPlayers) << ": " << classGameFieldVector->at(classPlayerVector->at(listPlayers).getCurrentPosition()).getFieldName() << "\n";
		}
		cout << "\n\n\n\n";
		cout << "NAME:\t" << classPlayerVector->at(thisPlayer).getPlayerName() << "\n";
		cout << "MONEY:\t" << classPlayerVector->at(thisPlayer).getPlayerMoney() << "\n";
		cout << "CURRENT FIELD:\t" << classGameFieldVector->at(classPlayerVector->at(thisPlayer).getCurrentPosition()).getFieldName() << "\n\n";
		cout << "[1] Roll Dice\n";
		cout << "[2] TRADE\n";
		cout << "[3] VIEW PLAYER INFO\n";
		cout << "[4] RESIGN\n\n";
		cout << "Option: ";
		cin >> userInput;

		if (userInput == 1) {
			classPlayerVector->at(thisPlayer).setNewPosition(rollDice());															/*Sets the new position of the player by calling the function rollDice().*/
			if (classGameFieldVector->at(classPlayerVector->at(thisPlayer).getCurrentPosition()).getIsPurchasable() == false) {		/*Then it will be checked if the player landed on a purchasable field or not.*/
				eventFields(classGameFieldVector, classPlayerVector, &thisPlayer);
			}
			else if (classGameFieldVector->at(classPlayerVector->at(thisPlayer).getCurrentPosition()).getIsPurchasable() == true) {
				purchasAbleFields(classGameFieldVector, classPlayerVector, &thisPlayer);
			}
		}

		else if (userInput == 2) {
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
				trade(classGameFieldVector, classPlayerVector, &thisPlayer, &tradePartner);
			}
		}

		else if (userInput == 3) {																									/****************************************/
			system("cls");																											/*Viewing the info of a selected player.*/
			cout << "Of which player do you want to see the info?\n\n";																/*Currently viewing:					*/
			for (int listPlayers = 0; listPlayers < classPlayerVector->size(); listPlayers++) {										/*				- Playername			*/
				cout << "[" << listPlayers + 1 << "] " << classPlayerVector->at(listPlayers).getPlayerName() << "\n";				/*				- Money					*/
			}																														/*				- Current position		*/
			cout << "\nChoose: ";																									/*				- Possessing fields		*/
			cin >> userInput;																										/*				  (Strings)				*/
			cout << "\nNAME:\t\t" << classPlayerVector->at(userInput - 1).getPlayerName() << "\n";									/****************************************/
			cout << "MONEY:\t\t" << classPlayerVector->at(userInput - 1).getPlayerMoney() << "\n";
			cout << "CURRENT FIELD:\t" << classGameFieldVector->at(classPlayerVector->at(userInput - 1).getCurrentPosition()).getFieldName() << "\n\n";
			cout << "POSSESSIONS: ";
			classPlayerVector->at(userInput - 1).getMyGroupStrings();
			cout << "\n";
			system("pause");
			thisPlayer--;
		}

		else { goto gameRoundBegin; }


		if (thisPlayer == classPlayerVector->size() - 1) {		/*Check if the iteration through the vector classPlayerVector*/
			thisPlayer = -1;									/*is finished and reset the iterator.*/
		}
	}
}

void eventFields(vector <classGameField>* classGameFieldVector, vector <classPlayer>* classPlayerVector, int* thisPlayer) {		/*Event fields:*/
	int field = classPlayerVector->at(*thisPlayer).getCurrentPosition();														/*The string of the event fields in checked*/
	system("cls");																												/*and make happen the event based on the name*/
	if (classGameFieldVector->at(field).getFieldName() == "START") {															/*of the event field.*/
		cout << "YOU LANDED EXACTLY ON START AND GOT 4000!\n\n";
		system("pause");
		cout << "\n" << classPlayerVector->at(*thisPlayer).getPlayerMoney() << "\x1B[32m + 4000\033[0m";
		classPlayerVector->at(*thisPlayer).addPlayerMoney(4000);
		cout << "\nNEW MONEY: " << classPlayerVector->at(*thisPlayer).getPlayerMoney() << "\n\n";
	}
	else if (classGameFieldVector->at(field).getFieldName() == "COMMUNITY FIELD") {
		cout << "YOU LANDED ON A COMMUNITY FIELD!\n\n";
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
	}
	else if (classGameFieldVector->at(field).getFieldName() == "VISIT/JAIL") {
		cout << "You are at VISIT/JAIL!\n\n";
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
		classPlayerVector->at(*thisPlayer).setIsInJail(true);
	}
	else if (classGameFieldVector->at(field).getFieldName() == "ADDITIONAL TAX") {
		cout << "YOU NEED TO PAY 1000 INCOME TAX!\n\n";
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
			cout << "\n\n";
			system("pause");
		}
		else if (userInput == 2 && classGameFieldVector->at(field).getGroupPosition() != 0) {
			system("cls");																						/*Displaying the info of the field.*/
			cout << classGameFieldVector->at(field).getFieldName();
			cout << "\n\nPrice Per House:\t" << classGameFieldVector->at(field).getPricePerHouse();
			cout << "\n\nRent:\t\t\tBase:\t\t" << classGameFieldVector->at(field).getBaseRent();
			cout << "\n\t\t\tFull group:\t" << classGameFieldVector->at(field).getBaseRent() * 2;
			cout << "\n\n\t\t\tWith 1 House:\t" << classGameFieldVector->at(field).getBaseRent() * 3;
			cout << "\n\t\t\tWith 2 Houses:\t" << classGameFieldVector->at(field).getBaseRent() * 3 * 2;
			cout << "\n\t\t\tWith 3 Houses:\t" << classGameFieldVector->at(field).getBaseRent() * 3 * 2 * 2;
			cout << "\n\t\t\tWith 4 Houses:\t" << classGameFieldVector->at(field).getBaseRent() * 3 * 2 * 2 * 2;
			cout << "\n\t\t\tWith HOTEL:\t" << classGameFieldVector->at(field).getBaseRent() * 3 * 2 * 2 * 2 * 2;
			cout << "\n\n";
			system("pause");
			goto purchasAbleFieldsBegin;
		}
		else if (userInput == 2 && classGameFieldVector->at(field).getGroupPosition() == 0) {
			system("cls");																						/*Displaying the info of the field when it is a port.*/
			cout << classGameFieldVector->at(field).getFieldName();
			cout << "\n\nRent:\t\t\t1 Port:\t\t" << classGameFieldVector->at(field).getBaseRent();
			cout << "\n\t\t\t2 Ports:\t" << classGameFieldVector->at(field).getBaseRent() * 2;
			cout << "\n\t\t\t3 Ports:\t" << classGameFieldVector->at(field).getBaseRent() * 2 * 2;
			cout << "\n\t\t\t4 Ports:\t" << classGameFieldVector->at(field).getBaseRent() * 2 * 2 * 2;
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
		cout << "\nHOUSES: \t" << classGameFieldVector->at(field).getAmoutOfHouses() << "\n\n";
		cout << "RENT:\t" << classGameFieldVector->at(field).getRent();
		cout << "\nMONEY:\t" << classPlayerVector->at(*thisPlayer).getPlayerMoney() << "\n\n";
		cout << "[1] PAY\n";
		cout << "Pay: ";
		cin >> userInput;
		if (userInput != 1) { goto purchasAbleFieldsBegin; }
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
	/*If the field is not available to buy and belongs to the player who landed on it.*/
	else if (classGameFieldVector->at(field).getIsAvailable() == false && classGameFieldVector->at(field).getBelongsTo() == classPlayerVector->at(*thisPlayer).getPlayerName()) {
		system("cls");
		cout << classGameFieldVector->at(field).getFieldName() << "\n\n";
		cout << "BELONGS TO:\t" << classGameFieldVector->at(field).getBelongsTo();
		cout << "\nHOUSES: \t" << classGameFieldVector->at(field).getAmoutOfHouses();
		cout << "\nPrice Per House:\t" << classGameFieldVector->at(field).getPricePerHouse();
		cout << "\nMONEY:\t" << classPlayerVector->at(*thisPlayer).getPlayerMoney() << "\n\n";
		cout << "[1] BUY HOUSE/HOTEL\n";
		cout << "[2] INFO\n";
		cout << "[3] CONTINUE\n";
		cin >> userInput;
		if (userInput == 1) {
			if (classGameFieldVector->at(field).getAmoutOfHouses() == 5) {					/*Checking if all houses are already built*/
				system("cls");																/*on this field. If no, the player has the */
				cout << "All houses were built on this field!\n\n";							/*option to buy a house. Then the amount of*/
				system("pause");															/*houses and the rent will be increased.*/
				goto purchasAbleFieldsBegin;
			}
			else {
				/*Checking if the player posseses the full group.*/
				if (classPlayerVector->at(*thisPlayer).checkforFullGroup(classGameFieldVector->at(field).getGroupPosition(), classGameFieldVector->at(field).getFieldType()) == true) {
					cout << "\n";
					cout << classPlayerVector->at(*thisPlayer).getPlayerMoney() << "\x1B[31m - ";
					cout << classGameFieldVector->at(field).getPricePerHouse();
					cout << "\033[0m\n";
					classPlayerVector->at(*thisPlayer).losePlayerMoney(classGameFieldVector->at(field).getPricePerHouse());
					cout << "NEW MONEY: " << classPlayerVector->at(*thisPlayer).getPlayerMoney() << "\n";
					classGameFieldVector->at(field).increaseAmountOfHouses(1);
					classGameFieldVector->at(field).increaseRent(2);
					cout << "\nHOUSES\x1B[32m + 1\033[0m: " << classGameFieldVector->at(field).getAmoutOfHouses() << " now\n\n";
					cout << "\nNEW RENT: " << classGameFieldVector->at(field).getRent() << "\n\n";
					system("pause");
				}
				else if (classGameFieldVector->at(field).getFieldType() == "Port") {			/*Checking if the current field is a port.*/
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
			cout << "\n\nHOUSES:\t\t" << classGameFieldVector->at(field).getAmoutOfHouses();
			cout << "\n\nRent:\t\t\tBase:\t\t" << classGameFieldVector->at(field).getBaseRent();
			cout << "\n\t\t\tFull group:\t" << classGameFieldVector->at(field).getBaseRent();
			cout << "\n\n\t\t\tWith 1 House:\t" << classGameFieldVector->at(field).getBaseRent() * 2;
			cout << "\n\t\t\tWith 2 Houses:\t" << classGameFieldVector->at(field).getBaseRent() * 2 * 2;
			cout << "\n\t\t\tWith 3 Houses:\t" << classGameFieldVector->at(field).getBaseRent() * 2 * 2 * 2;
			cout << "\n\t\t\tWith 4 Houses:\t" << classGameFieldVector->at(field).getBaseRent() * 2 * 2 * 2 * 2;
			cout << "\n\t\t\tWith HOTEL:\t" << classGameFieldVector->at(field).getBaseRent() * 2 * 2 * 2 * 2 * 2;
			cout << "\n\n";
			system("pause");
			goto purchasAbleFieldsBegin;
		}
	}
}

void trade(vector <classGameField>* classGameFieldVector, vector <classPlayer>* classPlayerVector, int* thisPlayer, int* selectedPlayer) {
	/*Used as a function to trade belogings between players.*/
}

int rollDice() {
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

