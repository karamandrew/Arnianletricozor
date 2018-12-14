#ifndef ORANGESTARWIN_H
#define ORANGESTARWIN_H

#include <QDialog>

namespace Ui {
class OrangeStarWin;
}

class OrangeStarWin : public QDialog
{
    Q_OBJECT

public:
    explicit OrangeStarWin(QWidget *parent = nullptr);
    ~OrangeStarWin();

private:
    Ui::OrangeStarWin *ui;
};

#endif // ORANGESTARWIN_H
