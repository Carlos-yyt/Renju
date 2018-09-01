#include "CAlphaBetaEngine.h"



CAlphaBetaEngine::CAlphaBetaEngine()
{
}


CAlphaBetaEngine::~CAlphaBetaEngine()
{
}

//找到最好的那一步棋
chessMove CAlphaBetaEngine::SearchAGoodMove(BYTE(&chessboard)[board_length][board_length], ChessType chess)
{
	memcpy(CurPosition, chessboard, board_length*board_length);
	alphabata(SearchDepth, -_CRT_INT_MAX, _CRT_INT_MAX);//剪枝算法
	MakeMove(&m_cmBestMove, chess);
	memcpy(chessboard, CurPosition, board_length*board_length);
	return m_cmBestMove;
}

int CAlphaBetaEngine::alphabata(int depth, int alpha, int beta)
{
	ChessType curNextOne;//当前下一步该谁走
	int possibleMove = 0;//可能的走法的个数
	int value = 0;//局面的值	用m_pMG->moveList[depth][0].Score替代了

	if (SearchDepth % 2 == depth % 2)
	{
		curNextOne = nextOne;
	}
	else
	{
		if (nextOne == BChess)
		{
			curNextOne = WChess;
		}
		else
		{
			curNextOne = BChess;
		}
	}

	if (depth == 0)
	{
		return m_pEval->evaluate(CurPosition, curNextOne);
	}
	possibleMove = m_pMG->CreatPossibleMove(CurPosition, depth, curNextOne);//对的
	if (depth == SearchDepth)
	{
		m_cmBestMove = m_pMG->moveList[depth][0];//int(0.5*possibleMove)
	}

	if (curNextOne == BChess)
	{
		value = -_CRT_INT_MAX;
		for (int i = 0; i < possibleMove; i++)
		{
			MakeMove(&m_pMG->moveList[depth][i], curNextOne);//对的
			m_pMG->moveList[depth][i].Score = alphabata(depth - 1, -beta, -alpha);
			UnMakeMove(&m_pMG->moveList[depth][i]);
			if (m_pMG->moveList[depth][i].Score > value)
			{
				value = m_pMG->moveList[depth][i].Score;
				if (depth == SearchDepth)
				{
					m_cmBestMove = m_pMG->moveList[depth][i];				
				}
				if (beta <= alpha)
				{
					break; 
				}
			}

		}
	}
	else
	{
		value = _CRT_INT_MAX;
		for (int i = 0; i < possibleMove; i++)
		{
			MakeMove(&m_pMG->moveList[depth][i], curNextOne);//对的
			m_pMG->moveList[depth][i].Score = alphabata(depth - 1, -beta, -alpha);
			UnMakeMove(&m_pMG->moveList[depth][i]);
			if (m_pMG->moveList[depth][i].Score < value)
			{
				value = m_pMG->moveList[depth][i].Score;
				if (depth == SearchDepth)
				{
					m_cmBestMove = m_pMG->moveList[depth][i];

				}
				if (beta <= alpha)
				{
					break;
				}
			}
		}

	}
	return value;

	/*if (m_pMG->moveList[depth][i].Score > alpha)
	{
		alpha = m_pMG->moveList[depth][i].Score;
		if (depth==SearchDepth)
		{
			m_cmBestMove = m_pMG->moveList[depth][i];
		}
	}
	if (alpha >= beta)
	{
		break;
	}*/
	//return alpha;
}
