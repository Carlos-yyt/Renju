#pragma once
#include "define.h"
class CMoveGenerator
{
public:
	CMoveGenerator();
	~CMoveGenerator();
	
	//给出下一步所有合法的走法	nSide不知道是用来干什么的
	int CreatPossibleMove(BYTE chessboard[board_length][board_length], int nPly, int nSide);

	//用来记录走法的数组
	CHESSMOVE moveList[10][board_length*board_length];
protected:
	//向走法数组中添加走法 nPly是走法的层次
	int AddMove(int nToX, int nToY, int nPly);
	
	//记录走法的数量
	int m_nMoveCount;
private:

};

