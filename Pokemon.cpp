#include <iostream>
#include <string>
#include <vector>
#include <map>
#include <cstdlib>
#include <ctime>
#include <limits>
#include <algorithm>

using namespace std;
enum class Type { FIRE, WATER, GRASS, ELECTRIC, GROUND, NORMAL };
const string TypeNames[] = { "Fire~ 🔥", "Water~ 💧", "Grass~ 🌿", "Electric~ ⚡", "Ground~ 🌍", "Normal~" };
enum class Status { NONE, BURNED, PARALYZED, POISONED };
const string StatusMessages[] = {
    "", 
    "is hurt by the burn! >_<", 
    "can't move! (≧﹏≦)", 
    "takes poison damage! ;_;"
};
map<pair<Type, Type>, float> typeMatchup = {
    {{Type::FIRE, Type::GRASS}, 2.0f}, 
    {{Type::FIRE, Type::WATER}, 0.5f},
    {{Type::WATER, Type::FIRE}, 2.0f},
    {{Type::WATER, Type::GROUND}, 2.0f},
    {{Type::GRASS, Type::WATER}, 2.0f},
    {{Type::GRASS, Type::GROUND}, 2.0f},
    {{Type::ELECTRIC, Type::WATER}, 2.0f},
    {{Type::ELECTRIC, Type::GROUND}, 0.0f},
    {{Type::GROUND, Type::FIRE}, 2.0f}
};

class Move {
private:
    string name;
    Type type;
    int power;
    int accuracy;
    int pp;
    int maxPP;
    Status effect;
    float effectChance;

public:
    Move(string n, Type t, int pwr, int acc, int pp, Status eff = Status::NONE, float chance = 0.0f)
        : name(n), type(t), power(pwr), accuracy(acc), pp(pp), maxPP(pp), effect(eff), effectChance(chance) {}

    string getName() const { return name + "~"; }
    Type getType() const { return type; }
    int getPower() const { return power; }
    int getAccuracy() const { return accuracy; }
    int getPP() const { return pp; }
    Status getEffect() const { return effect; }
    float getEffectChance() const { return effectChance; }

    bool use() {
        if (pp > 0) {
            pp--;
            return true;
        }
        return false;
    }

    void restorePP(int amount) {
        pp = min(maxPP, pp + amount);
    }

    void display() const {
        cout << "✨ " << name << "~ [" << TypeNames[(int)type] << "]";
        cout << "\n   Power: " << power << " | Accuracy: " << accuracy << "%";
        cout << "\n   PP: " << pp << "/" << maxPP;
        if (effect != Status::NONE) {
            cout << "\n   Effect: " << StatusMessages[(int)effect] << " (" << (effectChance*100) << "%)";
        }
        cout << endl;
    }
};

class Pokemon {
private:
    string nickname;
    string species;
    Type type;
    int level;
    int hp;
    int maxHP;
    int attack;
    int defense;
    int speed;
    vector<Move*> moves;
    Status status;
    bool protectedThisTurn;

public:
    Pokemon(string name, string species, Type t, int lvl, int hp, int atk, int def, int spd)
        : nickname(name), species(species), type(t), level(lvl), 
          hp(hp), maxHP(hp), attack(atk), defense(def), speed(spd),
          status(Status::NONE), protectedThisTurn(false) {}

    ~Pokemon() {
        for (auto move : moves) {
            delete move;
        }
    }

    void addMove(Move* move) {
        if (moves.size() < 4) {
            moves.push_back(move);
        }
    }

    const vector<Move*>& getMoves() const {
        return moves;
    }

    void takeDamage(int damage) {
        hp = max(0, hp - damage);
    }

    void heal(int amount) {
        hp = min(maxHP, hp + amount);
    }

    void fullRestore() {
        hp = maxHP;
        status = Status::NONE;
        for (auto move : moves) {
            move->restorePP(move->getPP());
        }
    }

    bool isFainted() const {
        return hp <= 0;
    }

    bool canAttack() const {
        if (status == Status::PARALYZED) {
            return (rand() % 100) < 75;
        }
        return true;
    }

    void applyStatus(Status newStatus) {
        if (status == Status::NONE && (rand() % 100) < 70) {
            status = newStatus;
            cout << nickname << " got " << StatusMessages[(int)status] << endl;
        }
    }

