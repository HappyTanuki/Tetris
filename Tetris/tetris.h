#ifndef _TETRIS_H
#define _TETRIS_H
#include <windows.h>
#include <mmsystem.h>

#pragma comment(lib, "winmm.lib")

#if 0
#define __DEBUG
#endif

#define NUM_BLOCK		7

#define SIZE_HIGH		23
#define SIZE_WIDTH		12


#define KEY_HOLD		VK_SHIFT
#define KEY_CCROTATE	VK_CONTROL

#define KEY_HARDDROP	' '
#define KEY_PAUSE		'p'
#define KEY_RESET		'r'
#define KEY_QUIT		'q'

#define KEY_EXT			0xE0
#define KEY_CROTATE		72
#define KEY_SOFTDROP	80
#define KEY_RIGHT		77
#define KEY_LEFT		75

#define ICON_WALL		0xF0
#define ICON_I_MINO		0x00
#define ICON_J_MINO		0x01
#define ICON_L_MINO		0x02
#define ICON_O_MINO		0x03
#define ICON_S_MINO		0x04
#define ICON_T_MINO		0x05
#define ICON_Z_MINO		0x06
#define ICON_EMPTY		0x0F

#define RET_SUCCESS		1
#define RET_FAIL		0

#define DIR_UP			0
#define DIR_RIGHT		1
#define DIR_DOWN		2
#define DIR_LEFT		3

#pragma pack(push,1)

typedef struct {
	BYTE byteState;
	BYTE byteNote;
	BYTE byteVelocity;
	BYTE byteNULL;
}MJGRShortMidiMSG_ST;

typedef union {
	DWORD                dwMidi_Data;
	MJGRShortMidiMSG_ST  stMidi_Data;
}MJGRShortMidiMSG;

#pragma pack(pop)

typedef struct _POS {
	int row;
	int col;
}POS;

void			gotorc(POS Position);
void			setcolor(WORD color);
void			init();
void			newBlock();
void			holdBlock();
void			display();
unsigned char	getKey();
void			getMove(int key, POS* mPos, int* dir, int test);
int				delayFunction(unsigned int t);
int				checkMove(POS mPos, int mDir);
void			moveBlock(POS mPos, int mDir);
void			copyGround(int(*source)[SIZE_WIDTH], int(*target)[SIZE_WIDTH]);
void			copybasGroundTodisGround();
void			removeLines();
int				checkFinish();

void			__DEBUGFUNC();

POS				(*blockType[NUM_BLOCK])[4];
int				blockColor[NUM_BLOCK];
int				basGround[SIZE_HIGH][SIZE_WIDTH + 10];
int				disGround[SIZE_HIGH][SIZE_WIDTH + 10];
int				preGround[SIZE_HIGH][SIZE_WIDTH + 10];
POS				(*rotationKicks[8])[5];
POS				(*rotationKicksForI[8])[5];
POS				bPos;
int				bQueue[7];
int				bDir, bType;
int				hBlock;
int				currentScore;

#endif