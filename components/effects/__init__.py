import esphome.codegen as cg
import esphome.config_validation as cv
from esphome.components.light.types import AddressableLightEffect
from esphome.components.light.effects import register_addressable_effect
from esphome.const import CONF_ID, CONF_NAME, CONF_UPDATE_INTERVAL, CONF_WIDTH, CONF_HEIGHT


CONF_EMNGR_ID = "emngr_id"


effects_ns = cg.esphome_ns.namespace("effects")

EffectsManagerComponent = effects_ns.class_("EffectsManager", cg.Component)

AddressableFireEffect = effects_ns.class_(
    "AddressableFireEffect", AddressableLightEffect
)
AddressableLightersEffect = effects_ns.class_(
    "AddressableLightersEffect", AddressableLightEffect
)
AddressableMatrixEffect = effects_ns.class_(
    "AddressableMatrixEffect", AddressableLightEffect
)
AddressableRainEffect = effects_ns.class_(
    "AddressableRainEffect", AddressableLightEffect
)
AddressableRainbowEffect = effects_ns.class_(
    "AddressableRainbowEffect", AddressableLightEffect
)
AddressableSinusoidEffect = effects_ns.class_(
    "AddressableSinusoidEffect", AddressableLightEffect
)
AddressableSnowEffect = effects_ns.class_(
    "AddressableSnowEffect", AddressableLightEffect
)

CONFIG_SCHEMA = cv.All(cv.Schema({}), cv.only_with_arduino)

# TODO: add effects manager component with width, height and matrix type properties
CONFIG_SCHEMA = cv.All(
    cv.Schema(
        {
            cv.GenerateID(): cv.declare_id(EffectsManagerComponent),
            cv.Optional(
                CONF_WIDTH, default="16"
            ): cv.int_range(0, 255),
            cv.Optional(
                CONF_HEIGHT, default="16"
            ): cv.int_range(0, 255),
            # cv.Optional(CONF_METHOD, default="MULTICAST"): cv.one_of(
            #     *METHODS, upper=True
            # ),
        }
    ),
    cv.only_with_arduino,
)

async def to_code(config):
    var = cg.new_Pvariable(config[CONF_ID])
    await cg.register_component(var, config)
    cg.add(var.set_width(config[CONF_WIDTH]))
    cg.add(var.set_height(config[CONF_HEIGHT]))

