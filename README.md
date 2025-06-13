# The Binding of Notissac

## About the Project

**The Binding of Notissac** is a hobby project, strongly inspired by *The Binding of Isaac*. It is developed in C++ using the SFML 3.0.0 library. The main focus is on practicing object-oriented programming concepts, especially **polymorphism**.

> ⚠️ Disclaimer: This project was created by highly unqualified individuals who take no responsibility for any brain damage caused while analyzing this divine, highly optimized, and absolutely flawless code with perfect memory management. Proceed at your own risk.

## Tools used

- **C++**
- **SFML 3.0.0**
- **God’s help** 

## How to Play

[Here](https://mega.nz/file/vwBxlZZC#fW8a1laHALsKUOsJyPNfB5chmsUNmIx2mOMNXm13uAk) is a precompiled `.exe` file that allows you to play the game right away — no installation or setup required.

## Compilation Guide

### 1. Open the project folder in your terminal

Make sure you are in the directory of the project.

### 2. Compile the source file:

### 1. Open the project folder in your terminal

Make sure you are in the root directory of the project.

### 2. Compile the source file:
```console
g++ -c main.cpp -I"./SFML-3.0.0/include"
```
### 3. Link the libraries:
```console
g++ main.o -o example_name -L"./SFML-3.0.0/lib" -lsfml-graphics -lsfml-window -lsfml-system -lsfml-network -lsfml-audio
```
### Notes:

- Replace `example_name` with the desired name for your executable.
- Make sure the path to SFML (`./SFML-3.0.0/`) is correct and matches your project structure. (it is included in the repository)
- On **Windows**, you may also need to copy `.dll` files from the SFML `bin` directory next to your executable. (it also is included)

## Assets

This project is strictly non-commercial and does not generate any financial profit. All assets used in the game come from the following sources:

- [Pixel RPG Free NPC by Snoblin](https://snoblin.itch.io/pixel-rpg-free-npc)
- [Dungeon Tileset II by 0x72](https://0x72.itch.io/dungeontileset-ii)
- [Eradication Wars Weapon Sprite Pack by Reactorcore](https://reactorcore.itch.io/eradication-wars-weapon-sprite-pack)
- [Sound effects from Pixabay](https://pixabay.com/sound-effects/)
