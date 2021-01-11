#ifndef UNICODE
#define UNICODE
#endif

#pragma comment(linker,"\"/manifestdependency:type='win32' \
    name='Microsoft.Windows.Common-Controls' version='6.0.0.0' \
    processorArchitecture='*' publicKeyToken='6595b64144ccf1df' language='*'\"")

#include <Windows.h>

#include "GridLayout.hpp"
#include "ButtonComponent.hpp"
#include "PaddingLayout.hpp"
#include "TestWindow.hpp"

int WINAPI wWinMain(
    _In_     HINSTANCE hInstance,
    _In_opt_ HINSTANCE hPrevInstance,
    _In_     PWSTR     pCmdLine,
    _In_     INT       nCmdShow
)
{
    GridLayout grid(2, 2);

    ButtonComponent btnA(L"A"), btnB(L"B"), btnC(L"C"), btnD(L"D");
    grid.AddComponent(0, 0, 1, 1, &btnA);
    grid.AddComponent(1, 0, 1, 1, &btnB);
    grid.AddComponent(0, 1, 1, 1, &btnC);
    grid.AddComponent(1, 1, 1, 1, &btnD);

    PaddingLayout padding(10, 10, 10, 10);
    padding.SetComponent(&grid);

    TestWindow wndTest(&padding);
    if (!wndTest.Create(L"Test Window"))
    {
        return 0;
    }
    wndTest.Show(nCmdShow);

    MSG msg = { 0 };
    while (GetMessage(&msg, NULL, 0, 0))
    {
        TranslateMessage(&msg);
        DispatchMessage(&msg);
    }
    
    return 0;
}
