//
// Created by jbili on 27.04.2021.
//

#ifndef CLUSEK_RT_COMMANDLINEARGUMENTSPARSER_H
#define CLUSEK_RT_COMMANDLINEARGUMENTSPARSER_H

#include <argh.h>
#include <string>

class CommandLineArgumentsParser final
{
public:
    CommandLineArgumentsParser(int argc, char* argv[]);
    ~CommandLineArgumentsParser() = default;
    CommandLineArgumentsParser(const CommandLineArgumentsParser& other) = delete;
    CommandLineArgumentsParser(CommandLineArgumentsParser&& other) noexcept = delete;
    CommandLineArgumentsParser& operator=(const CommandLineArgumentsParser& other) = delete;
    CommandLineArgumentsParser& operator=(CommandLineArgumentsParser&& other) noexcept = delete;

    [[nodiscard]] std::string GetConfigFilePath() const;

private:
    argh::parser InternalParser;
};


#endif //CLUSEK_RT_COMMANDLINEARGUMENTSPARSER_H
