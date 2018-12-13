#ifndef MAINWINDOW_H
#define MAINWINDOW_H
#include <QMouseEvent>
#include <QMainWindow>
#include <QPushButton>
#include <QLabel>
#include"gameobject.h"
#include "map.h"
#include "terrain.h"
#include "dialogunitprice.h"
#include "dialogshowrules.h"
#include "dialogshowcommands.h"
#include "dialoglanguage.h"



class Gameobject;
namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = nullptr);
    ~MainWindow();
    void redraw();
    void createMapObjects();
    Terrain& getMapObject(int i, int j);
    void updateMoneyTeam(int teamT, int teamF);
    void updateTurn(bool turn);

private slots :
    void changeTurn();
    void showPrice();
    void showRules();
    void showCommands();
    void language();

private:
    Ui::MainWindow *ui;
    DialogUnitPrice *priceDialog;
    DialogShowRules *rulesDialog;
    DialogShowCommands *commandsDialog;
    DialogLanguage *languageDialog;
    Map *map;
    QPushButton *changeTurnButton = nullptr;
    QPushButton *showUnitPriceButton = nullptr;
    QPushButton *showRulesButton= nullptr;
    QPushButton *showCommandsButton=nullptr;
    QPushButton *languageButton=nullptr;
    QLabel* labelArnian = nullptr;
    bool m_turn;
    QLabel* labelMoneyT = nullptr;
    QLabel* labelMoneyF = nullptr;
    QLabel* labelNameT= nullptr;
    QLabel* labelNameF= nullptr;
    QLabel* labelTurn= nullptr;
    QLabel* labelT1= nullptr;
    QLabel* labelT2= nullptr;
    QLabel* labelT3= nullptr;
    QLabel* labelT4= nullptr;
    QLabel* labelDeviseT= nullptr;
    QLabel* labelDeviseF=nullptr;

};

#endif // MAINWINDOW_H
