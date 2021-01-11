#pragma once

#include <Windows.h>

class Component
{
public:

    virtual BOOL OnCreate(
        HWND hParentWnd
    ) = 0;

    virtual void OnLayout(
        _In_ INT  x,
        _In_ INT  y,
        _In_ UINT width,
        _In_ UINT height
    ) = 0;

    virtual void OnDestroy() = 0;

};
