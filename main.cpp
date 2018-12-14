#include "mainwindow.h"
#include"gameobject.h"
#include "game.h"
#include <QApplication>
#include <QHBoxLayout>
#include "introwindow.h"

int main(int argc, char *argv[])
{


    QApplication a(argc, argv);

    MainWindow w;
    IntroWindow intro;
    intro.show();
    intro.setWindow(&w);

    //Game& game=Game::Instance(); //

   // game.start(w);

    //w.show();

    return a.exec();

}
