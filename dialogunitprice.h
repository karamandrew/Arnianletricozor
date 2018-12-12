#ifndef DIALOGUNITPRICE_H
#define DIALOGUNITPRICE_H

#include <QDialog>

namespace Ui {
class DialogUnitPrice;
}

class DialogUnitPrice : public QDialog
{
    Q_OBJECT

public:
    explicit DialogUnitPrice(QWidget *parent = nullptr);
    ~DialogUnitPrice();

private:
    Ui::DialogUnitPrice *ui;
};

#endif // DIALOGUNITPRICE_H
