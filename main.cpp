#include <iostream>
#include <thread>
#include <chrono>
#include <cstring>

using namespace std;

//Global variables
const short int rowSize = 10;
const short int colSize = 10;

//Ship classes
class shipEntity_player {
  public:
      bool p_isDead;
      int p_hp;
      char positionsPlayer[rowSize][colSize];
};

class shipEntity_computer {
  public:
    bool c_isDead;
    int c_hp;
    char positionsComputer[rowSize][colSize];
};

//Functions

void computerHitCheck(char (&board2)[rowSize][colSize], int inputR, int inputC, int& computer_totalHP, shipEntity_computer& computerCarrier, shipEntity_computer& computerBattleship, shipEntity_computer& computerDestroyer, shipEntity_computer& computerSubmarine, shipEntity_computer& computerPT);

//Final Boards
void player_placeShips(char (&board1)[rowSize][colSize]);

//Computer ship placements / checks
void carrierPlacement(char (&board2)[rowSize][colSize], shipEntity_computer& computerCarrier);
void battleshipPlacement(char (&board2)[rowSize][colSize], shipEntity_computer& computerBattleship);
void destroyerPlacement(char (&board2)[rowSize][colSize], shipEntity_computer& computerDestroyer);
void submarinePlacement(char (&board2)[rowSize][colSize], shipEntity_computer& computerSubmarine);
void patrolPlacement(char (&board2)[rowSize][colSize], shipEntity_computer& computerPT);

int main() {
  //Game variables
  char playerBoard[rowSize][colSize];
  static char last_playerBoard[rowSize][colSize];
  char computerBoard[rowSize][colSize];

  //Game checks
  bool isGameRunning;
  int player_totalHP = 17;
  int computer_totalHP = 17; 

  //Choice variables
  char questionChoice;
  int inputR;
  int inputC;

  //Introduce game
  cout << "Welcome to Battleship!" << endl;
  cout << endl;
  cout << "You have 5 ships to place: " << endl;
  cout << endl;
  cout << "CARRIER [5 SPACES]" << endl;
  cout << "BATTLESHIP [4 SPACES]" << endl;
  cout << "DESTROYER [3 SPACES]" << endl;
  cout << "SUBMARINE [3 SPACES]" << endl;
  cout << "PATROL BOAT [2 SPACES]" << endl;

  cout << "Would you like to play? (Y/N)" << endl;
  cin >> questionChoice;

  if (questionChoice == 'N' || questionChoice == 'n') {
    return 0;
  } else if (questionChoice == 'Y' || questionChoice == 'y') {
    system("clear");
  } else {
    return 0;
  }

  //Placeholder values in array
  for (int i = 0; i < 10; i++) {
    for (int j = 0; j < 10; j++) {
      playerBoard[i][j] = '#';
      last_playerBoard[i][j] = '#';
      computerBoard[i][j] = '#';
    }
  }

  //Create class objects
  shipEntity_player playerCarrier, playerBattleship, playerDestroyer, playerSubmarine, playerPT;
  shipEntity_computer computerCarrier, computerBattleship, computerDestroyer, computerSubmarine, computerPT;
 
  //Set object health values
  playerCarrier.p_hp = 5;
  playerBattleship.p_hp = 4;
  playerDestroyer.p_hp = 3;
  playerSubmarine.p_hp = 3;
  playerPT.p_hp = 2;

  computerCarrier.c_hp = 5;
  computerBattleship.c_hp = 4;
  computerDestroyer.c_hp = 3;
  computerSubmarine.c_hp = 3;
  computerPT.c_hp = 2;

  //Set object booleans
  playerCarrier.p_isDead = false;
  playerBattleship.p_isDead = false;
  playerDestroyer.p_isDead = false;
  playerSubmarine.p_isDead = false;
  playerPT.p_isDead = false;

  computerCarrier.c_isDead = false;
  computerBattleship.c_isDead = false;
  computerDestroyer.c_isDead = false;
  computerSubmarine.c_isDead = false;
  computerPT.c_isDead = false;

  //Fill in secondary arrays
  for (int i = 0; i < rowSize; i++) {
    for (int j = 0; j < colSize; j++) {
      playerCarrier.positionsPlayer[i][j] = '#';
      playerBattleship.positionsPlayer[i][j] = '#';
      playerDestroyer.positionsPlayer[i][j] = '#';
      playerSubmarine.positionsPlayer[i][j] = '#';
      playerPT.positionsPlayer[i][j] = '#';

      computerCarrier.positionsComputer[i][j] = '#';
      computerBattleship.positionsComputer[i][j] = '#';
      computerDestroyer.positionsComputer[i][j] = '#';
      computerSubmarine.positionsComputer[i][j] = '#';
      computerPT.positionsComputer[i][j] = '#';
    }
  }
  //Start ship placements
  player_placeShips(playerBoard);
  carrierPlacement(computerBoard, computerCarrier);
  battleshipPlacement(computerBoard, computerBattleship);
  destroyerPlacement(computerBoard, computerDestroyer);
  submarinePlacement(computerBoard, computerSubmarine);
  patrolPlacement(computerBoard, computerPT);

  system("clear");

  int a = rand() % 2;

  if (a == 0) {
    while (isGameRunning == true) {
      copy(begin(playerBoard), end(playerBoard), begin(last_playerBoard));

      cout << "This is your current board: " << endl;

      for (int i = 0; i < rowSize; i++) {
        for (int j = 0; j < colSize; j++) {
          cout << playerBoard[i][j];
        }
        cout << endl;
      }

      computerHitCheck(computerBoard, inputR, inputC, computer_totalHP, computerCarrier, computerBattleship, computerDestroyer, computerSubmarine, computerPT);

      system("clear");
    }
  } else if (a == 1) {

  }

  return 0;
}

