// Copyright (c) FIRST and other WPILib contributors.
// Open Source Software; you can modify and/or share it under the terms of
// the WPILib BSD license file in the root directory of this project.

#pragma once

#include <frc2/command/CommandPtr.h>
#include <frc2/command/button/CommandXboxController.h>
#include <frc2/command/button/Trigger.h>

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

#include "COMETS3357/Subsystems/Chassis/SwerveSubsystem.h"
#include "COMETS3357/Auton/Autons.h"
#include "COMETS3357/Configs/ControllerMap.h"

#include "RobotData.h"

#include "commands/test.h"



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

  RobotData robotData{};


  //Subsystems
  COMETS3357::GyroSubsystem gyro{robotData.gyroData};
  COMETS3357::SwerveSubsystem swerve{"Swerve", robotData.gyroData};







  std::unordered_map<std::string, std::shared_ptr<frc2::Command>> actionMap 
  {
    {"Test", std::make_shared<Test>()}
    // {"asdc", std::make_shared<StopRollerSparkMaxCommand>()}
  };

  COMETS3357::ControllerMap controllerMap{actionMap, "CompControllerMap"};
  COMETS3357::Autons autos{&swerve, actionMap};

  //frc2::CommandXboxController exampleCommandController{0};
 


  void ConfigureBindings();

  frc::Timer timer{};
  units::second_t time = 0_s;
  units::second_t lastTime = 0_s;
  units::second_t deltaTime = 0_s;
};
