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
    mystic = 10;
}

Card::Card(string nm, string rk, string fc, int lv, int str, int skl, int spd, int tc, int my){
    name = nm != "" ? nm : "N/A";
    rank = rk != "" ? rk : "Common";
    faction = fc != "" ? fc : "neutral";
    level = lv > 0 ? lv : 1;
    strength = str > 0 ? str : 10;
    speed = spd > 0 ? spd : 10;
    skill = skl > 0 ? skl : 10;
    tech = tc > 0 ? tc : 10;
    mystic = my > 0 ? my : 10;
}

int Card::getLevel(){return level;}

void Card::increase(int num){
    if(num > 0){
        strength += num; skill += num; speed += num;
        tech += num; mystic += num;
    }
}

int Card::getStrength(){return strength;}

int Card::getSkill(){return skill;}

int Card::getSpeed(){return speed;}

int Card::getTech(){return tech;}

int Card::getMystic(){return mystic;}

string Card::getName(){return name;}

string Card::getRank(){return rank;}

string Card::getFaction(){return faction;}

void Card::levelUp(){
    level++;
    if(level == 10){rank = "Uncommon"; strength++; skill++; speed++; tech++; mystic++;} //rank ups
    if(level == 25){rank = "Rare"; strength+=3; skill+=3; speed+=3; tech+=3; mystic+=3;}
    if(level == 50){rank = "Mythic"; strength+=5; skill+=5; speed+=5; tech+=5; mystic +=5;}
    if(level == 100){rank = "Legendary"; strength+=10; skill+=10; speed+=10; tech+=10;mystic+=10;}

    int x;
    cout << "Select a stat to increase for " << name << endl; //stat increase choice
    cout << "(1) Strength +1 [" << strength << "]" << endl
     << "(2) Skill +1 [" << skill << "]" << endl 
     << "(3) Speed +1 [" << speed << "]" << endl
     << "(4) Tech +1 [" << tech << "]" << endl
     << "(5) Mystic +1 [" << mystic << "]" << endl;
    cin >> x;
    system("clear");
    if(x == 1){strength++;}
    else if(x == 2){skill++;}
    else if(x == 3){speed++;}
    else if(x == 4){tech++;}
    else{mystic++;}
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
    mystic = 10;
}

Battle::Battle(string nm, string fc, int coin, int str, int skl, int spd, int tc, int my){
    name = nm != "" ? nm : "N/A";
    faction = fc != "" ? fc : "neutral";
    coins = coin > 0 ? coin : 10;
    strength = str > 0 ? str : 10;
    skill = skl > 0 ? skl : 10;
    speed = spd > 0 ? spd : 10;
    tech = tc > 0 ? tc : 10;
    mystic = my > 0 ? my : 10;
}

string Battle::getFaction(){return faction;}

string Battle::getName(){return name;}

int Battle::getCoins(){return coins;}

int Battle::getStr(){return strength;}

int Battle::getSkill(){return skill;}

int Battle::getSpeed(){return speed;}

int Battle::getTech(){return tech;}

int Battle::getMystic(){return mystic;}

bool Battle::battle_good(vector <Card> owned){
    if(faction == "ALL"){return true;}
    for(size_t i = 0; i < owned.size(); i++){
        if(faction == owned.at(i).getName()){return true;}
    }
    return false; //default
}

Campaign::Campaign(){
    name = "N/A";
    faction = "neutral";
    stat = 10;
    coins = 10;
}

Campaign::Campaign(string nm, string fc, int st, int cn){
    name = nm != "" ? nm : "N/A";
    stat = st > 0 ? st : 10;
    coins = cn > 0 ? cn : 10;
    faction = fc != "" ? fc : "neutral";
}

int Campaign::getCoins(){return coins;}

int Campaign::getStat(){return stat;}

string Campaign::getName(){return name;}

string Campaign::getFaction(){return faction;}
