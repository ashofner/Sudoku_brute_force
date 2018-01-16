#include "Board.h"

/******************************************************************
 * Class for setting a Sudoku board, read and parsed via Sudoku.cpp
 * The board is vector of vector<int>. Each vector <int> contains... 
 *    -at(0) - DUMMY int, originally 0
 *    -at(1) through at(NINE) - either a DUMMY int or ONE through NINE int
 *    -at(NINE+1) - DUMMY int
 *    -at(NINE+2) and beyond - integers that originally were not in row
 * All vectors are buffered with DUMMY variable for ease of use
 * see header for function names or look below. 
 *     In alphabetical order except for the constructor
 * Author/copyright:  Alyssa Shofner. All rights reserved.
 * Date: 13 July 2013
 *
**/

static const string TAG = "Board: ";

/****************************************************************
 * Constructor.
**/
Board::Board()
{
}


/****************************************************************
 * Destructor.
**/
Board::~Board()
{
}

/****************************************************************
 * Accessors and mutators.
**/

/****************************************************************
 * Function for getting the value of a square.
 * returns single int from the board at the row and col given
 *  
 * ASSUMES
 *    board is made up of only integers
 *    no error checking needed
 *
 * PARAMETERS
 *    int row - row of wanted square
 *    int col - column of wanted square
 *
 * OUTPUT
 *    int value at the wanted square, 
 *      including the DUMMY originially to be 0
 *
**/
int Board::getSquare(int row, int col)
{
  return this->theBoard[row][col];
} // int Board::getSquare(int row, int col)

/****************************************************************
 * Function for getting the size of a row
 * returns the size of the row request  
 *  
 * ASSUMES
 *    board is made up of vector<int>
 *    no error checking needed
 *
 * PARAMETERS
 *    int row - row of wanted size
 *
 * OUTPUT
 *    int size of the row requested, errors if request board.at(size)
**/
int Board::getRowSize(int row)
{
  return this->theBoard.at(row).size();
} // int Board::getRowSize

/*************************************************************************
 * Function for adding a line to the board, utilized in Sudoku::readPuzzle
 * 
 * ASSUMES
 *  build of vector is true to form specificed in PARAMETERS, 
 *  as NO error checking occurs here
 * 
 * PARAMETERS
 *  vector<int> newLine is assumed to have following structure:
 *    -at(0) - DUMMY int, originally 0
 *    -at(1) through at(NINE) - either a DUMMY int or ONE through NINE int
 *    -at(NINE+1) - DUMMY int
 *    -at(NINE+2) and beyond - integers that originally were not in row 
**/
void Board::addLine(vector<int> newLine)
{
  this->theBoard.push_back(newLine);
}
/*********************************************************************
 * Function for testing the legality of the board.
 * utilizes Board::isLegal() to check that the rows, columns, 
 *   and boxes of the board have no repeating integers except for DUMMY
 *   Does NOT check to see if all are filled.
 *
 * ASSUMES
 *  isLegal(startRow, endRow, startCol, endCol) returns a bool
 *  there are 3 boxes per row, as box check is somewhat hard coded to reduce
 *     multiplication and division 
 *  that Sudoku board is only ints, due to the called isLegal
 * 
 * OUTPUT - boolean
 *   if false, depicts that there is a repeat in the board
 *   if true, depicts that there is no repeat in the board
 *   DOES NOT check to see if all are filled. 
 *   
 * VARIABLES 
 *  -i - counter to hold onto variables
**/
bool Board::isLegal()
{
  for(int i = ONE; i<=NINE; i++)
  {
    //testing rows
    if(this->isLegal(i, i, ONE, NINE) == false)
    {
      return false;
    }

    //testing columns
    if(this->isLegal(ONE, NINE, i, i) == false)
    {
      return false;
    }
  }

  //testing boxes
  for(int i = ONE; i <= THREE; i++)
  {
    //first box in row
    if(this->isLegal( (i*THREE), (i*THREE)+(THREE-1), ONE, THREE)==false)
    {
      return false;
    }  

   //second box in row
    if(this->isLegal( (i*THREE), (i*THREE)+(THREE-1), THREE+1, THREE+THREE)
       == false)
    {
      return false;
    }

   //third box in row
   if(this->isLegal( (i*THREE), (i*THREE)+(THREE-1), THREE+THREE+1, NINE)
      == false)
   {
     return false;
   } 
  }
   return true;
} // bool Board::isLegal()

