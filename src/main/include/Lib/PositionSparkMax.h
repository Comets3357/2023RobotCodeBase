#pragma once

#include <rev/CANSparkMax.h>

#include <frc/controller/ProfiledPIDController.h>
#include <frc/trajectory/TrapezoidProfile.h>
#include <frc/controller/ArmFeedforward.h>
#include <frc2/command/ProfiledPIDCommand.h>
#include <units/acceleration.h>
#include <units/length.h>
#include <units/time.h>
#include <units/velocity.h>
#include <units/voltage.h>
#include <units/angle.h>
#include <math.h>
#include <thread>
#include "PID.h"
#include "Lib/ConfigFiles.h"
#include "Lib/PositionSparkMaxRunMode.h"


class PositionSparkMax
{
public:

    PositionMotorConfig config;

    PositionSparkMax(std::string configName);
    void RobotInit();
    void ZeroRelativeEncoder();
    void ChangeFeedBackDevice(PositionSparkMaxRunMode mode);
    void SetVelocityPID(PID pid);
    void SetPositionPID(PID pid);

    void SetPIDOutputRange(double min, double max, int slot);

    double GetPosition();
    double GetRelativePosition();
    double GetAbsolutePosition();

    double GetRelativeVelocity();
    double GetAbsoluteVelocity();

    void SetVelocity(double velocity);

    void SetPosition(double position);


    void Periodic();

    void changeRunMode(PositionSparkMaxRunMode mode);

    

    double absoluteEncoderPosition = 0;
    double relativeEncoderPosition = 0;

    PID positionPID{};
    PID velocityPID{};

    rev::CANSparkMax motor;

private:

    PositionSparkMaxRunMode runMode = POSITION_SPARK_MAX_NONE;
    PositionSparkMaxRunMode runModeRequest = runMode;
    bool requestRunMode = false;
    PositionSparkMaxRunMode defaultRunMode = POSITION_SPARK_MAX_ABSOLUTE;
    rev::SparkMaxPIDController PIDController;
    rev::SparkMaxRelativeEncoder relativeEncoder;
    rev::SparkMaxAbsoluteEncoder absoluteEncoder;

    int absAttempts = 0;
    double lastPosition;

    void CheckAbsoluteEncoder();

};