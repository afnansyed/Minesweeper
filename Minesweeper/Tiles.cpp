
//Reference for writing this file: Prof. Fox lecture "code examples with SFML part 1,2,3"

#include "Tiles.h"
#include "TextureManager.h"
using namespace std;

Tiles::Tiles(const char* tileName) {
    hidden.setTexture(TextureManager::GetTexture(tileName));
    revealed.setTexture(TextureManager::GetTexture("tile_revealed"));
    flagged.setTexture(TextureManager::GetTexture("flag"));
    mine.setTexture(TextureManager::GetTexture("mine"));

    isHidden = true;
    isFlagged = false;
    isMine = false;
    isDebug = false;
    isNumber = false;

    flaggedCorrect = false;
}

void Tiles::SetPosition(float xPosition, float yPosition) {
    hidden.setPosition(xPosition, yPosition);
    revealed.setPosition(xPosition, yPosition);
    flagged.setPosition(xPosition,yPosition);
    mine.setPosition(xPosition,yPosition);
    number.setPosition(xPosition,yPosition);
}

void Tiles::Draw(sf::RenderWindow &window) {
    if(isHidden){
        window.draw(hidden);
        if(isFlagged){
            window.draw(flagged);
        }
        if(isDebug && isMine){
            window.draw(mine);
        }
    }

    else{
        if(!isFlagged){
            window.draw(revealed);

        }
        if(isFlagged){
            window.draw(hidden);
        }
        if(isMine == true){
            window.draw(mine);
        }
        if(numNeighborMines > 0){
            window.draw(number);
        }
    }

}


sf::FloatRect Tiles::GetBounds() {
    return hidden.getGlobalBounds();
}

void Tiles::neighborMines() {
// reference for writing this function: T.A Alexis Daughtery
    if(numNeighborMines > 0){
        isNumber = true;
        number.setTexture(TextureManager::GetTexture("number_"+to_string(numNeighborMines)));
    }
}




