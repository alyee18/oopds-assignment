//Comment (K-Kooxiushen,S-SooShaoXu,N-Ngjiahui,A-Alice)
/*
(K -> A)
ship class里面要有：
void fireAt(vector<shared_ptr<Ship>> &enemies); 这个我的part（K）
string getType() const;
string getName() const;
string getTeam() const;
int getHP() const;
int getMaxHP() const;
string getId() const { return id; }
bool alive() const;
vector<shared_ptr<Crew>> &getPilots() { return pilots; }
vector<shared_ptr<Crew>> &getGunners() { return gunners; }
vector<shared_ptr<Crew>> &getTorpedoHandlers() { return torpedoHandlers; }
*/


#include <iostream>
#include <string>
#include <vector>
#include <memory>
#include <random>
#include <sstream>
#include <fstream>
#include <algorithm>
#include <cctype>
#include <utility>
#include <iomanip>

using namespace std;

enum class CrewPosition
{
    PILOT,
    GUNNER,
    TORPEDO
};

//NG JIA HUI
/*
class Crew
class Weapon
class LightCannon : public Weapon 
class Torpedo : public Weapon
*/

//ALICE
/*
class Ship
class Guerriero : public Ship
class Medio : public Ship
class Corazzata : public Ship
class Jager : public Ship
class Kreuzer : public Ship
class Fregatte : public Ship
*/

//Function Declaration
shared_ptr<Ship> makeShip(const string &type, const string &id, const string &name, const string &team); // creates ship based on type （ALICE)
vector<shared_ptr<Ship>> loadShipsCSV(const string &filename, const string &teamName); // loads ships from CSV file (SOO SHAO XU)
vector<shared_ptr<Crew>> loadCrewCSV(const string &filename); // loads crew from CSV file (SOO SHAO XU)
void assignCrewToShips(vector<shared_ptr<Crew>> &crew, vector<shared_ptr<Ship>> &ships); // assigns crew to ships (SOO SHAO XU)
int alive(const vector<shared_ptr<Ship>> &v); // counts alive ships in vector (KOO XIU SHEN)
void displayFleetConfig(const vector<shared_ptr<Ship>> &ships, const string &teamName); // displays fleet configuration (KOO XIU SHEN)
void assignCrewOptimal(vector<shared_ptr<Crew>> &crew, vector<shared_ptr<Ship>> &ships); // optimally assigns crew to ships (SOO SHAO XU)

