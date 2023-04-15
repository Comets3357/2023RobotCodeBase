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

struct PositionMotorConfig {
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

struct RobotConfig {
    std::map<std::string, PositionMotorConfig> positionMotorConfigs;
    std::map<std::string, WheelMotorConfig> wheelMotorConfigs;
    std::map<std::string, RollerMotorConfig> rollerMotorConfigs;

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

    RobotConfig robot_config;

    private:

    ConfigFiles() {} // Private constructor to prevent instantiation outside of class
    ConfigFiles(const ConfigFiles&) = delete; // Disable copy constructor
    ConfigFiles& operator=(const ConfigFiles&) = delete; // Disable copy assignment operator
    ConfigFiles(ConfigFiles&&) = delete; // Disable move constructor
    ConfigFiles& operator=(ConfigFiles&&) = delete; // Disable move assignment operator
};

