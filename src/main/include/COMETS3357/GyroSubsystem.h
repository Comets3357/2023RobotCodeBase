#pragma once

#include <frc/ADXRS450_Gyro.h>
#include <frc/SerialPort.h>
#include <frc2/command/SubsystemBase.h>
#include <frc/geometry/Rotation2d.h>
#include <frc/SPI.h>

struct GyroData
{
    double angle = 0;
    double angleRate = 0;
};

class GyroSubsystem : public frc2::SubsystemBase
{

public:
    GyroSubsystem(GyroData& data);
    void Periodic() override;

private:
    frc::ADXRS450_Gyro m_navx;


    GyroData& gyroData;

};