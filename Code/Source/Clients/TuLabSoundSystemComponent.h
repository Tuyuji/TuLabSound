/*
 * SPDX-License-Identifier: MIT
 * SPDX-FileCopyrightText: Copyright (c) 2025+ Reece Hagan
 *
 * For complete copyright and license terms please see the LICENSE at the root of this distribution.
 */
#pragma once

#include <AzCore/Component/Component.h>
#include <AzCore/Component/TickBus.h>
#include <TuLabSound/TuLabSoundBus.h>
#include <TuLabSound/AudioBusManagerInterface.h>

#include "BusManager.h"
#include "ImGuiBus.h"
#include "AzCore/Asset/AssetCommon.h"

namespace lab
{
    class SampledAudioNode;
}

namespace lab
{
    class AudioDevice;
    class AudioDestinationNode;
    class AudioContext;
}

namespace TuLabSound
{
    class SoundPlayer;
    class TuLabSoundSystemComponent
        : public AZ::Component
        , protected TuLabSoundRequestBus::Handler
        , protected AZ::TickBus::Handler
        , protected ImGui::ImGuiUpdateListenerBus::Handler
        , protected PlayerEffectFactoryBus::MultiHandler
    {
    public:
        AZ_COMPONENT_DECL(TuLabSoundSystemComponent);

        static void Reflect(AZ::ReflectContext* context);

        static void GetProvidedServices(AZ::ComponentDescriptor::DependencyArrayType& provided);
        static void GetIncompatibleServices(AZ::ComponentDescriptor::DependencyArrayType& incompatible);
        static void GetRequiredServices(AZ::ComponentDescriptor::DependencyArrayType& required);
        static void GetDependentServices(AZ::ComponentDescriptor::DependencyArrayType& dependent);

        TuLabSoundSystemComponent();
        ~TuLabSoundSystemComponent() override;

        // Disable copying
        TuLabSoundSystemComponent(const TuLabSoundSystemComponent&) = delete;
        TuLabSoundSystemComponent& operator=(const TuLabSoundSystemComponent&) = delete;

    protected:
        ////////////////////////////////////////////////////////////////////////
        // TuLabSoundRequestBus interface implementation
        std::shared_ptr<lab::AudioDevice> GetAudioDevice() const override { return m_device; }
        std::shared_ptr<lab::AudioContext> GetLabContext() const override { return m_context; }
        std::shared_ptr<lab::AudioDestinationNode> GetAudioDestination() const override { return m_destination; }

        SoundPlayerId CreatePlayer() override;
        void DestroyPlayer(SoundPlayerId id) override;

        IPlayerAudioEffect* CreateEffect(const AZStd::string& name) override;

        int GetPeriodSizeInFrames() const override
        {
            return m_periodSizeInFrames;
        }
        ////////////////////////////////////////////////////////////////////////

        ////////////////////////////////////////////////////////////////////////
        // AZ::Component interface implementation
        void Init() override;
        void Activate() override;
        void Deactivate() override;
        ////////////////////////////////////////////////////////////////////////

        ////////////////////////////////////////////////////////////////////////
        // AZTickBus interface implementation
        void OnTick(float deltaTime, AZ::ScriptTimePoint time) override;
        int GetTickOrder() override
        {
            return AZ::TICK_LAST;
        }
        ////////////////////////////////////////////////////////////////////////

        void OnImGuiMainMenuUpdate() override;
        void OnImGuiUpdate() override;
    private:
        friend class SoundPlayer;
        AZStd::vector<AZStd::unique_ptr<AZ::Data::AssetHandler>> m_assetHandlers = {};

        int m_periodSizeInFrames = 128;
        std::shared_ptr<lab::AudioDevice> m_device = {};
        std::shared_ptr<lab::AudioContext> m_context = {};
        std::shared_ptr<lab::AudioDestinationNode> m_destination = {};
        AZStd::shared_ptr<BusManager> m_busManager = {};

        AZStd::unordered_map<SoundPlayerId, AZStd::shared_ptr<SoundPlayer>> m_players = {};
    };

} // namespace TuLabSound
