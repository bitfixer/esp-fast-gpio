idf_component_register(
    SRCS 
        "esp-fast-gpio.cc"
    INCLUDE_DIRS 
        "."
        "../../"
    REQUIRES 
        driver
)

target_compile_features(${COMPONENT_LIB} PRIVATE cxx_std_17)

target_compile_options(${COMPONENT_LIB} PRIVATE
    -Wall
    -Wextra
)