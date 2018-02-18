/**
 * @file       BlynkHandlers.cpp
 * @author     Volodymyr Shymanskyy
 * @license    This project is released under the MIT License (MIT)
 * @copyright  Copyright (c) 2015 Volodymyr Shymanskyy
 * @date       Jan 2015
 * @brief      Virtual pin utilities
 */

#include <Blynk/BlynkConfig.h>
#include <Blynk/BlynkHandlers.h>
#include <Blynk/BlynkDebug.h>

#ifdef __cplusplus
extern "C" {
#endif
void BlynkNoOpCbk()
{}

void BlynkWidgetReadDefault(BlynkReq BLYNK_UNUSED &request)
{
    BLYNK_LOG2(BLYNK_F("No handler for reading from pin "), request.pin);
}

void BlynkWidgetWriteDefault(BlynkReq BLYNK_UNUSED &request, const BlynkParam BLYNK_UNUSED &param)
{
    BLYNK_LOG2(BLYNK_F("No handler for writing to pin "), request.pin);
}

#define BLYNK_ON_READ_IMPL(pin)  void BlynkWidgetRead ## pin (BlynkReq BLYNK_UNUSED &req) \
          __attribute__((weak, alias("BlynkWidgetReadDefault")))

#define BLYNK_ON_WRITE_IMPL(pin) void BlynkWidgetWrite ## pin (BlynkReq BLYNK_UNUSED &req, const BlynkParam BLYNK_UNUSED &param) \
          __attribute__((weak, alias("BlynkWidgetWriteDefault")))
BLYNK_CONNECTED() __attribute__((weak, alias("BlynkNoOpCbk")));
BLYNK_DISCONNECTED() __attribute__((weak, alias("BlynkNoOpCbk")));

// Internal Virtual Pins
BLYNK_ON_WRITE_IMPL(InternalPinACON);
BLYNK_ON_WRITE_IMPL(InternalPinADIS);
BLYNK_ON_WRITE_IMPL(InternalPinRTC);
BLYNK_ON_WRITE_IMPL(InternalPinOTA);
#ifdef __cplusplus
} // "C"
#endif
