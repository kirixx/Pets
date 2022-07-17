#pragma once
#include <string>
namespace StringPractice
{
    enum class Case
    {
        TO_UPPER,
        TO_LOWER,
        SENSITIVE,
        INSENSITIVE
    };

    std::string ConvertToCase(const std::string& src, const Case charCase)
    {
        std::string retVal;
        for (auto& ch : src)
        {
            switch (charCase)
            {
            case Case::TO_LOWER:
                retVal.push_back(tolower(ch));
                break;
            case Case::TO_UPPER:
                retVal.push_back(toupper(ch));
                break;
            default:
                break;
            }

        }
        return retVal;
    }

    size_t Find(const std::string& source,
        const std::string& searchString,
        Case searchCase = Case::INSENSITIVE,
        size_t offset = 0) {
        size_t retVal = std::string::npos;
        if (searchCase == Case::INSENSITIVE)
        {
            std::string convertedSource = ConvertToCase(source, Case::TO_LOWER);
            std::string convertedPattern = ConvertToCase(searchString, Case::TO_LOWER);
            retVal = convertedSource.find(convertedPattern);
        }
        else
        {
            retVal = source.find(searchString, 0);
        }
        return retVal;
    }
}