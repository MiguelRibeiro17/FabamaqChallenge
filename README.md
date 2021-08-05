# FabamaqChallenge
Fabamaq Challenge
Options:
1:CashIn: allows the player to cash in money onto the game. The user specifies the amount he wishes in $ and it charges the account with the corresponding credits.
2:CashOut: aloows the player to withraw money from the game.The user specifies the amount he wishes in $ and it decreases the corresponding credits.
3:ChangeBet: allows the player to change the bet ammount (in credits). This amount is used for both game modes (play and gamble).
4:ChangeDenomination: Allows the player to change the denomination (AmountInCash = Denomination * AmountInCredits).
5:Play: The player bets the bet specified in credits. 10% goes to the house. 50% chance of winning, if the player wins 80% chance of winning credits and 20% of winning points.
6:Gamble: The player bets the bet specified in points. 10% goes to the house. 50% chance of winning, if the player wins 80% chance of winning points and 20% of winning credits.

The values of the following variables are written to "Parameters.txt" in this order:
credits
denomination
points
TCashIn
TCashOut
TCoinIn
TCoinOut
TPlays1
TPlays2
RTP
Bet
BalanceInCash
CoinIn[]
CoinOut[]
