#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    centralWidget = new QWidget(this);
    this->setCentralWidget(centralWidget);
    grid = new QGridLayout(centralWidget);

    for(int i = 0; i < 4; i++){
        for (int j = 0; j < 4; j++){
            fields[i][j] = new QLabel("", this);
            grid->addWidget(fields[i][j], i + 1, j);
            fields[i][j]->setAlignment(Qt::AlignCenter);
            changeColor(i , j);
        }
    }
    fields[1][0]->setFocus();
    setWindowTitle("2048");
    setFixedSize(400, 400);
    generate();
    createActions();
    createMenu();
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::start()
{
    for (int i = 0; i < 4; i++){
        for (int j = 0; j < 4; j++) {
            fields[i][j]->setText("");
            changeColor(i, j);
        }
    }
    generate();
}

void MainWindow::changeColor(int i, int j)
{
    switch (fields[i][j]->text().toInt()){
    case 2:
        fields[i][j]->setStyleSheet("QLabel { background-color: #eee4da; color: black; font:20pt; font-weight:400; border-radius: 5px;}");
        break;

    case 4:
        fields[i][j]->setStyleSheet("QLabel { background-color: #eddfc4; color: black; font:20pt; font-weight:400;border-radius: 5px;}");
        break;

    case 8:
        fields[i][j]->setStyleSheet("QLabel { background-color: #f4b17a; color: white; font:20pt; font-weight:400;border-radius: 5px;}");
        break;

    case 16:
        fields[i][j]->setStyleSheet("QLabel { background-color: #f79663; color: white; font:20pt; font-weight:400;border-radius: 5px;}");
        break;

    case 32:
        fields[i][j]->setStyleSheet("QLabel { background-color: #f67d62; color: white; font:20pt; font-weight:400;border-radius: 5px;}");
        break;

    case 64:
        fields[i][j]->setStyleSheet("QLabel { background-color: #f65e39; color: white; font:20pt; font-weight:400; border-radius: 5px;}");
        break;

    case 128:
        fields[i][j]->setStyleSheet("QLabel { background-color: #edce73; color: white; font:20pt; font-weight:400;border-radius: 5px;}");
        break;

    case 256:
        fields[i][j]->setStyleSheet("QLabel { background-color: #e9cf58; color: white; font:20pt; font-weight:400;border-radius: 5px;}");
        break;

    case 512:
        fields[i][j]->setStyleSheet("QLabel { background-color: #edc651; color: white; font:20pt; font-weight:400;border-radius: 5px;}");
        break;

    case 1024:
        fields[i][j]->setStyleSheet("QLabel { background-color: #eec744; color: white; font:20pt; font-weight:400;border-radius: 5px;}");
        break;

    case 2048:
        fields[i][j]->setStyleSheet("QLabel { background-color: #edca64; color: white; font:20pt; font-weight:400;border-radius: 5px;}");
        break;

    default:
        fields[i][j]->setStyleSheet("QLabel { background-color: #cdc1b5; color: black; font:20pt; font-weight:400; border-radius: 5px;}");
        break;
    }
}

void MainWindow::createMenu(){
    fileMenu = menuBar()->addMenu(tr("&Game"));
    fileMenu->addAction(saveAction);
    fileMenu->addAction(loadAction);
}
void MainWindow::createActions(){
    saveAction = new QAction(tr("&Save"));
    connect(saveAction, &QAction::triggered, this, &MainWindow::showSaveMenu);
    loadAction = new QAction(tr("&Load"));
    connect(loadAction, &QAction::triggered, this, &MainWindow::showLoadMenu);
}

void MainWindow::showSaveMenu(){
    QString filename = QFileDialog::getSaveFileName(this, tr("Save Document"), QDir::currentPath(), tr("Text file (*.TXT)"));
    std::string ActFileName = filename.toStdString();
    std::ofstream out;
    out.open(ActFileName);
    for(int i = 0; i < 4; i++){
        for(int j = 0; j < 4; j++){
            if((fields[i][j]->text()).toStdString() == ""){
                out << "NULL ";
            }else{
                out << (fields[i][j]->text()).toStdString() << " ";
            }
        }
    }
    out.close();
}

void MainWindow::showLoadMenu(){
    QString filename = QFileDialog::getOpenFileName(this, tr("Select load file"), "D:/", tr("TXT files (*.txt)"));
    std::string ActFileName = filename.toStdString();
    std::string tmp_string;
    std::ifstream in;
    in.open(ActFileName);
    for(int i = 0; i < 4; i++){
        for(int j = 0; j < 4; j++){
            in >> tmp_string;
            if(tmp_string != "NULL"){
                fields[i][j]->setText(QString::fromStdString(tmp_string));
                changeColor(i, j);
            }else{
                fields[i][j]->setText(QString::fromStdString(""));
                changeColor(i, j);
            }
        }
    }
    in.close();

}

void MainWindow::generate()
{
    bool full = true;
    for (int i = 0; i < 4; i++){
        for (int j = 0; j < 4; j++){
            if (fields[i][j]->text() == ""){
                full = false;
            }
        }
    }

    if (full){
        QDialog* gameOver = new QDialog();
        gameOver->setMinimumWidth(250);
        gameOver->show();
    }
    else {
        int x = 0, y = 0;
        do {
            x = rand() % 4;
            y = rand() % 4;
        } while (fields[x][y]->text() != "");
        fields[x][y]->setText("2");
        changeColor(x, y);
    }
}

