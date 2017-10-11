#include <iostream>
#include <queue>
#include <cstdlib>
#include <ctime>
#include <algorithm>
#include <vector>





using namespace std;

static const int rows = 3;
static const int columns = 3;
static const int arrayLength = 9;

class SliderPuzzle{

private:

    struct Tile {

        int tNumber;
        int tRow;
        int tColumn;


    };

    //tile array called puzzle


    //array to store the numbers as which they appear in the 2d array for easier visualization and comparison

public:

    bool areStatesEqual;
    //goalState constructor
    int storeArray[arrayLength];
    Tile* Puzzle[rows][columns];

    SliderPuzzle();
    //generated puzzle
    //SliderPuzzle(bool isNewState);

    //takes the tiles that can be affected by the movement of tile 0 so the search can generate the moves.
    //for initial state the most is possibly 2 on corner, 3 on edge, and 4 in middle
    //take the successors and create a new one based on tile0
    SliderPuzzle(int newArray[]);
    ~SliderPuzzle();
    int getTileRow(int thisTileRow);
    int getTileCol(int thisTileCol);
    bool checkIfTile0InCorner();
    bool checkIfTile0InMiddle();
    bool checkIfTile0InEdge();
    int heuristic(Tile tileArray[]);

    //create an generateStateFunction that that will generate 2


};//end class definition

//the no args constructor will generate the goal state
SliderPuzzle::SliderPuzzle(){


    int storeArray[arrayLength] = {1,2,3,4,5,6,7,8,0};
    int counter = 0;

    for(int i=0; i<rows; i++){

        for(int j=0; j<columns; j++){

            Puzzle[i][j] = new Tile;
            Puzzle[i][j]->tRow = i;
            Puzzle[i][j]->tColumn = j;
            Puzzle[i][j]->tNumber = storeArray[counter];

            //cout << "Row: " << Puzzle[i][j]->tRow << " Column: " << Puzzle[i][j]->tColumn << " tNumber: " << Puzzle[i][j]->tNumber <<  endl;
            counter++;
        }//end columns

    }//end for i

}//end no args constructor(goalstate)

/*
takes a newly generated array, which will come from one of the functions
depending on whether it is in the corner, middle, or edge which will create
a new array and given to this constructor to make it the new generated state
*/

SliderPuzzle::SliderPuzzle(int newArray[]){
     cout << "new puzzle created" << "\n" << endl;
    int counter = 0;

    for(int i=0; i<rows; i++){
        for(int j=0; j<columns; j++){

            Puzzle[i][j] = new Tile;
            Puzzle[i][j]->tRow = i;
            Puzzle[i][j]->tColumn = j;
            Puzzle[i][j]->tNumber = newArray[counter];

            storeArray[counter] = newArray[counter];

            cout << "Row: " << Puzzle[i][j]->tRow << " Column: " << Puzzle[i][j]->tColumn << " tNumber: " << Puzzle[i][j]->tNumber << "\n" <<  endl;

            counter++;

        }//end columns
    }//end rows

}//end overloaded constructor

SliderPuzzle::~SliderPuzzle(){

    cout << "farewell" << endl;

}//end deconstructor

int SliderPuzzle::getTileRow(int thisTileRow){

    for(int i=0; i<rows; i++){
        for(int j=0; j<columns; j++){
            if(Puzzle[i][j]->tNumber == thisTileRow){

                thisTileRow = Puzzle[i][j]->tRow;
                return thisTileRow;
                //cout << "in findtile0, row: " << tileRow << " column: " << tileCol << endl;
            }//end if
        }//end j for
    }//end i for


}//end find tile row

int SliderPuzzle::getTileCol(int thisTileCol){

    for(int i=0; i<rows; i++){
        for(int j=0; j<columns; j++){
            if(Puzzle[i][j]->tNumber == thisTileCol){

                thisTileCol = Puzzle[i][j]->tColumn;
                return thisTileCol;
                //cout << "in findtile0, row: " << tileRow << " column: " << tileCol << endl;
            }//end if
        }//end j for
    }//end i for
}//end find tile col

