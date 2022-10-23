#include <iostream>
using namespace std;

int n, m;
char board[256][256];
bool doorAccess = false;

struct PlayerAndFinishCoords {
    int x, y;
} Player, Finish;

int main() {
    cout << "\t\t\tWelcome to REACH THE FINISH\n\n";
    cout << "Help Arnold to get to the finish!\n\n";

    cout << "Create your own board using the elements below (make sure you include only one A, F and K (in case there's any D), and respect the dimensions of the board):\n";
    cout << "A = Arnold\n" << "F = finish\n" << ". = path\n" << "X = wall\n" << "D = door\n" << "K = key\n\n";

    cout << "After you're done, hit enter and get Arnold to the finish using the following controls:\n";
    cout << "A/a = move left\n" << "S/s = move down\n" << "W/w = move up\n" << "D/d = move right\n\n";
    cout << "HAVE FUN!!!\n";

    bool good = 0;
    do {
        cout << "Enter the number of rows: ";
        cin >> n;
        cout << "Enter the number of columns: ";
        cin >> m;
        cout << "Create your board and then press any of your controls to start:\n";

        for (int i = 0; i < n; ++i)
            for (int j = 0; j < m; ++j) {
                cin >> board[i][j];
                if (board[i][j] == 'A') {
                    Player.x = i;
                    Player.y = j;
                }
                if (board[i][j] == 'F') {
                    Finish.x = i;
                    Finish.y = j;
                }
            }

        int goods = 0, doorGood = 0;
        for (int i = 0; i < n; ++i)
            for (int j = 0; j < m; ++j) {
                if (board[i][j] == 'A') ++goods;
                if (board[i][j] == 'F') ++goods;
                if (board[i][j] == 'D') doorGood = 1;
                if (board[i][j] == 'K') ++goods;
            }
        if ((doorGood == 1 && goods == 3) || (doorGood == 0 && goods == 2)) good = 1;
        else cout << "You forgot to add something to your board or you added something extra. Read the rules and create the board again!\n";
    } while (!good);

    //Gameplay (making it move)
    while (Player.x != Finish.x || Player.y != Finish.y) {
        char command;
        cout << "Enter command and hit enter: ";
        cin >> command;
        system("cls");
        if (command == 'A' || command == 'a') { //LEFT
            Player.y--; //moving left

            //leaving the board
            if (Player.y < 0) {
                Player.y++;
                cout << "Out of bounds!\n";
            }

            //hitting a wall
            if (board[Player.x][Player.y] == 'X') {
                Player.y++;
                cout << "You've hit a wall!\n";
            }

            //hitting the door
            if (board[Player.x][Player.y] == 'D' && doorAccess == false) {
                Player.y++;
                cout << "The door is locked!\n";
            }

        }
        else if (command == 'W' || command == 'w') { //UP
            Player.x--; //moving up

            //leaving the board
            if (Player.x < 0) {
                Player.x++;
                cout << "Out of bounds!\n";
            }

            //hitting a wall
            if (board[Player.x][Player.y] == 'X') {
                Player.x++;
                cout << "You've hit a wall\n";
            }

            //hitting the door
            if (board[Player.x][Player.y] == 'D' && doorAccess == false) {
                Player.x++;
                cout << "The door is locked!\n";
            }

        }
        else if (command == 'S' || command == 's') { //DOWN
            Player.x++; //moving down

            //leaving the board
            if (Player.x > n - 1) {
                Player.x--;
                cout << "Out of bounds!\n";
            }

            //hitting a wall
            if (board[Player.x][Player.y] == 'X') {
                Player.x--;
                cout << "You've hit a wall\n";
            }

            //hitting the door
            if (board[Player.x][Player.y] == 'D' && doorAccess == false) {
                Player.x--;
                cout << "The door is locked!\n";
            }

        }
        else if (command == 'D' || command == 'd') { //RIGHT
            Player.y++; //moving right

            //leaving the board
            if (Player.y > m - 1) {
                Player.y--;
                cout << "Out of bounds!\n";
            }

            //hitting a wall
            if (board[Player.x][Player.y] == 'X') {
                Player.y--;
                cout << "You've hit a wall\n";
            }

            //hitting the door
            if (board[Player.x][Player.y] == 'D' && doorAccess == false) {
                Player.y--;
                cout << "The door is locked!\n";
            }

        }
        else {
            cout << "Invalid command!\n";
        }

        //taking the key
        if (board[Player.x][Player.y] == 'K')
            doorAccess = true;

        //analysing the board in order to move the player
        for (int i = 0; i < n; ++i)
            for (int j = 0; j < m; ++j) {
                if (board[i][j] == 'A')
                    board[i][j] = '.';
                if (i == Player.x && j == Player.y)
                    board[i][j] = 'A';
            }

        //displaying the board
        for (int i = 0; i < n; ++i) {
            for (int j = 0; j < m; ++j)
                cout << board[i][j];
            cout << '\n';
        }
        cout << '\n';
    }

    cout << "CONGRATULATIONS, YOU'VE WON!!!\n";
    return 0;
}