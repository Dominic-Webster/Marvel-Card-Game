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
void welcome(); //for new game intro
void fight(Battle b1); //runs a battle
void store();
void getHero(); //unlock
void print(); //show roster
void updateFile();
void saveFile();
void swapSave();
int COINS;
vector <Card> owned, all;
vector <string> factions = {"Asgard", "Avenger", "Gamma", "Pym", "S.H.I.E.L.D.", "Spiderverse", "Wakanda"};
vector <Battle> battle;

int main(int argc, char const *argv[]){
    srand(time(0)); //sets random
    ifstream infile;
    infile.open("card_list.txt"); //for getting roster info
    if(infile.fail()){
        cout << "ERROR: file failure" << endl;
        exit(0);
    }

    string temp, waste, name, level, rank, faction, str, spd, skl, tc, coin;
    infile >> temp >> waste;
    COINS = stoi(waste);
    getline(infile, temp);
    getline(infile, temp);
    getline(infile, temp);
    while(temp != "-------"){ //gets owned
        stringstream s(temp);
        getline(s, name, '|');
        s >> rank >> waste >> faction >> waste >> level 
        >> waste >> str >> waste >> skl >> waste >> spd >> waste >> tc;
        Card c1(name, rank, faction, stoi(level), stoi(str), stoi(skl), stoi(spd), stoi(tc));
        owned.push_back(c1);
        getline(infile, temp);
    }
    getline(infile, temp);
    getline(infile, temp);
    while(!infile.eof()){ //gets all
        stringstream s(temp);
        getline(s, name, '|');
        s >> rank >> waste >> faction >> waste >> level >> waste 
        >> str >> waste >> skl >> waste >> spd >> waste >> tc;
        Card c1(name, rank, faction, stoi(level), stoi(str), stoi(skl), stoi(spd), stoi(tc));
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
        getline(s, faction, '|');
        s >> coin >> waste >> str >> waste >> skl >> waste >> spd >> waste >> tc;
        Battle b1(name, faction, stoi(coin), stoi(str), stoi(skl), stoi(spd), stoi(tc));
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
    if(command == "-save"){
        cout << "This will overwrite anything in save file 1. Proceed? (y/n) " << endl;
        cin >> waste;
        if(waste == "y" || waste == "Y"){
            saveFile();
            exit(0);
        }
        else{exit(0);}
    }
    if(command == "-open_save"){
        cout << "Proceed with swapping saves? (y/n) " << endl;
        cin >> waste;
        if(waste == "y" || waste == "Y"){
            swapSave();
            exit(0);
        }
        else{exit(0);}
    }
    system("clear");

    if(owned.size() == 0){ //welcome message
        welcome();
    }
    
    menu(); //start game

    return 0;
}

void menu(){
    string x;
    cout << "    - MENU -" << endl << endl;
    cout << "Characters owned: " << owned.size() << endl;
    cout << "Coins: " << COINS << endl << endl;
    cout << " (1): View Roster" << endl;
    cout << " (2): Battle" << endl;
    cout << " (3): Store" << endl;
    cout << " (4): [Exit Game]" << endl;
    cin >> x;
    system("clear");

    if(x == "1"){print();}
    else if(x == "2"){battle_menu();}
    else if(x == "3"){store();}
    else if(x == "4"){exit(0);}
    else{menu();}
}

void print(){
    cout << "    - CHARACTER ROSTER -" << endl;
    cout << "Owned: " << owned.size() << "/" << all.size() << endl << endl;

    for(size_t j = 0; j < factions.size(); j++){
        cout << "  {" << factions.at(j) << "}" << endl;
        for(size_t i = 0; i < owned.size(); i++){
            if(owned.at(i).getFaction() == factions.at(j)){
                cout << " - " << owned.at(i).getName() << " (" << owned.at(i).getRank() 
                << " - level: " << owned.at(i).getLevel() << ")" << endl;
                cout << "     Strength: " << owned.at(i).getStrength() << endl;
                cout << "        Skill: " << owned.at(i).getSkill() << endl;
                cout << "        Speed: " << owned.at(i).getSpeed() << endl;
                cout << "         Tech: " << owned.at(i).getTech() << endl << endl;
            }
        }
        cout << "--------------------" << endl;
    }

    
    int x;
    cout << " (1): [Menu]" << endl;
    cin >> x;
    system("clear");
    menu();
}

void store(){
    int x;
    cout << "    - STORE -" << endl << endl;
    cout << "Coins: " << COINS << endl << endl;
    cout << " (1): Common Pack (x1) {100 coins}" << endl;
    cout << " (2): Uncommon Pack (x5) {400 coins}" << endl; //x5
    cout << " (3): Rare Pack (x15) {1000 coins}" << endl; //x15
    cout << " (4): Mythic Pack (x20) {1300 coins}" << endl; //x20
    cout << " (5): [Menu]" << endl;
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
    else if(x == 4){
        if(COINS < 1300){
            cout << "Not enough coins" << endl << endl;
            store();
        }
        else{
            COINS -= 1300;
            for(int i = 0; i < 20; i++){getHero();} //unlock x15
            store();
        }
    }
    else{menu();}
}

void battle_menu(){
    size_t x;
    string space;
    cout << "    - BATTLE -" << endl << endl;
    for(size_t i = 0; i < battle.size(); i++){ //prints options
        if((i)%2 == 0){space = "";}
        else{space = " ";}
        cout << space << " (" << (i)+1 << "): Fight " << battle.at(i).getName()
        << " - [" << battle.at(i).getFaction() << "] - {Reward: "
        << battle.at(i).getCoins() << " coins}" << endl << endl;
    }
    cout << endl << " (" << battle.size()+1 << "): [Menu]" << endl;
    cin >> x;
    system("clear");

    if(x <= battle.size()){fight(battle.at(x-1));}
    else{menu();}
}

void fight(Battle b1){
    int stat = rand()%4, hero, enemy, z;
    size_t x;
    vector <Card> options;
    string opp;
    if(stat == 0){opp = "Strength";} //determine opposing stat
    else if(stat == 1){opp = "Skill";}
    else if(stat == 2){opp = "Speed";}
    else{opp = "Tech";}

    do{ //runs until valid input is given
    cout << "     - FIGHT -" << endl;
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
    else if(stat == 2){enemy = rand() % b1.getSpeed();
        hero = rand() % options.at(x-1).getSpeed();}
    else{enemy = rand() % b1.getTech();
        hero = rand() % options.at(x-1).getTech();}

    if(options.at(x-1).getLevel() > 99){hero+=10;}
    else if(options.at(x-1).getLevel() > 49){hero+=5;}
    else if(options.at(x-1).getLevel() > 24){hero+=2;}
    else if(options.at(x-1).getLevel() > 9){hero++;}

    cout << options.at(x-1).getName() << " vs " << b1.getName() << endl;
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
    all.at(x).getSkill(), all.at(x).getSpeed(), all.at(x).getTech()); //make new card from all list

    for(size_t i = 0; i < owned.size(); i++){ //checks for duplicates
        if(c1 == owned.at(i)){
            tester = 1;
            owned.at(i).levelUp(); //levels up the character
            i = owned.size();
        }
    }

    if(tester != 1){ //while no duplicates
        owned.push_back(c1); //add to rsoter
        cout << " - Unlocked: " << c1.getName() << " {" << c1.getFaction() << "}" << endl;
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
        << owned.at(i).getSpeed() << " | " << owned.at(i).getTech() << endl;
    }
    outfile << "-------" << endl << "ALL" << endl; //every base character
    for(size_t i = 0; i < all.size(); i++){
        outfile << all.at(i).getName() << "| " << all.at(i).getRank() << " | "
        << all.at(i).getFaction() << " | " << all.at(i).getLevel() << " | "
        << all.at(i).getStrength() << " | " << all.at(i).getSkill() << " | "
        << all.at(i).getSpeed() << " | " << all.at(i).getTech() << endl;
    }
    outfile.close();
}

void welcome(){
    int x;
    cout << "Welcome to the Marvel Card Game!" << endl;
    cout << " - Collect Classic Characters" << endl;
    cout << " - Battle Epic Enemies" << endl;
    cout << " - Level Up Your Roster" << endl;
    cout << endl << " (1): Next" << endl;
    cin >> x;
    system("clear");
    cout << "Currently, your roster is empty" << endl;
    cout << "You have been given 100 coins to start your journey" << endl;
    cout << "When you reach the menu, head to the shop" << endl;
    cout << "You can buy a Common Pack to unlock your first character" << endl;
    cout << endl << " (1): Next" << endl;
    cin >> x;
    system("clear");
    cout << "Next, head to the Battle Menu, and select your first fight" << endl;
    cout << "Continue to battle, unlock characters, and upgrade your roster" << endl;
    cout << "Good luck!" << endl;
    cout << endl << "(1): Begin Game" << endl;
    cin >> x;
    system("clear");
}

void saveFile(){
    ofstream outfile;
    string temp;
    ifstream infile;
    infile.open("card_list.txt");
    if(outfile.fail()){cout << "ERROR: file failure" << endl; exit(0);}    
    outfile.open("save_1.txt");
    if(outfile.fail()){cout << "ERROR: file failure" << endl; exit(0);}

    getline(infile, temp); 
    while(!infile.eof()){
        outfile << temp << endl;
        getline(infile, temp);
    }
    infile.close();
    outfile.close();
}

void swapSave(){
    ifstream infile;
    ofstream outfile;
    infile.open("card_list.txt");
    if(infile.fail()){cout << "ERROR: File failure" << endl; exit(0);}
    outfile.open("swap_save.txt");
    if(outfile.fail()){cout << "ERROR: File failure" << endl; exit(0);}
    string temp;

    getline(infile, temp); //send current to temp file
    while(!infile.eof()){
        outfile << temp << endl;
        getline(infile, temp);
    }
    infile.close();
    outfile.close();

    infile.open("save_1.txt");
    if(infile.fail()){cout << "ERROR: File failure" << endl; exit(0);}
    outfile.open("card_list.txt");
    if(outfile.fail()){cout << "ERROR: File failure" << endl; exit(0);}

    getline(infile, temp); //send saved to current file
    while(!infile.eof()){
        outfile << temp << endl;
        getline(infile, temp);
    }
    infile.close();
    outfile.close();

    infile.open("swap_save.txt");
    if(infile.fail()){cout << "ERROR: File failure" << endl; exit(0);}
    outfile.open("save_1.txt");
    if(outfile.fail()){cout << "ERROR: File failure" << endl; exit(0);}

    getline(infile, temp); //send saved to current file
    while(!infile.eof()){
        outfile << temp << endl;
        getline(infile, temp);
    }
    infile.close();
    outfile.close();
}