bool SliderPuzzle::checkIfTile0InCorner(){

    bool inCorner = false;
    int tile0 = 0;

    for(int i=0; i<rows; i++){
        for(int j=0; j<columns; j++){
            if(Puzzle[i][j]->tNumber == tile0){
                if(Puzzle[i][j]->tRow == 0 && Puzzle[i][j]->tColumn == 0){
                    inCorner = true;
                }//end top left corner
                if(Puzzle[i][j]->tRow == 0 && Puzzle[i][j]->tColumn == 2){
                    inCorner = true;
                }//end top right corner
                if(Puzzle[i][j]->tRow == 2 && Puzzle[i][j]->tColumn == 0){
                    inCorner = true;
                }//end bot left corner
                if(Puzzle[i][j]->tRow == 2 && Puzzle[i][j]->tColumn == 2){
                    inCorner = true;
                }//end bot right corner
            }//end find tile 0
        }//end for columns
    }//end for rows
    return inCorner;

}//end check if blank tile is in corner

bool checkIfSliderPuzzleInClosedList(SliderPuzzle newSP, vector<SliderPuzzle> closedList){

    bool isInClosedList = false;
    vector<SliderPuzzle>::iterator closedListIter;

    //cout << "is making into check if in closed list" << endl;

    for(closedListIter = closedList.begin(); closedListIter != closedList.end(); closedListIter++){
        for(int i=0; i<arrayLength; i++){
            if(newSP.storeArray[i] == closedListIter->storeArray[i]){
                //cout << "is making into if statement" << endl;
                //cout << "before true" << isInClosedList << endl;

                isInClosedList = true;

                return isInClosedList;

            }//end if
        }//end for for go through array
    }//end for iterator
}//end check in list


