#pragma once

#include "Component.hpp"

class ButtonComponent : public Component
{
protected:

    PCWSTR m_pLabel;
    HWND   m_hWnd;
    HFONT  m_hFont;

public:

    ButtonComponent(
        PCWSTR pLabel
    ) :
        m_pLabel(pLabel),
        m_hWnd(NULL),
        m_hFont(NULL)
    {}

    BOOL OnCreate(
        HWND hParentWnd
    )
    {
        m_hWnd = CreateWindow(
            L"BUTTON",
            m_pLabel,
            WS_CHILD | WS_VISIBLE,
            CW_USEDEFAULT, CW_USEDEFAULT,
            CW_USEDEFAULT, CW_USEDEFAULT,
            hParentWnd,
            NULL,
            (HINSTANCE) GetWindowLongPtr(hParentWnd, GWLP_HINSTANCE),
            NULL
        );
        if (!m_hWnd)
        {
            return FALSE;
        }

        NONCLIENTMETRICS metrics = { 0 };
        metrics.cbSize = sizeof(NONCLIENTMETRICS);
        SystemParametersInfo(
            SPI_GETNONCLIENTMETRICS,
            metrics.cbSize,
            &metrics,
            0
        );

        m_hFont = CreateFontIndirect(&metrics.lfCaptionFont);
        SendMessage(m_hWnd, WM_SETFONT, (WPARAM) m_hFont, MAKELPARAM(FALSE, 0));

        ShowWindow(m_hWnd, SW_SHOWDEFAULT);

        return TRUE;
    }

    void OnLayout(
        _In_ INT  x,
        _In_ INT  y,
        _In_ UINT width,
        _In_ UINT height
    )
    {
        HDWP hDWP = BeginDeferWindowPos(1);
        if (hDWP)
        {
            DeferWindowPos(
                hDWP,
                m_hWnd,
                NULL,
                x, y,
                width, height,
                SWP_NOZORDER
            );
        }
        EndDeferWindowPos(hDWP);
    }

    void OnDestroy()
    {
        if (m_hFont)
        {
            DeleteObject(m_hFont);
        }
    }

};
