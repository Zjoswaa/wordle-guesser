#include "App.h"

App::App() {
    this->initVariables();
    this->initWindow();
    if (this->initTextures() && this->initWordList()) {
        this->initSprites();
    }
}

App::~App() {
    delete this->window;
}

void App::update() {
    this->pollEvents();
    this->updateSelectedRowStatus();
//    for (int i = 0; i < squareCount; i++) {
//        std::cout << letterId[i] << " ";
//    }
//    std::cout << std::endl;
}

void App::render() {
    this->window->clear(sf::Color::White);
    this->drawSprites();
    this->window->display();
}

bool App::running() {
    return this->window->isOpen();
}

void App::pollEvents() {
    while (this->window->pollEvent(ev)) {
        switch (ev.type) {
            // X Button
            case sf::Event::Closed:
                this->window->close();
                break;

            // Mouse Pressed
            case sf::Event::MouseButtonPressed:
                if (sf::Mouse::isButtonPressed(sf::Mouse::Left)) {
                    int clicked = clickedSquare();
                    if (clicked != -1 && this->currentRow == (int)floor((double)clicked / 5) && this->letterId[clicked] != 0) {
                        int nextBg = currentSquareBackgrounds[clicked];
                        if (nextBg == 2) {
                            nextBg = 0;
                        } else {
                            nextBg++;
                        }
                        currentSquareBackgrounds[clicked] = nextBg;
                        backgroundSprites[clicked].setTexture(backgroundTextures[nextBg]);
                    }

                } else if (sf::Mouse::isButtonPressed(sf::Mouse::Right)) {

                }
                break;

            // Key Pressed
            case sf::Event::KeyPressed:
                switch (ev.key.code) {
                    case sf::Keyboard::Escape:
                        this->window->close();
                        break;

                    case sf::Keyboard::A:
                        insertLetter(1);
                        break;

                    case sf::Keyboard::B:
                        insertLetter(2);
                        break;

                    case sf::Keyboard::C:
                        insertLetter(3);
                        break;

                    case sf::Keyboard::D:
                        insertLetter(4);
                        break;

                    case sf::Keyboard::E:
                        insertLetter(5);
                        break;

                    case sf::Keyboard::F:
                        insertLetter(6);
                        break;

                    case sf::Keyboard::G:
                        insertLetter(7);
                        break;

                    case sf::Keyboard::H:
                        insertLetter(8);
                        break;

                    case sf::Keyboard::I:
                        insertLetter(9);
                        break;

                    case sf::Keyboard::J:
                        insertLetter(10);
                        break;

                    case sf::Keyboard::K:
                        insertLetter(11);
                        break;

                    case sf::Keyboard::L:
                        insertLetter(12);
                        break;

                    case sf::Keyboard::M:
                        insertLetter(13);
                        break;

                    case sf::Keyboard::N:
                        insertLetter(14);
                        break;

                    case sf::Keyboard::O:
                        insertLetter(15);
                        break;

                    case sf::Keyboard::P:
                        insertLetter(16);
                        break;

                    case sf::Keyboard::Q:
                        insertLetter(17);
                        break;

                    case sf::Keyboard::R:
                        insertLetter(18);
                        break;

                    case sf::Keyboard::S:
                        insertLetter(19);
                        break;

                    case sf::Keyboard::T:
                        insertLetter(20);
                        break;

                    case sf::Keyboard::U:
                        insertLetter(21);
                        break;

                    case sf::Keyboard::V:
                        insertLetter(22);
                        break;

                    case sf::Keyboard::W:
                        insertLetter(23);
                        break;

                    case sf::Keyboard::X:
                        insertLetter(24);
                        break;

                    case sf::Keyboard::Y:
                        insertLetter(25);
                        break;

                    case sf::Keyboard::Z:
                        insertLetter(26);
                        break;

                    case sf::Keyboard::BackSpace:
                        deleteLastLetter();
                        moveToPreviousLine();
                        break;

                    case sf::Keyboard::Enter:
                        confirmLines();
                        moveToNextLine();
                        break;

                    default:
                        break;
                }
            default:
                break;
        }
    }
}