// KOO XIU SHEN
int main()
{
    // Load ships and crew from files
    vector<shared_ptr<Ship>> zShips = loadShipsCSV("zShips1.csv", "Zapezoids");
    vector<shared_ptr<Ship>> rShips = loadShipsCSV("rShips1.csv", "Rogoatuskan");
    vector<shared_ptr<Crew>> zCrew = loadCrewCSV("zCrew1.csv");
    vector<shared_ptr<Crew>> rCrew = loadCrewCSV("rCrew1.csv");

    // Assign crew to ships optimally
    assignCrewOptimal(zCrew, zShips);
    assignCrewOptimal(rCrew, rShips);

    // Display fleet configuration
    displayFleetConfig(zShips, "ZAPEZOID FLEET");
    displayFleetConfig(rShips, "ROGOATUSKAN FLEET");

    cout << "========================================\n";
    cout << "              BATTLE START              \n";
    cout << "========================================\n\n";

    srand(time(0)); // Seed random number generator
    int round = 1;

    // Battle loop - runs until one team is eliminated
    while (alive(zShips) > 0 && alive(rShips) > 0)
    {
        cout << "\n>>> ROUND " << round << " <<<\n";

        // Each ship fires at enemy ships
        for (shared_ptr<Ship> &s : zShips)
            s->fireAt(rShips);
        for (shared_ptr<Ship> &s : rShips)
            s->fireAt(zShips);

        // Display round summary
        cout << "\n--- Round Status Report ---\n";
        cout << "Zapezoids:\n";
        for (shared_ptr<Ship> &s : zShips)
        {
            if (s->alive())
                cout << " [" << s->getId() << "] " << s->getType() << " " << s->getName()
                     << " (" << s->getHP() << "/" << s->getMaxHP() << ")\n";
            else
                cout << " [" << s->getId() << "] " << s->getType() << " " << s->getName()
                     << " -- DESTROYED --\n";
        }
        cout << "Rogoatuskans:\n";
        for (shared_ptr<Ship> &s : rShips)
        {
            if (s->alive())
                cout << " [" << s->getId() << "] " << s->getType() << " " << s->getName()
                     << " (" << s->getHP() << "/" << s->getMaxHP() << ")\n";
            else
                cout << " [" << s->getId() << "] " << s->getType() << " " << s->getName()
                     << " -- DESTROYED --\n";
        }

        round++;
    }

    // Display battle results
    cout << "\n========================================\n";
    cout << "              FINAL RESULT              \n";
    cout << "========================================\n";

    if (alive(zShips) > 0)
    {
        cout << "*** ZAPEZOIDS WIN! ***\n";
        cout << "\nSurvivors:\n";
        for (shared_ptr<Ship> &s : zShips)
            if (s->alive())
                cout << " [" << s->getId() << "] " << s->getType() << " " << s->getName()
                     << " (" << s->getHP() << "/" << s->getMaxHP() << ")\n";
    }
    else if (alive(rShips) > 0)
    {
        cout << "*** ROGOATUSKANS WIN! ***\n";
        cout << "\nSurvivors:\n";
        for (shared_ptr<Ship> &s : rShips)
            if (s->alive())
                cout << " [" << s->getId() << "] " << s->getType() << " " << s->getName()
                     << " (" << s->getHP() << "/" << s->getMaxHP() << ")\n";
    }
    else
    {
        cout << "*** ALL SHIPS DESTROYED; DRAW. ***\n";
    }
    cout << "========================================\n";

    return 0;
}

// function declaration for display fleet configuration report
void displayFleetConfig(const vector<shared_ptr<Ship>> &ships, const string &teamName)
{
    cout << "========================================\n";
    cout << "       FLEET CONFIGURATION REPORT       \n";
    cout << "========================================\n\n";
    cout << "--- " << teamName << " FLEET ---\n";

    for (int i = 0; i < ships.size(); i++)
    {
        shared_ptr<Ship> s = ships[i];
        cout << "[" << s->getId() << "] "
             << left << setw(20) << s->getName()
             << "(" << s->getType() << ")\n";
        cout << "      HP: " << s->getHP() << "/" << s->getMaxHP() << "\n";

        // Display pilots
        vector<shared_ptr<Crew>> &pilots = s->getPilots();
        cout << "      Pilots (" << pilots.size() << "/" << s->getPilots().size() << "): ";
        for (int j = 0; j < pilots.size(); j++)
        {
            if (j > 0)
                cout << ", ";
            cout << pilots[j]->getName();
        }
        cout << "\n";

        // Display gunners
        vector<shared_ptr<Crew>> &gunners = s->getGunners();
        cout << "      Gunners (" << gunners.size() << "/" << s->getNumLightCannons() << "): ";
        for (int j = 0; j < gunners.size(); j++)
        {
            if (j > 0)
                cout << ", ";
            cout << gunners[j]->getName();
        }
        cout << "\n";

        // Display torpedo handlers
        vector<shared_ptr<Crew>> &torps = s->getTorpedoHandlers();
        cout << "      Torp Handlers (" << torps.size() << "/" << s->getNumTorpedoes() << "): ";
        for (int j = 0; j < torps.size(); j++)
        {
            if (j > 0)
                cout << ", ";
            cout << torps[j]->getName();
        }
        cout << "\n";
        cout << "--------------------------------------------------\n";
    }
    cout << "\n";
}
// KOO XIU SHEN
