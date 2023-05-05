
//Reference for writing this file: Prof. Fox lecture "code examples with SFML part 1,2,3"

#include <SFML/Graphics.hpp>
#include <fstream>
#include <sstream>
#include <iostream>
#include <string>
#include <vector>
#include <iomanip>

#include "Tiles.h"
#include "Random.h"

using namespace std;

int readFile( string file, vector<Tiles>& tiles, int mineCount);
void mineCreator(vector<Tiles>& tiles, int mineCount, int numTiles);
void reset(vector<Tiles>& tiles);
void numbers(vector<Tiles>& tiles, int c, int tilesNum);
void surrEmpty(vector<Tiles>& tiles, int c, int i, bool stop);

int main()
{
    //read file in;  Reference: prof. Fox lecture "reading simple data w/ ifstream"
    vector<int> values;
    ifstream fileName("boards/config.cfg");
    int value;
    while(fileName >> value){
        values.push_back(value);
    }
    fileName.close();

    int numCols = values.at(0);
    int numRows = values.at(1);

    int totMines = values.at(2);
    int mineCount = totMines;
    int tileCount = numRows*numCols;

    int w = numCols*32;
    int h = (numRows*32)+88;

    //reference: lab 8
    int first = mineCount % 10;   //third digit
    int second = (mineCount /10) % 10;   //second digit
    int third = (mineCount/100) % 10;    //first digit


    int numEmptyTiles = tileCount - mineCount;   //number of empty tiles


    sf::RenderWindow window(sf::VideoMode(w, h), "Minesweeper");

    Tiles tileHidden("tile_hidden");
    vector<Tiles> tiles;    //vectore for tiles

    //set position for tiles; Reference: T.A Alexis Daughtery
    for(int i = 0; i< numRows; i++){
        for(int j = 0; j< numCols; j++){
            tileHidden.SetPosition(j*32, i*32);
            tiles.push_back(tileHidden);

        }
    }

    mineCreator(tiles, mineCount, tileCount);   //set position for mines

    int flagCounter = mineCount;
    bool loose = false;
    int correct = 0;

    numbers(tiles, numCols, tileCount);   //set numbers for tiles neighboring a mine



    //load in spirits and set position,  Reference: Prof. Fox lecture "code examples with SFML part 1,2,3"
    sf::Sprite smileySprite(TextureManager::GetTexture("face_happy"));
    smileySprite.setPosition(((numCols/2)*64)/2,(numRows*64)/2);

    sf::Sprite debugSprite(TextureManager::GetTexture("debug"));
    debugSprite.setPosition(((numCols-8)*64)/2,(numRows*64)/2);

    sf::Sprite test1Sprite(TextureManager::GetTexture("test_1"));
    test1Sprite.setPosition(((numCols-6)*64)/2,(numRows*64)/2);

    sf::Sprite test2Sprite(TextureManager::GetTexture("test_2"));
    test2Sprite.setPosition(((numCols-4)*64)/2,(numRows*64)/2);

    sf::Sprite test3Sprite(TextureManager::GetTexture("test_3"));
    test3Sprite.setPosition(((numCols-2)*64)/2,(numRows*64)/2);




    sf::Sprite deadSprite(TextureManager::GetTexture("face_lose"));
    deadSprite.setPosition(((numCols/2)*64)/2,(numRows*64)/2);



    while (window.isOpen()){
        sf::Event event;
        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed) {
                window.close();
            }
            if(event.type == sf::Event::MouseButtonPressed){
                if(event.mouseButton.button == sf::Mouse::Left){
                    sf::Vector2f mousePosition (sf::Mouse::getPosition(window).x,sf::Mouse::getPosition(window).y);

                    //click on a tiles
                        if(loose == false && correct != numEmptyTiles){
                            for(unsigned int i =0; i< tiles.size(); i++){
                                if(tiles[i].GetBounds().contains(mousePosition) ){

                                    if(tiles[i].isMine == true && tiles[i].isFlagged == false){  //if mine
                                        loose = true;   //loose game
                                    }
                                    else{
                                        bool stop = false;
                                        tiles[i].Revealed();   //reveal tile
                                        if(tiles[i].isFlagged == false){   //if it is not flagged
                                            if(tiles[i].isNumber == false){   //if it is not a number
                                                surrEmpty(tiles, numCols, i, stop);   //reveal surrounding tiles
                                            }
                                        }

                                    }
                                }
                                if(debugSprite.getGlobalBounds().contains(mousePosition)){   //click on debug button
                                    if(tiles[i].isMine ){  //reveal mines
                                        tiles[i].isHidden = true;
                                        tiles[i].Debugged();
                                    }

                                }

                            }


                        }


                        //click on test 1
                    if(test1Sprite.getGlobalBounds().contains(mousePosition)){
                        //reset all variables
                        loose = false;
                        correct = 0;
                        reset(tiles);
                        string file = "boards/testboard1.brd";
                        mineCount = readFile(file, tiles, mineCount);   //read in file, return mine count
                        flagCounter = mineCount;
                        numEmptyTiles = tileCount - flagCounter;   //number of empty tiles

                        //set counter values
                        first = flagCounter % 10;
                        second = (flagCounter /10) % 10;
                        third = (flagCounter/100) % 10;
                        numbers(tiles, numCols, tileCount);  //set numbers for tiles surrounding a mine
                    }
                    if(test2Sprite.getGlobalBounds().contains(mousePosition)){
                        //reset all variables
                        loose = false;
                        correct = 0;
                        reset(tiles);
                        string file = "boards/testboard2.brd";
                        mineCount = readFile(file, tiles, mineCount); //read in file, return mine count
                        flagCounter = mineCount;
                        numEmptyTiles = tileCount - flagCounter; //number of empty tiles

                        //set counter values
                        first = flagCounter % 10;
                        second = (flagCounter /10) % 10;
                        third = (flagCounter/100) % 10;
                        numbers(tiles, numCols, tileCount); //set numbers for tiles surrounding a mine
                    }
                    if(test3Sprite.getGlobalBounds().contains(mousePosition)){
                        //reset all variables
                        loose = false;
                        correct = 0;
                        reset(tiles);
                        string file = "boards/testboard3.brd";
                        mineCount = readFile(file, tiles, mineCount); //read in file, return mine count
                        flagCounter = mineCount;
                        numEmptyTiles = tileCount - flagCounter; //number of empty tiles

                        //set counter values
                        first = flagCounter % 10;
                        second = (flagCounter /10) % 10;
                        third = (flagCounter/100) % 10;
                        numbers(tiles, numCols, tileCount); //set numbers for tiles surrounding a mine

                    }
                    if(smileySprite.getGlobalBounds().contains(mousePosition)){
                        //reset all variables
                            loose = false;
                            correct = 0;
                            reset(tiles);
                            mineCount = totMines;
                            mineCreator(tiles, mineCount, tileCount);  //create new position for mines
                            numbers(tiles, numCols, tileCount);  //set numbers for tiles surrounding a mine
                            flagCounter = mineCount;
                            numEmptyTiles = tileCount - flagCounter;  //number of empty tiles

                        //set counter values
                            first = flagCounter % 10;
                            second = (flagCounter /10) % 10;
                            third = (flagCounter/100) % 10;
                    }

                }

                if(event.mouseButton.button == sf::Mouse::Right){
                    sf::Vector2f mousePosition (sf::Mouse::getPosition(window).x,sf::Mouse::getPosition(window).y);
                    if(loose == false && correct != numEmptyTiles){
                        for(unsigned int i =0; i< tiles.size(); i++){
                            if(tiles[i].GetBounds().contains(mousePosition)){

                                //set counter value
                                if(tiles[i].isHidden == true){
                                        if(tiles[i].isFlagged == true){   //when removing a flag
                                            flagCounter = flagCounter +1;
                                            if(flagCounter < 0){
                                                first = (flagCounter*(-1)) % 10;
                                                second = ((flagCounter*(-1)) /10) % 10;
                                                third = ((flagCounter*(-1))/100) % 10;
                                            }
                                            else{
                                                first = flagCounter % 10;
                                                second = (flagCounter /10) % 10;
                                                third = (flagCounter/100) % 10;
                                            }

                                        }
                                        else {   //when adding a flag
                                            flagCounter = flagCounter - 1;
                                            if (flagCounter < 0) {
                                                first = (flagCounter * (-1)) % 10;
                                                second = ((flagCounter * (-1)) / 10) % 10;
                                                third = ((flagCounter * (-1)) / 100) % 10;
                                            } else {
                                                first = flagCounter % 10;
                                                second = (flagCounter / 10) % 10;
                                                third = (flagCounter / 100) % 10;
                                            }
                                        }


                                }
                                tiles[i].Flagged();  //tile is flagged

                            }


                        }


                    }
                }

            }
        }






        //if game lose
        if(loose == true){
            for(int i = 0; i< tiles.size(); i++){
                tiles[i].isDebug = true;  //reveal mines
            }


        }

        //when empty tiles are not fully revealed
        if(correct < numEmptyTiles){
            correct = 0;
            for(int i = 0; i < tiles.size(); i++){

                if(tiles[i].isMine == false){
                    if(tiles[i].isHidden == false){
                        correct++;   //add number of current tiles revealed that are not mines
                    }

                }
            }
        }


        //when all the tiles are revealed
        if(correct == numEmptyTiles){

            for(int i = 0; i< tiles.size(); i++){
                if(tiles[i].isMine == true){

                    tiles[i].isFlagged = true;  //flag all mines
                }

            }
            //reset counter to zero
            first = 0;
            second = 0;
            third = 0;

        }






        //load and set position for win
        sf::Sprite winSprite(TextureManager::GetTexture("face_win"));
        winSprite.setPosition(((numCols/2)*64)/2,(numRows*64)/2);



        //negative sign, if flagcounter is negative
        sf::Texture counter;
        if(flagCounter < 0){
            counter.loadFromFile("images/digits.png", sf::IntRect(210, 2, 21, 32));
        }
        sf::Sprite counterSprite(counter);
        counterSprite.setPosition(0,(numRows*64)/2);


        //load and set position for counters
        sf::Texture counter3;
        counter3.loadFromFile("images/digits.png", sf::IntRect(0+(21*third), 2, 21, 32));
        sf::Sprite counter3Sprite(counter3);
        counter3Sprite.setPosition(21,(numRows*64)/2);


        sf::Texture counter2;
        counter2.loadFromFile("images/digits.png", sf::IntRect(0+(21*first), 2, 21, 32));
        sf::Sprite counter2Sprite(counter2);
        counter2Sprite.setPosition(63,(numRows*64)/2);

        sf::Texture counter1;
        counter1.loadFromFile("images/digits.png", sf::IntRect(0+(21*second), 2, 21, 32));
        sf::Sprite counter1Sprite(counter1);
        counter1Sprite.setPosition(42,(numRows*64)/2);





        window.clear();

        //draw all the tiles,  Reference: T.A Alexis Daugthery and Prof. Fox lecture "code examples with SFML part 1,2,3"
        for(int i =0; i<tiles.size(); i++){
            tiles[i].Draw(window);
        }

        //draw smiley face
        if(loose == false && correct != numEmptyTiles){
            window.draw(smileySprite);
        }
        //draw other buttons
        window.draw(debugSprite);
        window.draw(test1Sprite);
        window.draw(test2Sprite);
        window.draw(test3Sprite);

        //draw counter
        window.draw(counterSprite);
        window.draw(counter1Sprite);
        window.draw(counter2Sprite);
        window.draw(counter3Sprite);

        //game lost, draw dead face
        if(loose == true){
            window.draw(deadSprite);
        }

        //game won, draw sunglasses face
        if(correct == numEmptyTiles){
            window.draw(winSprite);
        }


        window.display();
    }

    return 0;
}


