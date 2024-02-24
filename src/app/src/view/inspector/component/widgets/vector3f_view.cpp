#include "vector3f_view.h"

#include <algorithm>
#include <functional>
#include <vector>

#include <QLabel>
#include <QSpinBox>

Vector3fView::Vector3fView(QWidget* parent, std::string name)
    : QWidget{parent}
{
    m_pLayout = new QHBoxLayout(this);
    this->setLayout(m_pLayout);

    //QMargins margins;
    //margins.setLeft(0);
    //m_pLayout->setContentsMargins(margins);

    QLabel* pLabel = new QLabel(this);
    pLabel->setText(name.c_str());
    pLabel->setStyleSheet(NAME_STYLE.c_str());
    m_pLayout->addWidget(pLabel, Qt::AlignLeft);

    m_pFieldX = new QDoubleSpinBox(this);
    m_pFieldY = new QDoubleSpinBox(this);
    m_pFieldZ = new QDoubleSpinBox(this);

    m_pFieldX->setObjectName("vector_field_x");
    m_pFieldY->setObjectName("vector_field_y");
    m_pFieldZ->setObjectName("vector_field_z");

    std::vector<QDoubleSpinBox*> fields;
    fields.push_back(m_pFieldX);
    fields.push_back(m_pFieldY);
    fields.push_back(m_pFieldZ);

    std::ranges::for_each(std::as_const(fields), [this](QDoubleSpinBox* pField) {
        m_pLayout->addWidget(pField, Qt::AlignRight);
        pField->setMaximum(9999999);
        pField->setMaximumWidth(80);
    });

    //    std::ranges::for_each(std::as_const(fields),
    //                          [](QSpinBox* m_pField) { m_pField->setMaximumSize(MAX_LENGTH); });

    //    std::ranges::for_each(std::as_const(fields),
    //                          [](QDoubleSpinBox* m_pField) { m_pField->setMaximumWidth(MAX_WIDTH); });
}

void Vector3fView::setX(float x)
{
    m_pFieldX->setValue(x);
}

void Vector3fView::setY(float y)
{
    m_pFieldY->setValue(y);
}

void Vector3fView::setZ(float z)
{
    m_pFieldZ->setValue(z);
}

const int Vector3fView::MAX_LENGTH = 16;
const int Vector3fView::MAX_WIDTH = 72;
const std::string Vector3fView::NAME_STYLE
    = "QLabel {margin-right: 20%; font-size: 12 px; background-color: transparent; "
      "border-radius: 4px;}";