void App::initVariables() {
    this->window = nullptr;

    std::vector<char> v;
    for (int i = 0; i < 5; i++) {
        v.clear();
        for (int j = 0; j < 26; j++) {
            v.push_back(alphabet[j + 1]);
        }
        possibleLetters[i] = v;
    }

    for (int i = 0; i < squareCount; i++) {
        this->currentSquareBackgrounds[i] = 0;
    }

    for (int i = 0 ; i < squareCount; i++) {
        this->letterId[i] = 0;
    }

    for (int i = 0; i < 6; i++) {
        enteredWords[i] = "     ";
    }

    this->currentRow = 0;

    this->nextSquare = 0;
}

bool App::initWordList() {
    std::ifstream input("../wordle-words.txt");
    std::string word;

    if (!input.is_open()) {
        std::cout << "Can't open word list file" << std::endl;
        return false;
    }

    std::cout << "Succesfully opened word list file" << std::endl;
    std::cout << "Starting reading of word list" << std::endl;

    while (!input.eof()) {
        input >> word;
        wordList.push_back(word);
    }

    std::cout << "Finished reading " << wordList.size() << " words" << std::endl;

    input.close();
    return true;
}

void App::initWindow() {
    this->window = new sf::RenderWindow(sf::VideoMode(windowWidth, windowHeight), "Wordle Guesser", sf::Style::Titlebar | sf::Style::Close);
    this->window->setFramerateLimit(fps);
}

bool App::initTextures() {
    if (!this->menuTexture.loadFromFile("../textures/wordle-menu.png")) {
        return false;
    } if (!this->letterTextures[0].loadFromFile("../textures/letters/empty.png")) {
        return false;
    } if (!this->letterTextures[1].loadFromFile("../textures/letters/a.png")) {
        return false;
    } if (!this->letterTextures[2].loadFromFile("../textures/letters/b.png")) {
        return false;
    } if (!this->letterTextures[3].loadFromFile("../textures/letters/c.png")) {
        return false;
    } if (!this->letterTextures[4].loadFromFile("../textures/letters/d.png")) {
        return false;
    } if (!this->letterTextures[5].loadFromFile("../textures/letters/e.png")) {
        return false;
    } if (!this->letterTextures[6].loadFromFile("../textures/letters/f.png")) {
        return false;
    } if (!this->letterTextures[7].loadFromFile("../textures/letters/g.png")) {
        return false;
    } if (!this->letterTextures[8].loadFromFile("../textures/letters/h.png")) {
        return false;
    } if (!this->letterTextures[9].loadFromFile("../textures/letters/i.png")) {
        return false;
    } if (!this->letterTextures[10].loadFromFile("../textures/letters/j.png")) {
        return false;
    } if (!this->letterTextures[11].loadFromFile("../textures/letters/k.png")) {
        return false;
    } if (!this->letterTextures[12].loadFromFile("../textures/letters/l.png")) {
        return false;
    } if (!this->letterTextures[13].loadFromFile("../textures/letters/m.png")) {
        return false;
    } if (!this->letterTextures[14].loadFromFile("../textures/letters/n.png")) {
        return false;
    } if (!this->letterTextures[15].loadFromFile("../textures/letters/o.png")) {
        return false;
    } if (!this->letterTextures[16].loadFromFile("../textures/letters/p.png")) {
        return false;
    } if (!this->letterTextures[17].loadFromFile("../textures/letters/q.png")) {
        return false;
    } if (!this->letterTextures[18].loadFromFile("../textures/letters/r.png")) {
        return false;
    } if (!this->letterTextures[19].loadFromFile("../textures/letters/s.png")) {
        return false;
    } if (!this->letterTextures[20].loadFromFile("../textures/letters/t.png")) {
        return false;
    } if (!this->letterTextures[21].loadFromFile("../textures/letters/u.png")) {
        return false;
    } if (!this->letterTextures[22].loadFromFile("../textures/letters/v.png")) {
        return false;
    } if (!this->letterTextures[23].loadFromFile("../textures/letters/w.png")) {
        return false;
    } if (!this->letterTextures[24].loadFromFile("../textures/letters/x.png")) {
        return false;
    } if (!this->letterTextures[25].loadFromFile("../textures/letters/y.png")) {
        return false;
    } if (!this->letterTextures[26].loadFromFile("../textures/letters/z.png")) {
        return false;
    } if (!this->backgroundTextures[0].loadFromFile("../textures/wordle-gray-bg.png")) {
        return false;
    } if (!this->backgroundTextures[1].loadFromFile("../textures/wordle-yellow-bg.png")) {
        return false;
    } if (!this->backgroundTextures[2].loadFromFile("../textures/wordle-green-bg.png")) {
        return false;
    } if (!this->selectedStatusTextures[0].loadFromFile("../textures/wordle-row-not-selected.png")) {
        return false;
    } if (!this->selectedStatusTextures[1].loadFromFile("../textures/wordle-row-selected.png")) {
        return false;
    }

    std::cout << "Succesfully loaded textures" << std::endl;
    return true;
}

