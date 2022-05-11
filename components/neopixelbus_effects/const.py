CHIP_DOTSTAR = "dotstar"
CHIP_WS2801 = "ws2801"
CHIP_WS2811 = "ws2811"
CHIP_WS2812 = "ws2812"
CHIP_WS2812X = "ws2812x"
CHIP_WS2813 = "ws2813"
CHIP_SK6812 = "sk6812"
CHIP_TM1814 = "tm1814"
CHIP_TM1829 = "tm1829"
CHIP_TM1914 = "tm1914"
CHIP_800KBPS = "800kbps"
CHIP_400KBPS = "400kbps"
CHIP_APA106 = "apa106"
CHIP_LC8812 = "lc8812"
CHIP_LPD8806 = "lpd8806"
CHIP_LPD6803 = "lpd6803"
CHIP_P9813 = "p9813"

ONE_WIRE_CHIPS = [
    CHIP_WS2811,
    CHIP_WS2812,
    CHIP_WS2812X,
    CHIP_WS2813,
    CHIP_SK6812,
    CHIP_TM1814,
    CHIP_TM1829,
    CHIP_TM1914,
    CHIP_800KBPS,
    CHIP_400KBPS,
    CHIP_APA106,
    CHIP_LC8812,
]
TWO_WIRE_CHIPS = [
    CHIP_DOTSTAR,
    CHIP_WS2801,
    CHIP_LPD6803,
    CHIP_LPD8806,
    CHIP_P9813,
]
CHIP_TYPES = [*ONE_WIRE_CHIPS, *TWO_WIRE_CHIPS]
CONF_ASYNC = "async"
CONF_BUS = "bus"