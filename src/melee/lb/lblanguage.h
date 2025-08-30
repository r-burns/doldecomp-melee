#ifndef _lblanguage_h_
#define _lblanguage_h_

#include <platform.h>

#include "lb/forward.h"

enum Language lbLang_GetLanguageSetting(void);
enum Language lbLang_SetLanguageSetting(enum Language language);
bool lbLang_IsSettingJP(void);
bool lbLang_IsSettingUS(void);
enum Language lbLang_GetSavedLanguage(void);
void lbLang_SetSavedLanguage(enum Language language);
bool lbLang_IsSavedLanguageJP(void);
bool lbLang_IsSavedLanguageUS(void);

#endif
