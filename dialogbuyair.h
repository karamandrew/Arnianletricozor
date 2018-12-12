#ifndef DIALOGBUYAIR_H
#define DIALOGBUYAIR_H

#include <QDialog>

namespace Ui {
class DialogBuyAir;
}

class DialogBuyAir : public QDialog
{
    Q_OBJECT

public:
    explicit DialogBuyAir(QWidget *parent = nullptr);
        void getInfo(int x, int y, bool value);
    ~DialogBuyAir();

private slots:
    void on_spinBox_valueChanged(int arg1);

    void on_spinBox_editingFinished();

private:
    Ui::DialogBuyAir *ui;
    int m_unitWanted = 0;
    int m_x;
    int m_y;
    char m_type = 'a';
    bool m_value;
};

#endif // DIALOGBUYAIR_H