void App::initSprites() {
    this->menuSprite.setTexture(menuTexture);

    for (int i = 0; i < squareCount; i++) {
        // Initialize all the squares to be the empty square
        this->letterSprites[i].setTexture(this->letterTextures[0]);
        // Initialize all the squares to have the gray background
        this->backgroundSprites[i].setTexture(this->backgroundTextures[this->currentSquareBackgrounds[i]]);
    }

    for (int i = 0; i < 6; i++) {
        this->rowSelectedStatus[i].setTexture(this->selectedStatusTextures[0]);
    }
    this->rowSelectedStatus[currentRow].setTexture(this->selectedStatusTextures[1]);

    for (int i = 0; i < 5; i++) {
        this->letterSprites[i].setPosition((float)(24 + (96 * i)), 24);
        this->backgroundSprites[i].setPosition((float)(32 + (96 * i)), 32);
    }
    for (int i = 0; i < 5; i++) {
        this->letterSprites[i+5].setPosition((float)(24 + (96 * i)), 120);
        this->backgroundSprites[i+5].setPosition((float)(32 + (96 * i)), 128);
    }
    for (int i = 0; i < 5; i++) {
        this->letterSprites[i+10].setPosition((float)(24 + (96 * i)), 216);
        this->backgroundSprites[i+10].setPosition((float)(32 + (96 * i)), 224);
    }
    for (int i = 0; i < 5; i++) {
        this->letterSprites[i+15].setPosition((float)(24 + (96 * i)), 312);
        this->backgroundSprites[i+15].setPosition((float)(32 + (96 * i)), 320);
    }
    for (int i = 0; i < 5; i++) {
        this->letterSprites[i+20].setPosition((float)(24 + (96 * i)), 408);
        this->backgroundSprites[i+20].setPosition((float)(32 + (96 * i)), 416);
    }
    for (int i = 0; i < 5; i++) {
        this->letterSprites[i+25].setPosition((float)(24 + (96 * i)), 504);
        this->backgroundSprites[i+25].setPosition((float)(32 + (96 * i)), 512);
    }

    for (int i = 0; i < 6; i++) {
        this->rowSelectedStatus[i].setPosition(504, (float)(24 + (96 * i)));
    }
}

void App::drawSprites() {
    this->window->draw(menuSprite);
    for (int i = 0; i < squareCount; i++) {
        this->window->draw(backgroundSprites[i]);
        this->window->draw(letterSprites[i]);
    }
    for (int i = 0; i < 6; i++) {
        this->window->draw(rowSelectedStatus[i]);
    }
}

