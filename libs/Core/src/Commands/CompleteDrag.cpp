/***
 * Copyright (C) Falko Axmann. All rights reserved.
 * Licensed under the MIT license.
 * See LICENSE.txt file in the project root for full license information.
 ****/

#include "CompleteDrag.h"

#include <Spix/Scene/Scene.h>
#include <Spix/Events/Identifiers.h>
#include <thread>

namespace spix {
namespace cmd {

CompleteDrag::CompleteDrag(ItemPath path, int from_x, int from_y, int to_x, int to_y)
: m_path(std::move(path))
, m_from_x(from_x)
, m_from_y(from_y)
, m_to_x(to_x), m_to_y(to_y)
{
}

void CompleteDrag::execute(CommandEnvironment& env)
{
    using namespace std::chrono_literals;

    auto item = env.scene().itemAtPath(m_path);

    if (!item) {
        env.state().reportError("DragBegin: Item not found: " + m_path.string());
        return;
    }

    auto size = item->size();
    Point midPoint(size.width / 2.0, size.height / 2.0);
    env.scene().events().mouseDown(item.get(), midPoint, spix::MouseButtons::Left, spix::KeyModifiers::None);
    env.scene().events().mouseMove(item.get(), midPoint);

    Point nextPoint = midPoint;
    nextPoint.x += m_to_x;
    //nextPoint.y += m_to_y;
    //nextPoint.x = midPoint.x - 100;


    env.scene().events().mouseMove(item.get(), nextPoint);
    std::this_thread::sleep_for(50ms);
    env.scene().events().mouseUp(item.get(), nextPoint, spix::MouseButtons::Left, spix::KeyModifiers::None);
}

} // namespace cmd
} // namespace spix
