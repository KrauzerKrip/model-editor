#pragma once

#include "view/inspector/component/component.h"
#include "view/inspector/component/widgets/vector3f_view.h"

class TestComponent : public Component
{
public:
    TestComponent();
    ~TestComponent();

private:
    Vector3fView* m_pVectorView;
};
