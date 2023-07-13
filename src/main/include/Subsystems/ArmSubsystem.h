#pragma once


#include <COMETS3357/Subsystems/Subsystem.h>
#include <COMETS3357/Subsystems/SparkMax/PositionSparkMax.h>


struct ArmData
{
    
};

enum ArmState
{

};

class ArmSubsystem : public COMETS3357::Subsystem<ArmState, ArmSubsystem>
{
public:

    bool IsBullBarSafePosition();

    COMETS3357::PositionSparkMax Elbow{"Elbow"};
    COMETS3357::PositionSparkMax Wrist{"Wrist"};

};