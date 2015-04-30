// Solving Problems with Programming
// Professor Ken Bauer
//
// Sudoku

// Student Mitzi Sarahi Hernández Jauregui
// Student A01630243
// and
// Student Pablo Daniel Guerra Cervantes
// Student A01271665

// Standard libraries
#include <string>
#include <iostream>
#include <fstream>
#include <vector>
#include <algorithm>

using namespace std;

const int BOARDSIZE = 9;
const int EMPTY = 0;

/*
 * creates a board filed with zeroes (empty spaces)
 * we will do this, then populate it from a file with
 * another function below
 */
void createZeroBoard(vector< vector<int> >& board){
  for(int r = 0; r < BOARDSIZE ; r++){
    // grab a full line from the file
    for(int c = 0; c < BOARDSIZE ; c++){
      board[r][c] = EMPTY;
    }
  }
}

/*
 * Populates the board from the contents of the file
 * The file must contain 9 lines with 9 values each line
 * The values must be either zero (0) for empty or values between 1 and 9
 */
void populateBoardFromFile(vector< vector<int> >& board, string filename){
  ifstream infile(filename.c_str()); // the c_str() is to convert from string to char*
  int cell;
  string line;
  if(infile.good()){
    for(int r = 0; r < BOARDSIZE ; r++){
      // grab a full line from the file
      for(int c = 0; c < BOARDSIZE ; c++){
  infile >> cell;
  board[r][c] = cell;
      }
    }
  } else {
    cout << "\x1b[34m\x1b[40mSomething is wrong with the input file" << endl;
    cout << "\x1b[39;49m";
  }
}

/*
 * The function prints the board.
 * Each cell is a zero (for empty) or the value 1 to 9
 * Each cell is separated by a space
 * NO SPACE at end of row.
 */
 void printBoard(vector< vector<int> >& board){
   // nothing for now, you will implement this for Partial 2 project delivery
   cout << "=====================" << endl;
   for(int r = 0; r < BOARDSIZE ; r++){
     cout << "|";
     for(int c = 0; c < BOARDSIZE ; c++){
         if(c > 0){

   cout << " ";
       }
       cout << board[r][c];
       if(c%3 == 2){
         cout << "|";
       }
     }
     cout << endl;
     if(r%3 == 2){
       cout << "=====================" << endl;
     }
   }
 }

bool n_check (int row, int column)
{
  if ((row < BOARDSIZE) && (column < BOARDSIZE))
    return true;
  else
    cout << "\x1b[34m\x1b[40mPlease enter a number lower than 9, thank you" << endl;
    return false;
    cout << "\x1b[39;49m";
}

bool n_checkl (int row, int column,int number,vector< vector<int> >& theBoard)
{
    for (int i=0; i< BOARDSIZE; i++)
    {
      if (theBoard[row][i] == number){
        cout << "\x1b[34m\x1b[40mInvalid move, an equal numver it´s already in the row" << endl;
        return false;
        cout << "\x1b[39;49m";
      }
    }

    for (int i=0; i< BOARDSIZE; i++)
    {
      if (theBoard[i][column] == number){
        cout << "\x1b[34m\x1b[40mInvalid move, an equal number it´s already in the column" << endl;
        return false;
        cout << "\x1b[39;49m";
      }
    }
    return true;
}
bool check (int row, int column)
{
  if ((row >= 0 ) && (row<BOARDSIZE) &&(column >= 0) && (column< BOARDSIZE))
    return true;
  else
  {
  cout <<"\x1b[31m\x1b[40mMust be a number between 0 and 8" << endl;
  return false;
  cout << "\x1b[39;49m";
  }
}

bool quadrant (int row, int number, int column, vector< vector<int> >& theBoard )
{
  int cor, coc,limitr,limitc;
              // (4,5)
  cor = (row/3)*3;
  coc = (column/3)*3;

             //  (1,1) Posición izquierda superior del cuadrante donde se encuentra el número;
  for (int i=coc; i<coc+3; i++)
  {
    for (int j=cor; j<cor+3;j++)
    {
      if (theBoard [j][i] == number )
      {
        cout << "\x1b[34m\x1b[40mInvalid move, equal number in the same quadrant" << endl;
      return false;
      cout << "\x1b[39;49m";
      }
    }
  }
  return true;
}

/*
 * Your main program goes here.
 * first get the parameters, check if parameter size is 2
 * first parameter is always the program name in C/C++
 * second parameter is the filename to read in this program
 * any other number of parameters is illegal
 */
