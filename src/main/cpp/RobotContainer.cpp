// Copyright (c) FIRST and other WPILib contributors.
// Open Source Software; you can modify and/or share it under the terms of
// the WPILib BSD license file in the root directory of this project.

#include "RobotContainer.h"
#include <frc2/command/RunCommand.h>
#include <frc2/command/button/Trigger.h>





RobotContainer::RobotContainer() {
  // Initialize all of your commands and subsystems here
  // Configure the button bindings
  ConfigureBindings();
  timer.Start();

}

void RobotContainer::ConfigureBindings() {
  // Configure your trigger bindings here

  // Schedule `ExampleCommand` when `exampleCondition` changes to `true`
  //  swerve.SetDefaultCommand(frc2::RunCommand(
  //     [this] {
  //       swerve.Drive(
  //           -units::meters_per_second_t{frc::ApplyDeadband(
  //               exampleCommandController.GetLeftY(), 0.05)},
  //           -units::meters_per_second_t{frc::ApplyDeadband(
  //               exampleCommandController.GetLeftX(), 0.05)},
  //           -units::radians_per_second_t{frc::ApplyDeadband(
  //               exampleCommandController.GetRightX(), 0.05)},
  //           true, true);
  //     },
  //     {&swerve}));




  //exampleCommandController.B().WhileTrue(&stopCommand);

  // Schedule `ExampleMethodCommand` when the Xbox controller's B button is
  // pressed, cancelling on release.
 // m_driverController.B().WhileTrue(m_subsystem.ExampleMethodCommand());
}


void RobotContainer::Periodic()
{
  time = timer.Get();

  deltaTime = time - lastTime;
  frc::SmartDashboard::PutNumber("TicksPerSecond", 1.0/(double)deltaTime);

  lastTime = time;
}

// frc2::CommandPtr RobotContainer::GetAutonomousCommand() {
//   // An example command will be run in autonomous
//   return autos::ExampleAuto(&m_subsystem);
// }
