//
// Created by jbili on 15.03.2021.
//

#include "Text.h"

#include <fmt/os.h>
#include <fmt/compile.h>

#include "../debug/Logger.h"

void Text::Initialize(const std::vector<std::pair<std::string, std::string>>& languagesWithPaths)
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
            LOG_WARNING(fmt::format(FMT_COMPILE("Loading data from '{}' failed!"), path));
            LOG_WARNING(e.what());
        }
        catch (...)
        {
            LOG_WARNING(fmt::format(FMT_COMPILE("An unknown exception happened when loading data from '{}'!"), path));
        }
    }

    Initialized = true;
}

void Text::Free()
{
    LOG_DEBUG("Preparing to free Text module...");

    Initialized = false;
}

void Text::SetLanguage(const std::string& language)
{
    if (!Initialized)
        LOG_ERROR("Text module is not initialized!");

    Language = language;
    LOG_DEBUG(fmt::format(FMT_COMPILE("Language has been set to '{}'."), Language));
}

std::string Text::Get()
{
    if (!Initialized)
    {
        LOG_ERROR("Text module is not initialized!");
        return std::string();
    }

    return std::string(); // TODO: Change this
}

void Text::LoadFileIntoMap(const std::string& language, const std::string& path)
{

}
