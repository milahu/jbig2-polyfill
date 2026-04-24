#include <fstream>
#include <vector>
#include <iostream>
#include <cstdint>

#include "wasm_api.hpp"

extern "C" {
    uint8_t* jbig2_to_bmp(uint8_t*, size_t, uint32_t*);
    void free_buffer(uint8_t*);
}

int main(int argc, char** argv) {
    if (argc < 3) {
        std::cerr << "Usage: jbig2_to_bmp input.jbig2 output.bmp\n";
        return 1;
    }

    std::ifstream in(argv[1], std::ios::binary);
    std::vector<uint8_t> data((std::istreambuf_iterator<char>(in)),
                              std::istreambuf_iterator<char>());

    uint32_t out_size = 0;
    uint8_t* bmp = jbig2_to_bmp(data.data(), data.size(), &out_size);

    if (!bmp) {
        std::cerr << "Decode failed\n";
        return 1;
    }

    std::ofstream out(argv[2], std::ios::binary);
    out.write((char*)bmp, out_size);

    free_buffer(bmp);

    // std::cout << "Converted successfully\n";
    return 0;
}
