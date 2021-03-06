#pragma once

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

class IConfig;

namespace AZ
{
    class SerializeContext;

    namespace RC
    {
        class ISceneConfig
        {
        public:
            virtual ~ISceneConfig() = 0;

            virtual const char* GetManifestFileExtension() const = 0;

            virtual void ReflectSceneModules(SerializeContext* context) = 0;
            virtual void ActivateSceneModules() = 0;
            virtual void DeactivateSceneModules() = 0;

            virtual size_t GetErrorCount() const = 0;
        };

        inline ISceneConfig::~ISceneConfig() = default;
    } // RC
} // AZ