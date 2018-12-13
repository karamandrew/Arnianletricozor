#ifndef DIALOGSHOWCOMMANDS_H
#define DIALOGSHOWCOMMANDS_H

#include <QDialog>

namespace Ui {
class DialogShowCommands;
}

class DialogShowCommands : public QDialog
{
    Q_OBJECT

public:
    explicit DialogShowCommands(QWidget *parent = nullptr);
    ~DialogShowCommands();

private:
    Ui::DialogShowCommands *ui;
};

#endif // DIALOGSHOWCOMMANDS_H
