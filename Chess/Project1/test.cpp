/*
测试入口
*/

#include "define.h"
BYTE CHESSBOARD[board_length][board_length];//实况棋盘

extern BYTE CHESSBOARD[board_length][board_length];	//棋盘
int step_sum=0;//棋盘上棋子总数
char VS_type=1;//对局类型 0是玩家VS玩家，1是玩家VS电脑

#include "version.h"
#include <stdlib.h>
#include "SearchEngine.h"
#include "CAlphaBetaEngine.h"
#include "CTool.h"
int main() {

	//初始化棋盘
	for (int i = 0; i < board_length; i++)
	{
		for (int j = 0; j < board_length; j++)
		{
			CHESSBOARD[i][j] = NOCHESS;	
		}
	}

	CVersion version;			//界面
	version.showChessBoard();	//打开绘图界面
	CAlphaBetaEngine search;	//alpha-beta搜索引擎
	search.SetSearchDepth(2);	//设置搜索的深度
	search.setNextOne(WChess);	//设置电脑执白
	CHESSMOVE move;				//棋子走法
	CHESSPos pos;				//棋子位置
	ChessType winner;			//获胜方
	FILE *fp;					//文件指针
	CEvaluation evalution;		//给工具栏用的
	fp = fopen("C:\\Users\\dell\\Desktop\\Carlos_chess\\Chess\\Project1\\Data.txt", "w");//设置文件地址
	CTool *tool=new CTool;					//工具类
	

	//closegraph();

	////int wow = _CRT_INT_MAX*0.0001;

	////printf("%f\n", PosValue[3][3] );
	////printf("%f\n", 0.0001);
	////printf("%f\n", PosValue[3][3] * INT_MAX * 0.0001);
	////printf("%f\n", PosValue[3][3] * 4 * 0.0001);
	////system("pause");

	////printf("%d\n", wow);

	////CHESSBOARD[7][7] = BChess;
	////printf("%d\n", evalution.evaluate(CHESSBOARD, WChess));
	////printf("%d\n", evalution.evaluate(CHESSBOARD, BChess));
	////CHESSBOARD[7][7] = NOCHESS;

	////CHESSBOARD[1][1] = WChess;
	////printf("%d\n", evalution.evaluate(CHESSBOARD, WChess));
	////printf("%d\n", evalution.evaluate(CHESSBOARD, BChess));
	////CHESSBOARD[1][1] = NOCHESS;

	////CHESSBOARD[1][2] = WChess;
	////printf("%d\n", evalution.evaluate(CHESSBOARD, WChess));
	////printf("%d\n", evalution.evaluate(CHESSBOARD, BChess));
	//CHESSBOARD[7][7] = BChess;
	//printf("%d\n", evalution.evaluate(CHESSBOARD, WChess));
	//printf("%d\n\n", evalution.evaluate(CHESSBOARD, BChess));

	//CHESSBOARD[7][8] = BChess;
	//printf("%d\n", evalution.evaluate(CHESSBOARD, WChess));
	//printf("%d\n\n", evalution.evaluate(CHESSBOARD, BChess));

	//CHESSBOARD[7][9] = BChess;
	//printf("%d\n", evalution.evaluate(CHESSBOARD, WChess));
	//printf("%d\n\n", evalution.evaluate(CHESSBOARD, BChess));

	//CHESSBOARD[7][10] = BChess;
	//printf("%d\n", evalution.evaluate(CHESSBOARD, WChess));
	//printf("%d\n\n", evalution.evaluate(CHESSBOARD, BChess));

	//CHESSBOARD[7][11] = BChess;
	//printf("%d\n", evalution.evaluate(CHESSBOARD, WChess));
	//printf("%d\n\n", evalution.evaluate(CHESSBOARD, BChess));


	//system("pause");
	while (1)
	{
		cleardevice();
		version.showChessBoard();
		version.showChess(CHESSBOARD);//更新棋盘
		version.showScore(CHESSBOARD, WChess, evalution);//刷新数据栏

		//玩家下棋
		pos = version.getNextStep(CHESSBOARD, BChess, step_sum, fp, evalution, tool);
		if (pos.x==16) {
			continue;//悔棋
		}
		version.showScore(CHESSBOARD, WChess, evalution);//刷新数据栏
		//debug
		setbkcolor(WHITE);	// 设置背景色为白色
		cleardevice();
		version.showChessBoard();
		version.showChess(CHESSBOARD);
		if (search.IsGameOver(CHESSBOARD, BChess))
		{
			winner = BChess;
			break;
		}
		search.setNextOne(WChess);
		move = search.SearchAGoodMove(CHESSBOARD, WChess);//电脑下棋 自带更新棋盘
		tool->addChess(move.StonePos.x, move.StonePos.y);//加到历史记录里面
		step_sum++;
		if (search.IsGameOver(CHESSBOARD, WChess))
		{
			winner = WChess;
			break;
		}
		version.showChess(CHESSBOARD);
		version.showScore(CHESSBOARD, BChess, evalution);
	}
	//version.showChess(CHESSBOARD);
	//system("pause");

	closegraph();//TODO

	if (winner == WChess)
	{
		printf("Winner is WHITE!\n");
	}
	else if (winner == BChess)
	{
		printf("Winner is BLACK!\n");
	}

	system("pause");
	return 0;
}