void player_placeShips(char (&board1)[rowSize][colSize]) {
  //Variables
  bool end = false;
  char choice;
  int rowInput;
  int colInput;

  cout << "You will place the below ships in order from top to bottom: " << endl;
  cout << endl;
  cout << "CARRIER [5 SPACES]" << endl;
  cout << "BATTLESHIP [4 SPACES]" << endl;
  cout << "DESTROYER [3 SPACES]" << endl;
  cout << "SUBMARINE [3 SPACES]" << endl;
  cout << "PATROL BOAT [2 SPACES]" << endl;

  this_thread::sleep_for(chrono::seconds(3));
  system("clear");

  int p = 0;

  while (p < 5 && end == false) {
    for (int k = 0; k < 10; k++) {
      for (int l = 0; l < 10; l++) {
        cout << board1[k][l]; 
      }
      cout << endl;
    }

    cout << endl;
    cout << "That's your current board" << endl;
    cout << endl;

    switch(p) {
      case 0:
        cout << "Will you like to place the carrier [5 PLACES] horizontally or vertically? (H/V)" << endl;
        cin >> choice;

        if (choice == 'H' || choice == 'h') {
          cout << "What ROW do you want the ship in? (1 - 10)" << endl; 
          cin >> rowInput;
          rowInput -= 1; //Adjust size

          if (rowInput < 0 || rowInput > 9) {
            cout << "ERROR: Invalid number, try again: " << endl;
            cin >> rowInput; 
            rowInput -= 1; //Adjust size

            system("clear");

            if (rowInput < 0 || rowInput > 9) {
              cout << "CRITICAL ERROR" << endl;
              end = true;
              break;
            }
          }

          cout << "What COLUMN do you want the FRONT (Facing right) of the ship in? (5 - 10)" << endl;
          cin >> colInput;
          colInput -= 1; //Adjust size

          if (colInput < 4 || colInput > 9) {
            cout << "ERROR: Invalid number, try again: " << endl;
            cin >> colInput; 
            colInput -= 1; //Adjust size

            system("clear");

            if (colInput < 4 || colInput > 9) {
              cout << "CRITICAL ERROR" << endl;
              end = true;
              break;
            }
          }

          cout << endl;
          cout << "Do you accept placement? (Y/N)" << endl;
          cin >> choice;

          if (choice == 'Y' || choice == 'y') {
            cout << "PLACING CARRIER" << endl;
          } else if (choice == 'N' || choice == 'N') {
            cout << "What ROW do you want the ship in? (1 - 10)" << endl; 
            cin >> rowInput;
            rowInput -= 1; //Adjust size

            if (rowInput < 0 || rowInput > 9) {
              cout << "ERROR: Invalid number, try again: " << endl;
              cin >> rowInput; 
              rowInput -= 1; //Adjust size

              system("clear");

              if (rowInput < 0 || rowInput > 9) {
                cout << "CRITICAL ERROR" << endl;
                end = true;
                break;
              }
            }

            cout << "What COLUMN do you want the FRONT (Facing right) ship in? (5 - 10)" << endl;
            cin >> colInput;
            colInput -= 1; //Adjust size

            if (colInput < 4 || colInput > 9) {
              cout << "ERROR: Invalid number, try again: " << endl;
              cin >> colInput; 
              colInput -= 1; //Adjust size

              system("clear");

              if (colInput < 4 || colInput > 9) {
                cout << "CRITICAL ERROR" << endl;
                end = true;
                break;
              }
            }

            board1[rowInput][colInput] = '-';
            board1[rowInput][colInput - 1] = '-';
            board1[rowInput][colInput - 2] = '-';
            board1[rowInput][colInput - 3] = '-';
            board1[rowInput][colInput - 4] = '-';
          }

          board1[rowInput][colInput] = '-';
          board1[rowInput][colInput - 1] = '-';
          board1[rowInput][colInput - 2] = '-';
          board1[rowInput][colInput - 3] = '-';
          board1[rowInput][colInput - 4] = '-';
        } else if (choice == 'V' || choice == 'v') {
          cout << "What COLUMN do you want the ship in? (1 - 10)" << endl; 
          cin >> colInput;
          colInput -= 1; //Adjust size

          if (colInput < 0 || colInput > 9) {
            cout << "ERROR: Invalid number, try again: " << endl;
            cin >> colInput; 
            colInput -= 1; //Adjust size

            system("clear");

            if (colInput < 0 || colInput > 9) {
              cout << "CRITICAL ERROR" << endl;
              end = true;
              break;
            }
          }

          cout << "What ROW do you want the FRONT (Front facing up) of the ship in? (1 - 5)" << endl;
          cin >> rowInput;
          rowInput -= 1; //Adjust size

          if (rowInput < 0 || rowInput > 4) {
            cout << "ERROR: Invalid number, try again: " << endl;
            cin >> rowInput; 
            rowInput -= 1; //Adjust size

            system("clear");

            if (rowInput < 0 || rowInput > 4) {
              cout << "CRITICAL ERROR" << endl;
              end = true;
              break;
            }
          }

          cout << endl;
          cout << "Do you accept placement? (Y/N)" << endl;
          cin >> choice;

          if (choice == 'Y' || choice == 'y') {
            cout << "PLACING CARRIER" << endl;
          } else if (choice == 'N' || choice == 'N') {
            cout << "What COLUMN do you want the ship in? (1 - 10)" << endl; 
            cin >> colInput;
            colInput -= 1; //Adjust size

            if (colInput < 0 || colInput > 9) {
              cout << "ERROR: Invalid number, try again: " << endl;
              cin >> colInput; 
              colInput -= 1; //Adjust size

              system("clear");

              if (colInput < 0 || colInput > 9) {
                cout << "CRITICAL ERROR" << endl;
                end = true;
                break;
              }
            }

            cout << "What ROW do you want the FRONT (Front facing up) of the ship in? (1 - 5)" << endl;
            cin >> rowInput;
            rowInput -= 1; //Adjust size

            if (rowInput < 0 || rowInput > 4) {
              cout << "ERROR: Invalid number, try again: " << endl;
              cin >> rowInput; 
              rowInput -= 1; //Adjust size

              system("clear");

              if (rowInput < 0 || rowInput > 4) {
                cout << "CRITICAL ERROR" << endl;
                end = true;
                break;
              }
            }

            board1[rowInput][colInput] = '|';
            board1[rowInput + 1][colInput] = '|';
            board1[rowInput + 2][colInput] = '|';
            board1[rowInput + 3][colInput] = '|';
            board1[rowInput + 4][colInput] = '|';
          }

          board1[rowInput][colInput] = '|';
          board1[rowInput + 1][colInput] = '|';
          board1[rowInput + 2][colInput] = '|';
          board1[rowInput + 3][colInput] = '|';
          board1[rowInput + 4][colInput] = '|';
        } else {
          break;
        }

        break;
      case 1:
        cout << "Will you like to place the battleship [4 PLACES] horizontally or vertically? (H/V)" << endl;
        cin >> choice;

        if (choice == 'H' || choice == 'h') {
          cout << "What ROW do you want the ship in? (1 - 10)" << endl; 
          cin >> rowInput;
          rowInput -= 1; //Adjust size

          if (rowInput < 0 || rowInput > 9) {
            cout << "ERROR: Invalid number, try again: " << endl;
            cin >> rowInput; 
            rowInput -= 1; //Adjust size

            system("clear");

            if (rowInput < 0 || rowInput > 9) {
              cout << "CRITICAL ERROR" << endl;
              end = true;
              break;
            }
          }

          cout << "What COLUMN do you want the FRONT (Facing right) of the ship in? (4 - 10)" << endl;
          cin >> colInput;
          colInput -= 1; //Adjust size

          if (colInput < 3 || colInput > 9) {
            cout << "ERROR: Invalid number, try again: " << endl;
            cin >> colInput; 
            colInput -= 1; //Adjust size

            system("clear");

            if (colInput < 3 || colInput > 9) {
              cout << "CRITICAL ERROR" << endl;
              end = true;
              break;
            }
          }

          cout << endl;
          cout << "Do you accept placement? (Y/N)" << endl;
          cin >> choice;

          if (choice == 'Y' || choice == 'y') {
            cout << "PLACING BATTLESHIP" << endl;
          } else if (choice == 'N' || choice == 'N') {
            cout << "What ROW do you want the ship in? (1 - 10)" << endl; 
            cin >> rowInput;
            rowInput -= 1; //Adjust size

            if (rowInput < 0 || rowInput > 9) {
              cout << "ERROR: Invalid number, try again: " << endl;
              cin >> rowInput; 
              rowInput -= 1; //Adjust size

              system("clear");

              if (rowInput < 0 || rowInput > 9) {
                cout << "CRITICAL ERROR" << endl;
                end = true;
                break;
              }
            }

            cout << "What COLUMN do you want the FRONT (Facing right) ship in? (4 - 10)" << endl;
            cin >> colInput;
            colInput -= 1; //Adjust size

            if (colInput < 3 || colInput > 9) {
              cout << "ERROR: Invalid number, try again: " << endl;
              cin >> colInput; 
              colInput -= 1; //Adjust size

              system("clear");

              if (colInput < 3 || colInput > 9) {
                cout << "CRITICAL ERROR" << endl;
                end = true;
                break;
              }
            }

            board1[rowInput][colInput] = '-';
            board1[rowInput][colInput - 1] = '-';
            board1[rowInput][colInput - 2] = '-';
            board1[rowInput][colInput - 3] = '-';
          }

          board1[rowInput][colInput] = '-';
          board1[rowInput][colInput - 1] = '-';
          board1[rowInput][colInput - 2] = '-';
          board1[rowInput][colInput - 3] = '-';
        } else if (choice == 'V' || choice == 'v') {
          cout << "What COLUMN do you want the ship in? (1 - 10)" << endl; 
          cin >> colInput;
          colInput -= 1; //Adjust size

          if (colInput < 0 || colInput > 9) {
            cout << "ERROR: Invalid number, try again: " << endl;
            cin >> colInput; 
            colInput -= 1; //Adjust size

            system("clear");

            if (colInput < 0 || colInput > 9) {
              cout << "CRITICAL ERROR" << endl;
              end = true;
              break;
            }
          }

          cout << "What ROW do you want the FRONT (Front facing up) of the ship in? (1 - 6)" << endl;
          cin >> rowInput;
          rowInput -= 1; //Adjust size

          if (rowInput < 0 || rowInput > 5) {
            cout << "ERROR: Invalid number, try again: " << endl;
            cin >> rowInput; 
            rowInput -= 1; //Adjust size

            system("clear");

            if (rowInput < 0 || rowInput > 5) {
              cout << "CRITICAL ERROR" << endl;
              end = true;
              break;
            }
          }

          cout << endl;
          cout << "Do you accept placement? (Y/N)" << endl;
          cin >> choice;

          if (choice == 'Y' || choice == 'y') {
            cout << "PLACING BATTLESHIP" << endl;
          } else if (choice == 'N' || choice == 'N') {
            cout << "What COLUMN do you want the ship in? (1 - 10)" << endl; 
            cin >> colInput;
            colInput -= 1; //Adjust size

            if (colInput < 0 || colInput > 9) {
              cout << "ERROR: Invalid number, try again: " << endl;
              cin >> colInput; 
              colInput -= 1; //Adjust size

              system("clear");

              if (colInput < 0 || colInput > 9) {
                cout << "CRITICAL ERROR" << endl;
                end = true;
                break;
              }
            }

            cout << "What ROW do you want the FRONT (Front facing up) of the ship in? (1 - 6)" << endl;
            cin >> rowInput;
            rowInput -= 1; //Adjust size

            if (rowInput < 0 || rowInput > 5) {
              cout << "ERROR: Invalid number, try again: " << endl;
              cin >> rowInput; 
              rowInput -= 1; //Adjust size

              system("clear");

              if (rowInput < 0 || rowInput > 5) {
                cout << "CRITICAL ERROR" << endl;
                end = true;
                break;
              }
            }

            board1[rowInput][colInput] = '|';
            board1[rowInput + 1][colInput] = '|';
            board1[rowInput + 2][colInput] = '|';
            board1[rowInput + 3][colInput] = '|';
          }

          board1[rowInput][colInput] = '|';
          board1[rowInput + 1][colInput] = '|';
          board1[rowInput + 2][colInput] = '|';
          board1[rowInput + 3][colInput] = '|';
        } else {
          break;
        } 

        break;
      case 2:
        cout << "Will you like to place the destroyer [3 PLACES] horizontally or vertically? (H/V)" << endl;
        cin >> choice;

        if (choice == 'H' || choice == 'h') {
          cout << "What ROW do you want the ship in? (1 - 10)" << endl; 
          cin >> rowInput;
          rowInput -= 1; //Adjust size

          if (rowInput < 0 || rowInput > 9) {
            cout << "ERROR: Invalid number, try again: " << endl;
            cin >> rowInput; 
            rowInput -= 1; //Adjust size

            system("clear");

            if (rowInput < 0 || rowInput > 9) {
              cout << "CRITICAL ERROR" << endl;
              end = true;
              break;
            }
          }

          cout << "What COLUMN do you want the FRONT (Facing right) of the ship in? (3 - 10)" << endl;
          cin >> colInput;
          colInput -= 1; //Adjust size

          if (colInput < 2 || colInput > 9) {
            cout << "ERROR: Invalid number, try again: " << endl;
            cin >> colInput; 
            colInput -= 1; //Adjust size

            system("clear");

            if (colInput < 2 || colInput > 9) {
              cout << "CRITICAL ERROR" << endl;
              end = true;
              break;
            }
          }

          cout << endl;
          cout << "Do you accept placement? (Y/N)" << endl;
          cin >> choice;

          if (choice == 'Y' || choice == 'y') {
            cout << "PLACING DESTROYER" << endl;
          } else if (choice == 'N' || choice == 'N') {
            cout << "What ROW do you want the ship in? (1 - 10)" << endl; 
            cin >> rowInput;
            rowInput -= 1; //Adjust size

            if (rowInput < 0 || rowInput > 9) {
              cout << "ERROR: Invalid number, try again: " << endl;
              cin >> rowInput; 
              rowInput -= 1; //Adjust size

              system("clear");

              if (rowInput < 0 || rowInput > 9) {
                cout << "CRITICAL ERROR" << endl;
                end = true;
                break;
              }
            }

            cout << "What COLUMN do you want the FRONT (Facing right) ship in? (3 - 10)" << endl;
            cin >> colInput;
            colInput -= 1; //Adjust size

            if (colInput < 2 || colInput > 9) {
              cout << "ERROR: Invalid number, try again: " << endl;
              cin >> colInput; 
              colInput -= 1; //Adjust size

              system("clear");

              if (colInput < 2 || colInput > 9) {
                cout << "CRITICAL ERROR" << endl;
                end = true;
                break;
              }
            }

            board1[rowInput][colInput] = '-';
            board1[rowInput][colInput - 1] = '-';
            board1[rowInput][colInput - 2] = '-';
          }

          board1[rowInput][colInput] = '-';
          board1[rowInput][colInput - 1] = '-';
          board1[rowInput][colInput - 2] = '-';
        } else if (choice == 'V' || choice == 'v') {
          cout << "What COLUMN do you want the ship in? (1 - 10)" << endl; 
          cin >> colInput;
          colInput -= 1; //Adjust size

          if (colInput < 0 || colInput > 9) {
            cout << "ERROR: Invalid number, try again: " << endl;
            cin >> colInput; 
            colInput -= 1; //Adjust size

            system("clear");

            if (colInput < 0 || colInput > 9) {
              cout << "CRITICAL ERROR" << endl;
              end = true;
              break;
            }
          }

          cout << "What ROW do you want the FRONT (Front facing up) of the ship in? (1 - 7)" << endl;
          cin >> rowInput;
          rowInput -= 1; //Adjust size

          if (rowInput < 0 || rowInput > 6) {
            cout << "ERROR: Invalid number, try again: " << endl;
            cin >> rowInput; 
            rowInput -= 1; //Adjust size

            system("clear");

            if (rowInput < 0 || rowInput > 6) {
              cout << "CRITICAL ERROR" << endl;
              end = true;
              break;
            }
          }

          cout << endl;
          cout << "Do you accept placement? (Y/N)" << endl;
          cin >> choice;

          if (choice == 'Y' || choice == 'y') {
            cout << "PLACING DESTROYER" << endl;
          } else if (choice == 'N' || choice == 'N') {
            cout << "What COLUMN do you want the ship in? (1 - 10)" << endl; 
            cin >> colInput;
            colInput -= 1; //Adjust size

            if (colInput < 0 || colInput > 9) {
              cout << "ERROR: Invalid number, try again: " << endl;
              cin >> colInput; 
              colInput -= 1; //Adjust size

              system("clear");

              if (colInput < 0 || colInput > 9) {
                cout << "CRITICAL ERROR" << endl;
                end = true;
                break;
              }
            }

            cout << "What ROW do you want the FRONT (Front facing up) of the ship in? (1 - 7)" << endl;
            cin >> rowInput;
            rowInput -= 1; //Adjust size

            if (rowInput < 0 || rowInput > 6) {
              cout << "ERROR: Invalid number, try again: " << endl;
              cin >> rowInput; 
              rowInput -= 1; //Adjust size

              system("clear");

              if (rowInput < 0 || rowInput > 6) {
                cout << "CRITICAL ERROR" << endl;
                end = true;
                break;
              }
            }

            board1[rowInput][colInput] = '|';
            board1[rowInput + 1][colInput] = '|';
            board1[rowInput + 2][colInput] = '|';
          }

          board1[rowInput][colInput] = '|';
          board1[rowInput + 1][colInput] = '|';
          board1[rowInput + 2][colInput] = '|';
        } else {
          break;
        }

        break;
      case 3:
        cout << "Will you like to place the submarine [3 PLACES] horizontally or vertically? (H/V)" << endl;
        cin >> choice;

        if (choice == 'H' || choice == 'h') {
          cout << "What ROW do you want the ship in? (1 - 10)" << endl; 
          cin >> rowInput;
          rowInput -= 1; //Adjust size

          if (rowInput < 0 || rowInput > 9) {
            cout << "ERROR: Invalid number, try again: " << endl;
            cin >> rowInput; 
            rowInput -= 1; //Adjust size

            system("clear");

            if (rowInput < 0 || rowInput > 9) {
              cout << "CRITICAL ERROR" << endl;
              end = true;
              break;
            }
          }

          cout << "What COLUMN do you want the FRONT (Facing right) of the ship in? (3 - 10)" << endl;
          cin >> colInput;
          colInput -= 1; //Adjust size

          if (colInput < 2 || colInput > 9) {
            cout << "ERROR: Invalid number, try again: " << endl;
            cin >> colInput; 
            colInput -= 1; //Adjust size

            system("clear");

            if (colInput < 2 || colInput > 9) {
              cout << "CRITICAL ERROR" << endl;
              end = true;
              break;
            }
          }

          cout << endl;
          cout << "Do you accept placement? (Y/N)" << endl;
          cin >> choice;

          if (choice == 'Y' || choice == 'y') {
            cout << "PLACING SUBMARINE" << endl;
          } else if (choice == 'N' || choice == 'N') {
            cout << "What ROW do you want the ship in? (1 - 10)" << endl; 
            cin >> rowInput;
            rowInput -= 1; //Adjust size

            if (rowInput < 0 || rowInput > 9) {
              cout << "ERROR: Invalid number, try again: " << endl;
              cin >> rowInput; 
              rowInput -= 1; //Adjust size

              system("clear");

              if (rowInput < 0 || rowInput > 9) {
                cout << "CRITICAL ERROR" << endl;
                end = true;
                break;
              }
            }

            cout << "What COLUMN do you want the FRONT (Facing right) ship in? (3 - 10)" << endl;
            cin >> colInput;
            colInput -= 1; //Adjust size

            if (colInput < 2 || colInput > 9) {
              cout << "ERROR: Invalid number, try again: " << endl;
              cin >> colInput; 
              colInput -= 1; //Adjust size

              system("clear");

              if (colInput < 2 || colInput > 9) {
                cout << "CRITICAL ERROR" << endl;
                end = true;
                break;
              }
            }

            board1[rowInput][colInput] = '-';
            board1[rowInput][colInput - 1] = '-';
            board1[rowInput][colInput - 2] = '-';
          }

          board1[rowInput][colInput] = '-';
          board1[rowInput][colInput - 1] = '-';
          board1[rowInput][colInput - 2] = '-';
        } else if (choice == 'V' || choice == 'v') {
          cout << "What COLUMN do you want the ship in? (1 - 10)" << endl; 
          cin >> colInput;
          colInput -= 1; //Adjust size

          if (colInput < 0 || colInput > 9) {
            cout << "ERROR: Invalid number, try again: " << endl;
            cin >> colInput; 
            colInput -= 1; //Adjust size

            system("clear");

            if (colInput < 0 || colInput > 9) {
              cout << "CRITICAL ERROR" << endl;
              end = true;
              break;
            }
          }

          cout << "What ROW do you want the FRONT (Front facing up) of the ship in? (1 - 7)" << endl;
          cin >> rowInput;
          rowInput -= 1; //Adjust size

          if (rowInput < 0 || rowInput > 6) {
            cout << "ERROR: Invalid number, try again: " << endl;
            cin >> rowInput; 
            rowInput -= 1; //Adjust size

            system("clear");

            if (rowInput < 0 || rowInput > 6) {
              cout << "CRITICAL ERROR" << endl;
              end = true;
              break;
            }
          }

          cout << endl;
          cout << "Do you accept placement? (Y/N)" << endl;
          cin >> choice;

          if (choice == 'Y' || choice == 'y') {
            cout << "PLACING SUBMARINE" << endl;
          } else if (choice == 'N' || choice == 'N') {
            cout << "What COLUMN do you want the ship in? (1 - 10)" << endl; 
            cin >> colInput;
            colInput -= 1; //Adjust size

            if (colInput < 0 || colInput > 9) {
              cout << "ERROR: Invalid number, try again: " << endl;
              cin >> colInput; 
              colInput -= 1; //Adjust size

              system("clear");

              if (colInput < 0 || colInput > 9) {
                cout << "CRITICAL ERROR" << endl;
                end = true;
                break;
              }
            }

            cout << "What ROW do you want the FRONT (Front facing up) of the ship in? (1 - 7)" << endl;
            cin >> rowInput;
            rowInput -= 1; //Adjust size

            if (rowInput < 0 || rowInput > 6) {
              cout << "ERROR: Invalid number, try again: " << endl;
              cin >> rowInput; 
              rowInput -= 1; //Adjust size

              system("clear");

              if (rowInput < 0 || rowInput > 6) {
                cout << "CRITICAL ERROR" << endl;
                end = true;
                break;
              }
            }

            board1[rowInput][colInput] = '|';
            board1[rowInput + 1][colInput] = '|';
            board1[rowInput + 2][colInput] = '|';
          }

          board1[rowInput][colInput] = '|';
          board1[rowInput + 1][colInput] = '|';
          board1[rowInput + 2][colInput] = '|';
        } else {
          break;
        }
        break;
      case 4:
        cout << "Will you like to place the patrol boat [2 PLACES] horizontally or vertically? (H/V)" << endl;
        cin >> choice;

        if (choice == 'H' || choice == 'h') {
          cout << "What ROW do you want the ship in? (1 - 10)" << endl; 
          cin >> rowInput;
          rowInput -= 1; //Adjust size

          if (rowInput < 0 || rowInput > 9) {
            cout << "ERROR: Invalid number, try again: " << endl;
            cin >> rowInput; 
            rowInput -= 1; //Adjust size

            system("clear");

            if (rowInput < 0 || rowInput > 9) {
              cout << "CRITICAL ERROR" << endl;
              end = true;
              break;
            }
          }

          cout << "What COLUMN do you want the FRONT (Facing right) of the ship in? (2 - 10)" << endl;
          cin >> colInput;
          colInput -= 1; //Adjust size

          if (colInput < 1 || colInput > 9) {
            cout << "ERROR: Invalid number, try again: " << endl;
            cin >> colInput; 
            colInput -= 1; //Adjust size

            system("clear");

            if (colInput < 1 || colInput > 9) {
              cout << "CRITICAL ERROR" << endl;
              end = true;
              break;
            }
          }

          cout << endl;
          cout << "Do you accept placement? (Y/N)" << endl;
          cin >> choice;

          if (choice == 'Y' || choice == 'y') {
            cout << "PLACING PATROL BOAT" << endl;
          } else if (choice == 'N' || choice == 'N') {
            cout << "What ROW do you want the ship in? (1 - 10)" << endl; 
            cin >> rowInput;
            rowInput -= 1; //Adjust size

            if (rowInput < 0 || rowInput > 9) {
              cout << "ERROR: Invalid number, try again: " << endl;
              cin >> rowInput; 
              rowInput -= 1; //Adjust size

              system("clear");

              if (rowInput < 0 || rowInput > 9) {
                cout << "CRITICAL ERROR" << endl;
                end = true;
                break;
              }
            }

            cout << "What COLUMN do you want the FRONT (Facing right) ship in? (2 - 10)" << endl;
            cin >> colInput;
            colInput -= 1; //Adjust size

            if (colInput < 1 || colInput > 9) {
              cout << "ERROR: Invalid number, try again: " << endl;
              cin >> colInput; 
              colInput -= 1; //Adjust size

              system("clear");

              if (colInput < 1 || colInput > 9) {
                cout << "CRITICAL ERROR" << endl;
                end = true;
                break;
              }
            }

            board1[rowInput][colInput] = '-';
            board1[rowInput][colInput - 1] = '-';
          }

          board1[rowInput][colInput] = '-';
          board1[rowInput][colInput - 1] = '-';
        } else if (choice == 'V' || choice == 'v') {
          cout << "What COLUMN do you want the ship in? (1 - 10)" << endl; 
          cin >> colInput;
          colInput -= 1; //Adjust size

          if (colInput < 0 || colInput > 9) {
            cout << "ERROR: Invalid number, try again: " << endl;
            cin >> colInput; 
            colInput -= 1; //Adjust size

            system("clear");

            if (colInput < 0 || colInput > 9) {
              cout << "CRITICAL ERROR" << endl;
              end = true;
              break;
            }
          }

          cout << "What ROW do you want the FRONT (Front facing up) of the ship in? (1 - 8)" << endl;
          cin >> rowInput;
          rowInput -= 1; //Adjust size

          if (rowInput < 0 || rowInput > 7) {
            cout << "ERROR: Invalid number, try again: " << endl;
            cin >> rowInput; 
            rowInput -= 1; //Adjust size

            system("clear");

            if (rowInput < 0 || rowInput > 7) {
              cout << "CRITICAL ERROR" << endl;
              end = true;
              break;
            }
          }

          cout << endl;
          cout << "Do you accept placement? (Y/N)" << endl;
          cin >> choice;

          if (choice == 'Y' || choice == 'y') {
            cout << "PLACING PATROL BOAT" << endl;
          } else if (choice == 'N' || choice == 'N') {
            cout << "What COLUMN do you want the ship in? (1 - 10)" << endl; 
            cin >> colInput;
            colInput -= 1; //Adjust size

            if (colInput < 0 || colInput > 9) {
              cout << "ERROR: Invalid number, try again: " << endl;
              cin >> colInput; 
              colInput -= 1; //Adjust size

              system("clear");

              if (colInput < 0 || colInput > 9) {
                cout << "CRITICAL ERROR" << endl;
                end = true;
                break;
              }
            }

            cout << "What ROW do you want the FRONT (Front facing up) of the ship in? (1 - 8)" << endl;
            cin >> rowInput;
            rowInput -= 1; //Adjust size

            if (rowInput < 0 || rowInput > 7) {
              cout << "ERROR: Invalid number, try again: " << endl;
              cin >> rowInput; 
              rowInput -= 1; //Adjust size

              system("clear");

              if (rowInput < 0 || rowInput > 7) {
                cout << "CRITICAL ERROR" << endl;
                end = true;
                break;
              }
            }

            board1[rowInput][colInput] = '|';
            board1[rowInput + 1][colInput] = '|';
          }

          board1[rowInput][colInput] = '|';
          board1[rowInput + 1][colInput] = '|';
        } else {
          break;
        } 

        break;
      default:
        end = true;
        break;
    }

    p++;

    system("clear");
  }
}

