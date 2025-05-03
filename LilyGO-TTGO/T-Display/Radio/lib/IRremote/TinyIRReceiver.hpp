/*
 *  TinyIRReceiver.hpp
 *
 *  Receives IR data of NEC protocol using pin change interrupts.
 *  NEC is the protocol of most cheap remote controls for Arduino.
 *
 *  Parity check is done for address and data.
 *  On a completely received IR command, the user function handleReceivedIRData(uint8_t aAddress, uint8_t aCommand, uint8_t aFlags)
 *  is called in interrupt context but with interrupts being enabled to enable use of delay() etc.
 *  !!!!!!!!!!!!!!!!!!!!!!
 *  Functions called in interrupt context should be running as short as possible,
 *  so if you require longer action, save the data (address + command) and handle them in the main loop.
 *  !!!!!!!!!!!!!!!!!!!!!
 *  aFlags can contain one of IRDATA_FLAGS_EMPTY, IRDATA_FLAGS_IS_REPEAT and IRDATA_FLAGS_PARITY_FAILED bits
 *
 * The FAST protocol is a proprietary modified JVC protocol without address, with parity and with a shorter header.
 *  FAST Protocol characteristics:
 * - Bit timing is like NEC or JVC
 * - The header is shorter, 3156 vs. 12500
 * - No address and 16 bit data, interpreted as 8 bit command and 8 bit inverted command,
 *     leading to a fixed protocol length of (6 + (16 * 3) + 1) * 526 = 55 * 526 = 28930 microseconds or 29 ms.
 * - Repeats are sent as complete frames but in a 50 ms period / with a 21 ms distance.
 *
 *
 *  This file is part of IRMP https://github.com/IRMP-org/IRMP.
 *  This file is part of Arduino-IRremote https://github.com/Arduino-IRremote/Arduino-IRremote.
 *
 ************************************************************************************
 * MIT License
 *
 * Copyright (c) 2022-2024 Armin Joachimsmeyer
 *
 * Permission is hereby granted, free of charge, to any person obtaining a copy
 * of this software and associated documentation files (the "Software"), to deal
 * in the Software without restriction, including without limitation the rights
 * to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
 * copies of the Software, and to permit persons to whom the Software is furnished
 * to do so, subject to the following conditions:
 *
 * The above copyright notice and this permission notice shall be included in all
 * copies or substantial portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR IMPLIED,
 * INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY, FITNESS FOR A
 * PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT
 * HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER IN AN ACTION OF
 * CONTRACT, TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE
 * OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.
 *
 ************************************************************************************
 */

/*
 * This library can be configured at compile time by the following options / macros:
 * For more details see: https://github.com/Arduino-IRremote/Arduino-IRremote#compile-options--macros-for-this-library (scroll down)
 *
 * - IR_RECEIVE_PIN         The pin number for TinyIRReceiver IR input.
 * - IR_FEEDBACK_LED_PIN    The pin number for TinyIRReceiver feedback LED.
 * - NO_LED_FEEDBACK_CODE   Disables the feedback LED function. Saves 14 bytes program memory.
 * - DISABLE_PARITY_CHECKS  Disable parity checks. Saves 48 bytes of program memory.
 * - USE_EXTENDED_NEC_PROTOCOL Like NEC, but take the 16 bit address as one 16 bit value and not as 8 bit normal and 8 bit inverted value.
 * - USE_ONKYO_PROTOCOL     Like NEC, but take the 16 bit address and command each as one 16 bit value and not as 8 bit normal and 8 bit inverted value.
 * - USE_FAST_PROTOCOL      Use FAST protocol (no address and 16 bit data, interpreted as 8 bit command and 8 bit inverted command) instead of NEC.
 * - ENABLE_NEC2_REPEATS    Instead of sending / receiving the NEC special repeat code, send / receive the original frame for repeat.
 * - USE_CALLBACK_FOR_TINY_RECEIVER   Call the user provided function "void handleReceivedTinyIRData()" each time a frame or repeat is received.
 */

#ifndef _TINY_IR_RECEIVER_HPP
#define _TINY_IR_RECEIVER_HPP

#include <Arduino.h>

/*
 * Protocol selection
 */
