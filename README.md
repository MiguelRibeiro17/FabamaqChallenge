# FabamaqChallenge
## Fabamaq Challenge
### Options:
1. CashIn: allows the player to cash in money onto the game. The user specifies the amount he wishes in $ and it charges the account with the corresponding credits.
1. CashOut: aloows the player to withraw money from the game.The user specifies the amount he wishes in $ and it decreases the corresponding credits.
1. ChangeBet: allows the player to change the bet ammount (in credits). This amount is used for both game modes (play and gamble).
1. ChangeDenomination: Allows the player to change the denomination (AmountInCash = Denomination * AmountInCredits).
1. Play: The player bets the bet specified in credits. 10% goes to the house. 50% chance of winning, if the player wins 80% chance of winning credits and 20% of winning points.
1. Gamble: The player bets the bet specified in points. 10% goes to the house. 50% chance of winning, if the player wins 80% chance of winning points and 20% of winning credits.

### The values of the following variables are written to "Parameters.txt" in this order:

| Variable      | Meaning                                                |
| ------------- | ------------------------------------------------------ |
| credits       | The representation of cash in the game.                |
| denominationR | Relation between cash and credits.                     |
| points        | Like credits but without direct relation to cash.      |
| TCashIn       | Total cash inserted onto the game.                     |
| TCashOut      | Total cash withdrawn from the game.                    |
| TCoinIn       | Total cash gambled by the player.                      |
| TCoinOut      | Total awards collected from the player.                |
| TPlays1       | Number of plays of type Play.                          |
| TPlays2       | Number of plays of type Gamble.                        |
| RTP           | Return to player (CoinOut/CoinIn)-                     |
| Bet           | The amount of credits used to play in both game modes. |
| BalanceInCash | The amount of cash the player has in $.                |
| CoinIn[]      | Up to 40 values of the latest plays to calculate RTP.  |
| CoinOut[]     | Up to 40 values of the latest plays to calculate RTP.  |