void moveIfTileInCorner(SliderPuzzle newSP, queue<SliderPuzzle> *spQ, vector<SliderPuzzle> *closedList, SliderPuzzle goalState){

    int moveHorizontally[arrayLength];
    int moveVertically[arrayLength];

    int temp1;
    int temp2;


    for(int i=0; i<arrayLength; i++){

        moveHorizontally[i] = newSP.storeArray[i];
        moveVertically[i] = newSP.storeArray[i];
        //cout << "saving array numbers: " << moveHorizontally[i] << endl;

    }//end save array to both arrays

    for(int i=0; i<rows; i++){
        for(int j=0; j<columns; j++){
            if(newSP.Puzzle[i][j]->tNumber == 0){

                //if tile 0 is first index of the array
                if(newSP.Puzzle[i][j]->tRow == 0 && newSP.Puzzle[i][j]->tColumn == 0){

                    temp1 = moveHorizontally[0];
                    moveHorizontally[0] = moveHorizontally[1];
                    moveHorizontally[1] = temp1;

                    temp2 = moveVertically[0];
                    moveVertically[0] = moveVertically[3];
                    moveVertically[3] = temp2;

                    SliderPuzzle newHSP = SliderPuzzle(&moveHorizontally[0]);
                    SliderPuzzle newVSP = SliderPuzzle(&moveVertically[0]);

                    if(checkIfSliderPuzzleInClosedList(newHSP, *closedList) != true){
                        spQ->push(newHSP);
                        closedList->push_back(newHSP);

                        for(int l=0; l<arrayLength; l++){
                            if(newHSP.storeArray[l] == goalState.storeArray[l]){
                                cout << "solution found by moving corner" << endl;
                            }//end if
                        }//end for
                    }//end if

                    if(checkIfSliderPuzzleInClosedList(newVSP, *closedList) != true){
                        spQ->push(newVSP);
                        closedList->push_back(newVSP);

                        for(int l=0; l<arrayLength; l++){
                            if(newVSP.storeArray[l] == goalState.storeArray[l]){
                                cout << "solution found by moving corner" << endl;
                            }//end if
                        }//end for
                    }//end if

                }//end top left corner
                if(newSP.Puzzle[i][j]->tRow == 0 && newSP.Puzzle[i][j]->tColumn == 2){

                    temp1 = moveHorizontally[2];
                    moveHorizontally[2] = moveHorizontally[1];
                    moveHorizontally[1] = temp1;

                    temp2 = moveVertically[2];
                    moveVertically[2] = moveVertically[5];
                    moveVertically[5] = temp2;

                    SliderPuzzle newHSP = SliderPuzzle(&moveHorizontally[0]);
                    SliderPuzzle newVSP = SliderPuzzle(&moveVertically[0]);

                    if(checkIfSliderPuzzleInClosedList(newHSP, *closedList) != true){
                        spQ->push(newHSP);
                        closedList->push_back(newHSP);

                        for(int l=0; l<arrayLength; l++){
                            if(newHSP.storeArray[l] == goalState.storeArray[l]){
                                cout << "solution found by moving corner" << endl;
                            }//end if
                        }//end for
                    }//end if

                    if(checkIfSliderPuzzleInClosedList(newVSP, *closedList) != true){
                        spQ->push(newVSP);
                        closedList->push_back(newVSP);

                        for(int l=0; l<arrayLength; l++){
                            if(newVSP.storeArray[l] == goalState.storeArray[l]){
                                cout << "solution found by moving corner" << endl;
                            }//end if
                        }//end for
                    }//end if;

                }//end top right corner
                if(newSP.Puzzle[i][j]->tRow == 2 && newSP.Puzzle[i][j]->tColumn == 0){

                    temp1 = moveHorizontally[6];
                    moveHorizontally[6] = moveHorizontally[7];
                    moveHorizontally[7] = temp1;

                    temp2 = moveVertically[6];
                    moveVertically[6] = moveVertically[3];
                    moveVertically[3] = temp2;

                    SliderPuzzle newHSP = SliderPuzzle(&moveHorizontally[0]);
                    SliderPuzzle newVSP = SliderPuzzle(&moveVertically[0]);

                    if(checkIfSliderPuzzleInClosedList(newHSP, *closedList) != true){
                        spQ->push(newHSP);
                        closedList->push_back(newHSP);

                        for(int l=0; l<arrayLength; l++){
                            if(newHSP.storeArray[l] == goalState.storeArray[l]){
                                cout << "solution found by moving corner" << endl;
                            }//end if
                        }//end for
                    }//end if

                    if(checkIfSliderPuzzleInClosedList(newVSP, *closedList) != true){
                        spQ->push(newVSP);
                        closedList->push_back(newVSP);

                        for(int l=0; l<arrayLength; l++){
                            if(newVSP.storeArray[l] == goalState.storeArray[l]){
                                cout << "solution found by moving corner" << endl;
                            }//end if
                        }//end for
                    }//end if

                }//end bot left corner
                if(newSP.Puzzle[i][j]->tRow == 2 && newSP.Puzzle[i][j]->tColumn == 2){

                    temp1 = moveHorizontally[8];
                    moveHorizontally[8] = moveHorizontally[7];
                    moveHorizontally[7] = temp1;

                    temp2 = moveVertically[8];
                    moveVertically[8] = moveVertically[5];
                    moveVertically[5] = temp2;

                    SliderPuzzle newHSP = SliderPuzzle(&moveHorizontally[0]);
                    SliderPuzzle newVSP = SliderPuzzle(&moveVertically[0]);

                    if(checkIfSliderPuzzleInClosedList(newHSP, *closedList) != true){
                        spQ->push(newHSP);
                        closedList->push_back(newHSP);

                        for(int l=0; l<arrayLength; l++){
                            if(newHSP.storeArray[l] == goalState.storeArray[l]){
                                cout << "solution found by moving corner" << endl;
                            }//end if
                        }//end for
                    }//end if

                    if(checkIfSliderPuzzleInClosedList(newHSP, *closedList) != true){
                        spQ->push(newHSP);
                        closedList->push_back(newHSP);

                        for(int l=0; l<arrayLength; l++){
                            if(newVSP.storeArray[l] == goalState.storeArray[l]){
                                cout << "solution found by moving corner" << endl;
                            }//end if
                        }//end for
                    }//end if
                }//end bot right corner
            }//end finding tile 0
        }//end columns
    }//end rows
}//end function