int App::clickedSquare() {
    if (sf::Mouse::getPosition(*this->window).x >= 24 && sf::Mouse::getPosition(*this->window).x <= 111
    && sf::Mouse::getPosition(*this->window).y >= 24 && sf::Mouse::getPosition(*this->window).y <= 111) {
        return 0;
    } if (sf::Mouse::getPosition(*this->window).x >= 120 && sf::Mouse::getPosition(*this->window).x <= 207
    && sf::Mouse::getPosition(*this->window).y >= 24 && sf::Mouse::getPosition(*this->window).y <= 111) {
        return 1;
    } if (sf::Mouse::getPosition(*this->window).x >= 216 && sf::Mouse::getPosition(*this->window).x <= 303
        && sf::Mouse::getPosition(*this->window).y >= 24 && sf::Mouse::getPosition(*this->window).y <= 111) {
        return 2;
    } if (sf::Mouse::getPosition(*this->window).x >= 312 && sf::Mouse::getPosition(*this->window).x <= 399
        && sf::Mouse::getPosition(*this->window).y >= 24 && sf::Mouse::getPosition(*this->window).y <= 111) {
        return 3;
    } if (sf::Mouse::getPosition(*this->window).x >= 408 && sf::Mouse::getPosition(*this->window).x <= 495
        && sf::Mouse::getPosition(*this->window).y >= 24 && sf::Mouse::getPosition(*this->window).y <= 111) {
        return 4;
    } if (sf::Mouse::getPosition(*this->window).x >= 24 && sf::Mouse::getPosition(*this->window).x <= 111
        && sf::Mouse::getPosition(*this->window).y >= 120 && sf::Mouse::getPosition(*this->window).y <= 207) {
        return 5;
    } if (sf::Mouse::getPosition(*this->window).x >= 120 && sf::Mouse::getPosition(*this->window).x <= 207
        && sf::Mouse::getPosition(*this->window).y >= 120 && sf::Mouse::getPosition(*this->window).y <= 207) {
        return 6;
    } if (sf::Mouse::getPosition(*this->window).x >= 216 && sf::Mouse::getPosition(*this->window).x <= 303
        && sf::Mouse::getPosition(*this->window).y >= 120 && sf::Mouse::getPosition(*this->window).y <= 207) {
        return 7;
    } if (sf::Mouse::getPosition(*this->window).x >= 312 && sf::Mouse::getPosition(*this->window).x <= 399
        && sf::Mouse::getPosition(*this->window).y >= 120 && sf::Mouse::getPosition(*this->window).y <= 207) {
        return 8;
    } if (sf::Mouse::getPosition(*this->window).x >= 408 && sf::Mouse::getPosition(*this->window).x <= 495
        && sf::Mouse::getPosition(*this->window).y >= 120 && sf::Mouse::getPosition(*this->window).y <= 207) {
        return 9;
    } if (sf::Mouse::getPosition(*this->window).x >= 24 && sf::Mouse::getPosition(*this->window).x <= 111
        && sf::Mouse::getPosition(*this->window).y >= 216 && sf::Mouse::getPosition(*this->window).y <= 303) {
        return 10;
    } if (sf::Mouse::getPosition(*this->window).x >= 120 && sf::Mouse::getPosition(*this->window).x <= 207
        && sf::Mouse::getPosition(*this->window).y >= 216 && sf::Mouse::getPosition(*this->window).y <= 303) {
        return 11;
    } if (sf::Mouse::getPosition(*this->window).x >= 216 && sf::Mouse::getPosition(*this->window).x <= 303
        && sf::Mouse::getPosition(*this->window).y >= 216 && sf::Mouse::getPosition(*this->window).y <= 303) {
        return 12;
    } if (sf::Mouse::getPosition(*this->window).x >= 312 && sf::Mouse::getPosition(*this->window).x <= 399
        && sf::Mouse::getPosition(*this->window).y >= 216 && sf::Mouse::getPosition(*this->window).y <= 303) {
        return 13;
    } if (sf::Mouse::getPosition(*this->window).x >= 408 && sf::Mouse::getPosition(*this->window).x <= 495
        && sf::Mouse::getPosition(*this->window).y >= 216 && sf::Mouse::getPosition(*this->window).y <= 303) {
        return 14;
    } if (sf::Mouse::getPosition(*this->window).x >= 24 && sf::Mouse::getPosition(*this->window).x <= 111
        && sf::Mouse::getPosition(*this->window).y >= 312 && sf::Mouse::getPosition(*this->window).y <= 399) {
        return 15;
    } if (sf::Mouse::getPosition(*this->window).x >= 120 && sf::Mouse::getPosition(*this->window).x <= 207
        && sf::Mouse::getPosition(*this->window).y >= 312 && sf::Mouse::getPosition(*this->window).y <= 399) {
        return 16;
    } if (sf::Mouse::getPosition(*this->window).x >= 216 && sf::Mouse::getPosition(*this->window).x <= 303
        && sf::Mouse::getPosition(*this->window).y >= 312 && sf::Mouse::getPosition(*this->window).y <= 399) {
        return 17;
    } if (sf::Mouse::getPosition(*this->window).x >= 312 && sf::Mouse::getPosition(*this->window).x <= 399
        && sf::Mouse::getPosition(*this->window).y >= 312 && sf::Mouse::getPosition(*this->window).y <= 399) {
        return 18;
    } if (sf::Mouse::getPosition(*this->window).x >= 408 && sf::Mouse::getPosition(*this->window).x <= 495
        && sf::Mouse::getPosition(*this->window).y >= 312 && sf::Mouse::getPosition(*this->window).y <= 399) {
        return 19;
    } if (sf::Mouse::getPosition(*this->window).x >= 24 && sf::Mouse::getPosition(*this->window).x <= 111
        && sf::Mouse::getPosition(*this->window).y >= 408 && sf::Mouse::getPosition(*this->window).y <= 495) {
        return 20;
    } if (sf::Mouse::getPosition(*this->window).x >= 120 && sf::Mouse::getPosition(*this->window).x <= 207
        && sf::Mouse::getPosition(*this->window).y >= 408 && sf::Mouse::getPosition(*this->window).y <= 495) {
        return 21;
    } if (sf::Mouse::getPosition(*this->window).x >= 216 && sf::Mouse::getPosition(*this->window).x <= 303
        && sf::Mouse::getPosition(*this->window).y >= 408 && sf::Mouse::getPosition(*this->window).y <= 495) {
        return 22;
    } if (sf::Mouse::getPosition(*this->window).x >= 312 && sf::Mouse::getPosition(*this->window).x <= 399
        && sf::Mouse::getPosition(*this->window).y >= 408 && sf::Mouse::getPosition(*this->window).y <= 495) {
        return 23;
    } if (sf::Mouse::getPosition(*this->window).x >= 408 && sf::Mouse::getPosition(*this->window).x <= 495
        && sf::Mouse::getPosition(*this->window).y >= 408 && sf::Mouse::getPosition(*this->window).y <= 495) {
        return 24;
    } if (sf::Mouse::getPosition(*this->window).x >= 24 && sf::Mouse::getPosition(*this->window).x <= 111
        && sf::Mouse::getPosition(*this->window).y >= 504 && sf::Mouse::getPosition(*this->window).y <= 591) {
        return 25;
    } if (sf::Mouse::getPosition(*this->window).x >= 120 && sf::Mouse::getPosition(*this->window).x <= 207
        && sf::Mouse::getPosition(*this->window).y >= 504 && sf::Mouse::getPosition(*this->window).y <= 591) {
        return 26;
    } if (sf::Mouse::getPosition(*this->window).x >= 216 && sf::Mouse::getPosition(*this->window).x <= 303
        && sf::Mouse::getPosition(*this->window).y >= 504 && sf::Mouse::getPosition(*this->window).y <= 591) {
        return 27;
    } if (sf::Mouse::getPosition(*this->window).x >= 312 && sf::Mouse::getPosition(*this->window).x <= 399
        && sf::Mouse::getPosition(*this->window).y >= 504 && sf::Mouse::getPosition(*this->window).y <= 591) {
        return 28;
    } if (sf::Mouse::getPosition(*this->window).x >= 408 && sf::Mouse::getPosition(*this->window).x <= 495
        && sf::Mouse::getPosition(*this->window).y >= 504 && sf::Mouse::getPosition(*this->window).y <= 591) {
        return 29;
    } else {
        return -1;
    }
}

