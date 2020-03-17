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
I included three screenshots of using the program. After launching, the program will prompt you to enter a few values. In general, all entries should be integers (otherwise there will be undefined behavior) and the players' bet sizes should be even numbers. First, you have to enter whether or not to run it in "print mode". Print mode is for error checking and prints info about each hand, showing the starting deck cards, the completed hands, and wins and losses. Two things to note here: 1) It deals and plays out each hand one at a time with consecutive cards from the deck, starting with the dealer's, and then doing each player's in ascending order. This is different than casino play but theoretically doesn't matter and was easier to program. 2) Double down hands are printed to the screen twice, rather than there being a note about a doubled bet size. At the start of the sim, the program will generate a shuffled shoe of 8 decks, but in print mode you can customize the starting cards of the deck by entering "1" for the prompt "custom deck?". Screenshot 2 exemplifies this and also shows the player resplitting and doubling down twice. Screenshot 3 shows running a multi-hand sim in print mode without a custom deck, and screenshot 1 shows running the sim normally to get results.

# Compilation
gcc -Wall -std=c99 -O3 -o hg main.c hg.c

  
  
  
  
  
