#pragma once
#define _CALPHABETAENGINE_H_
#include "SearchEngine.h"
#include <memory.h>

class CAlphaBetaEngine : public CSearchEngine
{
public:
	CAlphaBetaEngine();
	~CAlphaBetaEngine();
	chessMove SearchAGoodMove(BYTE(&chessboard)[board_length][board_length], ChessType chess);
	//BYTE CurPosition[board_length][board_length];
protected:
	int alphabata(int depth, int alpha, int beta);
};