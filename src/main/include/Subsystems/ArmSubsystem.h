#pragma once


#include <COMETS3357/Subsystems/Subsystem.h>
#include <COMETS3357/Subsystems/SparkMax/PositionSparkMax.h>



struct ArmData
{
    
};

enum ArmState
{
    ARM_HOME,
    ARM_MID
};

class ArmSubsystem : public COMETS3357::Subsystem<ArmState, ArmData>
{
public:

    ArmSubsystem()
    {
        Register("ArmSubsystem");
    }


    int k = 100;

  

};