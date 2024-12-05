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
    tech = 10;
}

Card::Card(string nm, string rk, string fc, int lv, int str, int skl, int spd, int tc){
    name = nm != "" ? nm : "N/A";
    rank = rk != "" ? rk : "Common";
    faction = fc != "" ? fc : "neutral";
    level = lv > 0 ? lv : 1;
    strength = str > 0 ? str : 10;
    speed = spd > 0 ? spd : 10;
    skill = skl > 0 ? skl : 10;
    tech = tc > 0 ? tc : 10;
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

void Card::setTech(int newTech){
    if(newTech > 0){tech = newTech;}
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

int Card::getTech(){
    return tech;
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
    if(level == 10){rank = "Uncommon"; strength++; skill++; speed++; tech++;} //rank ups
    if(level == 25){rank = "Rare"; strength+=3; skill+=3; speed+=3; tech+=3;}
    if(level == 50){rank = "Mythic"; strength+=5; skill+=5; speed+=5; tech+=5;}
    if(level == 100){rank = "Legendary"; strength+=10; skill+=10; speed+=10; tech+=10;}

    int x;
    cout << "Select a stat to increase for " << name << endl; //stat increase choice
    cout << "(1) Strength +1 [" << strength << "]" << endl
     << "(2) Skill +1 [" << skill << "]" << endl 
     << "(3) Speed +1 [" << speed << "]" << endl
     << "(4) Tech +1 [" << tech << "]" << endl;;
    cin >> x;
    system("clear");
    if(x == 1){strength++;}
    else if(x == 2){skill++;}
    else if(x == 3){speed++;}
    else{tech++;}
}

bool operator ==(const Card &c1, const Card &c2){
    return c1.name == c2.name;
}

Battle::Battle(){
    name = "N/A";
    faction = "neutral";
    coins = 10;
    strength = 10;
    skill = 10;
    speed = 10;
    tech = 10;
}

Battle::Battle(string nm, string fc, int coin, int str, int skl, int spd, int tc){
    name = nm != "" ? nm : "N/A";
    faction = fc != "" ? fc : "neutral";
    coins = coin > 0 ? coin : 10;
    strength = str > 0 ? str : 10;
    skill = skl > 0 ? skl : 10;
    speed = spd > 0 ? spd : 10;
    tech = tc > 0 ? tc : 10;
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

void Battle::setTech(int tc){
    if(tc > 0){tech = tc;}
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

int Battle::getTech(){
    return tech;
}
