//
//  ridethebus.cpp
//  ridethebus
//
//  Created by Manan Manchanda on 10/8/21.
//

#include "ridethebus.hpp"
#include <random>
#include <iostream>
#include <string>
#include <getopt.h>

using namespace std;

constexpr const char* const Card::RANK_TWO;
constexpr const char* const Card::RANK_THREE;
constexpr const char* const Card::RANK_FOUR;
constexpr const char* const Card::RANK_FIVE;
constexpr const char* const Card::RANK_SIX;
constexpr const char* const Card::RANK_SEVEN;
constexpr const char* const Card::RANK_EIGHT;
constexpr const char* const Card::RANK_NINE;
constexpr const char* const Card::RANK_TEN;
constexpr const char* const Card::RANK_JACK;
constexpr const char* const Card::RANK_QUEEN;
constexpr const char* const Card::RANK_KING;
constexpr const char* const Card::RANK_ACE;

constexpr const char* const Card::SUIT_SPADES;
constexpr const char* const Card::SUIT_HEARTS;
constexpr const char* const Card::SUIT_CLUBS;
constexpr const char* const Card::SUIT_DIAMONDS;

Card::Card()
: rank(RANK_TWO), suit(SUIT_SPADES) {}

Card::Card(const std::string &rank_in, const std::string &suit_in)
: rank(rank_in), suit(suit_in) {}

string Card::getRank() {
    return rank;
}

string Card::getSuit() {
    return suit;
}

ostream& operator<<(ostream& os, const Card& card) {
    os << card.rank << " of " << card.suit << "\n";
    return os;
}

Deck::Deck() {
    cards.resize(52);
    size_t packIndex = 0;
    for (int suitIndex = 0; suitIndex <= 3; ++suitIndex) {
        for (size_t rankIndex = 0; rankIndex <= 12; ++rankIndex) {
            cards[packIndex] = Card(CARD_VALUE_ARRAY[rankIndex], CARD_SUIT_ARRAY[suitIndex]);
            ++packIndex;
        }
    }
}

void Deck::shuffle() {
    for (size_t i = 0; i < cards.size(); i++) {
        std::random_device rd;
        std::mt19937 eng(rd());
        std::uniform_int_distribution<int> distr(0, static_cast<int>(i));
        
        size_t randomSwap = static_cast<size_t>(distr(eng));
        Card temp = cards[randomSwap];
        cards[randomSwap] = cards[i];
        cards[i] = temp;
    }
}

Card Deck::dealOne() {
    if (cardsDealt == 52) {
        cout << "Reshuffling... Take a drink and I will deal.";
        shuffle();
        cardsDealt = 0;
    }
    Card deal = cards[cardsDealt];
    cardsDealt++;
    return deal;
}

RideBus::RideBus() {
    gameDeck.shuffle();
}

Card RideBus::dealCard() {
    return gameDeck.dealOne();
}

int Card::getRankNumber() {
    if (rank == Card::RANK_ACE)
        return 14;
    else if (rank == Card::RANK_KING)
        return 13;
    else if (rank == Card::RANK_QUEEN)
        return 12;
    else if (rank == Card::RANK_JACK)
        return 11;
    else if (rank == Card::RANK_TEN)
        return 10;
    else if (rank == Card::RANK_NINE)
        return 9;
    else if (rank == Card::RANK_EIGHT)
        return 8;
    else if (rank == Card::RANK_SEVEN)
        return 7;
    else if (rank == Card::RANK_SIX)
        return 6;
    else if (rank == Card::RANK_FIVE)
        return 5;
    else if (rank == Card::RANK_FOUR)
        return 4;
    else if (rank == Card::RANK_THREE)
        return 3;
    else if (rank == Card::RANK_TWO)
        return 2;
    else return 1;
}

void RideBus::processCommandLine(int argc, char **argv) {
    opterr = true;
    int choice = 0;
    int option_index = 0;
    option long_options[] = {
        { "help",    no_argument,       nullptr, 'h' },
        { "figlet",  no_argument,       nullptr, 'f' },
        { "extreme", no_argument,       nullptr, 'e' },
        { nullptr,   0,                 nullptr, '\0' }
    };
    
    while ((choice = getopt_long(argc, argv, "hfe",
                                 long_options, &option_index)) != -1) {
        switch (choice) {
            case 'h':
                cout << "We are going to get drunk playing Ride the Bus. \n";
                cout << "----------------------------------------------- \n";
                cout << "Usage: \n";
                cout << "-h, --help:    This message will display.\n";
                cout << "-f, --figlet:  All card values will appear in larger";
                cout << " text.\n";
                cout << "-e, --extreme: Extreme mode. Every time you get a";
                cout << " card wrong, you drink for the amount of seconds";
                cout << " that is equal to the # of times you have been wrong.\n";
                exit(0);
                break;
            case 'f':
                figlet = true;
            case 'e':
                extreme = true;
        }
    }
}

