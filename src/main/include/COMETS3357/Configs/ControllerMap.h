#pragma once

#include <iostream>
#include <fstream>
#include "Json/picojson.h"
#include <string>
#include <vector>
#include <map>
#include <functional>
#include <frc2/command/button/Trigger.h>
#include <filesystem>
#include <frc/fileSystem.h>
#include <frc2/command/button/CommandXboxController.h>
#include <frc/MathUtil.h>
#include <frc2/command/InstantCommand.h>
#include <frc2/command/Command.h>


class Controller
{
    public:

    int slot;

    Controller(int slot, std::unordered_map<std::string, std::shared_ptr<frc2::Command>> &actions);

    frc2::CommandXboxController controller;
    std::map<std::string, std::map<std::string, std::map<std::string, frc2::Trigger>>> controllerMap;
    std::string currentMode = "SemiAuto";
    std::string currentController = "XBOX";

    std::unordered_map<std::string, std::shared_ptr<frc2::Command>> &actionMap;

    frc2::Trigger controllerConnectionTrigger{[this]() {return controller.IsConnected();}};

    void LoadConfig(picojson::value &controllers);

    bool LoadControls();

    frc2::CommandPtr wrappedEventCommand(std::shared_ptr<frc2::Command> command);

};


class ControllerMap
{
public:


     /**
     * Returns a static instance of the ControllerMap which is used
     * to globally distribute the ConfigFile Data
     */
    ControllerMap(std::unordered_map<std::string, std::shared_ptr<frc2::Command>> &actionMap, std::string fileName);


    Controller primary;
    Controller secondary;
    Controller test;
     /**
     * Loads data out of the selected config file and loads the data into a 
     * RobotConfig object which is then distributed out to subsystems
     *
     * @param fileName The name of the config file that is being loaded
     */
    void LoadControllerMap(std::string fileName);

     /**
     * Returns a reference to the RobotConfig data while making sure that it is generated
     */


private:



    
};