    void applyStatusEffects() {
        if (isFainted()) return;
        
        switch(status) {
            case Status::BURNED:
            case Status::POISONED:
                takeDamage(maxHP / 8);
                cout << nickname << " " << StatusMessages[(int)status] << endl;
                break;
            case Status::PARALYZED:
                cout << nickname << " " << StatusMessages[(int)status] << endl;
                break;
            default:
                break;
        }
    }

    void protect() {
        protectedThisTurn = true;
    }

    void resetProtection() {
        protectedThisTurn = false;
    }

    bool isProtected() const {
        return protectedThisTurn;
    }

    void displayStatus() const {
        cout << "\n♡ " << nickname << " the " << species << " ♡";
        cout << "\nLv." << level << " [" << TypeNames[(int)type] << "]";
        cout << "\nHP: ";
        int bars = static_cast<int>((static_cast<float>(hp) / maxHP) * 10);
        for (int i = 0; i < 10; i++) {
            cout << (i < bars ? "♥" : "♡");
        }
        cout << " " << hp << "/" << maxHP;
        
        if (status != Status::NONE) {
            cout << "\nStatus: " << StatusMessages[(int)status];
        }
        cout << endl;
    }

    void displayMoves() const {
        cout << "\nMoves:" << endl;
        for (size_t i = 0; i < moves.size(); i++) {
            cout << i+1 << ". ";
            moves[i]->display();
        }
        if (moves.size() < 4) {
            cout << moves.size()+1 << ". Protect~ 🛡️" << endl;
        }
    }

    string getNickname() const { return nickname; }
    Type getType() const { return type; }
    int getLevel() const { return level; }
    int getHP() const { return hp; }
    int getMaxHP() const { return maxHP; }
    int getAttack() const { return attack; }
    int getDefense() const { return defense; }
    int getSpeed() const { return speed; }
    Status getStatus() const { return status; }
};

class Battle {
private:
    Pokemon* player;
    Pokemon* opponent;
    int turnCount;

    float getTypeEffectiveness(Type moveType, Type pokemonType) {
        auto matchup = typeMatchup.find({moveType, pokemonType});
        if (matchup != typeMatchup.end()) {
            return matchup->second;
        }
        return 1.0f;
    }

    bool doesAttackHit(int moveAccuracy, int targetSpeed) {
        return (rand() % 100) < min(100, max(0, moveAccuracy - targetSpeed/4));
    }

    int calculateDamage(Move* move, Pokemon* attacker, Pokemon* defender) {
        if (!move || !doesAttackHit(move->getAccuracy(), defender->getSpeed())) {
            cout << attacker->getNickname() << "'s attack missed! (´；ω；｀)" << endl;
            return 0;
        }
        float stab = (move->getType() == attacker->getType()) ? 1.5f : 1.0f;
        float effectiveness = getTypeEffectiveness(move->getType(), defender->getType());
        bool isCritical = (rand() % 16) == 0;
        float critical = isCritical ? 1.5f : 1.0f;
        int damage = (((2 * attacker->getLevel() / 5 + 2) * move->getPower() * attacker->getAttack() / defender->getDefense()) / 50 + 2);
        damage = static_cast<int>(damage * stab * effectiveness * critical);
        if (defender->isProtected()) {
            damage /= 2;
            cout << defender->getNickname() << "'s protection reduced damage! 🛡️" << endl;
        }
        if (effectiveness > 1.0f) {
            cout << "It's super effective! (★ω★)/" << endl;
        } else if (effectiveness < 1.0f && effectiveness > 0.0f) {
            cout << "Not very effective... (´• ω •｀)" << endl;
        } else if (effectiveness == 0.0f) {
            cout << "It had no effect! (⊙_⊙;)？" << endl;
            return 0;
        }

        if (isCritical) {
            cout << "A critical hit! ✨" << endl;
        }

        return damage;
    }

