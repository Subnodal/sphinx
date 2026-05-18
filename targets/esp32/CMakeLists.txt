idf_component_register(
    SRCS "main.cpp" "term.cpp" ${SOURCES}
    INCLUDE_DIRS "." "../.."
)

target_compile_options(${COMPONENT_LIB} PRIVATE -fexceptions)