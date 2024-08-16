import esphome.codegen as cg
import esphome.config_validation as cv
from esphome import automation
from esphome.components import i2c
from esphome.const import CONF_ID, CONF_VOLUME

DEPENDENCIES = ["i2c"]
CONF_BAND = "band"
CONF_MUTE = "mute"

radio_ns = cg.esphome_ns.namespace("radio")
radio = radio_ns.class_("Radio", cg.Component, i2c.I2CDevice)

SetVolumeAction = radio_ns.class_("SetVolumeAction", automation.Action)
VolumeUpAction = radio_ns.class_("VolumeUpAction", automation.Action)
VolumeDownAction = radio_ns.class_("VolumeDownAction", automation.Action)
SetMuteAction = radio_ns.class_("SetMuteAction", automation.Action)
ToggleMuteAction = radio_ns.class_("ToggleMuteAction", automation.Action)
SetBandAction = radio_ns.class_("SetBandAction", automation.Action)

CONFIG_SCHEMA = cv.All(
    cv.Schema(
        {
            cv.GenerateID(): cv.declare_id(radio),
            cv.Optional(CONF_BAND, default=1018): cv.int_,
            cv.Optional(CONF_VOLUME, default=0): cv.int_,
            cv.Optional(CONF_MUTE, default=True): cv.boolean,
        }
    )
    .extend(cv.COMPONENT_SCHEMA)
    .extend(i2c.i2c_device_schema(default_address=0x11)),
)

async def to_code(config):
    var = cg.new_Pvariable(config[CONF_ID])
    await i2c.register_i2c_device(var, config)
    await cg.register_component(var, config)
    cg.add(var.set_band(config[CONF_BAND]))
    cg.add(var.set_volume(config[CONF_VOLUME]))
    cg.add(var.set_mute(config[CONF_MUTE]))


@automation.register_action(
    "radio.set_volume",
    SetVolumeAction,
    cv.maybe_simple_value(
        {
            cv.GenerateID(): cv.use_id(radio),
            cv.Required(CONF_VOLUME): cv.templatable(cv.int_),
        },
        key=CONF_VOLUME,
    ),
)
async def radio_set_volume_to_code(config, action_id, template_arg, args):
    var = cg.new_Pvariable(action_id, template_arg)
    await cg.register_parented(var, config[CONF_ID])
    template_ = await cg.templatable(config[CONF_VOLUME], args, int)
    cg.add(var.set_volume(template_))
    return var


@automation.register_action(
    "radio.volume_up",
    VolumeUpAction,
    cv.Schema(
        {
            cv.GenerateID(): cv.use_id(radio),
        }
    ),
)
async def radio_volume_up_to_code(config, action_id, template_arg, args):
    var = cg.new_Pvariable(action_id, template_arg)
    await cg.register_parented(var, config[CONF_ID])
    return var


@automation.register_action(
    "radio.volume_down",
    VolumeDownAction,
    cv.Schema(
        {
            cv.GenerateID(): cv.use_id(radio),
        }
    ),
)
async def radio_volume_down_to_code(config, action_id, template_arg, args):
    var = cg.new_Pvariable(action_id, template_arg)
    await cg.register_parented(var, config[CONF_ID])
    return var

@automation.register_action(
    "radio.set_mute",
    SetVolumeAction,
    cv.maybe_simple_value(
        {
            cv.GenerateID(): cv.use_id(radio),
            cv.Required(CONF_MUTE): cv.templatable(cv.boolean),
        },
        key=CONF_MUTE,
    ),
)
async def radio_set_mute_to_code(config, action_id, template_arg, args):
    var = cg.new_Pvariable(action_id, template_arg)
    await cg.register_parented(var, config[CONF_ID])
    template_ = await cg.templatable(config[CONF_MUTE], args, bool)
    cg.add(var.set_mute(template_))
    return var

@automation.register_action(
    "radio.toggle_mute",
    ToggleMuteAction,
    cv.Schema(
        {
            cv.GenerateID(): cv.use_id(radio),
        }
    ),
)
async def radio_toggle_mute_to_code(config, action_id, template_arg, args):
    var = cg.new_Pvariable(action_id, template_arg)
    await cg.register_parented(var, config[CONF_ID])
    return var


@automation.register_action(
    "radio.set_band",
    SetBandAction,
    cv.maybe_simple_value(
        {
            cv.GenerateID(): cv.use_id(radio),
            cv.Required(CONF_BAND): cv.templatable(cv.int_),
        },
        key=CONF_BAND,
    ),
)
async def radio_set_band_to_code(config, action_id, template_arg, args):
    var = cg.new_Pvariable(action_id, template_arg)
    await cg.register_parented(var, config[CONF_ID])
    template_ = await cg.templatable(config[CONF_BAND], args, int)
    cg.add(var.set_band(template_))
    return var