void carrierPlacement(char (&board2)[rowSize][colSize], shipEntity_computer& computerCarrier) {
  srand(time(NULL));

  int a;
  int b;

  int orientation = rand() % 2;

  if (orientation == 0) {
    a = rand() % 10;
    b = rand() % 5;

    board2[a][b] = '-';
    board2[a][b - 1] = '-';
    board2[a][b - 2] = '-';
    board2[a][b - 3] = '-';
    board2[a][b - 4] = '-';

    computerCarrier.positionsComputer[a][b] = '-';
    computerCarrier.positionsComputer[a][b - 1] = '-';
    computerCarrier.positionsComputer[a][b - 2] = '-';
    computerCarrier.positionsComputer[a][b - 3] = '-';
    computerCarrier.positionsComputer[a][b - 4] = '-';
  } else if (orientation == 1) {
    a = rand() % 5;
    b = rand() % 10;

    board2[a][b] = '|';
    board2[a + 1][b] = '|';
    board2[a + 2][b] = '|';
    board2[a + 3][b] = '|';
    board2[a + 4][b] = '|';

    computerCarrier.positionsComputer[a][b] = '|';
    computerCarrier.positionsComputer[a + 1][b] = '|';
    computerCarrier.positionsComputer[a + 2][b] = '|';
    computerCarrier.positionsComputer[a + 3][b] = '|';
    computerCarrier.positionsComputer[a + 4][b] = '|';
  }
}

