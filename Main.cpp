#include <iostream>
#include "Parameters.h"
#include <exception>
#include <iomanip>
#include <chrono>
#include <thread>
static std::string option;
static time_t start;
static Parameters parameters;
static bool sair = false;

void cashIn(Parameters& parameters)
{
	int cashIn;
	std::cout <<"\n"<< "How much cash do you wish to deposit?"<< "\n"<< std::endl;
	std::cin >> cashIn;
	float credits = cashIn/parameters.getDenomination();
	parameters.increaseCredits(credits);
	parameters.increaseTCashIn(cashIn);
	float balance = parameters.increaseBalanceInCash(cashIn);
	std::cout << "\n" << "You cashed in: " << cashIn << "$." <<" Considering your denomination of: "<< parameters.getDenomination()
		<< " it corresponds to: " << credits << " credits." << "\n"<<"\n" << "Total Balance: "<< balance <<"$."<<"\n" << std::endl;

}

void changeDenomination(Parameters& parameters)
{
	float denomination;
	std::cout << "\n"<<"What value do you want to set the denomination to ?"<<"\n" << std::endl;
	std::cin >> denomination;
	parameters.setDenomination(denomination);
	parameters.setCredits(parameters.getBalanceInCash()/parameters.getDenomination());
}

void cashOut(Parameters& parameters)
{
	int cashOut;
	std::cout << "\n"<<"How much cash do you wish to withraw?"<< "\n" << std::endl;
	std::cin >> cashOut;
	if (cashOut <= parameters.getBalanceInCash())
	{
		float credits = cashOut/parameters.getDenomination();
		parameters.decreaseCredits(credits);
		parameters.setTCashOut(cashOut);
		float balance = parameters.decreaseBalanceInCash(cashOut);
		std::cout << "\n" << "You withdrew: " << cashOut << "$." << " Considering your denomination of: " << parameters.getDenomination()
			<< " it corresponds to: " << credits << " credits." << "\n" << "\n" << "Total Balance: " << balance << "$."<<"\n" << std::endl;

	}
	else
	{
		std::cout << "\n"<<"You do not have enough credits" << "\n" << std::endl;
	}
}

void changeBet(Parameters& parameters)
{
	int bet;
	std::cout << "\n" <<"How much do you wish to bet?" <<"\n" << std::endl;
	std::cin >> bet;
	parameters.setBet(bet);
}

void play(Parameters& parameters)
{	
	start = time(NULL);
	if (parameters.getBet()*parameters.getDenomination()> (parameters.getBalanceInCash()))
	{
		std::cout <<"\n"<< "You do not have enough credits" << "\n"  << std::endl;
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
				std::cout << "\n" << "YOU WON "<< returnValue << " CREDITS!" << "\n" << std::endl;
				parameters.increaseTCoinOut(returnValue*parameters.getDenomination());
				parameters.increaseCredits(returnValue);
				parameters.insertCoinOut(returnValue*parameters.getDenomination());
			}
			else
			{
				std::cout <<"\n" <<"YOU WON " << returnValue << " POINTS!" << "\n" << std::endl;
				parameters.increasePoints(returnValue);
				parameters.insertCoinOut(0);
			}

		}
		else //lose
		{
			std::cout <<"\n"<< "You lost "<< parameters.getBet()*0.9 << " credits" << "\n" << std::endl;
			parameters.insertCoinOut(0);

		}
	}
	
}

void gamble(Parameters& parameters)
{
	if (parameters.getBet() > (parameters.getPoints()))
	{
		std::cout << "\n"<<"You do not have enough points" << "\n" << std::endl;
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
				std::cout << "\n"<<"YOU WON " << returnValue << " POINTS!" << "\n" << std::endl;
				parameters.increasePoints(returnValue);
				parameters.insertCoinOut(0);
			}
			else
			{
				std::cout << "\n"<<"YOU WON " << returnValue << " POINTS!" << "\n" << std::endl;

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
	std::cout <<"\n"<< "Choose one of the following options:"<<"\n" << std::endl << "1 - Cash In" << std::endl << "2 - Cash Out"
		<< std::endl << "3 - Change Bet" << std::endl << "4 - Change Denomination" << std::endl
		<< "5 - Play (Credits)" << std::endl << "6 - Gamble (Points)" << std::endl << "7 - Exit" << "\n" << std::endl;
}

void wait()
{
	time_t waitTime = 5;
	while (!sair)

	{	
		if ((time(NULL) - start > waitTime) && option.empty())
		{
			if (parameters.getBet() * parameters.getDenomination() <= (parameters.getBalanceInCash()))
			{
				play(parameters);
				parameters.displayValues();
				displayOptions();
			}
			else
			{
				if (parameters.getBet() <= parameters.getPoints())
				{
					gamble(parameters);
					parameters.displayValues();
					displayOptions();
				}
			}
			
		}
		std::this_thread::sleep_for(std::chrono::milliseconds(50));
	}
	
	
}

void display()
{
	
	while (!sair)
	{
			parameters.displayValues();
			std::cout << std::endl;
			displayOptions();
			option = "";
			
			std::cin >> option;

			if (option.length() > 1)
			{
				std::cout << "\n" << "Please type in a number from 1 to 7 and press ENTER" << "\n" << std::endl;

			}
			else
			{
				int optionInt = std::atoi(option.c_str());

				switch (optionInt)
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
					std::cout << "\n" << "Thank you for playing with us :)" << "\n" << std::endl;
					sair = true;
					break;
				}
				default:
					std::cout << "\n" << "Please type in a number from 1 to 7 and press ENTER" << "\n" << std::endl;
					break;

				}


			}
			
			std::this_thread::sleep_for(std::chrono::milliseconds(50));
			start = time(NULL);
			option = "";

	}
	
}

int main()
{
	start = time(NULL);
	std::thread diisplay(display);
	std::thread waiting(wait);
	diisplay.join();
	waiting.join();
	return 0;
}
