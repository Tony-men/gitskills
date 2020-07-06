#include "board.h"
#include<QPainter>
#include<QMouseEvent>
#include<QDebug>
#include<QMessageBox>
Board::Board(QWidget *parent) : QWidget(parent)
{
    this->resize(600,600);
    //setMinimumSize(_r*18+1, _r*20+1);

    this->setWindowTitle("中国象棋");

    this->_r = 20;
    init(true);

}
void Board::init(bool bRedSide)
{
    for(int i=0; i<32; ++i)
    {
        _s[i].init(i);

    }
    if(bRedSide)
    {
        for(int i=0; i<32; ++i)
        {
            _s[i].rotate();
            qDebug() << _s[i]._row <<"," << _s[i]._col<<"的棋子是 " <<_s[i].getText()<<"id是"<<_s[i]._id
                     <<"color是"<<_s[i]._isred;
        }
        for(int i=16;i<32; i++)
        {
            if(this->_s[i]._dead)
                {
                continue;
                }
            for(int row = 0; row<=9; ++row)
            {
                for(int col=0; col<=8; ++col)
                {
                    int killid = GetStoneId(row, col);
                    if(iscanmove(i, killid, row, col))
                    {
                        qDebug() << _s[i]._row <<"," << _s[i]._col<<"的"<<_s[i].getText()<<"可以到达 "
                                 << row<<","<<col;
                    }
                }
            }
        }

    }
    _selectid = -1;
    _bRedTurn = true;
    _bSide = bRedSide;
    update();
}
void Board::paintEvent(QPaintEvent *)
{

    QPainter painter(this);
    int d= 50;
    _r = d/2;
    //10条横线
    for(int i=1; i<=10; i++)
    {
        painter.drawLine(QPoint(d, i*d),QPoint(9*d, i*d));
    }
    //9条竖线,注意楚河汉界
    for(int i=1; i<=9; i++)
    {
        if(i==1 || i==9)
        {
        painter.drawLine(QPoint(d*i, d),QPoint(i*d, 10*d));
        }
        else
        {
            painter.drawLine(QPoint(d*i, d),QPoint(i*d, 5*d));
            painter.drawLine(QPoint(d*i, 6*d),QPoint(i*d, 10*d));

        }
    }
    QFont font;
    font.setPointSize(16);
    font.setFamily("宋体");
    painter.setFont(font);
    painter.drawText(2*d,5.7*d,QString("楚河"));
    painter.drawText(7*d,5.7*d,QString("汉界"));
    //九宫格
    painter.drawLine(QPoint(d*4, d),QPoint(6*d, 3*d));
    painter.drawLine(QPoint(d*6, d),QPoint(4*d, 3* d));
    painter.drawLine(QPoint(d*4, 8*d),QPoint(6*d, 10* d));
    painter.drawLine(QPoint(d*6, 8*d),QPoint(4*d, 10* d));
    for(int i = 0;i<32;i++)
    {
        drawStone(painter,i);

    }

}
//通过行列返回像素的位置
QPoint Board::center(int row, int col)
{
    QPoint ret;
    ret.rx() = (col+1)*_r*2;
    ret.ry() = (row+1)*_r*2;
    return ret;

}
QPoint Board::center(int id)
{
    return center(_s[id]._row,_s[id]._col);
}

void Board::drawStone(QPainter& painter,int id)//画棋子
{
    if(_s[id]._dead)//如果棋子死掉，就不画
           return;

    QPoint c= center(id);
    QRect rect = QRect(c.x()-_r,c.y()-_r,_r*2,_r*2);

    if(id == _selectid)//点到的棋子变成灰色
    {
        painter.setBrush(Qt::gray);
    }
    else {
        painter.setBrush(QBrush(Qt::yellow));

    }
    //先用黑笔画圈
    painter.setPen(Qt::black);
    painter.drawEllipse(center(id), _r, _r);
    //前16个黑棋，后16个红棋
    if(_s[id]._isred)
    {
        painter.setPen(Qt::red);
    }

    //painter.setFont(QFont("system",_r,700));
    //棋子的字
    painter.drawText(rect,_s[id].getText(),QTextOption(Qt::AlignCenter));

}


bool Board::getRowCol(QPoint pt, int &row, int &col)
{
    for(row = 0; row<=9; row++)
    {
        for(col = 0; col<=8; col++)
        {
            QPoint c = center(row,col);
            int dx = c.x()-pt.x();
            int dy = c.y()-pt.y();
            int disc = dx*dx + dy*dy;
            if(disc < _r*_r)
                return true;

        }
    }
    return  false;

}
void Board::killStone(int id)
{
    if(id == -1) return;
    _s[id]._dead = true;
}
void Board::reliveStone(int id)
{
    if(id == -1) return;
    _s[id]._dead = false;
}
int Board::Line(int row, int col, int row1, int col1)
{
    //走直线
    if(row != row1 && col != col1) return -1;
    int ret = 0;
    if(row == row1)//横走
    {
        int min = col < col1 ? col : col1;
        int max = col < col1 ? col1 : col;
        for(int i = min+1;i < max;i++)
        {
           if(!isempty(row,i))  ret++;
        }
    }
    else //竖走
    {
       int min = row < row1 ? row : row1;
       int max = row < row1 ? row1 : row;
       for(int i = min +1;i<max;i++)
       {
           if(!isempty(i,col)) ret++;

       }
    }
    return ret;

}



