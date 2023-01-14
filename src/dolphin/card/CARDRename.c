#include <cstring.h>
#include <dolphin/card.h>
#include <dolphin/card/CARDBios.h>
#include <dolphin/card/CARDDir.h>
#include <dolphin/card/CARDOpen.h>
#include <dolphin/os/OSTime.h>
#include <string.h>

#ifdef DOLPHIN_SMB
extern const DVDDiskID* __CARDDiskID;
#endif

s32 CARDRenameAsync(s32 chan, const char* old, const char* new,
                    CARDCallback callback)
{
    CARDControl* card;
    CARDDir* dir;
    CARDDir* ent;
    s32 result;
    int fileNo;
    int newNo;
    int oldNo;

    if (*old == 0xff || *new == 0xff || *old == 0x00 || *new == 0x00) {
        return CARD_RESULT_FATAL_ERROR;
    }
    if (CARD_FILENAME_MAX < (u32) strlen(old) ||
        CARD_FILENAME_MAX < (u32) strlen(new))
    {
        return CARD_RESULT_NAMETOOLONG;
    }
    result = __CARDGetControlBlock(chan, &card);
    if (result < 0) {
        return result;
    }

    newNo = oldNo = -1;
    dir = __CARDGetDirBlock(card);
    for (fileNo = 0; fileNo < CARD_MAX_FILE; fileNo++) {
        ent = &dir[fileNo];
        if (ent->gameName[0] == 0xff) {
            continue;
        }

#ifdef DOLPHIN_SMB
        if (memcmp(ent->gameName, __CARDDiskID->gameName,
                   sizeof(ent->gameName)) != 0 ||
            memcmp(ent->company, __CARDDiskID->company, sizeof(ent->company)) !=
                0)
#else
        if (memcmp(ent->gameName, card->diskID->gameName,
                   sizeof(ent->gameName)) != 0 ||
            memcmp(ent->company, card->diskID->company, sizeof(ent->company)) !=
                0)
#endif
        {
            continue;
        }

        if (__CARDCompareFileName(ent, old)) {
            oldNo = fileNo;
        }
        if (__CARDCompareFileName(ent, new)) {
            newNo = fileNo;
        }
    }

    if (oldNo == -1) {
        return __CARDPutControlBlock(card, CARD_RESULT_NOFILE);
    }
    if (newNo != -1) {
        return __CARDPutControlBlock(card, CARD_RESULT_EXIST);
    }

    ent = &dir[oldNo];
#ifdef DOLPHIN_SMB
    result = __CARDAccess(ent);
#else
    result = __CARDAccess(card, ent);
#endif
    if (result < 0) {
        return __CARDPutControlBlock(card, result);
    }

    strncpy((char*) ent->fileName, new, CARD_FILENAME_MAX);

    ent->time = OSTicksToSeconds(OSGetTime());
    result = __CARDUpdateDir(chan, callback);
    if (result < 0) {
        __CARDPutControlBlock(card, result);
    }
    return result;
}

int CARDRename(s32 chan, const char* old, const char* new, u32 offset)
{
    /// @todo Eliminate cast to #CARDCallback.
    int result =
        CARDRenameAsync(chan, old, new, (CARDCallback) __CARDSyncCallback);

    if (result < 0)
        return result;

    return __CARDSync(chan);
}
