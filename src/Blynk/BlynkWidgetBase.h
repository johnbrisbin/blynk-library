/**
 * @file       BlynkWidgetBase.h
 * @author     Volodymyr Shymanskyy
 * @license    This project is released under the MIT License (MIT)
 * @copyright  Copyright (c) 2016 Volodymyr Shymanskyy
 * @date       Nov 2016
 * @brief
 */

#ifndef BlynkWidgetBase_h
#define BlynkWidgetBase_h

#include <Blynk/BlynkApi.h>

template <class BlynkType>
class BlynkWidgetBase
{
public:
    BlynkWidgetBase(BlynkType& blinkEMIn,
    	uint8_t vPin) : blinkEM(blinkEMIn),mPin(vPin) {}
    	
    void setVPin(uint8_t vPin) { mPin = vPin; }

    void onWrite(BlynkReq BLYNK_UNUSED &request, const BlynkParam BLYNK_UNUSED &param) {
        BLYNK_LOG1(BLYNK_F("BlynkWidgetBase::onWrite should not be called"));
    }

    template<typename... Args>
    void setLabel(Args... args) {
        blinkEM.setProperty(mPin, "label", args...);
    }

    template<typename... Args>
    void setColor(Args... args) {
        blinkEM.setProperty(mPin, "color", args...);
    }

protected:
    uint8_t mPin;
    BlynkType& blinkEM;
};

class BlynkAttachWidgetHelper {
public:
    template<typename T>
    explicit BlynkAttachWidgetHelper(T& widget, uint8_t vPin) {
        widget.setVPin(vPin);
    }
};

// Could use __attribute__ ((constructor)), but hope for better portability
#define BLYNK_ATTACH_WIDGET(widget, pin) \
    BlynkAttachWidgetHelper BLYNK_CONCAT2(blnk_widget_helper_, __COUNTER__)((widget), (pin)); \
    BLYNK_WRITE(pin) { (widget).onWrite(request, param); }

#endif
