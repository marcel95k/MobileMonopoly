#pragma once
#include <iostream>
#include <vector>
#include <string>
#include <math.h>

#include "classGameField.h"
#include "classPlayer.h"

using namespace std;

class classTrade {
private:
	bool tradeAbort = false;		/*Used to determine whether the trade was aborted or not.*/
public:
	void trade(vector <classGameField>* classGameFieldVector, vector <classPlayer>* classPlayerVector, int* thisPlayer, int* selectedPlayer) {
	tradeBegin:
		setTradeAbort(false);
		/*Used as a function to trade belongings between players.*/
		string offered_field_player1;
		int choose;
		int accept;
		int field_player_1;
		int field_player_2;
		system("cls");
		cout << classPlayerVector->at(*thisPlayer).getPlayerName() << ", what do you offer?";	/*Player 1 section.*/
		cout << "\n\n[1] Offer Field";
		cout << "\n[2] Abort";
		cout << "\n\nOption: ";
		cin >> choose;
		if (choose == 1) {		
			system("cls");
			cout << "Which field do you offer?\n\n";
			for (int displayFields = 0; displayFields < classGameFieldVector->size(); displayFields++) {
				if (classPlayerVector->at(*thisPlayer).getPlayerName() == classGameFieldVector->at(displayFields).getBelongsTo()) {
					cout << "[" << displayFields << "] " << classGameFieldVector->at(displayFields).getFieldName() << "\n";
				}
			}
			cout << "\nOffer: ";
			cin >> field_player_1;
			if (field_player_1 > classGameFieldVector->size() || classGameFieldVector->at(field_player_1).getBelongsTo() != classPlayerVector->at(*thisPlayer).getPlayerName()) {
				cout << "\nField not found!\n";
				system("pause");
				goto tradeBegin;
			}
			else if(classGameFieldVector->at(field_player_1).getBelongsTo() == classPlayerVector->at(*thisPlayer).getPlayerName() || field_player_1 <= classGameFieldVector->size()){
				system("cls");
				cout << classPlayerVector->at(*selectedPlayer).getPlayerName() << ", what do you offer?";	/*Player 2 section.*/
				cout << "\n\n[1] Offer Field";
				cout << "\n[2] Abort";
				cout << "\n\nOption: ";
				cin >> choose;
				if (choose == 1) {		
					system("cls");
					cout << "Which field do you offer?\n\n";
					for (int displayFields = 0; displayFields < classGameFieldVector->size(); displayFields++) {
						if (classPlayerVector->at(*selectedPlayer).getPlayerName() == classGameFieldVector->at(displayFields).getBelongsTo()) {
							cout << "[" << displayFields << "] " << classGameFieldVector->at(displayFields).getFieldName() << "\n";
						}
					}
					cout << "\nOffer: ";
					cin >> field_player_2;
					if (field_player_2 > classGameFieldVector->size() || classGameFieldVector->at(field_player_2).getBelongsTo() != classPlayerVector->at(*selectedPlayer).getPlayerName()) {
						cout << "\nField not found!\n";
						system("pause");
						goto tradeBegin;
					}
					else if(classGameFieldVector->at(field_player_2).getBelongsTo() == classPlayerVector->at(*thisPlayer).getPlayerName() || field_player_2 <= classGameFieldVector->size()){
						system("cls");
						cout << "Trade " << classGameFieldVector->at(field_player_1).getFieldName() << " for " << classGameFieldVector->at(field_player_2).getFieldName() << "?";
						cout << "\n\n[1] Accept";
						cout << "\n[2] Decline";
						cout << "\n\nOption: ";
						cin >> accept;
						if(accept == 1){ 
							if (classGameFieldVector->at(field_player_1).getFieldType() != "Port") {	/*Execute this section if the FIRST traded field is NOT a port.*/
								classGameFieldVector->at(field_player_1).setBelongsTo(classPlayerVector->at(*selectedPlayer).getPlayerName());
								classGameFieldVector->at(field_player_1).setBelongingNumber(*selectedPlayer);
								classPlayerVector->at(*thisPlayer).removeFromMyGroupStrings(classGameFieldVector->at(field_player_1).getFieldName(), classGameFieldVector->at(field_player_1).getGroupPosition());
								classPlayerVector->at(*thisPlayer).removeFromMyGroup(1, classGameFieldVector->at(field_player_1).getGroupPosition());

								classPlayerVector->at(*selectedPlayer).addMyField(field_player_1);
								classPlayerVector->at(*selectedPlayer).addToMyGroupStrings(classGameFieldVector->at(field_player_1).getFieldName(), classGameFieldVector->at(field_player_1).getGroupPosition());
								classPlayerVector->at(*selectedPlayer).addToMyGroup(1, classGameFieldVector->at(field_player_1).getGroupPosition());
							}
							if (classGameFieldVector->at(field_player_2).getFieldType() != "Port") {	/*Execute this section if the SECOND traded field is NOT a port.*/
								classGameFieldVector->at(field_player_2).setBelongsTo(classPlayerVector->at(*thisPlayer).getPlayerName());
								classGameFieldVector->at(field_player_2).setBelongingNumber(*thisPlayer);
								classPlayerVector->at(*selectedPlayer).removeFromMyGroupStrings(classGameFieldVector->at(field_player_2).getFieldName(), classGameFieldVector->at(field_player_2).getGroupPosition());
								classPlayerVector->at(*selectedPlayer).removeFromMyGroup(1, classGameFieldVector->at(field_player_2).getGroupPosition());

								classPlayerVector->at(*thisPlayer).addMyField(field_player_2);
								classPlayerVector->at(*thisPlayer).addToMyGroupStrings(classGameFieldVector->at(field_player_2).getFieldName(), classGameFieldVector->at(field_player_2).getGroupPosition());
								classPlayerVector->at(*thisPlayer).addToMyGroup(1, classGameFieldVector->at(field_player_2).getGroupPosition());
							}

							if(classGameFieldVector->at(field_player_1).getFieldType() == "Port") {		/*Execute this section if the FIRST traded field IS a port.*/
								classGameFieldVector->at(field_player_1).setBelongsTo(classPlayerVector->at(*selectedPlayer).getPlayerName());
								classGameFieldVector->at(field_player_1).setBelongingNumber(*selectedPlayer);
								classPlayerVector->at(*thisPlayer).removeFromMyGroupStrings(classGameFieldVector->at(field_player_1).getFieldName(), classGameFieldVector->at(field_player_1).getGroupPosition());
								classPlayerVector->at(*thisPlayer).removeFromMyGroup(1, classGameFieldVector->at(field_player_1).getGroupPosition());

								classPlayerVector->at(*selectedPlayer).addMyField(field_player_1);
								classPlayerVector->at(*selectedPlayer).addToMyGroupStrings(classGameFieldVector->at(field_player_1).getFieldName(), classGameFieldVector->at(field_player_1).getGroupPosition());
								classPlayerVector->at(*selectedPlayer).addToMyGroup(1, classGameFieldVector->at(field_player_1).getGroupPosition());
								classPlayerVector->at(*thisPlayer).removeMyPort(1);
								classPlayerVector->at(*selectedPlayer).addMyPort(1);
							}

							if (classGameFieldVector->at(field_player_2).getFieldType() == "Port") {	/*Execute this section if the SECOND traded field IS a port.*/
								classGameFieldVector->at(field_player_2).setBelongsTo(classPlayerVector->at(*thisPlayer).getPlayerName());
								classGameFieldVector->at(field_player_2).setBelongingNumber(*thisPlayer);
								classPlayerVector->at(*selectedPlayer).removeFromMyGroupStrings(classGameFieldVector->at(field_player_2).getFieldName(), classGameFieldVector->at(field_player_2).getGroupPosition());
								classPlayerVector->at(*selectedPlayer).removeFromMyGroup(1, classGameFieldVector->at(field_player_2).getGroupPosition());

								classPlayerVector->at(*thisPlayer).addMyField(field_player_2);
								classPlayerVector->at(*thisPlayer).addToMyGroupStrings(classGameFieldVector->at(field_player_2).getFieldName(), classGameFieldVector->at(field_player_2).getGroupPosition());
								classPlayerVector->at(*thisPlayer).addToMyGroup(1, classGameFieldVector->at(field_player_2).getGroupPosition());
								classPlayerVector->at(*selectedPlayer).removeMyPort(1);
								classPlayerVector->at(*thisPlayer).addMyPort(1);
							}																	/*All playerstats and gamefield stats which are linked to each other*/
						}																		/*will be switched after the trading is completed.*/
						else {
							goto tradeBegin;
						}
					}
				}
				if (choose == 2) {	/*Trade aborted*/
					system("cls");
					cout << "Trade canceled!\n\n";
					system("pause");
					setTradeAbort(true);
				}
			}
		}
		if (choose == 2) {	/*Trade aborted*/
			system("cls");
			cout << "Trade canceled!\n\n";
			system("pause");
			setTradeAbort(true);
		}

	/*
	The player should be able to choose what object
	shall be traded (money, fields, houses).
	*/

	}
	void setTradeAbort(bool value) { tradeAbort = value; }	/*Switches tradeAbort between true and false, depending on the handed over value.*/
	bool getTradeAbort() { return tradeAbort; }
};
