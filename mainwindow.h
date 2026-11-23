#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QMenu>
#include <QMenuBar>
#include <QToolBar>
#include <QAction>
#include <QLabel>
#include <QIcon>
#include <QKeySequence>
#include <QStyle>
#include <QApplication>
#include <QFileDialog>
#include <QMessageBox>

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:
    void openImage();
    void saveImage();
    void editImage();

private:
    void createCentralWidget();
    void createActions();
    void createMenus();
    void createToolBars();

    // 中央工作區 (CentralWidget) 載體
    QLabel *imageLabel;

    // 選單與工具列
    QMenu *fileMenu;
    QMenu *imageMenu;
    QMenu *editMenu;
    QToolBar *mainToolBar;

    // QAction（包含 Icon 與 Shortcut）
    QAction *openAction;
    QAction *saveAction;
    QAction *exitAction;
    QAction *rotateAction;
    QAction *cropAction;
};

#endif // MAINWINDOW_H