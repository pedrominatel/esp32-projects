idf_component_get_property(LWIP_DIR lwip COMPONENT_DIR)
idf_component_get_property(MBEDTLS_DIR mbedtls COMPONENT_DIR)

list(APPEND COMPONENT_SOURCES
    ${CMAKE_CURRENT_LIST_DIR}/my_component.c
)

set(COMPONENT_INCLUDE_DIRS
    ${CMAKE_CURRENT_LIST_DIR}/include
    ${CMAKE_CURRENT_LIST_DIR}
    ${CMAKE_CURRENT_LIST_DIR}/port/inc
    ${CMAKE_CURRENT_LIST_DIR}/nested_component/include
    ${MBEDTLS_DIR}/mbedtls/include
    ${LWIP_DIR}/port/esp32/freertos
)

idf_component_register(
    SRCS ${COMPONENT_SOURCES}
    INCLUDE_DIRS ${COMPONENT_INCLUDE_DIRS}
    REQUIRES  nvs_flash mbedtls mqtt tcp_transport)

add_subdirectory(azure-sdk-for-c)