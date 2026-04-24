#include <stdlib.h>
#include <stdint.h>
#include <string.h>

#include "jbig2.h"
#include "jbig2_image.h"

typedef struct {
    uint8_t* data;
    uint32_t width;
    uint32_t height;
} jbig2_result;

jbig2_result decode_jbig2(const uint8_t* input, size_t size) {
    jbig2_result result = {0};

    Jbig2Ctx *ctx = jbig2_ctx_new(NULL, 0, NULL, NULL, NULL);
    if (!ctx) return result;

    jbig2_data_in(ctx, input, size);

    Jbig2Image *img = jbig2_page_out(ctx);
    if (!img) {
        jbig2_ctx_free(ctx);
        return result;
    }

    result.width = img->width;
    result.height = img->height;

    size_t stride = img->stride;
    size_t total = stride * img->height;

    result.data = (uint8_t*)malloc(total);
    memcpy(result.data, img->data, total);

    jbig2_release_page(ctx, img);
    jbig2_ctx_free(ctx);

    return result;
}

void free_jbig2_result(uint8_t* ptr) {
    free(ptr);
}
