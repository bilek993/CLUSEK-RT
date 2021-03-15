//
// Created by jbili on 15.03.2021.
//

#ifndef CLUSEK_RT_TEXT_H
#define CLUSEK_RT_TEXT_H

#include <string>
#include <unordered_map>

class Text final
{
public:
    static void Initialize();
    static std::string Get();

private:
    static std::unordered_map<std::string, std::string> TranslatedStrings;
};


#endif //CLUSEK_RT_TEXT_H
