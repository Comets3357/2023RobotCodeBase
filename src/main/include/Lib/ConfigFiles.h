#pragma once


#include <iostream>
#include <fstream>
#include "Json/picojson.h"

#include <string>
#include <vector>
#include <map>
#include <frc/fileSystem.h>
#include "PID.h"

#include <rev/CANSparkMax.h>
#include <units/velocity.h>
#include <units/angular_velocity.h>
#include "Lib/PositionSparkMaxRunMode.h"

struct PositionMotorConfig {
    int ID;
    PositionSparkMaxRunMode defaultMode;
    bool invertedAbsolute;
    bool invertedRelative;
    double currentLimit;
    double relativePositionConversionFactor;
    double relativeVelocityConversionFactor;
    double absolutePositionConversionFactor;
    double absoluteVelocityConversionFactor;
    double absoluteZeroOffset;
    double maxSpeed;
    double minSpeed;
    rev::CANSparkMax::IdleMode idleMode;

    bool positionPIDWrappingEnabled;
    double turningEncoderPositionPIDMinInput;
    double turningEncoderPositionPIDMaxInput;

    PID velocityPID;
    PID positionPID;
};

struct WheelMotorConfig {
    int ID;
    bool invertedRelative;
    double currentLimit;
    double relativeConversionFactor;
    rev::CANSparkMax::IdleMode idleMode;

    PID velocityPID;
};

struct RollerMotorConfig {
    int ID;
    bool invertedRelative;
    double currentLimit;
    rev::CANSparkMax::IdleMode idleMode;
};

struct SwerveModuleConfig
{
    std::string azimuthConfigName;
    std::string driveConfigName;
    double angularOffset;
};

struct SwerveConfig
{
    SwerveModuleConfig frontLeftModule{};
    SwerveModuleConfig frontRightModule{};
    SwerveModuleConfig backLeftModule{};
    SwerveModuleConfig backRightModule{};
    units::meter_t trackWidth{10};
    units::meter_t wheelBase{10};
    units::radians_per_second_t maxTurnSpeed{1};
    double directionSlewRate;
    units::meters_per_second_t maxSpeed{15};
    double magnitudeSlewRate;
    double rotationalSlewRate;
};

struct DrivebaseConfig
{
    
};

struct RobotConfig {
    std::map<std::string, PositionMotorConfig> positionMotorConfigs;
    std::map<std::string, WheelMotorConfig> wheelMotorConfigs;
    std::map<std::string, RollerMotorConfig> rollerMotorConfigs;
    std::map<std::string, SwerveConfig> swerveConfigs;
    std::map<std::string, SwerveModuleConfig> swerveModuleConfigs;
};


class ConfigFiles
{
public:

    static ConfigFiles& getInstance()
    {
        static ConfigFiles instance;
        return instance;
    }

    void LoadConfigFiles(std::string fileName);

    RobotConfig robotConfig;

    private:

    ConfigFiles() {} // Private constructor to prevent instantiation outside of class
    ConfigFiles(const ConfigFiles&) = delete; // Disable copy constructor
    ConfigFiles& operator=(const ConfigFiles&) = delete; // Disable copy assignment operator
    ConfigFiles(ConfigFiles&&) = delete; // Disable move constructor
    ConfigFiles& operator=(ConfigFiles&&) = delete; // Disable move assignment operator
};

