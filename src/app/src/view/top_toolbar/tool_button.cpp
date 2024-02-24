#include "tool_button.h"

ToolButtonTop::ToolButtonTop(QWidget* parent, std::string icon)
    : QPushButton{parent}
{
    const int size = 24;

    this->setCheckable(true);

    std::string iconPath = ICONS_PATH + icon;
    QPixmap pixmap(iconPath.c_str());
    QIcon buttonIcon(pixmap);
    this->setIcon(buttonIcon);
    QSize qsize(size, size);
    this->setIconSize(qsize);
    this->setObjectName("side_tool_button");
}

const std::string ToolButtonTop::ICONS_PATH = ":/icons/";