//reset function for all the tiles
void reset(vector<Tiles>& tiles){
    for(int i = 0; i < tiles.size(); i++){
        tiles[i].isHidden = true;
        tiles[i].isFlagged = false;
        tiles[i].isMine = false;
        tiles[i].isDebug = false;
        tiles[i].numNeighborMines = 0;
        tiles[i].isNumber = false;
    }
}

//set position for all the mines
void mineCreator(vector<Tiles>& tiles, int mineCount, int numTiles){
    //reference for writing this function: lab 7
    int j = 0;
    for(int i = 0; i < mineCount; i++){
            int position = Random::Int(0, numTiles);
            if (tiles[position].isMine == false) {
                tiles[position].isMine = true;
                j++;
        }
    }
    //get position for mines again if a position came up more than once
    while(mineCount - j != 0){
        int position = Random::Int(0, numTiles);
        if (tiles[position].isMine == false) {
            tiles[position].isMine = true;
            j++;
        }
    }

}

//read file
int readFile(string file, vector<Tiles>& tiles, int mineCount){
    //reference for writing this function: Prof. fox, reading simple data during ifstream lecture & lab 4,5,7
    //T.A Alexis Daugthery
    ifstream inFile(file);
    //if file is open
    mineCount = 0;
    char value;
    int i =0;
    if (inFile.is_open()) {
        while(inFile >> value){
                if(value == '1'){  //one = mine
                    tiles[i].isMine = true;  //set mine position
                    mineCount++;
                }
                i++;
        }
    }
    inFile.close();
    return mineCount;
}


