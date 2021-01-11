#pragma once

#include <Windows.h>

#include "Component.hpp"

template<class DERIVED_TYPE>
class BaseWindow
{
protected:

    HWND m_hWnd;

    virtual PCWSTR GetWindowClassName() const = 0;

public:

    static LRESULT CALLBACK WindowProc(
        _In_ HWND   hWnd,
        _In_ UINT   uMsg,
        _In_ WPARAM wParam,
        _In_ LPARAM lParam
    )
    {
        DERIVED_TYPE* pThis = NULL;

        if (uMsg == WM_NCCREATE)
        {
            CREATESTRUCT* pCreate = (CREATESTRUCT*) lParam;
            pThis = (DERIVED_TYPE*) pCreate->lpCreateParams;
            SetWindowLongPtr(hWnd, GWLP_USERDATA, (LONG_PTR) pThis);
            pThis->m_hWnd = hWnd;
        }
        else
        {
            pThis = (DERIVED_TYPE*) GetWindowLongPtr(hWnd, GWLP_USERDATA);
        }
        
        if (pThis)
        {
            return pThis->HandleMessage(uMsg, wParam, lParam);
        }
        else
        {
            return DefWindowProc(hWnd, uMsg, wParam, lParam);
        }        
    }

    BaseWindow() :
        m_hWnd(NULL)
    {}

    virtual LRESULT HandleMessage(
        _In_ UINT   uMsg,
        _In_ WPARAM wParam,
        _In_ LPARAM lParam
    ) = 0;

    BOOL Create(
        _In_ PCWSTR pWndName
    )
    {
        WNDCLASSEX wndClass    = { 0 };
        wndClass.cbSize        = sizeof(WNDCLASSEX);
        wndClass.style         = CS_HREDRAW | CS_VREDRAW;
        wndClass.lpfnWndProc   = DERIVED_TYPE::WindowProc;
        wndClass.hInstance     = GetModuleHandle(NULL);
        wndClass.hbrBackground = (HBRUSH) (COLOR_WINDOW + 1);
        wndClass.lpszClassName = GetWindowClassName();
        RegisterClassEx(&wndClass);

        m_hWnd = CreateWindowEx(
            0,
            GetWindowClassName(),
            pWndName,
            WS_OVERLAPPEDWINDOW,
            CW_USEDEFAULT, CW_USEDEFAULT,
            CW_USEDEFAULT, CW_USEDEFAULT,
            NULL,
            NULL,
            GetModuleHandle(NULL),
            this
        );
        return m_hWnd ? TRUE : FALSE;
    }

    void Show(
        _In_ INT nCmdShow
    )
    {
        ShowWindow(m_hWnd, nCmdShow);
    }

};
