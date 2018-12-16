#include "mainwindow.h"
#include "gameobject.h"
#include "game.h"
#include "ui_mainwindow.h"
#include <QPainter>
#include <iostream>
#include "terrain.h"
#include "introwindow.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{

    ui->setupUi(this);
    map = new Map(this);
    MainWindow::setCentralWidget(map);

    changeTurnButton = new QPushButton("Change Turn", this); // ui->changeTurnButton
          changeTurnButton->setGeometry(620,760, 160, 60);
        QObject::connect(changeTurnButton, SIGNAL(clicked()), this, SLOT(changeTurn()));

    showRulesButton = new QPushButton("Show Rules",this);
        showRulesButton->setGeometry(145,760, 120,50);
        QObject::connect(showRulesButton, SIGNAL(clicked()), this, SLOT(showRules()));

    showUnitPriceButton = new QPushButton("Show Units Prices", this);
        showUnitPriceButton->setGeometry(15,760, 120, 50);
        QObject::connect(showUnitPriceButton, SIGNAL(clicked()), this, SLOT(showPrice()));

    showCommandsButton = new QPushButton("Show commands", this);
        showCommandsButton->setGeometry(15,700, 120, 50);
        QObject::connect(showCommandsButton, SIGNAL(clicked()), this, SLOT(showCommands()));

    languageButton = new QPushButton("Language", this);
        languageButton->setGeometry(145,700, 120, 50);
        QObject::connect(languageButton, SIGNAL(clicked()), this, SLOT(language()));

    endGameButton = new QPushButton("End game !", this);
        endGameButton->setGeometry(15, 600, 120, 50);
        QObject::connect(endGameButton, SIGNAL(clicked()), this, SLOT(showIntro()));

     labelArnian = new QLabel("©(AR)NIANLETRICOZORProduction", this);
         labelArnian->setGeometry(1150,730, 200, 200);

     labelMoneyT = new QLabel("lol", this);
         labelMoneyT->setGeometry(15,340, 200, 50);
         labelMoneyT->setStyleSheet("QLabel { font: 15pt ; color : white; }");

     labelMoneyF = new QLabel("",this);
         labelMoneyF->setGeometry(1150,340, 200, 50);
         labelMoneyF->setStyleSheet("QLabel {  font: 15pt ; color : white; }");

     labelNameT= new QLabel ("Orange Star", this);
        labelNameT->setGeometry(15, 50, 200, 200);
        labelNameT->setStyleSheet("QLabel { font: 20pt ; color : white; }");

     labelNameF= new QLabel ("Blue Moon", this);
        labelNameF->setStyleSheet("QLabel {  font: 20pt ;color : white; }");
        labelNameF->setGeometry(1150, 50, 200, 200);

     labelTurn= new QLabel("",this);
        labelTurn->setGeometry(800 ,685,400,200);
        labelTurn->setStyleSheet("QLabel {font: 15pt ; color : white; }");


      labelT1= new QLabel("------------------", this);
        labelT1->setStyleSheet("QLabel { font: 20pt ; color:white;}");
        labelT1->setGeometry(15, 100, 300, 20);

      labelT2= new QLabel("------------------", this);
          labelT2->setStyleSheet("QLabel { font: 20pt ; color: white;}");
          labelT2->setGeometry(15, 225, 300, 20);

       labelT3= new QLabel("------------------", this);
          labelT3->setStyleSheet("QLabel { font: 20pt ; color:white;}");
          labelT3->setGeometry(1150, 100, 300, 20);

       labelT4= new QLabel("------------------", this);
          labelT4->setStyleSheet("QLabel { font: 20pt ; color:white;}");
          labelT4->setGeometry(1150, 225, 300, 20);

    labelDeviseF= new QLabel("Make America great again", this);
        labelDeviseF->setStyleSheet("QLabel{font: 9pt; color: white;}");
        labelDeviseF->setGeometry(1150, 150, 300,100);

    labelDeviseT= new QLabel("Diviser pour mieux régner", this);
        labelDeviseT->setStyleSheet("QLabel{font: 9pt; color: white;}");
        labelDeviseT->setGeometry(15, 150, 300,100);

    labelTerrainType= new QLabel ("Terrain type : ", this);
        labelTerrainType->setStyleSheet("QLabel { font: 12pt ; color: white}");
        labelTerrainType->setGeometry(280,740, 300, 30);

    labelViesOrange= new QLabel ("Unit life : ", this);
        labelViesOrange->setStyleSheet("QLabel { font: 15pt ; color: white;}");
        labelViesOrange->setGeometry(15, 385, 200, 50);

    labelViesBlue= new QLabel ("Unit life : ", this);
        labelViesBlue->setStyleSheet("QLabel { font: 15pt ; color: white;}");
        labelViesBlue->setGeometry(1150, 385, 300, 50);

    labelPtCap = new QLabel ("Capture points : ", this);
        labelPtCap->setStyleSheet("QLabel { font: 12pt ; color:white;}");
        labelPtCap->setGeometry(280, 780, 300, 30);

    labelPtDef=new QLabel ("Defense points :", this);
        labelPtDef->setStyleSheet("QLabel { font: 12pt ; color:white;}");
        labelPtDef->setGeometry(280, 760, 300, 30);

    labelAttackableO = new QLabel ("Attackable ?",this);
        labelAttackableO->setStyleSheet("QLabel { font: 12pt ; color:white;}");
        labelAttackableO->setGeometry(15,430,200,50);

    labelAttackableOrange = new QLabel ("",this);
        labelAttackableOrange->setStyleSheet("QLabel { font: 12pt ; color:white;}");
        labelAttackableOrange->setGeometry(15,470,200,50);

    labelAttackableB = new QLabel ("Attackable ?",this);
        labelAttackableB->setStyleSheet("QLabel { font: 12pt ; color:white;}");
        labelAttackableB->setGeometry(1150 ,430,300,50);

    labelAttackableBlue = new QLabel ("",this);
        labelAttackableBlue->setStyleSheet("QLabel { font: 12pt ; color:white}");
        labelAttackableBlue->setGeometry(1150 ,470,300,50);

        priceDialog = new  DialogUnitPrice(this);
        rulesDialog = new DialogShowRules(this);
        commandsDialog = new DialogShowCommands(this);
        languageDialog = new DialogLanguage(this);
}


