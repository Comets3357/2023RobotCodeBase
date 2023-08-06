#include "COMETS3357/Subsystems/SparkMax/RollerSparkMax.h"
#include <COMETS3357/Subsystems/SubsystemManager.h>

using namespace COMETS3357;

RollerSparkMax::RollerSparkMax(std::string configName) : config{ConfigFiles::getInstance().GetConfigFiles().rollerMotorConfigs[configName]}, motor{config.ID, rev::CANSparkMax::MotorType::kBrushless}
{
    config.motor = &motor;
    COMETS3357::SubsystemManager::GetInstance().AddInit([this]{RobotInit();});
}

void RollerSparkMax::SetPower(double power)
{
    motor.Set(power);
}

void RollerSparkMax::RobotInit()
{

    if (
        motor.GetInverted() != config.invertedRelative || 
        motor.GetIdleMode() != config.idleMode
    )
    {
        motor.RestoreFactoryDefaults();
        motor.SetInverted(config.invertedRelative);
        motor.SetSmartCurrentLimit(config.currentLimit);
        motor.SetIdleMode(config.idleMode);

        if (config.follow != "NONE")
        {
            motor.Follow(*COMETS3357::ConfigFiles::getInstance().GetConfigFiles().positionMotorConfigs[config.follow].motor);
        }

        motor.BurnFlash();
    }
}