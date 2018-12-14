#ifndef BLUEMOONWIN_H
#define BLUEMOONWIN_H

#include <QDialog>

namespace Ui {
class BlueMoonWin;
}

class BlueMoonWin : public QDialog
{
    Q_OBJECT

public:
    explicit BlueMoonWin(QWidget *parent = nullptr);
    ~BlueMoonWin();

private:
    Ui::BlueMoonWin *ui;
};

#endif // BLUEMOONWIN_H
