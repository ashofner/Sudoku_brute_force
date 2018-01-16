/****************************************************************
 * Header for the 'Sudoku' class.
 * utilizes Board class
 * Sudoku version 9x9 with 9 non-overlapping 3x3 boxes
 * 
 * Author/copyright: Alyssa Shofner
 * Date: 18 Oct 2015
 *
**/

#ifndef SUDOKU_H
#define SUDOKU_H

#include "../../Utilities/Utils.h"
#include "../../Utilities/Scanner.h"
#include "../../Utilities/ScanLine.h"
#include "Board.h"
#define DUMMY 0
#define NINE 9
#define THREE 3
#define ONE 1

class Sudoku
{
public:
/****************************************************************
 * Constructors and destructors for the class. 
**/
  Sudoku();
  virtual ~Sudoku();

/****************************************************************
 * General functions.
**/
  void readPuzzle(Scanner& inStream);
  void solvePuzzle();
  string toString(string label);

private:
/****************************************************************
 * Variables.
**/
  int depth;
  Board board;
/****************************************************************
 * Functions.
**/
  bool addSquare(int row, int column, int& depth);
};

#endif // DOTHEWORK_H
