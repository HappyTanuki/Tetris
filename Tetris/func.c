#include <stdio.h>
#include <windows.h>
#include <time.h>
#include "tetris.h"

void gotorc(POS Position) {
	static HANDLE handle = NULL;
	COORD Pos = { Position.col << 1, Position.row };
	
	if (!handle)
		handle = GetStdHandle(STD_OUTPUT_HANDLE);
	
	SetConsoleCursorPosition(handle, Pos);
}

void setcolor(WORD color) {
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), color);
}

void init() {
	int i = 0, j = 0;
	CONSOLE_CURSOR_INFO CurInfo;

	CurInfo.dwSize = 1;
	CurInfo.bVisible = FALSE;
	SetConsoleCursorInfo(GetStdHandle(STD_OUTPUT_HANDLE), &CurInfo);
	system("mode con: cols=48 lines=24");

	srand(time(NULL));

	hBlock == ICON_EMPTY;

	for (i = 0; i < SIZE_HIGH-1; i++) {
		for (j = 0; j < SIZE_WIDTH; j++) {
			if (j == 0 || j == SIZE_WIDTH - 1) {
				basGround[i][j]		= ICON_WALL;
				preGround[i][j]		= 0xFF;
			}
			else {
				basGround[i][j]		= ICON_EMPTY;
				preGround[i][j]		= 0xFF;
			}
		}
	}
	for (j = 0; j < SIZE_WIDTH; j++) {
		basGround[i][j]		= ICON_WALL;
		preGround[i][j]		= 0xFF;
	}
	
	for (i = 0; i < 7; i++) {
		bQueue[i] = rand() % 7;
		for (j = 0; j < i; j++) {
			if (bQueue[j] == bQueue[i]) {
				i--;
				break;
			}
		}
	}
}

void newBlock() {
	int i = 0, j = 0, row, col;

	bType = bQueue[0];
	for (i = 1; i < 7; i++) {
		bQueue[i - 1] = bQueue[i];
	}
	for (i = 6; i < 7; i++) {
		bQueue[i] = rand() % NUM_BLOCK;
		for (j = 0; j < i; j++) {
			if (bQueue[j] == bQueue[i]) {
				i--;
				break;
			}
		}
	}

	bDir = 0;
	if (bType == ICON_I_MINO)
		bPos.row = 1;
	else {
		bPos.row = 2;
		bDir = rand() % 4;
	}
	bPos.col = 4;
}

void holdBlock() {
	int temp = 0;

	if (hBlock == ICON_EMPTY) {
		hBlock = bType;
		newBlock();
	}
	else {
		temp = bType;
		bType = hBlock;
		hBlock = temp;
	}

	return;
}

void display(){
	int i = 0, j = 0;

	for (i = 2; i < SIZE_HIGH; i++) {
		for (j = 0; j < SIZE_WIDTH; j++) {
			switch (disGround[i][j]) {
			case ICON_WALL:
				gotorc((POS) { i, j });
				setcolor(0xff);
				printf("бс");
				setcolor(0x0f);
				break;
			case ICON_EMPTY:
				gotorc((POS) { i, j });
				printf("  ");
				break;
			default:
				gotorc((POS) { i, j });
				setcolor(blockColor[disGround[i][j]]);
				printf("бс");
				setcolor(0x0f);
				break;
			}
		}
	}

#ifdef __DEBUG
	gotorc((POS) { 23, 0 });
	printf("Block: {%d, %d} rotation: %d", bPos.row, bPos.col, bDir);
#endif

	gotorc((POS) { 10, 15 });
	printf("Score:%d", currentScore);

	copyGround(disGround, preGround);

	return;
}