void battleshipPlacement(char (&board2)[rowSize][colSize], shipEntity_computer& computerBattleship) {
  srand(time(NULL));

  int a;
  int b;

  int orientation = rand() % 2;

  if (orientation == 0) {
    a = rand() % 10;
    b = rand() % 5;

    if (board2[a][b] == '#' && board2[a][b - 1] == '#' && board2[a][b - 2] == '#' && board2[a][b - 3] == '#') {
      board2[a][b] = '-';
      board2[a][b - 1] = '-';
      board2[a][b - 2] = '-';
      board2[a][b - 3] = '-';

      computerBattleship.positionsComputer[a][b] = '-';
      computerBattleship.positionsComputer[a][b - 1] = '-';
      computerBattleship.positionsComputer[a][b - 2] = '-';
      computerBattleship.positionsComputer[a][b - 3] = '-';
    } else {
      battleshipPlacement(board2, computerBattleship);
    }
  } else if (orientation == 1) {
    a = rand() % 5;
    b = rand() % 10;

    if (board2[a][b] == '#' && board2[a + 1][b] == '#' && board2[a + 2][b] == '#' && board2[a + 3][b] == '#') {
      board2[a][b] = '|';
      board2[a + 1][b] = '|';
      board2[a + 2][b] = '|';
      board2[a + 3][b] = '|';

      computerBattleship.positionsComputer[a][b] = '|';
      computerBattleship.positionsComputer[a + 1][b] = '|';
      computerBattleship.positionsComputer[a + 2][b] = '|';
      computerBattleship.positionsComputer[a + 3][b] = '|';
    } else {
      battleshipPlacement(board2, computerBattleship);
    }
  }
}
 
