// hexic_hd - ReXGlue Recompiled Project

#include "generated/default/hexic_hd_init.h"

#include "hexic_hd_app.h"

REXCVAR_DEFINE_INT32(hexic_controls_version, 0, "Hexic",
                     "Keyboard defaults already applied to this config (0 = none yet)");

REX_DEFINE_APP(hexic_hd, HexicHdApp::Create)