void moveIfTileInMiddle(SliderPuzzle newSP, queue<SliderPuzzle> *spQ, vector<SliderPuzzle> *closedList, SliderPuzzle goalState){
    int moveRight[arrayLength];
    int moveUp[arrayLength];
    int moveLeft[arrayLength];
    int moveDown[arrayLength];

    int temp1;

    for(int i=0; i<arrayLength; i++){

        moveRight[i] = newSP.storeArray[i];
        moveUp[i] = newSP.storeArray[i];
        moveLeft[i] = newSP.storeArray[i];
        moveDown[i] = newSP.storeArray[i];
        //cout << "saving array numbers: " << moveHorizontally[i] << endl;

    }//end save array to both arrays

    for(int i=0; i<rows; i++){
        for(int j=0; j<columns; j++){
            if(newSP.Puzzle[i][j]->tNumber == 0){
                if(newSP.Puzzle[i][j]->tRow == 1 && newSP.Puzzle[i][j]->tColumn == 1){

                    temp1 = moveRight[4];
                    moveRight[4] = moveRight[5];
                    moveRight[5] = temp1;

                    temp1 = moveLeft[4];
                    moveLeft[3] = moveLeft[4];
                    moveLeft[4] = temp1;

                    temp1 = moveUp[4];
                    moveUp[1] = moveUp[4];
                    moveUp[4] = temp1;

                    temp1 = moveDown[4];
                    moveDown[7] = moveDown[4];
                    moveDown[4] = temp1;

                    SliderPuzzle newRSP = SliderPuzzle(&moveRight[0]);
                    SliderPuzzle newLSP = SliderPuzzle(&moveLeft[0]);
                    SliderPuzzle newUSP = SliderPuzzle(&moveUp[0]);
                    SliderPuzzle newDSP = SliderPuzzle(&moveDown[0]);

                    if(checkIfSliderPuzzleInClosedList(newRSP, *closedList) != true){
                        spQ->push(newRSP);
                        closedList->push_back(newRSP);

                        for(int l=0; l<arrayLength; l++){
                            if(newRSP.storeArray[l] == goalState.storeArray[l]){
                                cout << "solution found by moving middle" << endl;
                            }//end if
                        }//end for
                    }

                    if(checkIfSliderPuzzleInClosedList(newLSP, *closedList) != true){
                        spQ->push(newLSP);
                        closedList->push_back(newLSP);

                        for(int l=0; l<arrayLength; l++){
                            if(newLSP.storeArray[l] == goalState.storeArray[l]){
                                cout << "solution found by moving middle" << endl;
                            }//end if
                        }//end for
                    }

                    if(checkIfSliderPuzzleInClosedList(newUSP, *closedList) != true){
                        spQ->push(newUSP);
                        closedList->push_back(newUSP);

                        for(int l=0; l<arrayLength; l++){
                            if(newUSP.storeArray[l] == goalState.storeArray[l]){
                                cout << "solution found by moving middle" << endl;
                            }//end if
                        }//end for
                    }

                    if(checkIfSliderPuzzleInClosedList(newDSP, *closedList) != true){
                        spQ->push(newDSP);
                        closedList->push_back(newDSP);

                        for(int l=0; l<arrayLength; l++){
                            if(newDSP.storeArray[l] == goalState.storeArray[l]){
                                cout << "solution found by moving middle" << endl;
                            }//end if
                        }//end for
                    }//end if
                }//end middle check
            }//end file tile 0
        }//end for columns
    }//end rows for
}//end move middle blank

