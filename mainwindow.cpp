#include "mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
{
    // 1. 設定 CentralWidget（未來影像工作區）
    createCentralWidget();

    // 2. 初始化 QAction（配置 Icon 與 Shortcut）
    createActions();

    // 3. 建立 Menu 與 ToolBar
    createMenus();
    createToolBars();

    setWindowTitle(tr("桌面影像處理器"));
    resize(800, 600);
}

MainWindow::~MainWindow()
{
}

void MainWindow::createCentralWidget()
{
    // 建立中央畫布標籤，作為 CentralWidget 工作區
    imageLabel = new QLabel(tr("【 Central Widget 影像工作區預留 】\n尚未載入影像"), this);
    imageLabel->setAlignment(Qt::AlignCenter);

    // 設定樣式讓 CentralWidget 工作區範圍更明顯
    imageLabel->setStyleSheet("QLabel { background-color : #2b2b2b; color : #aaaaaa; font-size: 16px; border: 2px dashed #555555; }");

    // 掛載為 QMainWindow 的中央工作區
    setCentralWidget(imageLabel);
}

void MainWindow::createActions()
{
    // 取得 Qt 系統內建標準圖示（確保跨平台皆能正常顯示圖示）
    QStyle *style = QApplication::style();

    // 1. Open QAction (Icon + 快捷鍵 Ctrl+O)
    openAction = new QAction(style->standardIcon(QStyle::SP_DialogOpenButton), tr("&Open..."), this);
    openAction->setShortcut(QKeySequence::Open);
    openAction->setStatusTip(tr("開啟影像檔案"));
    connect(openAction, &QAction::triggered, this, &MainWindow::openImage);

    // 2. Save QAction (Icon + 快捷鍵 Ctrl+S)
    saveAction = new QAction(style->standardIcon(QStyle::SP_DialogSaveButton), tr("&Save"), this);
    saveAction->setShortcut(QKeySequence::Save);
    saveAction->setStatusTip(tr("儲存目前影像"));
    connect(saveAction, &QAction::triggered, this, &MainWindow::saveImage);

    // 3. Exit QAction (Icon + 快捷鍵 Ctrl+Q)
    exitAction = new QAction(style->standardIcon(QStyle::SP_DialogCloseButton), tr("E&xit"), this);
    exitAction->setShortcut(QKeySequence::Quit);
    exitAction->setStatusTip(tr("離開程式"));
    connect(exitAction, &QAction::triggered, this, &QWidget::close);

    // 4. Rotate QAction (Icon + 快捷鍵 Ctrl+R)
    rotateAction = new QAction(style->standardIcon(QStyle::SP_BrowserReload), tr("旋轉 (&Rotate)"), this);
    rotateAction->setShortcut(QKeySequence(Qt::CTRL | Qt::Key_R));
    rotateAction->setStatusTip(tr("順時針旋轉影像"));
    connect(rotateAction, &QAction::triggered, this, &MainWindow::editImage);

    // 5. Crop QAction (Icon + 快捷鍵 Ctrl+X)
    cropAction = new QAction(style->standardIcon(QStyle::SP_FileDialogListView), tr("剪裁 (&Crop)"), this);
    cropAction->setShortcut(QKeySequence(Qt::CTRL | Qt::Key_X));
    cropAction->setStatusTip(tr("剪裁影像區域"));
    connect(cropAction, &QAction::triggered, this, &MainWindow::editImage);
}

void MainWindow::createMenus()
{
    // File 選單
    fileMenu = menuBar()->addMenu(tr("&File"));
    fileMenu->addAction(openAction);
    fileMenu->addAction(saveAction);
    fileMenu->addSeparator();
    fileMenu->addAction(exitAction);

    // Image 選單
    imageMenu = menuBar()->addMenu(tr("&Image"));
    imageMenu->addAction(rotateAction);
    imageMenu->addAction(cropAction);

    // Edit 選單
    editMenu = menuBar()->addMenu(tr("&Edit"));
}

void MainWindow::createToolBars()
{
    mainToolBar = addToolBar(tr("Main ToolBar"));

    // 將包含 Icon 與 Shortcut 的 QAction 加入 ToolBar
    mainToolBar->addAction(openAction);
    mainToolBar->addAction(saveAction);
    mainToolBar->addSeparator();
    mainToolBar->addAction(rotateAction);
    mainToolBar->addAction(cropAction);
}

// 實作 Slot 動作
void MainWindow::openImage()
{
    QString fileName = QFileDialog::getOpenFileName(this, tr("開啟影像"), "", tr("Image Files (*.png *.jpg *.bmp)"));
    if (!fileName.isEmpty()) {
        imageLabel->setText(tr("已開啟檔案：\n%1").arg(fileName));
    }
}

void MainWindow::saveImage()
{
    QString fileName = QFileDialog::getSaveFileName(this, tr("儲存影像"), "", tr("Image Files (*.png *.jpg *.bmp)"));
    if (!fileName.isEmpty()) {
        imageLabel->setText(tr("已儲存檔案至：\n%1").arg(fileName));
    }
}

void MainWindow::editImage()
{
    imageLabel->setText(tr("已觸發：影像編輯工具"));
}