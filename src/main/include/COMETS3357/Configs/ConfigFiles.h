#pragma once

#include <iostream>
#include <fstream>
#include "Json/picojson.h"
#include <string>
#include <vector>
#include <map>
#include <frc/fileSystem.h>
#include "COMETS3357/PID.h"
#include <rev/CANSparkMax.h>
#include <units/velocity.h>
#include <units/angular_velocity.h>
#include "COMETS3357/PositionSparkMaxRunMode.h"
#include <unordered_map>

struct PositionMotorConfig {
    int ID = 1;
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
    int ID = 100;
    bool invertedRelative;
    double currentLimit;
    double relativePositionConversionFactor;
    double relativeVelocityConversionFactor;
    rev::CANSparkMax::IdleMode idleMode;
    PID velocityPID;
};

struct RollerMotorConfig {
    int ID = 1;
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

     /**
     * Returns a static instance of the ConfigFiles which is used
     * to globally distribute the ConfigFile Data
     */
    static ConfigFiles& getInstance()
    {
        static ConfigFiles instance;
        return instance;
    }

     /**
     * Loads data out of the selected config file and loads the data into a 
     * RobotConfig object which is then distributed out to subsystems
     *
     * @param fileName The name of the config file that is being loaded
     */
    void LoadConfigFiles(std::string fileName);

     /**
     * Returns a reference to the RobotConfig data while making sure that it is generated
     */
    RobotConfig& GetConfigFiles();

    std::unordered_map<std::string, double> positions;

private:

    bool initialized = false;
    RobotConfig robotConfig;

    ConfigFiles() {} // Private constructor to prevent instantiation outside of class
    ConfigFiles(const ConfigFiles&) = delete; // Disable copy constructor
    ConfigFiles& operator=(const ConfigFiles&) = delete; // Disable copy assignment operator
    ConfigFiles(ConfigFiles&&) = delete; // Disable move constructor
    ConfigFiles& operator=(ConfigFiles&&) = delete; // Disable move assignment operator
};