void moveIfTileOnEdge(SliderPuzzle newSP, queue<SliderPuzzle> *spQ, vector<SliderPuzzle> *closedList, SliderPuzzle goalState){

    int moveLeft[arrayLength];
    int moveRight[arrayLength];
    int moveDown[arrayLength];
    int moveUp[arrayLength];

    int temp1;

    for(int i=0; i<arrayLength; i++){

        moveRight[i] = newSP.storeArray[i];
        moveUp[i] = newSP.storeArray[i];
        moveLeft[i] = newSP.storeArray[i];
        moveDown[i] = newSP.storeArray[i];
        //cout << "saving array numbers: " << moveHorizontally[i] << endl;

    }//end save array to both arrays

    for(int i=0; i<rows; i++){
        for(int j=0; j<columns; j++){
            if(newSP.Puzzle[i][j]->tNumber == 0){
                if(newSP.Puzzle[i][j]->tRow == 0 && newSP.Puzzle[i][j]->tColumn == 1){

                    temp1 = moveLeft[1];
                    moveLeft[1] = moveLeft[0];
                    moveLeft[0] = temp1;

                    temp1 = moveRight[1];
                    moveRight[1] = moveRight[2];
                    moveRight[2] = temp1;

                    temp1 = moveDown[1];
                    moveDown[1] = moveDown[4];
                    moveDown[4] = temp1;

                    SliderPuzzle newLSP = SliderPuzzle(&moveLeft[0]);
                    SliderPuzzle newRSP = SliderPuzzle(&moveRight[0]);
                    SliderPuzzle newDSP = SliderPuzzle(&moveDown[0]);

                    if(checkIfSliderPuzzleInClosedList(newLSP, *closedList) != true){
                        spQ->push(newLSP);
                        closedList->push_back(newLSP);

                        for(int l=0; l<arrayLength; l++){
                            if(newLSP.storeArray[l] == goalState.storeArray[l]){
                                cout << "solution found by moving edge" << endl;
                            }//end if
                        }//end for
                    }

                    if(checkIfSliderPuzzleInClosedList(newRSP, *closedList) != true){
                        spQ->push(newRSP);
                        closedList->push_back(newRSP);

                        for(int l=0; l<arrayLength; l++){
                            if(newRSP.storeArray[l] == goalState.storeArray[l]){
                                cout << "solution found by moving edge" << endl;
                            }//end if
                        }//end for
                    }

                    if(checkIfSliderPuzzleInClosedList(newDSP, *closedList) != true){
                        spQ->push(newDSP);
                        closedList->push_back(newDSP);

                        for(int l=0; l<arrayLength; l++){
                            if(newDSP.storeArray[l] == goalState.storeArray[l]){
                                cout << "solution found by moving edge" << endl;
                            }//end if
                        }//end for
                    }

                }//end top edge
                if(newSP.Puzzle[i][j]->tRow == 1 && newSP.Puzzle[i][j]->tColumn == 0){

                    temp1 = moveUp[3];
                    moveUp[3] = moveUp[0];
                    moveUp[0] = temp1;

                    temp1 = moveRight[3];
                    moveRight[3] = moveRight[4];
                    moveRight[4] = temp1;

                    temp1 = moveDown[3];
                    moveDown[3] = moveDown[6];
                    moveDown[6] = temp1;

                    SliderPuzzle newUSP = SliderPuzzle(&moveUp[0]);
                    SliderPuzzle newRSP = SliderPuzzle(&moveRight[0]);
                    SliderPuzzle newDSP = SliderPuzzle(&moveDown[0]);

                    if(checkIfSliderPuzzleInClosedList(newUSP, *closedList) != true){
                        spQ->push(newUSP);
                        closedList->push_back(newUSP);

                        for(int l=0; l<arrayLength; l++){
                            if(newUSP.storeArray[l] == goalState.storeArray[l]){
                                cout << "solution found by moving edge" << endl;
                            }//end if
                        }//end for
                    }

                    if(checkIfSliderPuzzleInClosedList(newRSP, *closedList) != true){
                        spQ->push(newRSP);
                        closedList->push_back(newRSP);

                        for(int l=0; l<arrayLength; l++){
                            if(newRSP.storeArray[l] == goalState.storeArray[l]){
                                cout << "solution found by moving edge" << endl;
                            }//end if
                        }//end for
                    }

                    if(checkIfSliderPuzzleInClosedList(newDSP, *closedList) != true){
                        spQ->push(newDSP);
                        closedList->push_back(newDSP);

                        for(int l=0; l<arrayLength; l++){
                            if(newDSP.storeArray[l] == goalState.storeArray[l]){
                                cout << "solution found by moving edge" << endl;
                            }//end if
                        }//end for
                    }

                }//end left edge
                if(newSP.Puzzle[i][j]->tRow == 1 && newSP.Puzzle[i][j]->tColumn == 2){

                    temp1 = moveUp[5];
                    moveUp[5] = moveUp[2];
                    moveUp[2] = temp1;


                    temp1 = moveLeft[5];
                    moveLeft[5] = moveLeft[4];
                    moveLeft[4] = temp1;

                    temp1 = moveDown[5];
                    moveDown[5] = moveDown[8];
                    moveDown[8] = temp1;

                    SliderPuzzle newUSP = SliderPuzzle(&moveUp[0]);
                    SliderPuzzle newLSP = SliderPuzzle(&moveLeft[0]);
                    SliderPuzzle newDSP = SliderPuzzle(&moveDown[0]);

                    if(checkIfSliderPuzzleInClosedList(newUSP, *closedList) != true){
                        spQ->push(newUSP);
                        closedList->push_back(newUSP);

                        for(int l=0; l<arrayLength; l++){
                            if(newUSP.storeArray[l] == goalState.storeArray[l]){
                                cout << "solution found by moving edge" << endl;
                            }//end if
                        }//end for
                    }

                    if(checkIfSliderPuzzleInClosedList(newLSP, *closedList) != true){
                        spQ->push(newLSP);
                        closedList->push_back(newLSP);

                        for(int l=0; l<arrayLength; l++){
                            if(newLSP.storeArray[l] == goalState.storeArray[l]){
                                cout << "solution found by moving edge" << endl;
                            }//end if
                        }//end for
                    }

                    if(checkIfSliderPuzzleInClosedList(newDSP, *closedList) != true){
                        spQ->push(newDSP);
                        closedList->push_back(newDSP);

                        for(int l=0; l<arrayLength; l++){
                            if(newDSP.storeArray[l] == goalState.storeArray[l]){
                                cout << "solution found by moving edge" << endl;
                            }//end if
                        }//end for
                    }

                }//end right edge
                if(newSP.Puzzle[i][j]->tRow == 2 && newSP.Puzzle[i][j]->tColumn == 1){

                    temp1 = moveLeft[7];
                    moveLeft[7] = moveLeft[6];
                    moveLeft[6] = temp1;

                    temp1 = moveUp[7];
                    moveUp[7] = moveUp[4];
                    moveUp[4] = temp1;

                    temp1 = moveRight[7];
                    moveRight[7] = moveRight[8];
                    moveRight[8] = temp1;

                    SliderPuzzle newLSP = SliderPuzzle(&moveLeft[0]);
                    SliderPuzzle newUSP = SliderPuzzle(&moveUp[0]);
                    SliderPuzzle newRSP = SliderPuzzle(&moveRight[0]);

                    if(checkIfSliderPuzzleInClosedList(newLSP, *closedList) != true){
                        spQ->push(newLSP);
                        closedList->push_back(newLSP);

                        for(int l=0; l<arrayLength; l++){
                            if(newLSP.storeArray[l] == goalState.storeArray[l]){
                                cout << "solution found by moving edge" << endl;
                            }//end if
                        }//end for
                    }

                    if(checkIfSliderPuzzleInClosedList(newUSP, *closedList) != true){
                        spQ->push(newUSP);
                        closedList->push_back(newUSP);

                        for(int l=0; l<arrayLength; l++){
                            if(newUSP.storeArray[l] == goalState.storeArray[l]){
                                cout << "solution found by moving edge" << endl;
                            }//end if
                        }//end for
                    }

                    if(checkIfSliderPuzzleInClosedList(newRSP, *closedList) != true){

                        spQ->push(newRSP);
                        closedList->push_back(newRSP);



                    }//end if in closed list
                }//end bottom edge
            }//end if to find tile 0
        }//end columns
    }//end rows
}//end move on tile

