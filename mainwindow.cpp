#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "HeapArrayUtility.h"
#include "HeapLoggerTraverser.h"

#include <QMessageBox>
#include <QLineEdit>
#include <QVBoxLayout>
#include <QScrollArea>
#include <QList>
#include <QGraphicsItem>
#include <QGraphicsPathItem>
#include <QGraphicsLineItem>
#include <QPropertyAnimation>
#include <QParallelAnimationGroup>


#define MAX_HEAP_SELECTION 0
#define MIN_HEAP_SELECTION 1

#define NODE_SIZE 30

#define FIRST_LV_DISTANCE 25

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    this->heapType = MAX_HEAP_SELECTION;
    createNewHeap();
    ui->setupUi(this);
    setupListInputterUI();

    scene = new QGraphicsScene();
    ui->heapGraphicsView->setScene(scene);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::setupListInputterUI()
{
    this->vBox = new QVBoxLayout();
    QWidget* contentWidget = new QWidget();
    QLineEdit* firstLineEdit = new QLineEdit();
    QObject::connect(firstLineEdit, SIGNAL(textEdited(QString)), this, SLOT(elementEditedSlot(QString)));
    vBox->addWidget(firstLineEdit);
    contentWidget->setLayout(vBox);
    ui->listEleScrollArea->setWidget(contentWidget);

    this->lineEditList.push_back(firstLineEdit);
}

void MainWindow::on_heapTypeCombox_currentIndexChanged(int index)
{
    this->heapType = index;
    runCurrentHeap();

}

void MainWindow::elementEditedSlot(QString content) {
    bool convertOK;
    content.toInt(&convertOK, 10);
    if (content[0] == '-' && content.size() == 1)
        return;
    else if (!convertOK) {
        sortList();
        QMessageBox::critical(this, "Error", "You need to enter a number", QMessageBox::Ok);
        return;
    }

    addNewEditLineWhenNeeded();
}

void MainWindow::sortList() {
    std::vector<int> unsortedList;
    for (unsigned int idxEditLine = 0; idxEditLine < this->lineEditList.size(); idxEditLine++) {
        bool convertOK;
        int newNum = this->lineEditList[idxEditLine]->text().toInt(&convertOK);
        if (this->lineEditList[idxEditLine]->text().size() != 0
                & convertOK)
            unsortedList.push_back(newNum);
    }
    sorter->buildHeap(unsortedList);
    std::vector<int> sortedList = sorter->getSortedList();
    QString sortedListStr;
    for (unsigned int idxElement = 0; idxElement < sortedList.size(); idxElement++) {
        sortedListStr += QString::number(sortedList[idxElement]) + ' ';
    }
    ui->resultTxtEdit->setText(sortedListStr);
}

void MainWindow::addNewEditLineWhenNeeded() {
    bool hasEmptySlot = false;
    int totalElement = 0;
    for (int idxLineEdit = 0; idxLineEdit < this->lineEditList.size(); idxLineEdit++) {
        if (this->lineEditList[idxLineEdit]->text().size() == 0)
            hasEmptySlot = true;
        totalElement++;
    }
    ui->totalEleEditLn->setText("Total: " + QString::number(totalElement) + " elements");
    if (!hasEmptySlot) {
        QLineEdit* newLineEdit = new QLineEdit();
        QObject::connect(newLineEdit, SIGNAL(textEdited(QString)), this, SLOT(elementEditedSlot(QString)));
        this->vBox->addWidget(newLineEdit);
        this->lineEditList.push_back(newLineEdit);
    }
}

void MainWindow::createNewHeap() {
    if (this->heapType == MAX_HEAP_SELECTION)
        sorter = new HeapSort(HeapSort::MAX_HEAP);
    else if (this->heapType == MIN_HEAP_SELECTION)
        sorter = new HeapSort(HeapSort::MIN_HEAP);
}

void MainWindow::recreateHeap() {
    delete sorter;
    createNewHeap();
}

void MainWindow::drawHeap(std::vector<int> heapArr) {
    scene->clear();

    if (heapArr.size() == 0)
        return;

    int heapHeight = HeapArrayUtility::getHeapHeight(heapArr.size());

    QBrush brush(Qt::blue);
    QPen pen(Qt::black);
    pen.setWidth(2);

    drawRootNode(heapArr, heapHeight, 0, brush, pen);
}

void MainWindow::runCurrentHeap() {
    recreateHeap();
    sortList();

    loggerTraverser = new HeapLoggerTraverser(sorter->getHeap()->getBuildLogger(),
                                              sorter->getHeap()->getPopLogger());
    if (loggerTraverser->hasNext())
        drawHeap(loggerTraverser->next().getCurrentHeap());

    ui->nextBtn->setEnabled(true);
    ui->prevBtn->setEnabled(true);
    ui->skipBtn->setEnabled(true);

}