void destroyerPlacement(char (&board2)[rowSize][colSize], shipEntity_computer& computerDestroyer) {
  srand(time(NULL));

  int a;
  int b;

  int orientation = rand() % 2;

  if (orientation == 0) {
    a = rand() % 10;
    b = rand() % 5;

    if (board2[a][b] == '#' && board2[a][b - 1] == '#' && board2[a][b - 2] == '#') {
      board2[a][b] = '-';
      board2[a][b - 1] = '-';
      board2[a][b - 2] = '-';

      computerDestroyer.positionsComputer[a][b] = '-';
      computerDestroyer.positionsComputer[a][b - 1] = '-';
      computerDestroyer.positionsComputer[a][b - 2] = '-';
    } else {
      destroyerPlacement(board2, computerDestroyer);
    }
  } else if (orientation == 1) {
    a = rand() % 5;
    b = rand() % 10;

    if (board2[a][b] == '#' && board2[a + 1][b] == '#' && board2[a + 2][b] == '#') {
      board2[a][b] = '|';
      board2[a + 1][b] = '|';
      board2[a + 2][b] = '|';

      computerDestroyer.positionsComputer[a][b] = '|';
      computerDestroyer.positionsComputer[a + 1][b] = '|';
      computerDestroyer.positionsComputer[a + 2][b] = '|';
    } else {
      destroyerPlacement(board2, computerDestroyer);
    }
  }
}

