#ifndef SINGLEGAME_H
#define SINGLEGAME_H

#include"board.h"
class SingleGame: public Board
{
    Q_OBJECT
public:
    explicit SingleGame(QWidget *parent = 0);


    int _level;
    Step*  GetBestMove();

    void getAllPossibleMove(QVector<Step *>& steps);
    virtual void Click(int id,int row,int col);
    void fakeMove(Step* step);//假设走这一步
    void unfakeMove(Step* step);//再退回来
    int score();//局面分
    int getMinScore(int level, int curMin);
    int getMaxScore(int level, int curMax);

    void back();//悔棋
public slots:
    void computerMove();
};

#endif // SINGLEGAME_H
