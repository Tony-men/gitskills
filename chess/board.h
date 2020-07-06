#ifndef BOARD_H
#define BOARD_H

#include <QWidget>
#include"stone.h"
#include"Step.h"
class Board : public QWidget
{
    Q_OBJECT
public:
    explicit Board(QWidget *parent = nullptr);
    void paintEvent(QPaintEvent *);//画棋盘
    void init(bool bRedSide);

    Stone _s[32];//定义32颗棋子
    int _r;//棋子的半径
    void drawStone(QPainter& painter,int id);//画棋子

    int _selectid;
    bool _bRedTurn;
    bool _bSide;




    //通过行列返回像素的位置
    QPoint center(int row,int col);
    QPoint center(int id);
    int GetStoneId(int row,int col);
    bool SameColor(int id1,int id2);


    //走棋
    QVector<Step*> _steps;
    void saveStep(int moveid,int killedid,int row,int col,QVector<Step *>& steps);//存储走棋，用来悔棋和人机计算

    void mouseReleaseEvent(QMouseEvent *event) ;
    bool getRowCol(QPoint pt,int& row, int& col);
    virtual void Click(int id,int row,int col);
    void Click(QPoint pt);
    void TrySelectStone(int id);
    void TryMoveStone(int killedid,int row,int col);
    void killStone(int id);
    void reliveStone(int id);
    void moveStone(int moveid, int killedid, int row, int col);
    void moveStone(int moveid, int row, int col);
    void backOne();
    void back(Step* step);
    virtual void back();


    bool iscanmove(int moveid,int row,int col,int killedid);
    bool iscanmoveJiang(int moveid,int killedid,int row,int col);
    bool iscanmoveShi(int moveid,int row,int col);
    bool iscanmoveXiang(int moveid,int row,int col);
    bool iscanmoveChe(int moveid,int row,int col);
    bool iscanmoveMa(int moveid,int row,int col);
    bool iscanmovePao(int moveid,int row,int col,int killedid);
    bool iscanmoveBing(int moveid,int row,int col);
    int relation(int moveid,int row, int col);
    bool isbottom(int id);//判断是否在棋盘下侧
    bool isempty(int row,int col);
    //炮  车 走法的辅助函数，返回直线间棋子的个数
    int  Line(int row,int col,int row1,int col1);
    void whoWin();
    void setdlg(bool isred);

signals:

public slots:
    void slotBack();

};

#endif // BOARD_H
