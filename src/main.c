#include <stdlib.h>
#include <stdio.h>
#include <stdint.h>
#include <stdarg.h>
#include <string.h>
#include <stdbool.h>

typedef int32_t i32;
typedef int64_t i64;
typedef uint64_t u32;
typedef uint32_t u64;

#include "log.h"
#include "lex.h"
#include "parse.h"
#include "runtime.h"

#define LINE_BUFFER_SIZE 256


int main(int argc, char** argv)
{
    if(argc == 1)
    {
        repl();
    }
    else if(argc == 2)
    {
        // @Incomplete: Run file here
    }
    
    return 0;
}
