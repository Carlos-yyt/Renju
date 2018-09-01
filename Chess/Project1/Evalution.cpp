#include "define.h"
#include "Evaluation.h"

//位置重要性价值表，此表从中间向外，越往外价值越低
int PosValue[board_length][board_length] =
{
	{ 0,0,0,0,0,0,0,0,0,0,0,0,0,0,0 },
	{ 0,1,1,1,1,1,1,1,1,1,1,1,1,1,0 },
	{ 0,1,2,2,2,2,2,2,2,2,2,2,2,1,0 },
	{ 0,1,2,3,3,3,3,3,3,3,3,3,2,1,0 },
	{ 0,1,2,3,4,4,4,4,4,4,4,3,2,1,0 },
	{ 0,1,2,3,4,5,5,5,5,5,4,3,2,1,0 },
	{ 0,1,2,3,4,5,6,6,6,5,4,3,2,1,0 },
	{ 0,1,2,3,4,5,6,7,6,5,4,3,2,1,0 },
	{ 0,1,2,3,4,5,6,6,6,5,4,3,2,1,0 },
	{ 0,1,2,3,4,5,5,5,5,5,4,3,2,1,0 },
	{ 0,1,2,3,4,4,4,4,4,4,4,3,2,1,0 },
	{ 0,1,2,3,3,3,3,3,3,3,3,3,2,1,0 },
	{ 0,1,2,2,2,2,2,2,2,2,2,2,2,1,0 },
	{ 0,1,1,1,1,1,1,1,1,1,1,1,1,1,0 },
	{ 0,0,0,0,0,0,0,0,0,0,0,0,0,0,0 }
};/*
  不知道怎么把这个也做成和board_length相关的东西。
  因为在函数外初始化的时候没法写逻辑进去，
  在函数内初始化的话又增加了复杂性，要在保证调用PosValue之前调用这个函数。
  */

  //全局变量，用来统计估值函数的执行遍数
int Evalution_Count = 0;


CEvaluation::CEvaluation()
{
}

CEvaluation::~CEvaluation()
{
}

