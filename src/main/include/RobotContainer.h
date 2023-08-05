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
#include "COMETS3357/TimerSubsystem.h"

#include "commands/test.h"

#include <COMETS3357/Commands/SparkMax/PositionSparkMaxTrapCommand.h>

#include "Subsystems/ArmSubsystem.h"
#include "Subsystems/BullBarSubsystem.h"
#include "Subsystems/ElevatorSubsystem.h"


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


  //Subsystems
  COMETS3357::TimerSubsystem timer{};
  COMETS3357::GyroSubsystem gyro{};
   COMETS3357::SwerveSubsystem swerve{"Swerve", *this};

  ArmSubsystem arm{};
  BullBarSubsystem buyll{};
  ElevatorSubsystem elevator{};
 



frc2::CommandXboxController controller{1};

  std::unordered_map<std::string, std::shared_ptr<frc2::Command>> buttonActionMap 
  {
      {"Test1", std::make_shared<Test>(1)},
      {"Test2", std::make_shared<Test>(2)},
      {"Test3", std::make_shared<Test>(3)}
  };

  std::unordered_map<std::string, std::tuple<std::function<void(double, double, double, double)>, frc2::Subsystem*, COMETS3357::Controller::JoystickCommandMode>> joystickActionMap
  {
    {"Set1", {[this](auto leftX, auto leftY, auto rightX, auto rightY){elevator.SetOutput(leftX, leftY, 0, 0);}, &elevator, COMETS3357::Controller::JoystickCommandMode::JOYSTICK_DEADZONE_COMMAND}},
    {"Set2", {[this](auto leftX, auto leftY, auto rightX, auto rightY){elevator.SetOutput(leftX, leftY, 0, 0);}, &elevator, COMETS3357::Controller::JoystickCommandMode::JOYSTICK_DEADZONE_COMMAND}}
  };

  COMETS3357::ControllerMap controllerMap{buttonActionMap, joystickActionMap, "CompControllerMap", };
 // COMETS3357::Autons autos{&swerve, actionMap};

  void ConfigureBindings();
};
