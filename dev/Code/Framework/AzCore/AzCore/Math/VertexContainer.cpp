/*
* All or portions of this file Copyright (c) Amazon.com, Inc. or its affiliates or
* its licensors.
*
* For complete copyright and license terms please see the LICENSE at the root of this
* distribution (the "License"). All use of this software is governed by the License,
* or, if provided, by the license below or the license accompanying this file. Do not
* remove or modify any license notices. This file is distributed on an "AS IS" BASIS,
* WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
*
*/
#ifndef AZ_UNITY_BUILD

#include <AzCore/Math/VertexContainer.h>
#include <AzCore/Math/Vector3.h>
#include <AzCore/Math/Vector2.h>
#include <AzCore/Memory/SystemAllocator.h>
#include <AzCore/Serialization/EditContext.h>
#include <AzCore/Serialization/SerializeContext.h>

namespace AZ
{
    void VertexContainerReflect(SerializeContext& context)
    {
        VertexContainer<Vector2>::Reflect(context);
        VertexContainer<Vector3>::Reflect(context);
    }

    AZ_CLASS_ALLOCATOR_IMPL_TEMPLATE(VertexContainer<Vector2>, AZ::SystemAllocator, 0)
    AZ_CLASS_ALLOCATOR_IMPL_TEMPLATE(VertexContainer<Vector3>, AZ::SystemAllocator, 0)
}

#endif // #ifndef AZ_UNITY_BUILD