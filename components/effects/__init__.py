import esphome.codegen as cg
import esphome.config_validation as cv
from esphome.components.light.types import AddressableLightEffect
from esphome.components.light.effects import register_addressable_effect
from esphome.const import CONF_NAME, CONF_UPDATE_INTERVAL

effects_ns = cg.esphome_ns.namespace("effects")
AddressableFireEffect = effects_ns.class_(
    "AddressableFireEffect", AddressableLightEffect
)
AddressableMatrixEffect = effects_ns.class_(
    "AddressableMatrixEffect", AddressableLightEffect
)
AddressableRainbowEffect = effects_ns.class_(
    "AddressableRainbowEffect", AddressableLightEffect
)
AddressableSnowEffect = effects_ns.class_(
    "AddressableSnowEffect", AddressableLightEffect
)

CONFIG_SCHEMA = cv.All(cv.Schema({}), cv.only_with_arduino)

@register_addressable_effect(
    "addressable_fire",
    AddressableFireEffect,
    "Fire",
    {
        cv.Optional(
            CONF_UPDATE_INTERVAL, default="37ms"
        ): cv.positive_time_period_milliseconds,
        cv.Optional(
            "scale", default="1"
        ): cv.int_range(0, 255),
        cv.Optional(
            "sparkles", default=True
        ): cv.boolean,
    },
)
async def addressable_fire_effect_to_code(config, effect_id):
    var = cg.new_Pvariable(effect_id, config[CONF_NAME])
    cg.add(var.set_update_interval(config[CONF_UPDATE_INTERVAL]))
    cg.add(var.set_scale(config["scale"]))
    cg.add(var.set_sparkles(config["sparkles"]))
    return var

@register_addressable_effect(
    "addressable_matrix",
    AddressableMatrixEffect,
    "Matrix",
    {
        cv.Optional(
            CONF_UPDATE_INTERVAL, default="255ms"
        ): cv.positive_time_period_milliseconds,
    },
)
async def addressable_matrix_effect_to_code(config, effect_id):
    var = cg.new_Pvariable(effect_id, config[CONF_NAME])
    cg.add(var.set_update_interval(config[CONF_UPDATE_INTERVAL]))
    return var

@register_addressable_effect(
    "addressable_rainbow",
    AddressableRainbowEffect,
    "Rainbow",
    {
        cv.Optional(
            CONF_UPDATE_INTERVAL, default="100ms"
        ): cv.positive_time_period_milliseconds,
        cv.Optional(
            "vertical", default=True
        ): cv.boolean,
    },
)
async def aaddressable_rainbow_vertical_effect_to_code(config, effect_id):
    var = cg.new_Pvariable(effect_id, config[CONF_NAME])
    cg.add(var.set_update_interval(config[CONF_UPDATE_INTERVAL]))
    cg.add(var.set_vertical(config["vertical"]))
    return var

@register_addressable_effect(
    "addressable_snow",
    AddressableSnowEffect,
    "Snow",
    {
        cv.Optional(
            CONF_UPDATE_INTERVAL, default="255ms"
        ): cv.positive_time_period_milliseconds,
    },
)
async def addressable_snow_effect_to_code(config, effect_id):
    var = cg.new_Pvariable(effect_id, config[CONF_NAME])
    cg.add(var.set_update_interval(config[CONF_UPDATE_INTERVAL]))
    return var