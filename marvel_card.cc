#include "card.h"
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
void campaign();
void camp_go(Campaign cam1, size_t stage);
int COINS;
string X; //for menu selects
size_t Y, STAGE; //for menu selects and stage count
vector <Card> owned, all;
vector <string> factions; 
vector <Battle> battle;
vector <Campaign> story, progress;

int main(int argc, char const *argv[]){
    srand(time(0)); //sets random
    ifstream infile;
    infile.open("card_list.txt"); //for getting roster info
    if(infile.fail()){
        cout << "ERROR: file failure" << endl;
        exit(0);
    }

    string temp, waste, name, level, rank, faction, str, spd, skl, tc, my, coin;
    int filled;
    infile >> temp >> waste;
    COINS = stoi(waste);
    getline(infile, temp);
    getline(infile, temp);
    getline(infile, temp);
    while(temp != "-------"){ //gets owned
        stringstream s(temp);
        getline(s, name, '|');
        s >> rank >> waste >> faction >> waste >> level 
        >> waste >> str >> waste >> skl >> waste >> spd >> waste >> tc >> waste >> my;
        Card c1(name, rank, faction, stoi(level), stoi(str), stoi(skl), stoi(spd), stoi(tc), stoi(my));
        owned.push_back(c1);
        getline(infile, temp);
    }
    getline(infile, temp);
    getline(infile, temp);
    while(!infile.eof()){ //gets all
        stringstream s(temp);
        getline(s, name, '|');
        s >> rank >> waste >> faction >> waste >> level >> waste 
        >> str >> waste >> skl >> waste >> spd >> waste >> tc >> waste >> my;
        Card c1(name, rank, faction, stoi(level), stoi(str), stoi(skl), stoi(spd), stoi(tc), stoi(my));
        all.push_back(c1);
        getline(infile, temp);
    }
    infile.close();

    for(size_t i = 0; i < owned.size(); i++){
        filled = 0;
        for(size_t j = 0; j < factions.size(); j++){
            if(owned.at(i).getFaction() == factions.at(j)){
                filled = 1;
                j = factions.size();
            }
        }
        if(filled == 0){factions.push_back(owned.at(i).getFaction());}
    }

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
        s >> coin >> waste >> str >> waste >> skl >> waste >> spd >> waste >> tc >> waste >> my;
        Battle b1(name, faction, stoi(coin), stoi(str), stoi(skl), stoi(spd), stoi(tc), stoi(my));
        battle.push_back(b1);
        getline(infile, temp);
    }
    infile.close();

    infile.open("campaign.txt"); //campaign
    if(infile.fail()){
        cout << "ERROR: File failure" << endl;
        exit(0);
    }
    infile >> waste >> level;
    STAGE = stoi(level);
    getline(infile, temp);
    getline(infile, temp);
    while(!infile.eof()){
        stringstream a(temp);
        getline(a, name, '|');
        a >> faction >> waste >> coin >> waste >> skl;
        Campaign cam1(name, faction, stoi(skl), stoi(coin));
        story.push_back(cam1);
        getline(infile, temp);
    }
    infile.close();

    for(size_t i = 0; i < STAGE; i++){ //get progress
        progress.push_back(story.at(i));
    }

    string command = ""; //dev commands
    if(argc == 2){
        command = argv[1];
    }
    if(command == "-reset"){
        COINS = 100;
        STAGE = 1;
        owned.erase(owned.begin(), owned.begin() + owned.size());
        if(all.size() > 14){all.erase(all.begin() + 14, all.begin() + all.size());}
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
    cout << "    - MENU -" << endl << endl;
    cout << "Characters owned: " << owned.size() << endl;
    cout << "Coins: " << COINS << endl << endl;
    cout << " (1): View Roster" << endl;
    cout << " (2): Campaign" << endl;
    cout << " (3): Battle" << endl;
    cout << " (4): Store" << endl;
    cout << " (5): [Exit Game]" << endl;
    cin >> X;
    system("clear");

    if(X == "1"){print();}
    else if(X == "2"){campaign();}
    else if(X == "3"){battle_menu();}
    else if(X == "4"){store();}
    else if(X == "5"){exit(0);}
    else{menu();}
}

