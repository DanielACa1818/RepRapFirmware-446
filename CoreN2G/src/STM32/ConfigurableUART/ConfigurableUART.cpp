//author: sdavi
#if USE_UART0 || USE_UART1 || USE_UART2
#include <CoreImp.h>
#include "ConfigurableUART.h"
extern "C" void debugPrintf(const char* fmt, ...) __attribute__ ((format (printf, 1, 2)));

#if USE_UART0
ConfigurableUART UART_Slot0;
#endif
#if USE_UART1
ConfigurableUART UART_Slot1;
#endif
#if USE_UART2
ConfigurableUART UART_Slot2;
#endif




//Wrapper class around HardwareSerial for configurable Serial in RRF

ConfigurableUART::ConfigurableUART() noexcept
    : serialPort(nullptr) 
{
}


int8_t ConfigurableUART::GetUARTPortNumber() noexcept
{
    if(serialPort == nullptr) return -1;
#if defined(HAVE_HWSERIAL1)
    if(serialPort == &Serial1) return 1;
#endif
#if defined(HAVE_HWSERIAL2)
    if(serialPort == &Serial2) return 2;
#endif
#if defined(HAVE_HWSERIAL3)
    if(serialPort == &Serial3) return 3;
#endif
#if defined(HAVE_HWSERIAL4)
    if(serialPort == &Serial4) return 4;
#endif
#if defined(HAVE_HWSERIAL5)
    if(serialPort == &Serial5) return 5;
#endif
#if defined(HAVE_HWSERIAL6)
    if(serialPort == &Serial6) return 6;
#endif
#if defined(HAVE_HWSERIAL7)
    if(serialPort == &Serial7) return 7;
#endif
#if defined(HAVE_HWSERIAL8)
    if(serialPort == &Serial8) return 8;
#endif
#if defined(HAVE_HWSERIAL9)
    if(serialPort == &Serial9) return 9;
#endif
#if defined(HAVE_HWSERIAL10)
    if(serialPort == &Serial10) return 10;
#endif
#if defined(HAVE_HWSERIALLP1)
    if(serialPort == &SerialLP1) return 11;
#endif
        return -1;
}

bool ConfigurableUART::Configure(Pin rx, Pin tx) noexcept
{
    //Find the UART based on the confgured Pins
    void* rxDev = pinmap_peripheral(rx, PinMap_UART_RX);
    void* txDev = pinmap_peripheral(tx, PinMap_UART_TX);

    if (rxDev != nullptr && (rxDev == txDev))
    {
#if defined(HAVE_HWSERIAL1)
        if (rxDev == USART1)
            serialPort = &Serial1;
#endif
#if defined(HAVE_HWSERIAL2)
        if (rxDev == USART2)
            serialPort = &Serial2;
#endif
#if defined(HAVE_HWSERIAL3)
        if (rxDev == USART3)
            serialPort = &Serial3;
#endif
#if defined(HAVE_HWSERIAL4)
#if defined(USART4)
        if (rxDev == USART4)
            serialPort = &Serial4;
#else
        if (rxDev == UART4)
            serialPort = &Serial4;
#endif
#endif
#if defined(HAVE_HWSERIAL5)
#if defined(USART5)
        if (rxDev == USART5)
            serialPort = &Serial5;
#else
        if (rxDev == UART5)
            serialPort = &Serial5;
#endif
#endif
#if defined(HAVE_HWSERIAL6)
        if (rxDev == USART6)
            serialPort = &Serial6;
#endif
#if defined(HAVE_HWSERIAL7)
#if defined(USART7)
        if (rxDev == USART7)
            serialPort = &Serial7;
#else
        if (rxDev == UART7)
            serialPort = &Serial7;
#endif
#endif
#if defined(HAVE_HWSERIAL8)
#if defined(USART8)
        if (rxDev == USART8)
            serialPort = &Serial8;
#else
        if (rxDev == UART8)
            serialPort = &Serial8;
#endif
#endif
#if defined(HAVE_HWSERIAL9)
        if (rxDev == USART9)
            serialPort = &Serial9;
#endif
#if defined(HAVE_HWSERIAL10)
        if (rxDev == USART10)
            serialPort = &Serial10;
#endif
#if defined(HAVE_HWSERIALLP1)
        if (rxDev == USART12)
            serialPort = &SerialLP1;
#endif

        if (serialPort != nullptr)
        {
            serialPort->setRx(rx);
            serialPort->setTx(tx);
            return true;
        }
    }
    return false;    
}

void ConfigurableUART::begin(uint32_t baud) noexcept
{
    if(serialPort != nullptr)
    {
        serialPort->begin(baud);
    }
}

void ConfigurableUART::end(void) noexcept
{
    if(serialPort != nullptr)
    {
        serialPort->end();
    }
}

int ConfigurableUART::read(void) noexcept
{
    if(serialPort != nullptr)
    {
        return serialPort->read();
    }

    return -1;
}

int ConfigurableUART::peek(void) noexcept
{
    if(serialPort != nullptr)
    {
        return serialPort->peek();
    }
    
    return -1;
}

int ConfigurableUART::available(void) noexcept
{
    if(serialPort != nullptr)
    {
        return serialPort->available();
    }
    return 0;
}

int ConfigurableUART::availableForWrite(void) noexcept
{
    if(serialPort != nullptr)
    {
        return serialPort->read();
    }
    
    return 0;
}

size_t ConfigurableUART::canWrite() noexcept
{
    if(serialPort != nullptr)
    {
        return serialPort->canWrite();
    }
    return 0;
}

size_t ConfigurableUART::write(const uint8_t ch) noexcept
{
    if(serialPort != nullptr)
    {
        return serialPort->write(ch);
    }

    return 1;
}


size_t ConfigurableUART::write(const uint8_t *buffer, size_t size) noexcept
{
    if(serialPort != nullptr)
    {
        return serialPort->write(buffer, size);
    }

    return size;
}

void ConfigurableUART::flush(void) noexcept
{
    if(serialPort != nullptr)
    {
        serialPort->flush();
    }
}


void ConfigurableUART::setInterruptPriority(uint32_t priority) noexcept
{
    if(serialPort != nullptr)
    {
        serialPort->setInterruptPriority(priority);
    }
}

uint32_t ConfigurableUART::getInterruptPriority() noexcept
{
#if 0
// FIXME
    if(serialPort != nullptr)
    {
        return serialPort->getInterruptPriority();
    }
#endif   
    return 0;
}

bool ConfigurableUART::IsConnected() noexcept
{
    if(serialPort != nullptr) return true;
    return false;
}


// FIXME we should probbaly implement the call back for this!
ConfigurableUART::InterruptCallbackFn ConfigurableUART::SetInterruptCallback(InterruptCallbackFn f) noexcept
{
	InterruptCallbackFn ret = interruptCallback;
	interruptCallback = f;
	return ret;
}

// Get and clear the errors
ConfigurableUART::Errors ConfigurableUART::GetAndClearErrors() noexcept
{
	Errors errs;
    flush();
    errs.uartOverrun = 0;
    if (serialPort != nullptr)
    {
        errs.bufferOverrun = serialPort->_serial.rx_full;
        errs.framing = serialPort->_serial.hw_error;
        serialPort->_serial.hw_error = serialPort->_serial.rx_full = 0;
    }
    else
    {
        errs.bufferOverrun = 0;
        errs.framing = 0;
    }
	return errs;
}
#endif
