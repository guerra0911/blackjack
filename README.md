# Blackjack Simulator
## Overview
This project is a simulation of the popular casino card game, Blackjack. It’s purpose is to simulate players using different strategies, including my own card counting probability technique, and compare the player performance.

## Features
- Simulates a game of Blackjack with up to 5 players and a dealer.
- Tracks each player's balance and bet amount.
- Uses a shoe of 8 decks, with an option to reinitialize and shuffle the shoe when the number of cards left falls below a certain point.
- Supports various player strategies including `HARD_17`, `SOFT_17`, `OPTIMAL_CHART`, `CARD_COUNTING`.
- Allows players to make decisions such as 
    `H = HIT`
    `S = STAND`
    `P = SPLIT`
    `DS = DOUBLE IF ALLOWED, OTHERWISE STAND`
    `DH = DOUBLE IF ALLOWED, OTHERWISE HIT`
    `RH = SURRENDER IF ALLOWED OTHERWISE HIT`

## Classes
- `Card`: Represents a playing card.
- `Hand`: Represents a hand of cards held by a player or the dealer.
- `Shoe`: Represents a shoe of cards to be dealt.
- `Player`: Represents a player in the game, with methods for making decisions based on a strategy.
- `Dealer`: Represents the dealer in the game.
- `Table`: Represents the blackjack table, with methods for playing rounds, handling bets, and managing players.
## UML Diagram
![UML Class Diagram](Pics/Blackjack_UML_Diagram.png)

## Strategies
- `HARD_17`: Player stands on a hand value of 17+, otherwise the player hits.
- `SOFT_17`: Player stands on a hand value of 17+. However, if their hand has a value of 17 with an Ace in it, they hit. For all hand values less than 17, the player hits.
- `OPTIMAL_CHART`: Renowned Chart derived by mathematicians, often provided by casino’s themselves that maps any combination of player cards and/or hand value, with the dealer’s visible card, to an Optimal Decision. 
![Optimal Chart](Pics/Optimal_Chart.png)

- `CARD_COUNTING`: Player keeps track of all the possible cards left in the shoe, and decides on whether to Hit, Stand, Double or Surrender, based on the probability of their next dealt card causing them to bust.
![Simulation](Pics/CardCount_Explanation.png)
![Probability](Pics/Probability_Equation.png)

Now, what does a player do with this probability? They will use it, along with a threshold to make a final decision on what action to do next. 
In simpler terms, if a player thinks their probability to bust in their next dealt card is too high, then they will `STAND`. Vice versa, if a player thinks their probability to bust in their next dealt card is low enough, then they will `HIT`.

### How do we find these Thresholds? 
One simulation consists of a Player playing through 250,000 games, using a constant arbitrary threshold to make their decision. This simulation is then repeated for numerous different threshold amounts (0.01 - 0.99 with 0.01 Increments). 
For each different hand value a player can have, (2,3,4, … ,18,19,20,21), there is a different threshold for a player to decide with.
I.e. A player with a hand value of 12 has a lower probability to bust than a player with a hand value of 19, thus they need a different threshold to evaluate at each variation of hand value.

All simulations for each threshold and each possible hand value is independently run and analyzed to ensure no cross-influence between two thresholds.

After completion of all simulations, 250,000 games for each threshold, the average balance of a player at each turn, over their 250,000 games is examined, and the threshold that allowed the greatest earnings, over time was chosen as the optimal threshold.

## Analysis


## Future Improvements
- Add more Player Strategies.
- Implement a Graphical User Interface with Custom User Input.