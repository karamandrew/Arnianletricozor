#ifndef DIALOGSHOWRULES_H
#define DIALOGSHOWRULES_H

#include <QDialog>

namespace Ui {
class DialogShowRules;
}

class DialogShowRules : public QDialog
{
    Q_OBJECT

public:
    explicit DialogShowRules(QWidget *parent = nullptr);
    ~DialogShowRules();

private:
    Ui::DialogShowRules *ui;
};

#endif // DIALOGSHOWRULES_H