MainWindow::~MainWindow()
{
    delete ui;

    delete map;

    delete changeTurnButton;
    delete showRulesButton;
    delete showUnitPriceButton;
    delete showCommandsButton;
    delete languageButton;
    delete endGameButton;

    delete labelArnian;
    delete labelMoneyT;
    delete labelMoneyF;
    delete labelNameF;
    delete labelNameT;
    delete labelTurn;
    delete labelT1;
    delete labelT2;
    delete labelT3;
    delete labelT4;
    delete labelDeviseF;
    delete labelDeviseT;
    delete labelPtCap;
    delete labelPtDef;
    delete labelViesOrange;
    delete labelViesBlue;
    delete labelTerrainType;
    delete labelAttackableBlue;
    delete labelAttackableOrange;
    delete labelAttackableB;
    delete labelAttackableO;

    delete priceDialog;
    delete rulesDialog;
    delete commandsDialog;
    delete languageDialog;

}

void MainWindow::createMapObjects() {
    map->setmapobject();
}

void MainWindow::redraw()
{
    map->redraw();
}

Terrain& MainWindow::getMapObject(int i, int j)
{
    return map->getmapObject(i,j);
}

void MainWindow::changeTurn()
{
    Game& game = Game::Instance();
    game.turnChange();
}

void MainWindow::showPrice(){
    priceDialog->show();
}

void MainWindow::showRules(){
    rulesDialog->show();
}

void MainWindow::showCommands(){
    commandsDialog->show();
}

void MainWindow::language(){
    languageDialog->show();
}

void MainWindow::updateMoneyTeam(int moneyTeamT, int moneyTeamF) {
    std::string moneyT = std::to_string(moneyTeamT);
    std::string moneyF = std::to_string(moneyTeamF);
    labelMoneyT->setText("MONEY : " + QString::fromStdString(moneyT) );
    labelMoneyF->setText( "MONEY : " + QString::fromStdString(moneyF));
}

void MainWindow::updateTurn(bool activeTurn){
    if (activeTurn){
        labelTurn->setText("Orange Star, à vous de jouer!");
    }
    else {
        labelTurn->setText("Blue Moon, à vous de jouer!");
    }
}

void MainWindow::setUp(int type){
    Game& game = Game::Instance();
    game.start(*this);
    game.setgameType(type);
}

void MainWindow::updateInfoPos(string terrainType, int PtDefense, int PtCapture, bool unit, bool team, int viesUnit, bool attackable, int degats, bool update){

    std::string PtDef = std::to_string(PtDefense);
    std::string PtCap = std::to_string(PtCapture);
    std::string viesU = std::to_string(viesUnit);
    std::string deg = std::to_string(degats);

    labelTerrainType->setText("Terrain type : " + QString::fromStdString(terrainType));
    labelPtDef->setText("Defense points : " + QString::fromStdString(PtDef));

    if (PtCapture == 0){
        labelPtCap->setText("Capture points : ");
    }
    if (PtCapture != 0){
        labelPtCap->setText("Capture points : " + QString::fromStdString(PtCap));
    }
    if (unit){
        if (team) {
            labelViesOrange->setText("Unit life : " + QString::fromStdString(viesU));
            labelViesBlue->setText("Unit life : ");
            labelAttackableBlue->setText("");
            if (attackable){
                labelAttackableOrange->setText( "Yes! Dammage : " + QString::fromStdString(deg));
            }
            if (!attackable){
                labelAttackableOrange->setText("No ! ");
            }
        }
        if (!team){
            labelViesOrange->setText("Unit life : ");
            labelViesBlue->setText("Unit life : " + QString::fromStdString(viesU));
            labelAttackableOrange->setText("");
            if (attackable){
                labelAttackableBlue->setText("Yes! Dammage : " + QString::fromStdString(deg));
            }
            if (!attackable){
                labelAttackableBlue->setText("No! ");
            }
        }
    }
    if (!unit){
        labelViesBlue->setText("Unit life : ");
        labelViesOrange->setText("Unit life : ");
        labelAttackableOrange->setText("");
        labelAttackableBlue->setText("");
    }

    if (update){
        labelTerrainType->setText("Terrain type :");
        labelPtDef->setText("Defense points :");
        labelPtCap->setText("Caputre points :");
        labelViesBlue->setText("Unit life :");
        labelViesOrange->setText("Unit Life :");
        labelViesBlue->setText("Unit life :");
        labelAttackableBlue->setText("");
        labelAttackableOrange->setText("");
    }
}

void MainWindow::showIntro(){
    Game& game = Game::Instance();
    game.endGame();
}

Map& MainWindow::getMap(){
    return *map;
}
