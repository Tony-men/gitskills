#ifndef STONE_H
#define STONE_H

#include<QString>
class Stone
{
public:
    Stone();
    enum TYPE{JIANG, CHE, PAO, MA, BING,SHI, XIANG};

    int _row;
    int _col;
    int _id;
    bool _dead;
    bool _isred;
    int _type;//棋子的类型
    void rotate();

    void init(int id)//棋子初始化
    {
        struct {
            int row,col;
            Stone::TYPE type;
        }pos[16] = {
        {0, 0, Stone::CHE},
        {0, 1, Stone::MA},
        {0, 2, Stone::XIANG},
        {0, 3, Stone::SHI},
        {0, 4, Stone::JIANG},
        {0, 5, Stone::SHI},
        {0, 6, Stone::XIANG},
        {0, 7, Stone::MA},
        {0, 8, Stone::CHE},

        {2, 1, Stone::PAO},
        {2, 7, Stone::PAO},
        {3, 0, Stone::BING},
        {3, 2, Stone::BING},
        {3, 4, Stone::BING},
        {3, 6, Stone::BING},
        {3, 8, Stone::BING},

        };

        if(id < 16)//红棋
        {
            _row = pos[id].row;
            _col = pos[id].col;
            _type = pos[id].type;
        }
        //黑棋
        //行数为9    列数为8
        else {
            _row = 9-pos[id-16].row;
            _col = 8-pos[id-16].col;
            _type = pos[id-16].type;
        }
        _id = id;
        _dead = false;
        _isred = id<16;//红黑棋各一半
    }
    QString getText()//根据类型返回棋子的text
    {
        switch (this->_type)
        {
            case CHE:
                return "车";
              case JIANG:
                return "将";
        case PAO:
            return "炮";
           case MA:
            return "马";
        case BING:
            return "兵";
           case SHI:
            return "士";
        case XIANG:
            return "相";
        }
        return "错误";

    }
};

#endif // STONE_H
