import esphome.codegen as cg
import esphome.config_validation as cv
from esphome.components.light.types import AddressableLightEffect
from esphome.components.light.effects import register_addressable_effect
from esphome.const import CONF_NAME, CONF_UPDATE_INTERVAL

effects_ns = cg.esphome_ns.namespace("effects")
AddressableMatrixEffect = effects_ns.class_(
    "AddressableMatrixEffect", AddressableLightEffect
)

CONFIG_SCHEMA = cv.All(cv.Schema({}), cv.only_with_arduino)


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