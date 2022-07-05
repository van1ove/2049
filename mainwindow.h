#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QGridLayout>
#include <QDialog>
#include <QLabel>
#include <QPushButton>
#include <QKeyEvent>

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

protected:
    virtual void keyPressEvent(QKeyEvent * event);

private:
    void changeColor(int x, int y);
    void generate();
    void start();

    void moveUp();
    void moveDown();
    void moveLeft();
    void moveRight();
    void rotate();

    Ui::MainWindow *ui;
    QWidget *centralWidget;
    QGridLayout* grid;
    QLabel*  fields[4][4];
};
#endif // MAINWINDOW_H
