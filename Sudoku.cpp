#include "Sudoku.h"

/**************************************************************************
 * Class for solving a Sudoku puzzle by brute force.
 * Originally made for 9x9 board, separated into 9 3x3 non-overlapping boxes
 * ASSUMES
 *   Board class exists using vector< vector<int> > 
 * Author/copyright: Alyssa Shofner. All rights reserved.
 * Date: 12 August 2015
 *
**/

static const string TAG = "Sudoku: ";

/****************************************************************
 * Constructor.
**/
Sudoku::Sudoku()
{
}

/****************************************************************
 * Destructor.
**/
Sudoku::~Sudoku()
{
}

/****************************************************************
 * Accessors and mutators.
 * NONE, use toString to get Board and general functions to 
 *  manipulate
**/

/****************************************************************
 * General functions.
**/
/****************************************************************
 * General recursive function for adding to a board.
 * 
 * PARAMETERS
 *   int row - currRow in board
 *   int column - currColumn in board
 *   int depth - current depth in recursive call used purely for DEBUG
 *
 * OUTPUT
 *   returns ifCompletedBoardIsLegal
 *     -false means it cannot be solved
 * 
 * METHOD
 * Finds next DUMMY, if reaches end of the board with no DUMMY, 
 *                   return true for entire recursive call as 
 *                   legality is checked per step
 * With next DUMMY found, 
 *    -set DUMMY square with integer not originally used in the row 
 *        (the columns in the row beyond NINE+1)
 *    -check row, column, and box legality using set of Board::checkLegal()
 *        methods
 *        -if any return false, reset Square to DUMMY_VAR and 
 *           check ifAllUnusedInts have been tried
 *           -> if true, return false for this recursive call
 *           -> if false, try next unused int
 *        -if all return true, check recursive call
 *           -> if returns false, treat as if a checkLegal returned false
 *           -> if returns true, return true for entire recursive call
 *
 * VARIABLES
 *  -row - int currRow in board
 *  -column - int currColumn in board
 *  -depth - int current depth in recursive call used purely for DEBUG
 *  -unusedPosition - int of vector position that has not yet been used 
 *                    --make use add/remove with intCounter instead?
 *  -rowBox - int 0, 1, 2 gen from row % 3 to get the row 3x3 Box of square
 *  -colBox - int 0, 1, 2 gen from row % 3 to get the row 3x2 Box of square
**/
bool Sudoku::addSquare(int row, int column, int& depth)
{
 if(depth == 100)
 {
   cout<< "TOO LONG"<< endl;
   return true;
 }
 //Finding next 0 --> TODO:? do in my solve puzzle? reset otherwise....
  while(board.getSquare(row, column) != 0)
  {
   //checking that the end of the board has not been reached
    if(column == NINE)
    {
      if(row == NINE)
      {
        return true; //all have been passed, legality checked in adding
      }
      row++;
      column = 0;
    }
    column++; //reset to 0 makes this 1... 1 is not lost
  }
 
#ifdef EBUG
  cout<< "0 is at "<< row << " row and " << column << " column" << endl;
#endif 

  int unusedPosition = NINE+2;
  while(unusedPosition < board.getRowSize(row))
  {

   //set unused int in 0 square
    int unusedInt = board.getSquare(row, unusedPosition); 
    board.setSquare(row, column, unusedInt);

#ifdef EBUG
    cout<< "curr board" <<endl;
    cout<< board.toString() << endl;
#endif
   
   //finding 3x3 box of given square
    int rowBox = row % 3;
    int colBox = column % 3;

   //check legality of row
    if(board.isLegal(row, row, ONE, NINE)==true && 
       board.isLegal(ONE, NINE, column, column)==true &&
       board.isLegal(rowBox, colBox)==true )
    {

      //check if rest of the board can be filled legally
      depth++;
      if(addSquare(row, column, depth)==true)//call itself finds next 0
      {
        return true;
      }
      depth--;

    }

   //need to unset Square and redo
    board.unsetSquare(row, column);
    unusedPosition++;
  }
   
 //all options have been used, TODO: UNset square?
  return false;
} // bool Sudoku::addSquare(int& depth)

