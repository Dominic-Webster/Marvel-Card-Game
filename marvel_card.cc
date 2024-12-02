#include "card.h"
#include <vector>
#include <fstream>
#include <iostream>
#include <sstream>
#include <ctime>
#include <cstdlib>
using namespace std;

void menu(); //main menu
void battle_menu();
void fight(Battle b1); //runs a battle
void store();
void getHero(); //unlock
void print(); //show roster
void updateFile();
int COINS;
vector <Card> owned, all;
vector <Battle> battle;

int main(int argc, char const *argv[]){
    srand(time(0)); //sets random
    ifstream infile;
    infile.open("card_list.txt"); //for getting roster info
    if(infile.fail()){
        cout << "ERROR: file failure" << endl;
        exit(0);
    }

    string temp, waste, name, level, rank, faction, str, spd, skl, coin;
    infile >> temp >> waste;
    COINS = stoi(waste);
    getline(infile, temp);
    getline(infile, temp);
    getline(infile, temp);
    while(temp != "-------"){
        stringstream s(temp);
        getline(s, name, '|');
        s >> rank >> waste >> faction >> waste >> level >> waste >> str >> waste >> skl >> waste >> spd;
        Card c1(name, rank, faction, stoi(level), stoi(str), stoi(skl), stoi(spd));
        owned.push_back(c1);
        getline(infile, temp);
    }
    getline(infile, temp);
    getline(infile, temp);
    while(!infile.eof()){
        stringstream s(temp);
        getline(s, name, '|');
        s >> rank >> waste >> faction >> waste >> level >> waste >> str >> waste >> skl >> waste >> spd;
        Card c1(name, rank, faction, stoi(level), stoi(str), stoi(skl), stoi(spd));
        all.push_back(c1);
        getline(infile, temp);
    }
    infile.close();

    infile.open("battle.txt"); //for battle list
    if(infile.fail()){
        cout << "ERROR: File failure" << endl;
        exit(0);
    }
    getline(infile, temp);
    while(!infile.eof()){
        stringstream s(temp);
        getline(s, name, '|');
        getline(s, faction, '|'};
        s >> coin >> waste >> str >> waste >> skl >> waste >> spd;
        Battle b1(name, faction, stoi(coin), stoi(str), stoi(skl), stoi(spd));
        battle.push_back(b1);
        getline(infile, temp);
    }
    infile.close();

    string command = ""; //dev commands
    if(argc == 2){
        command = argv[1];
    }
    if(command == "-reset"){
        COINS = 100;
        owned.erase(owned.begin(), owned.begin() + owned.size());
        updateFile();
        cout << "File Reset" << endl;
        exit(0);
    }
    if(command == "-money"){
        COINS += 1000;
        updateFile();
        cout << "1000 coins have been added to your account" << endl;
        exit(0);
    }
    system("clear");
    menu(); //start game

    return 0;
}

void menu(){
    string x;
    cout << "    MENU" << endl;
    cout << "Characters owned: " << owned.size() << endl;
    cout << "Coins: " << COINS << endl;
    cout << " (1): View Roster" << endl;
    cout << " (2): Battle" << endl;
    cout << " (3): Store" << endl;
    cout << " (4): [Exit Game]" << endl;
    cin >> x;
    system("clear");

    if(x == "1"){print();}
    else if(x == "2"){battle_menu();}
    else if(x == "3"){store();}
    else{exit(0);}
}

void print(){
    cout << "    CHARACTER ROSTER" << endl;
    cout << "Owned: " << owned.size() << "/" << all.size() << endl << endl;
    for(size_t i = 0; i < owned.size(); i++){
        cout << owned.at(i).getName() << "{" << owned.at(i).getFaction() << "} (" 
        << owned.at(i).getRank() << " - level: " << owned.at(i).getLevel() << ")" << endl;
        cout << "   Strength: " << owned.at(i).getStrength() << endl;
        cout << "      Skill: " << owned.at(i).getSkill() << endl;
        cout << "      Speed: " << owned.at(i).getSpeed() << endl;
    }
    int x;
    cout << endl << " (1): [Menu]" << endl;
    cin >> x;
    system("clear");
    menu();
}

void store(){
    int x;
    cout << "    STORE" << endl;
    cout << "Coins: " << COINS << endl;
    cout << " (1): Common Pack {100 coins}" << endl;
    cout << " (2): Uncommon Pack {400 coins}" << endl; //x5
    cout << " (3): Rare Pack {1000 coins}" << endl; //x15
    cout << " (4): [Menu]" << endl;
    cin >> x;
    system("clear");

    if(x == 1){
        if(COINS < 100){
            cout << "Not enough coins" << endl << endl;
            store();
        }
        else{
            COINS -= 100;
            getHero(); //unlock
            store();
        }
    }
    else if(x == 2){
        if(COINS < 400){
            cout << "Not enough coins" << endl << endl;
            store();
        }
        else{
            COINS -= 400;
            for(int i = 0; i < 5; i++){getHero();} //unlock x5
            store();
        }
    }
    else if(x == 3){
        if(COINS < 1000){
            cout << "Not enough coins" << endl << endl;
            store();
        }
        else{
            COINS -= 1000;
            for(int i = 0; i < 15; i++){getHero();} //unlock x15
            store();
        }
    }
    else{menu();}
}

