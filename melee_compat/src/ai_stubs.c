// AI (audio interface)

#include "compat_report.h"

#include <dolphin/ai.h>

void AIInit(u8* stack) { COMPAT_STUB(); (void) stack; }
void AISetDSPSampleRate(u32 rate) { (void) rate; }
void AISetStreamVolLeft(u8 vol) { (void) vol; }
void AISetStreamVolRight(u8 vol) { (void) vol; }
