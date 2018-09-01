/*
工具类，实现一些辅助功能：悔棋、存档
*/
#pragma once
#include "define.h"

class CTool
{
	friend class CVersion;
public:
	CTool();
	~CTool();
	//悔1步棋，如果无棋可悔则返回-1。type为0是玩家VS玩家，type为1是玩家VS电脑。
	char retractChess(int type);

	//加一步棋到histroy_Pos里面
	char addChess(int x, int y);
protected:
private:
	CHESSPos histroy_Pos[255];	//记录棋局
	CHESSPos pur_Pos;			//最后落子点
};


