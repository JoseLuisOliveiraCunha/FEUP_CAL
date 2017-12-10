/*
 * Menu.cpp
 *
 *  Created on: 03/04/2017
 *      Author: PC
 */

#include "Menu.h"
#include <cstdlib>

Menu::Menu(SupermarketManager s)
{
	this->s = s;
	this->mainMenu();
}

void Menu::mainMenu()
{
	bool flag = true;
	while (flag)
	{
		int operation;
		cout << endl;
		cout << "MAIN MENU\n";
		cout << "Select the desired operation:\n";
		cout << "1. MAKE graph \n";
		cout << "2. LOAD graph \n";
		cout << "3. Make deliver REQUEST \n";
		cout << "4. Make deliver REQUESTS for ALL CLIENTS\n";
		cout << "5. DELIVER all requests \n";
		cout << "6. SEARCH \n";
		cout << "7. Exit\n";
		cout << "Operation selected: ";
		operation = readNumber(1, 7);
		switch (operation)
		{
		case 1:
			s.makeGraph();
			break;
		case 2:
			s.loadGraph();
			break;
		case 3:
			s.makeRequest();
			break;
		case 4:
			s.makeRandomRequests();
			break;
		case 5:
			deliverMenu();
				break;
		case 6:
			searchMenu();
			break;
		case 7:
			flag = false;
			break;
		}
	}
	exit(0);
}

void Menu::deliverMenu()
{
	int operation;
	cout << endl;
	cout << "DELIVER MENU\n";
	cout << "Select the desired operation:\n";
	cout << "1. Prioritize SIZE \n";
	cout << "2. Prioritize DISTANCE \n";
	cout << "3. Return to Main Menu \n";
	cout << "Operation selected: ";
	operation = readNumber(1, 3);
	switch (operation)
	{
	case 1:
		s.deliverAllRequests(0);
		break;
	case 2:
		s.deliverAllRequests(1);
		break;
	case 3:
		return;
		break;
	}
}

void Menu::searchMenu()
{
	int operation;
	cout << endl;
	cout << "SEARCH MENU\n";
	cout << "Select the desired operation:\n";
	cout << "1. EXACT search STREET \n";
	cout << "2. EXACT search SUPERMARKET \n";
	cout << "3. APPROXIMATE search STREET \n";
	cout << "4. APPROXIMATE search SUPERMARKET \n";
	cout << "5. EXACT search DISTRICT \n";
	cout << "6. Return to Main Menu \n";
	cout << "Operation selected: ";
	operation = readNumber(1, 6);
	switch (operation)
	{
	case 1:
		s.exactSearchStreet();
		break;
	case 2:
        s.exactSearchSupermarket();
		break;
	case 3:
		s.approximateSearchStreet();
		break;
	case 4:
		s.approximateSearchSupermarket();
		break;
	case 5:
		s.exactSearchDistrict();
		break;
	case 6:
		return;
		break;
	}
}
