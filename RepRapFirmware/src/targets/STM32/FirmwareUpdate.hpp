/*
    Most STM32 boards use a Bootloader to flash new firmware. So firmware updates is just
    moving firmware.bin to / and rebooting.
*/

extern uint32_t _estack;			// defined in the linker script

// Check the prerequisites for updating the main firmware. Return True if satisfied, else print a message to 'reply' and return false.
bool RepRap::CheckFirmwareUpdatePrerequisites(const StringRef& reply, const StringRef& filenameRef) noexcept
{
    #if HAS_MASS_STORAGE && (defined(LPC_NETWORKING) || HAS_WIFI_NETWORKING)
        FileStore * const firmwareFile = platform->OpenFile(FIRMWARE_DIRECTORY, filenameRef.IsEmpty() ? IAP_FIRMWARE_FILE : filenameRef.c_str(), OpenMode::read);
        if (firmwareFile == nullptr)
        {
            reply.printf("Firmware binary \"%s\" not found", IAP_FIRMWARE_FILE);
            return false;
        }

        // Check that the binary looks sensible. The first word is the initial stack pointer, which should be the top of RAM.
        const uint32_t initialStackPointer = (uint32_t)&_estack;

        uint32_t firstDword;
        bool ok = firmwareFile->Read(reinterpret_cast<char*>(&firstDword), sizeof(firstDword)) == (int)sizeof(firstDword);
        firmwareFile->Close();
        if (!ok || firstDword != initialStackPointer)
        {
            reply.printf("Firmware binary \"%s\" is not valid for this electronics %x %x", FIRMWARE_FILE, (unsigned)firstDword, (unsigned)initialStackPointer);
            return false;
        }
    #else
        reply.printf("To update firmware download firmware.bin to the sdcard as /firmware.bin and reset");
        return false;
    #endif

    return true;
}

// Update the firmware. Prerequisites should be checked before calling this.
void RepRap::UpdateFirmware(const StringRef& filenameRef) noexcept
{
#if  HAS_MASS_STORAGE && (defined(LPC_NETWORKING) || HAS_WIFI_NETWORKING)
    //DWC will upload firmware to 0:/sys/ we need to move to 0:/firmware.bin and reboot
    
    String<MaxFilenameLength> location;
    MassStorage::CombineName(location.GetRef(), FIRMWARE_DIRECTORY, filenameRef.IsEmpty() ? IAP_FIRMWARE_FILE : filenameRef.c_str());
    
    if(!MassStorage::Rename(location.c_str(), FIRMWARE_FILE, true, false))
    {
        //failed to rename
        platform->MessageF(FirmwareUpdateMessage, "Failed to move firmware file.\n");
        return;
    }
    EmergencyStop();			// turn off heaters etc.
    debugPrintf("Restarting....\n");
    delay(1000);    
    SoftwareReset(SoftwareResetReason::user); // Reboot
#endif
    
}
