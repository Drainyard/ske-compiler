#ifndef NB_FILE_H
#define NB_FILE_H

typedef struct
{
    FILE* handle;
    String* path;
    String* extension;
} File;

typedef enum
{
    FILE_READ   = 1 << 0,
    FILE_WRITE  = 1 << 1,
    FILE_TEXT   = 1 << 2,
    FILE_BINARY = 1 << 3,
    FILE_CREATE = 1 << 4,
} File_Open_Options;

/* File file_open(String* path, u32 open_flags) */
/* { */
    
/* } */

#endif