/****************************************************************
 * Function for reading the set up of the puzzle in from a file 
 *   including what numbers are not used in each line.
 *
 * ASSUMPTIONS
 *   that Board.cpp and Board.h have been included in makefile 
 *   that the only characters in the input file are white spaces, '.', and
 *     integers 1-9
 *   that white spaces separate the squares as opposed to tabs or commas
 *
 * METHOD
 * Adds bufferVector to board
 * Then reads in lines from Scanner passed by reference.
 * For each line in the Scanner, vector<int> aboutToAdd is created through
 *     -pushing DUMMY into at(0)
 *     -creating and initializing visitedVect<bool> to NINE+1 false 
 *     -creating and reading currLine through evaluating currChar at 
 *         currLine.at(position) via the following method:
 *         ->if currChar is ' ', increment position by 1, reassign currChar
 *         ->if currChar is '.', push DUMMY onto aboutToAdd
 *         ->else, currChar is assumed to be int, 
 *                 -currChar is parsed into currInt
 *                 -currInt is pushed into aboutToAdd
 *                 -visitedVect<bool>.at(currInt) is changed to true
 *         ->increment position by two and repeat until end of currLine
 *     -pushing DUMMY into aboutToAdd
 *     -pushing the indexes of all false bool in visitedVect<bool> to 
 *        aboutToAdd
 *     -add aboutToAdd to board
 *
 * VARIABLES:
 *   -bufferVect<int> - only at beginning
 *   -visitedVect<bool> - to document what integers have been marked
 *        ->at(0) through at(NINE) initiated to be false and when currInt is
 *                created, at(currInt) turns true 
 *   -aboutToAdd<int> - vector that is added to the board every Scanner line
 *        ->at(0) dummy variable is add
 *        ->at(1) through at(NINE) is either DUMMY or an int depending on 
 *                whether currChar is a '.' or not (then assumed to be int) 
 *        ->at(NINE+1) is DUMMY to separate puzzle from unused int
 *        ->at(NINE+2) and beyond is every int that has false in visitedVect
 *   -currLine - string that is each line of the Scanner
 *   -currChar - char read from currLine at(position) either ' ', '.', or 
 *               an int
 *   -currInt - integer parsed from currChar when currChar is not ' ' or '.'
 *   -int i and int j as counters inside of for loops
 *   -position - int position in currLine incremented by2 to skip spaces
 *  
**/
void Sudoku::readPuzzle(Scanner& inStream)
{
 //adding buffer vector to board row
  vector<int> bufferVect;
  board.addLine(bufferVect);

 //reading inputStream line by line
  while(inStream.hasNext()) 
  {
   //creating and initializing visitedVect
    vector<bool> visitedVect;
    for (int i = 0; i <= NINE; i++)
    {
      visitedVect.push_back(false);
    }

   //creating aboutToAdd vector and pushing back DUMMY
    vector<int> aboutToAdd;
    aboutToAdd.push_back(DUMMY);

   //creating, initializing, and reading currLine
    string currLine = "";
    currLine = inStream.nextLine();
    if(currLine!="")//for the lines between the Sudoku 3x3 boxes
    {
      int position = 0; 
      for(int j = 0; j<NINE; j++)
      {
        char currChar = currLine.at(position);

       //reinitilizing currChar if it is a space to account for 
        //the 2 empty spaces in between the Sudoku 3x3 boxes
        if(currChar==' ')
        {
          position+=1;
          currChar = currLine.at(position);
        }
      
       //adding DUMMY or adding the correct integer to aboutToAdd
       //NOTE: will NOT work for integers > 9; 
       //      if int > 9, check if c++ has standard std::string::split 
       //      using spaces, or implement from following url
       //      http://stackoverflow.com/questions/236129/split-a-string-in-c
        if (currChar == '.')
        {
          aboutToAdd.push_back( DUMMY );  
        }
        else 
        {
          int currInt = (int)currChar - 48; //the ASCII character DEPRECATED
                                           //with C11 in compiler, use stoi
          aboutToAdd.push_back( currInt );
         //marking visited
          visitedVect.at(currInt) = true;
        }
      position+=2;//ASSUMPTION
    }

    //separating ints in final puzzle vs ints unused
    aboutToAdd.push_back(DUMMY);

    //finding and adding integers not used in line and adding to aboutToAdd
     //using counter, not iter, so that index can be accessed easily without
     // address manipulation
    for(int i = 1; i <= NINE; i++)
    {
       if(visitedVect.at(i)==false)
       {
         aboutToAdd.push_back(i);
       }
    }

   //pushing about to add to the board
    this->board.addLine(aboutToAdd);
    }
  }
  return;
} // void Sudoku::readPuzzle(Scanner& inStream)

/****************************************************************
 * General function for solving the puzzle through selected brute force
 * Sets and starts addSquare, which is private recursive function 
 * 
 * ASSUMES
 *   row and column for addSquare are NOT passed by reference
 *   vector is buffered so that board.at(0).at(0) will always be DUMMY
**/
void Sudoku::solvePuzzle()
{
  cout<< "SOLVING" <<endl;
  int depth = 0;
  addSquare(1, 1, depth); //addSquare(row, column, &depth)
  return;
} // void Sudoku::solvePuzzle()

/****************************************************************
 * Usual 'toString' function.
 * This outputs a board display with a label.
 *
 * ASSUMES 
 *   board.toString() prints correctly
 *
 * PARAMETERS
 *   -string label - line that precludes the board printed by Board.toString
 * 
 * OUTPUTS - string
 *   paragraph of label followed by the board printed by Board::toString()
 *   see Board::toString() for example and specifics
**/
string Sudoku::toString(string label)
{
  return label + '\n' + board.toString();
} // string Sudoku::toString()