void submarinePlacement(char (&board2)[rowSize][colSize], shipEntity_computer& computerSubmarine) {
  srand(time(NULL));

  int a;
  int b;

  int orientation = rand() % 2;

  if (orientation == 0) {
    a = rand() % 10;
    b = rand() % 5;

    if (board2[a][b] == '#' && board2[a][b - 1] == '#' && board2[a][b - 2] == '#') {
      board2[a][b] = '-';
      board2[a][b - 1] = '-';
      board2[a][b - 2] = '-';
      computerSubmarine.positionsComputer[a][b] = '-';
      computerSubmarine.positionsComputer[a][b - 1] = '-';
      computerSubmarine.positionsComputer[a][b - 2] = '-';
    } else {
      submarinePlacement(board2, computerSubmarine);
    }
  } else if (orientation == 1) {
    a = rand() % 5;
    b = rand() % 10;

    if (board2[a][b] == '#' && board2[a + 1][b] == '#' && board2[a + 2][b] == '#') {
      board2[a][b] = '|';
      board2[a + 1][b] = '|';
      board2[a + 2][b] = '|';

      computerSubmarine.positionsComputer[a][b] = '|';
      computerSubmarine.positionsComputer[a + 1][b] = '|';
      computerSubmarine.positionsComputer[a + 2][b] = '|';
    } else {
      submarinePlacement(board2, computerSubmarine);
    }
  }
}

