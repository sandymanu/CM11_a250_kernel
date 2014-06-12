/** @file
 * @brief  基礎データ型の型定義
 * @author Masaki HIRAGA (garhyla@morphoinc.com)
 * @date   2008-09-06
 */
#ifndef MORPHO_PRIMITIVE_H
#define MORPHO_PRIMITIVE_H

#ifdef __cplusplus
extern "C" {
#endif

typedef signed   char          morpho_Int8;   /**<  8ビット符号付整数. */
typedef unsigned char          morpho_Uint8;  /**<  8ビット符号無整数. */
typedef signed   short         morpho_Int16;  /**< 16ビット符号付整数. */
typedef unsigned short         morpho_Uint16; /**< 16ビット符号無整数. */
typedef signed   int           morpho_Int32;  /**< 32ビット符号付整数. */
typedef unsigned int           morpho_Uint32; /**< 32ビット符号無整数. */

#ifdef __IPHONE__
typedef unsigned short         morpho_Char;
#define MORPHO_LCHAR(S) L ## S
#define MORPHO_LSTR(S) L ## S

#elif defined(__SYMBIAN32__)
typedef unsigned short         morpho_Char;
#define MORPHO_LCHAR(S) L ## S
#define MORPHO_LSTR(S) L ## S

#elif defined(__BREW_SYS__)
typedef char      	       morpho_Char;
#define MORPHO_LCHAR(S) S
#define MORPHO_LSTR(S) S

#elif defined(_WIN32)
typedef char      	       morpho_Char;
#define MORPHO_LCHAR(S) S
#define MORPHO_LSTR(S) S

#else
typedef char      	       morpho_Char;
#define MORPHO_LCHAR(S) S
#define MORPHO_LSTR(S) S
#endif

typedef morpho_Uint32             morpho_Bool;

#define MORPHO_TRUE       (1)
#define MORPHO_FALSE      (0)

#ifdef __cplusplus
} /* extern "C" */
#endif

#endif /* #ifndef MORPHO_PRIMITIVE_H */
