/*
最基本的头文件，包括了宏定义和棋盘等等
*/
#pragma once
#include <stdio.h>
#include <math.h>
#include <memory.h>
#include "stdlib.h"

#define board_length 15	//棋盘的宽度（标准五子棋棋盘是15*15，不是像素的数量）

#define OK 1
#define YES 1
#define TRUE 1
#define FALSE 0
#define NO 0
#define ERROR 0
enum ChessType	//点位的状态
{
	BChess,	//黑棋 0 0'\0'
	WChess,	//白棋 1 1'\x1'
	NOCHESS,	//没有棋子 2'\x2'
};
typedef unsigned char BYTE;	//存棋子的数据类型
typedef unsigned char Status;	//状态

//棋子的位置
typedef struct chessPossition
{
	BYTE x;
	BYTE y;
}CHESSPos;

//走法
typedef struct chessMove
{
	CHESSPos StonePos;//棋子的位置
	int Score;//分数
}CHESSMOVE;

extern BYTE CHESSBOARD[board_length][board_length];	//棋盘
extern int step_sum;//棋盘上棋子总数
extern char VS_type;//对局类型 0是玩家VS玩家，1是玩家VS电脑