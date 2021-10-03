#pragma once
#include <iostream>
#include <vector>
#include <string>
#include <math.h>

#include "classGameField.h"

using namespace std;

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
void setPrice(int buyingPriceValue, int pricePerHouseValue, int rentValue, int groupValue) {				/*Sets the values of price, pricePerHouse, rent and groupPosition to the handed over values.*/
	price = buyingPriceValue;
	pricePerHouse = pricePerHouseValue;
	rent = rentValue;
	groupPosition = groupValue;
}
void increaseRent(int value) {			/*Multiplies the value of rent by the handed over value.*/
	rent = rent * value;
}
void increaseAmountOfHouses(int value) {
	amountOfHouses += value;
}
void setIsAvailable(bool value) {		/*Sets the value of isAvailable to the handed over value.*/
	isAvailable = value;
}
void setIsPurchasable(bool value) {		/*Sets the value of isPurchasable to the handed over value.*/
	isPurchasable = value;
}

/*Calling Get-Methods*/

string getFieldName() { return fieldName; }
string getBelongsTo() { return belongsTo; }
int getBelongingNumber() { return belongingNumber; }
int getPrice() { return price; }
int getPricePerHouse() { return pricePerHouse; }
int getRent() { return rent; }
int getGroupPosition() { return groupPosition; }
bool getIsAvailable() { return isAvailable; }
int getAmoutOfHouses() { return amountOfHouses; }
bool getIsPurchasable() { return isPurchasable; }
