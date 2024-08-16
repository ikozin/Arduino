import esphome.codegen as cg
import esphome.config_validation as cv
from esphome import automation
from esphome.components import i2c
from esphome.const import CONF_ID, CONF_VOLUME

DEPENDENCIES = ["i2c"]
MULTI_CONF = True
CONF_BAND = "band" 

rda5807m_ns = cg.esphome_ns.namespace("rda5807m")
RDA5807MComponent = rda5807m_ns.class_("RDA5807M", cg.Component, i2c.I2CDevice)

SetVolumeAction = rda5807m_ns.class_("SetVolumeAction", automation.Action)
VolumeUpAction = rda5807m_ns.class_("VolumeUpAction", automation.Action)
VolumeDownAction = rda5807m_ns.class_("VolumeDownAction", automation.Action)
ToggleMuteAction = rda5807m_ns.class_("ToggleMuteAction", automation.Action)
SetBandAction = rda5807m_ns.class_("SetBandAction", automation.Action)

CONFIG_SCHEMA = cv.All(
    cv.Schema(
        {
            cv.GenerateID(): cv.declare_id(RDA5807MComponent),
        }
    )
    .extend(cv.COMPONENT_SCHEMA)
    .extend(i2c.i2c_device_schema(0x11)),
)

async def to_code(config):
    var = cg.new_Pvariable(config[CONF_ID])
    await cg.register_component(var, config)
    await i2c.register_i2c_device(var, config)


@automation.register_action(
    "rda5807m.volume_up",
    VolumeUpAction,
    cv.Schema(
        {
            cv.GenerateID(): cv.use_id(RDA5807MComponent),
        }
    ),
)
async def rda5807m_volume_up_to_code(config, action_id, template_arg, args):
    var = cg.new_Pvariable(action_id, template_arg)
    await cg.register_parented(var, config[CONF_ID])
    return var


@automation.register_action(
    "rda5807m.volume_down",
    VolumeDownAction,
    cv.Schema(
        {
            cv.GenerateID(): cv.use_id(RDA5807MComponent),
        }
    ),
)
async def rda5807m_volume_down_to_code(config, action_id, template_arg, args):
    var = cg.new_Pvariable(action_id, template_arg)
    await cg.register_parented(var, config[CONF_ID])
    return var

    
@automation.register_action(
    "rda5807m.set_volume",
    SetVolumeAction,
    cv.maybe_simple_value(
        {
            cv.GenerateID(): cv.use_id(RDA5807MComponent),
            cv.Required(CONF_VOLUME): cv.templatable(cv.int_),
        },
        key=CONF_VOLUME,
    ),
)
async def rda5807m_set_volume_to_code(config, action_id, template_arg, args):
    var = cg.new_Pvariable(action_id, template_arg)
    await cg.register_parented(var, config[CONF_ID])
    template_ = await cg.templatable(config[CONF_VOLUME], args, int)
    cg.add(var.set_volume(template_))
    return var


@automation.register_action(
    "rda5807m.toggle_mute",
    ToggleMuteAction,
    cv.Schema(
        {
            cv.GenerateID(): cv.use_id(RDA5807MComponent),
        }
    ),
)
async def rda5807m_toggle_mute_to_code(config, action_id, template_arg, args):
    var = cg.new_Pvariable(action_id, template_arg)
    await cg.register_parented(var, config[CONF_ID])
    return var


@automation.register_action(
    "rda5807m.set_band",
    SetBandAction,
    cv.maybe_simple_value(
        {
            cv.GenerateID(): cv.use_id(RDA5807MComponent),
            cv.Required(CONF_BAND): cv.templatable(cv.int_),
        },
        key=CONF_BAND,
    ),
)
async def rda5807m_set_band_to_code(config, action_id, template_arg, args):
    var = cg.new_Pvariable(action_id, template_arg)
    await cg.register_parented(var, config[CONF_ID])
    template_ = await cg.templatable(config[CONF_BAND], args, int)
    cg.add(var.set_band(template_))
    return var


