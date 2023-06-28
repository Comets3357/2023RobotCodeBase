#pragma once

#include "COMETS3357/GyroSubsystem.h"
#include "COMETS3357/TimerSubsystem.h"


class RobotData
{
public:

    COMETS3357::GyroData gyroData{};
    COMETS3357::TimerData timerData{};
};