#include "mainwindow.h"
#include "./ui_mainwindow.h"
#include <QDockWidget>
#include <QFile>
#include <QLabel>
#include <QPushButton>
#include <QStyleFactory>
#include <QTimer>
#include <QToolBar>

#include "model/editor.h"
#include "view/inspector/component/components/test.h"
#include "view/inspector/component/components/transform.h"
#include "view/inspector/inspector.h"
#include "view/main_layout.h"
#include "view/menu_bar.h"
#include "view/side_toolbar/side_toolbar.h"
#include "view/top_toolbar/top_toolbar.h"
#include "model/core/graphics/viewer.h"

#include <QOpenGLWindow>

MainWindow::MainWindow(QWidget* parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    //ui->setupUi(this);
    resize(1920, 1080);
    setWindowState(Qt::WindowMaximized);
    setWindowTitle("Local` Editor");
    MenuBar* pMenuBar = new MenuBar();
    setMenuBar(pMenuBar);
    setStyle(QStyleFactory::create("fusion")); // try windowsvista and fusion

    Viewer* pViewerWindow = new Viewer();
    QWidget* pViewerWidget = new QWidget();
    auto* pViewerWidget2 = pViewerWidget->createWindowContainer(pViewerWindow);
    pViewerWidget2->setFixedSize(QSize(1280, 720));
    pViewerWidget2->setSizePolicy(QSizePolicy(QSizePolicy::Fixed, QSizePolicy::Fixed));
    setCentralWidget(pViewerWidget2);
    pViewerWidget2->show();

//    Viewer* pViewerWindow = new Viewer();
//    pViewerWindow->setFixedSize(QSize(1280, 720));
//    QSizePolicy(QSizePolicy::Fixed, QSizePolicy::Fixed);
//    setCentralWidget(pViewerWindow);
//    pViewerWindow->show();

    Editor* pEditor = new Editor(pViewerWindow);
    m_pEditor = pEditor;

    SideToolBar* pSideToolBar = new SideToolBar(&pEditor->getModeHandler());
    addToolBar(Qt::ToolBarArea::LeftToolBarArea, pSideToolBar);

    TopToolbar* pTopToolBar = new TopToolbar();
    addToolBar(Qt::ToolBarArea::TopToolBarArea, pTopToolBar);

    QFile styleF;

    styleF.setFileName(":/qss/dark.css");
    styleF.open(QFile::ReadOnly);
    QString qssStr = styleF.readAll();

    qApp->setStyleSheet(qssStr);

    this->setStyleSheet("QMainWindow::separator {background: rgb(32, 32, 32);}");

    QVBoxLayout* testButtons = new QVBoxLayout();

    QPushButton* add = new QPushButton("Add");
    QPushButton* rename = new QPushButton("Rename");
    QPushButton* remove = new QPushButton("Remove");
    QPushButton* removeall = new QPushButton("Remove All");

    testButtons->setSpacing(3);
    testButtons->addStretch(1);
    testButtons->addWidget(add);
    testButtons->addWidget(rename);
    testButtons->addWidget(remove);
    testButtons->addWidget(removeall);
    testButtons->addStretch(1);

    //QWidget* pWidget = new QWidget(this);
    //pWidget->setLayout(testButtons);

    //    QDockWidget* dockWidget = new QDockWidget(tr("Dock Widget"), this);
    //    dockWidget->setStyleSheet("QDockWidget {background-color: rgb(42, 42, 42); border: 1px solid "
    //                              "rgb(32, 32, 32);} QDockWidget > "
    //                              "QWidget {background-color: rgb(42, 42, 42);}"
    //                              "QDockWidget::title {text-align: left;"
    //                              "background: rgb(32, 32, 32);}");
    //    dockWidget->setAllowedAreas(Qt::LeftDockWidgetArea | Qt::RightDockWidgetArea
    //                                | Qt::BottomDockWidgetArea);
    // dockWidget->setWidget(pWidget);

    //addDockWidget(Qt::LeftDockWidgetArea, dockWidget);

    Inspector* pInspector = new Inspector(this);
    pInspector->addComponent(new view::Transform(pInspector));
    pInspector->update();
    addDockWidget(Qt::RightDockWidgetArea, pInspector);

    QDockWidget* downWidget = new QDockWidget(tr("Dock Widget"), this);
    downWidget->setStyleSheet("QDockWidget {background-color: rgb(42, 42, 42); "
                              "rgb(32, 32, 32);} QDockWidget > "
                              "QWidget {background-color: rgb(42, 42, 42);;}"
                              "QDockWidget::title {text-align: left;"
                              "background: rgb(32, 32, 32);"
                              "foreground: red;"
                              "}");
    downWidget->setAllowedAreas(Qt::BottomDockWidgetArea);
    QWidget* pWidgetDown = new QWidget(this);
    downWidget->setWidget(pWidgetDown);
    addDockWidget(Qt::BottomDockWidgetArea, downWidget);

    //    QWidget* center = new QWidget(this);
    //    center->setStyleSheet("QWidget {"
    //                          "background-color:black;"
    //                          "}");

    QStatusBar* sb = statusBar();
    sb->setStyleSheet("QStatusBar {background-color: rgb(32, 32, 32); border: none;}");

    QLabel* label = new QLabel;
    label->setStyleSheet("QLabel {color : rgb(232, 232, 232); background-color: rgb(32, 32, 32); "
                         "font-size: 8pt; border: none;}");
    label->setText("Start");
    QTimer* timer = new QTimer(sb);
    timer->setInterval(4000);
    connect(timer, &QTimer::timeout, label, &QObject::deleteLater);
    sb->addWidget(label);
    timer->start();
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::showEvent(QShowEvent* event) {
    QWidget::showEvent(event);
    if (!m_isViewerActivated) {
        QTimer::singleShot(0, this, SLOT(activateViewer()));
    }
    m_isViewerActivated = true;
}

void MainWindow::activateViewer() {
    m_pEditor->activateViewer();
}
