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

#include "UiInteractableComponent.h"

#include <LyShine/Bus/UiDropdownBus.h>
#include <LyShine/Bus/UiInitializationBus.h>
#include <LyShine/Bus/UiInteractableBus.h>
#include <LyShine/Bus/UiCanvasBus.h>
#include <LyShine/UiComponentTypes.h>

#include <AzCore/Component/TickBus.h>

////////////////////////////////////////////////////////////////////////////////////////////////////
class UiDropdownComponent
    : public UiInteractableComponent
    , public UiDropdownBus::Handler
    , public UiInitializationBus::Handler
    , public UiCanvasInputNotificationBus::Handler
    , public UiInteractableNotificationBus::MultiHandler
    , public AZ::TickBus::Handler
{
public: // types

    //! These are the visual states
    enum
    {
        DropdownStateExpanded = UiInteractableStatesInterface::NumStates,
    };


public: // member functions

    AZ_COMPONENT(UiDropdownComponent, LyShine::UiDropdownComponentUuid, AZ::Component);

    UiDropdownComponent();
    ~UiDropdownComponent() override;

    // UiDropdownInterface
    AZ::EntityId GetValue() override;
    void SetValue(AZ::EntityId value) override;
    AZ::EntityId GetContent() override;
    void SetContent(AZ::EntityId content) override;
    bool GetExpandOnHover() override;
    void SetExpandOnHover(bool expandOnHover) override;
    float GetWaitTime() override;
    void SetWaitTime(float waitTime) override;
    bool GetCollapseOnOutsideClick() override;
    void SetCollapseOnOutsideClick(bool collapseOnOutsideClick) override;
    AZ::EntityId GetExpandedParentId() override;
    void SetExpandedParentId(AZ::EntityId expandedParentId) override;
    AZ::EntityId GetTextElement() override;
    void SetTextElement(AZ::EntityId textElement) override;
    AZ::EntityId GetIconElement() override;
    void SetIconElement(AZ::EntityId iconElement) override;
    void Expand() override;
    void Collapse() override;
    const LyShine::ActionName& GetExpandedActionName() override;
    void SetExpandedActionName(const LyShine::ActionName& actionName) override;
    const LyShine::ActionName& GetCollapsedActionName() override;
    void SetCollapsedActionName(const LyShine::ActionName& actionName) override;
    const LyShine::ActionName& GetOptionSelectedActionName() override;
    void SetOptionSelectedActionName(const LyShine::ActionName& actionName) override;
    // ~UiDropdownInterface

    // UiInitializationInterface
    void InGamePostActivate() override;
    // ~UiInitializationInterface

    // UiInteractableInterface
    bool HandleReleased(AZ::Vector2 point) override;
    bool HandleEnterReleased() override;
    void HandleHoverStart() override;
    void HandleHoverEnd() override;
    // ~UiInteractableInterface

    // UiInteractableNotifications
    void OnReceivedHoverByNavigatingFromDescendant(AZ::EntityId descendantEntityId) override;
    // ~UiInteractableNotifications

    // UiCanvasInputNotificationBus
    void OnCanvasPrimaryReleased(AZ::EntityId entityId) override;
    void OnCanvasEnterReleased(AZ::EntityId entityId) override;
    void OnCanvasHoverStart(AZ::EntityId entityId) override;
    void OnCanvasHoverEnd(AZ::EntityId entityId) override;
    // ~UiCanvasInputNotificationBus

    // TickBus
    void OnTick(float deltaTime, AZ::ScriptTimePoint time) override;
    // ~TickBus

protected: // member functions

    // AZ::Component
    void Activate() override;
    void Deactivate() override;
    // ~AZ::Component

    static void GetProvidedServices(AZ::ComponentDescriptor::DependencyArrayType& provided)
    {
        provided.push_back(AZ_CRC("UiInteractableService", 0x1d474c98));
        provided.push_back(AZ_CRC("UiStateActionsService"));
        provided.push_back(AZ_CRC("UiNavigationService"));
    }

    static void GetIncompatibleServices(AZ::ComponentDescriptor::DependencyArrayType& incompatible)
    {
        incompatible.push_back(AZ_CRC("UiInteractableService", 0x1d474c98));
        incompatible.push_back(AZ_CRC("UiNavigationService"));
        incompatible.push_back(AZ_CRC("UiStateActionsService"));
    }

    static void GetRequiredServices(AZ::ComponentDescriptor::DependencyArrayType& required)
    {
        required.push_back(AZ_CRC("UiElementService", 0x3dca7ad4));
        required.push_back(AZ_CRC("UiTransformService", 0x3a838e34));
    }

    static void Reflect(AZ::ReflectContext* context);

private: // member functions

    AZ_DISABLE_COPY_MOVE(UiDropdownComponent);

    using EntityComboBoxVec = AZStd::vector< AZStd::pair< AZ::EntityId, AZStd::string > >;
    EntityComboBoxVec PopulateChildEntityList();

    void OnExpandedStateActionsChanged();

    bool HandleReleasedCommon(const AZ::Vector2& point);
    void HandleCanvasReleasedCommon(AZ::EntityId entityId);

    void TransferHoverToDescendant();
    AZ::EntityId FindFirstDescendantInteractable(AZ::EntityId parentEntityId);
    AZ::EntityId CreateContentParentInteractable();
    bool ContentIsAncestor(AZ::EntityId entityId);

    // UiInteractableInterface
    UiInteractableStatesInterface::State ComputeInteractableState() override;
    // ~UiInteractableInterface

private: // data

    AZ::EntityId m_value;

    AZ::EntityId m_content;
    bool m_expandOnHover;
    float m_waitTime;
    bool m_collapseOnOutsideClick;
    AZ::EntityId m_expandedParentId;
    AZ::EntityId m_textElement;
    AZ::EntityId m_iconElement;
    StateActions m_expandedStateActions;
    LyShine::ActionName m_expandedActionName;
    LyShine::ActionName m_collapsedActionName;
    LyShine::ActionName m_optionSelectedActionName;

    bool m_expanded;
    AZ::EntityId m_canvasEntityId;
    float m_delayTimer;
    AZ::EntityId m_baseParent;
    LyShine::EntityArray m_submenus;
    bool m_expandedByClick;

    // An interactable that is created when the dropdown is expanded to act as the parent
    // of the content element. The content element needs a parent interactable in order to constrain
    // navigation between the content's descendant iteractables. Since the content element is
    // reparented from the dropdown interactable when expanded, this temporary interactable takes
    // place as the parent interactable.
    AZ::EntityId m_tempContentParentInteractable;
};
