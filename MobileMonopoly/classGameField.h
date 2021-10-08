#pragma once
#pragma once
#include <iostream>
#include <vector>
#include <string>
#include <math.h>

using namespace std;

class classGameField {
private:
	string fieldName;							/*Used as the name of the field during the entire program.*/
	string belongsTo;							/*Tells to which player the field belongs.*/
	string fieldType;							/*Tells the type of the fields, whether it is a 2-Group field, 3-Group field or a port.*/
	int belongingNumber;						/*Represents the position of the vector of the players.*/
	int price;									/*Used as the current price of the field.*/
	int pricePerHouse;							/*Used as the price for a house of the field.*/
	int baseRent;								/*Used as the base rent of the field.*/
	int rent;									/*Used as the current rent of the field.*/
	int groupPosition;
	int amountOfHouses = 0;						/*Represents the amount of houses on the field.*/
	bool isAvailable = true;					/*Tells if the field is available to buy for a player.*/
	bool isPurchasable = true;
public:
	 classGameField(string fieldNameValue, int priceValue, bool availabilityValue) {			/*Constructor of classGameField.*/
	fieldName = fieldNameValue;																			/*Hands over the value for fieldName, price and isAvailable.*/
	price = priceValue;
	isAvailable = availabilityValue;
}

/*Calling Set-Methods*/

void classGameField::setBelongsTo(string value) {		/*Sets the value of belongsTo to the handed over value.*/
	belongsTo = value;
}
void classGameField::setBelongingNumber(int value) {	/*Sets the value of belongingNumber to the handed over value.*/
	belongingNumber = value;
}
void classGameField::setFieldStats(int buyingPriceValue, int pricePerHouseValue, int baseRentValue, int rentValue, int groupValue, string fieldTypeValue) {				/*Sets the values of price, pricePerHouse, rent and groupPosition to the handed over values.*/
	price = buyingPriceValue;
	pricePerHouse = pricePerHouseValue;
	baseRent = baseRentValue;
	rent = rentValue;
	groupPosition = groupValue;
	fieldType = fieldTypeValue;
}
void classGameField::increaseRent(int value, int factor) {			/*Multiplies the value of baseRent by the handed over value. This new value represents the new rent*/
	rent = value * factor;
}
void classGameField::setRent(int value) {				/*Sets the rent to the handed over value.*/
	rent = value;
}
void classGameField::increaseAmountOfHouses(int value) {
	amountOfHouses += value;
}
void classGameField::setIsAvailable(bool value) {		/*Sets the value of isAvailable to the handed over value.*/
	isAvailable = value;
}
void classGameField::setIsPurchasable(bool value) {		/*Sets the value of isPurchasable to the handed over value.*/
	isPurchasable = value;
}

/*Calling Get-Methods*/

string classGameField::getFieldName() { return fieldName; }
string classGameField::getBelongsTo() { return belongsTo; }
string classGameField::getFieldType() { return fieldType; }
int classGameField::getBelongingNumber() { return belongingNumber; }
int classGameField::getPrice() { return price; }
int classGameField::getPricePerHouse() { return pricePerHouse; }
int classGameField::getBaseRent() { return baseRent; }
int classGameField::getRent() { return rent; }
int classGameField::getGroupPosition() { return groupPosition; }
bool classGameField::getIsAvailable() { return isAvailable; }
int classGameField::getAmoutOfHouses() { return amountOfHouses; }
bool classGameField::getIsPurchasable() { return isPurchasable; }
};
