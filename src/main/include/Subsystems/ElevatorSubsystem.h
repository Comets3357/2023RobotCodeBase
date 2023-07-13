#pragma once


#include <COMETS3357/Subsystems/Subsystem.h>
#include <COMETS3357/Subsystems/SparkMax/PositionSparkMax.h>


struct ElevatorData
{

};

enum ElevatorState
{

};

class ElevatorSubsystem : public COMETS3357::Subsystem<ElevatorState, ElevatorData>
{
public:

    COMETS3357::PositionSparkMax elevator{"Elevator"};

};