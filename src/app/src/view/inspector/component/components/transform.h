#pragma once

#include "view/inspector/component/component.h"
#include "view/inspector/component/widgets/vector3f_view.h"
#include <QWidget>

namespace view {
class Transform : public Component
{
public:
    Transform(QWidget* parent);

private:
    Vector3fView* m_pPositionView;
    Vector3fView* m_pRotationView;
    Vector3fView* m_pScaleView;
};
} // namespace view
