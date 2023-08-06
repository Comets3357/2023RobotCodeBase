#pragma once

#include "COMETS3357/Subsystems/Subsystem.h"
#include "COMETS3357/Subsystems/SparkMax/PositionSparkMax.h"
#include "COMETS3357/Subsystems/SparkMax/RollerSparkMax.h"
#include "COMETS3357/Subsystems/SparkMax/WheelSparkMax.h"

enum ExampleSubsystemState
{

};

class ExampleSubsystem : public COMETS3357::Subsystem<ExampleSubsystemState>
{
public:

    ExampleSubsystem();

    void Initialize() override;

    void Periodic() override;

private:

    COMETS3357::PositionSparkMax positionSparkMax{"ExamplePositionMotor"};
    COMETS3357::WheelSparkMax wheelSparkMax{"ExampleWheelMotor"};
    COMETS3357::RollerSparkMax rollerSparkMax{"ExampleRollerMotor"};

};