void RideBus::play() {
    Card first = Card();
    Card second = Card();
    Card third = Card();
    Card suit = Card();
    int step = 1;
    bool finished = false;
    while (!finished) {
        if (step == 1) {
            cout << "Red or Black? \nOPTIONS:\n1 - Red\n2 - Black\n>> ";
            int entry;
            cin >> entry;
            cout << "Dealing card: \n";
            first = dealCard();
            if (!figlet)
                cout << first << "\n";
            else {
                cout << bigText(first.getRank()) << "\n" << bigText("of") << "\n" << bigText(first.getSuit()) << "\n\n";
            }
            if (first.getSuit() == Card::SUIT_HEARTS || first.getSuit() == Card::SUIT_DIAMONDS) {
                if (entry == 1) {
                    cout << "CORRECT!\n\n";
                    step++;
                    continue;
                }
            }
            else {
                if (entry == 2) {
                    cout << "CORRECT!\n\n";
                    step++;
                    continue;
                }
            }
        }
        else if (step == 2) {
            cout << "Next: Higher or Lower? \nOPTIONS:\n1 - Higher\n2 - Lower\n>> ";
            int entry;
            cin >> entry;
            cout << "Dealing card: \n";
            second = dealCard();
            if (!figlet)
                cout << second << "\n";
            else {
                cout << bigText(second.getRank()) << "\n" << bigText("of") << "\n" << bigText(second.getSuit()) << "\n\n";
            }
            if (second.getRankNumber() == 14 || first.getRankNumber() == 14) {
                cout << "CORRECT!\n\n";
                step++;
                continue;
            }
            else if (entry == 1) {
                if (second.getRankNumber() >= first.getRankNumber()) {
                    cout << "CORRECT!\n\n";
                    step++;
                    continue;
                }
            }
            else {
                if (second.getRankNumber() <= first.getRankNumber()) {
                    cout << "CORRECT!\n\n";
                    step++;
                    continue;
                }
            }
        }
        else if (step == 3) {
            cout << "Next: In Between or Outside? \nOPTIONS:\n1 - In Between\n2 - Outside\n>> ";
            int entry;
            cin >> entry;
            cout << "Dealing card: \n";
            third = dealCard();
            if (!figlet)
                cout << third << "\n";
            else {
                cout << bigText(third.getRank()) << "\n" << bigText("of") << "\n" << bigText(third.getSuit()) << "\n\n";
            }
            if (second.getRankNumber() == 14 || first.getRankNumber() == 14) {
                cout << "CORRECT!\n\n";
                step++;
                continue;
            }
            else if (entry == 1) {
                if ((first.getRankNumber() <= third.getRankNumber() && third.getRankNumber() <= second.getRankNumber()) ||
                    (second.getRankNumber() <= third.getRankNumber() && third.getRankNumber() <= first.getRankNumber())) {
                    cout << "CORRECT!\n\n";
                    step++;
                    continue;
                }
            }
            else {
                if ((first.getRankNumber() <= third.getRankNumber() && second.getRankNumber() <= third.getRankNumber()) ||
                    (first.getRankNumber() >= third.getRankNumber() && second.getRankNumber() >= third.getRankNumber())) {
                    cout << "CORRECT!\n\n";
                    step++;
                    continue;
                }
            }
        }
        else {
            cout << "Finally: Suit? \nOPTIONS:\n1 - Spades\n2 - Hearts\n3 - Clubs\n4 - Diamonds\n>> ";
            int entry;
            cin >> entry;
            cout << "Dealing card: \n";
            suit = dealCard();
            if (!figlet)
                cout << suit << "\n";
            else {
                cout << bigText(suit.getRank()) << "\n" << bigText("of") << "\n" << bigText(suit.getSuit()) << "\n\n";
            }
            if ((suit.getSuit() == Card::SUIT_SPADES && entry == 1) ||
                (suit.getSuit() == Card::SUIT_HEARTS && entry == 2) ||
                (suit.getSuit() == Card::SUIT_CLUBS && entry == 3) ||
                (suit.getSuit() == Card::SUIT_DIAMONDS && entry == 4) ) {
                cout << "You win!!! You should have taken ";
                cout << drinksHad << (drinksHad == 1 ? " drink " : " drinks ") << "this game.\n";
                break;
            }
        }
        cout << "WRONG\nTAKE A DRINK!!!\n\n\n";
        step = 1;
        drinksHad++;
    }
}

