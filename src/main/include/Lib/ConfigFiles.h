#include <iostream>
#include <fstream>
#include "Json/json.h"

#include <string>
#include <vector>
#include <map>
#include <frc/fileSystem.h>
#include "PID.h"

#include <rev/CANSparkMax.h>

struct PositionMotorConfig {
    bool inverted_absolute;
    bool inverted_relative;
    int current_limit;
    double relative_conversion_factor;
    double absolute_conversion_factor;
    double absolute_zero_offset;
    double max_speed;
    double min_speed;
    rev::CANSparkMax::IdleMode idleMode;

    PID velocity_pid;
    PID position_pid;
};

struct WheelMotorConfig {
    bool inverted_relative;
    int current_limit;
    double relative_conversion_factor;
    rev::CANSparkMax::IdleMode idleMode;

    struct VelocityPID {
        double p;
        double i;
        double d;
        double ff;
    } velocity_pid;
};

struct RollerMotorConfig {
    bool inverted_relative;
    int current_limit;
    rev::CANSparkMax::IdleMode idleMode;
};

struct RobotConfig {
    std::map<std::string, PositionMotorConfig> position_motor_configs;
    std::map<std::string, WheelMotorConfig> wheel_motor_configs;
    std::map<std::string, RollerMotorConfig> roller_motor_configs;

};


class ConfigFiles
{
public:

    static ConfigFiles& getInstance()
    {
        static ConfigFiles config;
        return config;
    }

    void LoadConfigFiles(std::string fileName)
    {
        std::ifstream json_file(frc::filesystem::GetDeployDirectory() + "\\ConfigFiles\\" + fileName + ".json");
        Json::Value root;
        Json::CharReaderBuilder builder;
        std::string errors;

        if (!Json::parseFromStream(builder, json_file, &root, &errors)) {
            std::cerr << "Failed to parse JSON: " << errors << std::endl;
        }

        // Access values in root object
        

        for (const auto& position_motor_config_json : root["PositionMotorConfigs"]) {
            PositionMotorConfig position_motor_config;

            position_motor_config.inverted_absolute = position_motor_config_json["InvertedAbsolute"].asBool();
            position_motor_config.inverted_relative = position_motor_config_json["InvertedRelative"].asBool();
            position_motor_config.current_limit = position_motor_config_json["CurrentLimit"].asInt();
            position_motor_config.relative_conversion_factor = position_motor_config_json["RelativeConversionFactor"].asDouble();
            position_motor_config.absolute_conversion_factor = position_motor_config_json["AbsoluteConversionFactor"].asDouble();
            position_motor_config.absolute_zero_offset = position_motor_config_json["AbsoluteZeroOffset"].asDouble();
             position_motor_config.max_speed = position_motor_config_json["MaxSpeed"].asDouble();
            position_motor_config.min_speed = position_motor_config_json["MinSpeed"].asDouble();
            position_motor_config.idleMode = position_motor_config_json["IdleMode"].asString()=="Break" ? rev::CANSparkMax::IdleMode::kBrake : rev::CANSparkMax::IdleMode::kCoast;

            const auto& velocity_pid_json = position_motor_config_json["VelocityPID"];
            position_motor_config.velocity_pid.P = velocity_pid_json["P"].asDouble();
            position_motor_config.velocity_pid.I = velocity_pid_json["I"].asDouble();
            position_motor_config.velocity_pid.D = velocity_pid_json["D"].asDouble();
            position_motor_config.velocity_pid.FF = velocity_pid_json["FF"].asDouble();

            const auto& position_pid_json = position_motor_config_json["PositionPID"];
            position_motor_config.position_pid.P = position_pid_json["P"].asDouble();
            position_motor_config.position_pid.I = position_pid_json["I"].asDouble();
            position_motor_config.position_pid.D = position_pid_json["D"].asDouble();
            position_motor_config.position_pid.FF = position_pid_json["FF"].asDouble();
           

            robot_config.position_motor_configs[position_motor_config_json["Name"].asString()] = position_motor_config;
        }

        for (const auto& wheel_motor_config_json : root["WheelMotorConfig"]) {
            WheelMotorConfig wheel_motor_config;

            wheel_motor_config.inverted_relative = wheel_motor_config_json["InvertedRelative"].asBool();
            wheel_motor_config.current_limit = wheel_motor_config_json["CurrentLimit"].asInt();
            wheel_motor_config.relative_conversion_factor = wheel_motor_config_json["RelativeConversionFactor"].asDouble();
            wheel_motor_config.idleMode = wheel_motor_config_json["IdleMode"].asString()=="Break" ? rev::CANSparkMax::IdleMode::kBrake : rev::CANSparkMax::IdleMode::kCoast;

            const auto& velocity_pid_json = wheel_motor_config_json["VelocityPID"];
            wheel_motor_config.velocity_pid.p = velocity_pid_json["P"].asDouble();
            wheel_motor_config.velocity_pid.i = velocity_pid_json["I"].asDouble();
            wheel_motor_config.velocity_pid.d = velocity_pid_json["D"].asDouble();
            wheel_motor_config.velocity_pid.ff = velocity_pid_json["FF"].asDouble();

            robot_config.wheel_motor_configs[wheel_motor_config_json["Name"].asString()] = wheel_motor_config;
        }

        for (const auto& roller_motor_config_json : root["RollerMotorConfig"])
        {
            RollerMotorConfig roller_motor_config;

            roller_motor_config.inverted_relative = roller_motor_config_json["InvertedRelative"].asBool();
            roller_motor_config.current_limit = roller_motor_config_json["CurrentLimit"].asInt();
            roller_motor_config.idleMode = roller_motor_config_json["IdleMode"].asString()=="Break" ? rev::CANSparkMax::IdleMode::kBrake : rev::CANSparkMax::IdleMode::kCoast;


            robot_config.roller_motor_configs[roller_motor_config_json["Name"].asString()] = roller_motor_config;

        }
    }

    RobotConfig robot_config;
};

