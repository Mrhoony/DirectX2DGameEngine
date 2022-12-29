#include "stdafx.h"
#include "Intersect.h"
#include "Scene/Rendering/Rect.h"

bool Intersect::IsIntersect(Rect* const lhs, Rect* const rhs)
{
    if (lhs->IsActive() == false || rhs->IsActive() == false)
        return false;

    D3DXVECTOR3 lhs_min = lhs->GetPosition() - (lhs->GetScale() * 0.5);
    D3DXVECTOR3 lhs_max = lhs->GetPosition() + (lhs->GetScale() * 0.5);

    D3DXVECTOR3 rhs_min = rhs->GetPosition() - (rhs->GetScale() * 0.5);
    D3DXVECTOR3 rhs_max = rhs->GetPosition() + (rhs->GetScale() * 0.5);

    bool check = true;

    check &= lhs_max.x > rhs_min.x;
    check &= lhs_min.x < rhs_max.x;
    check &= lhs_max.y > rhs_min.y;
    check &= lhs_min.y < rhs_max.y;

    return check;
}
