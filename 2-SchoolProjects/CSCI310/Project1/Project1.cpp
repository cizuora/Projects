#include <stdio.h>
#include <iostream>
#include <pthread.h>
#include <unistd.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>
#include <vector>

using namespace std;

// Game state
char board[3][3];
pthread_mutex_t board_mutex;
bool game_over = false;
char winner = ' ';

// Function to initialize the board
void init_board() {
    for(int i = 0; i < 3; i++) {
        for(int j = 0; j < 3; j++) {
            board[i][j] = ' ';
        }
    }
}

// Function to print the board
void print_board() {
    cout << "\n=== Current Board ===" << endl;
    cout << "  0   1   2" << endl;
    for (int i = 0; i < 3; i++) {
        cout << i << " ";
        for (int j = 0; j < 3; j++) {
            cout << board[i][j];
            if (j < 2) cout << " | ";
        }
        cout << endl;
        if (i < 2) cout << "  ---------" << endl;
    }
    cout << "===================\n" << endl;
}

// Function to check if player has won
bool check_winner(char player) { // NEED TO ADD PLAYER FOR CHECKING
    // check rows
    for(int i = 0; i < 3; i++) {
        if(board[i][0] == player && board[i][1] == player && board[i][2] == player) {
            return true;
        }
    }

    // check columns
    for(int j = 0; j < 3; j++) {
        if(board[0][j] == player && board[1][j] == player && board[2][j] == player) {
            return true;
        }
    }

    // check diagnals
    if(board[0][0] == player && board[1][1] == player && board[2][2] == player) {
        return true;
    }
    if(board[0][2] == player && board[1][1] == player && board[2][0] == player) {
        return true;
    }

    return false;
}

// Function to check if board is full (there is a draw)
bool is_board_full() {
    for(int i = 0; i < 3; i++) {
        for(int j = 0; j < 3; j++) {
            if(board[i][j] == ' ') {
                return false;
            }
        }
    }

    return true;
}

// Function to find available moves
vector<pair<int,int>> get_available_moves() {
    vector<pair<int,int>> moves;

    for(int i = 0; i < 3; i++) {
        for(int j = 0; j < 3; j++) {
            if(board[i][j] == ' ') {
                moves.push_back(make_pair(i,j));
            }
        }
    }

    return moves;
}

// Function for player threads
void* player_thread(void* arg) {
    char player = *(char*)arg;

    while(true) {
        pthread_mutex_lock(&board_mutex);

        if(game_over) {
            pthread_mutex_unlock(&board_mutex);
            break;
        }

        vector<pair<int,int>> available_moves = get_available_moves();

        if(available_moves.empty()) {
            game_over = true;
            winner = 'D'; // Draw
            cout << "Game ended in a draw!" << endl;
            pthread_mutex_unlock(&board_mutex);
            break;
        }

        int random_index = rand() % available_moves.size();
        int row = available_moves[random_index].first;
        int col = available_moves[random_index].second;

        board[row][col] = player;

        cout << "Player " << player << " makes a move at (" << row << ", " << col << ")" << endl;

        print_board();

        if(check_winner(player)) {
            game_over = true;
            winner = player;
            cout << "\n*** Player " << player << " Wins! ***\n" << endl;
            pthread_mutex_unlock(&board_mutex);
            break;
        }

        if(is_board_full()) {
            game_over = true;
            winner = 'D'; // Draw
            cout << "\n*** Game ended in a Draw! ***\n" << endl;
            pthread_mutex_unlock(&board_mutex);
            break;
        }

        pthread_mutex_unlock(&board_mutex);

        // Add short delay for personal preferance
        usleep(500000); // 0.5 seconds
    }

    return NULL;
}

int main() {
    srand(time(NULL));

    init_board();

    pthread_mutex_init(&board_mutex, NULL);

    char player_x = 'X';
    char player_o = 'O';

    pthread_t thread_x, thread_o;

    cout << "Starting Tic-Tac-Toe Game with 2 Threads" << endl;
    print_board();

    pthread_create(&thread_x, NULL, player_thread, &player_x);
    pthread_create(&thread_o, NULL, player_thread, &player_o);

    pthread_join(thread_x, NULL);
    pthread_join(thread_o, NULL);

    cout << "\n=== Game Over ==="  << endl;
    if(winner == 'D') {
        cout << "Result: Draw" << endl;
    } else {
        cout << "Result: Player " << winner << endl;
    }

    pthread_mutex_destroy(&board_mutex);

    return 0;
}