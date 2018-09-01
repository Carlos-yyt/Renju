#pragma once
#include "CTool.h"

//悔棋
char CTool::retractChess(int type)
{
	//type为0是玩家VS玩家，type为1是玩家VS电脑。
	if (step_sum>1 && type==1)
	{
		//因为是玩家VS电脑，一次退两步
		pur_Pos = histroy_Pos[--step_sum];
		CHESSBOARD[pur_Pos.x][pur_Pos.y] = NOCHESS;
		pur_Pos = histroy_Pos[--step_sum];
		CHESSBOARD[pur_Pos.x][pur_Pos.y] = NOCHESS;
	}
	else if (step_sum>0 && type==0)
	{
		//玩家VS玩家
		pur_Pos = histroy_Pos[--step_sum];
		CHESSBOARD[pur_Pos.x][pur_Pos.y] = NOCHESS;
	}
	else if (step_sum<=0)
	{
		return -1;
	}
	return step_sum;
}

char CTool::addChess(int x, int y)
{
	this->histroy_Pos[step_sum].x = x;
	this->histroy_Pos[step_sum].y = y;
	return 0;
}
