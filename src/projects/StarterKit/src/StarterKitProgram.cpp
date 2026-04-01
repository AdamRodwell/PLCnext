#include "StarterKitProgram.hpp"
#include "Arp/System/Commons/Logging.h"
#include "Arp/System/Core/ByteConverter.hpp"

namespace StarterKit
{
void
StarterKitProgram::Execute()
{
    // TON: fans only activate after command has been held true for 500 ms
    outputOnDelay_.update(config_.allowOutputs && command_.setOutput);
    if (outputOnDelay_.Q())
    {
        // control two fans for cooling
        dOUT01_ = true;
        dOUT02_ = true;
    }
    else
    {
        dOUT01_ = false;
        dOUT02_ = false;
    }

    // EdgeTrigger: log analog reading only on the rising edge of readAnalog1
    readAnalog1Trig_.update(static_cast<bool>(command_.readAnalog1));
    if (readAnalog1Trig_.Q())
    {
        uint32 analogReading = aiN1_;

        log.Info("Analog one reading: {0}", analogReading);

        const double scaledReading = Utils::Scale(
            static_cast<double>(analogReading),
            0.0, 10000.0,
            static_cast<double>(config_.analogInOne.minRange),
            static_cast<double>(config_.analogInOne.maxRange));

        log.Info("Scaled analog reading {0}", scaledReading);
    }
}

} // end of namespace StarterKit
