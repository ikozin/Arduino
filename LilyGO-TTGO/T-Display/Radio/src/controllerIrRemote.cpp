#include "controllerIrRemote.h"


//  -----------------------------------------------------------------------------------------
//  |                                                                                       |
//  |           POWER                       RETURN                      MODE                |
//  |   addr: 0xff00 cmd: 0xba45    addr: 0xff00 cmd: 0xb946    addr: 0xff00 cmd: 0xb847    |
//  |                                                                                       |
//  |           TIME                        SEL                         EQ                  |
//  |   addr: 0xff00 cmd: 0xbb44    addr: 0xff00 cmd: 0xbf40    addr: 0xff00 cmd: 0xbc43    |
//  |                                                                                       |
//  |           PREV                        NEXT                    PLAY/PAUSE              |
//  |   addr: 0xff00 cmd: 0xf807    addr: 0xff00 cmd: 0xea15    addr: 0xff00 cmd: 0xf609    |
//  |                                                                                       |
//  |           VOLUME-                     VOLUME+                         0               |
//  |   addr: 0xff00 cmd: 0xe916    addr: 0xff00 cmd: 0xe619    addr: 0xff00 cmd: 0xf20d    |
//  |                                                                                       |
//  |               1                           2                           3               |
//  |   addr: 0xff00 cmd: 0xf30c    addr: 0xff00 cmd: 0xe718    addr: 0xff00 cmd: 0xa15e    |
//  |                                                                                       |
//  |               4                           5                           6               |
//  |   addr: 0xff00 cmd: 0xf708    addr: 0xff00 cmd: 0xe31c    addr: 0xff00 cmd: 0xa55a    |
//  |                                                                                       |
//  |               7                           8                           9               |
//  |   addr: 0xff00 cmd: 0xbd42    addr: 0xff00 cmd: 0xad52    addr: 0xff00 cmd: 0xb54a    |
//  |                                                                                       |
//  -----------------------------------------------------------------------------------------

// addr: 0xff00 cmd: 0xba45
// addr: 0xff00 cmd: 0xb946
// addr: 0xff00 cmd: 0xb847
// addr: 0xff00 cmd: 0xbb44
// addr: 0xff00 cmd: 0xbf40
// addr: 0xff00 cmd: 0xbc43
// addr: 0xff00 cmd: 0xf807
// addr: 0xff00 cmd: 0xea15
// addr: 0xff00 cmd: 0xf609
// addr: 0xff00 cmd: 0xe916
// addr: 0xff00 cmd: 0xe619
// addr: 0xff00 cmd: 0xf20d
// addr: 0xff00 cmd: 0xf30c
// addr: 0xff00 cmd: 0xe718
// addr: 0xff00 cmd: 0xa15e
// addr: 0xff00 cmd: 0xf708
// addr: 0xff00 cmd: 0xe31c
// addr: 0xff00 cmd: 0xa55a
// addr: 0xff00 cmd: 0xbd42
// addr: 0xff00 cmd: 0xad52
// addr: 0xff00 cmd: 0xb54a


// static rmt_channel_t example_tx_channel = RMT_CHANNEL_0;
static rmt_channel_t rx_channel = RMT_CHANNEL_0;

ControllerIrRemote::ControllerIrRemote(const char* name, gpio_num_t pin, rmt_channel_t channel, SemaphoreHandle_t updateEvent) :
                        ControllerT(name, updateEvent) {
    _pin = pin;
    _channel = channel;
    _addr = 0;
    _cmd = 0;
    _repeat = false;
    _ir_parser = nullptr;
    _rb = nullptr;
}

InitResponse_t ControllerIrRemote::OnInit() {
    esp_err_t err;
    rmt_config_t rmt_rx_config = RMT_DEFAULT_CONFIG_RX(_pin, _channel);
    err = rmt_config(&rmt_rx_config);
    // LOGN("%s::rmt_config: %d", _name, err);

    err = rmt_driver_install(_channel, 1000/*2048*/, 0);
    // LOGN("%s::rmt_driver_install: %d", _name, err);
    ir_parser_config_t ir_parser_config = IR_PARSER_DEFAULT_CONFIG((ir_dev_t)_channel);
    ir_parser_config.flags |= IR_TOOLS_FLAGS_PROTO_EXT; // Using extended IR protocols (both NEC and RC5 have extended version)
    _ir_parser = ir_parser_rmt_new_nec(&ir_parser_config);
    //get RMT RX ringbuffer
    err = rmt_get_ringbuf_handle(_channel, &_rb);
    // LOGN("%s::rmt_get_ringbuf_handle: %d", _name, err);
    assert(_rb != nullptr);
    // Start receive
    rmt_rx_start(_channel, true);

    return OnInitResultStart;
}

void ControllerIrRemote::OnDone() {
    _ir_parser->del(_ir_parser);
    rmt_driver_uninstall(_channel);
}

IterationCode_t ControllerIrRemote::OnIteration() {
    IterationCode_t result = IterationCode_t::Skip;
    size_t length = 0;
    rmt_item32_t *items = nullptr;
    items = (rmt_item32_t *) xRingbufferReceive(_rb, &length, portMAX_DELAY);
    if (items) {
        length /= 4; // one RMT = 4 Bytes
        if (_ir_parser->input(_ir_parser, items, length) == ESP_OK) {
            _addr = _cmd = 0;
            _repeat = false;
            if (_ir_parser->get_scan_code(_ir_parser, &_addr, &_cmd, &_repeat) == ESP_OK) {
                LOGN("%s::Scan Code %s --- addr: 0x%04x cmd: 0x%04x", _name, _repeat ? "(repeat)" : "", _addr, _cmd);
                result = IterationCode_t::Ok;
            }
        }
        //after parsing the data, return spaces to ringbuffer.
        vRingbufferReturnItem(_rb, (void *) items);
    }
    return result;
}
