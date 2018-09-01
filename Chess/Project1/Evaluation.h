#pragma once
#include "define.h"
enum CHESSFORM	//棋子的类型
{
	STWO,	//眠二	连且只连了两个同类棋子，有且只有一段被封住了 1
	STHREE,	//眠三	连且只连了三个同类棋子，有且只有一段被封住了 2
	SFOUR,	//眠四	连且只连了四个同类棋子，有且只有一段被封住了 3
	TWO,	//活二	连且只连了二个同类棋子，两端都有气 4
	THREE,	//活三	连且只连了三个同类棋子，两端都有气 5
	FOUR,	//活四	连且只连了四个同类棋子，两端都有气 6
	FIVE,	//五连 7
	ANALSISED,	//已经分析过的 8
	TOBEANALSIS	//待分析的 9
};

extern int PosValue[board_length][board_length];

class CEvaluation
{
	friend class CVersion;
public:
	CEvaluation();
	virtual ~CEvaluation();	//不太理解virtual在这里是为了什么

	//估值函数 chess传的是下一步该谁走
	virtual int evaluate(BYTE chessboard[board_length][board_length], ChessType chess);
protected:
	//分析水平方向上某点及其周边的棋型
	int AnalysisHorizon(BYTE chessboard[board_length][board_length], int i, int j);

	//分析垂直方向上某点及其周围的棋型
	int AnalysisVertical(BYTE chessboard[board_length][board_length], int i, int j);

	//分析左斜45°方向上及其周围的棋型
	int AnalysisLeft(BYTE chessboard[board_length][board_length], int i, int j);

	//分析右斜45°方向上及其周围的棋型
	int AnalysisRight(BYTE chessboard[board_length][board_length], int i, int j);

	//分析给定的某一条线上的点及其周围的棋型	chessboard是这条线的首地址，GridNum是这条线上棋子的总数，StonePos是所要分析的棋子的位置
	int AnalysisLine(BYTE *chessboard, int GridNum, int StonePos);

	//存放AnalysisLine分析结果的数组
	BYTE m_LineRecord[30];	//存放AnalysisLine分析结果的数组 不理解为什么是30，自己觉得是15啊，因为最多15个元素

	/*
	存放所有分析结果的数组
	第三个维度以此用来存放水平、垂直、左斜、右斜4个方向上的所有棋型
	*/
	int TypeRecord[board_length][board_length][4] = { 0 };

	//存放统计分析过的分析结果的数组
	int TypeCount[2][20] = { 0 };	//第一维是分黑白（但是其实放的不是int型而是ChessType类型的数据。好在可以把Bchess和Wchess设置为枚举类型的头两个值，这样刚好是0和1），第二维是储存不同棋型（CHESSFORM）出现的次数

private:

};