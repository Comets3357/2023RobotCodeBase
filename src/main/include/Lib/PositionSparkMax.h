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

enum PositionSparkMaxRunMode
{
    POSITION_SPARK_MAX_RELATIVE,
    POSITION_SPARK_MAX_ABSOLUTE,
    POSITION_SPARK_MAX_NONE
};

class PositionSparkMax
{
public:

    

    PositionSparkMax(const int ID, PositionSparkMaxRunMode mode)
     : motor{ID, rev::CANSparkMax::MotorType::kBrushless},
        PIDController{motor.GetPIDController()},
        relativeEncoder{motor.GetEncoder()},
        absoluteEncoder{motor.GetAbsoluteEncoder(rev::SparkMaxAbsoluteEncoder::Type::kDutyCycle)}
    {
        defaultRunMode = mode;
        runMode = defaultRunMode;

        ChangeFeedBackDevice(defaultRunMode);

        if (runMode == POSITION_SPARK_MAX_ABSOLUTE)
        {
            absoluteEncoderTask = std::make_unique<std::thread>(&PositionSparkMax::CheckAbsoluteEncoder, this);
        }
    };

    void SetConfig(std::string name)
    {
        PositionMotorConfig config = ConfigFiles::getInstance().robot_config.positionMotorConfigs[name];

        if (
            motor.GetInverted() != config.invertedRelative || 
            motor.GetIdleMode() != config.idleMode || 
            PIDController.GetOutputMin(1) != config.minSpeed ||
            PIDController.GetOutputMax(1) != config.maxSpeed ||
            relativeEncoder.GetPositionConversionFactor() != config.relativeConversionFactor;
            absoluteEncoder.GetInverted() != config.invertedAbsolute ||
            absoluteEncoder.GetPositionConversionFactor() != config.absoluteConversionFactor ||
            absoluteEncoder.GetZeroOffset() != config.absoluteZeroOffset
        )
        {
            motor.RestoreFactoryDefaults();
            motor.SetInverted(config.invertedRelative);
            motor.SetSmartCurrentLimit(config.currentLimit);
            motor.SetIdleMode(config.idleMode);
            PIDController.SetOutputRange(config.minSpeed, config.maxSpeed, 1);
            SetVelocityPID(config.velocityPID);
            SetPositionPID(config.positionPID);
            relativeEncoder.SetPositionConversionFactor(config.relativeConversionFactor);
            absoluteEncoder.SetInverted(config.invertedAbsolute);
            absoluteEncoder.SetPositionConversionFactor(config.absoluteConversionFactor);
            absoluteEncoder.SetZeroOffset(config.absoluteZeroOffset);
            motor.BurnFlash();
        }
    }

    void ZeroRelativeEncoder()
    {
        relativeEncoder.SetPosition(absoluteEncoderPosition);
    }

    void ChangeFeedBackDevice(PositionSparkMaxRunMode mode)
    {
        switch (mode)
        {
        case POSITION_SPARK_MAX_ABSOLUTE:
            PIDController.SetFeedbackDevice(absoluteEncoder);
            break;
        case POSITION_SPARK_MAX_RELATIVE:
            PIDController.SetFeedbackDevice(relativeEncoder);
            break;
        default:
            break;
        }
    }

    void SetVelocityPID(PID pid)
    {
        PIDController.SetP(pid.P, 0);
        PIDController.SetI(pid.I, 0);
        PIDController.SetD(pid.D, 0);
        PIDController.SetFF(pid.FF, 0);

        velocityPID = pid;
    }

    void SetPositionPID(PID pid)
    {
        PIDController.SetP(pid.P, 1);
        PIDController.SetI(pid.I, 1);
        PIDController.SetD(pid.D, 1);
        PIDController.SetFF(pid.FF, 1);

        positionPID = pid;
    }


    void SetPIDOutputRange(double min, double max, int slot)
    {
        PIDController.SetOutputRange(min, max, slot);
    }

    double GetPosition()
    {
        switch (runMode)
        {
        case POSITION_SPARK_MAX_ABSOLUTE:
            return absoluteEncoderPosition;
            break;
        case POSITION_SPARK_MAX_RELATIVE:
            return relativeEncoderPosition;
            break;
        default:
            return 0;
            break;
        }
    }

    void SetVelocity(double velocity)
    {
        PIDController.SetReference(velocity, rev::CANSparkMax::ControlType::kVelocity, 0);
    }

    void SetPosition(double position)
    {
        PIDController.SetReference(position, rev::CANSparkMax::ControlType::kPosition, 1);
    }


    void Periodic()
    {
        absoluteEncoderPosition = absoluteEncoder.GetPosition();
        relativeEncoderPosition = absoluteEncoder.GetPosition();
    }

    void changeRunMode(PositionSparkMaxRunMode mode)
    {
        runMode = mode;
        ChangeFeedBackDevice(runMode);
    }

    

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

    std::unique_ptr<std::thread> absoluteEncoderTask;

    int absAttempts = 0;
    double lastPosition;

    void CheckAbsoluteEncoder()
    {
        while (true) {
            if (runMode != POSITION_SPARK_MAX_ABSOLUTE) {
                return;
            }


            if (lastPosition != absoluteEncoderPosition)
            {
                absAttempts++;
            }
            else
            {
                absAttempts = 0;
            }
            lastPosition = absoluteEncoderPosition;

            if (absAttempts > 20)
            {
                changeRunMode(POSITION_SPARK_MAX_RELATIVE);
            }
        }
    }

};