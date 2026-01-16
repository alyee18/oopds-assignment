#include <iostream>
#include <string>
#include <memory>
using namespace std;

// Alice
// Ship Classes
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

    public:
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

    void takeDamage(int damage) {
        hp -= damage;
        if (hp < 0) hp =0;
    }

    bool alive() const {
        return hp > 0;
    }

    double getHitByLightProb() const {
        return hitByLightProb;
    }

    double getHitByTorpedoProb() const {
        return hitByTorpedoProb;
    }
};

//  Zapezoids Ships
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
};

int main() {
    shared_ptr<Ship> s1 = make_shared<Guerriero>("Z1", "Alpha");
    shared_ptr<Ship> s2 = make_shared<Fregatte>("R1", "Omega");

    cout << s1->getId() << " "
         << s1->getType() << " "
         << s1->getName() << " "
         << s1->getTeam() << " HP: "
         << s1->getHP() << endl;

    s1->takeDamage(50);

    cout << "After damage HP: " << s1->getHP() << endl;

    cout << s2->getId() << " "
         << s2->getType() << " "
         << s2->getName() << " "
         << s2->getTeam() << " HP: "
         << s2->getHP() << endl;

    return 0;
}