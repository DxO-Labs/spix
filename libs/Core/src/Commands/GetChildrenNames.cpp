/***
 * Copyright (C) Falko Axmann. All rights reserved.
 * Licensed under the MIT license.
 * See LICENSE.txt file in the project root for full license information.
 ****/

#include "GetChildrenNames.h"

#include <Spix/Scene/Scene.h>

namespace spix {
namespace cmd {

GetChildrenNames::GetChildrenNames(ItemPath path, std::promise<std::vector<std::string>> promise)
: m_path(std::move(path))
, m_promise(std::move(promise))
{
}

void GetChildrenNames::execute(CommandEnvironment& env)
{
    auto item = env.scene().itemAtPath(m_path);

    if (item) {
        m_promise.set_value(item->childrenNames());
    } else {
        m_promise.set_value({});
        env.state().reportError("GetChildrenNames: Item not found: " + m_path.string());
    }
}

} // namespace cmd
} // namespace spix
