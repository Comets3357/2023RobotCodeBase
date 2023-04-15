// Copyright (c) FIRST and other WPILib contributors.
// Open Source Software; you can modify and/or share it under the terms of
// the WPILib BSD license file in the root directory of this project.

#pragma once

#include <frc2/command/CommandPtr.h>
#include <frc2/command/button/CommandXboxController.h>
#include <frc2/command/button/Trigger.h>

#include "Constants.h"
#include "Lib/PositionSparkMaxTrapCommand.h"

#include <frc/controller/ProfiledPIDController.h>
#include <frc/trajectory/TrapezoidProfile.h>
#include <frc/controller/ArmFeedforward.h>
#include <frc2/command/ProfiledPIDCommand.h>
#include <frc/trajectory/TrajectoryUtil.h>
#include <units/acceleration.h>
#include <units/length.h>
#include <units/time.h>
#include <units/velocity.h>
#include <units/voltage.h>
#include <units/angle.h>
#include <math.h>

#include "subsystems/ElbowSubsystem.h"
#include "Lib/RunRollerSparkMaxCommand.h"
#include "Lib/StopRollerSparkMaxCommand.h"
#include "Lib/RunWheelSparkMaxCommand.h"
#include "Lib/StopWheelSparkMaxCommand.h"
#include "Lib/DrivebaseTrajectoryCommand.h"
#include "lib/SwerveSubsystem.h"
#include "lib/SwerveTrajectoryCommand.h"

#include "RobotData.h"



/**
 * This class is where the bulk of the robot should be declared.  Since
 * Command-based is a "declarative" paradigm, very little robot logic should
 * actually be handled in the {@link Robot} periodic methods (other than the
 * scheduler calls).  Instead, the structure of the robot (including subsystems,
 * commands, and trigger mappings) should be declared here.
 */
class RobotContainer {
 public:
  RobotContainer();

  void Periodic();

  //frc2::CommandPtr GetAutonomousCommand();

  // Replace with CommandPS4Controller or CommandJoystick if needed
  
  RobotData robotData{};

  //Subsystems

  BullBarRollerSubsystem bullBarRollerSubsystem{&robotData.bullBarRollersData};
  BullBarExtensionSubsystem bullBarExtensionSubsystem{&robotData.bullBarExtensionData};
  ElbowSubsystem elbowSubsystem{&robotData.elbowData};
  WristSubsystem wristSubsystem{&robotData.wristData};
  EndEffectorRollersSubsystem endEffectorRollersSubsystem{&robotData.endEffectorRollersData};
  SwerveSubsystem drivebaseSubsystem{"swerve", &robotData.timerData};
  TimerSubsystem timerSubsystem{&robotData.timerData};

  // Commands


  //RunRollerSparkMaxCommand runCommand{ &bullBarRollerSubsystem, 1, &bullBarRollerSubsystem.motor};
  //StopRollerSparkMaxCommand stopCommand{ &bullBarRollerSubsystem, &bullBarRollerSubsystem.motor};

  RunWheelSparkMaxCommand runCommand{&endEffectorRollersSubsystem, 100, &endEffectorRollersSubsystem.motor2};
  StopWheelSparkMaxCommand stopCommand{&endEffectorRollersSubsystem, &endEffectorRollersSubsystem.motor2};
  SwerveTrajectoryCommand pathCommand{frc::TrajectoryUtil::FromPathweaverJson(frc::filesystem::GetDeployDirectory() + "\\pathPlanner\\generatedJSON\\New Path.wpilib.json"), &drivebaseSubsystem};





  frc2::CommandXboxController exampleCommandController{1}; // Creates a CommandXboxController on port 1


  void ConfigureBindings();
};
