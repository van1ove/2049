#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QGridLayout>
#include <QDialog>
#include <QLabel>
#include <QPushButton>
#include <QKeyEvent>
#include <QMenuBar>
#include <QAction>
#include <QFileDialog>
#include <QDir>
#include <QShortcut>
#include <fstream>

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
    void createMenu();
    void createActions();

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
    QMenu *fileMenu;
    QAction *saveAction;
    QAction *loadAction;
    int dim = 4;
private slots:
    void showSaveMenu();
    void showLoadMenu();
};
#endif // MAINWINDOW_H
