#include "Parameters.h"
#include <sstream>

void Parameters::updateValues()
{
	this->calculateRTP(this->coinIn, this->coinOut);
	std::ofstream FILE;
	FILE.open("Parameters.txt", std::ofstream::out | std::ofstream::trunc);
	FILE<< credits << std::endl 
		<< denomination << std::endl 
		<< points << std::endl 
		<< TCashIn << std::endl 
		<< TCashOut << std::endl 
		<< TCoinIn << std::endl 
		<< TCoinOut << std::endl 
		<< TPlays1 	<< std::endl 
		<< TPlays2 << std::endl 
		<< RTP << std::endl 
		<< Bet << std::endl 
		<< BalanceInCash << std::endl;
	this->writeCoinOnFile(this->coinIn, FILE);
	this->writeCoinOnFile(this->coinOut, FILE);
	FILE.close();

}

void Parameters::writeCoinOnFile(std::deque <float> g,std::ofstream &file)
{	
	std::deque<float>::iterator it;
	for (it = g.begin(); it != g.end(); ++it)
	{
		file << *it << ',';
	}
	file << std::endl;
}

Parameters::Parameters()
{
	this->credits = 0;
	this->denomination = 0.2;
	this->points = 0;
	this->TCashIn = 0;
	this->TCashOut = 0;
	this->TCoinIn = 0;
	this->TCoinOut = 0;
	this->TPlays1 = 0;
	this->TPlays2 = 0;
	this->RTP = 0;
	this->Bet = 10;
	this->BalanceInCash = 0;
	this->readFile();
}

void Parameters::readFile()
{
	std::string text, textAux;
	std::ifstream FILE("Parameters.txt");

	if (!FILE.is_open())
	{
		return;
	}

	int counter = 1;
	while (!FILE.eof())
	{
		std::getline(FILE, text);
		switch (counter)
		{
			case 1:
				this->credits = std::stof(text.c_str());
				break;

			case 2:
				this->denomination = std::stof(text.c_str());
				break;

			case 3:
				this->points = std::stof(text);
				break;

			case 4:
				this->TCashIn = std::stof(text);
				break;

			case 5:
				this->TCashOut = std::stof(text);
				break;

			case 6:
				this->TCoinIn = std::stof(text);
				break;

			case 7:
				this->TCoinOut = std::stof(text);
				break;

			case 8:
				this->TPlays1 = std::stoi(text);
				break;

			case 9:
				this->TPlays2 = std::stoi(text);
				break;

			case 10:
				this->RTP = std::stof(text);
				break;

			case 11:
				this->Bet = std::stoi(text);
				break;
		
			case 12:
				this->BalanceInCash = std::stof(text);
				break;
		
			case 13:
				{
					std::stringstream lineStream(text);

					while (std::getline(lineStream, textAux, ','))
					{
						this->coinIn.push_front(std::stof(textAux));
					}
					break;
				}
			case 14:
				{
					std::stringstream lineStream(text);

					while (std::getline(lineStream, textAux, ','))
					{
						this->coinOut.push_front(std::stof(textAux));
					}
					break;
				}
		}
		counter++;
	}

	FILE.close();
}

void Parameters::displayValues()
{
	std::cout << "Your Statistics:"<< "\n" << std::endl << "Credits : " << this->credits << " | " << "Denomination : " << this->denomination << " | " << "Points : " << this->points << " | " << "Bet Value : " << this->Bet << std::endl;
				
}

void Parameters::calculateRTP(std::deque <float> coinIn, std::deque <float> coinOut)
{	
	float totalCoinIn = 0;
	float totalCoinOut=0;
	std::deque<float>::iterator it;
	int counter = 0;
	for (it = coinIn.begin(); it != coinIn.end(); ++it)
	{	
		totalCoinIn += this->coinIn.at(counter);
		this->coinIn.at(counter);
		totalCoinOut += this->coinOut.at(counter);
		this->coinOut.at(counter);
		counter++;
	}
	if ((this->RTP = totalCoinOut / totalCoinIn * 100)<0)
	{
		this->RTP = 0;
	}
	else
	{
		this->RTP = totalCoinOut / totalCoinIn * 100;
	}
}

void Parameters::setCredits(float credits)
{
	if (credits >= 0)
	{
		this->credits = credits;
	}
	else this->credits = 0;
}

void Parameters::setDenomination(float denomination)
{	
	if (denomination >= 0)
	{
		this->denomination = denomination;
	}
	else this->denomination = 0;
}

void Parameters::setPoints(float points)
{
	this->points = points;
}

void Parameters::increaseTCashIn(int TCashIn)
{
	this->TCashIn += TCashIn;
}

void Parameters::setTCashOut(int TCashOut)
{
	this->TCashOut += TCashOut;
}

void Parameters::setTCoinIn(int TCoinIn)
{
	this->TCoinIn = TCoinIn;
}

void Parameters::setTCoinOut(int TCoinOut)
{
	this->TCoinOut = TCoinOut;
}

void Parameters::setTPlays1(int TPlays1)
{
	this->TPlays1 = TPlays1;
}

void Parameters::setTPlays2(int TPlays2)
{
	this->TPlays2 = TPlays2;
}

void Parameters::setRTP(int RTP)
{
	this->RTP = RTP;
}

void Parameters::setBet(int Bet)
{
	this->Bet = Bet;
}

float Parameters::increaseBalanceInCash(float BalanceInCash)
{
	this->setBetBalanceInCash(BalanceInCash + this->BalanceInCash);
	return this->BalanceInCash;
}

float Parameters::decreaseBalanceInCash(float BalanceInCash)
{
	this->setBetBalanceInCash(this->BalanceInCash - BalanceInCash);
	return this->BalanceInCash;
}

void Parameters::setBetBalanceInCash(int bet)
{
	this->BalanceInCash = bet;
}

void Parameters::increaseCredits(float credits)
{	
	this->setCredits(credits + this->credits);
}

void Parameters::decreaseCredits(float credits)
{
	this->setCredits(this->credits - credits);

}

void Parameters::insertCoinOut(float value)
{	
	if (this->coinOut.size() >= 40)
	{
		this->coinOut.pop_back();
		this->coinOut.push_front(value);
	}
	else
	{
		this->coinOut.push_front(value);
	}
}

void Parameters::insertCoinIn(float value)
{
	if (this->coinIn.size() >= 40)
	{
		this->coinIn.pop_back();
		this->coinIn.push_front(value);
	}
	else
	{
		this->coinIn.push_front(value);
	}
}

void Parameters::increasePoints(float points)
{
	this->setPoints(points + this->points);
}

void Parameters::increaseTCoinIn(float CoinIn)
{
	this->setTCoinIn(CoinIn + this->TCoinIn);
}

void Parameters::increaseTCoinOut(float CoinOut)
{
	this->setTCoinOut(CoinOut + this->TCoinOut);
}

void Parameters::increaseTPlays1(int value)
{
	this->setTPlays1(value + this->TPlays1);
}

void Parameters::increaseTPlays2(int value)
{
	this->setTPlays2(value + this->TPlays2);
}

float Parameters::getDenomination()
{
	return this->denomination;
}

int Parameters::getCredits()
{
	return this->credits;
}

float Parameters::getBalanceInCash()
{
	return this->BalanceInCash;
}

float Parameters::getBet()
{
	return this->Bet;
}

float Parameters::getPoints()
{
	return this->points;
}

void Parameters::decreasePoints(float points)
{
	this->setPoints(this->points - points);

}