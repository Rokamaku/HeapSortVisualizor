#ifndef MAINWINDOW_H
#define MAINWINDOW_H
#include "HeapSort.h"
#include "HeapLoggerTraverser.h"

#include <QVBoxLayout>
#include <QMainWindow>
#include <QLineEdit>
#include <QGraphicsScene>
#include <QPropertyAnimation>
#include <QParallelAnimationGroup>

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();


private slots:

    void on_heapTypeCombox_currentIndexChanged(int index);

    void elementEditedSlot(QString content);

    void on_clearBtn_clicked();

    void on_closeBtn_clicked();

    void on_startBtn_clicked();

    void on_nextBtn_clicked();

    void on_prevBtn_clicked();

    void on_skipBtn_clicked();

private:
    int heapType;
    HeapSort* sorter;
    Ui::MainWindow *ui;
    QList<QLineEdit*> lineEditList;
    QVBoxLayout* vBox;
    QGraphicsScene* scene;

    HeapLoggerTraverser* loggerTraverser = NULL;



    void createNewHeap();
    void recreateHeap();
    void setupListInputterUI();
    void addNewEditLineWhenNeeded();
    void sortList();
    void runCurrentHeap();
    void drawHeap(std::vector<int> heapArr);
    void drawRootNode(std::vector<int> heapArr, int curLevel, int currNodePos, QBrush brush, QPen pen);
    void drawLeftNode(std::vector<int> heapArr, int curLevel, int currNodePos, QPoint prevNode, QBrush brush, QPen pen);
    void drawRightNode(std::vector<int> heapArr, int curLevel, int currNodePos, QPoint prevNode, QBrush brush, QPen pen);
    void drawBelowNode(std::vector<int> heapArr, int curLevel, int currNodePos, QPoint prevNode, QBrush brush, QPen pen);
    int calculateEdgeDistance(int curLevel);

};

#endif // MAINWINDOW_H
