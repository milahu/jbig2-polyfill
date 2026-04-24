// #include <vector>
// #include <cstdint>

// // #include <emscripten/emscripten.h>
// #include <cstdlib>
// #include <cstring>

extern "C" {
    struct jbig2_result {
        uint8_t* data;
        uint32_t width;
        uint32_t height;
    };

    jbig2_result decode_jbig2(const uint8_t*, size_t);
    void free_jbig2_result(uint8_t*);
    void free_buffer(uint8_t*);
}
