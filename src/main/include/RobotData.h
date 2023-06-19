#pragma once

#include "subsystems/BullBarExtensionSubsystem.h"
#include "subsystems/BullBarRollerSubsystem.h"
#include "subsystems/ElbowSubsystem.h"
#include "subsystems/EndEffectorRollersSubsystem.h"
#include "subsystems/WristSubsystem.h"
#include "Lib/DrivebaseSubsystem.h"
#include "Lib/TimerSubsystem.h"


class RobotData
{
public:
    BullBarExtensionData bullBarExtensionData{};
    BullBarRollersData bullBarRollersData{};
    ElbowData elbowData{};
    EndEffectorRollersData endEffectorRollersData{};
    WristData wristData{};
    DrivebaseData drivebaseData{};

    TimerData timerData{};
};