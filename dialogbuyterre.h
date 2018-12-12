#ifndef DIALOGBUYTERRE_H
#define DIALOGBUYTERRE_H

#include <QDialog>

namespace Ui {
class DialogBuyTerre;
}

class DialogBuyTerre : public QDialog
{
    Q_OBJECT

public:
    explicit DialogBuyTerre(QWidget *parent = nullptr);
    void getInfo(int x, int y, bool value);
    ~DialogBuyTerre();

private slots:
    void on_spinBox_valueChanged(int arg1);

    void on_spinBox_editingFinished();


private:
    Ui::DialogBuyTerre *ui;
    int m_unitWanted = 0;
    int m_x;
    int m_y;
    char m_type = 't';
    bool m_value;
};

#endif // DIALOGBUYTERRE_H
