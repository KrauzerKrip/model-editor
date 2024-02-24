#include "transform.h"

view::Transform::Transform(QWidget* parent)
    : Component(parent, "Transform")
{
    m_pPositionView = new Vector3fView(this, "Position");
    this->addComponentWidget(m_pPositionView);
    m_pRotationView = new Vector3fView(this, "Rotation");
    this->addComponentWidget(m_pRotationView);
    m_pScaleView = new Vector3fView(this, "Scale");
    this->addComponentWidget(m_pScaleView);
}
