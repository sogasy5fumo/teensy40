#pragma once
#include <arduino.h>

namespace Action
{
    enum Type
    {
        ATTACKER,

        COUNT
    };
}
namespace ATTACKER{
    enum Mode{
        YELLOW_GOAL,
        BLUE_GOAL,

        COUNT
    };
}