int Board::relation(int moveid, int row, int col)
{
    int dr = _s[moveid]._row - row;
    int dc = _s[moveid]._col - col;
    int d = abs(dr) * 10 + abs(dc);
    return d;
}


bool Board::SameColor(int id1, int id2)
{
    if(id1 == -1 || id2 == -1) return  false;
    return (_s[id1]._isred == _s[id2]._isred);
}
bool Board::isbottom(int id)
{

    return _bSide == _s[id]._isred;
}

bool Board::isempty(int row, int col)
{
    int i;
    for( i = 0; i<32; i++)//判断鼠标是否点到棋子
   {
       if(_s[i]._row == row && _s[i]._col == col && _s[i]._dead == false)
       {
           break;
       }
   }
   if(i<32)
   {
       return false;
   }
   return true;
}

bool Board::iscanmoveJiang(int moveid,int killedid,int row,int col)//将的走棋规则
{
    if(killedid != -1 && _s[killedid]._type == Stone::JIANG)//将面对面时可以直接吃
        return iscanmoveChe(moveid, row,  col);
    //1.只能在九宫格内走
    //2.移动的步长不能大于1
    //通过d可以限制走法
    //  3.只能直走
    int d = relation(moveid,row,col);

    if(d != 1 && d != 10) return false;

    if(col < 3 || col > 5) return false;
    if(isbottom(moveid))
    {
        if(row < 7) return false;
    }
    else
    {
        if(row > 2) return false;
    }
    return true;
}
bool Board::iscanmoveShi(int moveid,int row,int col)//士的走棋规则
{
    //1.只能在九宫格内走
    if(isbottom(moveid))
    {
        if(row < 7) return false;
    }
    else
    {
        if(row > 2) return false;
    }
    if(col < 3 || col > 5) return false;

    //2.只能在5个位置斜着走
    int d = relation(moveid,row,col);

    if(row == 0 && col == 3 && d == 11 ) return true;
    if(row == 0 && col == 5 && d == 11 ) return true;
    if(row == 1 && col == 4 && d == 11 ) return true;
    if(row == 2 && col == 3 && d == 11 ) return true;
    if(row == 2 && col == 5 && d == 11 ) return true;

    if(row == 7 && col == 3 && d == 11 ) return true;
    if(row == 7 && col == 5 && d == 11 ) return true;
    if(row == 8 && col == 4 && d == 11 ) return true;
    if(row == 9 && col == 3 && d == 11 ) return true;
    if(row == 9 && col == 5 && d == 11 ) return true;

    return  false;

}
bool Board::iscanmoveXiang(int moveid,int row,int col)//象的走棋规则
{
    //1.象走田
    int d = relation(moveid,row,col);
    if(d != 22) return false;
    //2.不过河
    if(isbottom(moveid))
    {
        if(row < 5 ) return false;
    }
    else
    {
        if(row > 4 ) return false;
    }
    //3.撇脚象
    int dr = (_s[moveid]._row + row)/2;
    int dc = (_s[moveid]._col + col)/2;
    if(!isempty(dr,dc)) return  false;
    return  true;
}
bool Board::iscanmoveChe(int moveid,int row,int col)//车的走棋规则
{
    //走直线，直线之间不可以有棋子
    if(!Line(row,col,_s[moveid]._row,_s[moveid]._col))
    {
       // qDebug() << _s[moveid]._row <<"," << _s[moveid]._col<<"的车 can move to " <<row<<","<<col;

        return true;
    }

    return  false;
}
bool Board::iscanmoveMa(int moveid,int row,int col)//马的走棋规则
{
    //1.马走日
    int dr,dc;
    int d = relation(moveid,row,col);
    if(d != 12 && d != 21) return false;
    //2.撇脚马
    if(d == 12)
    {
        dr = _s[moveid]._row;
        dc = (_s[moveid]._col + col)/2;
        if(!isempty(dr,dc)) return false;
    }
    if(d == 21)
    {
        dr = (_s[moveid]._row + row)/2;
        dc = _s[moveid]._col;
        if(!isempty(dr,dc)) return false;
    }
    return  true;
}
bool Board::iscanmovePao(int moveid,int row,int col,int killedid)//炮的走棋规则
{
    int ret = Line(row,col,_s[moveid]._row,_s[moveid]._col);
    if(killedid != -1)//炮吃棋的时候，中间必须要隔有一个棋子
    {
        if(ret == 1 ) return true;
    }
    else
    {
        if(ret == 0) return true;
    }
    return  false;
}
bool Board::iscanmoveBing(int moveid,int row,int col)//兵的走棋规则
{
    //移动步长为1
    int d = relation(moveid,row,col);
    if(d != 1 && d != 10) return false;
    //不能退，且过河后可以左右走
    if(isbottom(moveid))
    {
        if(row > _s[moveid]._row) return false;
        if(_s[moveid]._row >= 5 && row == _s[moveid]._row) return false;
    }
    else
    {
        if(row < _s[moveid]._row) return false;
        if(_s[moveid]._row <= 4 && row == _s[moveid]._row) return false;
    }

    return  true;
}