//估值函数 chess是下一步该谁走
int CEvaluation::evaluate(BYTE chessboard[board_length][board_length], ChessType chess)
{
	BYTE nStoneType;
	Evalution_Count++;	//估值函数被调用的次数，全局变量
	int i = 0;
	int j = 0;
	int k = 0;
	//清空分析结果
	//memset(this->TypeRecord, (int)TOBEANALSIS, board_length*board_length * 4 * sizeof(int));  memset在赋值的时候有约束条件
	for (i = 0; i < board_length; i++)
	{
		for (j = 0; j < board_length; j++)
		{
			for (k = 0; k < 4; k++)
			{
				TypeRecord[i][j][k] = (int)TOBEANALSIS;
			}
		}
	}
	for (i = 0; i < 2; i++)
	{
		for (j = 0; j < 20; j++)
		{
			TypeCount[i][j] = 0;
		}
	}
	//memset(TypeCount, 0, 20 * 2 * sizeof(int));

	//逐点分析
	for (int i = 0; i < board_length; i++)
	{
		for (int j = 0; j < board_length; j++)
		{
			if (chessboard[i][j] != NOCHESS)
			{
				if (TypeRecord[i][j][0] == TOBEANALSIS)
				{
					AnalysisHorizon(chessboard, i, j);
				}
				if (TypeRecord[i][j][1] == TOBEANALSIS)
				{
					AnalysisVertical(chessboard, i, j);
				}
				if (TypeRecord[i][j][2] == TOBEANALSIS)
				{
					AnalysisLeft(chessboard, i, j);
				}
				if (TypeRecord[i][j][3] == TOBEANALSIS)
				{
					AnalysisRight(chessboard, i, j);
				}
			}
		}
	}

	for (int i = 0; i < board_length; i++)
	{
		for (int j = 0; j < board_length; j++)
		{
			nStoneType = chessboard[i][j];
			if (nStoneType != NOCHESS)
			{
				for (int k = 0; k < 4; k++)
				{
					switch (TypeRecord[i][j][k])	//统计棋型
					{
					case FIVE:
						TypeCount[nStoneType][FIVE]++;
						break;
					case FOUR:
						TypeCount[nStoneType][FOUR]++;
						break;
					case SFOUR:
						TypeCount[nStoneType][SFOUR]++;
						break;
					case THREE:
						TypeCount[nStoneType][THREE]++;
						break;
					case STHREE:
						TypeCount[nStoneType][STHREE]++;
						break;
					case TWO:
						TypeCount[nStoneType][TWO]++;
						break;
					case STWO:
						TypeCount[nStoneType][STWO]++;
						break;
					default:
						break;
					}
				}
			}
		}
	}

	//结束判断 即 出现了五连
	if (chess == BChess)
	{
		if (TypeCount[BChess][FIVE])
		{
			return _CRT_INT_MAX;
		}
		if (TypeCount[WChess][FIVE])
		{
			return -_CRT_INT_MAX;
		}
	}
	if (chess == WChess)
	{
		if (TypeCount[BChess][FIVE])
		{
			return _CRT_INT_MAX;
		}
		if (TypeCount[WChess][FIVE])
		{
			return -_CRT_INT_MAX;
		}
	}

	//两个冲四等于一个活四
	if (TypeCount[WChess][SFOUR] > 1)
	{
		TypeCount[WChess][FOUR]++;
	}
	if (TypeCount[BChess][SFOUR] > 1)
	{
		TypeCount[BChess][FOUR]++;
	}

	//估值
	int WValue = 0;
	int BValue = 0;
	if (chess == WChess)	//下一步轮白棋走 //YYT
	{
		//生死棋型
		if (TypeCount[WChess][FOUR])	//白胜
		{
			return -(_CRT_INT_MAX - 10);
		}
		if (TypeCount[WChess][SFOUR])	//白胜
		{
			return -(_CRT_INT_MAX - 20);
		}
		if (TypeCount[BChess][FOUR])	//黑胜
		{
			return _CRT_INT_MAX - 30;
		}
		if (TypeCount[BChess][SFOUR] && TypeCount[BChess][THREE])	//黑胜
		{
			return _CRT_INT_MAX - 40;
		}
		if (TypeCount[WChess][THREE] && TypeCount[BChess][SFOUR] == 0)	//白胜
		{
			return -(_CRT_INT_MAX - 50);
		}
		if (TypeCount[BChess][THREE] > 1 && TypeCount[WChess][SFOUR] == 0 && TypeCount[WChess][THREE] == 0 && TypeCount[WChess][STHREE] == 0)	//黑胜
		{
			return _CRT_INT_MAX - 40;
		}

		//危险棋型
		if (TypeCount[WChess][THREE] > 1)
		{
			WValue += _CRT_INT_MAX*0.2;
		}
		else
		{
			if (TypeCount[WChess][THREE])
			{
				WValue += _CRT_INT_MAX*0.02;
			}
		}
		if (TypeCount[BChess][THREE] > 1)
		{
			BValue += _CRT_INT_MAX*0.05;
		}
		else if (TypeCount[BChess][THREE])
		{
			BValue += _CRT_INT_MAX*0.01;
		}

		//普通棋型
		if (TypeCount[WChess][STHREE]) {
			WValue += _CRT_INT_MAX*0.001*TypeCount[WChess][STHREE];
		}
		if (TypeCount[BChess][STHREE])
		{
			BValue += _CRT_INT_MAX* 0.001*TypeCount[BChess][STHREE];
		}
		if (TypeCount[WChess][TWO])
		{
			WValue += _CRT_INT_MAX* 0.0004*TypeCount[WChess][TWO];
		}
		if (TypeCount[BChess][STWO])
		{
			BValue += _CRT_INT_MAX*0.0004*TypeCount[BChess][STWO];
		}
		if (TypeCount[WChess][STWO])
		{
			WValue += _CRT_INT_MAX* 0.0001*TypeCount[WChess][STWO];
		}
		if (TypeCount[BChess][STWO])
		{
			BValue += _CRT_INT_MAX*0.0001* TypeCount[BChess][STWO];
		}
	}
	else
	{	//下一步轮黑棋走
		//生死棋型
		if (TypeCount[BChess][FOUR])	//黑胜
		{
			return _CRT_INT_MAX - 10;
		}
		if (TypeCount[BChess][SFOUR])	//黑胜
		{
			return _CRT_INT_MAX - 20;
		}
		if (TypeCount[WChess][FOUR])	//白胜
		{
			return -(_CRT_INT_MAX - 30);
		}
		if (TypeCount[WChess][SFOUR] && TypeCount[WChess][THREE])	//白胜
		{
			return -(_CRT_INT_MAX - 40);
		}
		if (TypeCount[BChess][THREE] && TypeCount[WChess][SFOUR] == 0)	//黑胜
		{
			return _CRT_INT_MAX - 50;
		}
		if (TypeCount[WChess][THREE] > 1 && TypeCount[BChess][SFOUR] == 0 && TypeCount[BChess][THREE] == 0 && TypeCount[BChess][STHREE] == 0)	//白胜
		{
			return -(_CRT_INT_MAX - 40);
		}

		//危险棋型
		if (TypeCount[BChess][THREE] > 1)
		{
			BValue += _CRT_INT_MAX*0.2;
		}
		else
		{
			if (TypeCount[BChess][THREE])
			{
				BValue += _CRT_INT_MAX*0.02;
			}
		}
		if (TypeCount[WChess][THREE] > 1)
		{
			WValue += _CRT_INT_MAX*0.05;
		}
		else
		{
			if (TypeCount[WChess][THREE])
			{
				WValue += _CRT_INT_MAX*0.01;
			}
		}

		//普通棋型
		if (TypeCount[BChess][STHREE]) {
			BValue += _CRT_INT_MAX*0.001* TypeCount[BChess][STHREE];
		}
		if (TypeCount[WChess][STHREE])
		{
			WValue += _CRT_INT_MAX* 0.001*TypeCount[WChess][STHREE];
		}
		if (TypeCount[BChess][TWO])
		{
			BValue += _CRT_INT_MAX* 0.0004*TypeCount[BChess][TWO];
		}
		if (TypeCount[WChess][TWO])
		{
			WValue += _CRT_INT_MAX*0.0004*TypeCount[WChess][TWO];
		}
		if (TypeCount[BChess][STWO])
		{
			BValue += _CRT_INT_MAX* 0.0001* TypeCount[BChess][TWO];
		}
		if (TypeCount[WChess][STWO])
		{
			WValue += _CRT_INT_MAX*0.0001* TypeCount[WChess][STWO];
		}
	}

	//考虑到棋子的偏远程度(PosValue表)
	for (int i = 0; i < board_length; i++)
	{
		for (int j = 0; j < board_length; j++)
		{
			nStoneType = chessboard[i][j];
			if (nStoneType != NOCHESS)
			{
				if (nStoneType == BChess)
				{
					BValue += _CRT_INT_MAX*0.0001*PosValue[i][j];
				}
				else
				{
					WValue += _CRT_INT_MAX*0.0001*PosValue[i][j];
				}
			}
		}
	}


	//if (chess==WChess)//如果下一步是白棋走
	//{
	//	return BValue - WValue;//那就要按照黑棋的立场来评估棋局
	//}
	//else
	//{
	//	return WValue - BValue;
	//}

	return BValue - WValue;//黑棋大值玩家，白棋小值玩家

}

