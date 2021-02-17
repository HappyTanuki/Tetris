#include <stdio.h>
#include <stdlib.h>
#include <conio.h>
#include "tetris.h"

int main() {
	int			key = 0, i = 0;
	POS			mPos = {0, 0};
	int			mDir;
	int			move = 0;

	init();
	newBlock();
	copybasGroundTodisGround();
	display();
	while (!checkFinish()) {
		if (delayFunction(1000))
			key = KEY_SOFTDROP;

		if (!key)
			key = getKey();
		if (key) {
			switch (key) {
			case KEY_HOLD:
				holdBlock();
				copybasGroundTodisGround();
				display();
				break;
			case KEY_HARDDROP:
				getMove(key, &mPos, &mDir, 0);
				moveBlock(mPos, mDir);
				copyGround(disGround, basGround);
				newBlock();
				break;
			case KEY_PAUSE:
				gotorc((POS) { 10, 1 });
				printf("Game is now paused.\n");
				gotorc((POS) { 23, 0 });
				system("pause");
				system("cls");
				display();
				break;
			case KEY_RESET:
				init();
				newBlock();
				copybasGroundTodisGround();
				display();
				currentScore = 0;
				continue;
			case KEY_QUIT:
				gotorc((POS) {23, 0});
				return;
			case KEY_SOFTDROP:
				getMove(key, &mPos, &mDir, 0);
				if (checkMove(mPos, mDir))
					moveBlock(mPos, mDir);
				else {
					copyGround(disGround, basGround);
					newBlock();
				}
				break;
			default:
				for (i = 0; i < 5; i++) {
					getMove(key, &mPos, &mDir, i);
					if (checkMove(mPos, mDir)) {
						move = 1;
						break;
					}
				}
				if (move) {
					moveBlock(mPos, mDir);
					move = 0;
				}
			}
			display(0);

			removeLines();

			key = 0;
		}
	}

	return 0;
}