/***
 * Copyright (C) Falko Axmann. All rights reserved.
 * Licensed under the MIT license.
 * See LICENSE.txt file in the project root for full license information.
 ****/

#pragma once

#include <chrono>
#include <functional>
#include <memory>
#include <thread>

#include <Spix/Data/Geometry.h>
#include <Spix/Data/ItemPath.h>
#include <Spix/Data/Variant.h>
#include <Spix/Events/Identifiers.h>

#include <Spix/spix_export.h>

namespace spix {

class CommandExecuter;

/**
 * @brief Base class that serves a test to the bot.
 *
 * A `TestServer` can be run by the bot and serves the
 * test to the bot. It can be a simple test case written
 * in C++ or it can be an actual server that handles
 * incoming RPC calls.
 * For basic C++ based tests, derive from this class and overide
 * the `executeTest` method.
 *
 * The code in `executeTest` is executed in its own thread so that
 * it does not affect the execution of the main application.
 */
class SPIX_EXPORT TestServer {
public:
    virtual ~TestServer();

    void start();
    void setCommandExecuter(CommandExecuter* exec);

    void setGenericCommandHandler(std::function<std::string(std::string, std::string)> handler);

    // Commands
    void wait(std::chrono::milliseconds waitTime);
    void mouseClick(ItemPath path, bool eventToItem = false);
    void mouseDoubleClick(ItemPath path, bool eventToItem = false);
    //void mouseClick(ItemPath path, MouseButton mouseButton);
    void mouseBeginDrag(ItemPath path);
    void mouseEndDrag(ItemPath path);
    void mouseDropUrls(ItemPath path, const std::vector<std::string>& urls);
    std::string genericCommand(std::string command, std::string payload);

    void inputText(ItemPath path, std::string text);
    void enterKey(ItemPath path, int keyCode, unsigned modifiers);

    std::string getStringProperty(ItemPath path, std::string propertyName);
    void setStringProperty(ItemPath path, std::string propertyName, std::string propertyValue);
    Variant invokeMethod(ItemPath path, std::string method, std::vector<Variant> args);
    Rect getBoundingBox(ItemPath path);
    bool existsAndVisible(ItemPath path);
    std::vector<std::string> getErrors();

    void dragItem(ItemPath path, int x, int y);

    void takeScreenshot(ItemPath targetItem, std::string filePath);
    std::string pickColorAt(ItemPath path, int x, int y);
    void quit();

protected:
    virtual void executeTest() = 0;

private:
    CommandExecuter* m_cmdExec;
    std::thread m_thread;
    std::function<std::string(std::string, std::string)> m_handler;
};

} // namespace spix
