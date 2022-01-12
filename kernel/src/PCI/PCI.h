#pragma once
#include <cstdint>
#include "../ACPI/ACPI.h"
#include "../include/PageTableManager.h"
#include "../include/BasicRenderer.h"
#include "../include/cStr.h"

namespace PCI {
    struct PCIDeviceHeader {
        uint16_t VendorID;
        uint16_t DeviceID;
        uint16_t Command;
        uint16_t Status;
        uint8_t RevisionID;
        uint8_t ProgIF;
        uint8_t Subclass;
        uint8_t Class;
        uint8_t CacheLineSize;
        uint8_t LatenctTimer;
        uint8_t HeaderType;
        uint8_t BIST;
    };

    void EnumeratePCI(ACPI::MCFGHeader* mcfg);
}