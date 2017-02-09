#ifndef CODEBOOK_H
#define CODEBOOK_H

#include <stdint.h>

struct _context
{
    void (*encrypt)( uint8_t * c, int32_t clen, uint8_t * key, int32_t klen);

};

void cbc_codebook ( void );
void ecb_codebook ( void );

#endif