void MainWindow::keyPressEvent(QKeyEvent * event)
{
    QString tempArr[4][4];
    for (int i = 0; i < 4; i++){
        for (int j = 0; j < 4; j++){
            tempArr[i][j] = fields[i][j]->text();
        }
    }

    switch (event->key()){
        case Qt::Key_Up:
            moveUp();
            break;

        case Qt::Key_Down:
            moveDown();
            break;

        case Qt::Key_Left:
            moveLeft();
            break;

        case Qt::Key_Right:
            moveRight();
            break;

        default:
            QMainWindow::keyPressEvent(event);
    }

    bool freeSpace = false;
    for (int i = 0; i < 4; i++){
        for (int j = 0; j < 4; j++){
            if (tempArr[i][j] != fields[i][j]->text()){
                freeSpace = true;
            }
        }
    }
    if(freeSpace){
        generate();
    }
}

void MainWindow::moveUp()
{
    for(int i = 0; i < 4; ++i){
        for(int j = 0; j < 3; ++j){
            if(fields[j][i]->text() == ""){
                int counter = j;
                while(fields[j][i]->text() == "" && counter < 4){
                    for(int k = j; k < 3; k++){
                        fields[k][i]->setText(fields[k + 1][i]->text());
                    }
                    fields[3][i]->setText("");
                    counter++;
                }
            }
        }
    }

    for(int i = 0; i < 4; ++i){
        for(int j = 0; j < 3; ++j){
            if(fields[j][i]->text() == fields[j + 1][i]->text() && fields[j][i]->text() != ""){
                int up = fields[j][i]->text().toInt();
                int down = fields[j + 1][i]->text().toInt();
                fields[j][i]->setText(QString::number(up + down));
                for(int k = j + 1; k < 3; ++k){
                    fields[k][i]->setText(fields[k + 1][i]->text());
                }
                fields[3][i]->setText("");
            }
        }
    }
}



void MainWindow::moveDown()
{
    for(int i = 0; i < 4; ++i){
        for(int j = 3; j > 0; j--){
            if(fields[j][i]->text() == ""){
                int counter = 3 - j;
                while(fields[j][i]->text() == "" && counter < 4){
                    for(int k = j; k > 0; k--){
                        fields[k][i]->setText(fields[k - 1][i]->text());
                    }
                    fields[0][i]->setText("");
                    counter++;
                }
            }
        }
    }

    for(int i = 0; i < 4; ++i){
        for(int j = 3; j > 0; j--){
            if(fields[j][i]->text() == fields[j - 1][i]->text() && fields[j][i]->text() != ""){
                int up = fields[j][i]->text().toInt();
                int down = fields[j - 1][i]->text().toInt();
                fields[j][i]->setText(QString::number(up + down));
                for(int k = j - 1; k > 0; --k){
                    fields[k][i]->setText(fields[k - 1][i]->text());
                }
                fields[0][i]->setText("");
            }
        }
    }
}

void MainWindow::moveLeft()
{
    for(int i = 0; i < 4; ++i){
        for(int j = 0; j < 3; ++j){
            if(fields[i][j]->text() == ""){
                int counter = j;
                while(fields[i][j]->text() == "" && counter < 4){
                    for(int k = j; k < 3; k++){
                        fields[i][k]->setText(fields[i][k + 1]->text());
                    }
                    fields[i][3]->setText("");
                    counter++;
                }
            }
        }
    }

    for(int i = 0; i < 4; ++i){
        for(int j = 0; j < 3; ++j){
            if(fields[i][j]->text() == fields[i][j + 1]->text() && fields[i][j]->text() != ""){
                int up = fields[i][j]->text().toInt();
                int down = fields[i][j + 1]->text().toInt();
                fields[i][j]->setText(QString::number(up + down));
                for(int k = j + 1; k < 3; ++k){
                    fields[i][k]->setText(fields[i][k + 1]->text());
                }
                fields[i][3]->setText("");
            }
        }
    }
}

void MainWindow::moveRight()
{
    for(int i = 0; i < 4; ++i){
        for(int j = 3; j > 0; j--){
            if(fields[i][j]->text() == ""){
                int counter = 3 - j;
                while(fields[i][j]->text() == "" && counter < 4){
                    for(int k = j; k > 0; k--){
                        fields[i][k]->setText(fields[i][k - 1]->text());
                    }
                    fields[i][0]->setText("");
                    counter++;
                }
            }
        }
    }

    for(int i = 0; i < 4; ++i){
        for(int j = 3; j > 0; j--){
            if(fields[i][j]->text() == fields[i][j - 1]->text() && fields[i][j]->text() != ""){
                int up = fields[i][j]->text().toInt();
                int down = fields[i][j - 1]->text().toInt();
                fields[i][j]->setText(QString::number(up + down));
                for(int k = j - 1; k > 0; --k){
                    fields[i][k]->setText(fields[i][k - 1]->text());
                }
                fields[i][0]->setText("");
            }
        }
    }
}

void MainWindow::rotate()
{

}
