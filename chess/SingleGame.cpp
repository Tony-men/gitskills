#include "SingleGame.h"
#include <QTimer>
#include <QDebug>
SingleGame::SingleGame(QWidget *parent) : Board(parent)
{
//    this->resize(600,600);
//    this->setWindowTitle("中国象棋");
    _level = 1;
}
void SingleGame::Click(int id, int row, int col)
{
    if(_bRedTurn)//不该红棋走就不要乱点
    {
        Board::Click(id,row,col);
        if(!_bRedTurn)
        {
            QTimer::singleShot(100, this, SLOT(computerMove()));
        }
    }


}


void SingleGame::computerMove()
{
    Step* step = GetBestMove();
    moveStone(step->_moveid, step->_killedid, step->_rowTo, step->_colTo);
    delete step;
    update();
}
void SingleGame::getAllPossibleMove(QVector<Step *> &steps)//先遍历某一方的所有棋子，再遍历整个棋盘，得到每个棋子的所有走棋情况
{
    int min, max;
    if(this->_bRedTurn)
    {
        min = 0, max = 16;

    }
    else
    {
        min = 16, max = 32;
    }
    for(int i=min;i<max; i++)
    {
        if(this->_s[i]._dead)
            {
            continue;
            }
        for(int row = 0; row<=9; row++)
        {
            for(int col=0; col<=8; col++)
            {
                int killid = GetStoneId(row, col);
                if(iscanmove(i, killid, row, col))
                {
                    qDebug() << _s[i]._row <<"," << _s[i]._col<<"的"<<_s[i].getText()<<"可以到达 "
                             << row<<","<<col;

                    saveStep(i, killid, row, col, steps);
                }
            }
        }
    }
}
void SingleGame::fakeMove(Step* step)//走过去试试
{
   killStone(step->_killedid);
   moveStone(step->_moveid,step->_rowTo,step->_colTo);
}
void SingleGame::unfakeMove(Step* step)//试完了还原
{
    reliveStone(step->_killedid);
    moveStone(step->_moveid,step->_rowFrom,step->_colFrom);
}
//评价局面分,返回 黑棋总分- 红棋总分！
int SingleGame::score()
{
    int redTotalScore =0;
    int blackTotalScore =0;
    //    enum TYPE{JIANG, CHE, PAO, MA, BING,SHI, XIANG};
    static int chessScore[] = {100,50,50,20,1500,10 ,10};
    //红棋的总分
    for(int i =0 ; i< 16;i++)
    {
        if(_s[i]._dead) continue;
        redTotalScore += chessScore[_s[i]._type];
    }

     //黑棋的总分
    for(int i =16 ; i< 32;i++)
    {
        if(_s[i]._dead) continue;
        blackTotalScore += chessScore[_s[i]._type];
    }
    return blackTotalScore - redTotalScore;
}
Step* SingleGame::GetBestMove()
{
    //1.//先遍历某一方的所有棋子，再遍历整个棋盘，得到每个棋子的所有走棋情况,放在一个vector中
    Step* ret = NULL;
    QVector<Step*> steps;
    getAllPossibleMove(steps);
    int maxInAllMinScore = -300000;

    while(steps.count())
    {
        Step* step = steps.last();
        steps.removeLast();

        fakeMove(step);
        int minScore = score();
        unfakeMove(step);

        if(minScore > maxInAllMinScore)
        {
            if(ret) delete ret;

            ret = step;
            maxInAllMinScore = minScore;
        }
        else
        {
            delete step;
        }
    }
    return ret;


}
int SingleGame::getMinScore(int level, int curMin)
{
    if(level == 0)
        return score();

    QVector<Step*> steps;
    getAllPossibleMove(steps);
    int minInAllMaxScore = 300000;

    while(steps.count())
    {
        Step* step = steps.last();
        steps.removeLast();

        fakeMove(step);
        int maxScore = getMaxScore(level-1, minInAllMaxScore);
        unfakeMove(step);
        delete step;

        if(maxScore <= curMin)//剪纸
        {
            while(steps.count())
            {
                Step* step = steps.last();
                steps.removeLast();
                delete step;
            }
            return maxScore;
        }

        if(maxScore < minInAllMaxScore)
        {
            minInAllMaxScore = maxScore;
        }


    }
    return minInAllMaxScore;
}

int SingleGame::getMaxScore(int level, int curMax)
{
    if(level == 0)
        return score();

    QVector<Step*> steps;
    getAllPossibleMove(steps);
    int maxInAllMinScore = -300000;

    while(steps.count())
    {
        Step* step = steps.last();
        steps.removeLast();

        fakeMove(step);
        int minScore = getMinScore(level-1, maxInAllMinScore);
        unfakeMove(step);
        delete step;

        if(minScore >= curMax)
        {
            while(steps.count())
            {
                Step* step = steps.last();
                steps.removeLast();
                delete step;
            }
            return minScore;
        }
        if(minScore > maxInAllMinScore)
        {
            maxInAllMinScore = minScore;
        }


    }
    return maxInAllMinScore;
}
void SingleGame::back()
{
    if(_bRedTurn)
    {
        backOne();
        backOne();
    }
}
