/***
 * Copyright (C) Falko Axmann. All rights reserved.
 * Licensed under the MIT license.
 * See LICENSE.txt file in the project root for full license information.
 ****/

#pragma once

#include <Spix/Commands/Command.h>
#include <Spix/Data/ItemPath.h>

namespace spix {
namespace cmd {

class CompleteDrag : public Command {
public:
    CompleteDrag(ItemPath path, int from_x, int from_y, int to_x, int to_y);

    void execute(CommandEnvironment& env) override;

private:
    ItemPath m_path;
    int m_from_x;
    int m_from_y;
    int m_to_x;
    int m_to_y;
};

} // namespace cmd
} // namespace spix
