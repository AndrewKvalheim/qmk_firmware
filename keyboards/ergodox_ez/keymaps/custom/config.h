#ifndef CONFIG_USER_H
#define CONFIG_USER_H
#include "../../config.h"

// Favor fast tapping over fast modifying.
#undef PERMISSIVE_HOLD

// Hold the modifier, not tapped key when pressed in quick succession.
#define TAPPING_FORCE_HOLD

// Transition from tapping to modifying sooner.
#undef TAPPING_TERM
#define TAPPING_TERM 150

#endif