void patrolPlacement(char (&board2)[rowSize][colSize], shipEntity_computer& computerPT) {
  srand(time(NULL));

  int a;
  int b;

  int orientation = rand() % 2;

  if (orientation == 0) {
    a = rand() % 10;
    b = rand() % 5;

    if (board2[a][b] == '#' && board2[a][b - 1] == '#') {
      board2[a][b] = '-';
      board2[a][b - 1] = '-';

      computerPT.positionsComputer[a][b] = '-';
      computerPT.positionsComputer[a][b - 1] = '-';
    } else {
      patrolPlacement(board2, computerPT);
    }
  } else if (orientation == 1) {
    a = rand() % 5;
    b = rand() % 10;

    if (board2[a][b] == '#' && board2[a + 1][b] == '#') {
      board2[a][b] = '|';
      board2[a + 1][b] = '|';

      computerPT.positionsComputer[a][b] = '|';
      computerPT.positionsComputer[a + 1][b] = '|';
    } else {
      patrolPlacement(board2, computerPT);
    }
  }
}

void computerHitCheck(char (&board2)[rowSize][colSize], int inputR, int inputC, int& computer_totalHP, shipEntity_computer& computerCarrier, shipEntity_computer computerBattleship, shipEntity_computer& computerDestroyer, shipEntity_computer& computerSubmarine, shipEntity_computer& computerPT) {
  cout << "It's your turn: " << endl;
  cout << endl;

  cout << "Input a row value (1 - 10): ";
  cin >> inputR;
  cout << endl;

  cout << "Input a column value (1 - 10): ";
  cin >> inputC;
  cout << endl;
  
  if ((inputR < 1 || inputR > 10) || (inputC < 1 || inputC > 10)) {
    cout << "BAD INPUT, WAIT FOR RETRY" << endl;

    this_thread::sleep_for(chrono::seconds(2));

    system("clear");

    computerHitCheck(board2, inputR, inputC, computer_totalHP, computerCarrier, computerBattleship, computerDestroyer, computerSubmarine, computerPT);
  } 

  if ((board2[inputR][inputC] == '-' && computerCarrier.positionsComputer[inputR][inputC] == '-') || (board2[inputR][inputC] == '|' && computerCarrier.positionsComputer[inputR][inputC] == '|')) {
    cout << "Hit!" << endl;

    board2[inputR][inputC] = 'X';
    computerCarrier.positionsComputer[inputR][inputC] = 'X';
    computerCarrier.c_hp -= 1;
    computer_totalHP -= 1;

    if (computerCarrier.c_hp == 0) {
      computerCarrier.c_isDead = true;
    }
  } else if ((board2[inputR][inputC] == '-' && computerBattleship.positionsComputer[inputR][inputC] == '-') || (board2[inputR][inputC] == '|' && computerBattleship.positionsComputer[inputR][inputC] == '|')) {
    cout << "Hit!" << endl;

    board2[inputR][inputC] = 'X';
    computerBattleship.positionsComputer[inputR][inputC] = 'X';
    computerBattleship.c_hp -= 1;
    computer_totalHP -= 1;

    if (computerBattleship.c_hp == 0) {
      computerBattleship.c_isDead = true;
    }
  } else if ((board2[inputR][inputC] == '-' && computerDestroyer.positionsComputer[inputR][inputC] == '-') || (board2[inputR][inputC] == '|' && computerDestroyer.positionsComputer[inputR][inputC] == '|')) {
    cout << "Hit!" << endl;

    board2[inputR][inputC] = 'X';
    computerDestroyer.positionsComputer[inputR][inputC] = 'X';
    computerDestroyer.c_hp -= 1;
    computer_totalHP -= 1;

    if (computerDestroyer.c_hp == 0) {
      computerDestroyer.c_isDead = true;
    }
  } else if ((board2[inputR][inputC] == '-' && computerSubmarine.positionsComputer[inputR][inputC] == '-') || (board2[inputR][inputC] == '|' && computerSubmarine.positionsComputer[inputR][inputC] == '|')) {
    cout << "Hit!" << endl;

    board2[inputR][inputC] = 'X';
    computerSubmarine.positionsComputer[inputR][inputC] = 'X';
    computerSubmarine.c_hp -= 1;
    computer_totalHP -= 1;

    if (computerSubmarine.c_hp == 0) {
      computerSubmarine.c_isDead = true;
    }
  } else if ((board2[inputR][inputC] == '-' && computerPT.positionsComputer[inputR][inputC] == '-') || (board2[inputR][inputC] == '|' && computerPT.positionsComputer[inputR][inputC] == '|')) {
    cout << "Hit!" << endl;

    board2[inputR][inputC] = 'X';
    computerPT.positionsComputer[inputR][inputC] = 'X';
    computerPT.c_hp -= 1;
    computer_totalHP -= 1;

    if (computerPT.c_hp == 0) {
      computerPT.c_isDead = true;
    }
  } else if (board2[inputR][inputC] == '#') {
    cout << "Miss!" << endl; 
  } else if (board2[inputR][inputC] == 'X' || board2[inputR][inputC] == 'O') {
    cout << "Already hit here, try again" << endl;

    this_thread::sleep_for(chrono::seconds(1));

    system("clear");

    computerHitCheck(board2, inputR, inputC, computer_totalHP, computerCarrier, computerBattleship, computerDestroyer, computerSubmarine, computerPT);
  }
}
