/***
 * Copyright (C) Falko Axmann. All rights reserved.
 * Licensed under the MIT license.
 * See LICENSE.txt file in the project root for full license information.
 ****/

#pragma once

#include <Spix/Commands/Command.h>
#include <Spix/Data/ItemPath.h>
#include <future>

namespace spix {
namespace cmd {

class ColorPick : public Command {
public:
    ColorPick(ItemPath targetItemPath, int x, int y, std::promise<std::string> promise);

    void execute(CommandEnvironment& env) override;

private:
    ItemPath m_itemPath;
    int m_x;
    int m_y;
    std::promise<std::string> m_promise;
};

} // namespace cmd
} // namespace spix
