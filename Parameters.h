#pragma once
#include <iostream>
#include <fstream>
#include <string>
#include <deque>

class Parameters
{
private:
	float denomination, BalanceInCash, credits, points,TCoinIn, TCoinOut ;
	int TCashIn, TCashOut, TPlays1, TPlays2, RTP, Bet;
	std::deque <float> coinIn, coinOut;
	
public:
	void writeCoinOnFile(std::deque <float> g, std::ofstream &file);
	void updateValues();
	void calculateRTP(std::deque <float> coinIn, std::deque <float> coinOut);
	Parameters();
	void readFile();
	
	void displayValues();
	//sets
	void setCredits(float credits);
	void setDenomination (float denomination);
	void setPoints(float points);
	void increaseTCashIn(int TCashIn);
	void setTCashOut(int TCashOut);
	void setTCoinIn(int TCoinIn);
	void setTCoinOut(int TCoinOut);
	void setTPlays1(int TPlays1);
	void setTPlays2(int TPlays2);
	void setRTP(int RTP);
	void setBet(int Bet);
	void setBetBalanceInCash(int bet);
	//increases
	void increaseTCoinIn(float CoinIn);
	void increaseTCoinOut(float CoinOut);
	float increaseBalanceInCash(float BalanceInCash);
	float decreaseBalanceInCash(float BalanceInCash);
	void increasePoints(float points);
	void increaseCredits(float credits);
	void decreaseCredits(float credits);
	void increaseTPlays1(int value);
	void increaseTPlays2(int value);
	void decreasePoints(float points);
	//inserts
	void insertCoinIn(float value);
	void insertCoinOut(float value);
	//gets
	float getDenomination();
	int   getCredits();
	float getBalanceInCash();
	float getBet();
	float getPoints();
	
};	


