#include "mainwindow.h"
#include"gameobject.h"
#include "game.h"
#include <QApplication>
#include <QHBoxLayout>

int main(int argc, char *argv[])
{


    QApplication a(argc, argv);

    MainWindow w;
    Game& game=Game::Instance(); //

    game.start(w);

    w.show();

    return a.exec();

}
