/*
Name: Priyanjali Rudra
Date: Dec 1, 2023
Prof: Mitchell D. Theys
Description: Undo and Print mechanic for Program 5 Connect 4 Game using linked lists
Environment used: Replitt
*/

#include <iostream>
#include <string>
#include <fstream>
#include <vector>

using namespace std;

//Class for each node in the linked list
class Undo {
  public:
  string boardCondition[7][7]; //current state of board
  Undo* prev;//pointer to next node (but previous move)

  //constructor
  Undo(string board[7][7]){
    for (int r = 0; r < 7; r++){
      for (int c = 0; c < 7; c++){
        boardCondition[r][c] = board[r][c];
      }
    }
    prev = NULL;
  }
};

//Class for the linked list
class UndoLinkedList {
  private:
    Undo* head; //head

  public:
    UndoLinkedList() : head(nullptr) {} //constructor defined
    ~UndoLinkedList(); //destructor
    void add(string state[7][7]); //adds move to stack
    void pop(); //removes most recent move from stack

    void recent(std::string result[7][7]) const;

    bool IsEmpty() const; //checks whether stack is empty

    bool hasMoreThanOneState() const; //checks whether stack has more than one state

    void printAll() const;
};

UndoLinkedList::~UndoLinkedList() {
   cout << "Destructor called." << endl;
   delete head;
}

void UndoLinkedList::add(string state[7][7]) {
  Undo* newNode = new Undo(state);
  newNode->prev = head;  // Set the prev pointer to the current head
  head = newNode;        // Update the head to the new node
}

void UndoLinkedList::pop() {
  if (head != nullptr) {
    Undo* top = head;
    head = top->prev;
    delete top;
  }
}

void UndoLinkedList::recent(string result[7][7]) const {
  if (head != nullptr) {
    // Copy the board condition
    for (int i = 0; i < 7; ++i) {
      for (int j = 0; j < 7; ++j) {
        result[i][j] = head->boardCondition[i][j];
      }
    }
  } 
}

bool UndoLinkedList::IsEmpty() const {
  if(head == nullptr) {
    return true;
  }
  else {
    return false;
  }
}

bool UndoLinkedList::hasMoreThanOneState() const {
  if (head != nullptr && head->prev != nullptr){
    return true;
  }
  else {
    return false;
  }
}

void UndoLinkedList::printAll() const {
  std::vector<Undo*> moves;  // Store moves in a vector

  // Collect all moves in reverse order
  Undo* current = head;
  while (current != nullptr) {
    moves.push_back(current);
    current = current->prev;
  }

  // Print moves in reverse order
  for (int i = moves.size() - 1; i >= 0; --i) {
    // Iterate through rows
    for (int r = 0; r < 7; ++r) {
    // Iterate through columns
      for (int c = 0; c < 7; ++c) {
        // Print the board condition for the current move
        cout << moves[i]->boardCondition[r][c] << " ";
      }
      // Move to the next row
      cout << endl;
    }
    // Add a newline between moves
    cout << endl;
  }
  
}

//Program 5 functions
void showBoard(string gameboard[7][7]) { //Displayes the board to user and sets the frame of the board
  for (int r = 0; r < 7; r++) {
    for (int c = 0; c < 7; c++) {
      cout << gameboard[r][c] << " ";
    }
    cout << endl;
  }

}

void moveX(string gameboard[7][7], char turn) {
  int col = turn - '0';
  for (int r = 6; r < 7; r--) {
    if (gameboard[r][col] == "-") {
      gameboard[r][col] = "X";
      break;
    }
  }
}

void moveO(string gameboard[7][7], char turn) {
  int col = turn - '0';
  for (int r = 6; r < 7; r--) {
    if (gameboard[r][col] == "-") {
      gameboard[r][col] = "O";
      break;
    }
  }
}

bool BoardisFull(string gameboard[7][7]) {
  int counter = 0;
  bool gameover = false;

  for (int r = 1; r < 7; r++) {
    for (int c = 0; c < 7; c++) {
      if ((gameboard[r][c] == "X") || (gameboard[r][c] == "O")) {
        counter++;
      }
    }
  }
  if (counter == 42) {
    gameover = true;
    cout << "Board is Full, It's a Draw!!!";
  }
  return gameover;
}

