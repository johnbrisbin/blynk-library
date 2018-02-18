/**
 * @file       BlynkHandlers.h
 * @author     Volodymyr Shymanskyy
 * @license    This project is released under the MIT License (MIT)
 * @copyright  Copyright (c) 2015 Volodymyr Shymanskyy
 * @date       Jan 2015
 * @brief      Handlers for virtual pin operations
 *
 */

#ifndef BlynkHandlers_h
#define BlynkHandlers_h

#include <Blynk/BlynkConfig.h>
#include <Blynk/BlynkParam.h>

// Helper macro

#define V0  0
#define V1  1
#define V2  2
#define V3  3
#define V4  4
#define V5  5
#define V6  6
#define V7  7
#define V8  8
#define V9  9
#define V10 10
#define V11 11
#define V12 12
#define V13 13
#define V14 14
#define V15 15
#define V16 16
#define V17 17
#define V18 18
#define V19 19
#define V20 20
#define V21 21
#define V22 22
#define V23 23
#define V24 24
#define V25 25
#define V26 26
#define V27 27
#define V28 28
#define V29 29
#define V30 30
#define V31 31
#ifdef BLYNK_USE_128_VPINS
  #define V32 32
  #define V33 33
  #define V34 34
  #define V35 35
  #define V36 36
  #define V37 37
  #define V38 38
  #define V39 39
  #define V40 40
  #define V41 41
  #define V42 42
  #define V43 43
  #define V44 44
  #define V45 45
  #define V46 46
  #define V47 47
  #define V48 48
  #define V49 49
  #define V50 50
  #define V51 51
  #define V52 52
  #define V53 53
  #define V54 54
  #define V55 55
  #define V56 56
  #define V57 57
  #define V58 58
  #define V59 59
  #define V60 60
  #define V61 61
  #define V62 62
  #define V63 63
  #define V64 64
  #define V65 65
  #define V66 66
  #define V67 67
  #define V68 68
  #define V69 69
  #define V70 70
  #define V71 71
  #define V72 72
  #define V73 73
  #define V74 74
  #define V75 75
  #define V76 76
  #define V77 77
  #define V78 78
  #define V79 79
  #define V80 80
  #define V81 81
  #define V82 82
  #define V83 83
  #define V84 84
  #define V85 85
  #define V86 86
  #define V87 87
  #define V88 88
  #define V89 89
  #define V90 90
  #define V91 91
  #define V92 92
  #define V93 93
  #define V94 94
  #define V95 95
  #define V96 96
  #define V97 97
  #define V98 98
  #define V99 99
  #define V100 100
  #define V101 101
  #define V102 102
  #define V103 103
  #define V104 104
  #define V105 105
  #define V106 106
  #define V107 107
  #define V108 108
  #define V109 109
  #define V110 110
  #define V111 111
  #define V112 112
  #define V113 113
  #define V114 114
  #define V115 115
  #define V116 116
  #define V117 117
  #define V118 118
  #define V119 119
  #define V120 120
  #define V121 121
  #define V122 122
  #define V123 123
  #define V124 124
  #define V125 125
  #define V126 126
  #define V127 127
#endif

// Initial syntax:
#define BLYNK_WRITE(ROLE,PIN,CODE) \
    ROLE.registerWriteHandler([](BlynkReq BLYNK_UNUSED &request, const BlynkParam BLYNK_UNUSED &param) -> void CODE,PIN)

#define BLYNK_READ(ROLE,PIN,CODE)  \
    role.registerReadHandler([](BlynkReq BLYNK_UNUSED &request) -> void CODE,PIN)

#define BlynkWidgetRead
#define BlynkWidgetWrite
// New, more readable syntax:
#define BLYNK_IN_2(pin)  \
    void BlynkWidgetWrite ## pin (BlynkReq BLYNK_UNUSED &request, const BlynkParam BLYNK_UNUSED &getValue)

#define BLYNK_OUT_2(pin) \
    void BlynkWidgetRead ## pin  (BlynkReq BLYNK_UNUSED &request)

#define BLYNK_INPUT_DEFAULT()   BLYNK_IN_2(Default)
#define BLYNK_OUTPUT_DEFAULT()  BLYNK_OUT_2(Default)

#define BLYNK_INPUT(pin)        BLYNK_IN_2(pin)
#define BLYNK_OUTPUT(pin)       BLYNK_OUT_2(pin)

// Additional handlers
#define BLYNK_CONNECTED()    void BlynkOnConnected()
#define BLYNK_DISCONNECTED() void BlynkOnDisconnected()

// Advanced functions

#define BLYNK_VAR_INT(name, pin) \
    int name;  \
    BLYNK_WRITE(pin) { name = param.asInt(); } \
    BLYNK_READ(pin)  { Blynk.virtualWrite(pin, name); }

#define BLYNK_VAR_LONG(name, pin) \
    long name;  \
    BLYNK_WRITE(pin) { name = param.asLong(); } \
    BLYNK_READ(pin)  { Blynk.virtualWrite(pin, name); }

#ifndef BLYNK_NO_FLOAT
#define BLYNK_VAR_DOUBLE(name, pin) \
    double name;  \
    BLYNK_WRITE(pin) { name = param.asDouble(); } \
    BLYNK_READ(pin)  { Blynk.virtualWrite(pin, name); }
#endif

#ifdef ARDUINO
#define BLYNK_VAR_STRING(name, pin) \
    String name;  \
    BLYNK_WRITE(pin) { name = param.asStr(); } \
    BLYNK_READ(pin)  { Blynk.virtualWrite(pin, name); }
#endif

// Default read/write handlers (you can redefine them in your code)
#ifdef __cplusplus
extern "C" {
#endif

struct BlynkReq
{
    uint8_t pin;
};

typedef void (*WidgetReadHandler)(BlynkReq &request);
typedef void (*WidgetWriteHandler)(BlynkReq &request, const BlynkParam &param);

WidgetReadHandler GetReadHandler(uint8_t pin);
WidgetWriteHandler GetWriteHandler(uint8_t pin);

void BlynkNoOpCbk();

// Declare all pin handlers (you can redefine them in your code)
BLYNK_CONNECTED();
BLYNK_DISCONNECTED();

void BlynkWidgetReadDefault(BlynkReq BLYNK_UNUSED &request);
void BlynkWidgetWriteDefault(BlynkReq BLYNK_UNUSED &request, const BlynkParam BLYNK_UNUSED &param);
void BlynkWidgetWriteInternalPinRTC(BlynkReq BLYNK_UNUSED &request, const BlynkParam BLYNK_UNUSED &param);
void BlynkWidgetWriteInternalPinOTA(BlynkReq BLYNK_UNUSED &request, const BlynkParam BLYNK_UNUSED &param);
void BlynkWidgetWriteInternalPinACON(BlynkReq BLYNK_UNUSED &request, const BlynkParam BLYNK_UNUSED &param);
void BlynkWidgetWriteInternalPinADIS(BlynkReq BLYNK_UNUSED &request, const BlynkParam BLYNK_UNUSED &param);
// Aliases
#define BLYNK_APP_CONNECTED()    void BlynkWidgetWriteInternalPinACON(BlynkReq BLYNK_UNUSED &request, const BlynkParam BLYNK_UNUSED &param)
#define BLYNK_APP_DISCONNECTED() void BlynkWidgetWriteInternalPinADIS(BlynkReq BLYNK_UNUSED &request, const BlynkParam BLYNK_UNUSED &param)

#ifdef __cplusplus
}
#endif

#endif
