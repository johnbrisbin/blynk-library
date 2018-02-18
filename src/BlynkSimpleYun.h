/**
 * @file       BlynkSimpleYun.h
 * @author     Volodymyr Shymanskyy
 * @license    This project is released under the MIT License (MIT)
 * @copyright  Copyright (c) 2015 Volodymyr Shymanskyy
 * @date       Mar 2015
 * @brief
 *
 */

#ifndef BlynkSimpleYun_h
#define BlynkSimpleYun_h

#include <Blynk/BlynkProtocol.h>
#include <Adapters/BlynkArduinoClient.h>
#include <BridgeClient.h>

typedef BlynkArduinoClient BlynkArduinoClientYun;

class BlynkYun
    : public BlynkProtocol< BlynkArduinoClientYun, BlynkYun >
{
    typedef BlynkProtocol< BlynkArduinoClientYun, BlynkYun > Base;
public:
    BlynkYun(BlynkArduinoClientYun& transp)
        : Base(transp)
    {}

    void config(const char* auth,
                const char* domain = BLYNK_DEFAULT_DOMAIN,
                uint16_t    port   = BLYNK_DEFAULT_PORT)
    {
        Base::begin(auth);
        this->conn.begin(domain, port);
    }

    void config(const char* auth,
                IPAddress   ip,
                uint16_t    port = BLYNK_DEFAULT_PORT)
    {
        Base::begin(auth);
        this->conn.begin(ip, port);
    }

    void begin(const char* auth,
               const char* domain = BLYNK_DEFAULT_DOMAIN,
               uint16_t    port   = BLYNK_DEFAULT_PORT)
    {
        BLYNK_LOG1(BLYNK_F("Bridge init..."));
        Bridge.begin();
        config(auth, domain, port);
        while(this->connect() != true) {}
    }

    void begin(const char* auth,
               IPAddress   ip,
               uint16_t    port = BLYNK_DEFAULT_PORT)
    {
        BLYNK_LOG1(BLYNK_F("Bridge init..."));
        Bridge.begin();
        config(auth, ip, port);
        while(this->connect() != true) {}
    }
    
    void registerReadHandler(WidgetReadHandler h,uint8_t pin)
    {
        BlynkApi<BlynkProtocol<BlynkArduinoClientYun,BlynkYun>,BlynkYun>::registerReadHandler( h, pin);
    }
    
    void registerWriteHandler(WidgetWriteHandler h,uint8_t pin)
    {
        BlynkApi<BlynkProtocol<BlynkArduinoClientYun,BlynkYun>,BlynkYun>::registerWriteHandler( h, pin);
    }

};

#define MakeBlynk(varname) BlynkYun varname(* new BlynkArduinoClient(* new BridgeClient()))
#define BLYNKEM_TYPE	BlynkYun

#include <BlynkWidgets.h>

#endif