bool SliderPuzzle::checkIfTile0InMiddle(){

    bool inMiddle = false;
    int tile0 = 0;

    for(int i=0; i<rows; i++){
        for(int j=0; j<columns; j++){
            if(Puzzle[i][j]->tNumber == tile0){
                if(Puzzle[i][j]->tRow == 1 && Puzzle[i][j]->tColumn == 1){
                    inMiddle = true;
                }//end middle check
            }//end find tile 0
        }//end columns
    }//end rows
    return inMiddle;
}//end check if tile is in middle

bool SliderPuzzle::checkIfTile0InEdge(){

    bool onEdge = false;
    int tile0 = 0;

    for(int i=0; i<rows; i++){
        for(int j=0; j<columns; j++){
            if(Puzzle[i][j]->tNumber == tile0){
                if(Puzzle[i][j]->tRow == 0 && Puzzle[i][j]->tColumn == 1){
                    onEdge = true;
                }//end top edge
                if(Puzzle[i][j]->tRow == 1 && Puzzle[i][j]->tColumn == 0){
                    onEdge = true;
                }//end left edge
                if(Puzzle[i][j]->tRow == 1 && Puzzle[i][j]->tColumn == 2){
                    onEdge = true;
                }//end right edge
                if(Puzzle[i][j]->tRow == 2 && Puzzle[i][j]->tColumn == 1){
                    onEdge = true;
                }//end bottom edge
            }//end if to find tile 0
        }//end columns
    }//end rows
    return onEdge;
}//end check if tile is on edge<< "\n"

