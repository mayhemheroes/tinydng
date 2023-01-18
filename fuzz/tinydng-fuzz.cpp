#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stddef.h>

#define STB_IMAGE_IMPLEMENTATION
#define TINY_DNG_LOADER_IMPLEMENTATION
#include "../tiny_dng_loader.h"

extern "C" int LLVMFuzzerTestOneInput(const uint8_t *Data, size_t Size) {

    if (Size > 1) {
        std::vector<tinydng::FieldInfo> custom_fields;
        std::vector<tinydng::DNGImage> images;
        std::string warn;
        std::string err;
        
        uint8_t* in_data = (uint8_t*) malloc(Size-1);
        memcpy(in_data, Data+1, Size-1);

        if (Data[0] % 2 == 0) {
            tinydng::LoadDNGFromMemory(reinterpret_cast<const char *>(in_data), Size - 1, custom_fields, &images, &warn, &err);
        } else if (Data[0] % 2 == 1) {
            tinydng::IsDNGFromMemory(reinterpret_cast<const char *>(in_data), Size - 1, &err);
        } else {
            tinydng::lj92 res;
            int _width;
            int _height;
            int _bitdepth;
            if (tinydng::lj92_open(&res, in_data, Size - 1, &_width, &_height, &_bitdepth)) {
                tinydng::lj92_close(res);
            }
        }
        

        free(in_data);
    }
    return 0;
}