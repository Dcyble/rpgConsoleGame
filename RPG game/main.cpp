#include <iostream>
#include <vector>
#include <algorithm>
#include <random>
#include <map>

struct Person {
    std::string name;
    std::string role;
    float health;
    float damage;

    Person(std::string n, float h, float d) : name(n), health(h), damage(d) {}
    Person(std::string n, std::string r, float h, float d) : name(n), role(r), health(h), damage(d) {}
};

class Battle {
private:
    std::string playerAttackTarget;
    std::string playerBlockTarget;
    std::string enemyAttackTarget;
    std::string enemyBlockTarget;    

    void playerMove() {
        int switcher;

        std::cout << "Where are you going to attack? Head|Body|Legs\n";
        switcher = 1;
        playerAttackChoice(switcher);

        std::cout << "What are you going to block? Head|Body|Legs\n";
        switcher = 2;
        playerAttackChoice(switcher);
    }

    void playerAttackChoice(int& switcher) {
        std::string input;

        do {
            std::cin >> input;            

            if (input != "head" && input != "body" && input != "legs") std::cout << "Incorrect input!\n";
            else {
                switch (switcher) {
                case 1:
                    playerAttackTarget = input;
                    break;
                case 2:
                    playerBlockTarget = input;
                    break;
                }
                break;
            }
        } while (true);
    }

    void enemyMove() {
        std::vector<std::string> bodyParts{"head", "body", "legs"};
        
        std::random_device rd;
        std::mt19937 gen(rd());
        std::uniform_int_distribution<> distr(0, bodyParts.size() - 1);

        enemyAttackTarget = bodyParts[distr(gen)];
        enemyBlockTarget = bodyParts[distr(gen)];
    }

    void calculatePlayerDamageMuliplier(float& playerDamageMultipier, Person& player) {             
        if (player.role == "Assasin") {
            std::srand(std::time(nullptr));
            int number = std::rand() % 3 + 1;

            if (number == 1) playerDamageMultipier = 2;
        }
        if (player.role == "Berserk") playerDamageMultipier = 300.0 / player.health;
    }

    void calculatePlayerAttack(Person& player, Person& enemy) {
        if (playerAttackTarget == enemyBlockTarget) std::cout << "The enemy blocked your attack!\n";
        else {
            float playerDamageMultipier = 1.0;

            calculatePlayerDamageMuliplier(playerDamageMultipier, player);
            enemy.health -= player.damage * playerDamageMultipier;
        }
    }

    void calculateEnemyAttack(Person& player, Person& enemy) {
        if (playerBlockTarget == enemyAttackTarget) std::cout << "You blocked enemy attack!\n";
        else {
            float playerBlockMultipier = 1.0;

            if (player.role == "Warrior") {
                std::srand(std::time(nullptr));
                int number = std::rand() % 3 + 1;

                if (number == 1) playerBlockMultipier = 10.0;
            }
            player.health -= enemy.damage / playerBlockMultipier;
        }
    }
     
public:
    void battleScript(Person& player ,Person& enemy) {
        int moveNumber = 1;
        
        do {
            this->playerMove();
            this->enemyMove();
            this->calculatePlayerAttack(player, enemy);
            this->calculateEnemyAttack(player, enemy);

            std::cout << "Move " << moveNumber << " is over, results:\n You have " << player.health << " HP |VS| " << enemy.name << " has " << enemy.health << std::endl;

            if (player.health <= 0 || enemy.health <= 0) break;
            else moveNumber++;
        } while (true);        
    };
};

class Enemies {
private:
    std::map<int, Person> enemies = {
        {1, {"Skeleton", 50.0f, 10.0f}},
        {2, {"Rotting Zombie", 80.0f, 12.0f}},
        {3, {"Orc Warrior", 120.0f, 18.0f}},
        {4, {"Dark Cultist", 100.0f, 25.0f}},
        {5, {"Wraith Marauder", 140.0f, 20.0f}},
        {6, {"Obsidian Golem", 250.0f, 30.0f}},
        {7, {"Fire Elemental", 180.0f, 40.0f}},
        {8, {"Shadow Assassin", 160.0f, 45.0f}},
        {9, {"Arch-Necromancer", 200.0f, 35.0f}},
        {10, {"Elder Dread Dragon", 600.0f, 75.0f}}
    };

public:
    Person getEnemyByDoor(int door) {
        return enemies.find(door)->second;
    }

    int getMaxDoor() {
        return enemies.rbegin()->first;
    }
};

void chooseRole(std::string& playerRole, float& playerHealth, float& playerDamage) {
    std::string input;

    do {
        std::cin >> input;

        if (input == "assasin") {
            playerRole = "Assasin";
            playerHealth = 250.0;
            playerDamage = 12.0;
            break;
        }
        else if (input == "warrior") {
            playerRole = "Warrior";
            playerHealth = 400.0;
            playerDamage = 10.0;
            break;
        }
        else if (input == "berserk") {
            playerRole = "Berserk";
            playerHealth = 300.0;
            playerDamage = 2.0;
            break;
        }
        /*else if (input == "test") {
            playerRole = "Assasin";
            playerHealth = 100000.0;
            playerDamage = 2000.0;
            break;
        }*/
        else std::cout << "Incorrect input!\n";
    } while (true);
}

int main()
{    
    std::string playerRole;
    float playerHealth;
    float playerDamage;

    Enemies enemies;

    do { //вхіж в данж
        std::cout << "You enter into the dungeon...\nPick your role: Assasin|Warrior|Berserk\n";

        chooseRole(playerRole, playerHealth, playerDamage);
        Person player("Hero", playerRole, playerHealth, playerDamage);
        int door = 1;
        
        do { //прохідка по дверям
            Person enemy(enemies.getEnemyByDoor(door));

            std::cout << "Great, " << player.role << ", you open "<< door << " door...\nYou initiate the battle!\nYour enemy - "
                << enemy.name << " (" << enemy.health << "HP, " << enemy.damage << "DMG)\n";

            Battle battle;

            battle.battleScript(player, enemy);

            if (player.health <= 0) {
                std::string input;
                bool isRestart = false;

                std::cout << "You are dead! Restart the game? Yes|No\n";

                do { //вибір після смерті
                    std::cin >> input;

                    if (input == "no") {
                        std::cout << "Game over.\n";
                        return 0;
                    }
                    else if (input == "yes") {
                        isRestart = true;
                        break;
                    }
                    else std::cout << "Incorrect input\n";
                } while (true);

                if (isRestart) break;
            }
            else if (door == enemies.getMaxDoor()) {
                std::cout << "Congratulations! You have completed the game!\n";
                return 0;
            }
            else std::cout << "Congratulations, it's win!\n";

            if (door < enemies.getMaxDoor()) door++;
        } while (true);
    } while (true);
}