void App::insertLetter(int letter) {
    if (nextSquare < 5) {
        this->letterSprites[(5 * currentRow) + nextSquare].setTexture(letterTextures[letter]);
        this->letterId[(5*currentRow) + nextSquare] = letter;
        nextSquare = std::min(nextSquare + 1, 5);
//        std::cout << "Row: " << currentRow << std::endl;
//        std::cout << "Square: " << nextSquare << std::endl;
    }
}

void App::deleteLastLetter() {
    if (nextSquare > 0) {
        this->letterSprites[(5 * currentRow) + nextSquare - 1].setTexture(this->letterTextures[0]);
        this->backgroundSprites[(5 * currentRow) + nextSquare - 1].setTexture(this->backgroundTextures[0]);
        this->currentSquareBackgrounds[(5 * currentRow) + nextSquare - 1] = 0;
        this->letterId[(5 * currentRow) + nextSquare - 1] = 0;
        this->nextSquare = std::max(this->nextSquare - 1, 0);
//        std::cout << "Row: " << currentRow << std::endl;
//        std::cout << "Square: " << nextSquare << std::endl;
    }
}

void App::moveToNextLine() {
    if (currentRow < 5 && nextSquare == 5) {
        currentRow++;
        nextSquare = 0;
    }
}

void App::moveToPreviousLine() {
    if (currentRow > 0 && nextSquare == 0) {
        currentRow--;
        nextSquare = 5;
    }
}

