# Sources that do not yet compile for PC, with the reason for each.

set(MELEE_PC_EXCLUDED
  # these read the PowerPC exception context ---
  src/melee/db/dberror.c                # OSContext.fpscr/gpr/srr0
  src/sysdolphin/baselib/debugconsole_main.c  # OSContext.cr/ctr/gpr

  # declaration/definition mismatches in the decomp
  # mwcc is laxer about these than clang
  src/melee/ft/chara/ftKirby/ftkirbyspecialsamus.c  # ftKb_SpecialNSs_800FCC14
  src/melee/mn/mnvibration.c            # HSD_GObj_804D783C declared 'long' vs s32

  # functions with a return type and without a return statement
  src/melee/mp/mpcoll.c                 # mpColl_80046F78
  src/melee/mp/mplib.c                  # mpLib_DrawMatchingLines
  src/melee/mn/mnsnap.c                 # mnSnap_8025441C

  # Layout-dependent data, replaced by melee_compat
  # .bss objects that the card code treats as one contiguous block,
  # addressing across the symbol boundaries by absolute offset. Redefined
  # adjacently in card_work.c
  src/sysdolphin/baselib/hsd_4D11.c
  # THP video decode
  src/melee/lb/lbmthp.c
  # --- Misc ---
)
