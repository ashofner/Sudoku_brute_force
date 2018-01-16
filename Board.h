/****************************************************************
 * Header for the 'Board' class for Sudoku class.
 *
 * Author/copyright: Alyssa Shofner
 * Date: 1 Oct 2015
 *
**/

#ifndef BOARD_H
#define BOARD_H

#include <vector>
#include "../../Utilities/Utils.h"
#define DUMMY 0
#define NINE 9
#define THREE 3
#define ONE 1
#define SIX 6

using namespace std;

class Board
{
public:
/****************************************************************
 * Constructors and destructors for the class. 
**/
  Board();
  virtual ~Board();

/****************************************************************
 * General functions.
**/
  bool isLegal();
  bool isLegal(int minRow, int maxRow, int minCol, int maxCol) const;
  bool isLegal(int rowBox, int colBox);
  void display();
  int getSquare(int row, int col);
  int getRowSize(int row);
  void setSquare(int row, int col, int value);
  void unsetSquare(int row, int col);
  void addLine(vector<int>);
  string toString();

private:
/****************************************************************
 * Variables.
**/
  vector< vector<int> > theBoard;
/****************************************************************
 * Functions.
**/
};

#endif // BOARD_H
