#include "version.h"

CTool::CTool()
{
}

CTool::~CTool()
{
}

CVersion::CVersion() {
	initgraph((board_length + 1 + 4) * box_length, (board_length + 1) * box_length, NULL);	//打开绘图环境
	setbkcolor(WHITE);	// 设置背景色为白色
	cleardevice();
}

CVersion::~CVersion() {
	closegraph();	//关闭绘图环境
}

//显示棋盘
Status CVersion::showChessBoard() {
	setlinecolor(LIGHTGRAY);	//设置线段颜色，这里是灰色
	setlinestyle(PS_SOLID, 3, NULL, 0);	//设置线段格式	这里是实线，3个像素宽
	for (int i = 1; i <= board_length; i++)
	{
		line(i*box_length, box_length, i*box_length, box_length*board_length);	//竖线
	}
	for (int i = 1; i <= board_length; i++)
	{
		line(box_length, i*box_length, box_length*board_length, i*box_length);	//横线
	}
	for (int i = 1; i <= board_length; i++)
	{
		for (int j = 1; j <= board_length; j++)
		{
			setfillcolor(WHITE);	//设置当前填充色为白色
			fillcircle(i*box_length, j*box_length, 2);	//给交点打点，大小为3个像素。这个不太好做成缩放，不太好和别的参数挂钩。
		}
	}
	return OK;
}

//显示棋子
Status CVersion::showChess(BYTE chessBoard[board_length][board_length]) {
	setlinecolor(BLACK);	//棋子的边的颜色，黑色
	setlinestyle(PS_SOLID, 2, NULL, 0);	//设置线段格式	这里是实线，2个像素宽
	for (int i = 0; i < board_length; i++)
	{
		for (int j = 0; j < board_length; j++)
		{
			if (CHESSBOARD[i][j] == BChess)
			{
				setfillcolor(BLACK);	//设置当前填充色为黑色
				fillcircle((i + 1)*box_length, (j + 1)*box_length, chess_r);	//黑子
			}
			if (CHESSBOARD[i][j] == WChess)
			{
				setfillcolor(WHITE);	//设置当前填充色为白色
				fillcircle((i + 1)*box_length, (j + 1)*box_length, chess_r);	//白子
			}
		}
	}
	return OK;
}

//显示按键
Status CVersion::showButton(MENU menu) {

	return OK;
}

//获得用户的下一步走法
CHESSPos CVersion::getNextStep(BYTE(&chessBoard)[board_length][board_length], ChessType chess, int &step_sum, FILE *&fp, CEvaluation eva, CTool *tool)
{

	MOUSEMSG m;
	int value_INT;//始终站在玩家的立场打分
	char value_STRING[20];
	CHESSPos pos;

	while (1)
	{
		m = GetMouseMsg();

		//光标落在棋盘上
		if (m.x > box_length*0.5 && m.x < (board_length + 0.5)*box_length && m.y > box_length*0.5 && m.y < (board_length + 0.5)*box_length)
		{

			//按住右键的话，则显示当前鼠标位置落子的话，场面分值
			if (m.uMsg == WM_RBUTTONDOWN && CHESSBOARD[(m.x / (box_length / 2) - 1) / 2][(m.y / (box_length / 2) - 1) / 2] == NOCHESS)
			{
				RECT purScore = { (board_length + 1)*box_length, (1 + 2) * box_length, (board_length + 1 + 4)*box_length, (1 + 2 + 2)*box_length };//两格
				clearrectangle((board_length + 1)*box_length, (1 + 2) * box_length, (board_length + 1 + 4)*box_length, (1 + 2 + 2)*box_length);//清空

				CHESSBOARD[(m.x / (box_length / 2) - 1) / 2][(m.y / (box_length / 2) - 1) / 2] = chess;//假设落子
				value_INT = eva.evaluate(chessBoard, WChess);
				CHESSBOARD[(m.x / (box_length / 2) - 1) / 2][(m.y / (box_length / 2) - 1) / 2] = NOCHESS;//恢复棋盘

				itoa(value_INT, value_STRING, 10);
				settextcolor(LIGHTBLUE);
				drawtext(_T(value_STRING), &purScore, DT_CENTER | DT_VCENTER | DT_SINGLELINE);

				continue;//按着右键的时候不可以落子
			}

			//真实落子
			if (m.uMsg == WM_LBUTTONUP && CHESSBOARD[(m.x / (box_length / 2) - 1) / 2][(m.y / (box_length / 2) - 1) / 2] == NOCHESS)
			{
				CHESSBOARD[(m.x / (box_length / 2) - 1) / 2][(m.y / (box_length / 2) - 1) / 2] = chess;	//确定鼠标点在哪一个格子上
				pos.x = (m.x / (box_length / 2) - 1) / 2;
				pos.y = (m.y / (box_length / 2) - 1) / 2;
				tool->addChess(pos.x, pos.y);
				step_sum++;
				break;
			}
		}

		//光标落在悔棋区域
		if (m.x > (board_length + 1)*box_length && m.x<(board_length + 1 + 4)*box_length && m.y>(1 + 2 + 2) * box_length && m.y < (1 + 2 + 2 + 1)*box_length && m.uMsg == WM_LBUTTONUP)
		{
			tool->retractChess(VS_type);
			pos.x =16;//悔棋的标志
			pos.y =16;
			break;
		}
	}
	return pos;
}

Status CVersion::showScore(BYTE chessboard[board_length][board_length], ChessType turn, CEvaluation eva)
{
	//清空
	clearrectangle((board_length + 1)*box_length, 0, (board_length + 1 + 4)*box_length, (1 + 2 + 1) * box_length);
	settextcolor(RED);
	//显示轮谁走 一格
	RECT whoseTurn = { (board_length + 1)*box_length, 0, (board_length + 1 + 4)*box_length, 1 * box_length };
	if (turn == BChess)
	{
		drawtext(_T("Black turn."), &whoseTurn, DT_CENTER | DT_VCENTER | DT_SINGLELINE);
	}
	else
	{
		drawtext(_T("White turn."), &whoseTurn, DT_CENTER | DT_VCENTER | DT_SINGLELINE);
	}

	//显示此时的估值 两格
	RECT purScore = { (board_length + 1)*box_length, 1 * box_length, (board_length + 1 + 4)*box_length, (1 + 2)*box_length };
	int value_INT = eva.evaluate(chessboard, BChess);//始终站在玩家的立场打分
	char value_STRING[20];
	itoa(value_INT, value_STRING, 10);
	drawtext(_T(value_STRING), &purScore, DT_CENTER | DT_VCENTER | DT_SINGLELINE);

	//悔棋键位
	RECT retract = { (board_length + 1)*box_length, (1 + 2 + 2) * box_length, (board_length + 1 + 4)*box_length, (1 + 2 + 2 + 1)*box_length };
	settextcolor(RED);
	drawtext(_T("悔一步棋"), &retract, DT_CENTER | DT_VCENTER | DT_SINGLELINE);

	return Status();
}
