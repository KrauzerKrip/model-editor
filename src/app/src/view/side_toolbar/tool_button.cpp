#include "tool_button.h"

ToolButton::ToolButton(QWidget* parent, std::string icon)
    : QPushButton{parent}
{
    const int size = 48;

    this->setCheckable(true);

    std::string iconPath = ICONS_PATH + icon;
    QPixmap pixmap(iconPath.c_str());
    QIcon buttonIcon(pixmap);
    this->setIcon(buttonIcon);
    QSize qsize(size, size);
    this->setIconSize(qsize);
    this->setObjectName("side_tool_button");
}

const std::string ToolButton::ICONS_PATH = ":/icons/";
