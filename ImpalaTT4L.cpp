// Comment (K-Kooxiushen,S-SooShaoXu,N-Ngjiahui,A-Alice)
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
#include <ctime>

using namespace std;

enum class CrewPosition
{
    PILOT,
    GUNNER,
    TORPEDO
};

// NG JIA HUI
/*
class Crew
class Weapon
class LightCannon : public Weapon
class Torpedo : public Weapon
*/

// Crew Class
class Crew
{
protected:
    int id;
    string name;

public:
    Crew(int id, const string &name) : id(id), name(name) {}
    virtual ~Crew() {}
    virtual string getRole() = 0;
    string getName() const { return name; }
};

// Pilot Class
class Pilot : public Crew
{
public:
    Pilot(int id, const string &name) : Crew(id, name) {}

    string getRole()
    {
        return "Pilot";
    }
};

// Gunner Class
class Gunner : public Crew
{
public:
    Gunner(int id, const string &name) : Crew(id, name) {}

    string getRole()
    {
        return "Gunner";
    }
};

// Torpedo Handler Class
class TorpedoHandler : public Crew
{
public:
    TorpedoHandler(int id, const string &name) : Crew(id, name) {}

    string getRole()
    {
        return "TorpedoHandler";
    }
};

// Weapon Class
class Weapon
{
protected:
    int damage;

public:
    Weapon(int damage) : damage(damage) {}
    virtual ~Weapon() {}

    int getDamage()
    {
        return damage;
    }

    virtual string getType() = 0;
};

// Light Cannon Class
class LightCannon : public Weapon
{
public:
    LightCannon(int damage) : Weapon(damage) {}

    string getType()
    {
        return "LightCannon";
    }
};

// Torpedo Class
class Torpedo : public Weapon
{
public:
    Torpedo(int damage) : Weapon(damage) {}

    string getType()
    {
        return "Torpedo";
    }
};

// ALICE
/*
class Ship
class Guerriero : public Ship
class Medio : public Ship
class Corazzata : public Ship
class Jager : public Ship
class Kreuzer : public Ship
class Fregatte : public Ship
*/

// Ship Class
class Ship
{
protected:
    string id;
    string name;
    string team;

    int hp;
    int maxHP;

    int requiredPilots;
    int requiredGunners;
    int requiredTorpedoHandlers;

    int lightCannons;
    int torpedoes;
    int lightCannonPower;
    int torpedoPower;

    double hitByLightProb;
    double hitByTorpedoProb;

    // crew containers
    vector<shared_ptr<Crew>> pilots;
    vector<shared_ptr<Crew>> gunners;
    vector<shared_ptr<Crew>> torpedoHandlers;

public:
    virtual ~Ship() {}

    // fireAt function (K)
    void fireAt(vector<shared_ptr<Ship>> &enemies)
    {
        // Ship cannot fire without a pilot
        if (pilots.empty() || !alive())
            return;

        vector<shared_ptr<Ship>> aliveEnemies = getAliveEnemies(enemies);
        if (aliveEnemies.empty())
            return;

        // Fire light cannons (one per gunner)
        for (size_t i = 0; i < gunners.size() && i < static_cast<size_t>(lightCannons); i++)
        {
            // Randomly select an enemy
            int targetIdx = rand() % aliveEnemies.size();
            shared_ptr<Ship> target = aliveEnemies[targetIdx];

            // Calculate hit probability
            double hitProb = target->getEffectiveHitByLightProb();
            double roll = (double)rand() / RAND_MAX;

            if (roll < hitProb)
            {
                // Hit!
                int damage = lightCannonPower;
                target->takeDamage(damage);
                cout << "  [" << id << "] " << name << " fires LightCannon at ["
                     << target->getId() << "] " << target->getName()
                     << " - HIT! (" << damage << " damage, " << target->getHP() << "/"
                     << target->getMaxHP() << " HP remaining)\n";
            }
            else
            {
                // Miss
                cout << "  [" << id << "] " << name << " fires LightCannon at ["
                     << target->getId() << "] " << target->getName() << " - MISS!\n";
            }
        }

        // Fire torpedoes (one per torpedo handler)
        for (size_t i = 0; i < torpedoHandlers.size() && i < static_cast<size_t>(torpedoes); i++)
        {
            // Randomly select an enemy
            int targetIdx = rand() % aliveEnemies.size();
            shared_ptr<Ship> target = aliveEnemies[targetIdx];

            // Calculate hit probability
            double hitProb = target->getEffectiveHitByTorpedoProb();
            double roll = (double)rand() / RAND_MAX;

            if (roll < hitProb)
            {
                // Hit!
                int damage = torpedoPower;
                target->takeDamage(damage);
                cout << "  [" << id << "] " << name << " fires Torpedo at ["
                     << target->getId() << "] " << target->getName()
                     << " - HIT! (" << damage << " damage, " << target->getHP() << "/"
                     << target->getMaxHP() << " HP remaining)\n";
            }
            else
            {
                // Miss
                cout << "  [" << id << "] " << name << " fires Torpedo at ["
                     << target->getId() << "] " << target->getName() << " - MISS!\n";
            }
        }
    }

