#ifndef _SEARCHENGINE_H_
#define _SEARCHENGINE_H_
#include "MoveGenerator.h"
#include "Evaluation.h"


class CSearchEngine
{
public:
	CSearchEngine();
	virtual ~CSearchEngine();

	//博弈接口，为当前局面走出下一步
	virtual CHESSMOVE SearchAGoodMove(BYTE (&chessboard)[board_length][board_length], ChessType chess) = 0;

	//设定最大搜索深度
	virtual void SetSearchDepth(int nDepth) { SearchDepth = nDepth; };

	//设定搜索引擎（估值函数？？）
	virtual void SetEveluator(CEvaluation *pEval) { m_pEval = pEval; };

	//设定走法产生器
	virtual void SetMoveGenerator(CMoveGenerator *pMG) { m_pMG = pMG; };

	//设定显示思考进度的进度条——先不做

	//设定下一步该谁走
	virtual void setNextOne(ChessType next) { nextOne = next; };


	virtual BYTE MakeMove(CHESSMOVE* move, int type);//根据某一走法 改变棋盘
	virtual void UnMakeMove(CHESSMOVE* move);//根据某一走法 恢复原来的棋盘
	virtual int IsGameOver(BYTE position[board_length][board_length], ChessType chess);//判断chess这一步是否终结了比赛    0-没有结束     非零（应该是一个很大的值）-结束
protected:

	BYTE CurPosition[board_length][board_length];//搜索时用于当前结点棋盘状态的数组
	CHESSMOVE m_cmBestMove;//记录最佳走法的变量

	CMoveGenerator *m_pMG;//走法产生器的指针
	CEvaluation *m_pEval;//估值核心的指针

	int SearchDepth;//最大搜索深度
					//int m_nMaxDepth;//当前搜索的最大搜索深度 这个好像不是alpha-beta用的变量，所以不用

	int m_bGameOver;//是否结束

	ChessType nextOne;//下一步该谁走
private:

};

#endif // _SEARCHENGINE_H_


