/*
界面
包括显示和读取用户的操作
*/
#pragma once
#include "define.h"
#include <graphics.h>
#include "Evaluation.h"
#include "CTool.h"
#define box_length 50	//一个棋格的宽度
#define chess_r (box_length/2)*0.8

enum MENU
{
	MENU_MAIN,	//主菜单
	MENU_SEARCH,	//搜索引擎
	WELCOME,	//欢迎界面
};//菜单层级或类型的变量

//界面类
class CVersion
{
public:
	CVersion();
	~CVersion();

	//显示棋盘
	Status showChessBoard();
	//显示棋子
	Status showChess(BYTE chessBoard[board_length][board_length]);
	//显示按键
	Status showButton(MENU menu);
	//获得用户的下一步走法
	CHESSPos getNextStep(BYTE(&chessBoard)[board_length][board_length], ChessType chess, int &step_sum, FILE *&fp, CEvaluation eva,CTool *tool);
	//显示 当前局面评估分数 顺带显示论谁走
	Status showScore(BYTE chessboard[board_length][board_length], ChessType turn,CEvaluation eva);
private:
};