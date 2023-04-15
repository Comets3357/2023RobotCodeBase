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

    void LoadConfigFiles(std::string fileName)
    {

        std::ifstream jsonFile("path/to/your/json/file.json");
        if (!jsonFile.is_open()) {
            std::cerr << "Failed to open file" << std::endl;
        }

        std::string jsonString((std::istreambuf_iterator<char>(jsonFile)), std::istreambuf_iterator<char>());

        picojson::value jsonValue;
        std::string error = picojson::parse(jsonValue, jsonString);
        if (!error.empty()) {
            std::cerr << "JSON parse error: " << error << std::endl;
        }

        picojson::array positionMotorConfigs = jsonValue.get("PositionMotorConfigs").get<picojson::array>();
        picojson::array rollerMotorConfigs = jsonValue.get("RollerMotorConfigs").get<picojson::array>();
        picojson::array wheelMotorConfigs = jsonValue.get("WheelMotorConfigs").get<picojson::array>();

        for (auto& config : positionMotorConfigs) {
            PositionMotorConfig motorConfig;
            motorConfig.invertedAbsolute = config.get("InvertedAbsolute").get<bool>();
            motorConfig.invertedRelative = config.get("InvertedRelative").get<bool>();
            motorConfig.currentLimit = config.get("CurrentLimit").get<double>();
            motorConfig.relativeConversionFactor = config.get("RelativeConversionFactor").get<double>();
            motorConfig.absoluteConversionFactor = config.get("AbsoluteConversionFactor").get<double>();
            motorConfig.absoluteZeroOffset = config.get("AbsoluteZeroOffset").get<double>();
            motorConfig.maxSpeed = config.get("MaxSpeed").get<double>();
            motorConfig.minSpeed = config.get("MinSpeed").get<double>();
            motorConfig.idleMode = config.get("IdleMode").get<std::string>() == "Break" ? rev::CANSparkMax::IdleMode::kBrake : rev::CANSparkMax::IdleMode::kCoast;

            motorConfig.velocityPID.P = config.get("VelocityPID").get("P").get<double>();
            motorConfig.velocityPID.I = config.get("VelocityPID").get("I").get<double>();
            motorConfig.velocityPID.D = config.get("VelocityPID").get("D").get<double>();
            motorConfig.velocityPID.FF = config.get("VelocityPID").get("FF").get<double>();

            motorConfig.positionPID.P = config.get("PositionPID").get("P").get<double>();
            motorConfig.positionPID.I = config.get("PositionPID").get("I").get<double>();
            motorConfig.positionPID.D = config.get("PositionPID").get("D").get<double>();
            motorConfig.positionPID.FF = config.get("PositionPID").get("FF").get<double>();

            robot_config.positionMotorConfigs[config.get("Name").get<std::string>()] = motorConfig;
        }

        for (auto& config : wheelMotorConfigs)
        {
        
            WheelMotorConfig motorConfig;
            motorConfig.invertedRelative = config.get("InvertedRelative").get<bool>();
            motorConfig.currentLimit = config.get("CurrentLimit").get<double>();
            motorConfig.relativeConversionFactor = config.get("RelativeConversionFactor").get<double>();
            motorConfig.idleMode = config.get("IdleMode").get<std::string>() == "Break" ? rev::CANSparkMax::IdleMode::kBrake : rev::CANSparkMax::IdleMode::kCoast;

            motorConfig.velocityPID.P = config.get("VelocityPID").get("P").get<double>();
            motorConfig.velocityPID.I = config.get("VelocityPID").get("I").get<double>();
            motorConfig.velocityPID.D = config.get("VelocityPID").get("D").get<double>();
            motorConfig.velocityPID.FF = config.get("VelocityPID").get("FF").get<double>();

            robot_config.wheelMotorConfigs[config.get("Name").get<std::string>()] = motorConfig;
        }

        for (auto& config : rollerMotorConfigs)
        {
            RollerMotorConfig motorConfig;
            motorConfig.invertedRelative = config.get("InvertedRelative").get<bool>();
            motorConfig.currentLimit = config.get("CurrentLimit").get<double>();
            motorConfig.idleMode = config.get("IdleMode").get<std::string>() == "Break" ? rev::CANSparkMax::IdleMode::kBrake : rev::CANSparkMax::IdleMode::kCoast;

            robot_config.rollerMotorConfigs[config.get("Name").get<std::string>()] = motorConfig;
        }


    }

    RobotConfig robot_config;

    private:

    ConfigFiles() {} // Private constructor to prevent instantiation outside of class
    ConfigFiles(const ConfigFiles&) = delete; // Disable copy constructor
    ConfigFiles& operator=(const ConfigFiles&) = delete; // Disable copy assignment operator
    ConfigFiles(ConfigFiles&&) = delete; // Disable move constructor
    ConfigFiles& operator=(ConfigFiles&&) = delete; // Disable move assignment operator
};

