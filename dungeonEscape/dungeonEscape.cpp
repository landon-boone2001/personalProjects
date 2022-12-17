//dungeonEscape.cpp
/*This program reads in 3 text files: encounterList.txt, enemyList.txt, roomList.txt. These files have all the
information regarding the enemy statsstats, room directions, random events, etc. of the game.
The program will then allow you to explore a dungeon, searching for a way out. In each room, you are prompted
to enter a character input. If a character command is not recognized, the program will output an error message, 
and prompt an input again. If a room has a random encounter, there is a chance that it will have a hostile encounter.
If so, an enemy is drawn from a list for you to fight. The enemy can heal or attack, depending on its health and number
of heals remaining. If the enemy defeats you in combat, you lose. Before the final room, there is a bossfight that 
follows the same rules of combat as the previous enemies.*/
//12/5/2022
#include "Dungeon.h"

using namespace std; 

//initializes the dungeon object. reads in roomList, encounterList, and enemyList. Sets the initial player stats.
Dungeon::Dungeon() {
    readRooms();
    readEncounters();
    readEnemyList();
    player.maxHealth = 50;
    player.currentHealth = player.maxHealth;
    player.defense = 0;
    player.attackBonus = 0;
}
//reads in room from a text file. Reads in the room name, room description, and exit directions.
void Dungeon::readRooms() {
    ifstream fin;
    totalRooms = 0;
    string input;
    string inFile = "roomList.txt";
    string tempString;
    char direction;
    int exitNum = 0;
    int  i, j = 0;
    fin.open(inFile);
    while (getline(fin, input)) {
        if (input.compare("~") == 0) {
            totalRooms++;
        }
    } 
    totalRooms = totalRooms / 3;
    fin.close();
    fin.clear();
    roomList.resize(totalRooms);
    for (i = 0; i < totalRooms; i++) {
        roomList[i].desc = "";
        roomList[i].hasVisited = false;
        roomList[i].isExit = false;
        roomList[i].hasEncounter = true;
        roomList[i].exitDirections.resize(4);
        for (j =0; j < 4; j++) {
            roomList[i].exitDirections[j] = 0;
        }
        roomList[i].exitToRoom.resize(4);
        for (j =0; j < 4; j++) {
            roomList[i].exitToRoom[j] = -1;
        }
    }
    fin.open(inFile);
    for (i = 0; i < totalRooms; i++) {
        while (getline(fin, input)) {
            if (input.compare("~") == 0) {
                break;
            }
            else {
                roomList[i].roomName = input;
            }
        }
        while (getline(fin,input)) {
            if (input.compare("~") == 0) {
                break;
            }
            else {
                roomList[i].desc += input + "\n";
            }
        }
        while (getline(fin,input)) {
            if (input.compare("~") == 0) {
                break;
            }
            else {
                tempString = input.substr(2,3);
                exitNum = stoi(tempString);
                direction = input[0];
                switch(direction) {
                    case 'n' :
                        roomList[i].exitDirections[0] = 1;
                        roomList[i].exitToRoom[0] = exitNum;
                        break;
                    case 'e' :
                        roomList[i].exitDirections[1] = 1;
                        roomList[i].exitToRoom[1] = exitNum;                         
                        break;
                    case 's' :
                        roomList[i].exitDirections[2] = 1;
                        roomList[i].exitToRoom[2] = exitNum;                          
                        break;        
                    case 'w' :
                        roomList[i].exitDirections[3] = 1;
                        roomList[i].exitToRoom[3] = exitNum;                        
                        break;
                } 
            }
        }
    }
    roomList[totalRooms-1].isExit = true;
    roomList[totalRooms-1].hasEncounter = false;
    roomList[0].hasEncounter = false;
    fin.close();
    fin.clear();
}
// reads in the encounters. Reads in the encounter name, encounter description,
// if the encounter is hostile, and the stat changes.
void Dungeon::readEncounters() {
    ifstream fin;
    totalEncounters = 0;
    string input;
    string inFile = "encounterList.txt";
    int i =0;
    fin.open(inFile);
    while (getline(fin, input)) {
        if (input.compare("~") == 0) {
            totalEncounters++;
        }
    }
    totalEncounters = totalEncounters / 7;
    fin.close();
    fin.clear();
    fin.open(inFile);
    encounterList.resize(totalEncounters);

    for (i = 0; i < totalEncounters; i++) {
        while (getline(fin, input)) {
            if (input.compare("~") == 0) {
                break;
            }
            else {
                encounterList[i].encounterTitle = input;
            }
        }
        while (getline(fin,input)) {
            if (input.compare("~") == 0) {
                break;
            }
            else {
                encounterList[i].encounterDesc += input + "\n";
            }
        }
        while (getline(fin,input)) {
            if (input.compare("~") == 0) {
                break;
            }
            else {
                if (input.compare("0") ==0) {
                    encounterList[i].isHostileEncounter = false;
                }
                else {
                    encounterList[i].isHostileEncounter = true;
                }
            }
        }
        while (getline(fin,input)) {
            if (input.compare("~") == 0) {
                break;
            }
            else {
                encounterList[i].maxHealthChange = stoi(input);
            }
        }
        while (getline(fin,input)) {
            if (input.compare("~") == 0) {
                break;
            }
            else {
                encounterList[i].currentHealthChange = stoi(input);
            }
        }
        while (getline(fin,input)) {
            if (input.compare("~") == 0) {
                break;
            }
            else {
                encounterList[i].attackBonusChange = stoi(input);
            }
        }
        while (getline(fin,input)) {
            if (input.compare("~") == 0) {
                break;
            }
            else {
                encounterList[i].defenseChange = stoi(input);
            }
        }
    }
    fin.close();
    fin.clear();
}
// reads in the list of enemies. Reads in the enemy name, description, and stats.
void Dungeon::readEnemyList() {
    ifstream fin;
    totalEnemies = 0;
    string input;
    string inFile = "enemyList.txt";
    int i = 0;
    fin.open(inFile);
    while (getline(fin, input)) {
        if (input.compare("~") == 0) {
            totalEnemies++;
        }
    }
    totalEnemies = totalEnemies / 6;
    fin.close();
    fin.clear();
    fin.open(inFile);
    enemyList.resize(totalEnemies);
    for (i = 0; i < totalEnemies; i++) {
        while (getline(fin, input)) {
            if (input.compare("~") == 0) {
                break;
            }
            else {
                enemyList[i].name = input;
            }
        }
        while (getline(fin,input)) {
            if (input.compare("~") == 0) {
                break;
            }
            else {
               enemyList[i].desc += input + "\n";
            }
        }
        while (getline(fin,input)) {
            if (input.compare("~") == 0) {
                break;
            }
            else {
                enemyList[i].maxHealth = stoi(input);
            }
        }
        while (getline(fin,input)) {
            if (input.compare("~") == 0) {
                break;
            }
            else {
                enemyList[i].currentHealth = stoi(input);
            }
        }
        while (getline(fin,input)) {
            if (input.compare("~") == 0) {
                break;
            }
            else {
                enemyList[i].defense = stoi(input);
            }
        }
        while (getline(fin,input)) {
            if (input.compare("~") == 0) {
                break;
            }
            else {
                enemyList[i].attackBonus = stoi(input);
            }
        }
    }
    fin.close();
    fin.clear();
}
// prints the player stats.
void Dungeon::printPlayerStats() {
    cout << "Your Max Health: " << player.maxHealth << endl;
    cout << "Your Current Health: " << player.currentHealth << endl; 
    cout << "Your Defense: " << player.defense << endl;
    cout << "Your Attack Bonus: " << player.attackBonus << endl;
}
// randomly rolls attack for both player and enemy
int Dungeon::rollAttack () {
    return rand() % 10;
}
// randomly rolls heal for both player and enemy
int Dungeon::rollHeal () {
    return rand() %10;
}
// AI combat. Determines if the enemy attacks or heals.
// Enemy heals based on the amount of health left and the number of heals it has available, else it will attack.
int Dungeon::AIcombat(int enemy, int enemyHealCount) {
    int healAmount = 0;
    int attackAmount = 0;
    if (enemyList[enemy].currentHealth <= enemyList[enemy].maxHealth/3 && enemyHealCount > 0) {
        healAmount = rollHeal();
        if (healAmount > 0) {
            if(enemy != 14) {
                cout << "The " << enemyList[enemy].name << " heals for " << healAmount << " points." << endl;
            }
            else {
                cout << enemyList[enemy].name << " heals for " << healAmount << " points." << endl;    
            }
        }
        else {
            if(enemy != 14) {
                cout << "The " << enemyList[enemy].name << " tries to heal, but fails! " << endl;
            }
            else {
                cout << enemyList[enemy].name << " tries to heal, but fails! " << endl;    
            }        
        }
        enemyHealCount--;
    }
    else {
        attackAmount = rollAttack();
    }
    if (attackAmount > 0) {
        attackAmount += enemyList[enemy].attackBonus;
        attackAmount -= player.defense;
        if (attackAmount < 0) {
            attackAmount = 0;
             if(enemy != 14) {
                cout << "The " << enemyList[enemy].name << " swings, but you deflect the attack!" << endl; 
             }
             else {
                cout  << enemyList[enemy].name << " swings, but you deflect the attack!" << endl; 
             }
        }
        else {
            if(enemy != 14) {
                cout << "The " << enemyList[enemy].name << " attacks for " << attackAmount << " damage." << endl;
            }
            else {
                cout << enemyList[enemy].name << " attacks for " << attackAmount << " damage." << endl;
            }
        }
    }

    enemyList[enemy].currentHealth += healAmount;
    if (enemyList[enemy].currentHealth > enemyList[enemy].maxHealth) {
        enemyList[enemy].currentHealth = enemyList[enemy].maxHealth;
    }
    player.currentHealth -= attackAmount;
    return enemyHealCount;
}
// Prints the description of the room and the potential exit directions.
void Dungeon::printRoomDesc(int currentRoom) {
    string exits = "";
    cout << roomList[currentRoom].roomName << endl;
    if (currentRoom == 0 && roomList[currentRoom].hasVisited == true) {
        cout << "The cell you woke up in. It probably wouldn't be wise to linger here." << endl;
    }
    else if (currentRoom == 18 && roomList[currentRoom].hasVisited == true) {
        cout << "Zangard's throneroom. His body lays still on the floor. You don't think he'll be waking up anytime soon." << endl;
    }
    else {
        cout << roomList[currentRoom].desc << endl;
    }
    if (roomList[currentRoom].exitDirections[0] == 1) {
            exits += "n " ;
    }
    if (roomList[currentRoom].exitDirections[1] == 1) {
        exits += "e " ;
    }
    if (roomList[currentRoom].exitDirections[2] == 1) {
        exits += "s " ;
    }
    if (roomList[currentRoom].exitDirections[3] == 1) {
        exits += "w " ;
    }
    if (roomList[currentRoom].isExit == false) {                       
        cout << "Exits: " << exits << endl; 
        cout << " " << endl; 
    }
}

