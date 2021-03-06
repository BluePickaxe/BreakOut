#include <stdio.h>
#include <Windows.h>
#include <conio.h>
#include <stdbool.h>
#include <process.h>
#include <time.h>

#define ROW 101
#define COLUMN 25

#define LEFT 75
#define RIGHT 77

#define LU 1
#define RU 2
#define LD 3
#define RD 4

char board[COLUMN][ROW];

boolean is_started = false;
boolean is_finished = false;
int bar_pos = 50;
int ballX = 50;
int ballY = 23;
int balldir = RU;

void gotoxy(int x, int y){
	COORD Pos = {x + 1, y + 2}; // 테두리와 처음 설명 부분 감안 
	SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), Pos);
}

void move_ball(){
	if(ballY == 0){
		if(balldir == LU){ // 위쪽 벽에 부딪힐때 
			balldir = LD;
		} else if(balldir == RU){
			balldir = RD;
		}
	} else if(ballX == 0){ // 왼쪽 벽에 부딪힐때 
		if(balldir == LU){
			balldir = RU;
		} else if(balldir == LD){
			balldir = RD;
		}
	} else if(ballX == 100){ // 오른쪽 벽에 부딪힐때 
		if(balldir == RD){
			balldir = LD;
		} else if(balldir == RU){
			balldir = LU;
		}
	} else if(board[ballY-1][ballX] == '#'){
		if(balldir == LU){ // 위쪽 벽에 부딪힐때 
			balldir = LD;
			board[ballY-1][ballX] = ' ';
			gotoxy(ballX, ballY-1);
			printf(" ");
		} else if(balldir == RU){
			balldir = RD;
			board[ballY-1][ballX] = ' ';
			gotoxy(ballX, ballY-1);
			printf(" ");
		}
	} else if(ballY == COLUMN-2){
		if(ballX == bar_pos-2 || ballX == bar_pos-1 || ballX == bar_pos || ballX == bar_pos+1 || ballX == bar_pos+2){ // 바에 부딪힐 때 
			if(balldir == LD){
				balldir = LU;
			} else if(balldir == RD){
				balldir = RU;
			}
		}
	} else if(ballY == COLUMN-1){
		is_finished = true;
	}
	switch(balldir){
		case LU:
			gotoxy(ballX, ballY);
			printf(" ");
			ballX -= 1;
			ballY -= 1;
			gotoxy(ballX, ballY);
			printf("O");
			break;
		case RU:
			gotoxy(ballX, ballY);
			printf(" ");
			ballX += 1;
			ballY -= 1;
			gotoxy(ballX, ballY);
			printf("O");
			break;
		case LD:
			gotoxy(ballX, ballY);
			printf(" ");
			ballX -= 1;
			ballY += 1;
			gotoxy(ballX, ballY);
			printf("O");
			break;
		case RD:
			gotoxy(ballX, ballY);
			printf(" ");
			ballX += 1;
			ballY += 1;
			gotoxy(ballX, ballY);
			printf("O");
			break;
	}
}


void make_board(){
	printf("SPACE 키를 누르면 시작하고 ENTER 키를 누르면 게임이 끝납니다.\n");
	printf("┌");
	for(int i=0;i<ROW;i++){
		printf("─");
	}
	printf("┐");
	printf("\n");
	for(int i=0;i<COLUMN;i++){
		printf("│");
		for(int j=0;j<ROW;j++){
			if(i < 5){
				board[i][j] = '#';	
				printf("#");
			} else if(i == 24){
				if(j >= 48 && j <= 52){
					board[i][j] = '=';
					printf("=");
				} else {
					board[i][j] = ' ';
					printf(" ");
				}
			} else {
				board[i][j] = ' ';
				printf(" ");
			}
			
			
		}
		printf("│");
		printf("\n");
	}
}

void move_bar(int LR){
	if(LR == LEFT){
		if(bar_pos-2 != 0){
			board[24][bar_pos+2] = '=';
			gotoxy(bar_pos+2,24);
			printf(" ");
			bar_pos -= 1;
			board[24][bar_pos-2] = '=';
			gotoxy(bar_pos-2,24);
			printf("=");
		}
	} else if(LR == RIGHT){
		if(bar_pos+2 != 100){
			board[24][bar_pos-2] = '=';
			gotoxy(bar_pos-2,24);
			printf(" ");
			bar_pos += 1;
			board[24][bar_pos+2] = '=';
			gotoxy(bar_pos+2,24);
			printf("=");
		}
	}
}

void start_game(){
	gotoxy(50, 23);
	printf("O");
	is_started = true;
}

int main(){
	make_board();
	
	while(true){
		clock_t start = clock();
		while(clock() - start < 100){
			if(_kbhit()){ //키보드 입력 체크
				char key = _getch();
				if(key == 32){ //스페이스
					if(is_started == false){
						start_game(); // 게임이 시작되지 않은 상태에서만 시작 
					}
				} else if(key == 13){ //엔터
					is_finished = true;
				} else if(key == -32){
					key = _getch();
					if(key == LEFT){ //왼쪽 방향키 
						move_bar(LEFT);
					} else if(key == RIGHT){ //오른쪽 방향키 
						move_bar(RIGHT);
					}
				}
			}
		}
		if(is_started){
			move_ball();
		}
		if(is_finished){
			system("cls");
			printf("게임이 종료되었습니다");
			break; // 반복문 탈출 
		}
	}
}