unsigned char getKey() {
	int key = 0;

	if (GetAsyncKeyState(KEY_HOLD) & 0x0001) {
		return KEY_HOLD;
	}

	if (GetAsyncKeyState(KEY_CCROTATE) & 0x0001) {
		return KEY_CCROTATE;
	}

	if (_kbhit()) {
		key = _getch();
		if (key == KEY_EXT) {
			key = _getch();
			return key;
		}
		else if (key == KEY_HARDDROP || key == KEY_PAUSE || key == KEY_RESET || key == KEY_QUIT)
			return key;
		else
			return RET_FAIL;
	}

	return RET_FAIL;
}

void getMove(int key, POS* mPos, int* mDir, int test) {
	POS prePos;

	*mDir = bDir;
	switch (key) {
	case KEY_CROTATE:
		if (bType == ICON_I_MINO) {
			switch (bDir) {
			case DIR_UP:
				*mDir = DIR_RIGHT;
				mPos->row += rotationKicksForI[0][test]->row;
				mPos->col += rotationKicksForI[0][test]->col;
				break;
			case DIR_RIGHT:
				*mDir = DIR_DOWN;
				mPos->row += rotationKicksForI[2][test]->row;
				mPos->col += rotationKicksForI[2][test]->col;
				break;
			case DIR_DOWN:
				*mDir = DIR_LEFT;
				mPos->row += rotationKicksForI[4][test]->row;
				mPos->col += rotationKicksForI[4][test]->col;
				break;
			case DIR_LEFT:
				*mDir = DIR_UP;
				mPos->row += rotationKicksForI[6][test]->row;
				mPos->col += rotationKicksForI[6][test]->col;
				break;
			}
		}
		else {
			switch (bDir) {
			case DIR_UP:
				*mDir = DIR_RIGHT;
				mPos->row += rotationKicks[0][test]->row;
				mPos->col += rotationKicks[0][test]->col;
				break;
			case DIR_RIGHT:
				*mDir = DIR_DOWN;
				mPos->row += rotationKicks[2][test]->row;
				mPos->col += rotationKicks[2][test]->col;
				break;
			case DIR_DOWN:
				*mDir = DIR_LEFT;
				mPos->row += rotationKicks[4][test]->row;
				mPos->col += rotationKicks[4][test]->col;
				break;
			case DIR_LEFT:
				*mDir = DIR_UP;
				mPos->row += rotationKicks[6][test]->row;
				mPos->col += rotationKicks[6][test]->col;
				break;
			}
		}
		break;
	case KEY_CCROTATE:
		if (bType == ICON_I_MINO) {
			switch (bDir) {
			case DIR_UP:
				*mDir = DIR_LEFT;
				mPos->row += rotationKicksForI[7][test]->row;
				mPos->col += rotationKicksForI[7][test]->col;
				break;
			case DIR_RIGHT:
				*mDir = DIR_UP;
				mPos->row += rotationKicksForI[1][test]->row;
				mPos->col += rotationKicksForI[1][test]->col;
				break;
			case DIR_DOWN:
				*mDir = DIR_RIGHT;
				mPos->row += rotationKicksForI[3][test]->row;
				mPos->col += rotationKicksForI[3][test]->col;
				break;
			case DIR_LEFT:
				*mDir = DIR_DOWN;
				mPos->row += rotationKicksForI[5][test]->row;
				mPos->col += rotationKicksForI[5][test]->col;
				break;
			}
		}
		else {
			switch (bDir) {
			case DIR_UP:
				*mDir = DIR_LEFT;
				mPos->row += rotationKicks[7][test]->row;
				mPos->col += rotationKicks[7][test]->col;
				break;
			case DIR_RIGHT:
				*mDir = DIR_UP;
				mPos->row += rotationKicks[1][test]->row;
				mPos->col += rotationKicks[1][test]->col;
				break;
			case DIR_DOWN:
				*mDir = DIR_RIGHT;
				mPos->row += rotationKicks[3][test]->row;
				mPos->col += rotationKicks[3][test]->col;
				break;
			case DIR_LEFT:
				*mDir = DIR_DOWN;
				mPos->row += rotationKicks[5][test]->row;
				mPos->col += rotationKicks[5][test]->col;
				break;
			}
		}
		break;
	case KEY_SOFTDROP:
		mPos->row = bPos.row + 1;
		mPos->col = bPos.col;
		break;
	case KEY_RIGHT:
		mPos->row = bPos.row;
		mPos->col = bPos.col + 1;
		break;
	case KEY_LEFT:
		mPos->row = bPos.row;
		mPos->col = bPos.col - 1;
		break;
	case KEY_HARDDROP:
		prePos = bPos;
		getMove(KEY_SOFTDROP, mPos, mDir, 0);
		while (1) {
			if (checkMove(*mPos, *mDir)) {
				bPos = *mPos;
				getMove(KEY_SOFTDROP, mPos, mDir, 0);
			}
			else {
				bPos = prePos;
				mPos->row--;
				break;
			}
				
		}
	default:
		return;
	}
}

