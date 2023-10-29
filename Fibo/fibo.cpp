#include <iostream>
#include <ctime>
#include <cstdlib>
#include <iomanip>

// Card Class
class Card {
public:
    Card() = default;
    Card(char r, char s);

    void setCard(char r, char s);
    int getValue() const;
    void show() const;

private:
    char rank;
    char suit;
};

Card::Card(char r, char s) {
    rank = r;
    suit = s;
}

void Card::setCard(char r, char s) {
    rank = r;
    suit = s;
}

int Card::getValue() const {
    if (rank == 'A') {
        return 1;
    }
    else if (rank >= '2' && rank <= '9') {
        return rank - '0';
    }
    else {
        return 10;
    }
}

void Card::show() const {
    std::cout << rank << suit;
}

// Deck Class
class Deck {
public:
    Deck();

    void resetDeck();
    Card deal();
    void shuffle();
    bool isEmpty() const;
    void show() const;

private:
    Card cards[52];
    int top;
};

Deck::Deck() {
    resetDeck();
}

void Deck::resetDeck() {
    const char suits[] = { 'S', 'H', 'D', 'C' };
    const char ranks[] = { 'A', '2', '3', '4', '5', '6', '7', '8', '9', 'T', 'J', 'Q', 'K' };
    int k = 0;

    for (char suit : suits) {
        for (char rank : ranks) {
            cards[k].setCard(rank, suit);
            k++;
        }
    }

    top = 0;
}

Card Deck::deal() {
    if (isEmpty()) {
        throw std::runtime_error("Deck is empty");
    }

    Card card = cards[top];
    top++;
    return card;
}

void Deck::shuffle() {
    for (int i = 0; i < 52; i++) {
        int randomIndex = rand() % 52;
        std::swap(cards[i], cards[randomIndex]);
    }

    top = 0;
}

bool Deck::isEmpty() const {
    return top == 52;
}

void Deck::show() const {
    for (int i = 0; i < 52; i++) {
        cards[i].show();
        std::cout << (i % 13 == 12 ? '\n' : ' ');
    }
}

// Helper functions
bool isFibo(int num) {
    int a = 0;
    int b = 1;

    while (b <= num) {
        if (b == num) {
            return true;
        }

        int temp = b;
        b = a + b;
        a = temp;
    }

    return false;
}

int playFiboSolitaire(Deck& deck) {
    if (deck.isEmpty()) {
        std::cout << "\n--- Warning: Deck is empty !!! ---\n" << std::endl;
        return -1;
    }

    std::cout << "\nPlaying Fibonacci Solitaire !!!\n" << std::endl;
    int currentHandSize = 0;
    int currentHand[52];
    int pileSum = 0;
    int totalPiles = 0;
    int i = 0;


    while (i < 52) {
        if (deck.isEmpty()) {
            return -1;
        }
        Card drawnCard = deck.deal();
        pileSum += drawnCard.getValue();
        if (!isFibo(pileSum)) {
                drawnCard.show();
                std::cout << ", ";
                currentHand[currentHandSize] = drawnCard.getValue();
                currentHandSize++;
         }
         else {
                drawnCard.show();
                std::cout << " Fibo: " << pileSum << std::endl;
                currentHandSize = 0;
                pileSum = 0;
                totalPiles++;
        }
        i++;
    }

    if (pileSum != 0) {
        std::cout << "\nLast Pile Not Fibo: " << pileSum << std::endl;
        std::cout << "\nLoser in " << totalPiles << " piles!\n" << std::endl;
        return 0;
    }
    else {
        std::cout << "\n\nWinner in " << totalPiles << " piles!" << std::endl;
        return 1;
    }
}



int winFiboSolitaire(Deck& deck) {
    int gamesPlayed = 0;
    int result = 0;

    while (result != 1) {
        deck.resetDeck();
        deck.shuffle();
        result = playFiboSolitaire(deck);
        gamesPlayed++;
    }

    std::cout << "Winner in " << gamesPlayed << " games!" << std::endl;
    return gamesPlayed;
}


int main() {
    srand(time(0));

    Deck deck;
    int choice;

    std::cout << "Welcome to Fibonacci Solitaire!" << std::endl;

    do {
        std::cout << "1) Create New Deck" << std::endl;
        std::cout << "2) Shuffle Deck" << std::endl;
        std::cout << "3) Display Deck" << std::endl;
        std::cout << "4) Play Fibo Solitaire" << std::endl;
        std::cout << "5) Win Fibo Solitaire" << std::endl;
        std::cout << "6) Exit" << std::endl;
        std::cout << "Enter your choice: ";
        std::cin >> choice;

        switch (choice) {
        case 1:
            deck.resetDeck();
            std::cout << "New deck created!" << std::endl;
            break;
        case 2:
            deck.shuffle();
            std::cout << "Deck shuffled!" << std::endl;
            break;
        case 3:
            deck.show();
            break;
        case 4:
            playFiboSolitaire(deck);
            break;
        case 5:
            winFiboSolitaire(deck);
            break;
        case 6:
            std::cout << "Goodbye!" << std::endl;
            break;
        default:
            std::cout << "Invalid choice, please try again." << std::endl;
        }
    } while (choice != 6);

    return 0;
}
