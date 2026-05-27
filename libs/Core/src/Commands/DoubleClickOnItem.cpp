/***
 * Copyright (C) Falko Axmann. All rights reserved.
 * Licensed under the MIT license.
 * See LICENSE.txt file in the project root for full license information.
 ****/

#include "DoubleClickOnItem.h"

#include <Spix/Scene/Scene.h>

namespace spix {
namespace cmd {

DoubleClickOnItem::DoubleClickOnItem(ItemPosition path, bool eventToItem)
: m_position(std::move(path))
, m_eventToItem(eventToItem)
{
}

void DoubleClickOnItem::execute(CommandEnvironment& env)
{
    auto path = m_position.itemPath();
    auto item = env.scene().itemAtPath(path);

    if (!item) {
        env.state().reportError("ClickOnItem: Item not found: " + path.string());
        return;
    }

    auto size = item->size();
    auto mousePoint = m_position.positionForItemSize(size);
    env.scene().events().mouseDown(item.get(), mousePoint, spix::MouseButtons::Left, m_eventToItem);
    env.scene().events().mouseUp(item.get(), mousePoint, spix::MouseButtons::Left, m_eventToItem);
    env.scene().events().mouseDoubleClick(item.get(), mousePoint, spix::MouseButtons::Left, m_eventToItem);
}

} // namespace cmd
} // namespace spix
