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


    void on_pushButton_clicked();

    void on_pushButton_2_clicked();

    void on_pushButton_3_clicked();

    void on_pushButton_4_clicked();

    void on_pushButton_5_clicked();

    void on_pushButton_6_clicked();

    void on_pushButton_7_clicked();

    void on_pushButton_8_clicked();

    void on_pushButton_9_clicked();

private:
    Ui::DialogBuyTerre *ui;
    int m_unitWanted = 0;
    int m_x;
    int m_y;
    char m_type = 't';
    bool m_value;
};

#endif // DIALOGBUYTERRE_H