/*************************************************************************
 * Function for testing if no numbers repeat in boxes of the board
 * hard coded so that multiplication does not have to be done.
 * utilizes isLegal(startRow, endRow, startCol, endCol)
 * ASSUMES
 *   isLegal(startRow, endRow, startCol, endCol) returns boolean
 *   define SIX is 2*THREE
 * 
 * PARAMETERS
 *   -int rowBox - 0, 1, 2 that is the rowBox (square % 3)
 *   -int colBox - 0, 1, 2 that is the colBox (square % 3)
 * 
 * OUTPUT - boolean
 *   if false, depicts that there is a repeat in given box
 *   if true, depicts that there is no repeat except perhaps for DUMMY int
 *
 * VARIABLES
 *   -startRow - int ONE, THREE+1, or SIX+1 to depict start row of 3x3 box
 *   -endRow - int THREE, SIX, or NINE to depict end row of 3x3 box 
 *   -startCol - int ONE, THREE+1, or SIX+1 to depict start column of 3x3box
 *   -endCol - int THREE, SIX, or NINE to dipict end column of 3x3 box
**/
bool Board::isLegal(int rowBox, int colBox)
{
  int startRow = 0;
  int endRow = 0;
  int startCol = 0;
  int endCol = 0;

 //assigning row
  if (rowBox == 0)
  {
    startRow = ONE;
    endRow = THREE;
  }
  else if (rowBox == 1)
  {
    startRow = THREE + 1;
    endRow = SIX;
  }
  else if (rowBox == 2)
  {
    startRow = SIX + 1;
    endRow = NINE;
  }
  else
  {
    cout<< TAG + "rowBox not found" << endl;
    return false;
  }

 //assigning column
  if (colBox == 0)
  {
    startCol = ONE;
    endRow = THREE;
  }
  else if (colBox == 1)
  {
    startCol = THREE + 1;
    endCol = SIX;
  }
  else if (colBox == 2)
  {
    startCol = SIX + 1;
    endCol = NINE;
  }
  else
  {
    cout << TAG + "columnBox not found" << endl;
    return false;
  }
  
  return this->isLegal(startRow, endRow, startCol, endCol);
}//isLegal()
/*******************************************************************
 * Function for testing if no numbers repeat in section of the board.
 * Uses boolean vector to check that no number is repeated twice.
 *
 * ASSUMES
 *   board is made up of ints
 *
 * PARAMETERS
 *   -int minRow - the row number that is the first to be checked
 *   -int maxRox - the row number that is the last to be checked
 *   -int minCol - the column number that is the first to be checked
 *   -int maxCol - the column number that is the last to be checked
 *
 * OUTPUT - boolean
 *   -if false, depicts that there was a repeat in the given area that is 
 *              not a DUMMY variable
 *   -if true,  depicts that there are no repeats except perhaps for DUMMY 
 *              variables in the given area
 *
 * VARIABLES
 *   -minRow, maxRow, minCol, maxCol, see PARAMETERS
 *   -alreadyMarked - vector<bool> that contains NINE+1 false bool until
 *                    the boolean at the index corresponding to
 *                    found integers in the given area are marked;
 *   -curr - int that depicts the currently being evaluated space
**/
bool Board::isLegal(int minRow, int maxRow, int minCol, int maxCol) const
{
 //initializing alreadyMarked Vector
  vector<bool> alreadyMarked;
  for(int i=0; i<=9; i++)//buffered vector
  {
    alreadyMarked.push_back(false);
  }

 //searching through each column and row for space that isn't a DUMMY int
  for(int i = minCol; i < maxCol+1; i++)
  {
    for(int j = minRow; j < maxRow+1; j++)
    {
      int curr = this->theBoard.at(j).at(i);
      if(curr != DUMMY)
      {
       //when int found, mark if hasn't been visited
        if(alreadyMarked.at(curr) == false)
        {
          cout<< "HERE at "<< curr << endl;
          alreadyMarked.at(curr) = true;
        }
        else //there is a repeat
        {
          cout << endl;
          return false;
        }
      }
    }
  }
  cout << endl;
  return true; 
} // bool Board::isLegal()

/****************************************************************
 * Function for setting the value of a square.
 *
 * ASSUMES
 *   board is made up of ints
 *   parameters are in bounds, as NO error checking occurs
 *
 * PARAMETERS
 *   -int row - row that the value is inputted into
 *   -int col - column that the value is inputted into
**/
void Board::setSquare(int row, int col, int value)
{
  if(this->theBoard.empty())
  {
    return;   
  }
  else
  {
    this->theBoard[row][col] = value;
  }
} // void Board::setSquare(int row, int col, int value)

/*******************************************************************
 * Function for un-setting the value of a square to default to DUMMY.
 *
 * ASSUMES
 *    -row and col are inbounds as NO error checking occurs
 *
 * PARAMETERS
 *    -int row - row of the wanted square
 *    -int col - column of the wanted square
 *
**/
void Board::unsetSquare(int row, int col)
{
  if(this->theBoard.empty())
  {
    return;
  }  
  else
  {
    this->theBoard[row][col] = DUMMY;
  }
} // void Board::unsetSquare(int row, int col)

/****************************************************************
 * General functions.
**/
/****************************************************************
 * Usual 'toString' function; this displays the current board.
 * 
 * ASSUMES
 *   that the vector is buffered and there is correct int value at NINE
 *
 * OUTPUTS - string
 *   in following format for original SUDOKU 9x9 board
 *   for rows, separated by a space, 3 sets of itegers separated by '|'
 *   for column, 3 sets of integers separated by '-'
 *   Example:
 *   0 2 4 | 8 3 9 | 1 6 7
 *   0 0 0 | 0 0 0 | 0 0 0
 *   0 0 0 | 0 3 0 | 8 9 4
 *   ------|-------|------
 *   2 0 0 | 5 0 0 | 3 0 0
 *   0 3 0 | 0 7 0 | 2 0 0
 *   0 4 0 | 0 9 0 | 6 0 0
 *   ------|-------|------
 *   0 9 3 | 0 8 0 | 4 0 0
 *   0 0 0 | 0 0 0 | 0 0 0
 *   0 0 0 | 0 0 0 | 0 0 0
**/
string Board::toString()
{
  string s;
  cout << TAG << "enter toString" << endl;

  for(int row = ONE; row <= NINE; ++row)
  {
    for(int col = ONE; col <= NINE; ++col)
    {
//      Utils::logStream << "zork " << endl;
      vector<int> theRow = this->theBoard[row];
      if(DUMMY == theRow[col])
      {
        s += " . ";
      }
      else
      {
        s += Utils::Format(theRow[col], 2) + " ";
      }
      if((0 == col%THREE) && (col < NINE))
      {
        s += "|";
      }
    } // for(int col = ONE; col <= NINE; ++col)
    s += "\n";

    if((0 == row%THREE) && (row < NINE))
    {
      s += "---------|---------|---------\n";
    }
  } // for(int row = ONE; row <= NINE; ++row)

  cout << TAG << "leave toString" << endl;
  return s;
} // void Board::toString()

