#pragma once

#include <string>

#include <QKeySequence>
#include <QPushButton>
#include <QWidget>

class ToolButton : public QPushButton
{
    Q_OBJECT
public:
    explicit ToolButton(QWidget* parent = nullptr, std::string icon = "default");

signals:

private:
    static const std::string ICONS_PATH;
};
