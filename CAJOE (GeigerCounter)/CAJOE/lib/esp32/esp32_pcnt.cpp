#include <esp32_pcnt.h>

#if defined(ESP32)

void pcntSetup(gpio_num_t pin, pcnt_unit_t unit, pcnt_channel_t channel) {
    esp_err_t code;
    pinMode((uint8_t)pin, INPUT);
    /* Prepare configuration for the PCNT unit */
    pcnt_config_t pcnt_config = {
        // Set PCNT input signal and control GPIOs
        .pulse_gpio_num = pin,
        .ctrl_gpio_num = PCNT_PIN_NOT_USED,
        // What to do when control input is low or high?
        .lctrl_mode = PCNT_MODE_KEEP,   // Reverse counting direction if low
        .hctrl_mode = PCNT_MODE_KEEP,   // Keep the primary counter mode if high
        // What to do on the positive / negative edge of pulse input?
        .pos_mode = PCNT_COUNT_DIS,   // Keep the counter value on the positive edge
        .neg_mode = PCNT_COUNT_INC,   // Count up on the negative edge
        // Set the maximum and minimum limit values to watch
        .counter_h_lim = 0,
        .counter_l_lim = 0,
        .unit = unit,
        .channel = channel,
    };
    /* Initialize PCNT unit */
    pcnt_unit_config(&pcnt_config);
    pcnt_counter_pause(unit);
    // pcnt_set_filter_value(unit, 10);
    // pcnt_filter_enable(unit);
    pcnt_counter_clear(unit);
    pcnt_counter_resume(unit);
    
    // /* Initialize PCNT's counter */
    // code = pcnt_counter_pause(unit);
    // Serial.println(code);

    // code = pcnt_set_filter_value(unit, 10);
    // code = pcnt_filter_enable(unit);
    

    // pcnt_filter_disable(unit);
    // pcnt_intr_disable(unit);


    // /* Everything is set up, now go to counting */
    // code = pcnt_counter_resume(unit);
    // Serial.println(code);
}


#endif
