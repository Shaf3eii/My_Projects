#include <iostream>
#include <graphics.h>
#include <string>
#include <conio.h>

void movetank1up();
void movetank1down();
void movetank1right();
void movetank1left();
void movetank2up();
void movetank2down();
void movetank2left();
void movetank2right();

using namespace std;

// Ma7mod Sala7 Elshaf3y

string pieces[9] = {
        "images/brick.ico", //0
        "images/tank_down_g.ico", //1 green tank down
        "images/tank_left_g.ico", //2
        "images/tank_right_g.ico", //3
        "images/tank_up_g.ico", //4
        "images/tank_down_y.ico", //5 yellow tank down
        "images/tank_left_y.ico", //6
        "images/tank_right_y.ico", //7
        "images/tank_up_y.ico" //8
};

const int BOARD_WIDTH = 30;
const int BOARD_HEIGHT = 30;
int tank1_row = 28;
int tank1_col = 15;
int tank2_row = 3;
int tank2_col = 15;
int board[BOARD_HEIGHT][BOARD_WIDTH] = {
        {0, 0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0, 0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0},
        {0, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, 5, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, 0},
        {0, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, 5, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, 0},
        {0, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, 5, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, 0},
        {0, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, 5, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, 0},
        {0, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, 5, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, 0},
        {0, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, 5, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, 0},
        {0, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, 5, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, 0},
        {0, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, 5, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, 0},
        {0, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, 5, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, 0},
        {0, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, 5, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, 0},
        {0, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, 5, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, 0},
        {0, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, 5, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, 0},
        {0, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, 5, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, 0},
        {0, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, 5, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, 0},
        {0, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, 5, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, 0},
        {0, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, 5, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, 0},
        {0, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, 5, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, 0},
        {0, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, 5, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, 0},
        {0, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, 5, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, 0},
        {0, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, 5, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, 0},
        {0, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, 5, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, 0},
        {0, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, 5, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, 0},
        {0, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, 5, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, 0},
        {0, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, 5, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, 0},
        {0, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, 5, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, 0},
        {0, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, 5, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, 0},
        {0, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, 5, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, 0},
        {0, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, 5, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, 0},
        {0, 0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0, 0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0},
};

const int w = 16;
const int h = 16;
const int OFFSET_X = 0;
const int OFFSET_Y = 0;

void draw() {
    cleardevice(); // Clear the device

    for (int i = 0; i < BOARD_HEIGHT; i++) {
        for (int x = 0; x < BOARD_WIDTH; x++) {
            int x1 = OFFSET_X + x * w;
            int x2 = x1 + w;
            int y1 = OFFSET_Y + i * h;
            int y2 = y1 + h;

            if (board[i][x] != -1) {
                int n = board[i][x];
                readimagefile(pieces[n].c_str(), x1, y1, x2, y2);
            }
        }
    }
}

bool IsEscape() {
    if (kbhit()) {
        char c = getch();
        if (c == 27)
            return true;
    }
    return false;
}

void movetank1up() {
    board[tank1_row][tank1_col] = -1;
    tank1_row--;
    board[tank1_row][tank1_col] = 4;
    draw();
}

void movetank1down() {
    board[tank1_row][tank1_col] = -1;
    tank1_row++;
    board[tank1_row][tank1_col] = 1;
    draw();
}

void movetank1left() {
    board[tank1_row][tank1_col] = -1;
    tank1_col--;
    board[tank1_row][tank1_col] = 2;
    draw();
}

void movetank1right() {
    board[tank1_row][tank1_col] = -1;
    tank1_col++;
    board[tank1_row][tank1_col] = 3;
    draw();
}

void movetank2up() {
    board[tank2_row][tank2_col] = -1;
    tank2_row--;
    board[tank2_row][tank2_col] = 8;
    draw();
}

void movetank2down() {
    board[tank2_row][tank2_col] = -1;
    tank2_row++;
    board[tank2_row][tank2_col] = 5;
    draw();
}

void movetank2left() {
    board[tank2_row][tank2_col] = -1;
    tank2_col--;
    board[tank2_row][tank2_col] = 6;
    draw();
}

void movetank2right() {
    board[tank2_row][tank2_col] = -1;
    tank2_col++;
    board[tank2_row][tank2_col] = 7;
    draw();
}


int main() {
    initwindow(480, 480, "Battle Tank", 100, 150);
    setbkcolor(BLACK);
    cleardevice();
    draw();
    while (!IsEscape()) {
        if (kbhit()) {
            char c = getch();
            switch (c) {
                case 27: // مفتاح "Esc"
                    exit(0);
                    break;
                case KEY_UP:
                    movetank1up();
                    break;
                case KEY_DOWN:
                    movetank1down();
                    break;
                case KEY_RIGHT:
                    movetank1right();
                    break;
                case KEY_LEFT:
                    movetank1left();
                    break;
                case 'w':
                    movetank2up();
                    break;
                case 's':
                    movetank2down();
                    break;
                case 'd':
                    movetank2right();
                    break;
                case 'a':
                    movetank2left();
                    break;
            }
        }
    }

    return 0;
}