void battle_menu(){
    size_t x;
    cout << "    BATTLE" << endl;
    for(size_t i = 0; i < battle.size(); i++){ //prints options
        cout << " (" << (i)+1 << "): Fight " << battle.at(i).getName()
        << "- [" << battle.at(i).getFaction() << "] - {Reward: "
        << battle.at(i).getCoins() << " coins}" << endl;
    }
    cout << " (" << battle.size()+1 << "): [Menu]" << endl;
    cin >> x;
    system("clear");

    if(x <= battle.size()){fight(battle.at(x-1));}
    else{menu();}
}

void fight(Battle b1){
    int stat = rand()%3, hero, enemy, z;
    size_t x;
    vector <Card> options;
    string opp;
    if(stat == 0){opp = "Strength";} //determine opposing stat
    else if(stat == 1){opp = "Skill";}
    else{opp = "Speed";}

    do{ //runs until valid input is given
    cout << "     FIGHT" << endl;
    cout << "Select Your Champion [Opposed stat: " << opp << "]" << endl;
    for(size_t i = 0; i < owned.size(); i++){ //gives options from roster
        if(owned.at(i).getFaction() == b1.getFaction() || b1.getFaction() == "ALL" || b1.getFaction() == owned.at(i).getName()){
            options.push_back(owned.at(i));
        }
    }
    for(size_t i = 0; i < options.size(); i++){ //prints options
        cout << " (" << (i)+1 << "): " << options.at(i).getName() << endl;
    }
    cout << " (" << options.size() + 1 << "): [Back]" << endl; //escape option
    cin >> x;
    system("clear");
    }while(x > options.size() + 1);

    if(x == options.size() + 1){battle_menu();} //return to battle menu

    if(stat == 0){enemy = rand() % b1.getStr();
        hero = rand() % options.at(x-1).getStrength();} //get stats (variable)
    else if(stat == 1){enemy = rand() % b1.getSkill();
        hero = rand() % options.at(x-1).getSkill();}
    else{enemy = rand() % b1.getSpeed();
        hero = rand() % options.at(x-1).getSpeed();}

    if(options.at(x-1).getLevel() > 99){hero+=10;}
    else if(options.at(x-1).getLevel() > 49){hero+=5;}
    else if(options.at(x-1).getLevel() > 24){hero+=2;}
    else if(options.at(x-1).getLevel() > 9){hero++;}

    cout << options.at(x-1).getName() << "vs " << b1.getName() << endl;
    if(hero == enemy){ //determine outcome (draw)
        COINS += (b1.getCoins() / 2);
        cout << " Results: Draw" << endl;
        cout << " Coins Earned: " << (b1.getCoins() / 2) << endl;
    }
    else if(hero < enemy){ //determine outcome (loss)
        cout << " Results: Loss" << endl;
        cout << " Coins Earned: 0" << endl;
    }
    else{ //determine outcome (win)
        COINS += b1.getCoins();
        cout << " Results: VICTORY!" << endl;
        cout << " Coins Earned: " << b1.getCoins() << endl; 
    }
    cout << endl << " (1): [Back]" << endl;
    cin >> z;
    system("clear");
    updateFile();
    battle_menu();
}

void getHero(){
    int x = rand() % all.size(), tester = 0; //x is a random numbered unlock, tester checks for duplicates
    Card c1(all.at(x).getName(), all.at(x).getRank(),
    all.at(x).getFaction(), all.at(x).getLevel(), all.at(x).getStrength(),
    all.at(x).getSkill(), all.at(x).getSpeed()); //make new card from all list

    for(size_t i = 0; i < owned.size(); i++){ //checks for duplicates
        if(c1 == owned.at(i)){
            tester = 1;
            owned.at(i).levelUp(); //levels up the character
            i = owned.size();
        }
    }

    if(tester != 1){ //while no duplicates
        owned.push_back(c1); //add to rsoter
        cout << " - Unlocked: " << c1.getName() << "{" << c1.getFaction() << "}" << endl;
        cout << endl;
    }
    updateFile();
}

void updateFile(){
    ofstream outfile;
    outfile.open("card_list.txt");
    if(outfile.fail()){
        cout << "ERROR: file failure" << endl;
        exit(0);
    }

    outfile << "Coins: " << COINS << endl;
    outfile << "OWNED" << endl; //owned roster
    for(size_t i = 0; i < owned.size(); i++){
        outfile << owned.at(i).getName() << "| " << owned.at(i).getRank() << " | "
        << owned.at(i).getFaction() << " | " << owned.at(i).getLevel() << " | "
        << owned.at(i).getStrength() << " | " << owned.at(i).getSkill() << " | "
        << owned.at(i).getSpeed() << endl;
    }
    outfile << "-------" << endl << "ALL" << endl; //every base character
    for(size_t i = 0; i < all.size(); i++){
        outfile << all.at(i).getName() << "| " << all.at(i).getRank() << " | "
        << all.at(i).getFaction() << " | " << all.at(i).getLevel() << " | "
        << all.at(i).getStrength() << " | " << all.at(i).getSkill() << " | "
        << all.at(i).getSpeed() << endl;
    }
    outfile.close();
}
