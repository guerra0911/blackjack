# Blackjack Simulator
## Overview
This project is a simulation of the popular casino card game, Blackjack. It’s purpose is to simulate players using different strategies, including my own card counting probability technique, and compare the player performance.

## Features
- Simulates a game of Blackjack with up to 5 players and a dealer.
- Supports various player strategies including `HARD_17`, `SOFT_17`, `OPTIMAL_CHART`, ‘CARD_COUNTING’.
- Tracks each player's balance and bet amount.
- Allows players to make decisions such as `HIT`, `STAND`, `SPLIT`, `DOUBLE`, and `SURRENDER`.
- Uses a shoe of 8 decks, with an option to reinitialize and shuffle the shoe when the number of cards left falls below a certain point.

## Classes
- `Card`: Represents a playing card.
- `Hand`: Represents a hand of cards held by a player or the dealer.
- `Shoe`: Represents a shoe of cards to be dealt.
- `Player`: Represents a player in the game, with methods for making decisions based on a strategy.
- `Dealer`: Represents the dealer in the game.
- `Table`: Represents the blackjack table, with methods for playing rounds, handling bets, and managing players.
## UML Diagram

## Strategies
- ‘HARD_17’: Player stands on a hand value of 17+, otherwise the player hits.
- ‘SOFT_17’: Player stands on a hand value of 17+. However, if their hand has a value of 17 with an Ace in it, they hit. For all hand values less than 17, the player hits.
- ‘OPTIMAL_CHART’: Renowned Chart derived by mathematicians, often provided by casino’s themselves that maps any combination of player cards and/or hand value, with the dealer’s visible card, to an Optimal Decision. 

- ‘CARD_COUNTING’: Player keeps track of all the possible cards left in the shoe, and decides on whether to Hit, Stand, Double or Surrender, based on the probability of their next dealt card causing them to bust.
 

## Future Improvements
- Add more player strategies.
- Implement a graphical user interface.
- Add support for more complex betting strategies.