void print(){
    cout << "    - CHARACTER ROSTER -" << endl << endl;
    cout << "Owned: " << owned.size() << "/" << all.size() << endl;
    cout << "--------------------" << endl;

    for(size_t j = 0; j < factions.size(); j++){
        cout << "  {" << factions.at(j) << "}" << endl << endl;
        for(size_t i = 0; i < owned.size(); i++){
            if(owned.at(i).getFaction() == factions.at(j)){
                cout << " - " << owned.at(i).getName() << " (" << owned.at(i).getRank() 
                << " - level: " << owned.at(i).getLevel() << ")" << endl;
                cout << "     Strength: " << owned.at(i).getStrength() << endl;
                cout << "        Skill: " << owned.at(i).getSkill() << endl;
                cout << "        Speed: " << owned.at(i).getSpeed() << endl;
                cout << "         Tech: " << owned.at(i).getTech() << endl;
                cout << "       Mystic: " << owned.at(i).getMystic() << endl << endl;
            }
        }
        cout << "--------------------" << endl;
    }

    cout << endl << " (1): [Menu]" << endl;
    cin >> X;
    system("clear");
    menu();
}

void store(){
    cout << "    - STORE -" << endl << endl;
    cout << "Coins: " << COINS << endl << endl;
    cout << " (1): Common Pack (x1) {100 coins}" << endl;
    cout << " (2): Uncommon Pack (x5) {400 coins}" << endl; //x5
    cout << " (3): Rare Pack (x15) {1000 coins}" << endl; //x15
    cout << " (4): Mythic Pack (x20) {1300 coins}" << endl; //x20
    cout << " (5): [Menu]" << endl;
    cin >> X;
    system("clear");

    if(X == "1"){
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
    else if(X == "2"){
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
    else if(X == "3"){
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
    else if(X == "4"){
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
    int good = 0;
    cout << "    - BATTLE -" << endl << endl;
    for(size_t i = 0; i < battle.size(); i++){ //prints options
        for(size_t j = 0; j < factions.size(); j++){
            if(battle.at(i).battle_good(owned) || battle.at(i).getFaction() == factions.at(j)){
                good = 1;
            }
        }
        if(good == 0){cout << "-Unavailable-";}
        cout << " (" << (i+1) << "): Fight " << battle.at(i).getName()
        << "- [" << battle.at(i).getFaction() << "] - {Reward: "
        << battle.at(i).getCoins() << " coins}" << endl << endl;
        good = 0;
    }
    cout << endl << " (" << battle.size()+1 << "): [Menu]" << endl;
    cin >> Y;
    system("clear");

    if(Y < battle.size()+1){fight(battle.at(Y-1));}
    else{menu();}
}

void fight(Battle b1){
    int stat = rand()%5, hero, enemy, z;
    vector <Card> options;
    string opp;
    if(stat == 0){opp = "Strength";} //determine opposing stat
    else if(stat == 1){opp = "Skill";}
    else if(stat == 2){opp = "Speed";}
    else if(stat == 3){opp = "Tech";}
    else{opp = "Mystic";}

    do{ //runs until valid input is given
    cout << "     - FIGHT -" << endl << endl;
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
    cin >> Y;
    system("clear");
    }while(Y > options.size() + 1);

    if(Y == options.size() + 1){battle_menu();} //return to battle menu

    if(stat == 0){enemy = rand() % b1.getStr();
        hero = rand() % options.at(Y-1).getStrength();} //get stats (varies)
    else if(stat == 1){enemy = rand() % b1.getSkill();
        hero = rand() % options.at(Y-1).getSkill();}
    else if(stat == 2){enemy = rand() % b1.getSpeed();
        hero = rand() % options.at(Y-1).getSpeed();}
    else if(stat == 3){enemy = rand() % b1.getTech();
        hero = rand() % options.at(Y-1).getTech();}
    else {enemy = rand() % b1.getMystic();
        hero = rand() % options.at(Y-1).getMystic();}

    if(options.at(Y-1).getLevel() > 99){hero+=10;}
    else if(options.at(Y-1).getLevel() > 49){hero+=5;}
    else if(options.at(Y-1).getLevel() > 24){hero+=2;}
    else if(options.at(Y-1).getLevel() > 9){hero++;}

    cout << options.at(Y-1).getName() << " vs " << b1.getName() << endl;
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

void campaign(){
    cout << "    - CAMPAIGN -" << endl << endl;
    cout << "Stages Unlocked: " << STAGE << "/" << story.size() << endl << endl;
    for(size_t i = 0; i < progress.size(); i++){
        cout << " (" << (i)+1 << "): " << progress.at(i).getName() <<
        "- [" << progress.at(i).getFaction() << "] - {Reward: " <<
        progress.at(i).getCoins() << " coins}" << endl << endl;
    }
    cout << " (" << (STAGE)+1 << "): [Menu]" << endl;
    cin >> Y;
    system("clear");
    if(Y <= progress.size()){camp_go(progress.at(Y-1), Y);}
    else{menu();}
}

void camp_go(Campaign cam1, size_t stage){
    int stat = rand()%5, hero, enemy, z;
    vector <Card> options;
    string opp;
    if(stat == 0){opp = "Strength";} //determine opposing stat
    else if(stat == 1){opp = "Skill";}
    else if(stat == 2){opp = "Speed";}
    else if(stat == 3){opp = "Tech";}
    else{opp = "Mystic";}

    cout << "     - STAGE " << STAGE << " -" << endl << endl;
    cout << "Select Your Champion [Opposed stat: " << opp << "]" << endl;
    for(size_t i = 0; i < owned.size(); i++){ //gives options from roster
        if(owned.at(i).getFaction() == cam1.getFaction() || cam1.getFaction() == "ALL" || cam1.getFaction() == owned.at(i).getName()){
            options.push_back(owned.at(i));
        }
    }
    for(size_t i = 0; i < options.size(); i++){ //prints options
        cout << " (" << (i)+1 << "): " << options.at(i).getName() << endl;
    }
    cout << endl << " (" << options.size() + 1 << "): [Back]" << endl; //escape option
    cin >> Y;
    system("clear");

    if(Y == options.size() + 1){campaign();} //return to battle menu

    enemy = rand() % cam1.getStat();

    if(stat == 0){hero = rand() % options.at(Y-1).getStrength();} //get stats (varies)
    else if(stat == 1){hero = rand() % options.at(Y-1).getSkill();}
    else if(stat == 2){hero = rand() % options.at(Y-1).getSpeed();}
    else if(stat == 3){hero = rand() % options.at(Y-1).getTech();}
    else {hero = rand() % options.at(Y-1).getMystic();}

    if(options.at(Y-1).getLevel() > 99){hero+=10;}
    else if(options.at(Y-1).getLevel() > 49){hero+=5;}
    else if(options.at(Y-1).getLevel() > 24){hero+=2;}
    else if(options.at(Y-1).getLevel() > 9){hero++;}

    cout << "Sending " << options.at(Y-1).getName() << " to " << cam1.getName() << endl;
    if(hero == enemy){ //determine outcome (draw)
        COINS += (cam1.getCoins() / 2);
        cout << " Results: Draw" << endl;
        cout << " Coins Earned: " << (cam1.getCoins() / 2) << endl;
    }
    else if(hero < enemy){ //determine outcome (loss)
        cout << " Results: Loss" << endl;
        cout << " Coins Earned: 0" << endl;
    }
    else{ //determine outcome (win)
        COINS +=  cam1.getCoins();
        cout << " Results: VICTORY!" << endl;
        cout << " Coins Earned: " << cam1.getCoins() << endl; 
        if(stage == STAGE && STAGE != story.size()){
            cout << " New Stage Unlocked!" << endl;
            cout << " +50 coins!" << endl;
            COINS += 50;
            progress.push_back(story.at(STAGE));
            STAGE++;
            if(STAGE == 8){
                Card card("Kilmonger", "Common", "Wakanda", 1, 15, 18, 14, 13, 2);
                cout << " Kilmonger Available" << endl;
                all.push_back(card);
            }
            if(STAGE == 11){
                Card card("Yellowjacket", "Common", "Pym", 7, 20, 15, 17, 24, 8);
                cout << " Yellowjacket Available" << endl;
                all.push_back(card);
            }
            if(STAGE == 14){
                Card card("Winter Soldier", "Common", "H.Y.D.R.A.", 5, 20, 22, 14, 16, 4);
                cout << " Winter Soldier Available" << endl;
                all.push_back(card);
            }
            if(STAGE == 18){
                Card card("Wolverine", "Uncommon", "X-Men", 10, 25, 14, 19, 6, 10);
                Card card1("Cyclops", "Unommon", "X-Men", 10, 20, 20, 15, 16, 13);
                cout << " Cyclops Available" << endl << " Wolverine Available" << endl;
                all.push_back(card); all.push_back(card1);
            }
            if(STAGE == 28){
                cout << endl << "Congratulations! You have Won!" << endl;
                COINS += 1000;
                cout << " +1,000 Coins!" << endl;
            }
        }
    }
    cout << endl << " (1): [Back]" << endl;
    cin >> z;
    system("clear");
    updateFile();
    campaign();
}

void getHero(){
    int x = rand() % all.size(), tester = 0; //x is a random numbered unlock, tester checks for duplicates
    Card c1(all.at(x).getName(), all.at(x).getRank(),
    all.at(x).getFaction(), all.at(x).getLevel(), all.at(x).getStrength(),
    all.at(x).getSkill(), all.at(x).getSpeed(), all.at(x).getTech(), all.at(x).getMystic()); //make new card from all list

    for(size_t i = 0; i < owned.size(); i++){ //checks for duplicates
        if(c1 == owned.at(i)){
            tester = 1;
            owned.at(i).levelUp(); //levels up the character
            i = owned.size();
        }
    }

    if(tester != 1){ //while no duplicates
        int n = 0;
        owned.push_back(c1); //add to rsoter
        cout << " - Unlocked: " << c1.getName() << " {" << c1.getFaction() << "}" << endl;
        for(size_t i = 0; i < factions.size(); i++){ //checks if faction needs added
            if(c1.getFaction() == factions.at(i)){n = 1;
                i = factions.size();}}
        if(n == 0){factions.push_back(c1.getFaction());}
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
        << owned.at(i).getSpeed() << " | " << owned.at(i).getTech() << " | "
        << owned.at(i).getMystic() << endl;
    }
    outfile << "-------" << endl << "ALL" << endl; //every base character
    for(size_t i = 0; i < all.size(); i++){
        outfile << all.at(i).getName() << "| " << all.at(i).getRank() << " | "
        << all.at(i).getFaction() << " | " << all.at(i).getLevel() << " | "
        << all.at(i).getStrength() << " | " << all.at(i).getSkill() << " | "
        << all.at(i).getSpeed() << " | " << all.at(i).getTech() << " | "
        << all.at(i).getMystic() << endl;
    }
    outfile.close();

    outfile.open("campaign.txt");
    if(outfile.fail()){
        cout << "ERROR: file failure" << endl; exit(0);}

    outfile << "Stage: " << STAGE << endl;
    for(size_t i = 0; i < story.size(); i++){
        outfile << story.at(i).getName() << "| " << story.at(i).getFaction() << 
        " | " << story.at(i).getCoins() << " | " << story.at(i).getStat() << endl;
    }
    outfile.close();
}

void welcome(){
    string x;
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