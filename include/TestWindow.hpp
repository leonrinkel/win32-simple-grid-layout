#include "BaseWindow.hpp"

class TestWindow : public BaseWindow<TestWindow>
{
protected:

    Component* m_pComp;

    PCWSTR GetWindowClassName() const
    {
        return L"Test Window Class";
    }

public:

    TestWindow(
        _In_ Component* pComp
    ) :
        BaseWindow(),
        m_pComp(pComp)
    {}

    LRESULT HandleMessage(
        _In_ UINT   uMsg,
        _In_ WPARAM wParam,
        _In_ LPARAM lParam
    )
    {
        switch (uMsg)
        {
        case WM_CREATE:
            m_pComp->OnCreate(m_hWnd);
            return 0;

        case WM_SIZE:
            {
                UINT width = LOWORD(lParam);
                UINT height = HIWORD(lParam);
                m_pComp->OnLayout(0, 0, width, height);
            }
            return 0;

        case WM_DESTROY:
            m_pComp->OnDestroy();
            PostQuitMessage(0);
            return 0;
        }

        return DefWindowProc(m_hWnd, uMsg, wParam, lParam);
    }

};
