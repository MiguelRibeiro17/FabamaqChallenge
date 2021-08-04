#include <iostream>
#include "Parameters.h"
#include <exception>
#include <iomanip>
void cashIn(Parameters& parameters)
{
	int cashIn;
	std::cout << "How much cash do you wish to deposit?" << std::endl;
	std::cin >> cashIn;
	float credits = cashIn/parameters.getDenomination();
	parameters.increaseCredits(credits);
	parameters.increaseTCashIn(cashIn);
	float balance = parameters.increaseBalanceInCash(cashIn);
	std::cout << "\n" << "You cashed in: " << cashIn << "$." <<" Considering your denomination of: "<< parameters.getDenomination()
		<< " it corresponds to: " << credits << " credits." << "\n" << "Total Balance: "<< balance <<"%." << std::endl;

}

void changeDenomination(Parameters& parameters)
{
	float denomination;
	std::cout << "What value do you want to set the denomination to ?" << std::endl;
	std::cin >> denomination;
	parameters.setDenomination(denomination);
	parameters.setCredits(parameters.getBalanceInCash()/parameters.getDenomination());
}

void cashOut(Parameters& parameters)
{
	int cashOut;
	std::cout << "How much cash do you wish to withraw?" << std::endl;
	std::cin >> cashOut;
	if (cashOut <= parameters.getBalanceInCash())
	{
		float credits = cashOut/parameters.getDenomination();
		parameters.decreaseCredits(credits);
		parameters.setTCashOut(cashOut);
		float balance = parameters.decreaseBalanceInCash(cashOut);
		std::cout << "\n" << "You withdrew: " << cashOut << "$." << " Considering your denomination of: " << parameters.getDenomination()
			<< " it corresponds to: " << credits << " credits." << "\n" << "Total Balance: " << balance << "%." << std::endl;

	}
	else
	{
		std::cout << "You do not have enough credits" << "\n" << std::endl;
	}
}

void changeBet(Parameters& parameters)
{
	int bet;
	std::cout << "How much do you wish to bet?" << std::endl;
	std::cin >> bet;
	parameters.setBet(bet);
}



void play(Parameters& parameters)
{
	if (parameters.getBet()*parameters.getDenomination()> (parameters.getBalanceInCash()))
	{
		std::cout << "You do not have enough credits" << "\n"  << std::endl;
	}
	else
	{
		float cash = parameters.getBet()*parameters.getDenomination();
		parameters.increaseTCoinIn(cash);
		parameters.increaseTPlays1(1);
		parameters.decreaseBalanceInCash(cash); //decrease rake(10%) + bet
		parameters.decreaseCredits(parameters.getBet());
		parameters.insertCoinIn(cash);
		int flip;
		flip = rand() % 2 ;
		if (flip ==1) 
		{
			float returnValue = parameters.getBet() * 1.8; 
			int flip2;
			flip2 = rand() % 5;
			if (flip2 !=4)
			{	
				std::cout << "YOU WON "<< returnValue << " CREDITS!" << "\n" << std::endl;
				parameters.increaseTCoinOut(returnValue*parameters.getDenomination());
				parameters.increaseCredits(returnValue);
				parameters.insertCoinOut(returnValue*parameters.getDenomination());
			}
			else
			{
				std::cout << "YOU WON " << returnValue << " POINTS!" << "\n" << std::endl;
				parameters.increasePoints(returnValue);
				parameters.insertCoinOut(0);
			}

		}
		else //lose
		{
			std::cout << "You lost "<< parameters.getBet()*0.9 << " credits" << "\n" << std::endl;
			parameters.insertCoinOut(0);

		}
	}
}

void gamble(Parameters& parameters)
{
	if (parameters.getBet() > (parameters.getPoints()))
	{
		std::cout << "You do not have enough points" << "\n" << std::endl;
	}
	else
	{
		parameters.increaseTPlays2(1);
		parameters.decreasePoints(parameters.getBet());
		parameters.insertCoinIn(0);

		int flip;
		flip = rand() % 2;
		if (flip == 1)
		{
			float returnValue = parameters.getBet() * 1.8;
			int flip2;
			flip2 = rand() % 5;
			if (flip2 != 4)
			{
				std::cout << "YOU WON " << returnValue << " POINTS!" << "\n" << std::endl;
				parameters.increasePoints(returnValue);
				parameters.insertCoinOut(0);
			}
			else
			{
				std::cout << "YOU WON " << returnValue << " POINTS!" << "\n" << std::endl;

				parameters.increaseTCoinOut(returnValue * parameters.getDenomination());
				parameters.increaseCredits(returnValue);
				parameters.insertCoinOut(returnValue * parameters.getDenomination());
			}

		}
		else 
		{
			std::cout << "You lost " << parameters.getBet() * 0.9 << " points" << "\n" << std::endl;
			parameters.insertCoinOut(0);

		}
	}
}



void displayOptions()
{
	std::cout << "Choose one of the following options:" << std::endl << "1 - Cash In" << std::endl << "2 - Cash Out"
		<< std::endl << "3 - Change Bet" << std::endl << "4 - Change Denomination" << std::endl
		<< "5 - Play (Credits)" << std::endl << "6 - Gamble (Points)" << std::endl << "7 - Exit" << "\n" << std::endl;
}
void display()
{
	Parameters parameters;
	std::string option;

	while (option != "7")
	{
		try
		{
			parameters.displayValues();
			std::cout << std::endl;
			displayOptions();
			std::cin >> option;
			if (option.length() > 1)
			{
				std::cout << "Please type in a number from 1 to 7 and press ENTER" << "\n" << std::endl;

			}
			else
			{
				int option2 = std::atoi(option.c_str());

				switch (option2)
				{
				case 1: cashIn(parameters);

					break;

				case 2: cashOut(parameters);
					break;

				case 3: changeBet(parameters);
					break;

				case 4:changeDenomination(parameters);
					break;

				case 5: play(parameters);
					break;

				case 6: gamble(parameters);
					break;

				case 7:
				{
					parameters.updateValues();
					std::cout << std::endl;
					std::cout << "Thank you for playing with us :)" << "\n" << std::endl;
					break;
				}
				default:
					std::cout << "Please type in a number from 1 to 7 and press ENTER" << "\n" << std::endl;

					break;

				}
			}
		}
		catch (std::exception& e)
		{
			std::cout << "exception thrown" << e.what() << std::endl;

		}
	}
}


int main()
{
	display();
	return 0;

}