//#define DISABLE_PARITY_CHECKS // Disable parity checks. Saves 48 bytes of program memory.
//#define USE_EXTENDED_NEC_PROTOCOL // Like NEC, but take the 16 bit address as one 16 bit value and not as 8 bit normal and 8 bit inverted value.
//#define USE_ONKYO_PROTOCOL    // Like NEC, but take the 16 bit address and command each as one 16 bit value and not as 8 bit normal and 8 bit inverted value.
//#define USE_FAST_PROTOCOL     // Use FAST protocol instead of NEC / ONKYO.
//#define ENABLE_NEC2_REPEATS // Instead of sending / receiving the NEC special repeat code, send / receive the original frame for repeat.
#include "TinyIR.h"

#include "digitalWriteFast.h"
/** \addtogroup TinyReceiver Minimal receiver for NEC and FAST protocol
 * @{
 */

TinyIRReceiverStruct TinyIRReceiverControl;
volatile TinyIRReceiverCallbackDataStruct TinyIRReceiverData;

/**
 * Declaration of the callback function provided by the user application.
 * It is called every time a complete IR command or repeat was received.
 */
extern void handleReceivedTinyIRData(void* parameter);

/**
 * The ISR (Interrupt Service Routine) of TinyIRRreceiver.
 * It handles the NEC protocol decoding and calls the user callback function on complete.
 * 5 us + 3 us for push + pop for a 16MHz ATmega
 */