void MainWindow::drawRootNode(std::vector<int> heapArr, int curLevel ,int currNodePos, QBrush brush, QPen pen) {

    QGraphicsEllipseItem* bound = new QGraphicsEllipseItem(0, 0, NODE_SIZE, NODE_SIZE);
    bound->setBrush(brush);
    bound->setPen(pen);
    QGraphicsTextItem* content = new QGraphicsTextItem(QString::number(heapArr[currNodePos]));
    content->setPos(2,2);
    scene->addItem(bound);
    scene->addItem(content);

    drawBelowNode(heapArr, curLevel, currNodePos, QPoint(0,0), brush, pen);

}

void MainWindow::drawLeftNode(std::vector<int> heapArr, int curLevel, int currNodePos,
                              QPoint prevNode, QBrush brush, QPen pen) {

    QPoint currNodePoint(prevNode.rx() - calculateEdgeDistance(curLevel), prevNode.ry() + 60);
    QGraphicsEllipseItem* bound = new QGraphicsEllipseItem(currNodePoint.rx(), currNodePoint.ry(),
                                                              NODE_SIZE, NODE_SIZE);
    bound->setBrush(brush);
    bound->setPen(pen);
    QGraphicsTextItem* content = new QGraphicsTextItem(QString::number(heapArr[currNodePos]));
    content->setPos(currNodePoint);
    scene->addItem(bound);
    scene->addItem(content);


    QGraphicsLineItem* lineConnect = new QGraphicsLineItem(prevNode.rx() + 2, prevNode.ry() + 22,
                                                     currNodePoint.rx() + 25, currNodePoint.ry() + 2);
    lineConnect->setPen(pen);
    scene->addItem(lineConnect);

    drawBelowNode(heapArr, curLevel, currNodePos, currNodePoint, brush, pen);
}

void MainWindow::drawRightNode(std::vector<int> heapArr, int curLevel, int currNodePos,
                               QPoint prevNode, QBrush brush, QPen pen) {

    QPoint currNodePoint(prevNode.rx() + calculateEdgeDistance(curLevel), prevNode.ry() + 60);
    QGraphicsEllipseItem* bound = new QGraphicsEllipseItem(currNodePoint.rx(), currNodePoint.ry(),
                                                              NODE_SIZE, NODE_SIZE);
    bound->setBrush(brush);
    bound->setPen(pen);
    QGraphicsTextItem* content = new QGraphicsTextItem(QString::number(heapArr[currNodePos]));
    content->setPos(currNodePoint);
    scene->addItem(bound);
    scene->addItem(content);


    QGraphicsLineItem* lineConnect = new QGraphicsLineItem(prevNode.rx() + 28, prevNode.ry() + 22,
                                                     currNodePoint.rx() + 5, currNodePoint.ry() + 2);
    lineConnect->setPen(pen);
    scene->addItem(lineConnect);

    drawBelowNode(heapArr, curLevel, currNodePos, currNodePoint, brush, pen);
}

void MainWindow::drawBelowNode(std::vector<int> heapArr, int curLevel, int currNodePos,
                               QPoint prevNode, QBrush brush, QPen pen) {
    int leftChildPos = HeapArrayUtility::getLeftChildPos(currNodePos);
    int rightChildPos = HeapArrayUtility::getRightChildPos(currNodePos);

    if (!HeapArrayUtility::isPosOverHeapSize(heapArr.size(), leftChildPos))
        drawLeftNode(heapArr, curLevel - 1, leftChildPos, prevNode, brush, pen);
    if (!HeapArrayUtility::isPosOverHeapSize(heapArr.size(), rightChildPos))
        drawRightNode(heapArr, curLevel - 1, rightChildPos, prevNode, brush, pen);
}

int MainWindow::calculateEdgeDistance(int curLevel) {
    int distance = FIRST_LV_DISTANCE;
    for (int idxCurLv = 2; idxCurLv <= curLevel; idxCurLv++) {
        distance = 2 * distance;
    }

    return distance;
}

void MainWindow::on_clearBtn_clicked()
{
    lineEditList.clear();

    if ( vBox != NULL )
    {
        QLayoutItem* item;
        while ( ( item = vBox->takeAt( 0 ) ) != NULL )
        {
            delete item->widget();
            delete item;
        }
        delete vBox;
    }
    scene->clear();
    ui->resultTxtEdit->setText("");

    setupListInputterUI();

    ui->nextBtn->setEnabled(false);
    ui->prevBtn->setEnabled(false);
    ui->skipBtn->setEnabled(false);
}

void MainWindow::on_closeBtn_clicked()
{
    qApp->exit();
}

void MainWindow::on_startBtn_clicked()
{
    runCurrentHeap();
}

void MainWindow::on_nextBtn_clicked()
{
    if (loggerTraverser->hasNext())
        drawHeap(loggerTraverser->next().getCurrentHeap());
}

void MainWindow::on_prevBtn_clicked()
{
    if (loggerTraverser->hasPrev())
        drawHeap(loggerTraverser->prev().getCurrentHeap());
}

void MainWindow::on_skipBtn_clicked()
{
    if (loggerTraverser->hasEndBuildHeap())
        drawHeap(loggerTraverser->endPop().getCurrentHeap());
    else
        drawHeap(loggerTraverser->endBuild().getCurrentHeap());
}
