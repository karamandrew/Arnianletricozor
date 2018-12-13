#ifndef DIALOGLANGUAGE_H
#define DIALOGLANGUAGE_H

#include <QDialog>

namespace Ui {
class DialogLanguage;
}

class DialogLanguage : public QDialog
{
    Q_OBJECT

public:
    explicit DialogLanguage(QWidget *parent = nullptr);
    ~DialogLanguage();

private:
    Ui::DialogLanguage *ui;
};

#endif // DIALOGLANGUAGE_H