IRAM_ATTR void IRPinChangeInterruptHandler(void* parameter) {
    /*
     * Save IR input level
     * Negative logic, true / HIGH means inactive / IR space, LOW / false means IR mark.
     */
    uint_fast8_t tIRLevel = digitalReadFast(IR_RECEIVE_PIN);

    /*
     * 1. compute microseconds after last change
     */
    // Repeats can be sent after a pause, which is longer than 64000 microseconds, so we need a 32 bit value for check of repeats
    uint32_t tCurrentMicros = micros();
    uint32_t tMicrosOfMarkOrSpace32 = tCurrentMicros - TinyIRReceiverControl.LastChangeMicros;
    uint16_t tMicrosOfMarkOrSpace = tMicrosOfMarkOrSpace32;

    TinyIRReceiverControl.LastChangeMicros = tCurrentMicros;

    uint8_t tState = TinyIRReceiverControl.IRReceiverState;

    if (tIRLevel == LOW) {
        /*
         * We have a mark here
         */
        if (tMicrosOfMarkOrSpace > 2 * TINY_RECEIVER_HEADER_MARK) {
            // timeout -> must reset state machine
            tState = IR_RECEIVER_STATE_WAITING_FOR_START_MARK;
        }
        if (tState == IR_RECEIVER_STATE_WAITING_FOR_START_MARK) {
            // We are at the beginning of the header mark, check timing at the next transition
            tState = IR_RECEIVER_STATE_WAITING_FOR_START_SPACE;
            TinyIRReceiverControl.Flags = IRDATA_FLAGS_EMPTY; // If we do it here, it saves 4 bytes
#if defined(ENABLE_NEC2_REPEATS)
            // Check for repeat, where full frame is sent again after TINY_RECEIVER_REPEAT_PERIOD ms
            // Not required for NEC, where repeats are detected by a special header space duration
            // Must use 32 bit arithmetic here!
            if (tMicrosOfMarkOrSpace32 < TINY_RECEIVER_MAXIMUM_REPEAT_DISTANCE) {
                TinyIRReceiverControl.Flags = IRDATA_FLAGS_IS_REPEAT;
            }
#endif
        }

        else if (tState == IR_RECEIVER_STATE_WAITING_FOR_FIRST_DATA_MARK) {
            if (tMicrosOfMarkOrSpace >= lowerValue25Percent(TINY_RECEIVER_HEADER_SPACE)
                    && tMicrosOfMarkOrSpace <= upperValue25Percent(TINY_RECEIVER_HEADER_SPACE)) {
                /*
                 * We had a valid data header space here -> initialize data
                 */
                TinyIRReceiverControl.IRRawDataBitCounter = 0;
#if (TINY_RECEIVER_BITS > 16)
                TinyIRReceiverControl.IRRawData.ULong = 0;
#else
                TinyIRReceiverControl.IRRawData.UWord = 0;
#endif
                TinyIRReceiverControl.IRRawDataMask = 1;
                tState = IR_RECEIVER_STATE_WAITING_FOR_DATA_SPACE;
#if !defined(ENABLE_NEC2_REPEATS)
                // Check for NEC repeat header
            } else if (tMicrosOfMarkOrSpace >= lowerValue25Percent(NEC_REPEAT_HEADER_SPACE)
                    && tMicrosOfMarkOrSpace <= upperValue25Percent(NEC_REPEAT_HEADER_SPACE)
                    && TinyIRReceiverControl.IRRawDataBitCounter >= TINY_RECEIVER_BITS) {
                /*
                 * We have a repeat header here and no broken receive before -> set repeat flag
                 */
                TinyIRReceiverControl.Flags = IRDATA_FLAGS_IS_REPEAT;
                tState = IR_RECEIVER_STATE_WAITING_FOR_DATA_SPACE;
#endif
            } else {
                // This parts are optimized by the compiler into jumps to one code :-)
                // Wrong length -> reset state
                tState = IR_RECEIVER_STATE_WAITING_FOR_START_MARK;
            }
        }

        else if (tState == IR_RECEIVER_STATE_WAITING_FOR_DATA_MARK) {
            // Check data space length
            if (tMicrosOfMarkOrSpace >= lowerValue50Percent(TINY_RECEIVER_ZERO_SPACE)
                    && tMicrosOfMarkOrSpace <= upperValue50Percent(TINY_RECEIVER_ONE_SPACE)) {
                // We have a valid bit here
                tState = IR_RECEIVER_STATE_WAITING_FOR_DATA_SPACE;
                if (tMicrosOfMarkOrSpace >= 2 * TINY_RECEIVER_UNIT) {
                    // we received a 1
#if (TINY_RECEIVER_BITS > 16)
                    TinyIRReceiverControl.IRRawData.ULong |= TinyIRReceiverControl.IRRawDataMask;
#else
                    TinyIRReceiverControl.IRRawData.UWord |= TinyIRReceiverControl.IRRawDataMask;
#endif
                } else {
                    // we received a 0 - empty code for documentation
                }
                // prepare for next bit
                TinyIRReceiverControl.IRRawDataMask = TinyIRReceiverControl.IRRawDataMask << 1;
                TinyIRReceiverControl.IRRawDataBitCounter++;
            } else {
                // Wrong length -> reset state
                tState = IR_RECEIVER_STATE_WAITING_FOR_START_MARK;
            }
        } else {
            // error wrong state for the received level, e.g. if we missed one change interrupt -> reset state
            tState = IR_RECEIVER_STATE_WAITING_FOR_START_MARK;
        }
    }

    else {
        /*
         * We have a space here
         */
        if (tState == IR_RECEIVER_STATE_WAITING_FOR_START_SPACE) {
            /*
             * Check length of header mark here
             */
            if (tMicrosOfMarkOrSpace >= lowerValue25Percent(TINY_RECEIVER_HEADER_MARK)
                    && tMicrosOfMarkOrSpace <= upperValue25Percent(TINY_RECEIVER_HEADER_MARK)) {
                tState = IR_RECEIVER_STATE_WAITING_FOR_FIRST_DATA_MARK;
            } else {
                // Wrong length of header mark -> reset state
                tState = IR_RECEIVER_STATE_WAITING_FOR_START_MARK;
            }
        }

        else if (tState == IR_RECEIVER_STATE_WAITING_FOR_DATA_SPACE) {
            // Check data mark length
            if (tMicrosOfMarkOrSpace >= lowerValue50Percent(TINY_RECEIVER_BIT_MARK)
                    && tMicrosOfMarkOrSpace <= upperValue50Percent(TINY_RECEIVER_BIT_MARK)) {
                /*
                 * We have a valid mark here, check for transmission complete, i.e. the mark of the stop bit
                 */
                if (TinyIRReceiverControl.IRRawDataBitCounter >= TINY_RECEIVER_BITS
#if !defined(ENABLE_NEC2_REPEATS)
                        || (TinyIRReceiverControl.Flags & IRDATA_FLAGS_IS_REPEAT) // Do not check for full length received, if we have a short repeat frame
#endif
                        ) {
                    /*
                     * Code complete -> optionally check parity
                     */
                    // Reset state for new start
                    tState = IR_RECEIVER_STATE_WAITING_FOR_START_MARK;

#if !defined(DISABLE_PARITY_CHECKS) && (TINY_RECEIVER_ADDRESS_BITS == 16) && TINY_RECEIVER_ADDRESS_HAS_8_BIT_PARITY
                    /*
                     * Check address parity
                     * Address is sent first and contained in the lower word
                     */
                    if (TinyIRReceiverControl.IRRawData.UBytes[0] != (uint8_t)(~TinyIRReceiverControl.IRRawData.UBytes[1])) {
#if defined(ENABLE_NEC2_REPEATS)
                    TinyIRReceiverControl.Flags |= IRDATA_FLAGS_PARITY_FAILED; // here we can have the repeat flag already set
#else
                        TinyIRReceiverControl.Flags = IRDATA_FLAGS_PARITY_FAILED; // here we do not check anything, if we have a repeat
#endif
                    }
#endif
#if !defined(DISABLE_PARITY_CHECKS) && (TINY_RECEIVER_COMMAND_BITS == 16) && TINY_RECEIVER_COMMAND_HAS_8_BIT_PARITY
                    /*
                     * Check command parity
                     */
#if (TINY_RECEIVER_ADDRESS_BITS > 0)
                    if (TinyIRReceiverControl.IRRawData.UBytes[2] != (uint8_t)(~TinyIRReceiverControl.IRRawData.UBytes[3])) {
#if defined(ENABLE_NEC2_REPEATS)
                    TinyIRReceiverControl.Flags |= IRDATA_FLAGS_PARITY_FAILED;
#else
                        TinyIRReceiverControl.Flags = IRDATA_FLAGS_PARITY_FAILED;
#endif

#else
                    // No address, so command and parity are in the lowest bytes
                    if (TinyIRReceiverControl.IRRawData.UBytes[0] != (uint8_t) (~TinyIRReceiverControl.IRRawData.UBytes[1])) {
                        TinyIRReceiverControl.Flags |= IRDATA_FLAGS_PARITY_FAILED;
#endif
                    }
#endif
                    /*
                     * Call user provided callback here
                     * The parameter size is dependent of the code variant used in order to save program memory.
                     * We have 6 cases: 0, 8 bit or 16 bit address, each with 8 or 16 bit command
                     */
                    TinyIRReceiverData.justWritten = true;
                    TinyIRReceiverData.Flags = TinyIRReceiverControl.Flags;
#if (TINY_RECEIVER_ADDRESS_BITS > 0)
#  if TINY_RECEIVER_ADDRESS_HAS_8_BIT_PARITY
                    // Here we have 8 bit address
                    TinyIRReceiverData.Address = TinyIRReceiverControl.IRRawData.UBytes[0];
#  else
                    // Here we have 16 bit address
                    TinyIRReceiverData.Address = TinyIRReceiverControl.IRRawData.UWord.LowWord;
#  endif
#  if TINY_RECEIVER_COMMAND_HAS_8_BIT_PARITY
                    // Here we have 8 bit command
                    TinyIRReceiverData.Command = TinyIRReceiverControl.IRRawData.UBytes[2];
#  else
                    // Here we have 16 bit command
                    TinyIRReceiverData.Command = TinyIRReceiverControl.IRRawData.UWord.HighWord;
#  endif

#else
                    // Here we have NO address
#  if TINY_RECEIVER_COMMAND_HAS_8_BIT_PARITY
                    // Here we have 8 bit command
                    TinyIRReceiverData.Command = TinyIRReceiverControl.IRRawData.UBytes[0];
#  else
                    // Here we have 16 bit command
                    TinyIRReceiverData.Command = TinyIRReceiverControl.IRRawData.UWord;
#  endif
#endif
                    handleReceivedTinyIRData(parameter);
                } else {
                    // not finished yet
                    tState = IR_RECEIVER_STATE_WAITING_FOR_DATA_MARK;
                }
            } else {
                // Wrong length -> reset state
                tState = IR_RECEIVER_STATE_WAITING_FOR_START_MARK;
            }
        } else {
            // error wrong state for the received level, e.g. if we missed one change interrupt -> reset state
            tState = IR_RECEIVER_STATE_WAITING_FOR_START_MARK;
        }
    }

    TinyIRReceiverControl.IRReceiverState = tState;
#ifdef _IR_MEASURE_TIMING
    digitalWriteFast(_IR_TIMING_TEST_PIN, LOW); // 2 clock cycles
#endif
}

bool isTinyReceiverIdle() {
    return (TinyIRReceiverControl.IRReceiverState == IR_RECEIVER_STATE_WAITING_FOR_START_MARK);
}

/*
 * Function to be used as drop in for IrReceiver.decode()
 */
bool TinyReceiverDecode() {
    bool tJustWritten = TinyIRReceiverData.justWritten;
    if (tJustWritten) {
        TinyIRReceiverData.justWritten = false;
    }
    return tJustWritten;
}

/*
 * Checks if IR_RECEIVE_PIN is connected and high
 * @return true, if IR Receiver is attached
 */
bool isIRReceiverAttachedForTinyReceiver() {
    pinModeFast(IR_RECEIVE_PIN, OUTPUT);
    digitalWriteFast(IR_RECEIVE_PIN, LOW); // discharge pin capacity
    pinModeFast(IR_RECEIVE_PIN, INPUT);
    return digitalRead(IR_RECEIVE_PIN); // use slow digitalRead here, since the pin capacity is not fully charged again if we use digitalReadFast.
}

/**
 * Sets IR_RECEIVE_PIN mode to INPUT, and if IR_FEEDBACK_LED_PIN is defined, sets feedback LED output mode.
 * Then call enablePCIInterruptForTinyReceiver()
 */
bool initPCIInterruptForTinyReceiver(void* parameter) {
    pinModeFast(IR_RECEIVE_PIN, INPUT);

#if !defined(NO_LED_FEEDBACK_CODE) && defined(IR_FEEDBACK_LED_PIN)
    pinModeFast(IR_FEEDBACK_LED_PIN, OUTPUT);
#endif
    return enablePCIInterruptForTinyReceiver(parameter);
}

#if defined (LOCAL_DEBUG_ATTACH_INTERRUPT) && !defined(STR)
// Helper macro for getting a macro definition as string
#define STR_HELPER(x) #x
#define STR(x) STR_HELPER(x)
#endif

/**************************************************
 * Pin to interrupt mapping for different platforms
 **************************************************/
// Default for all NON AVR platforms
#define USE_ATTACH_INTERRUPT

// https://docs.espressif.com/projects/esp-idf/en/stable/esp32/api-reference/peripherals/gpio.html
void attachInterruptArgExt(gpio_num_t pin, void (*handler)(void*), void * arg, gpio_int_type_t mode) {
    // gpio_install_isr_service(0);
    gpio_reset_pin(pin);
    gpio_isr_handler_remove(pin);
    gpio_pad_select_gpio(pin);
    gpio_set_direction(pin, GPIO_MODE_INPUT);
    gpio_set_pull_mode(pin, GPIO_FLOATING); 
    gpio_set_intr_type(pin, mode);
    gpio_intr_enable(pin);

    gpio_isr_handler_add(pin, handler, arg);
}


/**
 * Initializes hardware interrupt generation according to IR_RECEIVE_PIN or use attachInterrupt() function.
 * @return true if interrupt was successfully enabled
 */
bool enablePCIInterruptForTinyReceiver(void* parameter) {
    if(digitalPinToInterrupt(IR_RECEIVE_PIN) == NOT_AN_INTERRUPT){
        return false;
    }
    attachInterruptArgExt(IR_RECEIVE_PIN, IRPinChangeInterruptHandler, parameter, GPIO_INTR_ANYEDGE);
    return true;
}

void disablePCIInterruptForTinyReceiver() {
    // detachInterrupt(IR_RECEIVE_PIN);
}

void dummyFunctionToAvoidCompilerErrors() {
    IRPinChangeInterruptHandler(nullptr);
}

/** @}*/

#if defined(LOCAL_DEBUG_ATTACH_INTERRUPT)
#undef LOCAL_DEBUG_ATTACH_INTERRUPT
#endif
#if defined(LOCAL_TRACE_STATE_MACHINE)
#undef LOCAL_TRACE_STATE_MACHINE
#endif

#if defined(LOCAL_DEBUG)
#undef LOCAL_DEBUG
#endif
#endif // _TINY_IR_RECEIVER_HPP
