#include <iostream>
#include <vector>
using namespace std;

#ifndef CARD
#define CARD

class Card{
    public:
        Card();
        Card(string nm, string rk, string fc, int lv, int str, int skl, int spd, int tc, int my);
        void levelUp();
        void increase(int num);
        int getLevel();
        int getTech();
        int getStrength();
        int getSkill();
        int getSpeed();
        int getMystic();
        string getName();
        string getRank();
        string getFaction();
        friend bool operator ==(const Card &c1, const Card &c2); //compare names
    private:
        string name, rank, faction;
        int level, strength, skill, speed, tech, mystic;

};

class Battle{
    public:
        Battle();
        Battle(string nm, string fc, int coin, int str, int skl, int spd, int tc, int my);
        string getFaction();
        string getName();
        int getCoins();
        int getStr();
        int getSkill();
        int getSpeed();
        int getTech();
        int getMystic();
        bool battle_good(vector <Card> owned);
    private:
        string name, faction;
        int coins, strength, skill, speed, tech, mystic;
};

class Campaign{
    public:
        Campaign();
        Campaign(string nm, string fc, int st, int cn);
        string getName();
        int getStat();
        int getCoins();
        string getFaction();
    private:
        int stat, coins;
        string name, faction;
};
#endif