//set numbers for tiles neighboring  a mine
void numbers(vector<Tiles>& tiles, int c, int tilesNum){


    for(int i = 0; i< tiles.size(); i++){
        if(tiles[i].isMine){  //if mine

            if((i+1) % c != 0){
                tiles[i+1].numNeighborMines++;  //right
            }

            tiles[i + c].numNeighborMines++; //bottom


            if(i-1 >=0 && (i % c != 0) ){
                tiles[i-1].numNeighborMines++;  //left
            }
            if(i-c >= 0 ){
                tiles[i-c].numNeighborMines++;  //top

            }
            if(i-c-1 >= 0 && (i % c != 0)  ){
                tiles[i-c-1].numNeighborMines++;  //top-left
            }
            if(i-c+1 >= 0 && ((i+1)%c !=0)){
                tiles[i-c+1].numNeighborMines++;  //top-right

            }
            if((i+1) % c != 0){
                tiles[i+c+1].numNeighborMines++;  //bottom-right
            }
            if(i% c !=0){
                tiles[i+c-1].numNeighborMines++;  //bottom-left

            }
            tiles[i].isNumber = true;

        }
    }


    for(int i = 0; i<tiles.size(); i++){
        tiles[i].neighborMines();
    }
}



//reveal surrounding empty mines
void surrEmpty(vector<Tiles>& tiles, int c, int i, bool stop){

    //if tile is a mine or is a number
    if(tiles[i].isMine && tiles[i].isNumber == true){
        !stop;
    }
    else{
        if((i+1) % c != 0){
            if(tiles[i+1].isMine == false && (i+1)< tiles.size() && tiles[i+1].isHidden == true)  {
                tiles[i+1].Revealed();  //right
                if(tiles[i+1].isNumber == false && tiles[i+1].isFlagged == false){
                    surrEmpty(tiles, c, i+1, stop);
                }
            }
        }


        if(tiles[i + (c)].isMine == false  && (i+(c))< tiles.size() && tiles[i+(c)].isHidden == true){
            tiles[i + (c)].Revealed();  //bottom
            if(tiles[i+c].isNumber == false && tiles[i+c].isFlagged == false){
                surrEmpty(tiles, c, i+c, stop);
            }


        }

        if(i-1 >=0 && (i % c != 0) ){
            if(tiles[i-1].isMine == false && (i-1) >= 0  && tiles[i-1].isHidden == true){
                tiles[i-1].Revealed(); //left
                if(tiles[i-1].isNumber == false && tiles[i-1].isFlagged == false){
                    surrEmpty(tiles, c, i-1, stop);
                }

            }
        }

        if(i-c >= 0 ){
            if(tiles[i-(c)].isMine == false && (i-c)>= 0  && tiles[i-c].isHidden == true){
                tiles[i-(c)].Revealed();  //top
                if(tiles[i-c].isNumber == false && tiles[i-c].isFlagged == false){
                    surrEmpty(tiles, c, i-c, stop);
                }

            }
        }

        if(i-c-1 >= 0 && (i % c != 0)  ){
            if(tiles[i-(c)-1].isMine == false && (i-c-1) >= 0  && tiles[i-c-1].isHidden == true){
                tiles[i-(c)-1].Revealed();  //top-left
                if(tiles[i-c-1].isNumber == false && tiles[i-c-1].isFlagged == false){
                    surrEmpty(tiles, c, i-c-1, stop);
                }
            }
        }

        if(i-c+1 >= 0 && ((i+1)%c !=0)){
            if(tiles[i-(c)+1].isMine  == false && (i-c+1) >= 0  && tiles[i-c+1].isHidden == true){
                tiles[i-(c)+1].Revealed();  //top-right
                if(tiles[i-c+1].isNumber == false && tiles[i-c+1].isFlagged == false){
                    surrEmpty(tiles, c, i-c+1, stop);
                }
            }

        }

        if((i+1) % c != 0){
            if(tiles[i+(c)+1].isMine  == false && (i+c+1)< tiles.size() && tiles[i+c+1].isHidden == true){
                tiles[i+(c)+1].Revealed();  //bottom-right
                if(tiles[i+c+1].isNumber == false && tiles[i+c+1].isFlagged == false){
                    surrEmpty(tiles, c, i+c+1, stop);
                }
            }
        }

        if(i% c !=0){
            if(tiles[i+(c)-1].isMine  == false && (i+c-1)< tiles.size() && tiles[i+c-1].isHidden == true){
                tiles[i+(c)-1].Revealed();  //bottom-right
                if(tiles[i+c-1].isNumber == false && tiles[i+c-1].isFlagged == false){
                    surrEmpty(tiles, c, i+c-1, stop);
                }
            }

        }

    }

}
