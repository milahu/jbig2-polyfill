#include <vector>
#include <cstdint>

// #include <emscripten/emscripten.h>
#include <cstdlib>
#include <cstring>

#include "wasm_api.hpp"
#include "bmp_encoder.hpp"

extern "C" {

// EMSCRIPTEN_KEEPALIVE
uint8_t* jbig2_to_bmp(
    uint8_t* input,
    size_t size,
    uint32_t* out_size
) {
    auto decoded = decode_jbig2(input, size);

    if (!decoded.data) {
        *out_size = 0;
        return nullptr;
    }

    std::vector<uint8_t> src(
        decoded.data,
        decoded.data + (decoded.width * decoded.height) / 8
    );

    auto bmp = encode_bmp_1bit_fast(src, decoded.width, decoded.height);

    uint8_t* out = (uint8_t*)malloc(bmp.size());
    memcpy(out, bmp.data(), bmp.size());

    *out_size = bmp.size();

    free_jbig2_result(decoded.data);
    return out;
}

// EMSCRIPTEN_KEEPALIVE
void free_buffer(uint8_t* ptr) {
    free(ptr);
}

}
