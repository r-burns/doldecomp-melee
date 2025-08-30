#include "lb/lblanguage.h"

#include "gm/gmmain_lib.h"
#include "gm/types.h"

enum Language lbLang_GetLanguageSetting(void)
{
    return gmMainLib_804D3EE0->language;
}

enum Language lbLang_SetLanguageSetting(enum Language language)
{
    if (language >= Language_Japanese && language < Language_Max) {
        gmMainLib_804D3EE0->language = language;
    }

    return language;
}

bool lbLang_IsSettingJP(void)
{
    return (gmMainLib_804D3EE0->language) == 0 ? true : false;
}

bool lbLang_IsSettingUS(void)
{
    return (gmMainLib_804D3EE0->language) == 1 ? true : false;
}

enum Language lbLang_GetSavedLanguage(void)
{
    return gmMainLib_8015CC58()->saved_language;
}

void lbLang_SetSavedLanguage(enum Language language)
{
    if ((int) language >= (int) Language_Japanese &&
        (int) language < (int) Language_English)
    {
        gmMainLib_8015CC58()->saved_language = language;
    }
}

bool lbLang_IsSavedLanguageJP(void)
{
    return (gmMainLib_8015CC58()->saved_language == 0) ? true : false;
}

bool lbLang_IsSavedLanguageUS(void)
{
    return (gmMainLib_8015CC58()->saved_language == 1) ? true : false;
}
