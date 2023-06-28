// Copyright (c) FIRST and other WPILib contributors.
// Open Source Software; you can modify and/or share it under the terms of
// the WPILib BSD license file in the root directory of this project.

#pragma once

#include <frc2/command/CommandPtr.h>
#include <frc2/command/SubsystemBase.h>
#include <rev/CANSparkMax.h>
#include "COMETS3357/Subsystems/SparkMax/RollerSparkMax.h"

#include "Constants.h"

struct BullBarRollersData
{

};

class BullBarRollerSubsystem : public frc2::SubsystemBase {
 public:
  BullBarRollerSubsystem(BullBarRollersData* data);

  COMETS3357::RollerSparkMax motor{"BullBarRoller"};

};
