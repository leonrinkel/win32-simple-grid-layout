#pragma once

#include <vector>

#include "Component.hpp"

struct GridLayoutItem
{

    UINT nCol;
    UINT nRow;
    UINT nColsWidth;
    UINT nRowsWidth;

    Component* pComp;

};


class GridLayout : public Component
{
protected:

    UINT m_nCols;
    UINT m_nRows;

    std::vector<GridLayoutItem> m_items;

public:

    GridLayout(
        _In_ UINT nCols,
        _In_ UINT nRows
    ) :
        m_nCols(nCols),
        m_nRows(nRows),
        m_items()
    {}

    void AddComponent(
        _In_ UINT       nCol,
        _In_ UINT       nRow,
        _In_ UINT       nColsWidth,
        _In_ UINT       nRowsWidth,        
        _In_ Component* pComp
    )
    {
        m_items.push_back({
            nCol,
            nRow,
            nColsWidth,
            nRowsWidth,
            pComp
        });
    }

    BOOL OnCreate(
        _In_ HWND hParentWnd
    )
    {
        for (const GridLayoutItem item : m_items)
        {
            if (!item.pComp->OnCreate(hParentWnd))
            {
                return FALSE;
            }
        }
        return TRUE;
    }

    void OnLayout(
        _In_ INT  x,
        _In_ INT  y,
        _In_ UINT width,
        _In_ UINT height
    )
    {
        UINT cellWidth = width / m_nCols;
        UINT cellHeight = height / m_nRows;

        for (const GridLayoutItem item : m_items)
        {
            UINT x0 = cellWidth * item.nCol;
            UINT x1 = cellWidth * (item.nCol + item.nColsWidth);

            UINT y0 = cellHeight * item.nRow;
            UINT y1 = cellHeight * (item.nRow + item.nRowsWidth);

            item.pComp->OnLayout(
                x + x0,
                y + y0,
                x1 - x0,
                y1 - y0
            );
        }
    }

    void OnDestroy()
    {
        for (const GridLayoutItem item : m_items)
        {
            item.pComp->OnDestroy();
        }
    }

};