    void playerTurn() {
        cout << "\n=== " << player->getNickname() << "'s Turn ===" << endl;
        player->displayStatus();
        player->displayMoves();

        int choice;
        while (true) {
            cout << "\nChoose an action (1-" << player->getMoves().size()+1 << "): ";
            cin >> choice;
            
            if (cin.fail() || choice < 1 || choice > static_cast<int>(player->getMoves().size())+1) {
                cout << "Invalid choice! (╯°□°）╯︵ ┻━┻" << endl;
                clearInput();
                continue;
            }
            break;
        }

        if (choice == static_cast<int>(player->getMoves().size())+1 && player->getMoves().size() < 4) {
            player->protect();
            cout << player->getNickname() << " is protecting itself! 🛡️" << endl;
        } else {
            Move* selectedMove = player->getMoves()[choice-1];
            if (selectedMove && selectedMove->use()) {
                int damage = calculateDamage(selectedMove, player, opponent);
                if (damage > 0) {
                    opponent->takeDamage(damage);
                    cout << player->getNickname() << " used " << selectedMove->getName() << " and dealt " << damage << " damage! (ﾉ◕ヮ◕)ﾉ*:･ﾟ✧" << endl;
                    if (selectedMove->getEffect() != Status::NONE && 
                        (rand() % 100) < (selectedMove->getEffectChance() * 100)) {
                        opponent->applyStatus(selectedMove->getEffect());
                    }
                }
            } else {
                cout << "Can't use that move! (´；ω；｀)" << endl;
            }
        }
    }

    void opponentTurn() {
        cout << "\n=== " << opponent->getNickname() << "'s Turn ===" << endl;
        if ((rand() % 5) == 0 && opponent->getMoves().size() < 4) {
            opponent->protect();
            cout << opponent->getNickname() << " is protecting itself! 🛡️" << endl;
        } else {
            int moveIndex = rand() % opponent->getMoves().size();
            Move* selectedMove = opponent->getMoves()[moveIndex];
            
            if (selectedMove && selectedMove->use()) {
                int damage = calculateDamage(selectedMove, opponent, player);
                if (damage > 0) {
                    player->takeDamage(damage);
                    cout << opponent->getNickname() << " used " << selectedMove->getName() << " and dealt " << damage << " damage! (╥﹏╥)" << endl;
                    if (selectedMove->getEffect() != Status::NONE && 
                        (rand() % 100) < (selectedMove->getEffectChance() * 100)) {
                        player->applyStatus(selectedMove->getEffect());
                    }
                }
            } else {
                cout << opponent->getNickname() << " can't attack! (´• ω •｀)" << endl;
            }
        }
    }

    void clearInput() {
        cin.clear();
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
    }

public:
    Battle(Pokemon* p1, Pokemon* p2) : player(p1), opponent(p2), turnCount(1) {
        if (player->getSpeed() < opponent->getSpeed()) {
            swap(player, opponent);
        }
    }

    void start() {
        cout << "\n✨✨✨ BATTLE START! ✨✨✨" << endl;
        cout << player->getNickname() << " vs " << opponent->getNickname() << "! (ﾉ◕ヮ◕)ﾉ*:･ﾟ✧" << endl;

        while (!player->isFainted() && !opponent->isFainted()) {
            cout << "\n=== Turn " << turnCount << " ===" << endl;
            player->resetProtection();
            opponent->resetProtection();
            if (!player->isFainted() && player->canAttack()) {
                playerTurn();
            } else if (!player->canAttack()) {
                cout << player->getNickname() << " can't move! (≧﹏≦)" << endl;
            }
            
            if (opponent->isFainted()) break;
            if (!opponent->isFainted() && opponent->canAttack()) {
                opponentTurn();
            } else if (!opponent->canAttack()) {
                cout << opponent->getNickname() << " can't move! (≧﹏≦)" << endl;
            }
            player->applyStatusEffects();
            opponent->applyStatusEffects();
            
            turnCount++;
            cout << "\nPress Enter to continue...";
            clearInput();
            cin.get();
        }
        cout << "\n✨✨✨ BATTLE END! ✨✨✨" << endl;
        if (player->isFainted()) {
            cout << opponent->getNickname() << " wins! (ﾉ>ω<)ﾉ" << endl;
        } else {
            cout << player->getNickname() << " wins! ☆*:.｡.o(≧▽≦)o.｡.:*☆" << endl;
        }
    }
};

Pokemon* createPokemon(Type type, const string& name) {
    switch(type) {
        case Type::FIRE:
            return new Pokemon(name, "Charizard", Type::FIRE, 30, 120, 84, 78, 100);
        case Type::WATER:
            return new Pokemon(name, "Blastoise", Type::WATER, 30, 130, 83, 100, 78);
        case Type::GRASS:
            return new Pokemon(name, "Venusaur", Type::GRASS, 30, 125, 82, 83, 80);
        case Type::ELECTRIC:
            return new Pokemon(name, "Pikachu", Type::ELECTRIC, 30, 100, 55, 40, 90);
        case Type::GROUND:
            return new Pokemon(name, "Garchomp", Type::GROUND, 30, 135, 130, 95, 102);
        case Type::NORMAL:
        default:
            return new Pokemon(name, "Snorlax", Type::NORMAL, 30, 160, 110, 65, 30);
    }
}

