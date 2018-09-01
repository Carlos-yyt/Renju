#include "MoveGenerator.h"
#include "Evaluation.h"

CMoveGenerator::CMoveGenerator()
{
}

CMoveGenerator::~CMoveGenerator()
{
}

int CMoveGenerator::CreatPossibleMove(BYTE chessboard[board_length][board_length], int nPly, int nSide)
{
	m_nMoveCount = 0;
	for (int i = 0; i < board_length; i++)
	{
		for (int j = 0; j < board_length; j++)
		{
			if (chessboard[i][j]==(BYTE)NOCHESS)
			{
				AddMove(i, j, nPly);
			}
		}
	}

	return m_nMoveCount;//返回合理走法的个数
}

int CMoveGenerator::AddMove(int nToX, int nToY, int nPly)
{
	moveList[nPly][m_nMoveCount].StonePos.x = nToX;
	moveList[nPly][m_nMoveCount].StonePos.y = nToY;
	m_nMoveCount++;

	moveList[nPly][m_nMoveCount].Score = PosValue[nToX][nToY];
	return m_nMoveCount;
}