@register_addressable_effect(
    "addressable_fire",
    AddressableFireEffect,
    "Fire",
    {
        cv.GenerateID(CONF_EMNGR_ID): cv.use_id(EffectsManagerComponent),
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
    mngr = await cg.get_variable(config[CONF_EMNGR_ID])

    var = cg.new_Pvariable(effect_id, config[CONF_NAME])
    cg.add(var.set_update_interval(config[CONF_UPDATE_INTERVAL]))
    cg.add(var.set_scale(config["scale"]))
    cg.add(var.set_sparkles(config["sparkles"]))
    cg.add(var.set_manager(mngr))
    return var

@register_addressable_effect(
    "addressable_lighters",
    AddressableLightersEffect,
    "Lighters",
    {
        cv.GenerateID(CONF_EMNGR_ID): cv.use_id(EffectsManagerComponent),
        cv.Optional(
            CONF_UPDATE_INTERVAL, default="127ms"
        ): cv.positive_time_period_milliseconds,
        cv.Optional(
            "scale", default="10"
        ): cv.int_range(0, 255),        
    },
)
async def addressable_lighters_effect_to_code(config, effect_id):
    mngr = await cg.get_variable(config[CONF_EMNGR_ID])

    var = cg.new_Pvariable(effect_id, config[CONF_NAME])
    cg.add(var.set_update_interval(config[CONF_UPDATE_INTERVAL]))
    cg.add(var.set_scale(config["scale"]))
    cg.add(var.set_manager(mngr))
    return var

@register_addressable_effect(
    "addressable_matrix",
    AddressableMatrixEffect,
    "Matrix",
    {
        cv.GenerateID(CONF_EMNGR_ID): cv.use_id(EffectsManagerComponent),
        cv.Optional(
            CONF_UPDATE_INTERVAL, default="255ms"
        ): cv.positive_time_period_milliseconds,
    },
)
async def addressable_matrix_effect_to_code(config, effect_id):
    mngr = await cg.get_variable(config[CONF_EMNGR_ID])

    var = cg.new_Pvariable(effect_id, config[CONF_NAME])
    cg.add(var.set_update_interval(config[CONF_UPDATE_INTERVAL]))
    cg.add(var.set_manager(mngr))
    return var

@register_addressable_effect(
    "addressable_rain",
    AddressableRainEffect,
    "Rain",
    {
        cv.GenerateID(CONF_EMNGR_ID): cv.use_id(EffectsManagerComponent),
        cv.Optional(
            CONF_UPDATE_INTERVAL, default="100ms"
        ): cv.positive_time_period_milliseconds,
        cv.Optional(
            "scale", default="20"
        ): cv.int_range(0, 255),        
    },
)
async def addressable_rain_effect_to_code(config, effect_id):
    mngr = await cg.get_variable(config[CONF_EMNGR_ID])

    var = cg.new_Pvariable(effect_id, config[CONF_NAME])
    cg.add(var.set_update_interval(config[CONF_UPDATE_INTERVAL]))
    cg.add(var.set_scale(config["scale"]))
    cg.add(var.set_manager(mngr))
    return var

@register_addressable_effect(
    "addressable_rainbow",
    AddressableRainbowEffect,
    "Rainbow",
    {
        cv.GenerateID(CONF_EMNGR_ID): cv.use_id(EffectsManagerComponent),
        cv.Optional(
            CONF_UPDATE_INTERVAL, default="100ms"
        ): cv.positive_time_period_milliseconds,
        cv.Optional(
            "vertical", default=True
        ): cv.boolean,
        cv.Optional(
            "scale", default="18"
        ): cv.int_range(0, 255),
    },
)
async def aaddressable_rainbow_effect_to_code(config, effect_id):
    mngr = await cg.get_variable(config[CONF_EMNGR_ID])

    var = cg.new_Pvariable(effect_id, config[CONF_NAME])
    cg.add(var.set_update_interval(config[CONF_UPDATE_INTERVAL]))
    cg.add(var.set_vertical(config["vertical"]))
    cg.add(var.set_scale(config["scale"]))
    cg.add(var.set_manager(mngr))
    return var

@register_addressable_effect(
    "addressable_sinusoid",
    AddressableSinusoidEffect,
    "Sinusoid",
    {
        cv.GenerateID(CONF_EMNGR_ID): cv.use_id(EffectsManagerComponent),
        cv.Optional(
            CONF_UPDATE_INTERVAL, default="100ms"
        ): cv.positive_time_period_milliseconds,
        cv.Optional(
            "scale", default="20"
        ): cv.int_range(0, 255),
    },
)
async def addressable_sinusoid_effect_to_code(config, effect_id):
    mngr = await cg.get_variable(config[CONF_EMNGR_ID])

    var = cg.new_Pvariable(effect_id, config[CONF_NAME])
    cg.add(var.set_update_interval(config[CONF_UPDATE_INTERVAL]))
    cg.add(var.set_scale(config["scale"]))
    cg.add(var.set_manager(mngr))
    return var

@register_addressable_effect(
    "addressable_snow",
    AddressableSnowEffect,
    "Snow",
    {
        cv.GenerateID(CONF_EMNGR_ID): cv.use_id(EffectsManagerComponent),
        cv.Optional(
            CONF_UPDATE_INTERVAL, default="255ms"
        ): cv.positive_time_period_milliseconds,
    },
)
async def addressable_snow_effect_to_code(config, effect_id):
    mngr = await cg.get_variable(config[CONF_EMNGR_ID])

    var = cg.new_Pvariable(effect_id, config[CONF_NAME])
    cg.add(var.set_update_interval(config[CONF_UPDATE_INTERVAL]))
    cg.add(var.set_manager(mngr))
    return var