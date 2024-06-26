#pragma once
#include "Vector/Vector3.h"
#include "Vector/Vector4.h"
#include "Matrix/Matrix4.h"

#include <limits>

namespace LibMath
{
    struct BoundingBox
    {
        Vector3 m_min;
        Vector3 m_max;
    };

    inline BoundingBox transformBoundingBox(BoundingBox boundingBox, const Matrix4& transform)
    {
        Vector3 corners[8]
        {
            boundingBox.m_min,
            { boundingBox.m_min.m_x, boundingBox.m_max.m_y, boundingBox.m_min.m_z },
            { boundingBox.m_min.m_x, boundingBox.m_min.m_y, boundingBox.m_max.m_z },
            { boundingBox.m_min.m_x, boundingBox.m_max.m_y, boundingBox.m_max.m_z },
            { boundingBox.m_max.m_x, boundingBox.m_min.m_y, boundingBox.m_max.m_z },
            { boundingBox.m_max.m_x, boundingBox.m_max.m_y, boundingBox.m_min.m_z },
            { boundingBox.m_max.m_x, boundingBox.m_min.m_y, boundingBox.m_min.m_z },
            boundingBox.m_max
        };

        boundingBox.m_min = Vector3(std::numeric_limits<float>::max());
        boundingBox.m_max = Vector3(std::numeric_limits<float>::lowest());

        for (Vector3& corner : corners)
        {
            corner            = (transform * Vector4(corner, 1.f)).xyz();
            boundingBox.m_min = min(boundingBox.m_min, corner);
            boundingBox.m_max = max(boundingBox.m_max, corner);
        }

        return boundingBox;
    }
}
