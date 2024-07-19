#pragma once

#include <cstdio>
#include "Constants.hpp"

#define ERROR_PRINT(...) fprintf(stderr, RED "[ERROR] " __VA_ARGS__ NONE "\n")
#define SUCCESS_PRINT(_STR) (printf(LIGHT_GREEN "[SUCCESS]" _STR "\n" NONE))
#define WARN_PRINT(_STR) (printf(YELLOW _STR "\n" NONE))
#define INFO_PRINT(_STR) (printf(LIGHT_GRAY _STR "\n" NONE))
