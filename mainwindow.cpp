#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QMessageBox>
#include <QLineEdit>
#include <QVBoxLayout>
#include <QScrollArea>
#include <QList>
#include <QGraphicsItem>
#include <QGraphicsPathItem>
#include <QGraphicsLineItem>
#include "HeapArrayUtility.h"

#define MAX_HEAP_SELECTION 0
#define MIN_HEAP_SELECTION 1

#define NODE_SIZE 30

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
    recreateHeap();
    sortList();
    drawHeap();
}

void MainWindow::elementEditedSlot(QString content) {
    recreateHeap();

    bool convertOK;
    content.toInt(&convertOK, 10);
    if (convertOK) {
        sortList();
    }
    else if (content[0] == '-' && content.size() == 1) {
        return;
    }
    else {
        QMessageBox::critical(this, "Error", "You need to enter a number", QMessageBox::Ok);
        return;
    }

    addNewEditLineWhenNeeded();
}

void MainWindow::sortList() {
    std::vector<int> unsortedList;
    for (unsigned int idxEditLine = 0; idxEditLine < this->lineEditList.size(); idxEditLine++) {
        if (this->lineEditList[idxEditLine]->text().size() != 0)
            unsortedList.push_back(lineEditList[idxEditLine]->text().toInt());
    }
    sorter->buildHeap(unsortedList);
    scene->items().clear();
    scene->clear();
    drawHeap();
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

void MainWindow::drawHeap() {
    std::vector<int> heapArr = sorter->getHeap()->getHeapArr();

    int heapHeight = HeapArrayUtility::getHeapHeight(heapArr.size());

    QBrush brush(Qt::blue);
    QPen pen(Qt::black);
    pen.setWidth(2);

    drawRootNode(heapArr, heapHeight, 0, brush, pen);
}

void MainWindow::drawRootNode(std::vector<int> heapArr, int curLevel ,int currNodePos, QBrush brush, QPen pen) {

    QGraphicsEllipseItem* currNode = new QGraphicsEllipseItem(0, 0, NODE_SIZE, NODE_SIZE);
    currNode->setBrush(brush);
    currNode->setPen(pen);
    QGraphicsTextItem* text1 = new QGraphicsTextItem(QString::number(heapArr[currNodePos]));
    text1->setPos(2,2);
    scene->addItem(currNode);
    scene->addItem(text1);

    drawBelowNode(heapArr, curLevel, currNodePos, QPoint(0,0), brush, pen);

}

void MainWindow::drawLeftNode(std::vector<int> heapArr, int curLevel, int currNodePos,
                              QPoint prevNode, QBrush brush, QPen pen) {

    QPoint currNodePoint(prevNode.rx() - calculateEdgeDistance(curLevel), prevNode.ry() + 60);
    QGraphicsEllipseItem* ellipse2 = new QGraphicsEllipseItem(currNodePoint.rx(), currNodePoint.ry(),
                                                              NODE_SIZE, NODE_SIZE);
    ellipse2->setBrush(brush);
    ellipse2->setPen(pen);
    QGraphicsTextItem* text2 = new QGraphicsTextItem(QString::number(heapArr[currNodePos]));
    text2->setPos(currNodePoint);
    scene->addItem(ellipse2);
    scene->addItem(text2);

//    QGraphicsLineItem* line1 = new QGraphicsLineItem(2,22,-95,62);
    QGraphicsLineItem* line1 = new QGraphicsLineItem(prevNode.rx() + 2, prevNode.ry() + 22,
                                                     currNodePoint.rx() + 25, currNodePoint.ry() + 2);
    line1->setPen(pen);
    scene->addItem(line1);

    drawBelowNode(heapArr, curLevel, currNodePos, currNodePoint, brush, pen);
}

void MainWindow::drawRightNode(std::vector<int> heapArr, int curLevel, int currNodePos,
                               QPoint prevNode, QBrush brush, QPen pen) {

    QPoint currNodePoint(prevNode.rx() + calculateEdgeDistance(curLevel), prevNode.ry() + 60);
    QGraphicsEllipseItem* ellipse3 = new QGraphicsEllipseItem(currNodePoint.rx(), currNodePoint.ry(),
                                                              NODE_SIZE, NODE_SIZE);
    ellipse3->setBrush(brush);
    ellipse3->setPen(pen);
    QGraphicsTextItem* text3 = new QGraphicsTextItem(QString::number(heapArr[currNodePos]));
    text3->setPos(currNodePoint);
    scene->addItem(ellipse3);
    scene->addItem(text3);

//    QGraphicsLineItem* line2 = new QGraphicsLineItem(28,22,125,62);
    QGraphicsLineItem* line2 = new QGraphicsLineItem(prevNode.rx() + 28, prevNode.ry() + 22,
                                                     currNodePoint.rx() + 5, currNodePoint.ry() + 2);
    line2->setPen(pen);
    scene->addItem(line2);

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
    int distance = 0;
    for (int idxLevel = 1; idxLevel <= curLevel; idxLevel++) {
        distance += idxLevel * 10 + 30;
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
}

void MainWindow::on_closeBtn_clicked()
{
    qApp->exit();
}
