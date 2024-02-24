#pragma once

#include <QDoubleSpinBox>
#include <QHBoxLayout>
#include <QLineEdit>
#include <QWidget>

class Vector3fView : public QWidget
{
    Q_OBJECT
public:
    explicit Vector3fView(QWidget* parent = nullptr, std::string name = "default");

public slots:
    void setX(float x);
    void setY(float y);
    void setZ(float z);

signals:
    void xChanged(float x);
    void yChanged(float y);
    void zChanged(float z);

private:
    static const int MAX_LENGTH;
    static const int MAX_WIDTH;
    static const std::string NAME_STYLE;

    QHBoxLayout* m_pLayout;

    QDoubleSpinBox* m_pFieldX;
    QDoubleSpinBox* m_pFieldY;
    QDoubleSpinBox* m_pFieldZ;
};
