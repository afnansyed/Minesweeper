
//Reference for writing this file: Prof. Fox lecture "code examples with SFML part 1,2,3"

#pragma once
#include <SFML/Graphics.hpp>
#include <iostream>
#include <string>
#include <vector>
#include "TextureManager.h"
using namespace std;


class Tiles{
public:
    sf::Sprite hidden;
    sf::Sprite revealed;
    sf::Sprite flagged;
    sf::Sprite mine;
    sf::Sprite number;

    bool isHidden = true;
    bool isFlagged = false;
    bool isMine = false;
    bool isDebug = false;
    bool isNumber = false;
    bool flaggedCorrect = false;

    int numNeighborMines = 0;

    Tiles(const char* tileName);
    void SetPosition(float xPosition, float yPosition);

    void Draw(sf::RenderWindow& window);

    sf::FloatRect GetBounds();
    void Revealed(){
        if(isFlagged == false){
            isHidden = false;
        }
        if(isHidden == false){
            isHidden == false;
        }
        if(isDebug == true){
            isHidden ==false;
        }
    };
    void Flagged(){
        if(isHidden == true){
            isFlagged = !isFlagged;
        }

    };
    void Debugged(){
        if(isHidden == true){
            isDebug = !isDebug;
        }
    }

    void numCounter(){
        numNeighborMines++;
    };

    void neighborMines();



};