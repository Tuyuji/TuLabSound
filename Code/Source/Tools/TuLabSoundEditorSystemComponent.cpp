/*
 * SPDX-License-Identifier: MIT
 * SPDX-FileCopyrightText: Copyright (c) 2025+ Reece Hagan
 *
 * For complete copyright and license terms please see the LICENSE at the root of this distribution.
 */
#include "TuLabSoundEditorSystemComponent.h"
#include <TuLabSound/TuLabSoundTypeIds.h>

#include <AzCore/Serialization/SerializeContext.h>

#include "SoundAssetBuilder.h"
#include "API/ViewPaneOptions.h"
#include "AssetBuilderSDK/AssetBuilderSDK.h"
#include "AzFramework/Asset/GenericAssetHandler.h"
#include "BuilderSettings/SoundAssetSettings.h"
#include "BuilderSettings/SoundBuilderSettings.h"
#include "BuilderSettings/SoundPresetSettings.h"
#include "BuilderSettings/SoundBuilderSettingsManager.h"
#include "TuLabSound/SoundAsset.h"

namespace TuLabSound
{
    AZ_COMPONENT_IMPL(TuLabSoundEditorSystemComponent, "TuLabSoundEditorSystemComponent",
        TuLabSoundEditorSystemComponentTypeId, BaseSystemComponent);

    void TuLabSoundEditorSystemComponent::Reflect(AZ::ReflectContext* context)
    {
        SoundAssetSettings::Reflect(context);
        SoundBuilderSettings::Reflect(context);
        PatternMapping::Reflect(context);
        SoundPresetSettings::Reflect(context);
        MultiplatformSoundPreset::Reflect(context);


        if (auto serializeContext = azrtti_cast<AZ::SerializeContext*>(context))
        {
            serializeContext->Class<TuLabSoundEditorSystemComponent, TuLabSoundSystemComponent>()
                ->Version(0)
                ->Attribute(AZ::Edit::Attributes::SystemComponentTags, AZStd::vector<AZ::Crc32>({ AZ_CRC_CE("AssetBuilder") }));
        }
    }

    TuLabSoundEditorSystemComponent::TuLabSoundEditorSystemComponent()
    {
        // GraphContext::SetInstance(AZStd::make_unique<GraphContext>());
    }

    TuLabSoundEditorSystemComponent::~TuLabSoundEditorSystemComponent()
    {
        // GraphContext::SetInstance(nullptr);
    }

    void TuLabSoundEditorSystemComponent::GetProvidedServices(AZ::ComponentDescriptor::DependencyArrayType& provided)
    {
        BaseSystemComponent::GetProvidedServices(provided);
        provided.push_back(AZ_CRC_CE("TuLabSoundEditorService"));
    }

    void TuLabSoundEditorSystemComponent::GetIncompatibleServices(AZ::ComponentDescriptor::DependencyArrayType& incompatible)
    {
        BaseSystemComponent::GetIncompatibleServices(incompatible);
        incompatible.push_back(AZ_CRC_CE("TuLabSoundEditorService"));
    }

    void TuLabSoundEditorSystemComponent::GetRequiredServices([[maybe_unused]] AZ::ComponentDescriptor::DependencyArrayType& required)
    {
        BaseSystemComponent::GetRequiredServices(required);
    }

    void TuLabSoundEditorSystemComponent::GetDependentServices([[maybe_unused]] AZ::ComponentDescriptor::DependencyArrayType& dependent)
    {
        dependent.push_back(AZ_CRC_CE("AssetDatabaseService"));
        dependent.push_back(AZ_CRC_CE("AssetCatalogService"));
        BaseSystemComponent::GetDependentServices(dependent);
    }

    void TuLabSoundEditorSystemComponent::Activate()
    {
        TuLabSoundSystemComponent::Activate();
        AzToolsFramework::EditorEvents::Bus::Handler::BusConnect();

        AssetBuilderSDK::AssetBuilderDesc materialAssetBuilderDescriptor;
        materialAssetBuilderDescriptor.m_name = "TuLabSound Sound Asset Builder";
        materialAssetBuilderDescriptor.m_version = 1;

        SoundBuilderSettingsManager* settingsManager = SoundBuilderSettingsManager::Get();
        if (settingsManager)
        {
            materialAssetBuilderDescriptor.m_analysisFingerprint = settingsManager->GetAnalysisFingerprint();
        }

        materialAssetBuilderDescriptor.m_patterns.push_back(
            AssetBuilderSDK::AssetBuilderPattern("*.ogg", AssetBuilderSDK::AssetBuilderPattern::PatternType::Wildcard));
        materialAssetBuilderDescriptor.m_patterns.push_back(
            AssetBuilderSDK::AssetBuilderPattern("*.flac", AssetBuilderSDK::AssetBuilderPattern::PatternType::Wildcard));
        materialAssetBuilderDescriptor.m_patterns.push_back(
            AssetBuilderSDK::AssetBuilderPattern("*.mp3", AssetBuilderSDK::AssetBuilderPattern::PatternType::Wildcard));
        materialAssetBuilderDescriptor.m_patterns.push_back(
            AssetBuilderSDK::AssetBuilderPattern("*.wav", AssetBuilderSDK::AssetBuilderPattern::PatternType::Wildcard));
        materialAssetBuilderDescriptor.m_busId = azrtti_typeid<SoundAssetBuilder>();
        materialAssetBuilderDescriptor.m_createJobFunction =
            [this](const AssetBuilderSDK::CreateJobsRequest& request, AssetBuilderSDK::CreateJobsResponse& response)
            {
                m_soundAssetBuilder.CreateJobs(request, response);
            };
        materialAssetBuilderDescriptor.m_processJobFunction =
            [this](const AssetBuilderSDK::ProcessJobRequest& request, AssetBuilderSDK::ProcessJobResponse& response)
            {
                m_soundAssetBuilder.ProcessJob(request, response);
            };
        m_soundAssetBuilder.BusConnect(materialAssetBuilderDescriptor.m_busId);
        AssetBuilderSDK::AssetBuilderBus::Broadcast(
            &AssetBuilderSDK::AssetBuilderBus::Handler::RegisterBuilderInformation, materialAssetBuilderDescriptor);
    }

    void TuLabSoundEditorSystemComponent::Deactivate()
    {
        AzToolsFramework::EditorEvents::Bus::Handler::BusDisconnect();
        TuLabSoundSystemComponent::Deactivate();
    }

    void TuLabSoundEditorSystemComponent::NotifyRegisterViews()
    {
        AzToolsFramework::ViewPaneOptions options;
        options.paneRect = QRect(100, 100, 500, 400);
        options.showOnToolsToolbar = true;
        options.toolbarIcon = ":/TuLabSound/toolbar_icon.svg";

        // Register our custom widget as a dockable tool with the Editor under an Examples sub-menu
        // AzToolsFramework::RegisterViewPane<TuLabSoundWidget>("TuLabSound", "Examples", options);
    }
} // namespace TuLabSound
