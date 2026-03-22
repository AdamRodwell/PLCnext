#include "Arp/System/Core/Arp.h"
#include "Arp/Plc/Commons/Meta/TypeSystem/TypeSystem.h"
#include "StarterKitProgram.hpp"
#include "TemplateController.hpp"
#include "StarterKitLibrary.hpp"

namespace StarterKit
{

using namespace Arp::Plc::Commons::Meta;

    void StarterKitLibrary::InitializeTypeDomain()
    {
        this->typeDomain.AddTypeDefinitions
        (
            // Begin TypeDefinitions
            {
                {   // TypeDefinition: StarterKit::StarterKitProgram::StarterKitCommand
                    DataType::Struct, CTN<StarterKit::StarterKitProgram::StarterKitCommand>(), sizeof(::StarterKit::StarterKitProgram::StarterKitCommand), alignof(::StarterKit::StarterKitProgram::StarterKitCommand), StandardAttribute::None,
                    {
                        // FieldDefinitions:
                        { "readAnalog1", offsetof(::StarterKit::StarterKitProgram::StarterKitCommand, readAnalog1), DataType::Boolean, String::Empty, sizeof(Arp::boolean), alignof(Arp::boolean), {  }, StandardAttribute::None },
                        { "setOutput", offsetof(::StarterKit::StarterKitProgram::StarterKitCommand, setOutput), DataType::Boolean, String::Empty, sizeof(Arp::boolean), alignof(Arp::boolean), {  }, StandardAttribute::None },
                    }
                },
                {   // TypeDefinition: StarterKit::StarterKitProgram::StarterKitConfig
                    DataType::Struct, CTN<StarterKit::StarterKitProgram::StarterKitConfig>(), sizeof(::StarterKit::StarterKitProgram::StarterKitConfig), alignof(::StarterKit::StarterKitProgram::StarterKitConfig), StandardAttribute::None,
                    {
                        // FieldDefinitions:
                        { "allowOutputs", offsetof(::StarterKit::StarterKitProgram::StarterKitConfig, allowOutputs), DataType::Boolean, String::Empty, sizeof(Arp::boolean), alignof(Arp::boolean), {  }, StandardAttribute::None },
                        { "minRange", offsetof(::StarterKit::StarterKitProgram::StarterKitConfig, minRange), DataType::UInt32, String::Empty, sizeof(Arp::uint32), alignof(Arp::uint32), {  }, StandardAttribute::None },
                        { "analogInOne", offsetof(::StarterKit::StarterKitProgram::StarterKitConfig, analogInOne), DataType::Struct, CTN<StarterKit::StarterKitProgram::analogConfig>(), sizeof(StarterKit::StarterKitProgram::analogConfig), alignof(StarterKit::StarterKitProgram::analogConfig), {  }, StandardAttribute::None },
                    }
                },
                {   // TypeDefinition: StarterKit::StarterKitProgram::StarterKitData
                    DataType::Struct, CTN<StarterKit::StarterKitProgram::StarterKitData>(), sizeof(::StarterKit::StarterKitProgram::StarterKitData), alignof(::StarterKit::StarterKitProgram::StarterKitData), StandardAttribute::None,
                    {
                        // FieldDefinitions:
                        { "areOutPutActive", offsetof(::StarterKit::StarterKitProgram::StarterKitData, areOutPutActive), DataType::Boolean, String::Empty, sizeof(Arp::boolean), alignof(Arp::boolean), {  }, StandardAttribute::None },
                    }
                },
                {   // TypeDefinition: StarterKit::TemplateController::TemplateConfig
                    DataType::Struct, CTN<StarterKit::TemplateController::TemplateConfig>(), sizeof(::StarterKit::TemplateController::TemplateConfig), alignof(::StarterKit::TemplateController::TemplateConfig), StandardAttribute::None,
                    {
                        // FieldDefinitions:
                        { "exampleTimeoutMs", offsetof(::StarterKit::TemplateController::TemplateConfig, exampleTimeoutMs), DataType::UInt32, String::Empty, sizeof(Arp::uint32), alignof(Arp::uint32), {  }, StandardAttribute::None },
                        { "examplePositionMm", offsetof(::StarterKit::TemplateController::TemplateConfig, examplePositionMm), DataType::Float32, String::Empty, sizeof(Arp::float32), alignof(Arp::float32), {  }, StandardAttribute::None },
                        { "exampleIgnoreSensor", offsetof(::StarterKit::TemplateController::TemplateConfig, exampleIgnoreSensor), DataType::Boolean, String::Empty, sizeof(Arp::boolean), alignof(Arp::boolean), {  }, StandardAttribute::None },
                    }
                },
                {   // TypeDefinition: StarterKit::TemplateController::TemplateData
                    DataType::Struct, CTN<StarterKit::TemplateController::TemplateData>(), sizeof(::StarterKit::TemplateController::TemplateData), alignof(::StarterKit::TemplateController::TemplateData), StandardAttribute::None,
                    {
                        // FieldDefinitions:
                        { "isInitialisationDone", offsetof(::StarterKit::TemplateController::TemplateData, isInitialisationDone), DataType::Boolean, String::Empty, sizeof(Arp::boolean), alignof(Arp::boolean), {  }, StandardAttribute::None },
                        { "isCycleDone", offsetof(::StarterKit::TemplateController::TemplateData, isCycleDone), DataType::Boolean, String::Empty, sizeof(Arp::boolean), alignof(Arp::boolean), {  }, StandardAttribute::None },
                        { "cycleCount", offsetof(::StarterKit::TemplateController::TemplateData, cycleCount), DataType::UInt32, String::Empty, sizeof(Arp::uint32), alignof(Arp::uint32), {  }, StandardAttribute::None },
                        { "currentState", offsetof(::StarterKit::TemplateController::TemplateData, currentState), DataType::Enum | DataType::UInt8, CTN<StarterKit::TemplateController::TemplateControllerState>(), sizeof(StarterKit::TemplateController::TemplateControllerState), alignof(StarterKit::TemplateController::TemplateControllerState), {  }, StandardAttribute::None },
                        { "error", offsetof(::StarterKit::TemplateController::TemplateData, error), DataType::Struct, CTN<StarterKit::TemplateControllerError>(), sizeof(StarterKit::TemplateControllerError), alignof(StarterKit::TemplateControllerError), {  }, StandardAttribute::None },
                    }
                },
                {   // TypeDefinition: StarterKit::TemplateControllerError
                    DataType::Struct, CTN<StarterKit::TemplateControllerError>(), sizeof(::StarterKit::TemplateControllerError), alignof(::StarterKit::TemplateControllerError), StandardAttribute::None,
                    {
                        // FieldDefinitions:
                        { "warningExampleTimeout", offsetof(::StarterKit::TemplateControllerError, warningExampleTimeout), DataType::Boolean, String::Empty, sizeof(Arp::boolean), alignof(Arp::boolean), {  }, StandardAttribute::None },
                        { "warningExampleSensorFailed", offsetof(::StarterKit::TemplateControllerError, warningExampleSensorFailed), DataType::Boolean, String::Empty, sizeof(Arp::boolean), alignof(Arp::boolean), {  }, StandardAttribute::None },
                        { "errorExampleUnexpectedState", offsetof(::StarterKit::TemplateControllerError, errorExampleUnexpectedState), DataType::Boolean, String::Empty, sizeof(Arp::boolean), alignof(Arp::boolean), {  }, StandardAttribute::None },
                        { "hasErrorSubSystem", offsetof(::StarterKit::TemplateControllerError, hasErrorSubSystem), DataType::Boolean, String::Empty, sizeof(Arp::boolean), alignof(Arp::boolean), {  }, StandardAttribute::None },
                        { "hasWarningSubSystem", offsetof(::StarterKit::TemplateControllerError, hasWarningSubSystem), DataType::Boolean, String::Empty, sizeof(Arp::boolean), alignof(Arp::boolean), {  }, StandardAttribute::None },
                    }
                },
                {   // TypeDefinition: StarterKit::TemplateController::TemplateCommand
                    DataType::Struct, CTN<StarterKit::TemplateController::TemplateCommand>(), sizeof(::StarterKit::TemplateController::TemplateCommand), alignof(::StarterKit::TemplateController::TemplateCommand), StandardAttribute::None,
                    {
                        // FieldDefinitions:
                        { "disable", offsetof(::StarterKit::TemplateController::TemplateCommand, disable), DataType::Boolean, String::Empty, sizeof(Arp::boolean), alignof(Arp::boolean), {  }, StandardAttribute::None },
                        { "initialise", offsetof(::StarterKit::TemplateController::TemplateCommand, initialise), DataType::Boolean, String::Empty, sizeof(Arp::boolean), alignof(Arp::boolean), {  }, StandardAttribute::None },
                        { "startCycle", offsetof(::StarterKit::TemplateController::TemplateCommand, startCycle), DataType::Boolean, String::Empty, sizeof(Arp::boolean), alignof(Arp::boolean), {  }, StandardAttribute::None },
                        { "enterManualMode", offsetof(::StarterKit::TemplateController::TemplateCommand, enterManualMode), DataType::Boolean, String::Empty, sizeof(Arp::boolean), alignof(Arp::boolean), {  }, StandardAttribute::None },
                        { "manual", offsetof(::StarterKit::TemplateController::TemplateCommand, manual), DataType::Struct, CTN<StarterKit::TemplateController::TemplateManualCommand>(), sizeof(StarterKit::TemplateController::TemplateManualCommand), alignof(StarterKit::TemplateController::TemplateManualCommand), {  }, StandardAttribute::None },
                    }
                },
                {   // TypeDefinition: StarterKit::StarterKitProgram::analogConfig
                    DataType::Struct, CTN<StarterKit::StarterKitProgram::analogConfig>(), sizeof(::StarterKit::StarterKitProgram::analogConfig), alignof(::StarterKit::StarterKitProgram::analogConfig), StandardAttribute::None,
                    {
                        // FieldDefinitions:
                        { "minRange", offsetof(::StarterKit::StarterKitProgram::analogConfig, minRange), DataType::UInt32, String::Empty, sizeof(Arp::uint32), alignof(Arp::uint32), {  }, StandardAttribute::None },
                        { "maxRange", offsetof(::StarterKit::StarterKitProgram::analogConfig, maxRange), DataType::UInt32, String::Empty, sizeof(Arp::uint32), alignof(Arp::uint32), {  }, StandardAttribute::None },
                    }
                },
                {   // TypeDefinition: StarterKit::TemplateController::TemplateManualCommand
                    DataType::Struct, CTN<StarterKit::TemplateController::TemplateManualCommand>(), sizeof(::StarterKit::TemplateController::TemplateManualCommand), alignof(::StarterKit::TemplateController::TemplateManualCommand), StandardAttribute::None,
                    {
                        // FieldDefinitions:
                        { "activateOutput", offsetof(::StarterKit::TemplateController::TemplateManualCommand, activateOutput), DataType::Boolean, String::Empty, sizeof(Arp::boolean), alignof(Arp::boolean), {  }, StandardAttribute::None },
                        { "manualSetpoint", offsetof(::StarterKit::TemplateController::TemplateManualCommand, manualSetpoint), DataType::Float32, String::Empty, sizeof(Arp::float32), alignof(Arp::float32), {  }, StandardAttribute::None },
                    }
                },
                {   // ProgramDefinition: StarterKit::StarterKitProgram
                    DataType::Program, CTN<StarterKit::StarterKitProgram>(), sizeof(::StarterKit::StarterKitProgram), alignof(::StarterKit::StarterKitProgram), StandardAttribute::None,
                    {
                        // FieldDefinitions:
                        { "Command", offsetof(::StarterKit::StarterKitProgram, command_), DataType::Struct, CTN<StarterKit::StarterKitProgram::StarterKitCommand>(), sizeof(StarterKit::StarterKitProgram::StarterKitCommand), alignof(StarterKit::StarterKitProgram::StarterKitCommand), {  }, StandardAttribute::Input | StandardAttribute::Opc },
                        { "Config", offsetof(::StarterKit::StarterKitProgram, config_), DataType::Struct, CTN<StarterKit::StarterKitProgram::StarterKitConfig>(), sizeof(StarterKit::StarterKitProgram::StarterKitConfig), alignof(StarterKit::StarterKitProgram::StarterKitConfig), {  }, StandardAttribute::Input | StandardAttribute::Opc },
                        { "Data", offsetof(::StarterKit::StarterKitProgram, data_), DataType::Struct, CTN<StarterKit::StarterKitProgram::StarterKitData>(), sizeof(StarterKit::StarterKitProgram::StarterKitData), alignof(StarterKit::StarterKitProgram::StarterKitData), {  }, StandardAttribute::Output | StandardAttribute::Opc },
                        { "DIN01", offsetof(::StarterKit::StarterKitProgram, digitalIn1_), DataType::Boolean, String::Empty, sizeof(Arp::boolean), alignof(Arp::boolean), {  }, StandardAttribute::Input | StandardAttribute::Opc },
                        { "DIN02", offsetof(::StarterKit::StarterKitProgram, dIN02_), DataType::Boolean, String::Empty, sizeof(Arp::boolean), alignof(Arp::boolean), {  }, StandardAttribute::Input | StandardAttribute::Opc },
                        { "DIN03", offsetof(::StarterKit::StarterKitProgram, dIN03_), DataType::Boolean, String::Empty, sizeof(Arp::boolean), alignof(Arp::boolean), {  }, StandardAttribute::Input | StandardAttribute::Opc },
                        { "DIN04", offsetof(::StarterKit::StarterKitProgram, dIN04_), DataType::Boolean, String::Empty, sizeof(Arp::boolean), alignof(Arp::boolean), {  }, StandardAttribute::Input | StandardAttribute::Opc },
                        { "DIN05", offsetof(::StarterKit::StarterKitProgram, dIN05_), DataType::Boolean, String::Empty, sizeof(Arp::boolean), alignof(Arp::boolean), {  }, StandardAttribute::Input | StandardAttribute::Opc },
                        { "DIN06", offsetof(::StarterKit::StarterKitProgram, dIN06_), DataType::Boolean, String::Empty, sizeof(Arp::boolean), alignof(Arp::boolean), {  }, StandardAttribute::Input | StandardAttribute::Opc },
                        { "DIN07", offsetof(::StarterKit::StarterKitProgram, dIN07_), DataType::Boolean, String::Empty, sizeof(Arp::boolean), alignof(Arp::boolean), {  }, StandardAttribute::Input | StandardAttribute::Opc },
                        { "DIN08", offsetof(::StarterKit::StarterKitProgram, dIN08_), DataType::Boolean, String::Empty, sizeof(Arp::boolean), alignof(Arp::boolean), {  }, StandardAttribute::Input | StandardAttribute::Opc },
                        { "DIN09", offsetof(::StarterKit::StarterKitProgram, dIN09_), DataType::Boolean, String::Empty, sizeof(Arp::boolean), alignof(Arp::boolean), {  }, StandardAttribute::Input | StandardAttribute::Opc },
                        { "DIN10", offsetof(::StarterKit::StarterKitProgram, dIN10_), DataType::Boolean, String::Empty, sizeof(Arp::boolean), alignof(Arp::boolean), {  }, StandardAttribute::Input | StandardAttribute::Opc },
                        { "DIN11", offsetof(::StarterKit::StarterKitProgram, dIN11_), DataType::Boolean, String::Empty, sizeof(Arp::boolean), alignof(Arp::boolean), {  }, StandardAttribute::Input | StandardAttribute::Opc },
                        { "DIN12", offsetof(::StarterKit::StarterKitProgram, dIN12_), DataType::Boolean, String::Empty, sizeof(Arp::boolean), alignof(Arp::boolean), {  }, StandardAttribute::Input | StandardAttribute::Opc },
                        { "DIN13", offsetof(::StarterKit::StarterKitProgram, dIN13_), DataType::Boolean, String::Empty, sizeof(Arp::boolean), alignof(Arp::boolean), {  }, StandardAttribute::Input | StandardAttribute::Opc },
                        { "DIN14", offsetof(::StarterKit::StarterKitProgram, dIN14_), DataType::Boolean, String::Empty, sizeof(Arp::boolean), alignof(Arp::boolean), {  }, StandardAttribute::Input | StandardAttribute::Opc },
                        { "DIN15", offsetof(::StarterKit::StarterKitProgram, dIN15_), DataType::Boolean, String::Empty, sizeof(Arp::boolean), alignof(Arp::boolean), {  }, StandardAttribute::Input | StandardAttribute::Opc },
                        { "DIN16", offsetof(::StarterKit::StarterKitProgram, dIN16_), DataType::Boolean, String::Empty, sizeof(Arp::boolean), alignof(Arp::boolean), {  }, StandardAttribute::Input | StandardAttribute::Opc },
                        { "AIN1", offsetof(::StarterKit::StarterKitProgram, aiN1_), DataType::UInt32, String::Empty, sizeof(Arp::uint32), alignof(Arp::uint32), {  }, StandardAttribute::Input | StandardAttribute::Opc },
                        { "AIN2", offsetof(::StarterKit::StarterKitProgram, aiN2_), DataType::UInt32, String::Empty, sizeof(Arp::uint32), alignof(Arp::uint32), {  }, StandardAttribute::Input | StandardAttribute::Opc },
                        { "AIN3", offsetof(::StarterKit::StarterKitProgram, aiN3_), DataType::UInt32, String::Empty, sizeof(Arp::uint32), alignof(Arp::uint32), {  }, StandardAttribute::Input | StandardAttribute::Opc },
                        { "AIN4", offsetof(::StarterKit::StarterKitProgram, aiN4_), DataType::UInt32, String::Empty, sizeof(Arp::uint32), alignof(Arp::uint32), {  }, StandardAttribute::Input | StandardAttribute::Opc },
                        { "DOUT01", offsetof(::StarterKit::StarterKitProgram, dOUT01_), DataType::Boolean, String::Empty, sizeof(Arp::boolean), alignof(Arp::boolean), {  }, StandardAttribute::Output | StandardAttribute::Opc },
                        { "DOUT02", offsetof(::StarterKit::StarterKitProgram, dOUT02_), DataType::Boolean, String::Empty, sizeof(Arp::boolean), alignof(Arp::boolean), {  }, StandardAttribute::Output | StandardAttribute::Opc },
                        { "DOUT03", offsetof(::StarterKit::StarterKitProgram, dOUT03_), DataType::Boolean, String::Empty, sizeof(Arp::boolean), alignof(Arp::boolean), {  }, StandardAttribute::Output | StandardAttribute::Opc },
                        { "DOUT04", offsetof(::StarterKit::StarterKitProgram, dOUT04_), DataType::Boolean, String::Empty, sizeof(Arp::boolean), alignof(Arp::boolean), {  }, StandardAttribute::Output | StandardAttribute::Opc },
                        { "DOUT05", offsetof(::StarterKit::StarterKitProgram, dOUT05_), DataType::Boolean, String::Empty, sizeof(Arp::boolean), alignof(Arp::boolean), {  }, StandardAttribute::Output | StandardAttribute::Opc },
                        { "DOUT06", offsetof(::StarterKit::StarterKitProgram, dOUT06_), DataType::Boolean, String::Empty, sizeof(Arp::boolean), alignof(Arp::boolean), {  }, StandardAttribute::Output | StandardAttribute::Opc },
                        { "DOUT07", offsetof(::StarterKit::StarterKitProgram, dOUT07_), DataType::Boolean, String::Empty, sizeof(Arp::boolean), alignof(Arp::boolean), {  }, StandardAttribute::Output | StandardAttribute::Opc },
                        { "DOUT08", offsetof(::StarterKit::StarterKitProgram, dOUT08_), DataType::Boolean, String::Empty, sizeof(Arp::boolean), alignof(Arp::boolean), {  }, StandardAttribute::Output | StandardAttribute::Opc },
                        { "DOUT09", offsetof(::StarterKit::StarterKitProgram, dOUT09_), DataType::Boolean, String::Empty, sizeof(Arp::boolean), alignof(Arp::boolean), {  }, StandardAttribute::Output | StandardAttribute::Opc },
                        { "DOUT10", offsetof(::StarterKit::StarterKitProgram, dOUT10_), DataType::Boolean, String::Empty, sizeof(Arp::boolean), alignof(Arp::boolean), {  }, StandardAttribute::Output | StandardAttribute::Opc },
                        { "DOUT11", offsetof(::StarterKit::StarterKitProgram, dOUT11_), DataType::Boolean, String::Empty, sizeof(Arp::boolean), alignof(Arp::boolean), {  }, StandardAttribute::Output | StandardAttribute::Opc },
                        { "DOUT12", offsetof(::StarterKit::StarterKitProgram, dOUT12_), DataType::Boolean, String::Empty, sizeof(Arp::boolean), alignof(Arp::boolean), {  }, StandardAttribute::Output | StandardAttribute::Opc },
                        { "DOUT13", offsetof(::StarterKit::StarterKitProgram, dOUT13_), DataType::Boolean, String::Empty, sizeof(Arp::boolean), alignof(Arp::boolean), {  }, StandardAttribute::Output | StandardAttribute::Opc },
                        { "DOUT14", offsetof(::StarterKit::StarterKitProgram, dOUT14_), DataType::Boolean, String::Empty, sizeof(Arp::boolean), alignof(Arp::boolean), {  }, StandardAttribute::Output | StandardAttribute::Opc },
                        { "DOUT15", offsetof(::StarterKit::StarterKitProgram, dOUT15_), DataType::Boolean, String::Empty, sizeof(Arp::boolean), alignof(Arp::boolean), {  }, StandardAttribute::Output | StandardAttribute::Opc },
                        { "DOUT16", offsetof(::StarterKit::StarterKitProgram, dOUT16_), DataType::Boolean, String::Empty, sizeof(Arp::boolean), alignof(Arp::boolean), {  }, StandardAttribute::Output | StandardAttribute::Opc },
                    }
                },
                {   // ProgramDefinition: StarterKit::TemplateController
                    DataType::Program, CTN<StarterKit::TemplateController>(), sizeof(::StarterKit::TemplateController), alignof(::StarterKit::TemplateController), StandardAttribute::None,
                    {
                        // FieldDefinitions:
                        { "Config", offsetof(::StarterKit::TemplateController, config_), DataType::Struct, CTN<StarterKit::TemplateController::TemplateConfig>(), sizeof(StarterKit::TemplateController::TemplateConfig), alignof(StarterKit::TemplateController::TemplateConfig), {  }, StandardAttribute::Input | StandardAttribute::Opc | StandardAttribute::Retain },
                        { "Data", offsetof(::StarterKit::TemplateController, data_), DataType::Struct, CTN<StarterKit::TemplateController::TemplateData>(), sizeof(StarterKit::TemplateController::TemplateData), alignof(StarterKit::TemplateController::TemplateData), {  }, StandardAttribute::Output | StandardAttribute::Opc },
                        { "SystemTemplateError", offsetof(::StarterKit::TemplateController, systemTemplateError), DataType::Struct, CTN<StarterKit::TemplateControllerError>(), sizeof(StarterKit::TemplateControllerError), alignof(StarterKit::TemplateControllerError), {  }, StandardAttribute::Output | StandardAttribute::Opc },
                        { "Command", offsetof(::StarterKit::TemplateController, command_), DataType::Struct, CTN<StarterKit::TemplateController::TemplateCommand>(), sizeof(StarterKit::TemplateController::TemplateCommand), alignof(StarterKit::TemplateController::TemplateCommand), {  }, StandardAttribute::Input | StandardAttribute::Opc },
                        { "ExampleSensor", offsetof(::StarterKit::TemplateController, exampleSensor_), DataType::Boolean, String::Empty, sizeof(Arp::boolean), alignof(Arp::boolean), {  }, StandardAttribute::Input | StandardAttribute::Opc },
                    }
                },
            }
            // End TypeDefinitions
        );
        {
            TypeDefinition typeDefinition{DataType::Enum | DataType::UInt8, CTN<StarterKit::TemplateController::TemplateControllerState>(), sizeof(StarterKit::TemplateController::TemplateControllerState), alignof(StarterKit::TemplateController::TemplateControllerState), StandardAttribute::None, {}};
            {
                FieldDefinition field{"DISABLED", 0, DataType::Enum | DataType::UInt8, String::Empty, sizeof(StarterKit::TemplateController::TemplateControllerState), alignof(StarterKit::TemplateController::TemplateControllerState), {}, StandardAttribute::None};
                field.GetChildTypeInfo().AddCustomAttribute("Value", static_cast<std::underlying_type<StarterKit::TemplateController::TemplateControllerState>::type>(StarterKit::TemplateController::TemplateControllerState::DISABLED));
                typeDefinition.AddField(std::move(field));
            }
            {
                FieldDefinition field{"INITIALISING", 0, DataType::Enum | DataType::UInt8, String::Empty, sizeof(StarterKit::TemplateController::TemplateControllerState), alignof(StarterKit::TemplateController::TemplateControllerState), {}, StandardAttribute::None};
                field.GetChildTypeInfo().AddCustomAttribute("Value", static_cast<std::underlying_type<StarterKit::TemplateController::TemplateControllerState>::type>(StarterKit::TemplateController::TemplateControllerState::INITIALISING));
                typeDefinition.AddField(std::move(field));
            }
            {
                FieldDefinition field{"IDLE", 0, DataType::Enum | DataType::UInt8, String::Empty, sizeof(StarterKit::TemplateController::TemplateControllerState), alignof(StarterKit::TemplateController::TemplateControllerState), {}, StandardAttribute::None};
                field.GetChildTypeInfo().AddCustomAttribute("Value", static_cast<std::underlying_type<StarterKit::TemplateController::TemplateControllerState>::type>(StarterKit::TemplateController::TemplateControllerState::IDLE));
                typeDefinition.AddField(std::move(field));
            }
            {
                FieldDefinition field{"MANUAL_MODE", 0, DataType::Enum | DataType::UInt8, String::Empty, sizeof(StarterKit::TemplateController::TemplateControllerState), alignof(StarterKit::TemplateController::TemplateControllerState), {}, StandardAttribute::None};
                field.GetChildTypeInfo().AddCustomAttribute("Value", static_cast<std::underlying_type<StarterKit::TemplateController::TemplateControllerState>::type>(StarterKit::TemplateController::TemplateControllerState::MANUAL_MODE));
                typeDefinition.AddField(std::move(field));
            }
            {
                FieldDefinition field{"ERROR", 0, DataType::Enum | DataType::UInt8, String::Empty, sizeof(StarterKit::TemplateController::TemplateControllerState), alignof(StarterKit::TemplateController::TemplateControllerState), {}, StandardAttribute::None};
                field.GetChildTypeInfo().AddCustomAttribute("Value", static_cast<std::underlying_type<StarterKit::TemplateController::TemplateControllerState>::type>(StarterKit::TemplateController::TemplateControllerState::ERROR));
                typeDefinition.AddField(std::move(field));
            }
            typeDomain.AddTypeDefinition(std::move(typeDefinition));
        }
    }

} // end of namespace StarterKit

