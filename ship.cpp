#include <iostream>
#include <string>
#include <memory>
#include <vector>
using namespace std;

// Alice
// Ship Base Classes
class Ship {
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

    // xiushen part
    virtual void fireAt(vector<shared_ptr<Ship>> &enemies) = 0;

    virtual string getType() const = 0;

    string getId() const { 
        return id; 
    }
    string getName() const { 
        return name; 
    }
    string getTeam() const { 
        return team; 
    }

    int getHP() const {
        return hp;
    }

    int getMaxHP() const {
        return maxHP;
    }

    bool alive() const {
        return hp > 0;
    }

    int getNumLightCannons() const {
        return lightCannons
    }

    int getTorpedoPower() const {
        return torpedoPower
    }

    double getHitByLightProb() const {
        return hitByLightProb;
    }

    double getHitByTorpedoProb() const {
        return hitByTorpedoProb;
    }

    // crew access
    vector<shared_ptr<Crew>> &getPilots() {
        return pilots;
    }

    vector<shared_ptr<Crew>> &getGunner() {
        return gunners;
    }

    vector<shared_ptr<Crew>> &getTorpedoHandlers() {
        return torpedoHandlers;
    }

    void takeDamage(int damage) {
        hp -= damage;
        if (hp < 0) hp =0;
    }
};

// Ship Implementation
// Zapezoids Ships
class Guerriero : public Ship {
    public:
    Guerriero(const string& _id, const string& _name) {
        id = _id;
        name = _name;
        team = "Zapezoids";

        hp = maxHP = 123;

        requiredPilots = 1;
        requiredGunners =0;
        requiredTorpedoHandlers = 0;

        lightCannons =1;
        torpedoes =0;

        lightCannonPower =96;
        torpedoPower =0;

        hitByLightProb = 0.26;
        hitByTorpedoProb = 0.06;
    }

    string getType() const {
        return "Guerriero";
    }
    void fireAt(vector<shared_ptr<Ship>> &enemies) {}
};

class Medio : public Ship {
    public:
    Medio(const string& _id, const string& _name) {
        id = _id;
        name = _name;
        team = "Zapezoids";

        hp = maxHP = 214;

        requiredPilots = 1;
        requiredGunners =2;
        requiredTorpedoHandlers = 0;

        lightCannons =2;
        torpedoes =0;

        lightCannonPower =134;
        torpedoPower =0;

        hitByLightProb = 0.31;
        hitByTorpedoProb = 0.11;
    }

    string getType() const {
        return "Medio";
    }
    void fireAt(vector<shared_ptr<Ship>> &enemies) {}
};

class Corazzata : public Ship {
    public:
    Corazzata(const string& _id, const string& _name) {
        id = _id;
        name = _name;
        team = "Zapezoids";
        hp = maxHP = 1031;

        requiredPilots = 2;
        requiredGunners =10;
        requiredTorpedoHandlers = 4;

        lightCannons =10;
        torpedoes =4;

        lightCannonPower =164;
        torpedoPower =293;

        hitByLightProb = 0.50;
        hitByTorpedoProb = 0.25;
    }

    string getType() const {
        return "Corazzata";
    }
    void fireAt(vector<shared_ptr<Ship>> &enemies) {}
};

//  Rogoatuskan Ships
class Jager : public Ship {
    public:
    Jager(const string& _id, const string& _name) {
        id = _id;
        name = _name;
        team = "Rogoatuskan";
        hp = maxHP = 112;

        requiredPilots = 1;
        requiredGunners =0;
        requiredTorpedoHandlers = 0;

        lightCannons =1;
        torpedoes =0;

        lightCannonPower =101;
        torpedoPower =0;

        hitByLightProb = 0.24;
        hitByTorpedoProb = 0.05;
    }

    string getType() const {
        return "Jager";
    }
    void fireAt(vector<shared_ptr<Ship>> &enemies) {}
};

class Kreuzer : public Ship {
    public:
    Kreuzer(const string& _id, const string& _name) {
        id = _id;
        name = _name;
        team = "Rogoatuskan";
        hp = maxHP = 212;

        requiredPilots = 1;
        requiredGunners =2;
        requiredTorpedoHandlers = 0;

        lightCannons =2;
        torpedoes =0;

        lightCannonPower =132;
        torpedoPower =0;

        hitByLightProb = 0.29;
        hitByTorpedoProb = 0.10;
    }

    string getType() const {
        return "Kreuzer";
    }
    void fireAt(vector<shared_ptr<Ship>> &enemies) {}
};

class Fregatte : public Ship {
    public:
    Fregatte(const string& _id, const string& _name) {
        id = _id;
        name = _name;
        team = "Rogoatuskan";
        hp = maxHP = 1143;

        requiredPilots = 2;
        requiredGunners =11;
        requiredTorpedoHandlers = 5;

        lightCannons =11;
        torpedoes =5;

        lightCannonPower =159;
        torpedoPower =282;

        hitByLightProb = 0.60;
        hitByTorpedoProb = 0.30;
    }

    string getType() const {
        return "Fregatte";
    }
    void fireAt(vector<shared_ptr<Ship>> &enemies) {}
};