string RideBus::bigText(const std::string rankOrSuit) {
    string value = "";
    if (rankOrSuit == Card::RANK_TWO) {
        value = " _____               \n|_   _|_      _____  \n  | | \\ \\ /\\ / / _ \\ \n  | |  \\ V  V / (_) |\n  |_|   \\_/\\_/ \\___/ ";
    }
    else if (rankOrSuit == Card::RANK_THREE) {
        value = " _____ _                   \n|_   _| |__  _ __ ___  ___ \n  | | | '_ \\| '__/ _ \\/ _ \\\n  | | | | | | | |  __/  __/\n  |_| |_| |_|_|  \\___|\\___|";
    }
    else if (rankOrSuit == Card::RANK_FOUR) {
        value = " _____                \n|  ___|__  _   _ _ __ \n| |_ / _ \\| | | | '__|\n|  _| (_) | |_| | |   \n|_|  \\___/ \\__,_|_|   ";
    }
    else if (rankOrSuit == Card::RANK_FIVE) {
        value = " _____ _           \n|  ___(_)_   _____ \n| |_  | \\ \\ / / _ \\\n|  _| | |\\ V /  __/\n|_|   |_| \\_/ \\___|";
    }
    else if (rankOrSuit == Card::RANK_SIX) {
        value = " ____  _      \n/ ___|(_)_  __\n\\___ \\| \\ \\/ /\n ___) | |>  < \n|____/|_/_/\\_\\";
    }
    else if (rankOrSuit == Card::RANK_SEVEN) {
        value = " ____                       \n/ ___|  _____   _____ _ __  \n\\___ \\ / _ \\ \\ / / _ \\ '_ \\ \n ___) |  __/\\ V /  __/ | | |\n|____/ \\___| \\_/ \\___|_| |_|";
    }
    else if (rankOrSuit == Card::RANK_EIGHT) {
        value = " _____ _       _     _   \n| ____(_) __ _| |__ | |_ \n|  _| | |/ _` | '_ \\| __|\n| |___| | (_| | | | | |_ \n|_____|_|\\__, |_| |_|\\__|\n         |___/           ";
    }
    else if (rankOrSuit == Card::RANK_NINE) {
        value = " _   _ _            \n| \\ | (_)_ __   ___ \n|  \\| | | '_ \\ / _ \\\n| |\\  | | | | |  __/\n|_| \\_|_|_| |_|\\___|";
    }
    else if (rankOrSuit == Card::RANK_TEN) {
        value = " _____          \n|_   _|__ _ __  \n  | |/ _ \\ '_ \\ \n  | |  __/ | | |\n  |_|\\___|_| |_|";
    }
    else if (rankOrSuit == Card::RANK_JACK) {
        value = "     _            _    \n    | | __ _  ___| | __\n _  | |/ _` |/ __| |/ /\n| |_| | (_| | (__|   < \n \\___/ \\__,_|\\___|_|\\_\\";
    }
    else if (rankOrSuit == Card::RANK_QUEEN) {
        value = "  ___                        \n / _ \\ _   _  ___  ___ _ __  \n| | | | | | |/ _ \\/ _ \\ '_ \\ \n| |_| | |_| |  __/  __/ | | |\n \\__\\_\\\\__,_|\\___|\\___|_| |_|";
    }
    else if (rankOrSuit == Card::RANK_KING) {
        value = " _  ___             \n| |/ (_)_ __   __ _ \n| ' /| | '_ \\ / _` |\n| . \\| | | | | (_| |\n|_|\\_\\_|_| |_|\\__, |\n              |___/ ";
    }
    else if (rankOrSuit == Card::RANK_ACE) {
        value = "    _            \n   / \\   ___ ___ \n  / _ \\ / __/ _ \\\n / ___ \\ (_|  __/\n/_/   \\_\\___\\___|";
    }
    else if (rankOrSuit == Card::SUIT_CLUBS) {
        value = "  ____ _       _         \n / ___| |_   _| |__  ___ \n| |   | | | | | '_ \\/ __|\n| |___| | |_| | |_) \\__ \\\n \\____|_|\\__,_|_.__/|___/";
    }
    else if (rankOrSuit == Card::SUIT_HEARTS) {
        value = " _   _                 _      \n| | | | ___  __ _ _ __| |_ ___ \n| |_| |/ _ \\/ _` | '__| __/ __|\n|  _  |  __/ (_| | |  | |_\\__ \\\n|_| |_|\\___|\\__,_|_|   \\__|___/";
    }
    else if (rankOrSuit == Card::SUIT_SPADES) {
        value = " ____                  _           \n/ ___| _ __   __ _  __| | ___  ___ \n\\___ \\| '_ \\ / _` |/ _` |/ _ \\/ __|\n ___) | |_) | (_| | (_| |  __/\\__ \\\n|____/| .__/ \\__,_|\\__,_|\\___||___/\n      |_|                          ";
    }
    else if (rankOrSuit == Card::SUIT_DIAMONDS) {
        value = " ____  _                                 _     \n|  _ \\(_) __ _ _ __ ___   ___  _ __   __| |___ \n| | | | |/ _` | '_ ` _ \\ / _ \\| '_ \\ / _` / __|\n| |_| | | (_| | | | | | | (_) | | | | (_| \\__ \\\n|____/|_|\\__,_|_| |_| |_|\\___/|_| |_|\\__,_|___/";
    }
    else {
        assert(rankOrSuit == "of");
        value = "        __ \n  ___  / _|\n / _ \\| |_ \n| (_) |  _|\n \\___/|_|  ";
    }
    return value;
}
