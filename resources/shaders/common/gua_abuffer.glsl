
// HINT: define ABUF_MODE before including this file to change memory  
//       qualifier of frg_list and frg_storage buffers
#ifndef ABUF_MODE 
#define ABUF_MODE
#endif

#define ABUF_MAX_FRAGMENTS 300

// If max for uint64_t is not available
#if 1
#define MAX64(x, y) (((x)>(y))?(x):(y))
#define MIN64(x, y) (((x)<(y))?(x):(y))
#else
// this is not available with old drivers
#define MAX64(x, y) max(uint64_t(x), uint64_t(y))
#define MIN64(x, y) min(uint64_t(x), uint64_t(y))
#endif

// buffers
layout (binding = 0) uniform atomic_uint frag_counter;
layout (std430, binding = 0) ABUF_MODE coherent buffer abuf_list {
  uint64_t frag_list[];
};

layout (std430, binding = 1) ABUF_MODE coherent buffer abuf_data {
  uvec4 frag_data[];
};

// helper macros
#define UINT24_MAX           0xFFFFFF
#define UINT_MAX             0xFFFFFFFF
#define LSB64(a)             (uint32_t(a))

const unsigned int abuf_list_offset = gua_resolution.x * gua_resolution.y;

unsigned int pack_depth24(float z) {
  return (UINT_MAX - unsigned int(round(z * float(UINT24_MAX)))) << 8;
}

float unpack_depth24(unsigned int z) {
  return float((UINT_MAX - z) >> 8) / float(UINT24_MAX);
}