bool GameOver(string gameboard[7][7]) {
  bool gameover = false;
  //diagonal Downward
  //X 
  for (int r = 1; r < 4; r++) {
    for (int c = 0; c < 3; c++) {
      if (gameboard[r][c] == "X") {
        if ((gameboard[r+1][c+1] == "X") && (gameboard[r+2][c+2] == "X") && (gameboard[r+3][c+3] == "X")) { //Why did this work
          gameover = true;
          cout << "Game is Over, Player X got 4 in a row!!!!";
          return gameover;
        }
      }
    }
  }
  //O
  for (int r = 1; r < 4; r++) {
    for (int c = 0; c < 3; c++) {
      if (gameboard[r][c] == "O") {
        if ((gameboard[r+1][c+1] == "O") && (gameboard[r+2][c+2] == "O") && (gameboard[r+3][c+3] == "O")) { //Why did this work
          gameover = true;
          cout << "Game is Over, Player O got 4 in a row!!!!";
          return gameover;
        }
      }
    }
  }

  //diagonal upward
  //X
  for (int r = 6; r > 3; r--) {
    for (int c = 0; c < 4; c++) {

      if (gameboard[r][c] == "X") {
        if (gameboard[r-1][c+1] == "X" && gameboard[r-2][c+2] == "X" && gameboard[r-3][c+3] == "X") {
          gameover = true;
          cout << "Game is Over, Player X got 4 in a row!!!!";
          return gameover;
        }
      }
    }
  }
  //O
  for (int r = 6; r > 3; r--) {
    for (int c = 0; c < 4; c++) {

      if (gameboard[r][c] == "O") {
        if (gameboard[r-1][c+1] == "O" && gameboard[r-2][c+2] == "O" && gameboard[r-3][c+3] == "O") {
          gameover = true;
          cout << "Game is Over, Player O got 4 in a row!!!!";
          return gameover;
        }
      }
    }
  }

  //horizontal
  //X
  for (int r = 6; r < 7; r++) {
    for (int c = 0; c < 4; c++) {

      if (gameboard[r][c] == "X") {
        if (gameboard[r][c+1] == "X" && gameboard[r][c+2] == "X" && gameboard[r][c+3] == "X") {
          gameover = true;
          cout << "Game is Over, Player X got 4 in a row!!!!";
          return gameover;
        }
      }
    }
  }
  //O
  for (int r = 1; r < 7; r++) {
    for (int c = 0; c < 4; c++) {

      if (gameboard[r][c] == "O") {
        if (gameboard[r][c+1] == "O" && gameboard[r][c+2] == "O" && gameboard[r][c+3] == "O") {
          gameover = true;
          cout << "Game is Over, Player O got 4 in a row!!!!";
          return gameover;
        }
      }
    }
  }

  //vertical
  //X
  for (int r = 6; r > 3; r--) {
    for (int c = 0; c < 7; c++) {

      if (gameboard[r][c] == "X") {
        if (gameboard[r-1][c] == "X" && gameboard[r-2][c] == "X" && gameboard[r-3][c] == "X") {
          gameover = true;
          cout << "Game is Over, Player X got 4 in a row!!!!";
          return gameover;
        }
      }
    }
  }
  //O
  for (int r = 6; r > 3; r--) {
    for (int c = 0; c < 7; c++) {

      if (gameboard[r][c] == "O") {
        if (gameboard[r-1][c] == "O" && gameboard[r-2][c] == "O" && gameboard[r-3][c] == "O") {
          gameover = true;
          cout << "Game is Over, Player O got 4 in a row!!!!";
          return gameover;
        }
      }
    }
  }
  return gameover;
}
//end of Program 5 functions

int main() {
  char turn;

  string gameBoard[7][7] = 
  {{"0","1","2","3","4","5","6"},
  {"-","-","-","-","-","-","-"},
  {"-","-","-","-","-","-","-"},
  {"-","-","-","-","-","-","-"},
  {"-","-","-","-","-","-","-"},
  {"-","-","-","-","-","-","-"},
  {"-","-","-","-","-","-","-"}};

  UndoLinkedList undoHistory; //create linked list
  undoHistory.add(gameBoard);//add empty gameboard to linked list

  string initialState[7][7]; //empty board

  cout << "This is the Game Connect 4. Each player should place an X or an O in the space by entering the column you want to place the piece. The piece will fall until it reaches the bottom or the current pieces in the board."; 
  cout << "When X or O gets 4 in a row (either horizontally, vertically, or diagonally,then that person wins.";
  cout << "The user can enter Q (or q) to end the game early." << endl;

  cout << "Let's get started!!! " << endl;

  char player = 'X';
  showBoard(gameBoard);

  while ((GameOver(gameBoard) == false) && (BoardisFull(gameBoard) == false)) { 
    cout << "It is " << player << "'s turn." << endl;
    cout << "Enter a column to place your piece.";

    cin >> turn;


    if((turn == 'Q') || (turn =='q')) {
      cout << "Ending Game";
      break;
    }


    else if ((turn == 'U') || (turn =='u')) {
      if (undoHistory.hasMoreThanOneState()) {
        cout << "Undo" << endl;
        undoHistory.pop(); // Pop the last move
        string recentState[7][7];
        undoHistory.recent(recentState); //converts empty array recentState into the most recent gameboard

        // Update the game board with the recent state
        for (int r = 0; r < 7; ++r) {
          for (int c = 0; c < 7; ++c) {
            gameBoard[r][c] = recentState[r][c];
          }
        }
        if (player == 'X') { //if player was X now it is O
          player = 'O';
        }
        else if (player == 'O') { //if player was O now it is X
          player = 'X';
        }

        // Display the updated game board
        showBoard(gameBoard);
        continue; // Skip the rest of the loop to prevent adding the same state again
      } 
      else {
        cout << "Cannot undo. No more moves available." << endl;
        showBoard(gameBoard);
        continue;
      }
    }


    if ((turn == 'p') || (turn =='P')) { //Allws player to print all moves
      undoHistory.printAll();
    }


    else if (gameBoard[1][turn -'0'] != "-") {
      cout << "column chosen is already full" << endl;
      cout << endl;
      continue;
    }

    if (player == 'X') {
      moveX(gameBoard,turn);
      player = 'O';
    }
    else if (player == 'O') {
      moveO(gameBoard,turn);
      player = 'X';
    }


    for (int r = 0; r < 7; r++) {
      for (int c = 0; c < 7; c++) {
        initialState[r][c] = gameBoard[r][c]; //updates initialState once player has moved
      }
    }


    undoHistory.add(initialState); //adds players move onto linked list
    showBoard(gameBoard);
  }
}
