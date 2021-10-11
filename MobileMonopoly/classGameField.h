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
	int belongingNumber;						/*Represents the position in the vector of the players.*/
	int price;									/*Used as the current price of the field.*/
	int pricePerHouse;							/*Used as the price for a house of the field.*/
	int baseRent;								/*Used as the base rent of the field.*/
	int rent;									/*Used as the current rent of the field.*/
	int groupPosition;							/*Represents the group number of the field.*/
	int amountOfHouses = 0;						/*Represents the amount of houses on the field.*/
	bool isAvailable = true;					/*Tells if the field is available to buy for a player.*/
	bool isPurchasable = true;					/*Tells whether the field is purchasable or not.*/
	bool rentWasDoubled = false;				/*Tells whether the rent of the field was doubled or not.*/
public:
	 classGameField(string fieldNameValue, int priceValue, bool availabilityValue) {			/*Constructor of classGameField.*/
	fieldName = fieldNameValue;																			/*Hands over the value for fieldName, price and isAvailable.*/
	price = priceValue;
	isAvailable = availabilityValue;
}

/*Calling Set-Methods*/

void setBelongsTo(string value) {		/*Sets the value of belongsTo to the handed over value.*/
	belongsTo = value;
}
void setBelongingNumber(int value) {	/*Sets the value of belongingNumber to the handed over value.*/
	belongingNumber = value;
}
void setFieldStats(int buyingPriceValue, int pricePerHouseValue, int baseRentValue, int rentValue, int groupValue, string fieldTypeValue) {				/*Sets the values of price, pricePerHouse, rent and groupPosition to the handed over values.*/
	price = buyingPriceValue;
	pricePerHouse = pricePerHouseValue;
	baseRent = baseRentValue;
	rent = rentValue;
	groupPosition = groupValue;
	fieldType = fieldTypeValue;
}
void increaseRent(int value, int factor) {			/*Multiplies the value of baseRent by the handed over value. This new value represents the new rent*/
	rent = value * factor;
}
void setRent(int value) {				/*Sets the rent to the handed over value.*/
	rent = value;
}
void increaseAmountOfHouses(int value) {
	amountOfHouses += value;
}
void lowerAmountOfHouses(int value) {
	amountOfHouses -= value;
}
void setIsAvailable(bool value) {		/*Sets the value of isAvailable to the handed over value.*/
	isAvailable = value;
}
void classGameField::setIsPurchasable(bool value) {		/*Sets the value of isPurchasable to the handed over value.*/
	isPurchasable = value;
}
void setRentWasDoubled(bool value) {	/*Sets the value of rentWasDoubled to the handed over value.*/
	rentWasDoubled = value;
}

/*Calling Get-Methods*/

string getFieldName() { return fieldName; }
string getBelongsTo() { return belongsTo; }
string getFieldType() { return fieldType; }
int getBelongingNumber() { return belongingNumber; }
int getPrice() { return price; }
int getPricePerHouse() { return pricePerHouse; }
int getBaseRent() { return baseRent; }
int getRent() { return rent; }
int getGroupPosition() { return groupPosition; }
bool getIsAvailable() { return isAvailable; }
int getAmoutOfHouses() { return amountOfHouses; }
bool getIsPurchasable() { return isPurchasable; }
bool getRentWasDoubled() { return rentWasDoubled; }
};
