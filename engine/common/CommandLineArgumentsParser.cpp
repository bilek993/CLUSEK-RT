//
// Created by jbili on 27.04.2021.
//

#include "CommandLineArgumentsParser.h"

CommandLineArgumentsParser::CommandLineArgumentsParser(int argc, char** argv)
{
    InternalParser = argh::parser(argc, argv);
}

std::string CommandLineArgumentsParser::GetConfigFilePath() const
{
    std::string valueToBeReturned;
    InternalParser({ "cf", "config-file" }, "./data/configuration.json") >> valueToBeReturned;
    return valueToBeReturned;
}
