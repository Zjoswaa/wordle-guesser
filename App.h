#ifndef APP_H
#define APP_H

#include <algorithm>
#include <cmath>
#include <fstream>
#include <iostream>
#include <SFML/Graphics.hpp>
#include <vector>
#include "constants.h"

class App {
public:
    App();
    ~App();

    void update();
    void render();
    bool running();

private:
    // The list of all possible wordle words
    std::vector<std::string> wordList;

    // The words that are possible solutions for the current entered words
    std::vector<std::string> possibleWords;

    // The possible letters of solution for each position
    std::vector<char> possibleLetters[5];

    // The background of each square (0 = gray, 1 = yellow, 2 = green)
    int currentSquareBackgrounds[squareCount];

    // The id of the letter of each square (0 = empty, 1 = A, 2 = B, etc.)
    int letterId[squareCount];

    // The words that are confirmed in the rows
    std::string enteredWords[6];

    // The current editable row
    int currentRow;

    // The square that will have the next typed letter
    int nextSquare;

    sf::RenderWindow* window;
    sf::Event ev;

    sf::Texture menuTexture;
    sf::Sprite menuSprite;

    sf::Texture letterTextures[alphabetSize];
    sf::Sprite letterSprites[squareCount];

    sf::Texture backgroundTextures[3];
    sf::Sprite backgroundSprites[squareCount];

    sf::Texture selectedStatusTextures[2];
    sf::Sprite rowSelectedStatus[6];

    void pollEvents();
    void initVariables();
    bool initWordList();
    void initWindow();
    bool initTextures();
    void initSprites();
    void drawSprites();

    // Returns which square was clicked, if none, returns -1
    int clickedSquare();

    // Inserts a letter in the next free spot
    void insertLetter(int letter);

    // Deletes the last added letter
    void deleteLastLetter();

    // Move the selected line forward
    void moveToNextLine();

    // Move the selected line backwards
    void moveToPreviousLine();

    // Update the selected row indicator
    void updateSelectedRowStatus();

    // Confirm the entered lines
    void confirmLines();

    // Update the possible letters in each position based on the currently entered words
    void updatePossibleLetters();

    // Update the possible words for the solution based on the possible letters
    void updatePossibleWords();

    // Removes the character c from the vector if it is in it (ifitis innit bruv)
    void removeCharFromVector(std::vector<char> &v, char c);

    // Returns whether the c is in vector v
    bool charInVector(char c, std::vector<char> v);
};

#endif
