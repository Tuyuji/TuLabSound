/*
 * SPDX-License-Identifier: MIT
 * SPDX-FileCopyrightText: Copyright (c) 2025+ Reece Hagan
 *
 * For complete copyright and license terms please see the LICENSE at the root of this distribution.
 */
#pragma once

#include <AzCore/std/containers/vector.h>
#include <AzCore/std/smart_ptr/unique_ptr.h>
#include <AzCore/Asset/AssetManager.h>

#include <Clients/TuLabSoundSystemComponent.h>
#include <Tools/SoundAssetBuilder.h>

#include "API/ToolsApplicationAPI.h"

namespace TuLabSound
{
    /// System component for TuLabSound editor
    class TuLabSoundEditorSystemComponent
        : public TuLabSoundSystemComponent
        , protected AzToolsFramework::EditorEvents::Bus::Handler
    {
        using BaseSystemComponent = TuLabSoundSystemComponent;
    public:
        AZ_COMPONENT_DECL(TuLabSoundEditorSystemComponent);

        static void Reflect(AZ::ReflectContext* context);

        TuLabSoundEditorSystemComponent();
        ~TuLabSoundEditorSystemComponent() override;

    private:
        static void GetProvidedServices(AZ::ComponentDescriptor::DependencyArrayType& provided);
        static void GetIncompatibleServices(AZ::ComponentDescriptor::DependencyArrayType& incompatible);
        static void GetRequiredServices(AZ::ComponentDescriptor::DependencyArrayType& required);
        static void GetDependentServices(AZ::ComponentDescriptor::DependencyArrayType& dependent);

        // AZ::Component
        void Activate() override;
        void Deactivate() override;

        void NotifyRegisterViews() override;

        SoundAssetBuilder m_soundAssetBuilder;
    };
} // namespace TuLabSound
