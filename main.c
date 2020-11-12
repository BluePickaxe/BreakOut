#include <stdio.h>
#include <Windows.h>
#include <conio.h>
#include <stdbool.h>
#include <process.h>

#define ROW 101
#define COLUMN 25

#define LEFT 75
#define RIGHT 77

char board[COLUMN][ROW];

boolean game_started = false;
int bar_pos = 50;
int ballX = 50;
int ballY = 23;

void gotoxy(int x, int y){
	COORD Pos = {x + 1, y + 2}; // �׵θ��� ó�� ���� �κ� ���� 
	SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), Pos);
}

unsigned __stdcall t1(void *arg){
	while(true){
		Sleep(100);
		gotoxy(ballX, ballY);
		printf(" ");
		ballX += 1;
		ballY -= 1;
		gotoxy(ballX, ballY);
		printf("O");
	}
}

void make_board(){
	printf("SPACE Ű�� ������ �����ϰ� ENTER Ű�� ������ ������ �����ϴ�.\n");
	printf("��");
	for(int i=0;i<ROW;i++){
		printf("��");
	}
	printf("��");
	printf("\n");
	for(int i=0;i<COLUMN;i++){
		printf("��");
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
		printf("��");
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
	gotoxy(ballX, ballY);
	printf("O");
	_beginthreadex(NULL, 0, t1, 0, 0, NULL);


}

int main(){
	make_board();
	while(true){
		if(_kbhit()){ //Ű���� �Է� üũ
			char key = _getch();
			if(key == 32){ //�����̽�
				start_game();
			} else if(key == 13){ //����
				break; //�ݺ��� ���� 
			} else if(key == -32){
				key = _getch();
				if(key == LEFT){ //���� ����Ű 
					move_bar(LEFT);
				} else if(key == RIGHT){ //������ ����Ű 
					move_bar(RIGHT);
				}
			}
		}
	}
}