//水平
int CEvaluation::AnalysisHorizon(BYTE chessboard[board_length][board_length], int i, int j)
{
	AnalysisLine(chessboard[i], 15, j);
	for (int s = 0; s < 15; s++)
	{
		if (m_LineRecord[s] != TOBEANALSIS)
			TypeRecord[i][s][0] = m_LineRecord[s];

	}
	return TypeRecord[i][j][0];
}

//竖直
int CEvaluation::AnalysisVertical(BYTE chessboard[board_length][board_length], int i, int j)
{
	BYTE tempArray[board_length];

	for (int k = 0; k < board_length; k++)
		tempArray[k] = chessboard[k][j];
	AnalysisLine(tempArray, board_length, i);
	for (int s = 0; s < board_length; s++)
	{
		if (m_LineRecord[s] != TOBEANALSIS)
			TypeRecord[s][j][1] = m_LineRecord[s];

	}
	return TypeRecord[i][j][1];
}

int CEvaluation::AnalysisLeft(BYTE chessboard[board_length][board_length], int i, int j)
{
	BYTE tempArray[board_length];
	int x, y;
	if (i < j)
	{
		y = 0;
		x = j - i;
	}
	else
	{
		x = 0;
		y = i - j;
	}
	int k = 0;
	for (; k < board_length; k++)
	{
		if (x + k > 14 || y + k > 14)
			break;
		tempArray[k] = chessboard[y + k][x + k];
	}
	AnalysisLine(tempArray, k, j - x);
	for (int s = 0; s < k; s++)
	{
		if (m_LineRecord[s] != TOBEANALSIS)
			TypeRecord[y + s][x + s][2] = m_LineRecord[s];

	}
	return TypeRecord[i][j][2];
}

