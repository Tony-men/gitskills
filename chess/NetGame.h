#ifndef NETGAME_H
#define NETGAME_H
#include <QTcpServer>
#include <QTcpSocket>
#include"board.h"
class NetGame : public Board
{
    Q_OBJECT
public:
    explicit NetGame(bool server, QWidget *parent = 0);
    ~NetGame();

    bool _bServer;
    QTcpServer* _server;
    QTcpSocket* _socket;

    void back();
    void click(int id, int row, int col);

    void backFromNetwork(QByteArray buf);
    void clickFromNetwork(QByteArray buf);
    void initFromNetwork(QByteArray buf);

signals:

public slots:
    void slotNewConnection();
    void slotDataArrive();
};

#endif // NETGAME_H
