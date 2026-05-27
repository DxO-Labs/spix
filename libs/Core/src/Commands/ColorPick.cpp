/***
 * Copyright (C) Falko Axmann. All rights reserved.
 * Licensed under the MIT license.
 * See LICENSE.txt file in the project root for full license information.
 ****/

#include "ColorPick.h"

#include <Spix/Scene/Scene.h>
#include <sstream>

namespace spix {
namespace cmd {

ColorPick::ColorPick(ItemPath targetItemPath, int x, int y, std::promise<std::string> promise)
: m_itemPath(std::move(targetItemPath))
,m_x(x)
, m_y(y)
, m_promise(std::move(promise))
{
}

void ColorPick::execute(CommandEnvironment& env)
{
    const auto color = env.scene().colorAtPoint(m_itemPath, m_x, m_y);
    std::stringstream str;
    str << color.r << "," << color.g << "," << color.b;
    m_promise.set_value(str.str());
}

} // namespace cmd
} // namespace spix