void breadthFirstSearch(SliderPuzzle goalSP, SliderPuzzle newSP, queue<SliderPuzzle> *spQ, vector<SliderPuzzle> *closedList){

    spQ->push(newSP);

    //CONSIDER WHILE QUEUE NOT EMPTY, IMPLIES THAT YOU ADD TO QUE UNTIL NEWSP == GOALSP
    while(!spQ->empty()){
        if(newSP.checkIfTile0InCorner() == true){

            moveIfTileInCorner(newSP, spQ, closedList, goalSP);
        }//end if in corner
        if(newSP.checkIfTile0InEdge() == true){

            moveIfTileOnEdge(newSP, spQ, closedList, goalSP);
        }//end if
        if(newSP.checkIfTile0InMiddle() == true){

            moveIfTileInMiddle(newSP, spQ, closedList, goalSP);
        }//end if
    }//end while loop
}//end breadth search

void aStarSearch(SliderPuzzle goalSP, SliderPuzzle newSP, queue<SliderPuzzle> *spQ, vector<SliderPuzzle> *closedList, int heuristicVal){

    /*
    take in heuristic val and perform search based on heuristic val

    */

}//end a star search

int main(){

    queue<SliderPuzzle> SPQueue;
    vector<int> randIntVector;
    vector<int>::iterator iter;
    vector<SliderPuzzle> closedSPVector;
    int randomArray[arrayLength];
    int randomArray1[arrayLength];
    int randomArray2[arrayLength];
    srand(time(NULL));

    for(int i=0; i<arrayLength; i++){

        randIntVector.push_back(i);
        randomArray[i] = randIntVector.at(i);

    }//end for

    for(int i=0; i<arrayLength; i++){

        randIntVector.push_back(i);
        randomArray1[i] = randIntVector.at(i);

    }//end for

    for(int i=0; i<arrayLength; i++){

        randIntVector.push_back(i);
        randomArray[i] = randIntVector.at(i);

    }//end for

    //built in function from the algorithm library
    random_shuffle(randIntVector.begin(), randIntVector.end());



    bool testInt = 0;

    cout << "SP GoalState: " << endl;
    SliderPuzzle GoalState;

    //cout << "SP1 ints: " << endl;
    SliderPuzzle SP1 = SliderPuzzle(randomArray);
    SliderPuzzle SP2 = SliderPuzzle(randomArray1);

    breadthFirstSearch(GoalState, SP1, &SPQueue, &closedSPVector);
    breadthFirstSearch(GoalState, SP2, &SPQueue, &closedSPVector);

}//end main
