#include "ChooseDlg.h"
#include <QVBoxLayout>

ChooseDlg::ChooseDlg(QWidget *parent) : QDialog(parent)
{
    QVBoxLayout* lay = new QVBoxLayout(this);
    lay->setMargin(100);
    lay->addWidget(_buttons[0] = new QPushButton("人机对战"));
    lay->addStretch(50);
    lay->addWidget(_buttons[1] = new QPushButton("人人对战"));
    lay->addStretch(50);

    lay->addWidget(_buttons[2] = new QPushButton("网络对战(服务端)"));
    lay->addStretch(50);

    lay->addWidget(_buttons[3] = new QPushButton("网络对战(客户端)"));
    lay->addStretch(50);
    this->setLayout(lay);

    for(int i=0; i<4; ++i)
    {
        connect(_buttons[i], SIGNAL(clicked()), this, SLOT(slotClicked()));
    }
}

void ChooseDlg::slotClicked()
{
    QObject* s = sender();
    for(int i=0; i<4; ++i)
    {
        if(_buttons[i] == s)
        {
            this->_selected = i;
            break;
        }
    }
    accept();
}

ChooseDlg::~ChooseDlg()
{

}

