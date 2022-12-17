#ifndef DUNGEON_H
#define DUNGEON_H
// Dungeon.h
// Header file for a text-based adventure game "Dungeon Escape"
// Landon Boone - CS 202
// 11-1-22

#include <iostream>
#include <fstream>
#include <algorithm>
#include <stdlib.h>
#include <time.h>
#include <string>
#include <vector>
#include <sstream>

class Dungeon {
    public:
        // stat sheet for both player and enemies
       struct stats {
            std::string name;
            std::string desc;
            int maxHealth; // base health 
            int currentHealth; 
            int attackBonus; // provides flat bonus to enemy's attack
            int defense; // provides flat reduction to player's attack
        }; 
        //struct outlining information about a room
        struct room {
            std::string roomName;
            std::string desc;
            std::vector<int> exitDirections;
            std::vector<int> exitToRoom;
            bool hasEncounter; // false for beginning and final room
            bool isExit;
            bool hasVisited; // returns true if room has been visited previously
                             // if the room has no hostile encounters, will immediately return true upon visit;
        };
        //struct outlining information about encounters
        struct encounter {
            std::string encounterTitle;
            std::string encounterDesc;
            bool isHostileEncounter;
            int maxHealthChange;
            int currentHealthChange;
            int attackBonusChange;
            int defenseChange;
        };
        int totalRooms;
        int totalEnemies;
        int totalEncounters;
        stats player; // player stats
        std::vector<stats> enemyList; // list of enemies and their stats
        std::vector<room> roomList; 
        std::vector<encounter> encounterList;
        bool isFighting;
        bool playing;

    //public:
        Dungeon();
        void readRooms(); // reads rooms from a .txt file
        void readEncounters(); // reads in possible random encounters from a .txt file
        void readEnemyList(); // reads in possible enemies from a .txt file
        void printRoomDesc(int); // prints current room description
        void printEncounterDescription(int);
        void printPlayerStats();
        void printEnemyDesc(int); // prints the enemy's description and stats
        int AIcombat(int, int);  // determines if an enemy heals or attacks
        int  rollAttack(); // rolls a die to see how much damage a player/enemy does 
        int  rollHeal(); // rolls a die to see how much the player/enemy heals
};
#endif
