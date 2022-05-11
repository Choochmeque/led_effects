import esphome.codegen as cg
import esphome.config_validation as cv

from esphome.const import (
    CONF_NAME,
    CONF_UPDATE_INTERVAL,
)
from esphome.util import Registry
from .types import (
    AddressableMatrixEffect,
)

CONF_ADDRESSABLE_MATRIX = "addressable_matrix"

ADDRESSABLE_EFFECTS = []

EFFECTS_REGISTRY = Registry()


def register_effect(name, effect_type, default_name, schema, *extra_validators):
    schema = cv.Schema(schema).extend(
        {
            cv.Optional(CONF_NAME, default=default_name): cv.string_strict,
        }
    )
    validator = cv.All(schema, *extra_validators)
    return EFFECTS_REGISTRY.register(name, effect_type, validator)

def register_addressable_effect(
    name, effect_type, default_name, schema, *extra_validators
):
    # addressable effect can be used only in addressable
    ADDRESSABLE_EFFECTS.append(name)

    return register_effect(name, effect_type, default_name, schema, *extra_validators)


@register_addressable_effect(
    CONF_ADDRESSABLE_MATRIX,
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