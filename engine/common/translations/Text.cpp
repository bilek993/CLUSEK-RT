//
// Created by jbili on 15.03.2021.
//

#include "Text.h"

#include <fmt/os.h>
#include <fmt/compile.h>
#include <nlohmann/json.hpp>

#include "../debug/Logger.h"

std::unordered_map<std::string, std::string> Text::TranslatedStrings{};

void Text::Initialize(const std::vector<std::pair<Language, std::string>>& languagesWithPaths)
{
    LOG_DEBUG("Preparing to initialize Text module...");

    for (auto& currentLanguageWithPath : languagesWithPaths)
    {
        const auto& language = currentLanguageWithPath.first;
        const auto& path = currentLanguageWithPath.second;

        try
        {
            LOG_DEBUG(fmt::format(FMT_COMPILE("Preparing to load language '{}' from path '{}'..."), language, path));

            if (path.empty())
                throw std::invalid_argument("Path fo file cannot be empty!");

            LoadFileIntoMap(language, path);

            LOG_DEBUG(fmt::format(FMT_COMPILE("Successfully loaded {} into the memory."), path));
        }
        catch (const std::exception& e)
        {
            LOG_ERROR(e.what());
        }
        catch (...)
        {
            LOG_ERROR(fmt::format(FMT_COMPILE("An unknown exception happened when loading data from '{}'!"), path));
        }
    }

    Initialized = true;
}

void Text::Free()
{
    LOG_DEBUG("Preparing to free Text module...");

    Initialized = false;
}

void Text::SetLanguage(const Language language)
{
    if (!Initialized)
        LOG_ERROR("Text module is not initialized!");

    CurrentLanguage = language;
    LOG_DEBUG(fmt::format(FMT_COMPILE("Language has been set to '{}'."), CurrentLanguage));
}

std::string Text::Get(const std::string& id)
{
    if (!Initialized)
    {
        LOG_ERROR("Text module is not initialized!");
        return std::string();
    }

    const auto key = GenerateKey(CurrentLanguage, id);
    const auto item = TranslatedStrings.find(key);

    return item != TranslatedStrings.end() ? item->second : std::string();
}

void Text::LoadFileIntoMap(const Language language, const std::string& path)
{
    std::ifstream inputFile(path);
    nlohmann::json json;
    inputFile >> json;

    for (auto& item : json.items())
    {
        const auto key = GenerateKey(language, item.key());
        const auto value = item.value();

        TranslatedStrings[key] = value;
    }
}

std::string Text::GenerateKey(const Language language, const std::string& id)
{
    return fmt::format(FMT_COMPILE("{}___{}"), language, id);
}
