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
         labelMoneyT->setStyleSheet("QLabel { font: 15pt ; color : orange; }");

     labelMoneyF = new QLabel("",this);
         labelMoneyF->setGeometry(1150,340, 200, 50);
         labelMoneyF->setStyleSheet("QLabel {  font: 15pt ; color : blue; }");

     labelNameT= new QLabel ("", this);
        labelNameT->setText("Orange Star");
        labelNameT->setGeometry(15, 50, 200, 200);
        labelNameT->setStyleSheet("QLabel { font: 20pt ; color : orange; }");

     labelNameF= new QLabel ("", this);
        labelNameF->setText("BlueMoon");
        labelNameF->setStyleSheet("QLabel {  font: 20pt ;color : blue; }");
        labelNameF->setGeometry(1150, 50, 200, 200);

     labelTurn= new QLabel("",this);
        labelTurn->setGeometry(800 ,685,400,200);

      labelT1= new QLabel("", this);
        labelT1->setText("---------------------------");
        labelT1->setStyleSheet("QLabel { font: 20pt ; color:orange}");
        labelT1->setGeometry(15, 100, 300, 20);

      labelT2= new QLabel("", this);
          labelT2->setText("---------------------------");
          labelT2->setStyleSheet("QLabel { font: 20pt ; color:orange}");
          labelT2->setGeometry(15, 225, 300, 20);

       labelT3= new QLabel("", this);
          labelT3->setText("---------------------------");
          labelT3->setStyleSheet("QLabel { font: 20pt ; color:blue}");
          labelT3->setGeometry(1150, 100, 300, 20);

       labelT4= new QLabel("", this);
          labelT4->setText("---------------------------");
          labelT4->setStyleSheet("QLabel { font: 20pt ; color:blue}");
          labelT4->setGeometry(1150, 225, 300, 20);

    labelDeviseF= new QLabel("", this);
        labelDeviseF->setText("Make America great again");
        labelDeviseF->setStyleSheet("QLabel{font: 12pt; color: blue}");
        labelDeviseF->setGeometry(1150, 150, 300,100);

    labelDeviseT= new QLabel("", this);
        labelDeviseT->setText("Diviser pour mieux reigner");
        labelDeviseT->setStyleSheet("QLabel{font: 12pt; color: orange}");
        labelDeviseT->setGeometry(15, 150, 300,100);
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
    priceDialog = new  DialogUnitPrice(this);
    priceDialog->show();
}

void MainWindow::showRules(){
    rulesDialog = new DialogShowRules(this);
    rulesDialog->show();

}

void MainWindow::showCommands(){
    commandsDialog = new DialogShowCommands(this);
    commandsDialog->show();

}

void MainWindow::language(){
    languageDialog = new DialogLanguage(this);
    languageDialog->show();

}

void MainWindow::updateMoneyTeam(int moneyTeamT, int moneyTeamF) {
    std::string moneyT = std::to_string(moneyTeamT);
    std::string moneyF = std::to_string(moneyTeamF);
    labelMoneyT->setText("MONEY : " + QString::fromStdString(moneyT) );
    labelMoneyF->setText( "MONEY : " + QString::fromStdString(moneyF));
}

void MainWindow::updateTurn(bool activeTurn){
    m_turn = activeTurn; // true si tour orange et false si tour bleu
    if (m_turn){
        labelTurn->setText("Orange Star, à vous de jouer!");
        labelTurn->setStyleSheet("QLabel {font: 15pt ; color : orange; }");
    }
    else {
        labelTurn->setText("Blue Moon, à vous de jouer!");
        labelTurn->setStyleSheet(" QLabel {font: 15pt ;color : blue; }");
    }
}

void MainWindow::setUp(int type){
    Game& game = Game::Instance();
    game.start(*this);
    game.setgameType(type);
}

void MainWindow::updateInfoPos(string terrainType, int PtDefense, int PtCapture, bool team, int viesUnit){
    std::string PtDef = std::to_string(PtDefense);
    std::string PtCap = std::to_string(PtCapture);
    std::string viesU = std::to_string(viesUnit);
    //labelTerrainType->setText(" Terrain type :" + QString::fromStdString(terrainType));
    //labelPtDef->setText(" Defense points :" + QString::fromStdString(PtDef));
    if (PtCapture = 0){
        //labelPtCap->setText(""); // N'affiche rien
    }
    if (PtCapture != 0){
        //labelPtCap->setText("Capture points :" + QString::fromStdString(PtCap));
    }
    if (team) {
        //labelViesOrange->setText("Unit lives : " + QString::fromStdString(viesU));
        //labelViesBlue->setText("");
    }
    if (!team){
        //labelViesOrange->setText("");
        //labelViesBlue->setText("Unit lives : " + QString::fromStdString(viesU));
    }
}

void MainWindow::showIntro(){
    IntroWindow intro;
    intro.setWindow(this);
    //this->close();
    intro.show();
}
