#include <cstdint>
#include <vector>

std::vector<uint8_t> encode_bmp_grayscale(
    const std::vector<uint8_t>& pixels,   // 0..255 per pixel
    uint32_t width,
    uint32_t height
);
    
std::vector<uint8_t> expand_1bit_to_8bit(
    const std::vector<uint8_t>& src,
    uint32_t width,
    uint32_t height
);

std::vector<uint8_t> encode_bmp_1bit_fast(
    const std::vector<uint8_t>& pixels,
    uint32_t width,
    uint32_t height
);
