#include "Lib/ConfigFiles.h"
#include "Lib/PositionSparkMax.h"
#include <frc/Filesystem.h>

RobotConfig& ConfigFiles::GetConfigFiles()
{
    if (!initialized)
    {
        LoadConfigFiles("Comp");
        initialized = true;
    }
    return robotConfig;
}

void ConfigFiles::LoadConfigFiles(std::string fileName)
{

    std::ifstream jsonFile(frc::filesystem::GetDeployDirectory() + "\\ConfigFiles\\" + fileName + ".json");
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
    picojson::array swerveConfigs = jsonValue.get("SwerveConfigs").get<picojson::array>();
    picojson::array swerveModuleConfigs = jsonValue.get("SwerveModuleConfigs").get<picojson::array>();

    for (auto& config : swerveModuleConfigs)
    {
        SwerveModuleConfig moduleConfig;
        moduleConfig.azimuthConfigName = config.get("Azimuth").get<std::string>();
        moduleConfig.driveConfigName = config.get("Drive").get<std::string>();
        moduleConfig.angularOffset = config.get("AngularOffset").get<double>();

        robotConfig.swerveModuleConfigs[config.get("Name").get<std::string>()] = moduleConfig;
    }

    for (auto& config : swerveConfigs)
    {
        SwerveConfig swerveConfig;
        swerveConfig.frontLeftModule = robotConfig.swerveModuleConfigs[config.get("FrontLeftModule").get<std::string>()];
        swerveConfig.frontRightModule = robotConfig.swerveModuleConfigs[config.get("FrontRightModule").get<std::string>()];
        swerveConfig.backLeftModule = robotConfig.swerveModuleConfigs[config.get("BackLeftModule").get<std::string>()];
        swerveConfig.backRightModule = robotConfig.swerveModuleConfigs[config.get("BackRightModule").get<std::string>()];

        swerveConfig.trackWidth = units::meter_t{config.get("TrackWidth").get<double>()};
        swerveConfig.wheelBase = units::meter_t{config.get("WheelBase").get<double>()};
        swerveConfig.maxSpeed = units::meters_per_second_t{config.get("MaxSpeed").get<double>()};
        swerveConfig.maxTurnSpeed = units::radians_per_second_t{config.get("MaxTurnSpeed").get<double>()};

        swerveConfig.directionSlewRate = config.get("DirectionSlewRate").get<double>();
        swerveConfig.magnitudeSlewRate = config.get("MagnitudeSlewRate").get<double>();
        swerveConfig.rotationalSlewRate = config.get("RotationalSlewRate").get<double>();

        robotConfig.swerveConfigs[config.get("Name").get<std::string>()] = swerveConfig;
    }

    for (auto& config : positionMotorConfigs) {
        PositionMotorConfig motorConfig;
        motorConfig.ID = (int)config.get("ID").get<double>();
        motorConfig.defaultMode = config.get("DefaultRunMode").get<std::string>()=="ABSOLUTE" ? PositionSparkMaxRunMode::POSITION_SPARK_MAX_ABSOLUTE : PositionSparkMaxRunMode::POSITION_SPARK_MAX_RELATIVE;
        motorConfig.invertedAbsolute = config.get("InvertedAbsolute").get<bool>();
        motorConfig.invertedRelative = config.get("InvertedRelative").get<bool>();
        motorConfig.currentLimit = config.get("CurrentLimit").get<double>();
        motorConfig.relativePositionConversionFactor = config.get("RelativePositionConversionFactor").get<double>();
        motorConfig.relativeVelocityConversionFactor = config.get("RelativeVelocityConversionFactor").get<double>();
        motorConfig.absolutePositionConversionFactor = config.get("AbsolutePositionConversionFactor").get<double>();
        motorConfig.absoluteVelocityConversionFactor = config.get("AbsoluteVelocityConversionFactor").get<double>();
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

        motorConfig.positionPIDWrappingEnabled = config.get("PositionPIDWrappingEnabled").get<bool>();
        motorConfig.turningEncoderPositionPIDMinInput = config.get("TurningEncoderPositionPIDMinInput").get<double>();
        motorConfig.turningEncoderPositionPIDMaxInput = config.get("TurningEncoderPositionPIDMaxInput").get<double>();

        robotConfig.positionMotorConfigs[config.get("Name").get<std::string>()] = motorConfig;
    }

    for (auto& config : wheelMotorConfigs)
    {
    
        WheelMotorConfig motorConfig;
        motorConfig.ID = (int)config.get("ID").get<double>();
        motorConfig.invertedRelative = config.get("InvertedRelative").get<bool>();
        motorConfig.currentLimit = config.get("CurrentLimit").get<double>();
        motorConfig.relativePositionConversionFactor = config.get("RelativePositionConversionFactor").get<double>();
        motorConfig.relativeVelocityConversionFactor = config.get("RelativeVelocityConversionFactor").get<double>();
        motorConfig.idleMode = config.get("IdleMode").get<std::string>() == "Break" ? rev::CANSparkMax::IdleMode::kBrake : rev::CANSparkMax::IdleMode::kCoast;

        motorConfig.velocityPID.P = config.get("VelocityPID").get("P").get<double>();
        motorConfig.velocityPID.I = config.get("VelocityPID").get("I").get<double>();
        motorConfig.velocityPID.D = config.get("VelocityPID").get("D").get<double>();
        motorConfig.velocityPID.FF = config.get("VelocityPID").get("FF").get<double>();

        robotConfig.wheelMotorConfigs[config.get("Name").get<std::string>()] = motorConfig;
    }

    for (auto& config : rollerMotorConfigs)
    {
        RollerMotorConfig motorConfig;
        motorConfig.ID = (int)config.get("ID").get<double>();
        motorConfig.invertedRelative = config.get("InvertedRelative").get<bool>();
        motorConfig.currentLimit = config.get("CurrentLimit").get<double>();
        motorConfig.idleMode = config.get("IdleMode").get<std::string>() == "Break" ? rev::CANSparkMax::IdleMode::kBrake : rev::CANSparkMax::IdleMode::kCoast;

        robotConfig.rollerMotorConfigs[config.get("Name").get<std::string>()] = motorConfig;
    }




}