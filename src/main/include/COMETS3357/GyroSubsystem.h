#pragma once

#include <frc/ADXRS450_Gyro.h>
#include <frc/SerialPort.h>
#include <frc2/command/SubsystemBase.h>
#include <frc/geometry/Rotation2d.h>
#include <frc/SPI.h>
#include <COMETS3357/Subsystems/Subsystem.h>
#include "AHRS.h"

namespace COMETS3357
{
    struct GyroData
    {
        double angle = 0;
        double angleRate = 0;
    };

    enum GyroState
    {
        GYRO_RUNNING
    };

    class GyroSubsystem : public COMETS3357::Subsystem<GyroState, GyroData>
    {

    public:

        GyroSubsystem();
        void Periodic() override;

    private:
        AHRS m_navx;

    };
};