    // getType function
    virtual string getType() const = 0;

    // Getters
    string getId() const
    {
        return id;
    }
    string getName() const
    {
        return name;
    }
    string getTeam() const
    {
        return team;
    }

    int getHP() const
    {
        return hp;
    }

    int getMaxHP() const
    {
        return maxHP;
    }

    bool alive() const
    {
        return hp > 0;
    }

    int getNumLightCannons() const
    {
        return lightCannons;
    }

    int getNumTorpedoes() const
    {
        return torpedoes;
    }

    int getTorpedoPower() const
    {
        return torpedoPower;
    }

    double getHitByLightProb() const
    {
        return hitByLightProb;
    }

    double getHitByTorpedoProb() const
    {
        return hitByTorpedoProb;
    }

    vector<shared_ptr<Crew>> &getPilots()
    {
        return pilots;
    }

    vector<shared_ptr<Crew>> &getGunners()
    {
        return gunners;
    }

    vector<shared_ptr<Crew>> &getTorpedoHandlers()
    {
        return torpedoHandlers;
    }

    // takeDamage function (K)
    void takeDamage(int damage)
    {
        hp -= damage;
        if (hp < 0)
            hp = 0;
    }

    // getEffectiveHitByLightProb function (K)
    double getEffectiveHitByLightProb() const
    {
        double baseProb = hitByLightProb;
        // If 2-pilot ship has only 1 pilot, increase hit probability by 25% of original
        if (requiredPilots == 2 && pilots.size() == 1)
        {
            baseProb = baseProb + (hitByLightProb * 0.25);
            if (baseProb > 1.0)
                baseProb = 1.0;
        }
        return baseProb;
    }

    // getEffectiveHitByTorpedoProb function (K)
    double getEffectiveHitByTorpedoProb() const
    {
        double baseProb = hitByTorpedoProb;
        // If 2-pilot ship has only 1 pilot, increase hit probability by 25% of original
        if (requiredPilots == 2 && pilots.size() == 1)
        {
            baseProb = baseProb + (hitByTorpedoProb * 0.25);
            if (baseProb > 1.0)
                baseProb = 1.0;
        }
        return baseProb;
    }

    // Get alive enemies
    static vector<shared_ptr<Ship>> getAliveEnemies(vector<shared_ptr<Ship>> &enemies)
    {
        vector<shared_ptr<Ship>> alive;
        for (auto &enemy : enemies)
        {
            if (enemy && enemy->alive())
            {
                alive.push_back(enemy);
            }
        }
        return alive;
    }
    // Getter for lightCannonPower
    int getLightCannonPower() const
    {
        return lightCannonPower;
    }
};

// Ship Implementation
// Zapezoids Ships
// Guerriero Class
class Guerriero : public Ship
{
public:
    Guerriero(const string &_id, const string &_name)
    {
        id = _id;
        name = _name;
        team = "Zapezoids";

        hp = maxHP = 123;

        requiredPilots = 1;
        requiredGunners = 0;
        requiredTorpedoHandlers = 0;

        lightCannons = 1;
        torpedoes = 0;

        lightCannonPower = 96;
        torpedoPower = 0;

        hitByLightProb = 0.26;
        hitByTorpedoProb = 0.06;
    }

    string getType() const
    {
        return "Guerriero";
    }
};

// Medio Class
class Medio : public Ship
{
public:
    Medio(const string &_id, const string &_name)
    {
        id = _id;
        name = _name;
        team = "Zapezoids";

        hp = maxHP = 214;

        requiredPilots = 1;
        requiredGunners = 2;
        requiredTorpedoHandlers = 0;

        lightCannons = 2;
        torpedoes = 0;

        lightCannonPower = 134;
        torpedoPower = 0;

        hitByLightProb = 0.31;
        hitByTorpedoProb = 0.11;
    }

    string getType() const
    {
        return "Medio";
    }
};

// Corazzata Class
class Corazzata : public Ship
{
public:
    Corazzata(const string &_id, const string &_name)
    {
        id = _id;
        name = _name;
        team = "Zapezoids";
        hp = maxHP = 1031;

        requiredPilots = 2;
        requiredGunners = 10;
        requiredTorpedoHandlers = 4;

        lightCannons = 10;
        torpedoes = 4;

        lightCannonPower = 164;
        torpedoPower = 293;

        hitByLightProb = 0.50;
        hitByTorpedoProb = 0.25;
    }

