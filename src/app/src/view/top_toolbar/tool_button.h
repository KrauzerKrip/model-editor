#pragma once

#include <string>

#include <QKeySequence>
#include <QPushButton>
#include <QWidget>

class ToolButtonTop : public QPushButton
{
    //Q_OBJECT
public:
    explicit ToolButtonTop(QWidget* parent = nullptr, std::string icon = "default");

private:
    static const std::string ICONS_PATH;
};
