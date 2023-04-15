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

struct PositionMotorConfig {
    int ID;
    bool invertedAbsolute;
    bool invertedRelative;
    double currentLimit;
    double relativeConversionFactor;
    double absoluteConversionFactor;
    double absoluteZeroOffset;
    double maxSpeed;
    double minSpeed;
    rev::CANSparkMax::IdleMode idleMode;

    PID velocityPID;
    PID positionPID;
};

struct WheelMotorConfig {
    bool invertedRelative;
    double currentLimit;
    double relativeConversionFactor;
    rev::CANSparkMax::IdleMode idleMode;

    PID velocityPID;
};

struct RollerMotorConfig {
    bool invertedRelative;
    double currentLimit;
    rev::CANSparkMax::IdleMode idleMode;
};

struct SwerveModuleConfig
{
    int azimuthID;
    int driveID;
    double absoluteZeroOffset;
    double absoluteConversionFactor;
    double relativeConversionFactor;
    bool relativeInverted;
    bool absoluteInverted;
};

struct SwerveConfig
{
    SwerveModuleConfig frontLeftModule{};
    SwerveModuleConfig frontRightModule{};
    SwerveModuleConfig backLeftModule{};
    SwerveModuleConfig backRightModule{};
    units::meter_t trackWidth{10};
    units::meter_t wheelBase{10};
    units::meters_per_second_t xSpeed{5};
    units::meters_per_second_t ySpeed{5};
    units::radians_per_second_t maxTurnSpeed{1};
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