    string getType() const
    {
        return "Corazzata";
    }
};

//  Rogoatuskan Ships
// Jager Class
class Jager : public Ship
{
public:
    Jager(const string &_id, const string &_name)
    {
        id = _id;
        name = _name;
        team = "Rogoatuskan";
        hp = maxHP = 112;

        requiredPilots = 1;
        requiredGunners = 0;
        requiredTorpedoHandlers = 0;

        lightCannons = 1;
        torpedoes = 0;

        lightCannonPower = 101;
        torpedoPower = 0;

        hitByLightProb = 0.24;
        hitByTorpedoProb = 0.05;
    }

    string getType() const
    {
        return "Jager";
    }
};

// Kreuzer Class
class Kreuzer : public Ship
{
public:
    Kreuzer(const string &_id, const string &_name)
    {
        id = _id;
        name = _name;
        team = "Rogoatuskan";
        hp = maxHP = 212;

        requiredPilots = 1;
        requiredGunners = 2;
        requiredTorpedoHandlers = 0;

        lightCannons = 2;
        torpedoes = 0;

        lightCannonPower = 132;
        torpedoPower = 0;

        hitByLightProb = 0.29;
        hitByTorpedoProb = 0.10;
    }

    string getType() const
    {
        return "Kreuzer";
    }
};

// Fregatte Class
class Fregatte : public Ship
{
public:
    Fregatte(const string &_id, const string &_name)
    {
        id = _id;
        name = _name;
        team = "Rogoatuskan";
        hp = maxHP = 1143;

        requiredPilots = 2;
        requiredGunners = 11;
        requiredTorpedoHandlers = 5;

        lightCannons = 11;
        torpedoes = 5;

        lightCannonPower = 159;
        torpedoPower = 282;

        hitByLightProb = 0.60;
        hitByTorpedoProb = 0.30;
    }

    string getType() const
    {
        return "Fregatte";
    }
};

// Function Declarations
shared_ptr<Ship> makeShip(const string &type, const string &id, const string &name, const string &team); // creates ship based on type (ALICE)
vector<shared_ptr<Ship>> loadShipsCSV(const string &filename, const string &teamName);                   // loads ships from CSV file (SOO SHAO XU)
vector<shared_ptr<Crew>> loadCrewCSV(const string &filename);                                            // loads crew from CSV file (SOO SHAO XU)
void assignCrewOptimal(vector<shared_ptr<Crew>> &crew, vector<shared_ptr<Ship>> &ships);                 // optimally assigns crew to ships (SOO SHAO XU)
int alive(const vector<shared_ptr<Ship>> &v);                                                            // counts alive ships in vector (KOO XIU SHEN)
void displayFleetConfig(const vector<shared_ptr<Ship>> &ships, const string &teamName);                  // displays fleet configuration (KOO XIU SHEN)

