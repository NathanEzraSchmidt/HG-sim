# HG-sim

# About

The program simulates banking blackjack at HG with the goal of finding the optimal amount to cover. 

The HG blackjack rules are:
  blackjack pays 6:5, 
  dealer hits soft 17, 
  player can double down on any two cards including after splitting, 
  player can surrender anytime before doubling down or busting if the dealer doesn't have blackjack, 
  if the dealer busts with a three card 16 and the player busts, it's a tie, 
  player can split up to three times for a total of four hands,
  player can resplit aces,
  player cannot draw to split aces,
  a player hand consisting of an ace and a ten valued card gotten after splitting aces automatically wins
  
The sim executes basic strategy decisions for the players. This can be modified by changing the return values in the function `get_basic_strat`.

# Use
The program will ask the user for a few values for running the sim. See the screenshot examples for this. You should enter only integers and the players' bet sizes should be even numbers. If you don't enter integers, there will be undefined behavior.
In print mode (screenshot 2), it prints info about each hand one at a time, showing the starting deck cards, the completed hands, and wins and losses. This is mainly for error checking. Two things to note: 1) It deals and plays out each hand one at a time with consecutive cards from the deck, starting with the dealer then doing each player in ascending order. This is different than casino play but theoretically doesn't matter and was easier to program. 2) Double down hands are printing to the screen twice.
To run the sim normally, enter 0 for print mode (screenshot 1). 
# Compilation
gcc -Wall -std=c99 -O3 -o hg main.c hg.c

  
  
  
  
  