int CEvaluation::AnalysisRight(BYTE chessboard[board_length][board_length], int i, int j)
{
	BYTE tempArray[board_length];
	int x, y, realnum;

	if (14 - i < j)
	{
		y = 14;
		x = j - 14 + i;
		realnum = 14 - i;
	}
	else
	{
		x = 0;
		y = i + j;
		realnum = j;
	}
	int k = 0;;
	for (; k < board_length; k++)
	{
		if (x + k > 14 || y - k < 0)
			break;
		tempArray[k] = chessboard[y - k][x + k];
	}
	AnalysisLine(tempArray, k, j - x);
	for (int s = 0; s < k; s++)
	{
		if (m_LineRecord[s] != TOBEANALSIS)
			TypeRecord[y - s][x + s][3] = m_LineRecord[s];

	}
	return TypeRecord[i][j][3];

	return 0;
}


//分析line
int CEvaluation::AnalysisLine(BYTE * chessboard, int GridNum, int StonePos)
{
	BYTE StoneType;
	BYTE AnalyLine[30];
	int nAnalyPos;
	int LeftEdge, RightEdge;
	int LeftRange, RightRange;

	if (GridNum < 5)
	{
		memset(m_LineRecord, ANALSISED, GridNum);
		return 0;
	}

	nAnalyPos = StonePos;
	memset(m_LineRecord, TOBEANALSIS, 30);
	memset(AnalyLine, 0x0F, 30);
	memcpy(&AnalyLine, chessboard, GridNum);

	GridNum--;

	StoneType = AnalyLine[nAnalyPos];
	LeftEdge = nAnalyPos;
	RightEdge = nAnalyPos;

	while (LeftEdge > 0)
	{
		if (AnalyLine[LeftEdge - 1] != StoneType)
			break;
		LeftEdge--;
	}

	while (RightEdge < GridNum)
	{
		if (AnalyLine[RightEdge + 1] != StoneType)
			break;
		RightEdge++;
	}

	LeftRange = LeftEdge;
	RightRange = RightEdge;

	while (LeftRange > 0)
	{
		if (AnalyLine[LeftRange - 1] == !StoneType)
			break;
		LeftRange--;
	}

	while (RightRange < GridNum)
	{
		if (AnalyLine[RightRange + 1] == !StoneType)
			break;
		RightRange++;
	}

	if (RightRange - LeftRange < 4)
	{
		for (int k = LeftRange; k <= RightRange; k++)
			m_LineRecord[k] = ANALSISED;
		return FALSE;
	}

	for (int k = LeftEdge; k <= RightEdge; k++)
		m_LineRecord[k] = ANALSISED;

	if (RightEdge - LeftEdge > 3)//五连
	{
		m_LineRecord[nAnalyPos] = FIVE;
		return FIVE;
	}


	if (RightEdge - LeftEdge == 3)//4连
	{
		int Leftfour = FALSE;
		if (LeftEdge > 0)
		{
			if (AnalyLine[LeftEdge - 1] == NOCHESS)
				Leftfour = TRUE;
		}

		if (RightEdge < GridNum)
		{
			if (AnalyLine[RightEdge + 1] == NOCHESS)
			{
				if (Leftfour == TRUE)
					m_LineRecord[nAnalyPos] = FOUR;
				else
					m_LineRecord[nAnalyPos] = SFOUR;
			}
			else
			{
				if (Leftfour == TRUE)
					m_LineRecord[nAnalyPos] = SFOUR;
			}

		}
		else
		{
			if (Leftfour = TRUE)
				m_LineRecord[nAnalyPos] = SFOUR;
		}

		return m_LineRecord[nAnalyPos];
	}



	if (RightEdge - LeftEdge == 2)//3连
	{
		int LeftThree = FALSE;
		if (LeftEdge > 0)
		{

			if (AnalyLine[LeftEdge - 1] == NOCHESS)
			{
				if (LeftEdge > 1 && AnalyLine[LeftEdge - 2] == AnalyLine[LeftEdge])
				{
					m_LineRecord[LeftEdge] = SFOUR;
					m_LineRecord[LeftEdge - 2] = ANALSISED;
				}
				else
					LeftThree = TRUE;
			}
			else
			{
				if (RightEdge == GridNum || AnalyLine[RightEdge + 1] != NOCHESS)
					return FALSE;
			}
		}

		if (RightEdge < GridNum)
		{
			if (AnalyLine[RightEdge + 1] == NOCHESS)
			{
				if (RightEdge < GridNum - 1 && AnalyLine[RightEdge + 2] == AnalyLine[RightEdge])
				{
					m_LineRecord[RightEdge] = SFOUR;
					m_LineRecord[RightEdge + 2] = ANALSISED;

				}
				else
				{
					if (LeftThree == TRUE)
						m_LineRecord[RightEdge] = THREE;
					else
						m_LineRecord[RightEdge] = STHREE;
				}
			}
			else
			{
				if (m_LineRecord[LeftEdge] == SFOUR)
					return m_LineRecord[LeftEdge];
				if (LeftThree == TRUE)
					m_LineRecord[nAnalyPos] = STHREE;
			}

		}
		else
		{
			if (m_LineRecord[LeftEdge] == SFOUR)
				return m_LineRecord[LeftEdge];
			if (LeftThree == TRUE)
				m_LineRecord[nAnalyPos] = STHREE;

		}
		return m_LineRecord[nAnalyPos];
	}

	if (RightEdge - LeftEdge == 1)//2连
	{
		int Lefttwo = FALSE;
		int Leftthree = FALSE;
		if (LeftEdge > 2)
		{
			if (AnalyLine[LeftEdge - 1] == NOCHESS)
			{
				if (LeftEdge - 1 > 1 && AnalyLine[LeftEdge - 2] == AnalyLine[LeftEdge])
				{
					if (AnalyLine[LeftEdge - 3] == AnalyLine[LeftEdge])
					{
						m_LineRecord[LeftEdge - 3] = ANALSISED;
						m_LineRecord[LeftEdge - 2] = ANALSISED;
						m_LineRecord[LeftEdge] = SFOUR;
					}
					else
						if (AnalyLine[LeftEdge - 3] == NOCHESS)
						{
							m_LineRecord[LeftEdge - 2] = ANALSISED;
							m_LineRecord[LeftEdge] = STHREE;
						}
				}
				else
					Lefttwo = TRUE;
			}
		}
		if (RightEdge < GridNum)
		{
			if (AnalyLine[RightEdge + 1] == NOCHESS)
			{
				if (RightEdge + 1 < GridNum - 1 && AnalyLine[RightEdge + 2] == AnalyLine[RightEdge])
				{
					if (AnalyLine[RightEdge + 3] == AnalyLine[RightEdge])
					{
						m_LineRecord[RightEdge + 3] = ANALSISED;
						m_LineRecord[RightEdge + 2] = ANALSISED;
						m_LineRecord[RightEdge] = SFOUR;
					}
					else
						if (AnalyLine[RightEdge + 3] == NOCHESS)
						{
							m_LineRecord[RightEdge + 2] = ANALSISED;
							if (Lefttwo == TRUE)
								m_LineRecord[RightEdge] = THREE;
							else
								m_LineRecord[RightEdge] = STHREE;
						}

				}
				else
				{
					if (m_LineRecord[LeftEdge] == SFOUR)
						return m_LineRecord[LeftEdge];
					if (m_LineRecord[LeftEdge] == STHREE)
					{
						m_LineRecord[LeftEdge] = THREE;
						return m_LineRecord[LeftEdge];
					}

					if (Lefttwo == TRUE)
						m_LineRecord[nAnalyPos] = TWO;
					else
						m_LineRecord[nAnalyPos] = STWO;
				}
			}
			else
			{
				if (m_LineRecord[LeftEdge] == SFOUR)
					return m_LineRecord[LeftEdge];
				if (Lefttwo == TRUE)
					m_LineRecord[nAnalyPos] = STWO;
			}

		}
		return m_LineRecord[nAnalyPos];
	}
	return 0;
}
