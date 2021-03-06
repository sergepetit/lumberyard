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

#include <IGem.h>

#include <AzFramework/API/ApplicationAPI.h>
#include <AzFramework/Input/Events/InputChannelEventListener.h>

////////////////////////////////////////////////////////////////////////////////////////////////////
namespace ProcessLifeManagement
{
    ////////////////////////////////////////////////////////////////////////////////////////////////
    class ProcessLifeManagementGem
        : public CryHooksModule
        , public AzFramework::ApplicationLifecycleEvents::Bus::Handler
        , public AzFramework::InputChannelEventNotificationBus::Handler
    {
        AZ_RTTI(ProcessLifeManagementGem, "{D2BE47BB-53A7-4121-977D-95C94DF65155}", CryHooksModule)

    public:
        ProcessLifeManagementGem();
        ~ProcessLifeManagementGem() override;

        void OnApplicationConstrained(AzFramework::ApplicationLifecycleEvents::Event /*lastEvent*/) override;
        void OnApplicationUnconstrained(AzFramework::ApplicationLifecycleEvents::Event /*lastEvent*/) override;

        void OnInputChannelEvent(const AzFramework::InputChannel& inputChannel, bool& o_hasBeenConsumed) override;
        AZ::s32 GetPriority() const override { return AzFramework::InputChannelEventListener::GetPriorityFirst(); }

    private:
        AZ::EntityId m_pausedCanvasId;
    };
} // namespace ProcessLifeManagement
