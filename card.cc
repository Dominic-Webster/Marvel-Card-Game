#include "card.h"
#include <iostream>
using namespace std;

Card::Card(){
    name = "N/A";
    rank = "Common";
    faction = "neutral";
    level = 1;
    strength = 10;
    skill = 10;
    speed = 10;
}

Card::Card(string nm, string rk, string fc, int lv, int str, int skl, int spd){
    name = nm != "" ? nm : "N/A";
    rank = rk != "" ? rk : "Common";
    faction = fc != "" ? fc : "neutral";
    level = lv > 0 ? lv : 1;
    strength = str > 0 ? str : 1;
    speed = spd > 0 ? spd : 1;
    skill = skl > 0 ? skl : 1;
}

void Card::setName(string newName){
    if(newName != ""){name = newName;}
}

void Card::setRank(string newRank){
    if(newRank != ""){rank = newRank;}
}

void Card::setFaction(string newFaction){
    if(newFaction != ""){faction = newFaction;}
}

void Card::setLevel(int newLevel){
    if(newLevel > 0){level = newLevel;}
}

void Card::setStrength(int newStr){
    if(newStr > 0){strength = newStr;}
}

void Card::setSpeed(int newSpeed){
    if(newSpeed > 0){speed = newSpeed;}
}

void Card::setSkill(int newSkill){
    if(newSkill > 0){skill = newSkill;}
}

int Card::getLevel(){
    return level;
}

int Card::getStrength(){
    return strength;
}

int Card::getSkill(){
    return skill;
}

int Card::getSpeed(){
    return speed;
}

string Card::getName(){
    return name;
}

string Card::getRank(){
    return rank;
}

string Card::getFaction(){
    return faction;
}

void Card::levelUp(){
    level++;
    if(level == 10){rank = "Uncommon"; strength++; skill++; speed++;} //rank ups
    if(level == 25){rank = "Rare"; strength+=3; skill+=3; speed+=3;}
    if(level == 50){rank = "Mythic"; strength+=5; skill+=5; speed+=5;}
    if(level == 100){rank = "Legendary"; strength+=10; skill+=10; speed+=10;}

    int x;
    cout << "Select a stat to increase for " << name << endl; //stat increase choice
    cout << "(1) Strength +1 [" << strength << "]" << endl
     << "(2) Skill +1 [" << skill << "]" << endl 
     << "(3) Speed +1 [" << speed << "]" << endl;
    cin >> x;
    system("clear");
    if(x == 1){strength++;}
    else if(x == 2){skill++;}
    else{speed++;}
}

bool operator ==(const Card &c1, const Card &c2){
    return c1.name == c2.name;
}

Battle::Battle(){
    name = "N/A";
    faction = "neutral";
    coins = 10;
    strength = 1;
    skill = 1;
    speed = 1;
}

Battle::Battle(string nm, string fc, int coin, int str, int skl, int spd){
    name = nm != "" ? nm : "N/A";
    faction = fc != "" ? fc : "neutral";
    coins = coin > 0 ? coin : 10;
    strength = str > 0 ? str : 1;
    skill = skl > 0 ? skl : 1;
    speed = spd > 0 ? spd : 1;
}

void Battle::setName(string nm){
    if(nm != ""){name = nm;}
}

void Battle::setCoins(int coin){
    if(coin > 0){coins = coin;}
}

void Battle::setStr(int str){
    if(str > 0){strength = str;}
}

void Battle::setSkill(int skl){
    if(skl > 0){skill = skl;}
}

void Battle::setSpeed(int spd){
    if(spd > 0){speed = spd;}
}

void Battle::setFaction(string fc){
    if(fc != ""){faction = fc;}
}

string Battle::getFaction(){
    return faction;
}

string Battle::getName(){
    return name;
}

int Battle::getCoins(){
    return coins;
}

int Battle::getStr(){
    return strength;
}

int Battle::getSkill(){
    return skill;
}

int Battle::getSpeed(){
    return speed;
}
