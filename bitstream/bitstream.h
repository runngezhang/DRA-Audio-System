#include <stdint.h>
#include "../util/vector.h"

struct bit_stream {
    struct vector*     vec; /* use a vector of int32 to represent bit-stream */
    uint32_t    buffer;     /* a buffer */
    uint8_t     buf_size;   /* buffer size (how many bits are taken from last element) */
};

struct bit_stream* bitstream_init();
void bitstream_destroy(struct bit_stream* bs);

void bitstream_push(
    struct bit_stream* bs, 
    uint32_t target,      /* holder of the bits */
    uint32_t bits         /* how many bits to write */
    );

