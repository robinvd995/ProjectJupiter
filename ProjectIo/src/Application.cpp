#include <iostream>
#include <string>

#include "CommandParser.hpp"
#include "ProjectIo.h"

int main(int argc, char* argv[])
{
    Jupiter::CommandParser commandParser(argc, argv);
    std::string cfgLocation;
    bool hasConfig = commandParser.findArgument("config", cfgLocation);
    if (!hasConfig) cfgLocation = "Config.io";

    Jupiter::Io::ProjectIO projectIo(cfgLocation);

    projectIo.init();

    std::string error;
    if (!projectIo.load(error)) { std::cout << error << std::endl; return 0; }
    if (!projectIo.execute(error)) { std::cout << error << std::endl; return 0; }
    if (!projectIo.release(error)) { std::cout << error << std::endl; return 0; }

}
