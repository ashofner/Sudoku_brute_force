/****************************************************************
 * Homework 4 main program.
 *
 * Author/copyright:  Duncan Buell. All rights reserved.
 * Date: 18 August 2015
 * runs the Sudoku and Board of Alyssa Shofner
**/
#include "Main.h"

static const string TAG = "Main: ";

int main(int argc, char *argv[])
{
  string timeCallOutput;
  string inStreamName;
  string outStreamName;

  Scanner inStream;
  ofstream outStream;
  Sudoku sudoku;

  Utils::CheckArgs(2, argc, argv, "infilename outfilename");
  inStreamName = static_cast<string>(argv[1]);
  outStreamName = static_cast<string>(argv[2]);

  Utils::FileOpen(outStream, outStreamName);

  timeCallOutput = Utils::timecall("beginning");
  outStream << timeCallOutput;
  outStream << TAG << "\nBeginning execution" << endl;
  outStream << "infile  '" << inStreamName << "'\n";
  outStream << "outfile '" << outStreamName << "'\n";
  outStream.flush();

  inStream.openFile(inStreamName);

  sudoku.readPuzzle(inStream);
  outStream << sudoku.toString("\nAfter reading");
  outStream.flush();
  inStream.close();

  sudoku.solvePuzzle();
  outStream << sudoku.toString("\nAfter solving");
  outStream.flush();

  outStream << TAG << "\nEnding execution" << endl;
  timeCallOutput = Utils::timecall("ending");
  outStream << timeCallOutput;
  outStream.flush();

  outStream.close();

  return 0;
}
