/*
 * SPDX-License-Identifier: MIT
 * SPDX-FileCopyrightText: Copyright (c) 2025+ Reece Hagan
 *
 * For complete copyright and license terms please see the LICENSE at the root of this distribution.
 */
#include <TuLabSound/TuLabSoundTypeIds.h>
#include <TuLabSoundModuleInterface.h>
#include "TuLabSoundEditorSystemComponent.h"
#include "Components/EditorAudioPlayerComponent.h"

void InitTuLabSoundResources()
{
    Q_INIT_RESOURCE(TuLabSound);
}

namespace TuLabSound
{
    class TuLabSoundEditorModule
        : public TuLabSoundModuleInterface
    {
    public:
        AZ_RTTI(TuLabSoundEditorModule, TuLabSoundEditorModuleTypeId, TuLabSoundModuleInterface);
        AZ_CLASS_ALLOCATOR(TuLabSoundEditorModule, AZ::SystemAllocator);

        TuLabSoundEditorModule()
        {
            // Push results of [MyComponent]::CreateDescriptor() into m_descriptors here.
            // Add ALL components descriptors associated with this gem to m_descriptors.
            // This will associate the AzTypeInfo information for the components with the the SerializeContext, BehaviorContext and EditContext.
            // This happens through the [MyComponent]::Reflect() function.
            m_descriptors.insert(m_descriptors.end(), {
                TuLabSoundEditorSystemComponent::CreateDescriptor(),
                EditorAudioPlayerComponent::CreateDescriptor()
            });
        }

        /**
         * Add required SystemComponents to the SystemEntity.
         * Non-SystemComponents should not be added here
         */
        AZ::ComponentTypeList GetRequiredSystemComponents() const override
        {
            return AZ::ComponentTypeList {
                azrtti_typeid<TuLabSoundEditorSystemComponent>(),
            };
        }
    };
}// namespace TuLabSound

#if defined(O3DE_GEM_NAME)
AZ_DECLARE_MODULE_CLASS(AZ_JOIN(Gem_, O3DE_GEM_NAME, _Editor), TuLabSound::TuLabSoundEditorModule)
#else
AZ_DECLARE_MODULE_CLASS(Gem_TuLabSound_Editor, TuLabSound::TuLabSoundEditorModule)
#endif
