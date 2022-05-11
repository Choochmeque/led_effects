import esphome.codegen as cg

# Base
light_ns = cg.esphome_ns.namespace("light")

# Effects
LightEffect = light_ns.class_("LightEffect")
AddressableLightEffect = light_ns.class_("AddressableLightEffect", LightEffect)
AddressableLambdaLightEffect = light_ns.class_(
    "AddressableMatrixEffect", AddressableLightEffect
)