#pragma once

#include "Component.hpp"

class PaddingLayout : public Component
{
protected:

    UINT m_left;
    UINT m_top;
    UINT m_right;
    UINT m_bottom;    

    Component* m_pComp;

public:

    PaddingLayout(
        UINT left,
        UINT top,
        UINT right,
        UINT bottom
    ) :
        m_left(left),
        m_top(top),
        m_right(right),
        m_bottom(bottom)        
    {}

    void SetComponent(
        _In_ Component* pComp
    )
    {
        m_pComp = pComp;
    }

    BOOL OnCreate(
        _In_ HWND hParentWnd
    )
    {
        return m_pComp->OnCreate(hParentWnd);
    }

    void OnLayout(
        _In_ INT  x,
        _In_ INT  y,
        _In_ UINT width,
        _In_ UINT height
    )
    {
        m_pComp->OnLayout(
            x + m_left,
            y + m_top,
            width - m_left - m_right,
            height - m_top - m_bottom
        );
    }


    void OnDestroy()
    {
        return m_pComp->OnDestroy();
    }

};
