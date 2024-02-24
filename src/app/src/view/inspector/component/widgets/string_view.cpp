#include "string_view.h"

#include <QLabel>

StringView::StringView(QWidget* parent, std::string name)
    : QWidget{parent}
{
    m_pLayout = new QHBoxLayout(this);

    QLabel* pLabel = new QLabel(name.c_str(), this);
    m_pLayout->addWidget(pLabel, Qt::AlignLeft);
    pLabel->setStyleSheet(NAME_STYLE.c_str());

    m_pStringLabel = new QLabel(this);
    m_pStringLabel->setStyleSheet(NAME_STYLE.c_str());
    m_pLayout->addWidget(m_pStringLabel, Qt::AlignRight);
}

void StringView::setString(std::string string)
{
    m_pStringLabel->setText(string.c_str());
}

const std::string StringView::NAME_STYLE
    = "QLabel {margin-right: 20%; font-size: 12 px; background-color: transparent; "
      "border-radius: 4px;}";
