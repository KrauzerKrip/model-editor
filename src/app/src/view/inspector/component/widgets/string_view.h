#pragma once

#include <string>
#include <QHBoxLayout>
#include <QLabel>
#include <QWidget>

class StringView : public QWidget
{
    Q_OBJECT
public:
    explicit StringView(QWidget* parent = nullptr, std::string name = "default");

public slots:
    void setString(std::string string);

signals:

private:
    static const std::string NAME_STYLE;

    QHBoxLayout* m_pLayout;
    QLabel* m_pStringLabel;
};
