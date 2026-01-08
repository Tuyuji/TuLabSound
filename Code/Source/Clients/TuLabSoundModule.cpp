/*
 * SPDX-License-Identifier: MIT
 * SPDX-FileCopyrightText: Copyright (c) 2025+ Reece Hagan
 *
 * For complete copyright and license terms please see the LICENSE at the root of this distribution.
 */
#include <TuLabSound/TuLabSoundTypeIds.h>
#include <TuLabSoundModuleInterface.h>
#include "TuLabSoundSystemComponent.h"

namespace TuLabSound
{
    class TuLabSoundModule
        : public TuLabSoundModuleInterface
    {
    public:
        AZ_RTTI(TuLabSoundModule, TuLabSoundModuleTypeId, TuLabSoundModuleInterface);
        AZ_CLASS_ALLOCATOR(TuLabSoundModule, AZ::SystemAllocator);
    };
}// namespace TuLabSound

#if defined(O3DE_GEM_NAME)
AZ_DECLARE_MODULE_CLASS(AZ_JOIN(Gem_, O3DE_GEM_NAME), TuLabSound::TuLabSoundModule)
#else
AZ_DECLARE_MODULE_CLASS(Gem_TuLabSound, TuLabSound::TuLabSoundModule)
#endif
