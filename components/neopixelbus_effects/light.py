import esphome.codegen as cg
import esphome.config_validation as cv
from esphome.components import light, output
from esphome.const import CONF_OUTPUT_ID, CONF_OUTPUT


neopixelbus_e_ns = cg.esphome_ns.namespace("neopixelbus_effects")
NeoPixelBusELightOutputBase = neopixelbus_e_ns.class_(
    "NeoPixelBusLightOutputBase", light.AddressableLight
)
NeoPixelRGBELightOutput = neopixelbus_e_ns.class_(
    "NeoPixelRGBLightOutput", NeoPixelBusELightOutputBase
)
NeoPixelRGBWELightOutput = neopixelbus_e_ns.class_(
    "NeoPixelRGBWLightOutput", NeoPixelBusELightOutputBase
)

CONFIG_SCHEMA = light.BRIGHTNESS_ONLY_LIGHT_SCHEMA.extend({
    cv.GenerateID(CONF_OUTPUT_ID): cv.declare_id(NeoPixelBusELightOutputBase)
})

def to_code(config):
    var = cg.new_Pvariable(config[CONF_OUTPUT_ID])
    yield light.register_light(var, config)

    out = yield cg.get_variable(config[CONF_OUTPUT])
    cg.add(var.set_output(out))