//
// Created by jbili on 15.03.2021.
//

#ifndef CLUSEK_RT_TEXT_H
#define CLUSEK_RT_TEXT_H

#include <string>
#include <vector>
#include <unordered_map>

#include "Language.h"

class Text final
{
public:
    static void Initialize(const std::vector<std::pair<Language, std::string>>& languagesWithPaths);
    static void Free();

    static void SetLanguage(Language language);

    static std::string Get(const std::string& id);

private:
    inline static bool Initialized = false;
    inline static Language CurrentLanguage;

    static std::unordered_map<std::string, std::string> TranslatedStrings;

    static void LoadFileIntoMap(Language language, const std::string& path);

    static std::string GenerateKey(Language language, const std::string& id);
};


#endif //CLUSEK_RT_TEXT_H
