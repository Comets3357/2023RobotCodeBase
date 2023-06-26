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

    Controller(int slot, std::unordered_map<std::string, std::shared_ptr<frc2::Command>> &actions);

    frc2::CommandXboxController controller;
    std::map<std::string, std::map<std::string, std::map<std::string, frc2::Trigger>>> controllerMap;
    std::string currentMode;
    std::string currentController;

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
    ControllerMap(std::unordered_map<std::string, std::shared_ptr<frc2::Command>> &actionMap);

    std::unordered_map<std::string, std::shared_ptr<frc2::Command>> &actions;


    Controller primary{0, actions};
    Controller secondary{1, actions};
    Controller test{2, actions};
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