int main(int argc, char* argv[]) {
  int column, row,number;
  string filename;

  vector< vector<int> > theBoard(BOARDSIZE,vector<int>(BOARDSIZE));
  vector< vector<int> > programer_Board(BOARDSIZE,vector<int>(BOARDSIZE));

  switch(argc)
    {
    case 1:
    cout<< "\x1b[31m **Please provide the parameters to the program, you must enter a filename to initiate the Sudoku.\x1b[39;49m" << endl;
      exit(1);
    case 2:
      filename = argv[1];
      break;
    default:
    cout<< "\x1b[31m **Please provide the parameters to the program, you must enter a filename to initiate the Sudoku.\x1b[39;49m" << endl;
      exit(1);
    }

  createZeroBoard(theBoard);
  populateBoardFromFile(theBoard,filename);

  createZeroBoard(programer_Board);
  populateBoardFromFile(programer_Board,filename);


  cout << "\x1b[37m\x1b[44mWelcome to Sudoku" << endl;
  cout << endl;
  cout << endl;
  cout << "Welcome to the sudoku world, please enjoy" << endl;
  cout << "The options that are able for you while you play are: "<< endl;
  cout << "Print: Will print you the board." << endl;
  cout << "Write: Will ask you for a row and a colum for the new number." << endl;
  cout << "Quit: Will close the sudoku." << endl;
  cout << endl;
  cout << "\x1b[39;49m";
  string userChoice = "";
  cout << "\x1b[35m\x1b[40mLet begin" << endl;
  do{
    cout << "\x1b[35m\x1b[40mWhat would you like to do (print, write, erase, quit):" << endl;
    cin >> userChoice;
    if(userChoice == "print"){
      cout << "\x1b[33m\x1b[40mThe table is: " << endl;
      printBoard(theBoard);
      continue;
    }
    if(userChoice == "write"){
      do
      {
        do
        {
          cout << "\x1b[36m\x1b[40mWhere would you like to enter the new number (column) note**(0 to 8) ? " << endl;
          while (!(cin >> column))
          {
            cout<< "must be a number " <<endl;
            cin.clear();
            cin.ignore(100, '\n');
          }
          cout<< "Where would you like to enter the new number (row) note**(0 to 8) ? " << endl;
          while (!(cin >> row))
          {
            cout<< "must be a number " <<endl;
            cin.clear();
            cin.ignore(100, '\n');
          }
          if (n_check (column, row) != true)
          cout<< "\x1b[31m **Invalid move, row and number must be lower than 9\x1b[39;49m" << endl;
          else
            if (programer_Board [row][column] != 0)
            cout<< "\x1b[31m **Original numbers can´t be modified\x1b[39;49m" << endl;
        }while (check (row,column) != true);
      }while (n_check (column, row) != true|| programer_Board [row][column] != 0);

      do
      {
        cout << "\x1b[39m\x1b[40mGive the new number: "<< endl;
        cin >> number;
      }while ((n_checkl(row,column,number,theBoard) != true)  || (quadrant (row,number,column, theBoard) != true));
      theBoard [row][column] = number;
      cout << "\x1b[33m\x1b[40mThe table is: " << endl;
      printBoard(theBoard);
      cout << "\x1b[39;49m";
      continue;
    }
    if(userChoice == "erase"){
      do {
        cout << "\x1b[32m\x1b[40mWhere is the  column of the number that has to be erased ? note**(0 to 8)" << endl;
        while (!(cin >> column)){
          cout<< "must be a number " <<endl;
          cin.clear();
          cin.ignore(100, '\n');
        }
        cout<< "Where is the row of the number that has to be erased ? note**(0 to 8)" << endl;
        while (!(cin >> row)){
          cout<< "must be a number " <<endl;
          cin.clear();
          cin.ignore(100, '\n');
        }
        if (n_check (column, row) != true)
        cout<< "\x1b[31m **Invalid move, row and number must be lower than 9\x1b[39;49m" << endl;
      }while (n_check (column, row) != true);

      if (programer_Board [row][column] != 0)
      cout<< "\x1b[31m **Original numbers can´t be modified\x1b[39;49m" << endl;
        else
        {
          theBoard [row][column] = 0;
          cout << "\x1b[39;49m";
        }
      cout << "\x1b[33m\x1b[40mThe table is: " << endl;
      printBoard(theBoard);
      cout << "\x1b[39;49m";
      continue;
    }
    if(userChoice == "quit"){
      cout << "\x1b[34m\x1b[40mThanks for playing our game, have a great day!" << endl;
      continue;
    }
    cout<< "\x1b[31m **That was not a valid choice, try again.\x1b[39;49m" << endl;
  } while (userChoice != "quit");
  cout << "\x1b[39;49m";

  return 0;
}
