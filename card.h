#include <iostream>
#include <vector>
using namespace std;

#ifndef CARD
#define CARD

class Card{
    public:
        Card();
        Card(string nm, string rk, string fc, int lv, int str, int skl, int spd, int tc);
        void setName(string newName);
        void setRank(string newRank);
        void setFaction(string newFaction);
        void setLevel(int level);
        void setStrength(int newStr);
        void setTech(int newTech);
        void setSkill(int newSkill);
        void setSpeed(int newSpd);
        void levelUp();
        int getLevel();
        int getTech();
        int getStrength();
        int getSkill();
        int getSpeed();
        string getName();
        string getRank();
        string getFaction();
        friend bool operator ==(const Card &c1, const Card &c2); //compare names
    private:
        string name, rank, faction;
        int level, strength, skill, speed, tech;

};

class Battle{
    public:
        Battle();
        Battle(string nm, string fc, int coin, int str, int skl, int spd, int tc);
        void setName(string nm);
        void setCoins(int coin);
        void setStr(int str);
        void setSkill(int skl);
        void setSpeed(int spd);
        void setTech(int tc);
        void setFaction(string fc);
        string getFaction();
        string getName();
        int getCoins();
        int getStr();
        int getSkill();
        int getSpeed();
        int getTech();
        bool battle_good(vector <Card> owned);
    private:
        string name, faction;
        int coins, strength, skill, speed, tech;
};
#endif
