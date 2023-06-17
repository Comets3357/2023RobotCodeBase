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

    /**
     * Creates a new PositionSparkMax that has the capability of running a motor
     * to a specific position using either relative or absolute encoders.
     *
     * @param configName The name of the config linked to this specific motor
     */
    PositionSparkMax(std::string configName);

    /**
     * The initialization of the PositionSparkMax
     */
    void RobotInit();

    /**
     * Zeros the relative encoder positions
     */
    void ZeroRelativeEncoder();

    /**
     * Changes the PID feedback device
     *
     * @param mode The runmode that cooresponds with the FeedbackDevice
     */
    void ChangeFeedBackDevice(PositionSparkMaxRunMode mode);

    /**
     * Changes the current velocity PID to a new velocity PID that is specified
     *
     * @param pid The velocity PID
     */
    void SetVelocityPID(PID pid);

    /**
     * Changes the current position PID to a new position PID that is specified
     *
     * @param pid The position PID
     */
    void SetPositionPID(PID pid);

    /**
     * Sets the PID min speed and max speed with a specified PID slot
     *
     * @param min The Minimum percent output that the PID is allowed to run at
     * @param max The Maximum percent output that the PID is allowed to tun at
     * @param slot The slot of the PID that needs to be changed
     */
    void SetPIDOutputRange(double min, double max, int slot);

    /**
     * Gets the position of the current encoder depending on the current feedback device
     *
     * @return The current position depending on the current feedback device
     */
    double GetPosition();

    /**
     * Gets the current encoder position of the Relative Encoder
     *
     * @return The current encoder position of the Relative Encoder
     */
    double GetRelativePosition();

    /**
     * Gets the current encoder position of rthe Absolute Encoder
     *
     * @return The current encoder position for the Absolute Encoder
     */
    double GetAbsolutePosition();

    /**
     * Gets the current velocity for the Relative Encoder
     *
     * @return The current velocity of the Relative Encoder
     */
    double GetRelativeVelocity();

    /**
     * Gets the current velocity for the Absolute Encoder
     *
     * @return The current velocity of the Absolute Encoder
     */
    double GetAbsoluteVelocity();

    /**
     * Sets a new target velocity for the motor using the Velocity PID
     *
     * @param velocity The new target velocity
     */
    void SetVelocity(double velocity);

    /**
     * Wraps an angle until it lies within the range from 0 to 2*PI (exclusive).
     *
     * @param velocity The new target velocity for the motor using PIDs
     */
    void SetPosition(double position);

    /**
     * Runs ever loop
     */
    void Periodic();

    /**
     * Changes the current runmode (running on Absolute or Relative encoder)
     *
     * @param mode The runmode to change to
     */
    void changeRunMode(PositionSparkMaxRunMode mode);

    /**
     * Checks to make sure that the Absolute Encoder is plugged in 
     */
    void CheckAbsoluteEncoder();

    rev::CANSparkMax motor;
    PID positionPID{};
    PID velocityPID{};

private:

    double absoluteEncoderPosition = 0;
    double relativeEncoderPosition = 0;
    PositionSparkMaxRunMode runMode = POSITION_SPARK_MAX_NONE;
    PositionSparkMaxRunMode runModeRequest = runMode;
    bool requestRunMode = false;
    PositionSparkMaxRunMode defaultRunMode = POSITION_SPARK_MAX_ABSOLUTE;
    rev::SparkMaxPIDController PIDController;
    rev::SparkMaxRelativeEncoder relativeEncoder;
    rev::SparkMaxAbsoluteEncoder absoluteEncoder;
    int absAttempts = 0;
    double lastPosition;

    

};