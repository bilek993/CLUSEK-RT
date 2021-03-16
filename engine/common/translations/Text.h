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
    static void Initialize(const std::vector<std::pair<std::string, std::string>>& languagesWithPaths);
    static void Free();

    static void SetLanguage(const std::string& language);
    static std::string Get();

private:
    inline static bool Initialized = false;
    inline static std::string Language;

    static std::unordered_map<std::string, std::string> TranslatedStrings;

    static void LoadFileIntoMap(const std::string& language, const std::string& path);
};


#endif //CLUSEK_RT_TEXT_H
