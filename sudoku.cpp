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
void printBoard(vector< vector<int> >& board, vector< vector<int> >& Original){
  // nothing for now, you will implement this for Partial 2 project delivery
  for(int r = 0; r < BOARDSIZE ; r++){
    for(int c = 0; c < BOARDSIZE ; c++){
      if(c > 0){
  cout << " ";
      }

      if (Original[r][c] != 0){
        // rojo 31
        cout << "\x1b[31m";
      } else {
        if (board[r][c] == 0){
           // white
           cout << "\x1b[39m";
        } else {
          // verde 41
          cout << "\x1b[32m";
        }
       
      }
      cout << board[r][c];
      // reset 91
    cout <<  "\x1b[39;49m";
    }
    cout << endl;
  }
}

bool winning(vector< vector<int> >& board){
  for(int r = 0; r < BOARDSIZE ; r++){
    for(int c = 0; c < BOARDSIZE ; c++){
      if(board [r][c]==0){
        return false;
      }
    }
  }
  return true;
}

bool check_rc(int value){
    if (value >= 0 && value<BOARDSIZE){
      return true;
    } else {
      cout << "Your answer is not valid. Please try again." << endl;
      return false;
    }
}

bool check_num(int value){
    if (value >= 1 && value<=BOARDSIZE){
      return true;
    } else {
      cout << "Your answer is not valid. Please try again." << endl;
      return false;
    }
}

bool evaluate_rc(int n, int r, int c, vector< vector<int> >& theBoard){
  for (int i=0; i<9; i++){
    if (theBoard[r][i]==n){
      cout << "Invalid movement. The number is repeated in that row." << endl;
      return false;
    }
  }
  for (int i=0; i<9; i++){
    if (theBoard[i][c]==n){
      cout << "Invalid movement. The number is repeated in that column." << endl;
      return false;
    }
  }
  return true;
}

bool evaluate_q(int n, int r, int c, vector< vector<int> >& theBoard){
  int kc, kr, ir, ic;
  ir = (r/3)*3;
  ic = (c/3)*3;
  for(kc=ic; kc < ic +3; kc++){
    for(kr=ir; kr < ir +3; kr++){
      if (theBoard [kr][kc]==n){
        cout << "Invalid movement. The number is repeated in that quadrant."  << endl;
        return false;
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
  createZeroBoard(Original);
  populateBoardFromFile(Original,filename);

  //    print (call the printBoard function)
  //    write (ask user what number they want to add and where), must accept only legal values
  //    erase (ask user which position they want to erase), must not erase original values
  //    quit (quit the program)
  string userChoice = "";
  while (winning(theBoard)==false && userChoice != "quit"){
    printBoard(theBoard,Original);
    cout << "What would you like to do (write, erase, reset, quit, history): ";
    cin >> userChoice;
    if(userChoice == "history"){
      cout << endl << "Sudoku (数独 sūdoku?, Digit-single), originally called Number Place,is a logic-based, combinatorial number-placement puzzle. The objective is to fill a 9×9 grid with digits so that each column, each row, and each of the nine 3×3 sub-grids that compose the grid (also called 'boxes', 'blocks', 'regions', or 'sub-squares') contains all of the digits from 1 to 9. The puzzle setter provides a partially completed grid, which for a well-posed puzzle has a unique solution." << endl << endl;
      continue;
    }
    if(userChoice == "reset"){
      populateBoardFromFile(theBoard,filename);
      continue;
    }
    if(userChoice == "write"){
      int r,c,n;
      do{
        do{
          cout << "Which row?" << endl;
          cin >> r;
        } while (check_rc(r)!= true);
        do{
          cout << "Wich column?"<< endl;
          cin >> c;
        } while (check_rc(c)!= true);
        if (theBoard[r][c] != 0){
          cout << "You already have a number there." << endl;
        }
      } while (theBoard[r][c] != 0);
      if (Original[r][c]!= 0){
        cout << "That is an original number and you can't change it" << endl;
      } else {
        do {
          cout << "Which number?" << endl;
          cin >> n;
        }while (check_num(n) != true || evaluate_rc (n, r, c, theBoard) !=true || evaluate_q (n, r, c, theBoard) !=true );
        theBoard[r][c] = n;
        }
      continue;
    }
    if(userChoice == "erase"){
      int r, c;
      do{
        cout << "Which row?" << endl;
        cin >> r;
      } while (check_rc(r)!= true);
      do{
        cout << "Wich column?"<< endl;
        cin >> c;
      } while (check_rc(c)!= true);
      if (Original[r][c] != 0){
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
  }
  if (winning(theBoard)==true){
  printBoard(theBoard,Original);
  cout << "Congratulations! You have complete the Sudoku!!" << endl;
}
  return 0;
}
