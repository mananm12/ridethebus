//
//  ridethebus.hpp
//  ridethebus
//
//  Created by Manan Manchanda on 10/8/21.
//

#ifndef ridethebus_hpp
#define ridethebus_hpp

#include <stdio.h>
#include <vector>
#include <string>
#include <unordered_map>

using namespace std;

class Card {
public:
    static constexpr const char* const RANK_TWO = "Two";
    static constexpr const char* const RANK_THREE = "Three";
    static constexpr const char* const RANK_FOUR = "Four";
    static constexpr const char* const RANK_FIVE = "Five";
    static constexpr const char* const RANK_SIX = "Six";
    static constexpr const char* const RANK_SEVEN = "Seven";
    static constexpr const char* const RANK_EIGHT = "Eight";
    static constexpr const char* const RANK_NINE = "Nine";
    static constexpr const char* const RANK_TEN = "Ten";
    static constexpr const char* const RANK_JACK = "Jack";
    static constexpr const char* const RANK_QUEEN = "Queen";
    static constexpr const char* const RANK_KING = "King";
    static constexpr const char* const RANK_ACE = "Ace";

    static constexpr const char* const SUIT_SPADES = "Spades";
    static constexpr const char* const SUIT_HEARTS = "Hearts";
    static constexpr const char* const SUIT_CLUBS = "Clubs";
    static constexpr const char* const SUIT_DIAMONDS = "Diamonds";
    
    Card();
    Card(const std::string &rank_in, const std::string &suit_in);
    std::string getSuit();
    std::string getRank();
    int getRankNumber();
    friend ostream& operator<<(ostream& os, const Card& card);
private:
    std::string rank;
    std::string suit;
};

class Deck {
    friend class RideBus;
public:
    Deck();
    void shuffle();
    Card dealOne();
private:
    std::vector<Card> cards;
    int cardsDealt = 0;
};

class RideBus {
public:
    RideBus();
    Card dealCard();
    void processCommandLine(int argc, char **argv);
    void play();
private:
    bool figlet = false;
    bool extreme = false;
    Deck gameDeck;
    int drinksHad = 0;
    string bigText(const std::string rankOrSuit);
};

constexpr const char* const CARD_SUIT_ARRAY[] = {
  Card::SUIT_SPADES,
  Card::SUIT_HEARTS,
  Card::SUIT_CLUBS,
  Card::SUIT_DIAMONDS
};
const int NUM_SUITS = 4;

constexpr const char* const CARD_VALUE_ARRAY[] = {
  Card::RANK_TWO,
  Card::RANK_THREE,
  Card::RANK_FOUR,
  Card::RANK_FIVE,
  Card::RANK_SIX,
  Card::RANK_SEVEN,
  Card::RANK_EIGHT,
  Card::RANK_NINE,
  Card::RANK_TEN,
  Card::RANK_JACK,
  Card::RANK_QUEEN,
  Card::RANK_KING,
  Card::RANK_ACE
};
const int NUM_RANKS = 13;

#endif /* ridethebus_hpp */
