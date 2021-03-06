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

#pragma once

#include <ScriptCanvas/Core/NativeDatumNode.h>

namespace ScriptCanvas
{
    namespace Nodes
    {
        namespace Math
        {
            const bool k_AABBNodeHasProperties = true;

            class AABB
                : public NativeDatumNode<AABB, Data::AABBType, k_AABBNodeHasProperties>
            {
            public:
                using ParentType = NativeDatumNode<AABB, Data::AABBType, k_AABBNodeHasProperties>;
                AZ_COMPONENT(AABB, "{AB0C2753-680E-47AD-8277-66B3AC01C659}", ParentType);

                static void Reflect(AZ::ReflectContext* reflection)
                {
                    ParentType::Reflect(reflection);

                    if (AZ::SerializeContext* serializeContext = azrtti_cast<AZ::SerializeContext*>(reflection))
                    {
                        serializeContext->Class<AABB, ParentType>()
                            ->Version(0)
                            ;

                        if (AZ::EditContext* editContext = serializeContext->GetEditContext())
                        {
                            editContext->Class<AABB>("AABB", "An axis-aligned bounding box value")
                                ->ClassElement(AZ::Edit::ClassElements::EditorData, "")
                                ->Attribute(AZ::Edit::Attributes::Icon, "Editor/Icons/ScriptCanvas/AABB.png")
                                ->Attribute(AZ::Edit::Attributes::Visibility, AZ::Edit::PropertyVisibility::ShowChildrenOnly)
                                ->Attribute(AZ::Script::Attributes::ExcludeFrom, AZ::Script::Attributes::ExcludeFlags::All)
                                ;
                        }
                    }
                }

                void AddProperties()
                {
                    AddProperty(&Data::AABBType::GetMin, &Data::AABBType::SetMin, "min");
                    AddProperty(&Data::AABBType::GetMax, &Data::AABBType::SetMax, "max");
                }

                void Visit(NodeVisitor& visitor) const override
                {
                    visitor.Visit(*this);
                }
            };
        }
    }
}