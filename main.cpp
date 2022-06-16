//Class code: June 16, 2022.
//we're making a game of roullette 

#include <iostream>
#include <vector>
#include <unistd.h>
#include <string>
#include <sstream>

using namespace std;

class Node {
private:
    int num;
    Node *next;
    
    
public:
    int get_num() const {
        return num;
    }
    Node *get_next() const {
        return next;
    }
    bool set_num(int n) { // Guarded setter will refuse to set negative values.
        if (n < 0)
            return false;
        num = n;
        return true;
    }
    void set_next(Node *p) {
        next = p;
    }
    
};

// Make a ring from p NUM_SLOTS nodes long
void make_a_ring(Node *p, size_t num_slots) {
    
    // Fill up the NUM_SLOTS with numbers and link them up in a circle.
    Node *q = p, *last = p;
    for (size_t i = 0; i < num_slots; i++) {
        // We dont check the return value of the following set because
        // we know that the parameter is guarenteed to be non-negative
        q->set_num(rand() % num_slots);
        q->set_next(new Node);
        last = q;
        //cout << "q = " << q << ", its number = " << q->get_num() << endl;
        q = q->get_next();
    }
    
    // Now p is the first node of a chain that has 99 other nodes.
    
    // That means we can get a ring by making q->next point to p.
    q->set_next(p);
    
    // We write a loop to print out all of the numbers in the ring.
    // Challenge: You cannot use NUM_SLOTS or 100 anymore.
    // No new numeric comparisons allowed.
    
    /* cout << "Part 2" << endl << endl;
    
    for(Node *r = p; r != last; r = r->get_next())
        cout << "r = " << r << ", its number = " << r->get_num() << endl;
    cout << "last = " << last << ", its number = " << last->get_num() << endl;
    
    
    q = p;
    There is a corner case one-off bug here: extra credit if you find it and post it
    (prints an extra zero)
    do {
        cout << "q = " << q << ", its number = " << q->get_num() << endl;
        q = q->get_next();
    } while (q != p); */
}

class Player {
public:
    string player_name;
    int player_slot;
    int player_bet; //bet is in whole dollars
    
    void set_data(string name, int slot, int bet) {
        player_name = name;
        player_slot = slot;
        player_bet = bet;
    }

    string get_name(){
        return player_name;
    }

    int get_slot(){
        return player_slot;
    }

    int get_bet(){
        return player_bet;
    }
    
};

// We will simulate a Roullette Casino Game
int main(int argc, const char * argv[]) {
    srand((unsigned) time(nullptr));
    
    const size_t NUM_SLOTS = 20;
    Node *p = new Node;
    int num_players = 0;
    string user_input;

    make_a_ring(p, NUM_SLOTS);
    
    //Prompt the user and get the number of players
    cout << "Enter the number of players: ";
    getline(cin, user_input);
    //Convert user input into num_players (two lines of code)
    stringstream number;
    number << user_input;
    number >> num_players;
    
    //TODO: Iterate over all of the players and get their names,
    //lucky number 0-100, and amount bet on that number
    //Store the names, numbers, and amounts in a vector of Player objects
    vector<Player> players(num_players);
    
    string player_name, lucky_number, bet_amount;
    int slot, bet;
    
    for(int i = 0; i < num_players; i++) {
        cout << "Enter player name: ";
        getline(cin, player_name);
        
        cout << "Enter player's lucky number: ";
        getline(cin, user_input);
        stringstream(user_input) >> slot;
        
        cout << "Enter the amount the player is betting: ";
        getline(cin, user_input);
        stringstream(user_input) >> bet;
        
        players[i].set_data(player_name, slot, bet);
    }
    
    
    //At this point, we have all the players, the numbers they bet on, and the amounts they bet, so we can start
    //the wheel spinning.
    
    int wait_time = 2; //amount of time to wait between ticking from one number to another
    Node *q = p;
    while(wait_time < 2*1000*1000) {
        usleep(wait_time);
        wait_time = (int) wait_time + (wait_time/2); //int division = 0 if <1
        q = q->get_next();
        cout << "----> " << q->get_num() << endl;
    }
    cout << "\aThe winning number is " << q->get_num() << endl;


    //if picked a user's number: print "<user> is winner"
    //else if (the user number not equal q->get_num()): print "no one wins"

    int num_winners = 0;
    for (int i = 0; i<num_players; i++){
        if(players[i].get_slot() == q->get_num()){
            cout << "PLAYER " << players[i].get_name()<< " IS THE WINNER!" << endl;
            cout << "You won " << players[i].get_bet()*2 << " dollors." << endl;
            num_winners++;
        }
    }
    if (num_winners == 0)
        cout << "No ones's number matches the winning number." << endl; 
    return 0;
}

//cout
//keep track of inputs

