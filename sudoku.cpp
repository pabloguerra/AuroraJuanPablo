// Solving Problems with Programming
// Professor Ken Bauer
//
// Sudoku

// Aurora Alvarado González
// A01630329
// and
// Juan Pablo Santana González
// A01229382

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
    cout << "Something is wrong with the input file" << endl;
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
  for(int r = 0; r < BOARDSIZE ; r++){
    for(int c = 0; c < BOARDSIZE ; c++){
      if(c > 0){
  cout << " ";
      }
      cout << board[r][c];
    }
    cout << endl;
  }
}

bool check(int value){
    if (value<BOARDSIZE){
      return true;
    } else {
      cout << "Your answer is not valid. Please try again." << endl;
      return false;
    }
}

/*
 * Your main program goes here.
 * first get the parameters, check if parameter size is 2
 * first parameter is always the program name in C/C++
 * second parameter is the filename to read in this program
 * any other number of parameters is illegal
 */
int main(int argc, char* argv[]) {
  string filename;

  vector< vector<int> > theBoard(BOARDSIZE,vector<int>(BOARDSIZE));
  vector< vector<int> > Original(BOARDSIZE,vector<int>(BOARDSIZE));

  switch(argc)
    {
    case 1:
      cout << "Please provide the parameters to the program, you must enter a filename to initiate the Sudoku." << endl;
      exit(1);
    case 2:
      filename = argv[1];
      break;
    default:
      cout << "Please provide the parameters to the program, you must enter a filename to initiate the Sudoku." << endl;
      exit(1);
    }

  createZeroBoard(theBoard);
  populateBoardFromFile(theBoard,filename);
  cout << "Welcome to the Game of Sudoku" << endl;
  // Here you provide a menu to the user to do what they want
  // The options are:
  createZeroBoard(theBoard);
  populateBoardFromFile(Original,filename);

  //    print (call the printBoard function)
  //    write (ask user what number they want to add and where), must accept only legal values
  //    erase (ask user which position they want to erase), must not erase original values
  //    quit (quit the program)
  string userChoice = "";
  do{
    cout << "What would you like to do (print, write, erase, quit): ";
    cin >> userChoice;
    if(userChoice == "print"){
      printBoard(theBoard);
      continue;
    }
    if(userChoice == "write"){
      int r,c,n;

      do{
        cout << "Which row?" << endl;
        cin >> r;
      } while (check(r)!= true);
      do{
        cout << "Wich column?"<< endl;
        cin >> c;
       } while (check(c)!= true);
       do {
        cout << "Which number?" << endl;
        cin >> n;
       }while (check(n) =! true);
       if (Original[r][c]=! 0){
         cout << "That is an original number and you can't erase it" << endl;
       } else{
        theBoard[r][c] = n;
       }

      continue;
    }
    if(userChoice == "erase"){
      int r, c;
      do{
        cout << "Which row?" << endl;
        cin >> r;
      } while (check(r)!= true);
      do{
        cout << "Wich column?"<< endl;
        cin >> c;
      } while (check(c)!= true);
      if (Original[r][c]=!0){
        cout << "That is an original number and you can't erase it" << endl;
      } else { 
        theBoard [r][c] = 0;
      }
      continue;
    }
    if(userChoice == "quit"){
      cout << "Thanks for playing our game, have a great day!" << endl;
      continue;
    }
    cout << "That was not a valid choice, try again." << endl;
  } while (userChoice != "quit");

  return 0;
}
