#pragma once

#include <map>
#include <string>
#include <vector>
#include <iostream>
#include <filesystem>

#include <frc/filesystem.h>
#include <fstream>

class ConfigFiles
{
    public:

    ConfigFiles();


    struct MotorConfig
    {
        bool inverted = false;
        double currentLimit = 40;

    };

    enum currentConfigType
    {
        NONE,
        MOTOR_CONFIG
    };


    void LoadConfig(std::string name)
    {

        std::ifstream file{frc::filesystem::GetDeployDirectory() + "\\ConfigFiles\\" + name};

        if (file.is_open())
        {
            std::string line;

            while (std::getline(file, line))
            {
                if (line.find("MotorConfig"))
                {
                    configName = line.substr(12);
                    configType = MOTOR_CONFIG;
                    motorConfigs[configName] = MotorConfig{};
                }
                else
                {
                    switch (configType)
                    {
                    case MOTOR_CONFIG:

                        if (line.find("inverted:"))
                        {
                            int num = std::stoi(line.substr(10));
                            motorConfigs[configName].inverted = num==1 ? true : false;
                        }
                        else if (line.find("currentlimit:"))
                        {
                            double num = std::stod(line.substr(14));
                            motorConfigs[configName].currentLimit = num;
                        }

                        break;
                    
                    default:
                        break;
                    }
                }

                
            }
        }
    }

    private:

    std::string configName = "";
    currentConfigType configType = NONE;

    std::map<std::string, MotorConfig> motorConfigs;
};