/***
 * Copyright (C) Falko Axmann. All rights reserved.
 * Licensed under the MIT license.
 * See LICENSE.txt file in the project root for full license information.
 ****/

#include "GetElementInfo.h"

#include <Spix/Scene/Scene.h>

namespace spix {
namespace cmd {

GetElementInfo::GetElementInfo(ItemPath path, std::promise<ElementInfo> promise)
: m_path(std::move(path))
, m_promise(std::move(promise))
{
}

void GetElementInfo::execute(CommandEnvironment& env)
{
    ElementInfo info;
    auto item = env.scene().itemAtPath(m_path);

    if (item) {
        info.objectName = item->objectName();
        info.typeName = item->typeName();
        info.visible = item->visible();
        info.children = item->childrenNames();
    } else {
        env.state().reportError("GetElementInfo: Item not found: " + m_path.string());
    }

    m_promise.set_value(std::move(info));
}

} // namespace cmd
} // namespace spix
