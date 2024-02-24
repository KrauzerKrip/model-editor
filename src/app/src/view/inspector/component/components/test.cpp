#include "test.h"

#include "view/inspector/component/widgets/string_view.h"

TestComponent::TestComponent()
{
    m_pVectorView = new Vector3fView(this, "Position");
    m_pVectorView->setX(100);
    m_pVectorView->setY(100);
    m_pVectorView->setZ(100);
    this->addComponentWidget(m_pVectorView);

    StringView* pStringView = new StringView(this, "ID");
    pStringView->setString("test_object");
    this->addComponentWidget(pStringView);
}

TestComponent::~TestComponent() {}
