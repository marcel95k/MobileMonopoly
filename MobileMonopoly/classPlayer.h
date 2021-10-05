#pragma once
#include <iostream>
#include <vector>
#include <string>
#include <math.h>

using namespace std;

class classPlayer {
private:
	string playerName;				/*Used as the playername during the entire program.*/
	int playerMoney;				/*Used as the money for each player during the entire progam.*/
	int amountOfMyFields = 0;		/*Tells how many fields each player possesses.*/
	int currentPosition = 0;		/*Tells the current position of a player on the gamefield.*/
	vector<string>myGroupStrings[9];
	vector<int>myGroup[9];
	vector <int> myField[40];		/*Tells the number of the field belonging to the player.*/
	bool isGroup = false;
	bool isMyField = false;			/*Checks if the current field, a player is standing on belongs to the player.*/
	bool IsInJail = false;			/*Checks if the a player is in jail at the moment.*/
	bool isLendingMoney = false;	/*Checks if the a player is currently lending money for the bank.*/
public:

classPlayer::classPlayer(string nameValue, int moneyValue) {			/*Constructor of classPlayer.*/
	playerName = nameValue;												/*Hands over the value for playerName and playerMoney*/
	playerMoney = moneyValue;
	myGroupStrings->resize(9);
	myGroup->resize(9);
}

classPlayer::~classPlayer() {}		/*Destructor of classPlayer.*/

/*Calling Set-Methods*/

void classPlayer::setPlayerName(string value) {		/*Applies the handed over value to playerName.*/
	playerName = value;
}
void classPlayer::setPlayerMoney(int value) {		/*Applies the handed over value to playerMoney.*/
	playerMoney = value;
}
void classPlayer::losePlayerMoney(int value) {		/*Reduces the amount of playerMoney by the handed over value.*/
	playerMoney -= value;
}
void classPlayer::addPlayerMoney(int value) {		/*Increases the amount of playerMoney by the handed over value.*/
	playerMoney += value;
}
void classPlayer::goBackOnField(int value) {		/*Used to let the player walk in the opposite direction on the field.*/
	currentPosition -= value;
}
void classPlayer::setNewPosition(int value) {		/*Sets the new position of the player on the gamefield by adding the value of the dice to the current position.*/
	int difference = 0;								/*In case the current position plus the value of the dice exceeds the amount of 39,*/
	int diffToGo;									/*the difference is calculated and the player starts again from field 0.*/
	if (currentPosition + value == 40) {			/*2000 is added to the variable playerMoney.*/
		currentPosition = 0;
	}
	else if (currentPosition + value > 39 && currentPosition + value != 40) {
		system("cls");
		cout << "You passed START and got 2000!\n\n";
		system("pause");
		playerMoney += 2000;
		difference = 39 - currentPosition;
		diffToGo = value - 1 - difference;
		currentPosition = currentPosition + difference;
		currentPosition = 0;
		currentPosition += diffToGo;
	}
	else currentPosition += value;
}
void classPlayer::addToMyGroupStrings(string fieldName, int value) {			/*Change the string of myGroupStrings to the handed over value at the handed over position.*/
	myGroupStrings->at(value) = myGroupStrings->at(value) + fieldName + ", ";
}
void classPlayer::addToMyGroup(int value, int position) {			/*Increases the value of the position in myGroup based on the handed over value.*/
	myGroup->at(position) += value;
}
bool classPlayer::checkforFullGroup(int position, string fieldTypeValue) { /*Check for full group by getting the fieldtype of the field and comparing it with the handed over value.*/

	if (fieldTypeValue == "2group" && myGroup->at(position) == 2 || fieldTypeValue == "3group" && myGroup->at(position) == 3) {
		return true;
	}
	else { return false; }
}
void classPlayer::addMyField(int value) {			/*Pushes the handed over value to the vector myField.*/
	myField->push_back(value);
}
void classPlayer::setIsMyField(bool value) {		/*Switches isMyField between true and false, depending on the handed over value.*/
	isMyField = value;
}
void classPlayer::setIsInJail(bool value) {			/*Switches IsInJail between true and false, depending on the handed over value.*/
	IsInJail = value;
}

/*Calling Get-Methods*/

string classPlayer::getPlayerName() { return playerName; }
int classPlayer::getPlayerMoney() { return playerMoney; }
int classPlayer::getAmountOfMyFields() { return amountOfMyFields; }
int classPlayer::getCurrentPosition() { return currentPosition; }
void classPlayer::getMyGroupStrings() {
	cout << "\n";
	for (int x = 0; x < myGroupStrings->size(); x++) {
		cout << "\tGroup " << x << ": " << myGroupStrings->at(x) << "\n";
	}
}
void classPlayer::getMyField() {
	for (int x = 0; x < myField->size(); x++) {
		cout << myField->at(x) << " ";
	}
}
bool classPlayer::getIsMyField() { return isMyField; }
bool classPlayer::getIsInJail() { return IsInJail; }
bool classPlayer::getIsLendingMoney() { return isLendingMoney; }
};