void App::updateSelectedRowStatus() {
    for (int i = 0; i < 6; i++) {
        this->rowSelectedStatus[i].setTexture(selectedStatusTextures[0]);
    }
    this->rowSelectedStatus[currentRow].setTexture(selectedStatusTextures[1]);
}

void App::confirmLines() {
    if (currentRow < 6 && nextSquare == 5) {
        for (int i = 0; i < 6; i++) {
            for (int j = 0; j < 5; j++) {
                enteredWords[i][j] = alphabet[letterId[(5 * i) + j]];
            }
        }
        this->updatePossibleLetters();
        this->updatePossibleWords();

    }

    std::cout << "Possible words: " << possibleWords.size() << std::endl;
    for (long unsigned int i = 0; i < possibleWords.size(); i++) {
        std::cout << possibleWords[i] << std::endl;
    }
//
//    for (int i = 0; i < 5; i++) {
//        std::cout << "Letter " << i << ": ";
//        for (int j = 0; j < possibleLetters[i].size(); j++) {
//            std::cout << possibleLetters[i][j] << " ";
//        }
//        std::cout << std::endl;
//    }
//
//    std::cout << "Entered words:" << std::endl;
//    for (int i = 0; i < 6; i++) {
//        if (enteredWords[i] == "     ") {
//            std::cout << "-----" << std::endl;
//        } else {
//            std::cout << enteredWords[i] << std::endl;
//        }
//    }
}

void App::updatePossibleLetters() {
    // First add all letters back to all the possible letters
    std::vector<char> v;
    for (int i = 0; i < 5; i++) {
        v.clear();
        for (int j = 0; j < 26; j++) {
            v.push_back(alphabet[j + 1]);
        }
        possibleLetters[i] = v;
    }

    for (int i = 0; i < currentRow + 1; i++) {
        for (int j = 0; j < 5; j++) {
//            std::cout << letterId[(5 * i) + j] << " " << currentSquareBackgrounds[(5 * i) + j] << std::endl;
            // Gray square (letter is not in word)
            if (currentSquareBackgrounds[(5 * i) + j] == 0) {
                // Remove the letter in this square from the possible letters of every letter
                for (int k = 0; k < 5; k++) {
                    this->removeCharFromVector(possibleLetters[k], alphabet[letterId[(5 * i) + j]]);
                }
            }
            // Yellow square (letter is in word but not this position)
            else if (currentSquareBackgrounds[(5 * i) + j] == 1) {
                // Remove the letter in this square from the possible letters of this square
                this->removeCharFromVector(possibleLetters[j], alphabet[letterId[(5 * i) + j]]);
            }
            // Green square (letter is in this position)
            else if (currentSquareBackgrounds[(5 * i) + j] == 2) {
                // Remove every letter but the letter in this square from the possible letters
                possibleLetters[j].clear();
                possibleLetters[j].push_back(alphabet[letterId[(5 * i) + j]]);
            }
        }
    }
}

void App::updatePossibleWords() {
    possibleWords.clear();
    bool flag;
    // For every word in word list
    for (long unsigned int i = 0; i < wordList.size(); i++) {
        // Check if every letter in the word is in the possible letters for that position in the word
        flag = true;
        for (int j = 0; j < 5; j++) {
            // If no, don't check the rest of this word
            if (!charInVector(wordList[i][j], possibleLetters[j])) {
                flag = false;
            }
        }
        // If yes, add to possible words
        if (flag) {
            possibleWords.push_back(wordList[i]);
        }
    }
}

void App::removeCharFromVector(std::vector<char> &v, char c) {
    std::vector<char> temp;
    int counter = 0;
    for (long unsigned int i = 0; i < v.size(); i++) {
        temp.push_back(v[i]);
    }
    v.clear();

    for (long unsigned int i = 0; i < temp.size(); i++) {
        if (temp[i] != c) {
            v.push_back(temp[i]);
        } else {
            counter++;
        }
    }
}

bool App::charInVector(char c, std::vector<char> v) {
    for (long unsigned int i = 0; i < v.size(); i++) {
        if (v[i] == c) {
            return true;
        }
    }
    return false;
}