bool Board::iscanmove(int moveid, int row, int col, int killedid)
{
    //如果两次选择同色的棋子
    if(SameColor(moveid,killedid))
    {return false;}

    switch(_s[moveid]._type)
    {
    case Stone::JIANG:
        return iscanmoveJiang( moveid,killedid, row,  col);
    case Stone::SHI:
        return iscanmoveShi( moveid, row,  col);
    case Stone::XIANG:
        return iscanmoveXiang( moveid, row,  col);
    case Stone::CHE:
        return iscanmoveChe( moveid, row,  col);
    case Stone::MA:
        return iscanmoveMa( moveid, row,  col);
    case Stone::PAO:
        return iscanmovePao( moveid, row,  col,  killedid);
    case Stone::BING:
        return iscanmoveBing( moveid, row,  col);
    }

    return  false;
}


void Board::saveStep(int moveid, int killedid, int row, int col, QVector<Step *> &steps)
{
    Step* step  = new Step;
    step->_rowFrom = _s[moveid]._row;
    step->_rowTo = row;
    step->_colFrom = _s[moveid]._col;
    step->_colTo = col;
    step->_moveid = moveid;
    step->_killedid = killedid;

    steps.append(step);

}
void Board::moveStone(int moveid, int killedid, int row, int col)
{
    saveStep(moveid, killedid, row, col, _steps);
    killStone(killedid);
    moveStone(moveid,row,col);
    whoWin();

}

void Board::moveStone(int moveid, int row, int col)
{
    _s[moveid]._row = row;
    _s[moveid]._col = col;
    _bRedTurn = !_bRedTurn;
}


int Board::GetStoneId(int row, int col)
{
    for(int i =0;i<32;i++)
    {
        if(_s[i]._row == row && _s[i]._col == col && _s[i]._dead == false )
        {
            return i;
        }
    }
    return -1;

}


void Board::TryMoveStone(int killedid, int row, int col)
{
    if(killedid != -1 && SameColor(killedid, _selectid))
    {
       TrySelectStone(killedid);
        return;
    }

    bool ret = iscanmove(_selectid,row,col,killedid);
    if(ret)
    {
        moveStone(_selectid,killedid,row,col);
        _selectid = -1;
       update();
    }

}
void Board::TrySelectStone(int id)
{

        if(id == -1 ) return;
        if(_bRedTurn != _s[id]._isred) {return;}


         _selectid = id;

         update();

}
void Board::Click(int id, int row, int col)
{
   if(this->_selectid == -1)
   {
       TrySelectStone(id);
   }
   else
   {
        TryMoveStone(id,row,col);
   }
}
void Board::Click(QPoint pt)
{
    int row,col;
    bool isin = getRowCol(pt,row,col);
    if(!isin)//点到棋盘外就一直返回
        return;
    int id = GetStoneId(row,col);
    Click(id,row,col);

}


void Board::mouseReleaseEvent(QMouseEvent *event)
{

    if(event->button() != Qt::LeftButton) return;
    Click(event->pos());

}


void Board::back(Step *step)
{
    reliveStone(step->_killedid);
    moveStone(step->_moveid, step->_rowFrom, step->_colFrom);
}

void Board::backOne()
{
    if(this->_steps.size() == 0) return;

    Step* step = this->_steps.last();
    _steps.removeLast();
    back(step);

    update();
    delete step;
}

void Board::back()
{
    backOne();
}

void Board::slotBack()
{
    back();
}
void Board::whoWin()
{
   if(_s[4]._dead == true && _s[20]._dead == false)
    {
        QMessageBox message(QMessageBox::Information,"提示","黑棋胜利！");
        message.setFont(QFont("楷体",16,QFont::Bold));
        message.exec();

    }
   if(_s[20]._dead == true && _s[4]._dead == false)
    {
        QMessageBox message(QMessageBox::Information,"提示","红棋胜利！");
        message.setFont(QFont("楷体",16,QFont::Bold));
        message.exec();

    }
}