int delayFunction(unsigned int t) {
	static ULONGLONG newTime = 0, oldTime = 0;
	static int first = 1;

	if (first) {
		oldTime = GetTickCount64();

		first = 0;
	}

	newTime = GetTickCount64();
	if ((newTime - oldTime) > t) {
		oldTime = newTime;
		return RET_SUCCESS;
	}

	return RET_FAIL;
}

int checkMove(POS mPos, int mDir) {
	int i = 0, row, col;

	for (i = 0; i < 4; i++) {
		row = mPos.row + blockType[bType][mDir][i].row;
		col = mPos.col + blockType[bType][mDir][i].col;

		if (basGround[row][col] != ICON_EMPTY)
			return RET_FAIL;
	}
	return RET_SUCCESS;
}

void moveBlock(POS mPos, int mDir) {
	int i = 0, j = 0;

	for (i = 0; i < SIZE_HIGH; i++)
		for (j = 0; j < SIZE_WIDTH; j++)
			preGround[i][j] = disGround[i][j];

	for (i = 0; i < 4; i++)
		disGround[bPos.row + blockType[bType][bDir][i].row][bPos.col + blockType[bType][bDir][i].col] = ICON_EMPTY;

	for (i = 0; i < 4; i++)
		disGround[mPos.row + blockType[bType][mDir][i].row][mPos.col + blockType[bType][mDir][i].col] = bType;

	bPos = mPos;
	bDir = mDir;

	return;
}

void copyGround(int(*source)[SIZE_WIDTH + 10], int(*target)[SIZE_WIDTH + 10]) {
	int i, j;

	for (i = 0; i < SIZE_HIGH; i++)
		for (j = 0; j < SIZE_WIDTH; j++)
			target[i][j] = source[i][j];

	return;
}

void copybasGroundTodisGround() {
	int i, row, col;

	copyGround(basGround, disGround);

	for (i = 0; i < 4; i++) {
		row = bPos.row + blockType[bType][bDir][i].row;
		col = bPos.col + blockType[bType][bDir][i].col;

		disGround[row][col] = bType;
	}
}

void removeLines() {
	int i = 0, j = 0, line = 0, k = 0;

	for (i = 3; i < SIZE_HIGH - 1; i++) {
		for (j = 1; j < SIZE_WIDTH-1; j++)
			if (basGround[i][j] == ICON_EMPTY)
				break;
		if (j == SIZE_WIDTH - 1) {
			for (i = i; i > 0; i--)
				for (j = 1; j < SIZE_WIDTH - 1; j++)
					basGround[i][j] = basGround[i - 1][j];

			for (j = 0; j < SIZE_HIGH; j++)
				for (k = 0; k < SIZE_WIDTH; k++)
					disGround[j][k] = basGround[j][k];

			display();
			line++;
		}
	}

	currentScore += line;

	return;
}

int checkFinish() {
	return !checkMove(bPos, bDir);
}

void __DEBUGFUNC() {
	int i = 0, j = 0;


	return;
}