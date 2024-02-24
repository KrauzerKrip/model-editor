#pragma once

#include <string>
#include <QVBoxLayout>
#include <QWidget>

class Component : public QWidget
{
    //Q_OBJECT
public:
    explicit Component(QWidget* parent = nullptr, std::string name = "default");

    //signals:

protected:
    void addComponentWidget(QWidget* pWidget);

private:
    QVBoxLayout* m_pLayout;
};
