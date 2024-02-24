#pragma once

#include <QMainWindow>

#include "model/editor.h"

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

    void showEvent(QShowEvent* event);

private:
    Ui::MainWindow *ui;
    Editor* m_pEditor = nullptr;
    bool m_isViewerActivated = false;

public slots:
    void activateViewer();
};
