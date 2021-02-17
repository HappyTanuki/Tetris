#include "tetris.h"

const POS zeroToRight[5]	 = { {00, 00}, {-1, 00}, {-1, +1}, {00, -2}, {-1, -2} };
const POS rightToZero[5]	 = { {00, 00}, {+1, 00}, {+1, -1}, {00, +2}, {+1, +2} };
const POS rightToTwo[5]		 = { {00, 00}, {+1, 00}, {+1, -1}, {00, +2}, {+1, +2} };
const POS twoToRight[5]		 = { {00, 00}, {-1, 00}, {-1, +1}, {00, -2}, {-1, -2} };
const POS twoToLeft[5]		 = { {00, 00}, {+1, 00}, {+1, +1}, {00, -2}, {+1, -2} };
const POS leftToTwo[5]		 = { {00, 00}, {-1, 00}, {-1, -1}, {00, +2}, {-1, +2} };
const POS leftToZero[5]		 = { {00, 00}, {-1, 00}, {-1, -1}, {00, +2}, {-1, +2} };
const POS zeroToLeft[5]		 = { {00, 00}, {+1, 00}, {+1, +1}, {00, -2}, {+1, -2} };

const POS zeroToRightForI[5] = { {00, 00}, {-2, 00}, {+1, 00}, {-2, -1}, {+1, +2} };
const POS rightToZeroForI[5] = { {00, 00}, {+2, 00}, {-1, 00}, {+2, +1}, {-1, -2} };
const POS rightToTwoForI[5]	 = { {00, 00}, {-1, 00}, {+2, 00}, {-1, +2}, {+2, -1} };
const POS twoToRightForI[5]	 = { {00, 00}, {+1, 00}, {-2, 00}, {+1, -2}, {-2, +1} };
const POS twoToLeftForI[5]	 = { {00, 00}, {+2, 00}, {-1, 00}, {+2, +1}, {-1, -2} };
const POS leftToTwoForI[5]	 = { {00, 00}, {-2, 00}, {+1, 00}, {-2, -1}, {+1, +2} };
const POS leftToZeroForI[5]	 = { {00, 00}, {+1, 00}, {-2, 00}, {+1, -2}, {-2, +1} };
const POS zeroToLeftForI[5]	 = { {00, 00}, {-1, 00}, {+2, 00}, {-1, +2}, {+2, -1} };

extern POS (*rotationKicks[8])[5]		 = { zeroToRight    , rightToZero    , rightToTwo    , twoToRight    , twoToLeft    , leftToTwo    , leftToZero    , zeroToLeft     };
extern POS (*rotationKicksForI[8])[5]	 = { zeroToRightForI, rightToZeroForI, rightToTwoForI, twoToRightForI, twoToLeftForI, leftToTwoForI, leftToZeroForI, zeroToLeftForI };
