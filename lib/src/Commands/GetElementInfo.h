/***
 * Copyright (C) Falko Axmann. All rights reserved.
 * Licensed under the MIT license.
 * See LICENSE.txt file in the project root for full license information.
 ****/

#pragma once

#include <Spix/spix_export.h>

#include "Command.h"
#include <Spix/Data/ItemPath.h>

#include <future>
#include <map>
#include <string>
#include <vector>

namespace spix {
namespace cmd {

/**
 * @brief Element information structure returned by GetElementInfo command
 */
struct ElementInfo {
    std::string objectName;
    std::string typeName;
    bool visible = false;
    std::vector<std::string> children;
};

class SPIX_EXPORT GetElementInfo : public Command {
public:
    GetElementInfo(ItemPath path, std::promise<ElementInfo> promise);

    void execute(CommandEnvironment& env) override;

private:
    ItemPath m_path;
    std::promise<ElementInfo> m_promise;
};

} // namespace cmd
} // namespace spix
