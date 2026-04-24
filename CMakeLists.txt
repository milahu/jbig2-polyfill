cmake_minimum_required(VERSION 3.16)
project(jbig2-polyfill)

set(CMAKE_C_STANDARD 99)
set(CMAKE_CXX_STANDARD 17)



# add_subdirectory(src/third_party/jbig2dec)

set(JBIG2DEC_DIR ${CMAKE_CURRENT_SOURCE_DIR}/src/third_party/jbig2dec)

# You should NOT compile these, because:
# jbig2dec.c → CLI tool (you already have your own)
# jbig2_image_png.c → requires libpng/zlib (not needed for your use case)
# jbig2_image_pbm.c → irrelevant output format
set(JBIG2DEC_SOURCES
    ${JBIG2DEC_DIR}/jbig2_arith.c
    ${JBIG2DEC_DIR}/jbig2_arith_int.c
    ${JBIG2DEC_DIR}/jbig2_arith_iaid.c
    ${JBIG2DEC_DIR}/jbig2_huffman.c
    ${JBIG2DEC_DIR}/jbig2_hufftab.c
    ${JBIG2DEC_DIR}/jbig2_segment.c
    ${JBIG2DEC_DIR}/jbig2_page.c
    ${JBIG2DEC_DIR}/jbig2_symbol_dict.c
    ${JBIG2DEC_DIR}/jbig2_text.c
    ${JBIG2DEC_DIR}/jbig2_halftone.c
    ${JBIG2DEC_DIR}/jbig2_generic.c
    ${JBIG2DEC_DIR}/jbig2_refinement.c
    ${JBIG2DEC_DIR}/jbig2_mmr.c
    ${JBIG2DEC_DIR}/jbig2_image.c
    ${JBIG2DEC_DIR}/jbig2.c
)

add_library(jbig2dec STATIC ${JBIG2DEC_SOURCES})

target_include_directories(jbig2dec PUBLIC
    ${JBIG2DEC_DIR}
)

target_compile_options(jbig2dec PRIVATE
    -Wall
    -Wextra
    -Wno-unused-parameter
    -O2
)

if(EMSCRIPTEN)
    target_compile_options(jbig2dec PRIVATE
        -sALLOW_MEMORY_GROWTH
    )
endif()



# add_library(jbig2_polyfill
#     src/jbig2_wrapper.c
#     src/wasm_api.cpp
#     src/bmp_encoder.cpp
# )

# target_include_directories(jbig2_polyfill PRIVATE
#     src/third_party/jbig2dec
# )

# # target_link_libraries(jbig2_polyfill jbig2dec)
# target_link_libraries(jbig2_polyfill PRIVATE jbig2dec)



if(EMSCRIPTEN)

    # WASM build
    add_executable(jbig2-polyfill
        src/jbig2_wrapper.c
        src/bmp_encoder.cpp
        # TODO? rename to jbig2_to_bmp.cpp
        src/wasm_api.cpp
    )

    target_link_libraries(jbig2-polyfill PRIVATE
        jbig2dec
    )

    target_link_options(jbig2-polyfill PRIVATE
        "-sWASM=1"
        "-sMODULARIZE=1"
        "-sEXPORT_NAME=create_jbig2_polyfill_module"
        "-sALLOW_MEMORY_GROWTH=1"
        "-sEXPORTED_FUNCTIONS=['_jbig2_to_bmp','_free_buffer','_malloc','_free']"
        "-sEXPORTED_RUNTIME_METHODS=['ccall','cwrap','HEAPU8','HEAPU32']"
        "-sNO_DISABLE_EXCEPTION_CATCHING"
    )

else()

    # CLI tool
    add_executable(jbig2_to_bmp
        src/jbig2_wrapper.c
        src/bmp_encoder.cpp
        src/wasm_api.cpp
        src/main.cpp
    )

    target_link_libraries(jbig2_to_bmp
        jbig2dec
    )

endif()
