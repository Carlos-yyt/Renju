#include "SearchEngine.h"

CSearchEngine::CSearchEngine()
{
	m_pEval = new	CEvaluation;
	m_pMG = new	CMoveGenerator;
}

CSearchEngine::~CSearchEngine()
{
	delete m_pEval;
	delete m_pMG;
}

BYTE CSearchEngine::MakeMove(CHESSMOVE * move, int type)
{
	CurPosition[move->StonePos.x][move->StonePos.y] = (BYTE)type;
	return 0;
}

void CSearchEngine::UnMakeMove(CHESSMOVE * move)
{
	CurPosition[move->StonePos.x][move->StonePos.y] = (BYTE)NOCHESS;
}

int CSearchEngine::IsGameOver(BYTE position[board_length][board_length], ChessType chess)
{
	int score;
	score = m_pEval->evaluate(position, chess);
	if (score == _CRT_INT_MAX || score==-_CRT_INT_MAX)
	{
		return score;//游戏结束
	}
	return 0;//游戏没有结束
}