// KOO XIU SHEN
int main(int argc, char *argv[])
{
    // Check command line arguments
    if (argc != 5)
    {
        cerr << "Usage: " << argv[0] << " <zShips.csv> <zCrew.csv> <rShips.csv> <rCrew.csv>\n";
        return 1;
    }

    // Load ships and crew from files
    vector<shared_ptr<Ship>> zShips = loadShipsCSV(argv[1], "Zapezoids");
    vector<shared_ptr<Ship>> rShips = loadShipsCSV(argv[3], "Rogoatuskan");
    vector<shared_ptr<Crew>> zCrew = loadCrewCSV(argv[2]);
    vector<shared_ptr<Crew>> rCrew = loadCrewCSV(argv[4]);

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

// Function Definitions (below main)

// Factory function to create ships based on type
shared_ptr<Ship> makeShip(const string &type, const string &id, const string &name, const string &team)
{
    if (team == "Zapezoids")
    {
        if (type == "Guerriero")
            return make_shared<Guerriero>(id, name);
        if (type == "Medio")
            return make_shared<Medio>(id, name);
        if (type == "Corazzata")
            return make_shared<Corazzata>(id, name);
    }
    else if (team == "Rogoatuskan")
    {
        if (type == "Jager")
            return make_shared<Jager>(id, name);
        if (type == "Kreuzer")
            return make_shared<Kreuzer>(id, name);
        if (type == "Fregatte")
            return make_shared<Fregatte>(id, name);
    }
    return nullptr;
}

// 1. Load Ships from CSV: Format [ID, Type, Name]
vector<shared_ptr<Ship>> loadShipsCSV(const string &filename, const string &teamName)
{
    vector<shared_ptr<Ship>> ships;
    ifstream file(filename);
    string line, id, type, name;

    if (!file.is_open())
    {
        cerr << "Error: Could not open " << filename << endl;
        return ships;
    }

    while (getline(file, line))
    {
        if (line.empty())
            continue;
        stringstream ss(line);
        // Splitting by comma
        if (getline(ss, id, ',') && getline(ss, type, ',') && getline(ss, name, ','))
        {
            // makeShip is the factory function Alice is writing
            auto s = makeShip(type, id, name, teamName);
            if (s)
                ships.push_back(s);
        }
    }
    file.close();
    return ships;
}

// 2. Load Crew from CSV: Format [ID, Name, Type]
vector<shared_ptr<Crew>> loadCrewCSV(const string &filename)
{
    vector<shared_ptr<Crew>> crewList;
    ifstream file(filename);
    string line, idStr, name, type;

    if (!file.is_open())
    {
        cerr << "Error: Could not open " << filename << endl;
        return crewList;
    }

    while (getline(file, line))
    {
        if (line.empty())
            continue;
        stringstream ss(line);
        if (getline(ss, idStr, ',') && getline(ss, name, ',') && getline(ss, type, ','))
        {
            int id = stoi(idStr);
            // Creating crew members based on their roles
            if (type == "pilot" || type == "Pilot")
                crewList.push_back(make_shared<Pilot>(id, name));
            else if (type == "gunner" || type == "Gunner")
                crewList.push_back(make_shared<Gunner>(id, name));
            else if (type == "torpedo handler" || type == "TorpedoHandler")
                crewList.push_back(make_shared<TorpedoHandler>(id, name));
        }
    }
    file.close();
    return crewList;
}

// 3. Optimal Crew Assignment: Spreads crew members to avoid empty ships
void assignCrewOptimal(vector<shared_ptr<Crew>> &crew, vector<shared_ptr<Ship>> &ships)
{
    if (ships.empty() || crew.empty())
        return;

    // Separate crew into pools
    vector<shared_ptr<Crew>> p, g, t;
    for (auto &c : crew)
    {
        if (c->getRole() == "Pilot")
            p.push_back(c);
        else if (c->getRole() == "Gunner")
            g.push_back(c);
        else if (c->getRole() == "TorpedoHandler")
            t.push_back(c);
    }

    size_t pIdx = 0, gIdx = 0, tIdx = 0;

    // Give every ship 1 Pilot first
    for (auto &s : ships)
    {
        if (pIdx < p.size())
            s->getPilots().push_back(p[pIdx++]);
    }

    // Assign extra pilots to 2-pilot ships
    for (auto &s : ships)
    {
        if (pIdx < p.size() && s->getPilots().size() < 2 &&
            (s->getType() == "Corazzata" || s->getType() == "Fregatte"))
        {
            s->getPilots().push_back(p[pIdx++]);
        }
    }

    // Spread Gunners and Torpedo Handlers across all available weapon slots
    bool assigned;
    do
    {
        assigned = false;
        for (auto &s : ships)
        {
            if (gIdx < g.size() && s->getGunners().size() < s->getNumLightCannons())
            {
                s->getGunners().push_back(g[gIdx++]);
                assigned = true;
            }
            if (tIdx < t.size() && s->getTorpedoHandlers().size() < s->getNumTorpedoes())
            {
                s->getTorpedoHandlers().push_back(t[tIdx++]);
                assigned = true;
            }
        }
    } while (assigned);
}

// Function to count alive ships in a vector
int alive(const vector<shared_ptr<Ship>> &v)
{
    int count = 0;
    for (const auto &s : v)
    {
        if (s && s->alive())
            count++;
    }
    return count;
}

// Function to display fleet configuration report
void displayFleetConfig(const vector<shared_ptr<Ship>> &ships, const string &teamName)
{
    cout << "========================================\n";
    cout << "       FLEET CONFIGURATION REPORT       \n";
    cout << "========================================\n\n";
    cout << "--- " << teamName << " ---\n";

    for (int i = 0; i < ships.size(); i++)
    {
        shared_ptr<Ship> s = ships[i];
        cout << "[" << s->getId() << "] "
             << left << setw(20) << s->getName()
             << "(" << s->getType() << ")\n";
        cout << "      HP: " << s->getHP() << "/" << s->getMaxHP() << "\n";

        // Display pilots
        vector<shared_ptr<Crew>> &pilots = s->getPilots();
        cout << "      Pilots (" << pilots.size() << "/" << (s->getType() == "Corazzata" || s->getType() == "Fregatte" ? 2 : 1) << "): ";
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