#ifndef __COMMON_H_
#define __COMMON_H_

#define MIN(X, Y) (((X) < (Y)) ? (X) : (Y))
#define MAX(X, Y) (((X) > (Y)) ? (X) : (Y))

#define SIZE(X) (sizeof(X) / sizeof(X)[0])

#define FREE(X)   if(X) free(X), X = NULL
#define DELETE(X) if(X) delete X, X = NULL

#define UNUSED(expr) do { (void)(expr); } while (0)

#define BITFIELD_SET(Y, LOC)         ( Y |=  (1 << LOC) )
#define BITFIELD_CLEAR(Y, LOC)       ( Y &= ~(1 << LOC) )
#define BITFIELD_FLIP(Y, LOC)        ( Y ^=  (1 << LOC) )
#define BITFIELD_GET(Y, LOC)         ( Y & (1 << LOC))

typedef unsigned char uchar;
typedef unsigned short ushort;
typedef unsigned int uint;
typedef unsigned long int ulong;

#define FILEPATH_MAX_LEN            256

#endif // __COMMON_H_