void Dungeon::printEncounterDescription(int currentEncounter) {
    cout << encounterList[currentEncounter].encounterDesc << endl;
}
// prints enemy description. Prints enemy's current health, attack bonus, and defense.
void Dungeon::printEnemyDesc(int currentEnemy) {
    cout << enemyList[currentEnemy].name << endl;
    cout << enemyList[currentEnemy].desc << endl;
    cout << "Enemy's health: " <<enemyList[currentEnemy].currentHealth << endl;
    cout << "Enemy's attack bonus: " <<enemyList[currentEnemy].attackBonus << endl;
    cout << "Enemy's defense: " <<enemyList[currentEnemy].defense << endl;

}

int main() {
    srand (time(NULL) );
    vector<int> usedEncounters;
    vector<int> usedEnemies;
    Dungeon dungeon;
    int rollCheck = 0;
    bool enemyTurn;
    bool choosingAction = true;
    bool running = true;
    bool rollingEncounters = true;
    bool rollingEnemies = true;
    bool inCombat = true;
    int enemyHealCount = 5;
    int currentRoom = 0;
    int currentEncounter = 0;
    int currentEnemy = 0;
    int attack;
    int heal;
    char command;
    //prints the first room's description.
    dungeon.printRoomDesc(currentRoom);
    while (running) {
        // makes sure if the room has already been visited, an encounter won't generate.
        if (dungeon.roomList[currentRoom].hasVisited == true) {
            dungeon.roomList[currentRoom].hasEncounter = false;
        }
        rollingEncounters = true;
        // win condition
        if (dungeon.roomList[currentRoom].isExit == true) {
            cout << "Congratulations, you have escaped the dungeon! You live to fight another day!";
            return 0;
        }
        //rolls for an encounter. If an encounter has already been used, it won't be used again.
        if (dungeon.roomList[currentRoom].hasEncounter) {
            if (currentRoom != 18) { // currentRoom 18 is the Boss's room.
                while (rollingEncounters) {
                    currentEncounter =rand() % (dungeon.totalEncounters - 2);
                    rollCheck = 0;
                    for (int i = 0; i < usedEncounters.size(); i++) {
                        if (currentEncounter == usedEncounters[i]) {
                            rollCheck++;
                        }
                    }
                    if( rollCheck == 0) {
                        rollingEncounters = false;
                    }
                }
            }
            else {
                currentEncounter = 19; //boss Encounter
            }
            //updates player stats
            usedEncounters.push_back(currentEncounter);
            dungeon.printEncounterDescription(currentEncounter);
            dungeon.player.maxHealth += dungeon.encounterList[currentEncounter].maxHealthChange;
            dungeon.player.currentHealth = dungeon.player.maxHealth;
            dungeon.player.currentHealth += dungeon.encounterList[currentEncounter].currentHealthChange;
            dungeon.player.defense += dungeon.encounterList[currentEncounter].attackBonusChange;
            dungeon.player.defense += dungeon.encounterList[currentEncounter].defenseChange;
            //rolls the enemy encounter similarly to the encounter roll.
            if (dungeon.encounterList[currentEncounter].isHostileEncounter) {
                if (currentRoom != 18) {
                    rollingEnemies = true;
                    while (rollingEnemies) {
                        currentEnemy = rand() % (dungeon.totalEnemies-2);
                        int rollCheck = 0;
                        for (int i = 0; i < usedEnemies.size(); i++) {
                            if (currentEnemy == usedEnemies[i]) {
                                rollCheck++;
                            }
                        }
                        if( rollCheck == 0) {
                            rollingEnemies = false;
                        }
                    }
                }
                else {
                    currentEnemy = 14; // boss enemy
                }
                usedEnemies.push_back(currentEnemy);
                cout << dungeon.enemyList[currentEnemy].name << endl;
                cout << dungeon.enemyList[currentEnemy].desc << endl;
                inCombat = true;
                enemyHealCount = 5; // amount of heals an enemy is allowed.
                while(inCombat) {
                    enemyTurn = true;
                    choosingAction = true;
                    cout << "Your health: " << dungeon.player.currentHealth << endl;
                    cout << "Enemy health: " << dungeon.enemyList[currentEnemy].currentHealth << endl;
                    while(choosingAction) {
                        attack = 0;
                        heal = 0;
                        cout << "Enter a combat command (Enter 'c' for combat command inputs): " << endl;
                        cout << "> ";
                        cin >> command;
                        // asks for a combat command referring to an attack, heal, inspecting enemy or player stats.
                        switch(command) {
                            case 'c': 
                                cout << "a  -- attack enemy." << endl;
                                cout << "h  -- heal self." << endl;
                                cout << "l  -- inspect enemy (free action)" << endl;
                                cout << "q  -- quit game." << endl;
                                cout << "p  -- prints player stats." << endl;
                                break; 
                            case 'a': 
                                attack = dungeon.rollAttack() + dungeon.player.attackBonus - dungeon.enemyList[currentEnemy].defense;
                                if ( attack < 0) {
                                    attack = 0;
                                    if (currentRoom != 18) {
                                        cout << "You swing, but the " << dungeon.enemyList[currentEnemy].name << " deflects the attack!" << endl;
                                    }
                                    else {
                                        cout << "You swing, but " << dungeon.enemyList[currentEnemy].name << " deflects the attack!" << endl;
                                    }
                                }
                                else {
                                    cout << "You swing for " << attack << " damage." << endl;
                                }
                                dungeon.enemyList[currentEnemy].currentHealth -= attack;
                                choosingAction = false;
                                break;
                            case 'h':
                                heal = dungeon.rollHeal();
                                cout << "You heal for " << heal << " health points." << endl;
                                dungeon.player.currentHealth += heal;
                                if (dungeon.player.currentHealth > dungeon.player.maxHealth) {
                                    dungeon.player.currentHealth = dungeon.player.maxHealth;
                                }
                                choosingAction = false;
                                break;
                            case 'q' :
                                if (currentRoom != 18)  {
                                    cout << "You have surrendered to the " << dungeon.enemyList[currentEnemy].name << "." << endl;
                                    cout << "GAME OVER" << endl;
                                }
                                else {
                                    cout << "You have surrendered to " << dungeon.enemyList[currentEnemy].name << "." << endl;
                                    cout << "GAME OVER" << endl;
                                }
                                return 0;
                            case 'l' : 
                                dungeon.printEnemyDesc(currentEnemy);
                                break;
                            case 'p' :
                                dungeon.printPlayerStats();
                                break;
                            default:
                                cout << "Unknown input." <<endl ;
                            break;                            
                        }
                    }
                    if (dungeon.enemyList[currentEnemy].currentHealth <= 0) {
                        if (currentRoom != 18) {
                            cout << "You have slain the " << dungeon.enemyList[currentEnemy].name << endl;
                        }
                        else {
                             cout << "You have slain " << dungeon.enemyList[currentEnemy].name << endl;
                        }
                        inCombat = false;
                        choosingAction = false;
                        enemyTurn = false;
                        dungeon.player.currentHealth = dungeon.player.maxHealth;
                    }
                    if (enemyTurn) {
                        enemyHealCount = dungeon.AIcombat(currentEnemy, enemyHealCount);
                    }
                    if (dungeon.player.currentHealth <= 0) {
                        if (currentRoom != 18) {
                            cout << "You have been felled by the " << dungeon.enemyList[currentEnemy].name << "." << endl;
                        }
                        else {
                            cout << "You have been felled by " << dungeon.enemyList[currentEnemy].name << "." << endl;    
                        }
                        cout << "GAME OVER" << endl;
                        return 0;
                    }
                }
                if (currentRoom != 18) {
                    cout << "Upon defeating the " << dungeon.enemyList[currentEnemy].name << ", you feel reinvigorated. Your health has been restored to full." << endl;
                }
                else {
                    cout << "Upon defeating " << dungeon.enemyList[currentEnemy].name << ", you feel reinvigorated. Your health has been restored to full." << endl;
                }
                dungeon.player.currentHealth = dungeon.player.maxHealth;
            }
        }
        //sets the room to be visited after a potential encounter.
        dungeon.roomList[currentRoom].hasVisited = true;
        // asks for a command for movement, playerstats, or looking around the room.
        cout << "Enter a command (type 'h' for command inputs): " << endl;
        cout << ">";
        cin >> command;
        switch (command) {
            case 'h':
                cout << "h  -- help menu." << endl;
                cout << "q  -- quit game." << endl;
                cout << "n  -- move north." << endl;
                cout << "e  -- move east." << endl;
                cout << "w  -- move west." << endl;
                cout << "s  -- move south." << endl;
                cout << "l  -- examine room." << endl;
                cout << "p  -- print player stats" << endl;
                break;
            case 'q':
                cout << "You have given up finding your way out, resigned to your fate. You hear a faint laughter in the distance." << endl ;
                cout << "GAME OVER" << endl;
                return 0;
                break;
            case 'p': 
                dungeon.printPlayerStats();
                break;
            case 'n' :
                if (dungeon.roomList[currentRoom].exitDirections[0] == 1) {
                    cout << "You moved north." << endl ;
                    cout << " " << endl;
                    currentRoom = dungeon.roomList[currentRoom].exitToRoom[0];
                    dungeon.printRoomDesc(currentRoom);
                }
                else {
                    cout << "You can't go north!" << endl;
                }
                break;
            case 'e' :
                if (dungeon.roomList[currentRoom].exitDirections[1] == 1) {
                    cout << "You moved east." << endl ;
                    cout << " " << endl;
                    currentRoom = dungeon.roomList[currentRoom].exitToRoom[1];
                    dungeon.printRoomDesc(currentRoom);   
                }
                else {
                    cout << "You can't go east!" << endl;
                }
                break;
            case 's' :
                if (dungeon.roomList[currentRoom].exitDirections[2] == 1) {
                    cout << "You moved south." << endl ;
                    cout << " " << endl;
                    currentRoom = dungeon.roomList[currentRoom].exitToRoom[2];
                    dungeon.printRoomDesc(currentRoom);
                }
                else {
                    cout << "You can't go south!" << endl;
                }
                break;        
            case 'w' :
                if (dungeon.roomList[currentRoom].exitDirections[3] == 1) {
                    cout << "You moved west." << endl ;
                    cout << " " << endl;
                    currentRoom = dungeon.roomList[currentRoom].exitToRoom[3];
                    dungeon.printRoomDesc(currentRoom);     
                }
                else {
                    cout << "You can't go west!" << endl;
                }
                break;
            case 'l' :
                dungeon.printRoomDesc(currentRoom);
                break;
            default:
                cout << "Unknown input." <<endl ;
                break;
        }
    }
}
