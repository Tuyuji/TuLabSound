/*
 * SPDX-License-Identifier: MIT
 * SPDX-FileCopyrightText: Copyright (c) 2025+ Reece Hagan
 *
 * For complete copyright and license terms please see the LICENSE at the root of this distribution.
 */
#pragma once

namespace TuLabSound
{
    // System Component TypeIds
    inline constexpr const char* TuLabSoundSystemComponentTypeId = "{500B499C-2E62-4163-BAA3-68A3838FCB31}";
    inline constexpr const char* TuLabSoundEditorSystemComponentTypeId = "{5B54BA1C-B259-4D8B-B5E7-132099B22F79}";

    // Module derived classes TypeIds
    inline constexpr const char* TuLabSoundModuleInterfaceTypeId = "{6CEEECCE-52B7-4DE1-BAAD-BF2F6AA724C1}";
    inline constexpr const char* TuLabSoundModuleTypeId = "{94FBCBBB-5D0A-4FBB-961F-034C0312F6E4}";
    // The Editor Module by default is mutually exclusive with the Client Module
    // so they use the Same TypeId
    inline constexpr const char* TuLabSoundEditorModuleTypeId = TuLabSoundModuleTypeId;

    // Interface TypeIds
    inline constexpr const char* TuLabSoundRequestsTypeId = "{F19B6EBA-5370-449E-A11E-360539E46BCF}";
    inline constexpr const char* AudioBusManagerRequestsTypeId = "{6857A5D6-A394-4723-A001-1F48BBADEAA5}";
    inline constexpr const char* AudioBusRequestsTypeId = "{D6147DA3-5B21-45AF-AF44-7CF6E787DEC9}";
    inline constexpr const char* TuSoundPlayerRequestsTypeId = "{58ECD253-93C8-42F3-9719-FC4DAB55EE7A}";


    inline constexpr const char* TuLabSoundSoundAssetTypeId = "{6CF7EA90-9FBF-4DB6-8199-A14C978E5EF3}";
    inline constexpr const char* TuLabSoundSoundAssetBuilderTypeId = "{ED3C6411-6871-4374-BCA5-9D04C33A9FC8}";
} // namespace TuLabSound
