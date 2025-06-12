# 🗡️ Dungeon Duel — Console RPG Battle Game

A simple C++ console RPG game created as a practice project to reinforce object-oriented programming, STL usage, and basic game logic implementation. The player fights through 10 consecutive rooms, each containing a new enemy, using turn-based combat mechanics and class-based bonuses.

## 🎮 Gameplay Overview

- Choose your class: **Assassin**, **Warrior**, or **Berserk**
- Fight through **10 rooms** filled with unique enemies
- Each battle is turn-based: 
  - Choose where to **attack**: `head`, `body`, or `legs`
  - Choose what to **block**: `head`, `body`, or `legs`
- Enemies randomly select attack/block areas
- If your health drops to 0 — you lose and can restart

## 🧙‍♂️ Player Classes

| Class     | Health | Damage | Special Ability |
|-----------|--------|--------|------------------|
| Assassin  | 250    | 12     | Chance to deal double damage |
| Warrior   | 400    | 10     | Chance to reduce incoming damage |
| Berserk   | 300    | 2      | Deals more damage the less HP you have |

## 🧟 Enemies

Each room has a stronger enemy:
- Skeleton, Orc Warrior, Shadow Assassin, Elder Dread Dragon and more
- Enemies vary in health and damage

## ⚔️ Combat System

- If the enemy blocks your attack, no damage is dealt
- If you block the enemy's attack — you receive no damage
- Class bonuses apply automatically during battle

## 🛠️ Technologies Used

- **C++**
- **STL containers**: `std::vector`, `std::map`
- **Random number generation**
- **Structured OOP design**

## 📁 File Structure

- `main.cpp` — entire project in one file for clarity
- Game is run directly from `main()`