void configurePokemon(Pokemon* pokemon) {
    switch(pokemon->getType()) {
        case Type::FIRE:
            pokemon->addMove(new Move("Flamethrower", Type::FIRE, 90, 85, 15, Status::BURNED, 0.1f));
            pokemon->addMove(new Move("Dragon Claw", Type::NORMAL, 80, 100, 15));
            pokemon->addMove(new Move("Air Slash", Type::NORMAL, 75, 95, 20));
            break;
        case Type::WATER:
            pokemon->addMove(new Move("Hydro Pump", Type::WATER, 110, 80, 5));
            pokemon->addMove(new Move("Ice Beam", Type::WATER, 90, 100, 10));
            pokemon->addMove(new Move("Aqua Tail", Type::WATER, 90, 90, 10));
            break;
        case Type::GRASS:
            pokemon->addMove(new Move("Solar Beam", Type::GRASS, 120, 100, 10));
            pokemon->addMove(new Move("Razor Leaf", Type::GRASS, 55, 95, 25));
            pokemon->addMove(new Move("Sleep Powder", Type::GRASS, 0, 75, 15, Status::PARALYZED, 1.0f));
            break;
        case Type::ELECTRIC:
            pokemon->addMove(new Move("Thunderbolt", Type::ELECTRIC, 90, 85, 15, Status::PARALYZED, 0.1f));
            pokemon->addMove(new Move("Quick Attack", Type::NORMAL, 40, 100, 30));
            pokemon->addMove(new Move("Thunder Wave", Type::ELECTRIC, 0, 90, 20, Status::PARALYZED, 1.0f));
            break;
        case Type::GROUND:
            pokemon->addMove(new Move("Earthquake", Type::GROUND, 100, 100, 10));
            pokemon->addMove(new Move("Dragon Rush", Type::NORMAL, 100, 75, 10));
            pokemon->addMove(new Move("Sand Attack", Type::GROUND, 0, 100, 15));
            break;
        case Type::NORMAL:
        default:
            pokemon->addMove(new Move("Body Slam", Type::NORMAL, 85, 100, 15));
            pokemon->addMove(new Move("Rest", Type::NORMAL, 0, 100, 10));
            pokemon->addMove(new Move("Hyper Beam", Type::NORMAL, 150, 90, 5));
            break;
    }
}

Pokemon* selectPlayerPokemon() {
    cout << "✨ Choose your Pokémon! ✨" << endl;
    cout << "0. Fire~ 🔥 (Charizard)" << endl;
    cout << "1. Water~ 💧 (Blastoise)" << endl;
    cout << "2. Grass~ 🌿 (Venusaur)" << endl;
    cout << "3. Electric~ ⚡ (Pikachu)" << endl;
    cout << "4. Ground~ 🌍 (Garchomp)" << endl;
    cout << "5. Normal~ (Snorlax)" << endl;
    
    int choice;
    while (true) {
        cout << "Enter your choice (0-5): ";
        cin >> choice;
        
        if (cin.fail() || choice < 0 || choice > 5) {
            cout << "Invalid choice! Please select a number from 0 to 5." << endl;
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            continue;
        }
        break;
    }
    
    string name;
    cout << "Give your companion a nickname: ";
    cin >> name;
    
    Type selectedType = static_cast<Type>(choice);
    Pokemon* playerPokemon = createPokemon(selectedType, name);
    configurePokemon(playerPokemon);
    
    return playerPokemon;
}

Pokemon* selectOpponentPokemon() {
    Type opponentType = static_cast<Type>(rand() % 6);
    const string opponentNames[] = {"Blaze", "Splash", "Leafy", "Zappy", "Rocky", "Normie"};
    
    Pokemon* opponent = createPokemon(opponentType, opponentNames[(int)opponentType]);
    configurePokemon(opponent);
    
    return opponent;
}

int main() {
    srand(time(0));
    
    cout << "🎀 Pokémon Battle System 🎀" << endl;
    cout << "------------------" << endl;
    
    Pokemon* player = selectPlayerPokemon();
    Pokemon* opponent = selectOpponentPokemon();
    
    Battle battle(player, opponent);
    battle.start();
    
    delete player;
    delete opponent;
    
    cout << "\nThanks for playing! (ﾉ´ヮ`)ﾉ*: ･ﾟ" << endl;
    return 0;
}
