// Copyright (c) FIRST and other WPILib contributors.
// Open Source Software; you can modify and/or share it under the terms of
// the WPILib BSD license file in the root directory of this project.

#pragma once

#include <frc2/command/CommandPtr.h>
#include <frc2/command/SubsystemBase.h>
#include <rev/CANSparkMax.h>
#include "Lib/PositionSparkMax.h"

#include "Constants.h"

struct ElbowData
{

};

class ElbowSubsystem : public frc2::SubsystemBase {
 public:
  ElbowSubsystem(ElbowData* data);

  void Periodic() override;

  PositionSparkMax motor{"Elbow"};

};
