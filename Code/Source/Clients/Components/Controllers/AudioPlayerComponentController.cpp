/*
* SPDX-License-Identifier: MIT
 * SPDX-FileCopyrightText: Copyright (c) 2025+ Reece Hagan
 *
 * For complete copyright and license terms please see the LICENSE at the root of this distribution.
 */
#include "AudioPlayerComponentController.h"
#include <AzCore/Serialization/SerializeContext.h>

#include "TuLabSound/PlayerAudioEffect.h"

using namespace TuLabSound;

AudioPlayerComponentController::AudioPlayerComponentController(const AudioPlayerComponentConfig& config)
{
    m_config = config;
}

void AudioPlayerComponentController::Reflect(AZ::ReflectContext* context)
{
    AudioPlayerComponentConfig::Reflect(context);

    if (auto sc = azdynamic_cast<AZ::SerializeContext*>(context))
    {
        sc->Class<AudioPlayerComponentController>()
            ->Version(0)
            ->Field("Config", &AudioPlayerComponentController::m_config);
    }
}

void AudioPlayerComponentController::GetProvidedServices(AZ::ComponentDescriptor::DependencyArrayType& provided)
{
    provided.push_back(TuLabSound::AudioPlayerServiceName);
}

void AudioPlayerComponentController::GetIncompatibleServices(AZ::ComponentDescriptor::DependencyArrayType& incompatible)
{
    incompatible.push_back(TuLabSound::AudioPlayerServiceName);
}

void AudioPlayerComponentController::GetRequiredServices(AZ::ComponentDescriptor::DependencyArrayType& required)
{
}

void AudioPlayerComponentController::SetConfiguration(const AudioPlayerComponentConfig& config)
{
    m_config = config;
}

const AudioPlayerComponentConfig& AudioPlayerComponentController::GetConfiguration() const
{
    return m_config;
}

void AudioPlayerComponentController::Activate(const AZ::EntityComponentIdPair& entityComponentIdPair)
{
    m_entityComponentIdPair = entityComponentIdPair;
    m_playerId = TuLabSoundInterface::Get()->CreatePlayer();
    OnConfigurationUpdated();

    AudioPlayerRequestBus::Handler::BusConnect(m_entityComponentIdPair.GetEntityId());
}

void AudioPlayerComponentController::Deactivate()
{
    AudioPlayerRequestBus::Handler::BusDisconnect();
    TuLabSoundInterface::Get()->DestroyPlayer(m_playerId);
    m_playerId = SoundPlayerId();
}

void AudioPlayerComponentController::OnConfigurationUpdated()
{
    TuSoundPlayerRequestBus::Event(m_playerId, &TuSoundPlayerRequestBus::Events::SetBus, m_config.m_audioBus);
    TuSoundPlayerRequestBus::Event(m_playerId, &TuSoundPlayerRequestBus::Events::SetAsset, m_config.m_audioAsset.GetId());
    TuSoundPlayerRequestBus::Event(m_playerId, &TuSoundPlayerRequestBus::Events::SetPlayMultiple, m_config.m_playMultiple);
    TuSoundPlayerRequestBus::Event(m_playerId, &TuSoundPlayerRequestBus::Events::SetGain, m_config.m_gain);
}

SoundPlayerId AudioPlayerComponentController::GetPlayerId() const
{
    return m_playerId;
}

void AudioPlayerComponentController::Play()
{
    if (m_config.m_loop)
    {
        TuSoundPlayerRequestBus::Event(m_playerId, &TuSoundPlayerRequestBus::Events::PlayLooping, -1, 0.0f);
    }
    else
    {
        TuSoundPlayerRequestBus::Event(m_playerId, &TuSoundPlayerRequestBus::Events::Play);
    }
}
