# 0 "src/main.c"
# 0 "<built-in>"
# 0 "<command-line>"
# 1 "/usr/include/stdc-predef.h" 1 3 4
# 0 "<command-line>" 2
# 1 "src/main.c"
# 1 "/usr/include/stdlib.h" 1 3 4
# 26 "/usr/include/stdlib.h" 3 4
# 1 "/usr/include/bits/libc-header-start.h" 1 3 4
# 33 "/usr/include/bits/libc-header-start.h" 3 4
# 1 "/usr/include/features.h" 1 3 4
# 392 "/usr/include/features.h" 3 4
# 1 "/usr/include/features-time64.h" 1 3 4
# 20 "/usr/include/features-time64.h" 3 4
# 1 "/usr/include/bits/wordsize.h" 1 3 4
# 21 "/usr/include/features-time64.h" 2 3 4
# 1 "/usr/include/bits/timesize.h" 1 3 4
# 19 "/usr/include/bits/timesize.h" 3 4
# 1 "/usr/include/bits/wordsize.h" 1 3 4
# 20 "/usr/include/bits/timesize.h" 2 3 4
# 22 "/usr/include/features-time64.h" 2 3 4
# 393 "/usr/include/features.h" 2 3 4
# 490 "/usr/include/features.h" 3 4
# 1 "/usr/include/sys/cdefs.h" 1 3 4
# 559 "/usr/include/sys/cdefs.h" 3 4
# 1 "/usr/include/bits/wordsize.h" 1 3 4
# 560 "/usr/include/sys/cdefs.h" 2 3 4
# 1 "/usr/include/bits/long-double.h" 1 3 4
# 561 "/usr/include/sys/cdefs.h" 2 3 4
# 491 "/usr/include/features.h" 2 3 4
# 514 "/usr/include/features.h" 3 4
# 1 "/usr/include/gnu/stubs.h" 1 3 4
# 10 "/usr/include/gnu/stubs.h" 3 4
# 1 "/usr/include/gnu/stubs-64.h" 1 3 4
# 11 "/usr/include/gnu/stubs.h" 2 3 4
# 515 "/usr/include/features.h" 2 3 4
# 34 "/usr/include/bits/libc-header-start.h" 2 3 4
# 27 "/usr/include/stdlib.h" 2 3 4





# 1 "/usr/lib/gcc/x86_64-pc-linux-gnu/12.2.0/include/stddef.h" 1 3 4
# 214 "/usr/lib/gcc/x86_64-pc-linux-gnu/12.2.0/include/stddef.h" 3 4

# 214 "/usr/lib/gcc/x86_64-pc-linux-gnu/12.2.0/include/stddef.h" 3 4
typedef long unsigned int size_t;
# 329 "/usr/lib/gcc/x86_64-pc-linux-gnu/12.2.0/include/stddef.h" 3 4
typedef int wchar_t;
# 33 "/usr/include/stdlib.h" 2 3 4







# 1 "/usr/include/bits/waitflags.h" 1 3 4
# 41 "/usr/include/stdlib.h" 2 3 4
# 1 "/usr/include/bits/waitstatus.h" 1 3 4
# 42 "/usr/include/stdlib.h" 2 3 4
# 56 "/usr/include/stdlib.h" 3 4
# 1 "/usr/include/bits/floatn.h" 1 3 4
# 119 "/usr/include/bits/floatn.h" 3 4
# 1 "/usr/include/bits/floatn-common.h" 1 3 4
# 24 "/usr/include/bits/floatn-common.h" 3 4
# 1 "/usr/include/bits/long-double.h" 1 3 4
# 25 "/usr/include/bits/floatn-common.h" 2 3 4
# 120 "/usr/include/bits/floatn.h" 2 3 4
# 57 "/usr/include/stdlib.h" 2 3 4


typedef struct
  {
    int quot;
    int rem;
  } div_t;



typedef struct
  {
    long int quot;
    long int rem;
  } ldiv_t;





__extension__ typedef struct
  {
    long long int quot;
    long long int rem;
  } lldiv_t;
# 98 "/usr/include/stdlib.h" 3 4
extern size_t __ctype_get_mb_cur_max (void) __attribute__ ((__nothrow__ , __leaf__)) ;



extern double atof (const char *__nptr)
     __attribute__ ((__nothrow__ , __leaf__)) __attribute__ ((__pure__)) __attribute__ ((__nonnull__ (1))) ;

extern int atoi (const char *__nptr)
     __attribute__ ((__nothrow__ , __leaf__)) __attribute__ ((__pure__)) __attribute__ ((__nonnull__ (1))) ;

extern long int atol (const char *__nptr)
     __attribute__ ((__nothrow__ , __leaf__)) __attribute__ ((__pure__)) __attribute__ ((__nonnull__ (1))) ;



__extension__ extern long long int atoll (const char *__nptr)
     __attribute__ ((__nothrow__ , __leaf__)) __attribute__ ((__pure__)) __attribute__ ((__nonnull__ (1))) ;



extern double strtod (const char *__restrict __nptr,
        char **__restrict __endptr)
     __attribute__ ((__nothrow__ , __leaf__)) __attribute__ ((__nonnull__ (1)));



extern float strtof (const char *__restrict __nptr,
       char **__restrict __endptr) __attribute__ ((__nothrow__ , __leaf__)) __attribute__ ((__nonnull__ (1)));

extern long double strtold (const char *__restrict __nptr,
       char **__restrict __endptr)
     __attribute__ ((__nothrow__ , __leaf__)) __attribute__ ((__nonnull__ (1)));
# 177 "/usr/include/stdlib.h" 3 4
extern long int strtol (const char *__restrict __nptr,
   char **__restrict __endptr, int __base)
     __attribute__ ((__nothrow__ , __leaf__)) __attribute__ ((__nonnull__ (1)));

extern unsigned long int strtoul (const char *__restrict __nptr,
      char **__restrict __endptr, int __base)
     __attribute__ ((__nothrow__ , __leaf__)) __attribute__ ((__nonnull__ (1)));



__extension__
extern long long int strtoq (const char *__restrict __nptr,
        char **__restrict __endptr, int __base)
     __attribute__ ((__nothrow__ , __leaf__)) __attribute__ ((__nonnull__ (1)));

__extension__
extern unsigned long long int strtouq (const char *__restrict __nptr,
           char **__restrict __endptr, int __base)
     __attribute__ ((__nothrow__ , __leaf__)) __attribute__ ((__nonnull__ (1)));




__extension__
extern long long int strtoll (const char *__restrict __nptr,
         char **__restrict __endptr, int __base)
     __attribute__ ((__nothrow__ , __leaf__)) __attribute__ ((__nonnull__ (1)));

__extension__
extern unsigned long long int strtoull (const char *__restrict __nptr,
     char **__restrict __endptr, int __base)
     __attribute__ ((__nothrow__ , __leaf__)) __attribute__ ((__nonnull__ (1)));
# 386 "/usr/include/stdlib.h" 3 4
extern char *l64a (long int __n) __attribute__ ((__nothrow__ , __leaf__)) ;


extern long int a64l (const char *__s)
     __attribute__ ((__nothrow__ , __leaf__)) __attribute__ ((__pure__)) __attribute__ ((__nonnull__ (1))) ;




# 1 "/usr/include/sys/types.h" 1 3 4
# 27 "/usr/include/sys/types.h" 3 4


# 1 "/usr/include/bits/types.h" 1 3 4
# 27 "/usr/include/bits/types.h" 3 4
# 1 "/usr/include/bits/wordsize.h" 1 3 4
# 28 "/usr/include/bits/types.h" 2 3 4
# 1 "/usr/include/bits/timesize.h" 1 3 4
# 19 "/usr/include/bits/timesize.h" 3 4
# 1 "/usr/include/bits/wordsize.h" 1 3 4
# 20 "/usr/include/bits/timesize.h" 2 3 4
# 29 "/usr/include/bits/types.h" 2 3 4


typedef unsigned char __u_char;
typedef unsigned short int __u_short;
typedef unsigned int __u_int;
typedef unsigned long int __u_long;


typedef signed char __int8_t;
typedef unsigned char __uint8_t;
typedef signed short int __int16_t;
typedef unsigned short int __uint16_t;
typedef signed int __int32_t;
typedef unsigned int __uint32_t;

typedef signed long int __int64_t;
typedef unsigned long int __uint64_t;






typedef __int8_t __int_least8_t;
typedef __uint8_t __uint_least8_t;
typedef __int16_t __int_least16_t;
typedef __uint16_t __uint_least16_t;
typedef __int32_t __int_least32_t;
typedef __uint32_t __uint_least32_t;
typedef __int64_t __int_least64_t;
typedef __uint64_t __uint_least64_t;



typedef long int __quad_t;
typedef unsigned long int __u_quad_t;







typedef long int __intmax_t;
typedef unsigned long int __uintmax_t;
# 141 "/usr/include/bits/types.h" 3 4
# 1 "/usr/include/bits/typesizes.h" 1 3 4
# 142 "/usr/include/bits/types.h" 2 3 4
# 1 "/usr/include/bits/time64.h" 1 3 4
# 143 "/usr/include/bits/types.h" 2 3 4


typedef unsigned long int __dev_t;
typedef unsigned int __uid_t;
typedef unsigned int __gid_t;
typedef unsigned long int __ino_t;
typedef unsigned long int __ino64_t;
typedef unsigned int __mode_t;
typedef unsigned long int __nlink_t;
typedef long int __off_t;
typedef long int __off64_t;
typedef int __pid_t;
typedef struct { int __val[2]; } __fsid_t;
typedef long int __clock_t;
typedef unsigned long int __rlim_t;
typedef unsigned long int __rlim64_t;
typedef unsigned int __id_t;
typedef long int __time_t;
typedef unsigned int __useconds_t;
typedef long int __suseconds_t;
typedef long int __suseconds64_t;

typedef int __daddr_t;
typedef int __key_t;


typedef int __clockid_t;


typedef void * __timer_t;


typedef long int __blksize_t;




typedef long int __blkcnt_t;
typedef long int __blkcnt64_t;


typedef unsigned long int __fsblkcnt_t;
typedef unsigned long int __fsblkcnt64_t;


typedef unsigned long int __fsfilcnt_t;
typedef unsigned long int __fsfilcnt64_t;


typedef long int __fsword_t;

typedef long int __ssize_t;


typedef long int __syscall_slong_t;

typedef unsigned long int __syscall_ulong_t;



typedef __off64_t __loff_t;
typedef char *__caddr_t;


typedef long int __intptr_t;


typedef unsigned int __socklen_t;




typedef int __sig_atomic_t;
# 30 "/usr/include/sys/types.h" 2 3 4



typedef __u_char u_char;
typedef __u_short u_short;
typedef __u_int u_int;
typedef __u_long u_long;
typedef __quad_t quad_t;
typedef __u_quad_t u_quad_t;
typedef __fsid_t fsid_t;


typedef __loff_t loff_t;




typedef __ino_t ino_t;
# 59 "/usr/include/sys/types.h" 3 4
typedef __dev_t dev_t;




typedef __gid_t gid_t;




typedef __mode_t mode_t;




typedef __nlink_t nlink_t;




typedef __uid_t uid_t;





typedef __off_t off_t;
# 97 "/usr/include/sys/types.h" 3 4
typedef __pid_t pid_t;





typedef __id_t id_t;




typedef __ssize_t ssize_t;





typedef __daddr_t daddr_t;
typedef __caddr_t caddr_t;





typedef __key_t key_t;




# 1 "/usr/include/bits/types/clock_t.h" 1 3 4






typedef __clock_t clock_t;
# 127 "/usr/include/sys/types.h" 2 3 4

# 1 "/usr/include/bits/types/clockid_t.h" 1 3 4






typedef __clockid_t clockid_t;
# 129 "/usr/include/sys/types.h" 2 3 4
# 1 "/usr/include/bits/types/time_t.h" 1 3 4
# 10 "/usr/include/bits/types/time_t.h" 3 4
typedef __time_t time_t;
# 130 "/usr/include/sys/types.h" 2 3 4
# 1 "/usr/include/bits/types/timer_t.h" 1 3 4






typedef __timer_t timer_t;
# 131 "/usr/include/sys/types.h" 2 3 4
# 144 "/usr/include/sys/types.h" 3 4
# 1 "/usr/lib/gcc/x86_64-pc-linux-gnu/12.2.0/include/stddef.h" 1 3 4
# 145 "/usr/include/sys/types.h" 2 3 4



typedef unsigned long int ulong;
typedef unsigned short int ushort;
typedef unsigned int uint;




# 1 "/usr/include/bits/stdint-intn.h" 1 3 4
# 24 "/usr/include/bits/stdint-intn.h" 3 4
typedef __int8_t int8_t;
typedef __int16_t int16_t;
typedef __int32_t int32_t;
typedef __int64_t int64_t;
# 156 "/usr/include/sys/types.h" 2 3 4


typedef __uint8_t u_int8_t;
typedef __uint16_t u_int16_t;
typedef __uint32_t u_int32_t;
typedef __uint64_t u_int64_t;


typedef int register_t __attribute__ ((__mode__ (__word__)));
# 176 "/usr/include/sys/types.h" 3 4
# 1 "/usr/include/endian.h" 1 3 4
# 24 "/usr/include/endian.h" 3 4
# 1 "/usr/include/bits/endian.h" 1 3 4
# 35 "/usr/include/bits/endian.h" 3 4
# 1 "/usr/include/bits/endianness.h" 1 3 4
# 36 "/usr/include/bits/endian.h" 2 3 4
# 25 "/usr/include/endian.h" 2 3 4
# 35 "/usr/include/endian.h" 3 4
# 1 "/usr/include/bits/byteswap.h" 1 3 4
# 33 "/usr/include/bits/byteswap.h" 3 4
static __inline __uint16_t
__bswap_16 (__uint16_t __bsx)
{

  return __builtin_bswap16 (__bsx);



}






static __inline __uint32_t
__bswap_32 (__uint32_t __bsx)
{

  return __builtin_bswap32 (__bsx);



}
# 69 "/usr/include/bits/byteswap.h" 3 4
__extension__ static __inline __uint64_t
__bswap_64 (__uint64_t __bsx)
{

  return __builtin_bswap64 (__bsx);



}
# 36 "/usr/include/endian.h" 2 3 4
# 1 "/usr/include/bits/uintn-identity.h" 1 3 4
# 32 "/usr/include/bits/uintn-identity.h" 3 4
static __inline __uint16_t
__uint16_identity (__uint16_t __x)
{
  return __x;
}

static __inline __uint32_t
__uint32_identity (__uint32_t __x)
{
  return __x;
}

static __inline __uint64_t
__uint64_identity (__uint64_t __x)
{
  return __x;
}
# 37 "/usr/include/endian.h" 2 3 4
# 177 "/usr/include/sys/types.h" 2 3 4


# 1 "/usr/include/sys/select.h" 1 3 4
# 30 "/usr/include/sys/select.h" 3 4
# 1 "/usr/include/bits/select.h" 1 3 4
# 31 "/usr/include/sys/select.h" 2 3 4


# 1 "/usr/include/bits/types/sigset_t.h" 1 3 4



# 1 "/usr/include/bits/types/__sigset_t.h" 1 3 4




typedef struct
{
  unsigned long int __val[(1024 / (8 * sizeof (unsigned long int)))];
} __sigset_t;
# 5 "/usr/include/bits/types/sigset_t.h" 2 3 4


typedef __sigset_t sigset_t;
# 34 "/usr/include/sys/select.h" 2 3 4



# 1 "/usr/include/bits/types/struct_timeval.h" 1 3 4







struct timeval
{




  __time_t tv_sec;
  __suseconds_t tv_usec;

};
# 38 "/usr/include/sys/select.h" 2 3 4

# 1 "/usr/include/bits/types/struct_timespec.h" 1 3 4
# 11 "/usr/include/bits/types/struct_timespec.h" 3 4
struct timespec
{



  __time_t tv_sec;




  __syscall_slong_t tv_nsec;
# 31 "/usr/include/bits/types/struct_timespec.h" 3 4
};
# 40 "/usr/include/sys/select.h" 2 3 4



typedef __suseconds_t suseconds_t;





typedef long int __fd_mask;
# 59 "/usr/include/sys/select.h" 3 4
typedef struct
  {






    __fd_mask __fds_bits[1024 / (8 * (int) sizeof (__fd_mask))];


  } fd_set;






typedef __fd_mask fd_mask;
# 91 "/usr/include/sys/select.h" 3 4

# 102 "/usr/include/sys/select.h" 3 4
extern int select (int __nfds, fd_set *__restrict __readfds,
     fd_set *__restrict __writefds,
     fd_set *__restrict __exceptfds,
     struct timeval *__restrict __timeout);
# 127 "/usr/include/sys/select.h" 3 4
extern int pselect (int __nfds, fd_set *__restrict __readfds,
      fd_set *__restrict __writefds,
      fd_set *__restrict __exceptfds,
      const struct timespec *__restrict __timeout,
      const __sigset_t *__restrict __sigmask);
# 153 "/usr/include/sys/select.h" 3 4

# 180 "/usr/include/sys/types.h" 2 3 4





typedef __blksize_t blksize_t;






typedef __blkcnt_t blkcnt_t;



typedef __fsblkcnt_t fsblkcnt_t;



typedef __fsfilcnt_t fsfilcnt_t;
# 227 "/usr/include/sys/types.h" 3 4
# 1 "/usr/include/bits/pthreadtypes.h" 1 3 4
# 23 "/usr/include/bits/pthreadtypes.h" 3 4
# 1 "/usr/include/bits/thread-shared-types.h" 1 3 4
# 44 "/usr/include/bits/thread-shared-types.h" 3 4
# 1 "/usr/include/bits/pthreadtypes-arch.h" 1 3 4
# 21 "/usr/include/bits/pthreadtypes-arch.h" 3 4
# 1 "/usr/include/bits/wordsize.h" 1 3 4
# 22 "/usr/include/bits/pthreadtypes-arch.h" 2 3 4
# 45 "/usr/include/bits/thread-shared-types.h" 2 3 4

# 1 "/usr/include/bits/atomic_wide_counter.h" 1 3 4
# 25 "/usr/include/bits/atomic_wide_counter.h" 3 4
typedef union
{
  __extension__ unsigned long long int __value64;
  struct
  {
    unsigned int __low;
    unsigned int __high;
  } __value32;
} __atomic_wide_counter;
# 47 "/usr/include/bits/thread-shared-types.h" 2 3 4




typedef struct __pthread_internal_list
{
  struct __pthread_internal_list *__prev;
  struct __pthread_internal_list *__next;
} __pthread_list_t;

typedef struct __pthread_internal_slist
{
  struct __pthread_internal_slist *__next;
} __pthread_slist_t;
# 76 "/usr/include/bits/thread-shared-types.h" 3 4
# 1 "/usr/include/bits/struct_mutex.h" 1 3 4
# 22 "/usr/include/bits/struct_mutex.h" 3 4
struct __pthread_mutex_s
{
  int __lock;
  unsigned int __count;
  int __owner;

  unsigned int __nusers;



  int __kind;

  short __spins;
  short __elision;
  __pthread_list_t __list;
# 53 "/usr/include/bits/struct_mutex.h" 3 4
};
# 77 "/usr/include/bits/thread-shared-types.h" 2 3 4
# 89 "/usr/include/bits/thread-shared-types.h" 3 4
# 1 "/usr/include/bits/struct_rwlock.h" 1 3 4
# 23 "/usr/include/bits/struct_rwlock.h" 3 4
struct __pthread_rwlock_arch_t
{
  unsigned int __readers;
  unsigned int __writers;
  unsigned int __wrphase_futex;
  unsigned int __writers_futex;
  unsigned int __pad3;
  unsigned int __pad4;

  int __cur_writer;
  int __shared;
  signed char __rwelision;




  unsigned char __pad1[7];


  unsigned long int __pad2;


  unsigned int __flags;
# 55 "/usr/include/bits/struct_rwlock.h" 3 4
};
# 90 "/usr/include/bits/thread-shared-types.h" 2 3 4




struct __pthread_cond_s
{
  __atomic_wide_counter __wseq;
  __atomic_wide_counter __g1_start;
  unsigned int __g_refs[2] ;
  unsigned int __g_size[2];
  unsigned int __g1_orig_size;
  unsigned int __wrefs;
  unsigned int __g_signals[2];
};

typedef unsigned int __tss_t;
typedef unsigned long int __thrd_t;

typedef struct
{
  int __data ;
} __once_flag;
# 24 "/usr/include/bits/pthreadtypes.h" 2 3 4



typedef unsigned long int pthread_t;




typedef union
{
  char __size[4];
  int __align;
} pthread_mutexattr_t;




typedef union
{
  char __size[4];
  int __align;
} pthread_condattr_t;



typedef unsigned int pthread_key_t;



typedef int pthread_once_t;


union pthread_attr_t
{
  char __size[56];
  long int __align;
};

typedef union pthread_attr_t pthread_attr_t;




typedef union
{
  struct __pthread_mutex_s __data;
  char __size[40];
  long int __align;
} pthread_mutex_t;


typedef union
{
  struct __pthread_cond_s __data;
  char __size[48];
  __extension__ long long int __align;
} pthread_cond_t;





typedef union
{
  struct __pthread_rwlock_arch_t __data;
  char __size[56];
  long int __align;
} pthread_rwlock_t;

typedef union
{
  char __size[8];
  long int __align;
} pthread_rwlockattr_t;





typedef volatile int pthread_spinlock_t;




typedef union
{
  char __size[32];
  long int __align;
} pthread_barrier_t;

typedef union
{
  char __size[4];
  int __align;
} pthread_barrierattr_t;
# 228 "/usr/include/sys/types.h" 2 3 4



# 396 "/usr/include/stdlib.h" 2 3 4






extern long int random (void) __attribute__ ((__nothrow__ , __leaf__));


extern void srandom (unsigned int __seed) __attribute__ ((__nothrow__ , __leaf__));





extern char *initstate (unsigned int __seed, char *__statebuf,
   size_t __statelen) __attribute__ ((__nothrow__ , __leaf__)) __attribute__ ((__nonnull__ (2)));



extern char *setstate (char *__statebuf) __attribute__ ((__nothrow__ , __leaf__)) __attribute__ ((__nonnull__ (1)));







struct random_data
  {
    int32_t *fptr;
    int32_t *rptr;
    int32_t *state;
    int rand_type;
    int rand_deg;
    int rand_sep;
    int32_t *end_ptr;
  };

extern int random_r (struct random_data *__restrict __buf,
       int32_t *__restrict __result) __attribute__ ((__nothrow__ , __leaf__)) __attribute__ ((__nonnull__ (1, 2)));

extern int srandom_r (unsigned int __seed, struct random_data *__buf)
     __attribute__ ((__nothrow__ , __leaf__)) __attribute__ ((__nonnull__ (2)));

extern int initstate_r (unsigned int __seed, char *__restrict __statebuf,
   size_t __statelen,
   struct random_data *__restrict __buf)
     __attribute__ ((__nothrow__ , __leaf__)) __attribute__ ((__nonnull__ (2, 4)));

extern int setstate_r (char *__restrict __statebuf,
         struct random_data *__restrict __buf)
     __attribute__ ((__nothrow__ , __leaf__)) __attribute__ ((__nonnull__ (1, 2)));





extern int rand (void) __attribute__ ((__nothrow__ , __leaf__));

extern void srand (unsigned int __seed) __attribute__ ((__nothrow__ , __leaf__));



extern int rand_r (unsigned int *__seed) __attribute__ ((__nothrow__ , __leaf__));







extern double drand48 (void) __attribute__ ((__nothrow__ , __leaf__));
extern double erand48 (unsigned short int __xsubi[3]) __attribute__ ((__nothrow__ , __leaf__)) __attribute__ ((__nonnull__ (1)));


extern long int lrand48 (void) __attribute__ ((__nothrow__ , __leaf__));
extern long int nrand48 (unsigned short int __xsubi[3])
     __attribute__ ((__nothrow__ , __leaf__)) __attribute__ ((__nonnull__ (1)));


extern long int mrand48 (void) __attribute__ ((__nothrow__ , __leaf__));
extern long int jrand48 (unsigned short int __xsubi[3])
     __attribute__ ((__nothrow__ , __leaf__)) __attribute__ ((__nonnull__ (1)));


extern void srand48 (long int __seedval) __attribute__ ((__nothrow__ , __leaf__));
extern unsigned short int *seed48 (unsigned short int __seed16v[3])
     __attribute__ ((__nothrow__ , __leaf__)) __attribute__ ((__nonnull__ (1)));
extern void lcong48 (unsigned short int __param[7]) __attribute__ ((__nothrow__ , __leaf__)) __attribute__ ((__nonnull__ (1)));





struct drand48_data
  {
    unsigned short int __x[3];
    unsigned short int __old_x[3];
    unsigned short int __c;
    unsigned short int __init;
    __extension__ unsigned long long int __a;

  };


extern int drand48_r (struct drand48_data *__restrict __buffer,
        double *__restrict __result) __attribute__ ((__nothrow__ , __leaf__)) __attribute__ ((__nonnull__ (1, 2)));
extern int erand48_r (unsigned short int __xsubi[3],
        struct drand48_data *__restrict __buffer,
        double *__restrict __result) __attribute__ ((__nothrow__ , __leaf__)) __attribute__ ((__nonnull__ (1, 2)));


extern int lrand48_r (struct drand48_data *__restrict __buffer,
        long int *__restrict __result)
     __attribute__ ((__nothrow__ , __leaf__)) __attribute__ ((__nonnull__ (1, 2)));
extern int nrand48_r (unsigned short int __xsubi[3],
        struct drand48_data *__restrict __buffer,
        long int *__restrict __result)
     __attribute__ ((__nothrow__ , __leaf__)) __attribute__ ((__nonnull__ (1, 2)));


extern int mrand48_r (struct drand48_data *__restrict __buffer,
        long int *__restrict __result)
     __attribute__ ((__nothrow__ , __leaf__)) __attribute__ ((__nonnull__ (1, 2)));
extern int jrand48_r (unsigned short int __xsubi[3],
        struct drand48_data *__restrict __buffer,
        long int *__restrict __result)
     __attribute__ ((__nothrow__ , __leaf__)) __attribute__ ((__nonnull__ (1, 2)));


extern int srand48_r (long int __seedval, struct drand48_data *__buffer)
     __attribute__ ((__nothrow__ , __leaf__)) __attribute__ ((__nonnull__ (2)));

extern int seed48_r (unsigned short int __seed16v[3],
       struct drand48_data *__buffer) __attribute__ ((__nothrow__ , __leaf__)) __attribute__ ((__nonnull__ (1, 2)));

extern int lcong48_r (unsigned short int __param[7],
        struct drand48_data *__buffer)
     __attribute__ ((__nothrow__ , __leaf__)) __attribute__ ((__nonnull__ (1, 2)));


extern __uint32_t arc4random (void)
     __attribute__ ((__nothrow__ , __leaf__)) ;


extern void arc4random_buf (void *__buf, size_t __size)
     __attribute__ ((__nothrow__ , __leaf__)) __attribute__ ((__nonnull__ (1)));



extern __uint32_t arc4random_uniform (__uint32_t __upper_bound)
     __attribute__ ((__nothrow__ , __leaf__)) ;




extern void *malloc (size_t __size) __attribute__ ((__nothrow__ , __leaf__)) __attribute__ ((__malloc__))
     __attribute__ ((__alloc_size__ (1))) ;

extern void *calloc (size_t __nmemb, size_t __size)
     __attribute__ ((__nothrow__ , __leaf__)) __attribute__ ((__malloc__)) __attribute__ ((__alloc_size__ (1, 2))) ;






extern void *realloc (void *__ptr, size_t __size)
     __attribute__ ((__nothrow__ , __leaf__)) __attribute__ ((__warn_unused_result__)) __attribute__ ((__alloc_size__ (2)));


extern void free (void *__ptr) __attribute__ ((__nothrow__ , __leaf__));







extern void *reallocarray (void *__ptr, size_t __nmemb, size_t __size)
     __attribute__ ((__nothrow__ , __leaf__)) __attribute__ ((__warn_unused_result__))
     __attribute__ ((__alloc_size__ (2, 3)))
    __attribute__ ((__malloc__ (__builtin_free, 1)));


extern void *reallocarray (void *__ptr, size_t __nmemb, size_t __size)
     __attribute__ ((__nothrow__ , __leaf__)) __attribute__ ((__malloc__ (reallocarray, 1)));



# 1 "/usr/include/alloca.h" 1 3 4
# 24 "/usr/include/alloca.h" 3 4
# 1 "/usr/lib/gcc/x86_64-pc-linux-gnu/12.2.0/include/stddef.h" 1 3 4
# 25 "/usr/include/alloca.h" 2 3 4







extern void *alloca (size_t __size) __attribute__ ((__nothrow__ , __leaf__));






# 588 "/usr/include/stdlib.h" 2 3 4





extern void *valloc (size_t __size) __attribute__ ((__nothrow__ , __leaf__)) __attribute__ ((__malloc__))
     __attribute__ ((__alloc_size__ (1))) ;




extern int posix_memalign (void **__memptr, size_t __alignment, size_t __size)
     __attribute__ ((__nothrow__ , __leaf__)) __attribute__ ((__nonnull__ (1))) ;




extern void *aligned_alloc (size_t __alignment, size_t __size)
     __attribute__ ((__nothrow__ , __leaf__)) __attribute__ ((__malloc__)) __attribute__ ((__alloc_align__ (1)))
     __attribute__ ((__alloc_size__ (2))) ;



extern void abort (void) __attribute__ ((__nothrow__ , __leaf__)) __attribute__ ((__noreturn__));



extern int atexit (void (*__func) (void)) __attribute__ ((__nothrow__ , __leaf__)) __attribute__ ((__nonnull__ (1)));







extern int at_quick_exit (void (*__func) (void)) __attribute__ ((__nothrow__ , __leaf__)) __attribute__ ((__nonnull__ (1)));






extern int on_exit (void (*__func) (int __status, void *__arg), void *__arg)
     __attribute__ ((__nothrow__ , __leaf__)) __attribute__ ((__nonnull__ (1)));





extern void exit (int __status) __attribute__ ((__nothrow__ , __leaf__)) __attribute__ ((__noreturn__));





extern void quick_exit (int __status) __attribute__ ((__nothrow__ , __leaf__)) __attribute__ ((__noreturn__));





extern void _Exit (int __status) __attribute__ ((__nothrow__ , __leaf__)) __attribute__ ((__noreturn__));




extern char *getenv (const char *__name) __attribute__ ((__nothrow__ , __leaf__)) __attribute__ ((__nonnull__ (1))) ;
# 667 "/usr/include/stdlib.h" 3 4
extern int putenv (char *__string) __attribute__ ((__nothrow__ , __leaf__)) __attribute__ ((__nonnull__ (1)));





extern int setenv (const char *__name, const char *__value, int __replace)
     __attribute__ ((__nothrow__ , __leaf__)) __attribute__ ((__nonnull__ (2)));


extern int unsetenv (const char *__name) __attribute__ ((__nothrow__ , __leaf__)) __attribute__ ((__nonnull__ (1)));






extern int clearenv (void) __attribute__ ((__nothrow__ , __leaf__));
# 695 "/usr/include/stdlib.h" 3 4
extern char *mktemp (char *__template) __attribute__ ((__nothrow__ , __leaf__)) __attribute__ ((__nonnull__ (1)));
# 708 "/usr/include/stdlib.h" 3 4
extern int mkstemp (char *__template) __attribute__ ((__nonnull__ (1))) ;
# 730 "/usr/include/stdlib.h" 3 4
extern int mkstemps (char *__template, int __suffixlen) __attribute__ ((__nonnull__ (1))) ;
# 751 "/usr/include/stdlib.h" 3 4
extern char *mkdtemp (char *__template) __attribute__ ((__nothrow__ , __leaf__)) __attribute__ ((__nonnull__ (1))) ;
# 804 "/usr/include/stdlib.h" 3 4
extern int system (const char *__command) ;
# 821 "/usr/include/stdlib.h" 3 4
extern char *realpath (const char *__restrict __name,
         char *__restrict __resolved) __attribute__ ((__nothrow__ , __leaf__)) ;






typedef int (*__compar_fn_t) (const void *, const void *);
# 841 "/usr/include/stdlib.h" 3 4
extern void *bsearch (const void *__key, const void *__base,
        size_t __nmemb, size_t __size, __compar_fn_t __compar)
     __attribute__ ((__nonnull__ (1, 2, 5))) ;







extern void qsort (void *__base, size_t __nmemb, size_t __size,
     __compar_fn_t __compar) __attribute__ ((__nonnull__ (1, 4)));
# 861 "/usr/include/stdlib.h" 3 4
extern int abs (int __x) __attribute__ ((__nothrow__ , __leaf__)) __attribute__ ((__const__)) ;
extern long int labs (long int __x) __attribute__ ((__nothrow__ , __leaf__)) __attribute__ ((__const__)) ;


__extension__ extern long long int llabs (long long int __x)
     __attribute__ ((__nothrow__ , __leaf__)) __attribute__ ((__const__)) ;






extern div_t div (int __numer, int __denom)
     __attribute__ ((__nothrow__ , __leaf__)) __attribute__ ((__const__)) ;
extern ldiv_t ldiv (long int __numer, long int __denom)
     __attribute__ ((__nothrow__ , __leaf__)) __attribute__ ((__const__)) ;


__extension__ extern lldiv_t lldiv (long long int __numer,
        long long int __denom)
     __attribute__ ((__nothrow__ , __leaf__)) __attribute__ ((__const__)) ;
# 893 "/usr/include/stdlib.h" 3 4
extern char *ecvt (double __value, int __ndigit, int *__restrict __decpt,
     int *__restrict __sign) __attribute__ ((__nothrow__ , __leaf__)) __attribute__ ((__nonnull__ (3, 4))) ;




extern char *fcvt (double __value, int __ndigit, int *__restrict __decpt,
     int *__restrict __sign) __attribute__ ((__nothrow__ , __leaf__)) __attribute__ ((__nonnull__ (3, 4))) ;




extern char *gcvt (double __value, int __ndigit, char *__buf)
     __attribute__ ((__nothrow__ , __leaf__)) __attribute__ ((__nonnull__ (3))) ;




extern char *qecvt (long double __value, int __ndigit,
      int *__restrict __decpt, int *__restrict __sign)
     __attribute__ ((__nothrow__ , __leaf__)) __attribute__ ((__nonnull__ (3, 4))) ;
extern char *qfcvt (long double __value, int __ndigit,
      int *__restrict __decpt, int *__restrict __sign)
     __attribute__ ((__nothrow__ , __leaf__)) __attribute__ ((__nonnull__ (3, 4))) ;
extern char *qgcvt (long double __value, int __ndigit, char *__buf)
     __attribute__ ((__nothrow__ , __leaf__)) __attribute__ ((__nonnull__ (3))) ;




extern int ecvt_r (double __value, int __ndigit, int *__restrict __decpt,
     int *__restrict __sign, char *__restrict __buf,
     size_t __len) __attribute__ ((__nothrow__ , __leaf__)) __attribute__ ((__nonnull__ (3, 4, 5)));
extern int fcvt_r (double __value, int __ndigit, int *__restrict __decpt,
     int *__restrict __sign, char *__restrict __buf,
     size_t __len) __attribute__ ((__nothrow__ , __leaf__)) __attribute__ ((__nonnull__ (3, 4, 5)));

extern int qecvt_r (long double __value, int __ndigit,
      int *__restrict __decpt, int *__restrict __sign,
      char *__restrict __buf, size_t __len)
     __attribute__ ((__nothrow__ , __leaf__)) __attribute__ ((__nonnull__ (3, 4, 5)));
extern int qfcvt_r (long double __value, int __ndigit,
      int *__restrict __decpt, int *__restrict __sign,
      char *__restrict __buf, size_t __len)
     __attribute__ ((__nothrow__ , __leaf__)) __attribute__ ((__nonnull__ (3, 4, 5)));





extern int mblen (const char *__s, size_t __n) __attribute__ ((__nothrow__ , __leaf__));


extern int mbtowc (wchar_t *__restrict __pwc,
     const char *__restrict __s, size_t __n) __attribute__ ((__nothrow__ , __leaf__));


extern int wctomb (char *__s, wchar_t __wchar) __attribute__ ((__nothrow__ , __leaf__));



extern size_t mbstowcs (wchar_t *__restrict __pwcs,
   const char *__restrict __s, size_t __n) __attribute__ ((__nothrow__ , __leaf__))
    __attribute__ ((__access__ (__read_only__, 2)));

extern size_t wcstombs (char *__restrict __s,
   const wchar_t *__restrict __pwcs, size_t __n)
     __attribute__ ((__nothrow__ , __leaf__))
  __attribute__ ((__access__ (__write_only__, 1, 3)))
  __attribute__ ((__access__ (__read_only__, 2)));






extern int rpmatch (const char *__response) __attribute__ ((__nothrow__ , __leaf__)) __attribute__ ((__nonnull__ (1))) ;
# 980 "/usr/include/stdlib.h" 3 4
extern int getsubopt (char **__restrict __optionp,
        char *const *__restrict __tokens,
        char **__restrict __valuep)
     __attribute__ ((__nothrow__ , __leaf__)) __attribute__ ((__nonnull__ (1, 2, 3))) ;
# 1026 "/usr/include/stdlib.h" 3 4
extern int getloadavg (double __loadavg[], int __nelem)
     __attribute__ ((__nothrow__ , __leaf__)) __attribute__ ((__nonnull__ (1)));
# 1036 "/usr/include/stdlib.h" 3 4
# 1 "/usr/include/bits/stdlib-float.h" 1 3 4
# 1037 "/usr/include/stdlib.h" 2 3 4
# 1048 "/usr/include/stdlib.h" 3 4

# 2 "src/main.c" 2
# 1 "/usr/include/stdio.h" 1 3 4
# 27 "/usr/include/stdio.h" 3 4
# 1 "/usr/include/bits/libc-header-start.h" 1 3 4
# 28 "/usr/include/stdio.h" 2 3 4





# 1 "/usr/lib/gcc/x86_64-pc-linux-gnu/12.2.0/include/stddef.h" 1 3 4
# 34 "/usr/include/stdio.h" 2 3 4


# 1 "/usr/lib/gcc/x86_64-pc-linux-gnu/12.2.0/include/stdarg.h" 1 3 4
# 40 "/usr/lib/gcc/x86_64-pc-linux-gnu/12.2.0/include/stdarg.h" 3 4
typedef __builtin_va_list __gnuc_va_list;
# 37 "/usr/include/stdio.h" 2 3 4


# 1 "/usr/include/bits/types/__fpos_t.h" 1 3 4




# 1 "/usr/include/bits/types/__mbstate_t.h" 1 3 4
# 13 "/usr/include/bits/types/__mbstate_t.h" 3 4
typedef struct
{
  int __count;
  union
  {
    unsigned int __wch;
    char __wchb[4];
  } __value;
} __mbstate_t;
# 6 "/usr/include/bits/types/__fpos_t.h" 2 3 4




typedef struct _G_fpos_t
{
  __off_t __pos;
  __mbstate_t __state;
} __fpos_t;
# 40 "/usr/include/stdio.h" 2 3 4
# 1 "/usr/include/bits/types/__fpos64_t.h" 1 3 4
# 10 "/usr/include/bits/types/__fpos64_t.h" 3 4
typedef struct _G_fpos64_t
{
  __off64_t __pos;
  __mbstate_t __state;
} __fpos64_t;
# 41 "/usr/include/stdio.h" 2 3 4
# 1 "/usr/include/bits/types/__FILE.h" 1 3 4



struct _IO_FILE;
typedef struct _IO_FILE __FILE;
# 42 "/usr/include/stdio.h" 2 3 4
# 1 "/usr/include/bits/types/FILE.h" 1 3 4



struct _IO_FILE;


typedef struct _IO_FILE FILE;
# 43 "/usr/include/stdio.h" 2 3 4
# 1 "/usr/include/bits/types/struct_FILE.h" 1 3 4
# 35 "/usr/include/bits/types/struct_FILE.h" 3 4
struct _IO_FILE;
struct _IO_marker;
struct _IO_codecvt;
struct _IO_wide_data;




typedef void _IO_lock_t;





struct _IO_FILE
{
  int _flags;


  char *_IO_read_ptr;
  char *_IO_read_end;
  char *_IO_read_base;
  char *_IO_write_base;
  char *_IO_write_ptr;
  char *_IO_write_end;
  char *_IO_buf_base;
  char *_IO_buf_end;


  char *_IO_save_base;
  char *_IO_backup_base;
  char *_IO_save_end;

  struct _IO_marker *_markers;

  struct _IO_FILE *_chain;

  int _fileno;
  int _flags2;
  __off_t _old_offset;


  unsigned short _cur_column;
  signed char _vtable_offset;
  char _shortbuf[1];

  _IO_lock_t *_lock;







  __off64_t _offset;

  struct _IO_codecvt *_codecvt;
  struct _IO_wide_data *_wide_data;
  struct _IO_FILE *_freeres_list;
  void *_freeres_buf;
  size_t __pad5;
  int _mode;

  char _unused2[15 * sizeof (int) - 4 * sizeof (void *) - sizeof (size_t)];
};
# 44 "/usr/include/stdio.h" 2 3 4
# 52 "/usr/include/stdio.h" 3 4
typedef __gnuc_va_list va_list;
# 84 "/usr/include/stdio.h" 3 4
typedef __fpos_t fpos_t;
# 133 "/usr/include/stdio.h" 3 4
# 1 "/usr/include/bits/stdio_lim.h" 1 3 4
# 134 "/usr/include/stdio.h" 2 3 4
# 143 "/usr/include/stdio.h" 3 4
extern FILE *stdin;
extern FILE *stdout;
extern FILE *stderr;






extern int remove (const char *__filename) __attribute__ ((__nothrow__ , __leaf__));

extern int rename (const char *__old, const char *__new) __attribute__ ((__nothrow__ , __leaf__));



extern int renameat (int __oldfd, const char *__old, int __newfd,
       const char *__new) __attribute__ ((__nothrow__ , __leaf__));
# 178 "/usr/include/stdio.h" 3 4
extern int fclose (FILE *__stream);
# 188 "/usr/include/stdio.h" 3 4
extern FILE *tmpfile (void)
  __attribute__ ((__malloc__)) __attribute__ ((__malloc__ (fclose, 1))) ;
# 205 "/usr/include/stdio.h" 3 4
extern char *tmpnam (char[20]) __attribute__ ((__nothrow__ , __leaf__)) ;




extern char *tmpnam_r (char __s[20]) __attribute__ ((__nothrow__ , __leaf__)) ;
# 222 "/usr/include/stdio.h" 3 4
extern char *tempnam (const char *__dir, const char *__pfx)
   __attribute__ ((__nothrow__ , __leaf__)) __attribute__ ((__malloc__)) __attribute__ ((__malloc__ (__builtin_free, 1)));






extern int fflush (FILE *__stream);
# 239 "/usr/include/stdio.h" 3 4
extern int fflush_unlocked (FILE *__stream);
# 258 "/usr/include/stdio.h" 3 4
extern FILE *fopen (const char *__restrict __filename,
      const char *__restrict __modes)
  __attribute__ ((__malloc__)) __attribute__ ((__malloc__ (fclose, 1))) ;




extern FILE *freopen (const char *__restrict __filename,
        const char *__restrict __modes,
        FILE *__restrict __stream) ;
# 293 "/usr/include/stdio.h" 3 4
extern FILE *fdopen (int __fd, const char *__modes) __attribute__ ((__nothrow__ , __leaf__))
  __attribute__ ((__malloc__)) __attribute__ ((__malloc__ (fclose, 1))) ;
# 308 "/usr/include/stdio.h" 3 4
extern FILE *fmemopen (void *__s, size_t __len, const char *__modes)
  __attribute__ ((__nothrow__ , __leaf__)) __attribute__ ((__malloc__)) __attribute__ ((__malloc__ (fclose, 1))) ;




extern FILE *open_memstream (char **__bufloc, size_t *__sizeloc) __attribute__ ((__nothrow__ , __leaf__))
  __attribute__ ((__malloc__)) __attribute__ ((__malloc__ (fclose, 1))) ;
# 328 "/usr/include/stdio.h" 3 4
extern void setbuf (FILE *__restrict __stream, char *__restrict __buf) __attribute__ ((__nothrow__ , __leaf__));



extern int setvbuf (FILE *__restrict __stream, char *__restrict __buf,
      int __modes, size_t __n) __attribute__ ((__nothrow__ , __leaf__));




extern void setbuffer (FILE *__restrict __stream, char *__restrict __buf,
         size_t __size) __attribute__ ((__nothrow__ , __leaf__));


extern void setlinebuf (FILE *__stream) __attribute__ ((__nothrow__ , __leaf__));







extern int fprintf (FILE *__restrict __stream,
      const char *__restrict __format, ...);




extern int printf (const char *__restrict __format, ...);

extern int sprintf (char *__restrict __s,
      const char *__restrict __format, ...) __attribute__ ((__nothrow__));





extern int vfprintf (FILE *__restrict __s, const char *__restrict __format,
       __gnuc_va_list __arg);




extern int vprintf (const char *__restrict __format, __gnuc_va_list __arg);

extern int vsprintf (char *__restrict __s, const char *__restrict __format,
       __gnuc_va_list __arg) __attribute__ ((__nothrow__));



extern int snprintf (char *__restrict __s, size_t __maxlen,
       const char *__restrict __format, ...)
     __attribute__ ((__nothrow__)) __attribute__ ((__format__ (__printf__, 3, 4)));

extern int vsnprintf (char *__restrict __s, size_t __maxlen,
        const char *__restrict __format, __gnuc_va_list __arg)
     __attribute__ ((__nothrow__)) __attribute__ ((__format__ (__printf__, 3, 0)));
# 403 "/usr/include/stdio.h" 3 4
extern int vdprintf (int __fd, const char *__restrict __fmt,
       __gnuc_va_list __arg)
     __attribute__ ((__format__ (__printf__, 2, 0)));
extern int dprintf (int __fd, const char *__restrict __fmt, ...)
     __attribute__ ((__format__ (__printf__, 2, 3)));







extern int fscanf (FILE *__restrict __stream,
     const char *__restrict __format, ...) ;




extern int scanf (const char *__restrict __format, ...) ;

extern int sscanf (const char *__restrict __s,
     const char *__restrict __format, ...) __attribute__ ((__nothrow__ , __leaf__));
# 434 "/usr/include/stdio.h" 3 4
extern int fscanf (FILE *__restrict __stream, const char *__restrict __format, ...) __asm__ ("" "__isoc99_fscanf")

                               ;
extern int scanf (const char *__restrict __format, ...) __asm__ ("" "__isoc99_scanf")
                              ;
extern int sscanf (const char *__restrict __s, const char *__restrict __format, ...) __asm__ ("" "__isoc99_sscanf") __attribute__ ((__nothrow__ , __leaf__))

                      ;
# 459 "/usr/include/stdio.h" 3 4
extern int vfscanf (FILE *__restrict __s, const char *__restrict __format,
      __gnuc_va_list __arg)
     __attribute__ ((__format__ (__scanf__, 2, 0))) ;





extern int vscanf (const char *__restrict __format, __gnuc_va_list __arg)
     __attribute__ ((__format__ (__scanf__, 1, 0))) ;


extern int vsscanf (const char *__restrict __s,
      const char *__restrict __format, __gnuc_va_list __arg)
     __attribute__ ((__nothrow__ , __leaf__)) __attribute__ ((__format__ (__scanf__, 2, 0)));





extern int vfscanf (FILE *__restrict __s, const char *__restrict __format, __gnuc_va_list __arg) __asm__ ("" "__isoc99_vfscanf")



     __attribute__ ((__format__ (__scanf__, 2, 0))) ;
extern int vscanf (const char *__restrict __format, __gnuc_va_list __arg) __asm__ ("" "__isoc99_vscanf")

     __attribute__ ((__format__ (__scanf__, 1, 0))) ;
extern int vsscanf (const char *__restrict __s, const char *__restrict __format, __gnuc_va_list __arg) __asm__ ("" "__isoc99_vsscanf") __attribute__ ((__nothrow__ , __leaf__))



     __attribute__ ((__format__ (__scanf__, 2, 0)));
# 513 "/usr/include/stdio.h" 3 4
extern int fgetc (FILE *__stream);
extern int getc (FILE *__stream);





extern int getchar (void);






extern int getc_unlocked (FILE *__stream);
extern int getchar_unlocked (void);
# 538 "/usr/include/stdio.h" 3 4
extern int fgetc_unlocked (FILE *__stream);
# 549 "/usr/include/stdio.h" 3 4
extern int fputc (int __c, FILE *__stream);
extern int putc (int __c, FILE *__stream);





extern int putchar (int __c);
# 565 "/usr/include/stdio.h" 3 4
extern int fputc_unlocked (int __c, FILE *__stream);







extern int putc_unlocked (int __c, FILE *__stream);
extern int putchar_unlocked (int __c);






extern int getw (FILE *__stream);


extern int putw (int __w, FILE *__stream);







extern char *fgets (char *__restrict __s, int __n, FILE *__restrict __stream)
     __attribute__ ((__access__ (__write_only__, 1, 2)));
# 632 "/usr/include/stdio.h" 3 4
extern __ssize_t __getdelim (char **__restrict __lineptr,
                             size_t *__restrict __n, int __delimiter,
                             FILE *__restrict __stream) ;
extern __ssize_t getdelim (char **__restrict __lineptr,
                           size_t *__restrict __n, int __delimiter,
                           FILE *__restrict __stream) ;







extern __ssize_t getline (char **__restrict __lineptr,
                          size_t *__restrict __n,
                          FILE *__restrict __stream) ;







extern int fputs (const char *__restrict __s, FILE *__restrict __stream);





extern int puts (const char *__s);






extern int ungetc (int __c, FILE *__stream);






extern size_t fread (void *__restrict __ptr, size_t __size,
       size_t __n, FILE *__restrict __stream) ;




extern size_t fwrite (const void *__restrict __ptr, size_t __size,
        size_t __n, FILE *__restrict __s);
# 702 "/usr/include/stdio.h" 3 4
extern size_t fread_unlocked (void *__restrict __ptr, size_t __size,
         size_t __n, FILE *__restrict __stream) ;
extern size_t fwrite_unlocked (const void *__restrict __ptr, size_t __size,
          size_t __n, FILE *__restrict __stream);







extern int fseek (FILE *__stream, long int __off, int __whence);




extern long int ftell (FILE *__stream) ;




extern void rewind (FILE *__stream);
# 736 "/usr/include/stdio.h" 3 4
extern int fseeko (FILE *__stream, __off_t __off, int __whence);




extern __off_t ftello (FILE *__stream) ;
# 760 "/usr/include/stdio.h" 3 4
extern int fgetpos (FILE *__restrict __stream, fpos_t *__restrict __pos);




extern int fsetpos (FILE *__stream, const fpos_t *__pos);
# 786 "/usr/include/stdio.h" 3 4
extern void clearerr (FILE *__stream) __attribute__ ((__nothrow__ , __leaf__));

extern int feof (FILE *__stream) __attribute__ ((__nothrow__ , __leaf__)) ;

extern int ferror (FILE *__stream) __attribute__ ((__nothrow__ , __leaf__)) ;



extern void clearerr_unlocked (FILE *__stream) __attribute__ ((__nothrow__ , __leaf__));
extern int feof_unlocked (FILE *__stream) __attribute__ ((__nothrow__ , __leaf__)) ;
extern int ferror_unlocked (FILE *__stream) __attribute__ ((__nothrow__ , __leaf__)) ;







extern void perror (const char *__s);




extern int fileno (FILE *__stream) __attribute__ ((__nothrow__ , __leaf__)) ;




extern int fileno_unlocked (FILE *__stream) __attribute__ ((__nothrow__ , __leaf__)) ;
# 823 "/usr/include/stdio.h" 3 4
extern int pclose (FILE *__stream);





extern FILE *popen (const char *__command, const char *__modes)
  __attribute__ ((__malloc__)) __attribute__ ((__malloc__ (pclose, 1))) ;






extern char *ctermid (char *__s) __attribute__ ((__nothrow__ , __leaf__))
  __attribute__ ((__access__ (__write_only__, 1)));
# 867 "/usr/include/stdio.h" 3 4
extern void flockfile (FILE *__stream) __attribute__ ((__nothrow__ , __leaf__));



extern int ftrylockfile (FILE *__stream) __attribute__ ((__nothrow__ , __leaf__)) ;


extern void funlockfile (FILE *__stream) __attribute__ ((__nothrow__ , __leaf__));
# 885 "/usr/include/stdio.h" 3 4
extern int __uflow (FILE *);
extern int __overflow (FILE *, int);
# 909 "/usr/include/stdio.h" 3 4

# 3 "src/main.c" 2
# 1 "/usr/lib/gcc/x86_64-pc-linux-gnu/12.2.0/include/stddef.h" 1 3 4
# 145 "/usr/lib/gcc/x86_64-pc-linux-gnu/12.2.0/include/stddef.h" 3 4
typedef long int ptrdiff_t;
# 424 "/usr/lib/gcc/x86_64-pc-linux-gnu/12.2.0/include/stddef.h" 3 4
typedef struct {
  long long __max_align_ll __attribute__((__aligned__(__alignof__(long long))));
  long double __max_align_ld __attribute__((__aligned__(__alignof__(long double))));
# 435 "/usr/lib/gcc/x86_64-pc-linux-gnu/12.2.0/include/stddef.h" 3 4
} max_align_t;
# 4 "src/main.c" 2
# 1 "/usr/lib/gcc/x86_64-pc-linux-gnu/12.2.0/include/stdint.h" 1 3 4
# 9 "/usr/lib/gcc/x86_64-pc-linux-gnu/12.2.0/include/stdint.h" 3 4
# 1 "/usr/include/stdint.h" 1 3 4
# 26 "/usr/include/stdint.h" 3 4
# 1 "/usr/include/bits/libc-header-start.h" 1 3 4
# 27 "/usr/include/stdint.h" 2 3 4

# 1 "/usr/include/bits/wchar.h" 1 3 4
# 29 "/usr/include/stdint.h" 2 3 4
# 1 "/usr/include/bits/wordsize.h" 1 3 4
# 30 "/usr/include/stdint.h" 2 3 4







# 1 "/usr/include/bits/stdint-uintn.h" 1 3 4
# 24 "/usr/include/bits/stdint-uintn.h" 3 4
typedef __uint8_t uint8_t;
typedef __uint16_t uint16_t;
typedef __uint32_t uint32_t;
typedef __uint64_t uint64_t;
# 38 "/usr/include/stdint.h" 2 3 4





typedef __int_least8_t int_least8_t;
typedef __int_least16_t int_least16_t;
typedef __int_least32_t int_least32_t;
typedef __int_least64_t int_least64_t;


typedef __uint_least8_t uint_least8_t;
typedef __uint_least16_t uint_least16_t;
typedef __uint_least32_t uint_least32_t;
typedef __uint_least64_t uint_least64_t;





typedef signed char int_fast8_t;

typedef long int int_fast16_t;
typedef long int int_fast32_t;
typedef long int int_fast64_t;
# 71 "/usr/include/stdint.h" 3 4
typedef unsigned char uint_fast8_t;

typedef unsigned long int uint_fast16_t;
typedef unsigned long int uint_fast32_t;
typedef unsigned long int uint_fast64_t;
# 87 "/usr/include/stdint.h" 3 4
typedef long int intptr_t;


typedef unsigned long int uintptr_t;
# 101 "/usr/include/stdint.h" 3 4
typedef __intmax_t intmax_t;
typedef __uintmax_t uintmax_t;
# 10 "/usr/lib/gcc/x86_64-pc-linux-gnu/12.2.0/include/stdint.h" 2 3 4
# 5 "src/main.c" 2
# 1 "/usr/lib/gcc/x86_64-pc-linux-gnu/12.2.0/include/stdarg.h" 1 3 4
# 6 "src/main.c" 2
# 1 "/usr/include/string.h" 1 3 4
# 26 "/usr/include/string.h" 3 4
# 1 "/usr/include/bits/libc-header-start.h" 1 3 4
# 27 "/usr/include/string.h" 2 3 4






# 1 "/usr/lib/gcc/x86_64-pc-linux-gnu/12.2.0/include/stddef.h" 1 3 4
# 34 "/usr/include/string.h" 2 3 4
# 43 "/usr/include/string.h" 3 4
extern void *memcpy (void *__restrict __dest, const void *__restrict __src,
       size_t __n) __attribute__ ((__nothrow__ , __leaf__)) __attribute__ ((__nonnull__ (1, 2)));


extern void *memmove (void *__dest, const void *__src, size_t __n)
     __attribute__ ((__nothrow__ , __leaf__)) __attribute__ ((__nonnull__ (1, 2)));





extern void *memccpy (void *__restrict __dest, const void *__restrict __src,
        int __c, size_t __n)
    __attribute__ ((__nothrow__ , __leaf__)) __attribute__ ((__nonnull__ (1, 2))) __attribute__ ((__access__ (__write_only__, 1, 4)));




extern void *memset (void *__s, int __c, size_t __n) __attribute__ ((__nothrow__ , __leaf__)) __attribute__ ((__nonnull__ (1)));


extern int memcmp (const void *__s1, const void *__s2, size_t __n)
     __attribute__ ((__nothrow__ , __leaf__)) __attribute__ ((__pure__)) __attribute__ ((__nonnull__ (1, 2)));
# 80 "/usr/include/string.h" 3 4
extern int __memcmpeq (const void *__s1, const void *__s2, size_t __n)
     __attribute__ ((__nothrow__ , __leaf__)) __attribute__ ((__pure__)) __attribute__ ((__nonnull__ (1, 2)));
# 107 "/usr/include/string.h" 3 4
extern void *memchr (const void *__s, int __c, size_t __n)
      __attribute__ ((__nothrow__ , __leaf__)) __attribute__ ((__pure__)) __attribute__ ((__nonnull__ (1)));
# 141 "/usr/include/string.h" 3 4
extern char *strcpy (char *__restrict __dest, const char *__restrict __src)
     __attribute__ ((__nothrow__ , __leaf__)) __attribute__ ((__nonnull__ (1, 2)));

extern char *strncpy (char *__restrict __dest,
        const char *__restrict __src, size_t __n)
     __attribute__ ((__nothrow__ , __leaf__)) __attribute__ ((__nonnull__ (1, 2)));


extern char *strcat (char *__restrict __dest, const char *__restrict __src)
     __attribute__ ((__nothrow__ , __leaf__)) __attribute__ ((__nonnull__ (1, 2)));

extern char *strncat (char *__restrict __dest, const char *__restrict __src,
        size_t __n) __attribute__ ((__nothrow__ , __leaf__)) __attribute__ ((__nonnull__ (1, 2)));


extern int strcmp (const char *__s1, const char *__s2)
     __attribute__ ((__nothrow__ , __leaf__)) __attribute__ ((__pure__)) __attribute__ ((__nonnull__ (1, 2)));

extern int strncmp (const char *__s1, const char *__s2, size_t __n)
     __attribute__ ((__nothrow__ , __leaf__)) __attribute__ ((__pure__)) __attribute__ ((__nonnull__ (1, 2)));


extern int strcoll (const char *__s1, const char *__s2)
     __attribute__ ((__nothrow__ , __leaf__)) __attribute__ ((__pure__)) __attribute__ ((__nonnull__ (1, 2)));

extern size_t strxfrm (char *__restrict __dest,
         const char *__restrict __src, size_t __n)
    __attribute__ ((__nothrow__ , __leaf__)) __attribute__ ((__nonnull__ (2))) __attribute__ ((__access__ (__write_only__, 1, 3)));



# 1 "/usr/include/bits/types/locale_t.h" 1 3 4
# 22 "/usr/include/bits/types/locale_t.h" 3 4
# 1 "/usr/include/bits/types/__locale_t.h" 1 3 4
# 27 "/usr/include/bits/types/__locale_t.h" 3 4
struct __locale_struct
{

  struct __locale_data *__locales[13];


  const unsigned short int *__ctype_b;
  const int *__ctype_tolower;
  const int *__ctype_toupper;


  const char *__names[13];
};

typedef struct __locale_struct *__locale_t;
# 23 "/usr/include/bits/types/locale_t.h" 2 3 4

typedef __locale_t locale_t;
# 173 "/usr/include/string.h" 2 3 4


extern int strcoll_l (const char *__s1, const char *__s2, locale_t __l)
     __attribute__ ((__nothrow__ , __leaf__)) __attribute__ ((__pure__)) __attribute__ ((__nonnull__ (1, 2, 3)));


extern size_t strxfrm_l (char *__dest, const char *__src, size_t __n,
    locale_t __l) __attribute__ ((__nothrow__ , __leaf__)) __attribute__ ((__nonnull__ (2, 4)))
     __attribute__ ((__access__ (__write_only__, 1, 3)));





extern char *strdup (const char *__s)
     __attribute__ ((__nothrow__ , __leaf__)) __attribute__ ((__malloc__)) __attribute__ ((__nonnull__ (1)));






extern char *strndup (const char *__string, size_t __n)
     __attribute__ ((__nothrow__ , __leaf__)) __attribute__ ((__malloc__)) __attribute__ ((__nonnull__ (1)));
# 246 "/usr/include/string.h" 3 4
extern char *strchr (const char *__s, int __c)
     __attribute__ ((__nothrow__ , __leaf__)) __attribute__ ((__pure__)) __attribute__ ((__nonnull__ (1)));
# 273 "/usr/include/string.h" 3 4
extern char *strrchr (const char *__s, int __c)
     __attribute__ ((__nothrow__ , __leaf__)) __attribute__ ((__pure__)) __attribute__ ((__nonnull__ (1)));
# 293 "/usr/include/string.h" 3 4
extern size_t strcspn (const char *__s, const char *__reject)
     __attribute__ ((__nothrow__ , __leaf__)) __attribute__ ((__pure__)) __attribute__ ((__nonnull__ (1, 2)));


extern size_t strspn (const char *__s, const char *__accept)
     __attribute__ ((__nothrow__ , __leaf__)) __attribute__ ((__pure__)) __attribute__ ((__nonnull__ (1, 2)));
# 323 "/usr/include/string.h" 3 4
extern char *strpbrk (const char *__s, const char *__accept)
     __attribute__ ((__nothrow__ , __leaf__)) __attribute__ ((__pure__)) __attribute__ ((__nonnull__ (1, 2)));
# 350 "/usr/include/string.h" 3 4
extern char *strstr (const char *__haystack, const char *__needle)
     __attribute__ ((__nothrow__ , __leaf__)) __attribute__ ((__pure__)) __attribute__ ((__nonnull__ (1, 2)));




extern char *strtok (char *__restrict __s, const char *__restrict __delim)
     __attribute__ ((__nothrow__ , __leaf__)) __attribute__ ((__nonnull__ (2)));



extern char *__strtok_r (char *__restrict __s,
    const char *__restrict __delim,
    char **__restrict __save_ptr)
     __attribute__ ((__nothrow__ , __leaf__)) __attribute__ ((__nonnull__ (2, 3)));

extern char *strtok_r (char *__restrict __s, const char *__restrict __delim,
         char **__restrict __save_ptr)
     __attribute__ ((__nothrow__ , __leaf__)) __attribute__ ((__nonnull__ (2, 3)));
# 407 "/usr/include/string.h" 3 4
extern size_t strlen (const char *__s)
     __attribute__ ((__nothrow__ , __leaf__)) __attribute__ ((__pure__)) __attribute__ ((__nonnull__ (1)));




extern size_t strnlen (const char *__string, size_t __maxlen)
     __attribute__ ((__nothrow__ , __leaf__)) __attribute__ ((__pure__)) __attribute__ ((__nonnull__ (1)));




extern char *strerror (int __errnum) __attribute__ ((__nothrow__ , __leaf__));
# 432 "/usr/include/string.h" 3 4
extern int strerror_r (int __errnum, char *__buf, size_t __buflen) __asm__ ("" "__xpg_strerror_r") __attribute__ ((__nothrow__ , __leaf__))

                        __attribute__ ((__nonnull__ (2)))
    __attribute__ ((__access__ (__write_only__, 2, 3)));
# 458 "/usr/include/string.h" 3 4
extern char *strerror_l (int __errnum, locale_t __l) __attribute__ ((__nothrow__ , __leaf__));



# 1 "/usr/include/strings.h" 1 3 4
# 23 "/usr/include/strings.h" 3 4
# 1 "/usr/lib/gcc/x86_64-pc-linux-gnu/12.2.0/include/stddef.h" 1 3 4
# 24 "/usr/include/strings.h" 2 3 4










extern int bcmp (const void *__s1, const void *__s2, size_t __n)
     __attribute__ ((__nothrow__ , __leaf__)) __attribute__ ((__pure__)) __attribute__ ((__nonnull__ (1, 2)));


extern void bcopy (const void *__src, void *__dest, size_t __n)
  __attribute__ ((__nothrow__ , __leaf__)) __attribute__ ((__nonnull__ (1, 2)));


extern void bzero (void *__s, size_t __n) __attribute__ ((__nothrow__ , __leaf__)) __attribute__ ((__nonnull__ (1)));
# 68 "/usr/include/strings.h" 3 4
extern char *index (const char *__s, int __c)
     __attribute__ ((__nothrow__ , __leaf__)) __attribute__ ((__pure__)) __attribute__ ((__nonnull__ (1)));
# 96 "/usr/include/strings.h" 3 4
extern char *rindex (const char *__s, int __c)
     __attribute__ ((__nothrow__ , __leaf__)) __attribute__ ((__pure__)) __attribute__ ((__nonnull__ (1)));






extern int ffs (int __i) __attribute__ ((__nothrow__ , __leaf__)) __attribute__ ((__const__));





extern int ffsl (long int __l) __attribute__ ((__nothrow__ , __leaf__)) __attribute__ ((__const__));
__extension__ extern int ffsll (long long int __ll)
     __attribute__ ((__nothrow__ , __leaf__)) __attribute__ ((__const__));



extern int strcasecmp (const char *__s1, const char *__s2)
     __attribute__ ((__nothrow__ , __leaf__)) __attribute__ ((__pure__)) __attribute__ ((__nonnull__ (1, 2)));


extern int strncasecmp (const char *__s1, const char *__s2, size_t __n)
     __attribute__ ((__nothrow__ , __leaf__)) __attribute__ ((__pure__)) __attribute__ ((__nonnull__ (1, 2)));






extern int strcasecmp_l (const char *__s1, const char *__s2, locale_t __loc)
     __attribute__ ((__nothrow__ , __leaf__)) __attribute__ ((__pure__)) __attribute__ ((__nonnull__ (1, 2, 3)));



extern int strncasecmp_l (const char *__s1, const char *__s2,
     size_t __n, locale_t __loc)
     __attribute__ ((__nothrow__ , __leaf__)) __attribute__ ((__pure__)) __attribute__ ((__nonnull__ (1, 2, 4)));



# 463 "/usr/include/string.h" 2 3 4



extern void explicit_bzero (void *__s, size_t __n) __attribute__ ((__nothrow__ , __leaf__)) __attribute__ ((__nonnull__ (1)))
    __attribute__ ((__access__ (__write_only__, 1, 2)));



extern char *strsep (char **__restrict __stringp,
       const char *__restrict __delim)
     __attribute__ ((__nothrow__ , __leaf__)) __attribute__ ((__nonnull__ (1, 2)));




extern char *strsignal (int __sig) __attribute__ ((__nothrow__ , __leaf__));
# 489 "/usr/include/string.h" 3 4
extern char *__stpcpy (char *__restrict __dest, const char *__restrict __src)
     __attribute__ ((__nothrow__ , __leaf__)) __attribute__ ((__nonnull__ (1, 2)));
extern char *stpcpy (char *__restrict __dest, const char *__restrict __src)
     __attribute__ ((__nothrow__ , __leaf__)) __attribute__ ((__nonnull__ (1, 2)));



extern char *__stpncpy (char *__restrict __dest,
   const char *__restrict __src, size_t __n)
     __attribute__ ((__nothrow__ , __leaf__)) __attribute__ ((__nonnull__ (1, 2)));
extern char *stpncpy (char *__restrict __dest,
        const char *__restrict __src, size_t __n)
     __attribute__ ((__nothrow__ , __leaf__)) __attribute__ ((__nonnull__ (1, 2)));
# 539 "/usr/include/string.h" 3 4

# 7 "src/main.c" 2
# 1 "/usr/lib/gcc/x86_64-pc-linux-gnu/12.2.0/include/stdbool.h" 1 3 4
# 8 "src/main.c" 2
# 1 "/usr/include/assert.h" 1 3 4
# 64 "/usr/include/assert.h" 3 4



extern void __assert_fail (const char *__assertion, const char *__file,
      unsigned int __line, const char *__function)
     __attribute__ ((__nothrow__ , __leaf__)) __attribute__ ((__noreturn__));


extern void __assert_perror_fail (int __errnum, const char *__file,
      unsigned int __line, const char *__function)
     __attribute__ ((__nothrow__ , __leaf__)) __attribute__ ((__noreturn__));




extern void __assert (const char *__assertion, const char *__file, int __line)
     __attribute__ ((__nothrow__ , __leaf__)) __attribute__ ((__noreturn__));



# 9 "src/main.c" 2
# 1 "/usr/include/errno.h" 1 3 4
# 28 "/usr/include/errno.h" 3 4
# 1 "/usr/include/bits/errno.h" 1 3 4
# 26 "/usr/include/bits/errno.h" 3 4
# 1 "/usr/include/linux/errno.h" 1 3 4
# 1 "/usr/include/asm/errno.h" 1 3 4
# 1 "/usr/include/asm-generic/errno.h" 1 3 4




# 1 "/usr/include/asm-generic/errno-base.h" 1 3 4
# 6 "/usr/include/asm-generic/errno.h" 2 3 4
# 2 "/usr/include/asm/errno.h" 2 3 4
# 2 "/usr/include/linux/errno.h" 2 3 4
# 27 "/usr/include/bits/errno.h" 2 3 4
# 29 "/usr/include/errno.h" 2 3 4








extern int *__errno_location (void) __attribute__ ((__nothrow__ , __leaf__)) __attribute__ ((__const__));
# 52 "/usr/include/errno.h" 3 4

# 10 "src/main.c" 2

# 1 "/usr/include/unistd.h" 1 3 4
# 27 "/usr/include/unistd.h" 3 4

# 202 "/usr/include/unistd.h" 3 4
# 1 "/usr/include/bits/posix_opt.h" 1 3 4
# 203 "/usr/include/unistd.h" 2 3 4



# 1 "/usr/include/bits/environments.h" 1 3 4
# 22 "/usr/include/bits/environments.h" 3 4
# 1 "/usr/include/bits/wordsize.h" 1 3 4
# 23 "/usr/include/bits/environments.h" 2 3 4
# 207 "/usr/include/unistd.h" 2 3 4
# 226 "/usr/include/unistd.h" 3 4
# 1 "/usr/lib/gcc/x86_64-pc-linux-gnu/12.2.0/include/stddef.h" 1 3 4
# 227 "/usr/include/unistd.h" 2 3 4
# 255 "/usr/include/unistd.h" 3 4
typedef __useconds_t useconds_t;
# 274 "/usr/include/unistd.h" 3 4
typedef __socklen_t socklen_t;
# 287 "/usr/include/unistd.h" 3 4
extern int access (const char *__name, int __type) __attribute__ ((__nothrow__ , __leaf__)) __attribute__ ((__nonnull__ (1)));
# 309 "/usr/include/unistd.h" 3 4
extern int faccessat (int __fd, const char *__file, int __type, int __flag)
     __attribute__ ((__nothrow__ , __leaf__)) __attribute__ ((__nonnull__ (2))) ;
# 339 "/usr/include/unistd.h" 3 4
extern __off_t lseek (int __fd, __off_t __offset, int __whence) __attribute__ ((__nothrow__ , __leaf__));
# 358 "/usr/include/unistd.h" 3 4
extern int close (int __fd);




extern void closefrom (int __lowfd) __attribute__ ((__nothrow__ , __leaf__));







extern ssize_t read (int __fd, void *__buf, size_t __nbytes)
    __attribute__ ((__access__ (__write_only__, 2, 3)));





extern ssize_t write (int __fd, const void *__buf, size_t __n)
    __attribute__ ((__access__ (__read_only__, 2, 3)));
# 389 "/usr/include/unistd.h" 3 4
extern ssize_t pread (int __fd, void *__buf, size_t __nbytes,
        __off_t __offset)
    __attribute__ ((__access__ (__write_only__, 2, 3)));






extern ssize_t pwrite (int __fd, const void *__buf, size_t __n,
         __off_t __offset)
    __attribute__ ((__access__ (__read_only__, 2, 3)));
# 437 "/usr/include/unistd.h" 3 4
extern int pipe (int __pipedes[2]) __attribute__ ((__nothrow__ , __leaf__)) ;
# 452 "/usr/include/unistd.h" 3 4
extern unsigned int alarm (unsigned int __seconds) __attribute__ ((__nothrow__ , __leaf__));
# 464 "/usr/include/unistd.h" 3 4
extern unsigned int sleep (unsigned int __seconds);







extern __useconds_t ualarm (__useconds_t __value, __useconds_t __interval)
     __attribute__ ((__nothrow__ , __leaf__));






extern int usleep (__useconds_t __useconds);
# 489 "/usr/include/unistd.h" 3 4
extern int pause (void);



extern int chown (const char *__file, __uid_t __owner, __gid_t __group)
     __attribute__ ((__nothrow__ , __leaf__)) __attribute__ ((__nonnull__ (1))) ;



extern int fchown (int __fd, __uid_t __owner, __gid_t __group) __attribute__ ((__nothrow__ , __leaf__)) ;




extern int lchown (const char *__file, __uid_t __owner, __gid_t __group)
     __attribute__ ((__nothrow__ , __leaf__)) __attribute__ ((__nonnull__ (1))) ;






extern int fchownat (int __fd, const char *__file, __uid_t __owner,
       __gid_t __group, int __flag)
     __attribute__ ((__nothrow__ , __leaf__)) __attribute__ ((__nonnull__ (2))) ;



extern int chdir (const char *__path) __attribute__ ((__nothrow__ , __leaf__)) __attribute__ ((__nonnull__ (1))) ;



extern int fchdir (int __fd) __attribute__ ((__nothrow__ , __leaf__)) ;
# 531 "/usr/include/unistd.h" 3 4
extern char *getcwd (char *__buf, size_t __size) __attribute__ ((__nothrow__ , __leaf__)) ;
# 545 "/usr/include/unistd.h" 3 4
extern char *getwd (char *__buf)
     __attribute__ ((__nothrow__ , __leaf__)) __attribute__ ((__nonnull__ (1))) __attribute__ ((__deprecated__))
    __attribute__ ((__access__ (__write_only__, 1)));




extern int dup (int __fd) __attribute__ ((__nothrow__ , __leaf__)) ;


extern int dup2 (int __fd, int __fd2) __attribute__ ((__nothrow__ , __leaf__));
# 564 "/usr/include/unistd.h" 3 4
extern char **__environ;







extern int execve (const char *__path, char *const __argv[],
     char *const __envp[]) __attribute__ ((__nothrow__ , __leaf__)) __attribute__ ((__nonnull__ (1, 2)));




extern int fexecve (int __fd, char *const __argv[], char *const __envp[])
     __attribute__ ((__nothrow__ , __leaf__)) __attribute__ ((__nonnull__ (2)));




extern int execv (const char *__path, char *const __argv[])
     __attribute__ ((__nothrow__ , __leaf__)) __attribute__ ((__nonnull__ (1, 2)));



extern int execle (const char *__path, const char *__arg, ...)
     __attribute__ ((__nothrow__ , __leaf__)) __attribute__ ((__nonnull__ (1, 2)));



extern int execl (const char *__path, const char *__arg, ...)
     __attribute__ ((__nothrow__ , __leaf__)) __attribute__ ((__nonnull__ (1, 2)));



extern int execvp (const char *__file, char *const __argv[])
     __attribute__ ((__nothrow__ , __leaf__)) __attribute__ ((__nonnull__ (1, 2)));




extern int execlp (const char *__file, const char *__arg, ...)
     __attribute__ ((__nothrow__ , __leaf__)) __attribute__ ((__nonnull__ (1, 2)));
# 619 "/usr/include/unistd.h" 3 4
extern int nice (int __inc) __attribute__ ((__nothrow__ , __leaf__)) ;




extern void _exit (int __status) __attribute__ ((__noreturn__));





# 1 "/usr/include/bits/confname.h" 1 3 4
# 24 "/usr/include/bits/confname.h" 3 4
enum
  {
    _PC_LINK_MAX,

    _PC_MAX_CANON,

    _PC_MAX_INPUT,

    _PC_NAME_MAX,

    _PC_PATH_MAX,

    _PC_PIPE_BUF,

    _PC_CHOWN_RESTRICTED,

    _PC_NO_TRUNC,

    _PC_VDISABLE,

    _PC_SYNC_IO,

    _PC_ASYNC_IO,

    _PC_PRIO_IO,

    _PC_SOCK_MAXBUF,

    _PC_FILESIZEBITS,

    _PC_REC_INCR_XFER_SIZE,

    _PC_REC_MAX_XFER_SIZE,

    _PC_REC_MIN_XFER_SIZE,

    _PC_REC_XFER_ALIGN,

    _PC_ALLOC_SIZE_MIN,

    _PC_SYMLINK_MAX,

    _PC_2_SYMLINKS

  };


enum
  {
    _SC_ARG_MAX,

    _SC_CHILD_MAX,

    _SC_CLK_TCK,

    _SC_NGROUPS_MAX,

    _SC_OPEN_MAX,

    _SC_STREAM_MAX,

    _SC_TZNAME_MAX,

    _SC_JOB_CONTROL,

    _SC_SAVED_IDS,

    _SC_REALTIME_SIGNALS,

    _SC_PRIORITY_SCHEDULING,

    _SC_TIMERS,

    _SC_ASYNCHRONOUS_IO,

    _SC_PRIORITIZED_IO,

    _SC_SYNCHRONIZED_IO,

    _SC_FSYNC,

    _SC_MAPPED_FILES,

    _SC_MEMLOCK,

    _SC_MEMLOCK_RANGE,

    _SC_MEMORY_PROTECTION,

    _SC_MESSAGE_PASSING,

    _SC_SEMAPHORES,

    _SC_SHARED_MEMORY_OBJECTS,

    _SC_AIO_LISTIO_MAX,

    _SC_AIO_MAX,

    _SC_AIO_PRIO_DELTA_MAX,

    _SC_DELAYTIMER_MAX,

    _SC_MQ_OPEN_MAX,

    _SC_MQ_PRIO_MAX,

    _SC_VERSION,

    _SC_PAGESIZE,


    _SC_RTSIG_MAX,

    _SC_SEM_NSEMS_MAX,

    _SC_SEM_VALUE_MAX,

    _SC_SIGQUEUE_MAX,

    _SC_TIMER_MAX,




    _SC_BC_BASE_MAX,

    _SC_BC_DIM_MAX,

    _SC_BC_SCALE_MAX,

    _SC_BC_STRING_MAX,

    _SC_COLL_WEIGHTS_MAX,

    _SC_EQUIV_CLASS_MAX,

    _SC_EXPR_NEST_MAX,

    _SC_LINE_MAX,

    _SC_RE_DUP_MAX,

    _SC_CHARCLASS_NAME_MAX,


    _SC_2_VERSION,

    _SC_2_C_BIND,

    _SC_2_C_DEV,

    _SC_2_FORT_DEV,

    _SC_2_FORT_RUN,

    _SC_2_SW_DEV,

    _SC_2_LOCALEDEF,


    _SC_PII,

    _SC_PII_XTI,

    _SC_PII_SOCKET,

    _SC_PII_INTERNET,

    _SC_PII_OSI,

    _SC_POLL,

    _SC_SELECT,

    _SC_UIO_MAXIOV,

    _SC_IOV_MAX = _SC_UIO_MAXIOV,

    _SC_PII_INTERNET_STREAM,

    _SC_PII_INTERNET_DGRAM,

    _SC_PII_OSI_COTS,

    _SC_PII_OSI_CLTS,

    _SC_PII_OSI_M,

    _SC_T_IOV_MAX,



    _SC_THREADS,

    _SC_THREAD_SAFE_FUNCTIONS,

    _SC_GETGR_R_SIZE_MAX,

    _SC_GETPW_R_SIZE_MAX,

    _SC_LOGIN_NAME_MAX,

    _SC_TTY_NAME_MAX,

    _SC_THREAD_DESTRUCTOR_ITERATIONS,

    _SC_THREAD_KEYS_MAX,

    _SC_THREAD_STACK_MIN,

    _SC_THREAD_THREADS_MAX,

    _SC_THREAD_ATTR_STACKADDR,

    _SC_THREAD_ATTR_STACKSIZE,

    _SC_THREAD_PRIORITY_SCHEDULING,

    _SC_THREAD_PRIO_INHERIT,

    _SC_THREAD_PRIO_PROTECT,

    _SC_THREAD_PROCESS_SHARED,


    _SC_NPROCESSORS_CONF,

    _SC_NPROCESSORS_ONLN,

    _SC_PHYS_PAGES,

    _SC_AVPHYS_PAGES,

    _SC_ATEXIT_MAX,

    _SC_PASS_MAX,


    _SC_XOPEN_VERSION,

    _SC_XOPEN_XCU_VERSION,

    _SC_XOPEN_UNIX,

    _SC_XOPEN_CRYPT,

    _SC_XOPEN_ENH_I18N,

    _SC_XOPEN_SHM,


    _SC_2_CHAR_TERM,

    _SC_2_C_VERSION,

    _SC_2_UPE,


    _SC_XOPEN_XPG2,

    _SC_XOPEN_XPG3,

    _SC_XOPEN_XPG4,


    _SC_CHAR_BIT,

    _SC_CHAR_MAX,

    _SC_CHAR_MIN,

    _SC_INT_MAX,

    _SC_INT_MIN,

    _SC_LONG_BIT,

    _SC_WORD_BIT,

    _SC_MB_LEN_MAX,

    _SC_NZERO,

    _SC_SSIZE_MAX,

    _SC_SCHAR_MAX,

    _SC_SCHAR_MIN,

    _SC_SHRT_MAX,

    _SC_SHRT_MIN,

    _SC_UCHAR_MAX,

    _SC_UINT_MAX,

    _SC_ULONG_MAX,

    _SC_USHRT_MAX,


    _SC_NL_ARGMAX,

    _SC_NL_LANGMAX,

    _SC_NL_MSGMAX,

    _SC_NL_NMAX,

    _SC_NL_SETMAX,

    _SC_NL_TEXTMAX,


    _SC_XBS5_ILP32_OFF32,

    _SC_XBS5_ILP32_OFFBIG,

    _SC_XBS5_LP64_OFF64,

    _SC_XBS5_LPBIG_OFFBIG,


    _SC_XOPEN_LEGACY,

    _SC_XOPEN_REALTIME,

    _SC_XOPEN_REALTIME_THREADS,


    _SC_ADVISORY_INFO,

    _SC_BARRIERS,

    _SC_BASE,

    _SC_C_LANG_SUPPORT,

    _SC_C_LANG_SUPPORT_R,

    _SC_CLOCK_SELECTION,

    _SC_CPUTIME,

    _SC_THREAD_CPUTIME,

    _SC_DEVICE_IO,

    _SC_DEVICE_SPECIFIC,

    _SC_DEVICE_SPECIFIC_R,

    _SC_FD_MGMT,

    _SC_FIFO,

    _SC_PIPE,

    _SC_FILE_ATTRIBUTES,

    _SC_FILE_LOCKING,

    _SC_FILE_SYSTEM,

    _SC_MONOTONIC_CLOCK,

    _SC_MULTI_PROCESS,

    _SC_SINGLE_PROCESS,

    _SC_NETWORKING,

    _SC_READER_WRITER_LOCKS,

    _SC_SPIN_LOCKS,

    _SC_REGEXP,

    _SC_REGEX_VERSION,

    _SC_SHELL,

    _SC_SIGNALS,

    _SC_SPAWN,

    _SC_SPORADIC_SERVER,

    _SC_THREAD_SPORADIC_SERVER,

    _SC_SYSTEM_DATABASE,

    _SC_SYSTEM_DATABASE_R,

    _SC_TIMEOUTS,

    _SC_TYPED_MEMORY_OBJECTS,

    _SC_USER_GROUPS,

    _SC_USER_GROUPS_R,

    _SC_2_PBS,

    _SC_2_PBS_ACCOUNTING,

    _SC_2_PBS_LOCATE,

    _SC_2_PBS_MESSAGE,

    _SC_2_PBS_TRACK,

    _SC_SYMLOOP_MAX,

    _SC_STREAMS,

    _SC_2_PBS_CHECKPOINT,


    _SC_V6_ILP32_OFF32,

    _SC_V6_ILP32_OFFBIG,

    _SC_V6_LP64_OFF64,

    _SC_V6_LPBIG_OFFBIG,


    _SC_HOST_NAME_MAX,

    _SC_TRACE,

    _SC_TRACE_EVENT_FILTER,

    _SC_TRACE_INHERIT,

    _SC_TRACE_LOG,


    _SC_LEVEL1_ICACHE_SIZE,

    _SC_LEVEL1_ICACHE_ASSOC,

    _SC_LEVEL1_ICACHE_LINESIZE,

    _SC_LEVEL1_DCACHE_SIZE,

    _SC_LEVEL1_DCACHE_ASSOC,

    _SC_LEVEL1_DCACHE_LINESIZE,

    _SC_LEVEL2_CACHE_SIZE,

    _SC_LEVEL2_CACHE_ASSOC,

    _SC_LEVEL2_CACHE_LINESIZE,

    _SC_LEVEL3_CACHE_SIZE,

    _SC_LEVEL3_CACHE_ASSOC,

    _SC_LEVEL3_CACHE_LINESIZE,

    _SC_LEVEL4_CACHE_SIZE,

    _SC_LEVEL4_CACHE_ASSOC,

    _SC_LEVEL4_CACHE_LINESIZE,



    _SC_IPV6 = _SC_LEVEL1_ICACHE_SIZE + 50,

    _SC_RAW_SOCKETS,


    _SC_V7_ILP32_OFF32,

    _SC_V7_ILP32_OFFBIG,

    _SC_V7_LP64_OFF64,

    _SC_V7_LPBIG_OFFBIG,


    _SC_SS_REPL_MAX,


    _SC_TRACE_EVENT_NAME_MAX,

    _SC_TRACE_NAME_MAX,

    _SC_TRACE_SYS_MAX,

    _SC_TRACE_USER_EVENT_MAX,


    _SC_XOPEN_STREAMS,


    _SC_THREAD_ROBUST_PRIO_INHERIT,

    _SC_THREAD_ROBUST_PRIO_PROTECT,


    _SC_MINSIGSTKSZ,


    _SC_SIGSTKSZ

  };


enum
  {
    _CS_PATH,


    _CS_V6_WIDTH_RESTRICTED_ENVS,



    _CS_GNU_LIBC_VERSION,

    _CS_GNU_LIBPTHREAD_VERSION,


    _CS_V5_WIDTH_RESTRICTED_ENVS,



    _CS_V7_WIDTH_RESTRICTED_ENVS,



    _CS_LFS_CFLAGS = 1000,

    _CS_LFS_LDFLAGS,

    _CS_LFS_LIBS,

    _CS_LFS_LINTFLAGS,

    _CS_LFS64_CFLAGS,

    _CS_LFS64_LDFLAGS,

    _CS_LFS64_LIBS,

    _CS_LFS64_LINTFLAGS,


    _CS_XBS5_ILP32_OFF32_CFLAGS = 1100,

    _CS_XBS5_ILP32_OFF32_LDFLAGS,

    _CS_XBS5_ILP32_OFF32_LIBS,

    _CS_XBS5_ILP32_OFF32_LINTFLAGS,

    _CS_XBS5_ILP32_OFFBIG_CFLAGS,

    _CS_XBS5_ILP32_OFFBIG_LDFLAGS,

    _CS_XBS5_ILP32_OFFBIG_LIBS,

    _CS_XBS5_ILP32_OFFBIG_LINTFLAGS,

    _CS_XBS5_LP64_OFF64_CFLAGS,

    _CS_XBS5_LP64_OFF64_LDFLAGS,

    _CS_XBS5_LP64_OFF64_LIBS,

    _CS_XBS5_LP64_OFF64_LINTFLAGS,

    _CS_XBS5_LPBIG_OFFBIG_CFLAGS,

    _CS_XBS5_LPBIG_OFFBIG_LDFLAGS,

    _CS_XBS5_LPBIG_OFFBIG_LIBS,

    _CS_XBS5_LPBIG_OFFBIG_LINTFLAGS,


    _CS_POSIX_V6_ILP32_OFF32_CFLAGS,

    _CS_POSIX_V6_ILP32_OFF32_LDFLAGS,

    _CS_POSIX_V6_ILP32_OFF32_LIBS,

    _CS_POSIX_V6_ILP32_OFF32_LINTFLAGS,

    _CS_POSIX_V6_ILP32_OFFBIG_CFLAGS,

    _CS_POSIX_V6_ILP32_OFFBIG_LDFLAGS,

    _CS_POSIX_V6_ILP32_OFFBIG_LIBS,

    _CS_POSIX_V6_ILP32_OFFBIG_LINTFLAGS,

    _CS_POSIX_V6_LP64_OFF64_CFLAGS,

    _CS_POSIX_V6_LP64_OFF64_LDFLAGS,

    _CS_POSIX_V6_LP64_OFF64_LIBS,

    _CS_POSIX_V6_LP64_OFF64_LINTFLAGS,

    _CS_POSIX_V6_LPBIG_OFFBIG_CFLAGS,

    _CS_POSIX_V6_LPBIG_OFFBIG_LDFLAGS,

    _CS_POSIX_V6_LPBIG_OFFBIG_LIBS,

    _CS_POSIX_V6_LPBIG_OFFBIG_LINTFLAGS,


    _CS_POSIX_V7_ILP32_OFF32_CFLAGS,

    _CS_POSIX_V7_ILP32_OFF32_LDFLAGS,

    _CS_POSIX_V7_ILP32_OFF32_LIBS,

    _CS_POSIX_V7_ILP32_OFF32_LINTFLAGS,

    _CS_POSIX_V7_ILP32_OFFBIG_CFLAGS,

    _CS_POSIX_V7_ILP32_OFFBIG_LDFLAGS,

    _CS_POSIX_V7_ILP32_OFFBIG_LIBS,

    _CS_POSIX_V7_ILP32_OFFBIG_LINTFLAGS,

    _CS_POSIX_V7_LP64_OFF64_CFLAGS,

    _CS_POSIX_V7_LP64_OFF64_LDFLAGS,

    _CS_POSIX_V7_LP64_OFF64_LIBS,

    _CS_POSIX_V7_LP64_OFF64_LINTFLAGS,

    _CS_POSIX_V7_LPBIG_OFFBIG_CFLAGS,

    _CS_POSIX_V7_LPBIG_OFFBIG_LDFLAGS,

    _CS_POSIX_V7_LPBIG_OFFBIG_LIBS,

    _CS_POSIX_V7_LPBIG_OFFBIG_LINTFLAGS,


    _CS_V6_ENV,

    _CS_V7_ENV

  };
# 631 "/usr/include/unistd.h" 2 3 4


extern long int pathconf (const char *__path, int __name)
     __attribute__ ((__nothrow__ , __leaf__)) __attribute__ ((__nonnull__ (1)));


extern long int fpathconf (int __fd, int __name) __attribute__ ((__nothrow__ , __leaf__));


extern long int sysconf (int __name) __attribute__ ((__nothrow__ , __leaf__));



extern size_t confstr (int __name, char *__buf, size_t __len) __attribute__ ((__nothrow__ , __leaf__))
    __attribute__ ((__access__ (__write_only__, 2, 3)));




extern __pid_t getpid (void) __attribute__ ((__nothrow__ , __leaf__));


extern __pid_t getppid (void) __attribute__ ((__nothrow__ , __leaf__));


extern __pid_t getpgrp (void) __attribute__ ((__nothrow__ , __leaf__));


extern __pid_t __getpgid (__pid_t __pid) __attribute__ ((__nothrow__ , __leaf__));

extern __pid_t getpgid (__pid_t __pid) __attribute__ ((__nothrow__ , __leaf__));






extern int setpgid (__pid_t __pid, __pid_t __pgid) __attribute__ ((__nothrow__ , __leaf__));
# 682 "/usr/include/unistd.h" 3 4
extern int setpgrp (void) __attribute__ ((__nothrow__ , __leaf__));






extern __pid_t setsid (void) __attribute__ ((__nothrow__ , __leaf__));



extern __pid_t getsid (__pid_t __pid) __attribute__ ((__nothrow__ , __leaf__));



extern __uid_t getuid (void) __attribute__ ((__nothrow__ , __leaf__));


extern __uid_t geteuid (void) __attribute__ ((__nothrow__ , __leaf__));


extern __gid_t getgid (void) __attribute__ ((__nothrow__ , __leaf__));


extern __gid_t getegid (void) __attribute__ ((__nothrow__ , __leaf__));




extern int getgroups (int __size, __gid_t __list[]) __attribute__ ((__nothrow__ , __leaf__))
    __attribute__ ((__access__ (__write_only__, 2, 1)));
# 722 "/usr/include/unistd.h" 3 4
extern int setuid (__uid_t __uid) __attribute__ ((__nothrow__ , __leaf__)) ;




extern int setreuid (__uid_t __ruid, __uid_t __euid) __attribute__ ((__nothrow__ , __leaf__)) ;




extern int seteuid (__uid_t __uid) __attribute__ ((__nothrow__ , __leaf__)) ;






extern int setgid (__gid_t __gid) __attribute__ ((__nothrow__ , __leaf__)) ;




extern int setregid (__gid_t __rgid, __gid_t __egid) __attribute__ ((__nothrow__ , __leaf__)) ;




extern int setegid (__gid_t __gid) __attribute__ ((__nothrow__ , __leaf__)) ;
# 778 "/usr/include/unistd.h" 3 4
extern __pid_t fork (void) __attribute__ ((__nothrow__));







extern __pid_t vfork (void) __attribute__ ((__nothrow__ , __leaf__));
# 799 "/usr/include/unistd.h" 3 4
extern char *ttyname (int __fd) __attribute__ ((__nothrow__ , __leaf__));



extern int ttyname_r (int __fd, char *__buf, size_t __buflen)
     __attribute__ ((__nothrow__ , __leaf__)) __attribute__ ((__nonnull__ (2)))
     __attribute__ ((__access__ (__write_only__, 2, 3)));



extern int isatty (int __fd) __attribute__ ((__nothrow__ , __leaf__));




extern int ttyslot (void) __attribute__ ((__nothrow__ , __leaf__));




extern int link (const char *__from, const char *__to)
     __attribute__ ((__nothrow__ , __leaf__)) __attribute__ ((__nonnull__ (1, 2))) ;




extern int linkat (int __fromfd, const char *__from, int __tofd,
     const char *__to, int __flags)
     __attribute__ ((__nothrow__ , __leaf__)) __attribute__ ((__nonnull__ (2, 4))) ;




extern int symlink (const char *__from, const char *__to)
     __attribute__ ((__nothrow__ , __leaf__)) __attribute__ ((__nonnull__ (1, 2))) ;




extern ssize_t readlink (const char *__restrict __path,
    char *__restrict __buf, size_t __len)
     __attribute__ ((__nothrow__ , __leaf__)) __attribute__ ((__nonnull__ (1, 2)))
     __attribute__ ((__access__ (__write_only__, 2, 3)));





extern int symlinkat (const char *__from, int __tofd,
        const char *__to) __attribute__ ((__nothrow__ , __leaf__)) __attribute__ ((__nonnull__ (1, 3))) ;


extern ssize_t readlinkat (int __fd, const char *__restrict __path,
      char *__restrict __buf, size_t __len)
     __attribute__ ((__nothrow__ , __leaf__)) __attribute__ ((__nonnull__ (2, 3)))
     __attribute__ ((__access__ (__write_only__, 3, 4)));



extern int unlink (const char *__name) __attribute__ ((__nothrow__ , __leaf__)) __attribute__ ((__nonnull__ (1)));



extern int unlinkat (int __fd, const char *__name, int __flag)
     __attribute__ ((__nothrow__ , __leaf__)) __attribute__ ((__nonnull__ (2)));



extern int rmdir (const char *__path) __attribute__ ((__nothrow__ , __leaf__)) __attribute__ ((__nonnull__ (1)));



extern __pid_t tcgetpgrp (int __fd) __attribute__ ((__nothrow__ , __leaf__));


extern int tcsetpgrp (int __fd, __pid_t __pgrp_id) __attribute__ ((__nothrow__ , __leaf__));






extern char *getlogin (void);







extern int getlogin_r (char *__name, size_t __name_len) __attribute__ ((__nonnull__ (1)))
    __attribute__ ((__access__ (__write_only__, 1, 2)));




extern int setlogin (const char *__name) __attribute__ ((__nothrow__ , __leaf__)) __attribute__ ((__nonnull__ (1)));







# 1 "/usr/include/bits/getopt_posix.h" 1 3 4
# 27 "/usr/include/bits/getopt_posix.h" 3 4
# 1 "/usr/include/bits/getopt_core.h" 1 3 4
# 28 "/usr/include/bits/getopt_core.h" 3 4








extern char *optarg;
# 50 "/usr/include/bits/getopt_core.h" 3 4
extern int optind;




extern int opterr;



extern int optopt;
# 91 "/usr/include/bits/getopt_core.h" 3 4
extern int getopt (int ___argc, char *const *___argv, const char *__shortopts)
       __attribute__ ((__nothrow__ , __leaf__)) __attribute__ ((__nonnull__ (2, 3)));


# 28 "/usr/include/bits/getopt_posix.h" 2 3 4


# 49 "/usr/include/bits/getopt_posix.h" 3 4

# 904 "/usr/include/unistd.h" 2 3 4







extern int gethostname (char *__name, size_t __len) __attribute__ ((__nothrow__ , __leaf__)) __attribute__ ((__nonnull__ (1)))
    __attribute__ ((__access__ (__write_only__, 1, 2)));






extern int sethostname (const char *__name, size_t __len)
     __attribute__ ((__nothrow__ , __leaf__)) __attribute__ ((__nonnull__ (1))) __attribute__ ((__access__ (__read_only__, 1, 2)));



extern int sethostid (long int __id) __attribute__ ((__nothrow__ , __leaf__)) ;





extern int getdomainname (char *__name, size_t __len)
     __attribute__ ((__nothrow__ , __leaf__)) __attribute__ ((__nonnull__ (1)))
     __attribute__ ((__access__ (__write_only__, 1, 2)));
extern int setdomainname (const char *__name, size_t __len)
     __attribute__ ((__nothrow__ , __leaf__)) __attribute__ ((__nonnull__ (1))) __attribute__ ((__access__ (__read_only__, 1, 2)));




extern int vhangup (void) __attribute__ ((__nothrow__ , __leaf__));


extern int revoke (const char *__file) __attribute__ ((__nothrow__ , __leaf__)) __attribute__ ((__nonnull__ (1))) ;







extern int profil (unsigned short int *__sample_buffer, size_t __size,
     size_t __offset, unsigned int __scale)
     __attribute__ ((__nothrow__ , __leaf__)) __attribute__ ((__nonnull__ (1)));





extern int acct (const char *__name) __attribute__ ((__nothrow__ , __leaf__));



extern char *getusershell (void) __attribute__ ((__nothrow__ , __leaf__));
extern void endusershell (void) __attribute__ ((__nothrow__ , __leaf__));
extern void setusershell (void) __attribute__ ((__nothrow__ , __leaf__));





extern int daemon (int __nochdir, int __noclose) __attribute__ ((__nothrow__ , __leaf__)) ;






extern int chroot (const char *__path) __attribute__ ((__nothrow__ , __leaf__)) __attribute__ ((__nonnull__ (1))) ;



extern char *getpass (const char *__prompt) __attribute__ ((__nonnull__ (1)));







extern int fsync (int __fd);
# 1002 "/usr/include/unistd.h" 3 4
extern long int gethostid (void);


extern void sync (void) __attribute__ ((__nothrow__ , __leaf__));





extern int getpagesize (void) __attribute__ ((__nothrow__ , __leaf__)) __attribute__ ((__const__));




extern int getdtablesize (void) __attribute__ ((__nothrow__ , __leaf__));
# 1026 "/usr/include/unistd.h" 3 4
extern int truncate (const char *__file, __off_t __length)
     __attribute__ ((__nothrow__ , __leaf__)) __attribute__ ((__nonnull__ (1))) ;
# 1049 "/usr/include/unistd.h" 3 4
extern int ftruncate (int __fd, __off_t __length) __attribute__ ((__nothrow__ , __leaf__)) ;
# 1070 "/usr/include/unistd.h" 3 4
extern int brk (void *__addr) __attribute__ ((__nothrow__ , __leaf__)) ;





extern void *sbrk (intptr_t __delta) __attribute__ ((__nothrow__ , __leaf__));
# 1091 "/usr/include/unistd.h" 3 4
extern long int syscall (long int __sysno, ...) __attribute__ ((__nothrow__ , __leaf__));
# 1114 "/usr/include/unistd.h" 3 4
extern int lockf (int __fd, int __cmd, __off_t __len) ;
# 1150 "/usr/include/unistd.h" 3 4
extern int fdatasync (int __fildes);
# 1159 "/usr/include/unistd.h" 3 4
extern char *crypt (const char *__key, const char *__salt)
     __attribute__ ((__nothrow__ , __leaf__)) __attribute__ ((__nonnull__ (1, 2)));
# 1198 "/usr/include/unistd.h" 3 4
int getentropy (void *__buffer, size_t __length)
    __attribute__ ((__access__ (__write_only__, 1, 2)));
# 1218 "/usr/include/unistd.h" 3 4
# 1 "/usr/include/bits/unistd_ext.h" 1 3 4
# 1219 "/usr/include/unistd.h" 2 3 4


# 12 "src/main.c" 2

# 1 "/usr/include/sys/wait.h" 1 3 4
# 27 "/usr/include/sys/wait.h" 3 4

# 36 "/usr/include/sys/wait.h" 3 4
# 1 "/usr/include/signal.h" 1 3 4
# 27 "/usr/include/signal.h" 3 4



# 1 "/usr/include/bits/signum-generic.h" 1 3 4
# 76 "/usr/include/bits/signum-generic.h" 3 4
# 1 "/usr/include/bits/signum-arch.h" 1 3 4
# 77 "/usr/include/bits/signum-generic.h" 2 3 4
# 31 "/usr/include/signal.h" 2 3 4

# 1 "/usr/include/bits/types/sig_atomic_t.h" 1 3 4







typedef __sig_atomic_t sig_atomic_t;
# 33 "/usr/include/signal.h" 2 3 4
# 57 "/usr/include/signal.h" 3 4
# 1 "/usr/include/bits/types/siginfo_t.h" 1 3 4



# 1 "/usr/include/bits/wordsize.h" 1 3 4
# 5 "/usr/include/bits/types/siginfo_t.h" 2 3 4

# 1 "/usr/include/bits/types/__sigval_t.h" 1 3 4
# 24 "/usr/include/bits/types/__sigval_t.h" 3 4
union sigval
{
  int sival_int;
  void *sival_ptr;
};

typedef union sigval __sigval_t;
# 7 "/usr/include/bits/types/siginfo_t.h" 2 3 4
# 16 "/usr/include/bits/types/siginfo_t.h" 3 4
# 1 "/usr/include/bits/siginfo-arch.h" 1 3 4
# 17 "/usr/include/bits/types/siginfo_t.h" 2 3 4
# 36 "/usr/include/bits/types/siginfo_t.h" 3 4
typedef struct
  {
    int si_signo;

    int si_errno;

    int si_code;





    int __pad0;


    union
      {
 int _pad[((128 / sizeof (int)) - 4)];


 struct
   {
     __pid_t si_pid;
     __uid_t si_uid;
   } _kill;


 struct
   {
     int si_tid;
     int si_overrun;
     __sigval_t si_sigval;
   } _timer;


 struct
   {
     __pid_t si_pid;
     __uid_t si_uid;
     __sigval_t si_sigval;
   } _rt;


 struct
   {
     __pid_t si_pid;
     __uid_t si_uid;
     int si_status;
     __clock_t si_utime;
     __clock_t si_stime;
   } _sigchld;


 struct
   {
     void *si_addr;
    
     short int si_addr_lsb;
     union
       {

  struct
    {
      void *_lower;
      void *_upper;
    } _addr_bnd;

  __uint32_t _pkey;
       } _bounds;
   } _sigfault;


 struct
   {
     long int si_band;
     int si_fd;
   } _sigpoll;



 struct
   {
     void *_call_addr;
     int _syscall;
     unsigned int _arch;
   } _sigsys;

      } _sifields;
  } siginfo_t ;
# 58 "/usr/include/signal.h" 2 3 4
# 1 "/usr/include/bits/siginfo-consts.h" 1 3 4
# 35 "/usr/include/bits/siginfo-consts.h" 3 4
enum
{
  SI_ASYNCNL = -60,
  SI_DETHREAD = -7,

  SI_TKILL,
  SI_SIGIO,

  SI_ASYNCIO,
  SI_MESGQ,
  SI_TIMER,





  SI_QUEUE,
  SI_USER,
  SI_KERNEL = 0x80
# 66 "/usr/include/bits/siginfo-consts.h" 3 4
};




enum
{
  ILL_ILLOPC = 1,

  ILL_ILLOPN,

  ILL_ILLADR,

  ILL_ILLTRP,

  ILL_PRVOPC,

  ILL_PRVREG,

  ILL_COPROC,

  ILL_BADSTK,

  ILL_BADIADDR

};


enum
{
  FPE_INTDIV = 1,

  FPE_INTOVF,

  FPE_FLTDIV,

  FPE_FLTOVF,

  FPE_FLTUND,

  FPE_FLTRES,

  FPE_FLTINV,

  FPE_FLTSUB,

  FPE_FLTUNK = 14,

  FPE_CONDTRAP

};


enum
{
  SEGV_MAPERR = 1,

  SEGV_ACCERR,

  SEGV_BNDERR,

  SEGV_PKUERR,

  SEGV_ACCADI,

  SEGV_ADIDERR,

  SEGV_ADIPERR,

  SEGV_MTEAERR,

  SEGV_MTESERR

};


enum
{
  BUS_ADRALN = 1,

  BUS_ADRERR,

  BUS_OBJERR,

  BUS_MCEERR_AR,

  BUS_MCEERR_AO

};
# 176 "/usr/include/bits/siginfo-consts.h" 3 4
enum
{
  CLD_EXITED = 1,

  CLD_KILLED,

  CLD_DUMPED,

  CLD_TRAPPED,

  CLD_STOPPED,

  CLD_CONTINUED

};


enum
{
  POLL_IN = 1,

  POLL_OUT,

  POLL_MSG,

  POLL_ERR,

  POLL_PRI,

  POLL_HUP

};
# 59 "/usr/include/signal.h" 2 3 4



# 1 "/usr/include/bits/types/sigval_t.h" 1 3 4
# 16 "/usr/include/bits/types/sigval_t.h" 3 4
typedef __sigval_t sigval_t;
# 63 "/usr/include/signal.h" 2 3 4



# 1 "/usr/include/bits/types/sigevent_t.h" 1 3 4



# 1 "/usr/include/bits/wordsize.h" 1 3 4
# 5 "/usr/include/bits/types/sigevent_t.h" 2 3 4
# 22 "/usr/include/bits/types/sigevent_t.h" 3 4
typedef struct sigevent
  {
    __sigval_t sigev_value;
    int sigev_signo;
    int sigev_notify;

    union
      {
 int _pad[((64 / sizeof (int)) - 4)];



 __pid_t _tid;

 struct
   {
     void (*_function) (__sigval_t);
     pthread_attr_t *_attribute;
   } _sigev_thread;
      } _sigev_un;
  } sigevent_t;
# 67 "/usr/include/signal.h" 2 3 4
# 1 "/usr/include/bits/sigevent-consts.h" 1 3 4
# 27 "/usr/include/bits/sigevent-consts.h" 3 4
enum
{
  SIGEV_SIGNAL = 0,

  SIGEV_NONE,

  SIGEV_THREAD,


  SIGEV_THREAD_ID = 4


};
# 68 "/usr/include/signal.h" 2 3 4




typedef void (*__sighandler_t) (int);




extern __sighandler_t __sysv_signal (int __sig, __sighandler_t __handler)
     __attribute__ ((__nothrow__ , __leaf__));
# 88 "/usr/include/signal.h" 3 4
extern __sighandler_t signal (int __sig, __sighandler_t __handler)
     __attribute__ ((__nothrow__ , __leaf__));
# 112 "/usr/include/signal.h" 3 4
extern int kill (__pid_t __pid, int __sig) __attribute__ ((__nothrow__ , __leaf__));






extern int killpg (__pid_t __pgrp, int __sig) __attribute__ ((__nothrow__ , __leaf__));



extern int raise (int __sig) __attribute__ ((__nothrow__ , __leaf__));



extern __sighandler_t ssignal (int __sig, __sighandler_t __handler)
     __attribute__ ((__nothrow__ , __leaf__));
extern int gsignal (int __sig) __attribute__ ((__nothrow__ , __leaf__));




extern void psignal (int __sig, const char *__s);


extern void psiginfo (const siginfo_t *__pinfo, const char *__s);
# 173 "/usr/include/signal.h" 3 4
extern int sigblock (int __mask) __attribute__ ((__nothrow__ , __leaf__)) __attribute__ ((__deprecated__));


extern int sigsetmask (int __mask) __attribute__ ((__nothrow__ , __leaf__)) __attribute__ ((__deprecated__));


extern int siggetmask (void) __attribute__ ((__nothrow__ , __leaf__)) __attribute__ ((__deprecated__));
# 193 "/usr/include/signal.h" 3 4
typedef __sighandler_t sig_t;





extern int sigemptyset (sigset_t *__set) __attribute__ ((__nothrow__ , __leaf__)) __attribute__ ((__nonnull__ (1)));


extern int sigfillset (sigset_t *__set) __attribute__ ((__nothrow__ , __leaf__)) __attribute__ ((__nonnull__ (1)));


extern int sigaddset (sigset_t *__set, int __signo) __attribute__ ((__nothrow__ , __leaf__)) __attribute__ ((__nonnull__ (1)));


extern int sigdelset (sigset_t *__set, int __signo) __attribute__ ((__nothrow__ , __leaf__)) __attribute__ ((__nonnull__ (1)));


extern int sigismember (const sigset_t *__set, int __signo)
     __attribute__ ((__nothrow__ , __leaf__)) __attribute__ ((__nonnull__ (1)));
# 229 "/usr/include/signal.h" 3 4
# 1 "/usr/include/bits/sigaction.h" 1 3 4
# 27 "/usr/include/bits/sigaction.h" 3 4
struct sigaction
  {


    union
      {

 __sighandler_t sa_handler;

 void (*sa_sigaction) (int, siginfo_t *, void *);
      }
    __sigaction_handler;







    __sigset_t sa_mask;


    int sa_flags;


    void (*sa_restorer) (void);
  };
# 230 "/usr/include/signal.h" 2 3 4


extern int sigprocmask (int __how, const sigset_t *__restrict __set,
   sigset_t *__restrict __oset) __attribute__ ((__nothrow__ , __leaf__));






extern int sigsuspend (const sigset_t *__set) __attribute__ ((__nonnull__ (1)));


extern int sigaction (int __sig, const struct sigaction *__restrict __act,
        struct sigaction *__restrict __oact) __attribute__ ((__nothrow__ , __leaf__));


extern int sigpending (sigset_t *__set) __attribute__ ((__nothrow__ , __leaf__)) __attribute__ ((__nonnull__ (1)));







extern int sigwait (const sigset_t *__restrict __set, int *__restrict __sig)
     __attribute__ ((__nonnull__ (1, 2)));







extern int sigwaitinfo (const sigset_t *__restrict __set,
   siginfo_t *__restrict __info) __attribute__ ((__nonnull__ (1)));







extern int sigtimedwait (const sigset_t *__restrict __set,
    siginfo_t *__restrict __info,
    const struct timespec *__restrict __timeout)
     __attribute__ ((__nonnull__ (1)));
# 292 "/usr/include/signal.h" 3 4
extern int sigqueue (__pid_t __pid, int __sig, const union sigval __val)
     __attribute__ ((__nothrow__ , __leaf__));







# 1 "/usr/include/bits/sigcontext.h" 1 3 4
# 31 "/usr/include/bits/sigcontext.h" 3 4
struct _fpx_sw_bytes
{
  __uint32_t magic1;
  __uint32_t extended_size;
  __uint64_t xstate_bv;
  __uint32_t xstate_size;
  __uint32_t __glibc_reserved1[7];
};

struct _fpreg
{
  unsigned short significand[4];
  unsigned short exponent;
};

struct _fpxreg
{
  unsigned short significand[4];
  unsigned short exponent;
  unsigned short __glibc_reserved1[3];
};

struct _xmmreg
{
  __uint32_t element[4];
};
# 123 "/usr/include/bits/sigcontext.h" 3 4
struct _fpstate
{

  __uint16_t cwd;
  __uint16_t swd;
  __uint16_t ftw;
  __uint16_t fop;
  __uint64_t rip;
  __uint64_t rdp;
  __uint32_t mxcsr;
  __uint32_t mxcr_mask;
  struct _fpxreg _st[8];
  struct _xmmreg _xmm[16];
  __uint32_t __glibc_reserved1[24];
};

struct sigcontext
{
  __uint64_t r8;
  __uint64_t r9;
  __uint64_t r10;
  __uint64_t r11;
  __uint64_t r12;
  __uint64_t r13;
  __uint64_t r14;
  __uint64_t r15;
  __uint64_t rdi;
  __uint64_t rsi;
  __uint64_t rbp;
  __uint64_t rbx;
  __uint64_t rdx;
  __uint64_t rax;
  __uint64_t rcx;
  __uint64_t rsp;
  __uint64_t rip;
  __uint64_t eflags;
  unsigned short cs;
  unsigned short gs;
  unsigned short fs;
  unsigned short __pad0;
  __uint64_t err;
  __uint64_t trapno;
  __uint64_t oldmask;
  __uint64_t cr2;
  __extension__ union
    {
      struct _fpstate * fpstate;
      __uint64_t __fpstate_word;
    };
  __uint64_t __reserved1 [8];
};



struct _xsave_hdr
{
  __uint64_t xstate_bv;
  __uint64_t __glibc_reserved1[2];
  __uint64_t __glibc_reserved2[5];
};

struct _ymmh_state
{
  __uint32_t ymmh_space[64];
};

struct _xstate
{
  struct _fpstate fpstate;
  struct _xsave_hdr xstate_hdr;
  struct _ymmh_state ymmh;
};
# 302 "/usr/include/signal.h" 2 3 4


extern int sigreturn (struct sigcontext *__scp) __attribute__ ((__nothrow__ , __leaf__));






# 1 "/usr/lib/gcc/x86_64-pc-linux-gnu/12.2.0/include/stddef.h" 1 3 4
# 312 "/usr/include/signal.h" 2 3 4

# 1 "/usr/include/bits/types/stack_t.h" 1 3 4
# 23 "/usr/include/bits/types/stack_t.h" 3 4
# 1 "/usr/lib/gcc/x86_64-pc-linux-gnu/12.2.0/include/stddef.h" 1 3 4
# 24 "/usr/include/bits/types/stack_t.h" 2 3 4


typedef struct
  {
    void *ss_sp;
    int ss_flags;
    size_t ss_size;
  } stack_t;
# 314 "/usr/include/signal.h" 2 3 4


# 1 "/usr/include/sys/ucontext.h" 1 3 4
# 37 "/usr/include/sys/ucontext.h" 3 4
__extension__ typedef long long int greg_t;
# 46 "/usr/include/sys/ucontext.h" 3 4
typedef greg_t gregset_t[23];
# 101 "/usr/include/sys/ucontext.h" 3 4
struct _libc_fpxreg
{
  unsigned short int significand[4];
  unsigned short int exponent;
  unsigned short int __glibc_reserved1[3];
};

struct _libc_xmmreg
{
  __uint32_t element[4];
};

struct _libc_fpstate
{

  __uint16_t cwd;
  __uint16_t swd;
  __uint16_t ftw;
  __uint16_t fop;
  __uint64_t rip;
  __uint64_t rdp;
  __uint32_t mxcsr;
  __uint32_t mxcr_mask;
  struct _libc_fpxreg _st[8];
  struct _libc_xmmreg _xmm[16];
  __uint32_t __glibc_reserved1[24];
};


typedef struct _libc_fpstate *fpregset_t;


typedef struct
  {
    gregset_t gregs;

    fpregset_t fpregs;
    __extension__ unsigned long long __reserved1 [8];
} mcontext_t;


typedef struct ucontext_t
  {
    unsigned long int uc_flags;
    struct ucontext_t *uc_link;
    stack_t uc_stack;
    mcontext_t uc_mcontext;
    sigset_t uc_sigmask;
    struct _libc_fpstate __fpregs_mem;
    __extension__ unsigned long long int __ssp[4];
  } ucontext_t;
# 317 "/usr/include/signal.h" 2 3 4







extern int siginterrupt (int __sig, int __interrupt) __attribute__ ((__nothrow__ , __leaf__))
  __attribute__ ((__deprecated__ ("Use sigaction with SA_RESTART instead")));

# 1 "/usr/include/bits/sigstack.h" 1 3 4
# 328 "/usr/include/signal.h" 2 3 4
# 1 "/usr/include/bits/sigstksz.h" 1 3 4
# 329 "/usr/include/signal.h" 2 3 4
# 1 "/usr/include/bits/ss_flags.h" 1 3 4
# 27 "/usr/include/bits/ss_flags.h" 3 4
enum
{
  SS_ONSTACK = 1,

  SS_DISABLE

};
# 330 "/usr/include/signal.h" 2 3 4



extern int sigaltstack (const stack_t *__restrict __ss,
   stack_t *__restrict __oss) __attribute__ ((__nothrow__ , __leaf__));




# 1 "/usr/include/bits/types/struct_sigstack.h" 1 3 4
# 23 "/usr/include/bits/types/struct_sigstack.h" 3 4
struct sigstack
  {
    void *ss_sp;
    int ss_onstack;
  };
# 340 "/usr/include/signal.h" 2 3 4







extern int sigstack (struct sigstack *__ss, struct sigstack *__oss)
     __attribute__ ((__nothrow__ , __leaf__)) __attribute__ ((__deprecated__));
# 376 "/usr/include/signal.h" 3 4
# 1 "/usr/include/bits/sigthread.h" 1 3 4
# 31 "/usr/include/bits/sigthread.h" 3 4
extern int pthread_sigmask (int __how,
       const __sigset_t *__restrict __newmask,
       __sigset_t *__restrict __oldmask)__attribute__ ((__nothrow__ , __leaf__));


extern int pthread_kill (pthread_t __threadid, int __signo) __attribute__ ((__nothrow__ , __leaf__));
# 377 "/usr/include/signal.h" 2 3 4






extern int __libc_current_sigrtmin (void) __attribute__ ((__nothrow__ , __leaf__));

extern int __libc_current_sigrtmax (void) __attribute__ ((__nothrow__ , __leaf__));





# 1 "/usr/include/bits/signal_ext.h" 1 3 4
# 392 "/usr/include/signal.h" 2 3 4


# 37 "/usr/include/sys/wait.h" 2 3 4
# 74 "/usr/include/sys/wait.h" 3 4
# 1 "/usr/include/bits/types/idtype_t.h" 1 3 4




typedef enum
{
  P_ALL,
  P_PID,
  P_PGID,
  P_PIDFD,

} idtype_t;
# 75 "/usr/include/sys/wait.h" 2 3 4
# 83 "/usr/include/sys/wait.h" 3 4
extern __pid_t wait (int *__stat_loc);
# 106 "/usr/include/sys/wait.h" 3 4
extern __pid_t waitpid (__pid_t __pid, int *__stat_loc, int __options);
# 127 "/usr/include/sys/wait.h" 3 4
extern int waitid (idtype_t __idtype, __id_t __id, siginfo_t *__infop,
     int __options);






struct rusage;







extern __pid_t wait3 (int *__stat_loc, int __options,
        struct rusage * __usage) __attribute__ ((__nothrow__));
# 159 "/usr/include/sys/wait.h" 3 4
extern __pid_t wait4 (__pid_t __pid, int *__stat_loc, int __options,
        struct rusage *__usage) __attribute__ ((__nothrow__));
# 173 "/usr/include/sys/wait.h" 3 4

# 14 "src/main.c" 2







# 20 "src/main.c"
typedef int16_t i16;
typedef int32_t i32;
typedef int64_t i64;
typedef uint8_t u8;
typedef uint16_t u16;
typedef uint32_t u32;
typedef uint64_t u64;
typedef uintptr_t umm;

typedef float f32;
typedef double f64;

# 1 "src/common.h" 1



typedef struct Source_Location Source_Location;
struct Source_Location
{
    const char* file_name;
    i32 line_number;


};

void generic_error(Source_Location location, const char* format, ...);

void compiler_bug(Source_Location location, const char* format, ...);

void not_implemented(Source_Location location, const char* format, ...);


Source_Location make_location(const char* file, i32 line);


void output_error(Source_Location location, const char* type, char* format, va_list arglist);
# 33 "src/main.c" 2

# 1 "src/log.h" 1
# 35 "src/main.c" 2
# 1 "src/nb_memory.h" 1






typedef struct Allocator Allocator;

typedef void* (*Allocate_Fn)(Allocator*, size_t);
typedef void (*Free_Fn)(Allocator*, void*);
typedef void (*Free_All_Fn)(Allocator*);

struct Allocator
{
    Allocate_Fn allocate;
    Free_Fn free;
    Free_All_Fn free_all;
};


# 20 "src/nb_memory.h" 3 4
_Bool 
# 20 "src/nb_memory.h"
    is_power_of_two(umm x)
{
    return (x & (x - 1)) == 0;
}

umm align_forward(umm pointer, size_t align)
{
    
# 27 "src/nb_memory.h" 3 4
   ((void) sizeof ((
# 27 "src/nb_memory.h"
   is_power_of_two(align)
# 27 "src/nb_memory.h" 3 4
   ) ? 1 : 0), __extension__ ({ if (
# 27 "src/nb_memory.h"
   is_power_of_two(align)
# 27 "src/nb_memory.h" 3 4
   ) ; else __assert_fail (
# 27 "src/nb_memory.h"
   "is_power_of_two(align)"
# 27 "src/nb_memory.h" 3 4
   , "src/nb_memory.h", 27, __extension__ __PRETTY_FUNCTION__); }))
# 27 "src/nb_memory.h"
                                 ;

    umm p = pointer;
    umm a = (umm)align;


    umm modulo = p & (a - 1);

    if (modulo != 0)
    {
        p += a - modulo;
    }
    return p;
}

typedef struct Arena Arena;
struct Arena
{
    Allocator base_allocator;
    unsigned char* buffer;
    size_t buffer_length;
    size_t previous_offset;
    size_t current_offset;
};


typedef struct Temporary_Arena Temporary_Arena;
struct Temporary_Arena
{
    Arena* arena;
    size_t previous_offset;
    size_t current_offset;
};

void* arena_alloc_align(Arena* arena, size_t size, size_t alignment)
{
    umm current_pointer = (umm)arena->buffer + (umm)arena->current_offset;
    umm offset = align_forward(current_pointer, alignment);

    offset -= (umm)arena->buffer;

    if (offset + size <= arena->buffer_length)
    {
        void* pointer = &arena->buffer[offset];
        arena->previous_offset = offset;
        arena->current_offset = offset + size;

        memset(pointer, 0, size);
        return pointer;
    }

    return 
# 78 "src/nb_memory.h" 3 4
          ((void *)0)
# 78 "src/nb_memory.h"
              ;
}




void* arena_alloc(Allocator* arena, size_t size)
{
    return arena_alloc_align(((Arena*)(arena)), size, (2 * sizeof(void*)));
}

void* arena_resize_align(Arena* arena, void* old_memory, size_t old_size, size_t new_size, size_t alignment)
{
    unsigned char* old_mem = (unsigned char*)old_memory;

    
# 93 "src/nb_memory.h" 3 4
   ((void) sizeof ((
# 93 "src/nb_memory.h"
   is_power_of_two(alignment)
# 93 "src/nb_memory.h" 3 4
   ) ? 1 : 0), __extension__ ({ if (
# 93 "src/nb_memory.h"
   is_power_of_two(alignment)
# 93 "src/nb_memory.h" 3 4
   ) ; else __assert_fail (
# 93 "src/nb_memory.h"
   "is_power_of_two(alignment)"
# 93 "src/nb_memory.h" 3 4
   , "src/nb_memory.h", 93, __extension__ __PRETTY_FUNCTION__); }))
# 93 "src/nb_memory.h"
                                     ;

    if (old_mem == 
# 95 "src/nb_memory.h" 3 4
                  ((void *)0) 
# 95 "src/nb_memory.h"
                       || old_size == 0)
    {
        return arena_alloc_align(arena, new_size, alignment);
    }
    else if (arena->buffer <= old_mem && old_mem <= arena->buffer + arena->buffer_length)
    {
        if (arena->buffer + arena->previous_offset == old_mem)
        {
            arena->current_offset = arena->previous_offset + new_size;
            if (new_size > old_size)
            {
                memset(&arena->buffer[arena->current_offset], 0, new_size - old_size);
            }
            return old_memory;
        }
        else
        {
            void* new_memory = arena_alloc_align(arena, new_size, alignment);
            size_t copy_size = old_size < new_size ? old_size : new_size;
            memmove(new_memory, old_memory, copy_size);
            return new_memory;
        }
    }
    else
    {
        
# 120 "src/nb_memory.h" 3 4
       ((void) sizeof ((
# 120 "src/nb_memory.h"
       0 && "Memory is out of bounds of the buffer in this arena"
# 120 "src/nb_memory.h" 3 4
       ) ? 1 : 0), __extension__ ({ if (
# 120 "src/nb_memory.h"
       0 && "Memory is out of bounds of the buffer in this arena"
# 120 "src/nb_memory.h" 3 4
       ) ; else __assert_fail (
# 120 "src/nb_memory.h"
       "0 && \"Memory is out of bounds of the buffer in this arena\""
# 120 "src/nb_memory.h" 3 4
       , "src/nb_memory.h", 120, __extension__ __PRETTY_FUNCTION__); }))
# 120 "src/nb_memory.h"
                                                                         ;
        return 
# 121 "src/nb_memory.h" 3 4
              ((void *)0)
# 121 "src/nb_memory.h"
                  ;
    }
}

void* arena_resize(Arena* arena, void* old_memory, size_t old_size, size_t new_size)
{
    return arena_resize_align(arena, old_memory, old_size, new_size, (2 * sizeof(void*)));
}

void arena_free(Allocator* allocator, void* ptr)
{
    (void)allocator;
    (void)ptr;
}

void arena_free_all(Allocator* allocator)
{
    Arena* arena = ((Arena*)(allocator));
    arena->current_offset = 0;
    arena->previous_offset = 0;
}

void arena_init(Arena* arena, void* backing_buffer, size_t backing_buffer_length)
{
    arena->base_allocator.allocate = arena_alloc;
    arena->base_allocator.free = arena_free;
    arena->base_allocator.free_all = arena_free_all;
    arena->buffer = (unsigned char*)backing_buffer;
    arena->buffer_length = backing_buffer_length;
    arena->current_offset = 0;
    arena->previous_offset = 0;
}

Temporary_Arena temp_arena_memory_begin(Arena* arena)
{
    Temporary_Arena temp;
    temp.arena = arena;
    temp.previous_offset = arena->previous_offset;
    temp.current_offset = arena->current_offset;
    return temp;
}

void temp_arena_memory_end(Temporary_Arena temp)
{
    temp.arena->previous_offset = temp.previous_offset;
    temp.arena->current_offset = temp.current_offset;
}
# 36 "src/main.c" 2
# 1 "src/nb_string.h" 1



typedef struct String String;
struct String
{
    size_t length;
    char* str;
};

typedef struct String_View String_View;
struct String_View
{
    String* string;
};

String_View sv_create(String* string)
{
    String_View view =
    {
        .string = string
    };
    return view;
}

size_t sv_len(String_View view)
{
    return view.string->length;
}

char* sv_null_terminated_string(String_View view)
{
    return view.string->str;
}

String string_create(char* nt_str)
{
    String string =
    {
        .length = strlen(nt_str),
        .str = nt_str
    };
    return string;
}

void string_set_length(String* string, char* value, size_t length)
{
    for(int i = 0; i < length; i++)
    {
        string->str[i] = value[i];
    }
    string->str[length] = '\0';
}

void string_set(String* string, char* value)
{
    size_t length = strlen(value);
    string_set_length(string, value, length);
}



String* string_allocate_empty(size_t size, Allocator* allocator)
{
    String* string = (String*)allocator->allocate(allocator, (sizeof(String) + size + 1));
    string->length = size;
    string->str = (char*)((umm)string) + sizeof(String);
    return string;
}

String* string_allocate(char* nt_str, Allocator* allocator)
{
    size_t size = strlen(nt_str);
    String* string = string_allocate_empty(size, allocator);
    string_set(string, nt_str);
    return string;
}

String* string_copy(String* input, Allocator* allocator)
{
    String* string = string_allocate_empty(input->length, allocator);
    string_set(string, input->str);
    return string;
}

typedef struct
{
    char* string;
    size_t current_index;
    size_t capacity;
} String_Builder;

String* string_create_from_file_with_allocator(FILE* file, Allocator* allocator)
{
    fseek(file, 0, 
# 95 "src/nb_string.h" 3 4
                  2
# 95 "src/nb_string.h"
                          );
    i32 file_size = ftell(file);
    if(file_size <= 0)
    {
        return 
# 99 "src/nb_string.h" 3 4
              ((void *)0)
# 99 "src/nb_string.h"
                  ;
    }

    fseek(file, 0, 
# 102 "src/nb_string.h" 3 4
                  0
# 102 "src/nb_string.h"
                          );

    String* new_string = string_allocate_empty(file_size, allocator);
    fread(new_string->str, file_size, 1, file);
    new_string->str[file_size] = '\0';

    return new_string;
}

void string_print(String* string);

void string_write_to_file(String* string, FILE* file)
{
    fwrite(string->str, string->length, 1, file);
}

String* string_createf(Allocator* allocator, const char* format, ...)
{
    va_list arglist;
    
# 121 "src/nb_string.h" 3 4
   __builtin_va_start(
# 121 "src/nb_string.h"
   arglist
# 121 "src/nb_string.h" 3 4
   ,
# 121 "src/nb_string.h"
   format
# 121 "src/nb_string.h" 3 4
   )
# 121 "src/nb_string.h"
                            ;
    i32 format_length = vsnprintf(
# 122 "src/nb_string.h" 3 4
                                 ((void *)0)
# 122 "src/nb_string.h"
                                     , 0, format, arglist);
    if (format_length == 0)
    {
        
# 125 "src/nb_string.h" 3 4
       __builtin_va_end(
# 125 "src/nb_string.h"
       arglist
# 125 "src/nb_string.h" 3 4
       )
# 125 "src/nb_string.h"
                      ;
        return 
# 126 "src/nb_string.h" 3 4
              ((void *)0)
# 126 "src/nb_string.h"
                  ;
    }

    String* result = string_allocate_empty(format_length, allocator);
    
# 130 "src/nb_string.h" 3 4
   __builtin_va_start(
# 130 "src/nb_string.h"
   arglist
# 130 "src/nb_string.h" 3 4
   ,
# 130 "src/nb_string.h"
   format
# 130 "src/nb_string.h" 3 4
   )
# 130 "src/nb_string.h"
                            ;
    vsnprintf(result->str, format_length + 1, format, arglist);
    result->str[format_length] = '\0';

    return result;
}


# 137 "src/nb_string.h" 3 4
_Bool 
# 137 "src/nb_string.h"
    string_equal(String* lhs, String* rhs)
{
    if (lhs->length != rhs->length) return 
# 139 "src/nb_string.h" 3 4
                                          0
# 139 "src/nb_string.h"
                                               ;
    return strncmp(lhs->str, rhs->str, lhs->length) == 0;
}


# 143 "src/nb_string.h" 3 4
_Bool 
# 143 "src/nb_string.h"
    string_equal_cstr(String* lhs, const char* rhs)
{
    size_t len = strlen(rhs);
    if(len != lhs->length) return 
# 146 "src/nb_string.h" 3 4
                                 0
# 146 "src/nb_string.h"
                                      ;
    return strncmp(lhs->str, rhs, len) == 0;
}


# 150 "src/nb_string.h" 3 4
_Bool 
# 150 "src/nb_string.h"
    string_ends_with_cstr(String* lhs, const char* rhs)
{
    size_t len = strlen(rhs);
    if (len > lhs->length) return 
# 153 "src/nb_string.h" 3 4
                                 0
# 153 "src/nb_string.h"
                                      ;

    size_t start = lhs->length - len;
    for (i32 i = 0; i < len; i++)
    {
        if (lhs->str[start + i] != rhs[i]) return 
# 158 "src/nb_string.h" 3 4
                                                 0
# 158 "src/nb_string.h"
                                                      ;
    }
    return 
# 160 "src/nb_string.h" 3 4
          1
# 160 "src/nb_string.h"
              ;
}

void string_print(String* string)
{
    printf("%s", string->str);
}

void string_fprintf(String* string, FILE* file)
{
    fprintf(file, "%s", string->str);
}

String* string_substring(String* string, size_t start, size_t length, Allocator* allocator)
{
    if (start < 0) start = 0;
    if (length <= 0) return 
# 176 "src/nb_string.h" 3 4
                           ((void *)0)
# 176 "src/nb_string.h"
                               ;
    if (length > string->length) length = string->length;
    if (length + start > string->length)
    {
        length = string->length - start;
    }

    String* substr = string_allocate_empty(length, allocator);
    size_t index = start;
    for (i32 i = 0; i < length; i++)
    {
        substr->str[i] = string->str[index++];
    }
    substr->str[substr->length] = '\0';
    return substr;
}

String* string_concat_str(String* lhs, String* rhs, Allocator* allocator)
{
    if (lhs->length == 0) return string_allocate(rhs->str, allocator);
    if (rhs->length == 0) return string_allocate(lhs->str, allocator);

    String* new_string = string_allocate_empty(lhs->length + rhs->length, allocator);

    for (i32 i = 0; i < lhs->length; i++)
    {
        new_string->str[i] = lhs->str[i];
    }

    size_t index = 0;
    for (size_t i = lhs->length; i < lhs->length + rhs->length; i++)
    {
        new_string->str[i] = rhs->str[index++];
    }

    return new_string;
}

String* string_concat_cstr(String* lhs, char* rhs, Allocator* allocator)
{
    size_t rhs_len = strlen(rhs);
    if(lhs->length == 0) return string_allocate(rhs, allocator);
    if(rhs_len == 0) return string_allocate(lhs->str, allocator);
    String* new_string = string_allocate_empty(lhs->length + rhs_len, allocator);

    for (i32 i = 0; i < lhs->length; i++)
    {
        new_string->str[i] = lhs->str[i];
    }

    size_t index = 0;
    for (size_t i = lhs->length; i < lhs->length + rhs_len; i++)
    {
        new_string->str[i] = rhs[index++];
    }

    return new_string;
}

typedef struct
{
    String** strings;
    i32 count;
    size_t capacity;
} String_Array;

String_Array* string_array_allocate(i32 capacity, Allocator* allocator)
{
    String_Array* array = allocator->allocate(allocator, sizeof(String_Array));
    array->strings = allocator->allocate(allocator, sizeof(String*) * capacity);
    array->capacity = capacity;
    array->count = 0;
    return array;
}

void string_array_push(String_Array* array, String* string)
{
    if(array->count + 1 >= array->capacity)
    {
        (generic_error((make_location("src/nb_string.h", 255)), "String array out of space: %d/%d\n", array->count, array->capacity));
        
# 256 "src/nb_string.h" 3 4
       ((void) sizeof ((0) ? 1 : 0), __extension__ ({ if (0) ; else __assert_fail (
# 256 "src/nb_string.h"
       "false"
# 256 "src/nb_string.h" 3 4
       , "src/nb_string.h", 256, __extension__ __PRETTY_FUNCTION__); }))
# 256 "src/nb_string.h"
                    ;
    }

    array->strings[array->count++] = string;
}

String_Array* string_split(String* string, char delim, Allocator* allocator)
{
    i32 count = 1;
    for (i32 i = 0; i < string->length; i++)
    {
        if(string->str[i] == delim)
        {
            count++;
        }
    }

    String_Array* array = string_array_allocate(count, allocator);
    array->count = count;
    i32 current_index = 0;
    for (i32 i = 0; i < array->count; i++)
    {
        i32 start = current_index;
        for (; current_index < string->length; current_index++)
        {
            if (string->str[current_index] == delim) break;
        }
        array->strings[i] = string_substring(string, start, current_index, allocator);
    }
    return array;
}

void sb_init(String_Builder* builder, size_t initial_capacity)
{
    builder->capacity = initial_capacity;
    builder->string = calloc(builder->capacity, 1);
    builder->current_index = 0;
}

void sb_init_with_allocator(String_Builder* builder, size_t initial_capacity, Allocator* allocator)
{
    builder->capacity = initial_capacity;
    builder->string = allocator->allocate(allocator, builder->capacity);
    for (i32 i = 0; i < initial_capacity; i++)
    {
        builder->string[i] = 0;
    }
    builder->current_index = 0;
}

static size_t next_power_of_two(size_t n)
{
    i32 power = 1;
    if (n && !(n & (n - 1)))
    {
        return n;
    }

    while (power < n)
    {
        power <<= 1;
    }

    return power;
}


static void sb_maybe_expand(String_Builder* builder, size_t extra_length)
{
    if (!builder->string)
    {
        sb_init(builder, next_power_of_two(extra_length));
    }

    if(builder->current_index + extra_length >= builder->capacity)
    {
        size_t old_capacity = builder->capacity;
        builder->capacity *= 2;
        builder->string = realloc(builder->string, builder->capacity);
        for (size_t i = old_capacity; i < builder->capacity; i++)
        {
            builder->string[i] = '\0';
        }
    }
}

void sb_append(String_Builder* builder, const char* str)
{
    size_t len = strlen(str);
    if(len == 0)
    {
        return;
    }

    sb_maybe_expand(builder, len);

    size_t c = 0;
    for (size_t i = builder->current_index; i < builder->current_index + len; i++)
    {
        builder->string[i] = str[c++];
    }
    builder->current_index += len;
}

void sb_appendf(String_Builder* builder, const char* format, ...)
{
    va_list arglist;
    
# 363 "src/nb_string.h" 3 4
   __builtin_va_start(
# 363 "src/nb_string.h"
   arglist
# 363 "src/nb_string.h" 3 4
   ,
# 363 "src/nb_string.h"
   format
# 363 "src/nb_string.h" 3 4
   )
# 363 "src/nb_string.h"
                            ;
    i32 format_length = vsnprintf(
# 364 "src/nb_string.h" 3 4
                                 ((void *)0)
# 364 "src/nb_string.h"
                                     , 0, format, arglist);
    if (format_length == 0)
    {
        
# 367 "src/nb_string.h" 3 4
       __builtin_va_end(
# 367 "src/nb_string.h"
       arglist
# 367 "src/nb_string.h" 3 4
       )
# 367 "src/nb_string.h"
                      ;
        return;
    }

    sb_maybe_expand(builder, format_length);

    
# 373 "src/nb_string.h" 3 4
   __builtin_va_start(
# 373 "src/nb_string.h"
   arglist
# 373 "src/nb_string.h" 3 4
   ,
# 373 "src/nb_string.h"
   format
# 373 "src/nb_string.h" 3 4
   )
# 373 "src/nb_string.h"
                            ;
    vsnprintf(&builder->string[builder->current_index], format_length + 1, format, arglist);
    
# 375 "src/nb_string.h" 3 4
   __builtin_va_end(
# 375 "src/nb_string.h"
   arglist
# 375 "src/nb_string.h" 3 4
   )
# 375 "src/nb_string.h"
                  ;

    builder->current_index += format_length;
}

void sb_newline(String_Builder* builder)
{
    sb_append(builder, "\n");
}

String* sb_get_result(String_Builder* builder, Allocator* allocator)
{
    if (!builder->string || builder->current_index == 0)
    {
        (generic_error((make_location("src/nb_string.h", 389)), "Trying to create the empty string.", ));
        return 
# 390 "src/nb_string.h" 3 4
              ((void *)0)
# 390 "src/nb_string.h"
                  ;
    }

    String* result = string_allocate_empty(builder->current_index, allocator);
    string_set(result, builder->string);
    return result;
}

void sb_free(String_Builder* builder)
{
    free(builder->string);
}

static void sb_indent(String_Builder* builder, i32 indentation)
{
    for(i32 i = 0; i < indentation; i++)
    {
        sb_append(builder, " ");
    }
}
# 37 "src/main.c" 2
# 1 "src/nb_file.h" 1



typedef struct
{
    FILE* handle;
    String* path;
    String* extension;
} File;

typedef enum
{
    FILE_READ = 1 << 0,
    FILE_WRITE = 1 << 1,
    FILE_TEXT = 1 << 2,
    FILE_BINARY = 1 << 3,
    FILE_CREATE = 1 << 4,
} File_Open_Options;
# 38 "src/main.c" 2
# 1 "src/os.h" 1



String_Array* temp_files;


String* create_temp_file(Allocator* allocator);
void cleanup_temp_files();

# 9 "src/os.h" 3 4
_Bool 
# 9 "src/os.h"
    run_subprocess(char** argv);

# 10 "src/os.h" 3 4
_Bool 
# 10 "src/os.h"
    absolute_path(String* str, String* out);
# 39 "src/main.c" 2


# 1 "src/linux_os.h" 1



String* create_temp_file(Allocator* allocator)
{
    if (!temp_files)
    {
        temp_files = string_array_allocate(32, allocator);
    }

    String* path = string_allocate("/tmp/ske-XXXXXX", allocator);
    i32 fd = mkstemp(path->str);
    if (fd == 1)
    {
        compiler_bug("mkstemp failed: %s\n", strerror(
# 15 "src/linux_os.h" 3 4
                                                     (*__errno_location ())
# 15 "src/linux_os.h"
                                                          ));
    }
    close(fd);
    string_array_push(temp_files, path);
    return path;
}

void cleanup_temp_files()
{
    if (temp_files)
    {
        for (i32 i = 0; i < temp_files->count; i++)
        {
            unlink(temp_files->strings[i]->str);
        }
        temp_files->count = 0;
    }
}


# 34 "src/linux_os.h" 3 4
_Bool 
# 34 "src/linux_os.h"
    run_subprocess(char** argv)
{
    if (fork() == 0)
    {
        execvp(argv[0], argv);
        generic_error("exec failed: %s: %s\n", argv[0], strerror(
# 39 "src/linux_os.h" 3 4
                                                                (*__errno_location ())
# 39 "src/linux_os.h"
                                                                     ));
        exit(1);
    }

    i32 status;
    while (wait(&status) > 0);
    if (status != 0)
    {
        exit(1);
    }
    return 
# 49 "src/linux_os.h" 3 4
          1
# 49 "src/linux_os.h"
              ;
}


# 52 "src/linux_os.h" 3 4
_Bool 
# 52 "src/linux_os.h"
    absolute_path(String* str, String* out)
{
    char* path = realpath(str->str, 
# 54 "src/linux_os.h" 3 4
                                   ((void *)0)
# 54 "src/linux_os.h"
                                       );
    if (!path)
    {
        return 
# 57 "src/linux_os.h" 3 4
              0
# 57 "src/linux_os.h"
                   ;
    }
    string_set(out, path);
    return 
# 60 "src/linux_os.h" 3 4
          1
# 60 "src/linux_os.h"
              ;
}
# 42 "src/main.c" 2




# 1 "src/lex.h" 1




typedef enum
{
    TOKEN_NUMBER,
    TOKEN_PLUS,
    TOKEN_MINUS,
    TOKEN_STAR,
    TOKEN_SLASH,
    TOKEN_SEMICOLON,
    TOKEN_COMMA,

    TOKEN_BANG,
    TOKEN_BANG_EQUAL,

    TOKEN_ARROW,

    TOKEN_LESS,
    TOKEN_GREATER,
    TOKEN_LESS_EQUAL,
    TOKEN_GREATER_EQUAL,

    TOKEN_PIPE,
    TOKEN_PIPE_PIPE,

    TOKEN_AMPERSAND,
    TOKEN_AMPERSAND_AMPERSAND,

    TOKEN_LEFT_PAREN,
    TOKEN_RIGHT_PAREN,
    TOKEN_LEFT_BRACE,
    TOKEN_RIGHT_BRACE,

    TOKEN_COLON,
    TOKEN_COLON_COLON,
    TOKEN_COLON_EQUAL,
    TOKEN_EQUAL,
    TOKEN_EQUAL_EQUAL,

    TOKEN_IF, TOKEN_ELSE, TOKEN_WHILE,
    TOKEN_RETURN,
    TOKEN_FALSE, TOKEN_TRUE, TOKEN_FOR,

    TOKEN_IDENTIFIER,
    TOKEN_STRING,

    TOKEN_EOF,

    TOKEN_ERROR
} Token_Type;

typedef struct
{
    Token_Type type;
    char* start;
    i32 length;
    i32 line;
    i32 position;
} Token;

typedef struct
{
    char* start;
    char* current;

    i32 line;
    i32 position_on_line;

    String_View file_name;
    String_View absolute_path;
} Lexer;

typedef struct
{
    Token* tokens;
    i32 capacity;
    i32 count;
} Token_List;

typedef struct
{
    Token* tokens;
    i32 current;
    i32 count;
} Token_Stream;

void Lex_init(Lexer* lexer, String* source, String_View file_name, String_View absolute_path);
Token Lex_scan_token(Lexer* lexer);

void token_list_init(Token_List* list, i32 initial_capacity);
void token_list_free(Token_List* list);
void token_list_maybe_expand(Token_List* list);
void token_list_add(Token_List* list, Token token);

Token_List* Lex_tokenize(String* input, String* file_name, String* absolute_path);
String* Lex_pretty_print(Token_List* list, Allocator* allocator);
# 47 "src/main.c" 2
# 1 "src/ast.h" 1



typedef enum
{
    AST_NODE_STATEMENT,
    AST_NODE_PROGRAM,
    AST_NODE_FUN_DECL,
    AST_NODE_CALL,
    AST_NODE_ARGUMENT_LIST,
    AST_NODE_FUNCTION_ARGUMENT,
    AST_NODE_VARIABLE,
    AST_NODE_IF,
    AST_NODE_RETURN,
    AST_NODE_BLOCK,
    AST_NODE_LITERAL,
    AST_NODE_STRING,
    AST_NODE_BINARY,
    AST_NODE_UNARY,
    AST_NODE_TYPE_SPECIFIER,
    AST_NODE_ERROR
} AST_Node_Type;

typedef enum
{
    TYPE_SPEC_INT,
    TYPE_SPEC_UNIT,
    TYPE_SPEC_INVALID
} Type_Specifier;

typedef struct AST_Node AST_Node;

typedef struct AST_Node_List AST_Node_List;
struct AST_Node_List
{
    AST_Node** nodes;
    i32 capacity;
    i32 count;
};

typedef struct AST_Literal AST_Literal;
struct AST_Literal
{
    enum AST_Literal_Type
    {
        LIT_INT,
        LIT_FLOAT,
        LIT_STRING
    } type;

    union
    {
        i64 i;
        f64 f;
        String* s;
    };
};

typedef struct AST_Node AST_Node;
struct AST_Node
{
    AST_Node_Type type;
    AST_Node* parent;

    union
    {
        AST_Literal literal;
        String* string;
        struct
        {
            AST_Node* expression;
            Token_Type operator;
        } unary;
        struct
        {
            AST_Node* left;
            AST_Node* right;

            Token_Type operator;
        } binary;
        struct
        {
            AST_Node_List declarations;
        } program;
        struct
        {
            AST_Node* expression;
        } expression;
        struct
        {
            AST_Node* statement;
        } statement;
        struct
        {
            AST_Node* expression;
        } return_statement;
        struct
        {
            AST_Node* condition;
            AST_Node* then_arm;
            AST_Node* else_arm;
        } if_statement;
        struct
        {
            String* variable_name;
        } variable;
        struct
        {
            String* name;
            AST_Node* return_type;
            AST_Node_List arguments;
            AST_Node* body;
        } fun_decl;
        struct
        {
            String* name;
            AST_Node* type;
        } fun_argument;
        struct
        {
            String* name;
            AST_Node_List arguments;
        } fun_call;
        struct
        {
            AST_Node_List declarations;
        } block;
        struct
        {
            Type_Specifier type;
        } type_specifier;
        struct
        {
            AST_Node* rest;
        } error;
    };
};

typedef void (*Pretty_Print_Fn)(AST_Node*, i32, String_Builder*);

static void pretty_print_unary(AST_Node* node, i32 indentation, String_Builder* builder);
static void pretty_print_binary(AST_Node* binary, i32 indentation, String_Builder* builder);
static void pretty_print_string(AST_Node* string, i32 indentation, String_Builder* builder);
static void pretty_print_expression(AST_Node* node, i32 indentation, String_Builder* builder);
static void pretty_print_block(AST_Node* block, i32 indentation, String_Builder* builder);
static void pretty_print_statement(AST_Node* statement, i32 indentation, String_Builder* builder);
static void pretty_print_expression(AST_Node* expression, i32 indentation, String_Builder* builder);
# 48 "src/main.c" 2
# 1 "src/parse.h" 1




typedef enum
{
    PREC_NONE,
    PREC_ASSIGNMENT,
    PREC_OR,
    PREC_AND,
    PREC_BITWISE,
    PREC_EQUALITY,
    PREC_COMPARISON,
    PREC_TERM,
    PREC_FACTOR,
    PREC_UNARY,
    PREC_CALL,
    PREC_PRIMARY
} Precedence;

typedef struct Parser Parser;
struct Parser
{
    Token current;
    Token previous;

    Token_List* token_stream;
    i32 current_token;

    String_View absolute_path;

    Allocator* allocator;

    
# 34 "src/parse.h" 3 4
   _Bool 
# 34 "src/parse.h"
        had_error;
    
# 35 "src/parse.h" 3 4
   _Bool 
# 35 "src/parse.h"
        panic_mode;

    AST_Node* root;
};

typedef AST_Node* (*Parse_Fn)(Parser*, AST_Node* left, AST_Node* parent);
typedef struct
{
    Parse_Fn prefix;
    Parse_Fn infix;
    Precedence precedence;
} Parse_Rule;

static Parse_Rule* Parser_get_rule(Token_Type type);
static AST_Node* Parser_statement(Parser* parser, AST_Node* parent);
static AST_Node* Parser_expression(Parser* parser, AST_Node* parent);
static AST_Node* Parser_precedence(Parser* parser, Precedence precedence, AST_Node* parent);
static AST_Node* Parser_declaration(Parser* parser, AST_Node* parent);
static AST_Node* Parser_call(Parser* parser, AST_Node* previous, AST_Node* parent);
static AST_Node* Parser_grouping(Parser* parser, AST_Node* previous, AST_Node* parent);
static AST_Node* Parser_unary(Parser* parser, AST_Node* previous, AST_Node* parent);
static AST_Node* Parser_binary(Parser* parser, AST_Node* previous, AST_Node* parent);
static AST_Node* Parser_variable(Parser* parser, AST_Node* previous, AST_Node* parent, const char* error_message);
static AST_Node* Parser_named_variable(Parser* parser, AST_Node* previous, AST_Node* parent);
static AST_Node* Parser_string(Parser* parser, AST_Node* previous, AST_Node* parent);
static AST_Node* Parser_number(Parser* parser, AST_Node* previous, AST_Node* parent);


Parse_Rule rules[] = {
  [TOKEN_LEFT_PAREN] = {Parser_grouping, Parser_call, PREC_CALL},
  [TOKEN_RIGHT_PAREN] = {
# 65 "src/parse.h" 3 4
                                ((void *)0)
# 65 "src/parse.h"
                                    , 
# 65 "src/parse.h" 3 4
                                                       ((void *)0)
# 65 "src/parse.h"
                                                           , PREC_NONE},
  [TOKEN_LEFT_BRACE] = {
# 66 "src/parse.h" 3 4
                                ((void *)0)
# 66 "src/parse.h"
                                    , 
# 66 "src/parse.h" 3 4
                                                       ((void *)0)
# 66 "src/parse.h"
                                                           , PREC_NONE},
  [TOKEN_RIGHT_BRACE] = {
# 67 "src/parse.h" 3 4
                                ((void *)0)
# 67 "src/parse.h"
                                    , 
# 67 "src/parse.h" 3 4
                                                       ((void *)0)
# 67 "src/parse.h"
                                                           , PREC_NONE},


  [TOKEN_MINUS] = {Parser_unary, Parser_binary, PREC_TERM},
  [TOKEN_PLUS] = {
# 71 "src/parse.h" 3 4
                                ((void *)0)
# 71 "src/parse.h"
                                    , Parser_binary, PREC_TERM},
  [TOKEN_SEMICOLON] = {
# 72 "src/parse.h" 3 4
                                ((void *)0)
# 72 "src/parse.h"
                                    , 
# 72 "src/parse.h" 3 4
                                                       ((void *)0)
# 72 "src/parse.h"
                                                           , PREC_NONE},
  [TOKEN_SLASH] = {
# 73 "src/parse.h" 3 4
                                ((void *)0)
# 73 "src/parse.h"
                                    , Parser_binary, PREC_FACTOR},
  [TOKEN_STAR] = {
# 74 "src/parse.h" 3 4
                                ((void *)0)
# 74 "src/parse.h"
                                    , Parser_binary, PREC_FACTOR},
  [TOKEN_BANG] = {Parser_unary, 
# 75 "src/parse.h" 3 4
                                                       ((void *)0)
# 75 "src/parse.h"
                                                           , PREC_TERM},
  [TOKEN_BANG_EQUAL] = {
# 76 "src/parse.h" 3 4
                                ((void *)0)
# 76 "src/parse.h"
                                    , Parser_binary, PREC_COMPARISON},
  [TOKEN_EQUAL] = {
# 77 "src/parse.h" 3 4
                                ((void *)0)
# 77 "src/parse.h"
                                    , Parser_binary, PREC_COMPARISON},
  [TOKEN_EQUAL_EQUAL] = {
# 78 "src/parse.h" 3 4
                                ((void *)0)
# 78 "src/parse.h"
                                    , Parser_binary, PREC_EQUALITY},
  [TOKEN_GREATER] = {
# 79 "src/parse.h" 3 4
                                ((void *)0)
# 79 "src/parse.h"
                                    , Parser_binary, PREC_COMPARISON},
  [TOKEN_GREATER_EQUAL] = {
# 80 "src/parse.h" 3 4
                                ((void *)0)
# 80 "src/parse.h"
                                    , Parser_binary, PREC_COMPARISON},
  [TOKEN_LESS] = {
# 81 "src/parse.h" 3 4
                                ((void *)0)
# 81 "src/parse.h"
                                    , Parser_binary, PREC_COMPARISON},
  [TOKEN_LESS_EQUAL] = {
# 82 "src/parse.h" 3 4
                                ((void *)0)
# 82 "src/parse.h"
                                    , Parser_binary, PREC_COMPARISON},
  [TOKEN_IDENTIFIER] = {Parser_named_variable, 
# 83 "src/parse.h" 3 4
                                                       ((void *)0)
# 83 "src/parse.h"
                                                           , PREC_NONE},
  [TOKEN_STRING] = {Parser_string, 
# 84 "src/parse.h" 3 4
                                                       ((void *)0)
# 84 "src/parse.h"
                                                           , PREC_NONE},
  [TOKEN_NUMBER] = {Parser_number, 
# 85 "src/parse.h" 3 4
                                                       ((void *)0)
# 85 "src/parse.h"
                                                           , PREC_NONE},
  [TOKEN_ELSE] = {
# 86 "src/parse.h" 3 4
                                ((void *)0)
# 86 "src/parse.h"
                                    , 
# 86 "src/parse.h" 3 4
                                                       ((void *)0)
# 86 "src/parse.h"
                                                           , PREC_NONE},
  [TOKEN_FALSE] = {
# 87 "src/parse.h" 3 4
                                ((void *)0)
# 87 "src/parse.h"
                                    , 
# 87 "src/parse.h" 3 4
                                                       ((void *)0)
# 87 "src/parse.h"
                                                           , PREC_NONE},
  [TOKEN_FOR] = {
# 88 "src/parse.h" 3 4
                                ((void *)0)
# 88 "src/parse.h"
                                    , 
# 88 "src/parse.h" 3 4
                                                       ((void *)0)
# 88 "src/parse.h"
                                                           , PREC_NONE},
  [TOKEN_IF] = {
# 89 "src/parse.h" 3 4
                                ((void *)0)
# 89 "src/parse.h"
                                    , 
# 89 "src/parse.h" 3 4
                                                       ((void *)0)
# 89 "src/parse.h"
                                                           , PREC_NONE},
  [TOKEN_PIPE] = {
# 90 "src/parse.h" 3 4
                                ((void *)0)
# 90 "src/parse.h"
                                    , Parser_binary, PREC_BITWISE},
  [TOKEN_PIPE_PIPE] = {
# 91 "src/parse.h" 3 4
                                ((void *)0)
# 91 "src/parse.h"
                                    , Parser_binary, PREC_OR},
  [TOKEN_AMPERSAND] = {
# 92 "src/parse.h" 3 4
                                ((void *)0)
# 92 "src/parse.h"
                                    , Parser_binary, PREC_BITWISE},
  [TOKEN_AMPERSAND_AMPERSAND] = {
# 93 "src/parse.h" 3 4
                                ((void *)0)
# 93 "src/parse.h"
                                    , Parser_binary, PREC_AND},
  [TOKEN_RETURN] = {
# 94 "src/parse.h" 3 4
                                ((void *)0)
# 94 "src/parse.h"
                                    , 
# 94 "src/parse.h" 3 4
                                                       ((void *)0)
# 94 "src/parse.h"
                                                           , PREC_NONE},
  [TOKEN_TRUE] = {
# 95 "src/parse.h" 3 4
                                ((void *)0)
# 95 "src/parse.h"
                                    , 
# 95 "src/parse.h" 3 4
                                                       ((void *)0)
# 95 "src/parse.h"
                                                           , PREC_NONE},
  [TOKEN_WHILE] = {
# 96 "src/parse.h" 3 4
                                ((void *)0)
# 96 "src/parse.h"
                                    , 
# 96 "src/parse.h" 3 4
                                                       ((void *)0)
# 96 "src/parse.h"
                                                           , PREC_NONE},
  [TOKEN_ERROR] = {
# 97 "src/parse.h" 3 4
                                ((void *)0)
# 97 "src/parse.h"
                                    , 
# 97 "src/parse.h" 3 4
                                                       ((void *)0)
# 97 "src/parse.h"
                                                           , PREC_NONE},
  [TOKEN_EOF] = {
# 98 "src/parse.h" 3 4
                                ((void *)0)
# 98 "src/parse.h"
                                    , 
# 98 "src/parse.h" 3 4
                                                       ((void *)0)
# 98 "src/parse.h"
                                                           , PREC_NONE},
};
# 49 "src/main.c" 2
# 1 "src/ir.h" 1




typedef enum
{
    IR_INS_MOV,
    IR_INS_PUSH,
    IR_INS_POP,
    IR_INS_JUMP,
    IR_INS_BINOP,
    IR_INS_RET,
    IR_INS_CALL,
    IR_INS_UNOP,
    IR_INS_COMPARE,
    IR_INS_COUNT
} IR_Instruction_Type;

typedef struct IR_Register_Table IR_Register_Table;
struct IR_Register_Table
{
    
# 22 "src/ir.h" 3 4
   _Bool 
# 22 "src/ir.h"
        *inuse_table;
    i32 capacity;
};

typedef enum
{
    SPECIAL_STACK_POINTER,
    SPECIAL_STACK_BASE,
    SPECIAL_INSTRUCTION_POINTER
} IR_Special_Register;





typedef struct IR_Register IR_Register;
struct IR_Register
{
    enum IR_Register_Type
    {
        IR_GPR,
        IR_SPECIAL
    } type;

    i32 gpr_index;
    IR_Special_Register special_register;
};

typedef struct IR_Mem IR_Mem;
struct IR_Mem
{
    enum IR_Mem_Type
    {
        IR_MEM_REGISTER,
        IR_MEM_OFFSET,
        IR_MEM_SCALED,
        IR_MEM_BASE_SCALED
    } type;

    union
    {
        IR_Register reg;
        struct
        {
            IR_Register reg;
            i32 offset;
        } offset;
        struct
        {
            IR_Register reg;
            IR_Register register_offset;
            i32 scale;
        } scaled;
    };
};

typedef struct IR_Location IR_Location;
struct IR_Location
{
    enum IR_Location_Type
    {
        IR_LOCATION_REGISTER,
        IR_LOCATION_MEMORY
    } type;

    union
    {
        IR_Register reg;
        IR_Mem mem;
    };
};

typedef struct IR_Data_Value IR_Data_Value;
struct IR_Data_Value
{
    enum
    {
        IR_DATA_STRING,
        IR_DATA_INT
    } type;

    union
    {
        String* string;
        i32 integer;
    };

    char name[32];
};

typedef struct
{
    IR_Data_Value* data;
    i32 count;
    i32 capacity;
} IR_Data_Array;

typedef struct IR_Variable IR_Variable;
struct IR_Variable
{
    char name[32];
};

typedef struct IR_Value IR_Value;
struct IR_Value
{
    enum Value_Type
    {
        VALUE_LOCATION,
        VALUE_INT,
        VALUE_VARIABLE
    } type;

    union
    {
        i32 integer;
        IR_Variable variable;
        IR_Location loc;
    };
};

typedef struct IR_Move IR_Move;
struct IR_Move
{
    IR_Value src;
    IR_Location dst;
};

typedef struct IR_Return IR_Return;
struct IR_Return
{
    IR_Register return_register;
    
# 154 "src/ir.h" 3 4
   _Bool 
# 154 "src/ir.h"
        has_return_value;
};

typedef struct IR_Call IR_Call;
struct IR_Call
{
    i32 function_index;
};

typedef struct IR_Label IR_Label;
struct IR_Label
{
    String* label_name;
};

typedef struct IR_Block_Address IR_Block_Address;
struct IR_Block_Address
{
    i32 address;
};

typedef enum
{
    JMP_ALWAYS,
    JMP_EQUAL,
    JMP_ZERO,
    JMP_NOT_EQUAL,
    JMP_NOT_ZERO,
    JMP_LESS,
    JMP_LESS_EQUAL,
    JMP_GREATER,
    JMP_GREATER_EQUAL
} IR_Jump_Type;

typedef struct IR_Jump IR_Jump;
struct IR_Jump
{
    IR_Jump_Type type;
    IR_Block_Address address;
};

typedef struct IR_Push IR_Push;
struct IR_Push
{
    IR_Value value;
};

typedef struct IR_Pop IR_Pop;
struct IR_Pop
{
    IR_Value value;
};

typedef enum
{
    OP_ADD,
    OP_SUB,
    OP_MUL,
    OP_DIV,
    OP_NOT,
    OP_EQUAL,
    OP_ASSIGN,
    OP_BIT_OR,
    OP_BIT_AND,
    OP_OR,
    OP_AND,
    OP_LESS,
    OP_GREATER,
    OP_LESS_EQUAL,
    OP_GREATER_EQUAL,
    OP_NOT_EQUAL
} IR_Op;

typedef struct IR_BinOp IR_BinOp;
struct IR_BinOp
{
    IR_Value left;
    IR_Value right;

    IR_Register destination;

    IR_Op operator;
};

typedef struct IR_Compare IR_Compare;
struct IR_Compare
{
    IR_Value left;
    IR_Location right;

    IR_Register destination;

    IR_Op operator;
};

typedef struct IR_UnOp IR_UnOp;
struct IR_UnOp
{
    IR_Value value;
    IR_Register destination;

    IR_Op operator;
};

typedef struct IR_Instruction IR_Instruction;
struct IR_Instruction
{
    IR_Instruction_Type type;
    union
    {
        IR_Move move;
        IR_Return ret;
        IR_Call call;
        IR_Jump jump;
        IR_Push push;
        IR_Pop pop;
        IR_BinOp binop;
        IR_UnOp unop;
        IR_Compare compare;
    };
};

typedef enum
{
    IR_NODE_INSTRUCTION,
    IR_NODE_LABEL,
    IR_NODE_FUNCTION_DECL,
} IR_Node_Type;

typedef struct IR_Function_Decl IR_Function_Decl;
struct IR_Function_Decl
{
    String* name;
    
# 287 "src/ir.h" 3 4
   _Bool 
# 287 "src/ir.h"
        export;
};

typedef struct IR_Node IR_Node;
struct IR_Node
{
    IR_Node_Type type;
    union
    {
        IR_Instruction instruction;
        IR_Label label;
        IR_Function_Decl function;
    };
};

typedef struct IR_Node_Array IR_Node_Array;
struct IR_Node_Array
{
    IR_Node* nodes;
    i32 count;
    i32 capacity;
};

typedef struct IR_Block IR_Block;
struct IR_Block
{
    IR_Block_Address block_address;

    IR_Block* previous;
    IR_Block* next;

    IR_Node_Array node_array;

    
# 320 "src/ir.h" 3 4
   _Bool 
# 320 "src/ir.h"
        has_label;

    struct IR_Program* parent_program;
};

typedef struct
{
    IR_Block* blocks;
    i32 count;
    i32 capacity;
} IR_Block_Array;

typedef struct IR_Function IR_Function;
struct IR_Function
{
    String_View name;
    
# 336 "src/ir.h" 3 4
   _Bool 
# 336 "src/ir.h"
        exported;
};

typedef struct IR_Function_Array IR_Function_Array;
struct IR_Function_Array
{
    IR_Function* functions;
    i32 count;
    i32 capacity;
};

typedef struct IR_Program IR_Program;
struct IR_Program
{
    IR_Data_Array data_array;
    IR_Block_Array block_array;
    IR_Function_Array function_array;

    i32 label_counter;
};

String* IR_pretty_print(IR_Program* program, Allocator* allocator);
void IR_pretty_print_register(String_Builder* sb, IR_Register* reg);
void IR_pretty_print_location(String_Builder* sb, IR_Location* location);
void IR_pretty_print_value(String_Builder* sb, IR_Value* value);
IR_Block* IR_get_current_block(IR_Program* program);
# 50 "src/main.c" 2
# 1 "src/codegen_x64.h" 1







typedef enum
{
    REG_AL, REG_AH, REG_AX, REG_EAX, REG_RAX,
    REG_BL, REG_BH, REG_BX, REG_EBX, REG_RBX,
    REG_CL, REG_CH, REG_CX, REG_ECX, REG_RCX,
    REG_DL, REG_DH, REG_DX, REG_EDX, REG_RDX,

    REG_SIL, REG_SI, REG_ESI, REG_RSI,
    REG_DIL, REG_DI, REG_EDI, REG_RDI,

    REG_SPL, REG_SP, REG_ESP, REG_RSP,

    REG_BPL, REG_BP, REG_EBP, REG_RBP,

    REG_R8B, REG_R8W, REG_R8D, REG_R8,
    REG_R9B, REG_R9W, REG_R9D, REG_R9,
    REG_R10B, REG_R10W, REG_R10D, REG_R10,
    REG_R11B, REG_R11W, REG_R11D, REG_R11,
    REG_R12B, REG_R12W, REG_R12D, REG_R12,
    REG_R13B, REG_R13W, REG_R13D, REG_R13,
    REG_R14B, REG_R14W, REG_R14D, REG_R14,
    REG_R15B, REG_R15W, REG_R15D, REG_R15,

    REG_COUNT
} Register;

typedef enum
{
    REG_SIZE_BYTE,
    REG_SIZE_WORD,
    REG_SIZE_LONG,
    REG_SIZE_QUAD,
    REG_SIZE_COUNT
} Reg_Size;
# 131 "src/codegen_x64.h"
const char* register_names[REG_COUNT] =
{
  [REG_AL] = "%al",
  [REG_AH] = "%ah",
  [REG_AX] = "%ax",
  [REG_EAX] = "%eax",
  [REG_RAX] = "%rax",

  [REG_BL] = "%bl",
  [REG_BH] = "%bh",
  [REG_BX] = "%bx",
  [REG_EBX] = "%ebx",
  [REG_RBX] = "%rbx",

  [REG_CL] = "%cl",
  [REG_CH] = "%ch",
  [REG_CX] = "%cx",
  [REG_ECX] = "%ecx",
  [REG_RCX] = "%rcx",

  [REG_DL] = "%dl",
  [REG_DH] = "%dh",
  [REG_DX] = "%dx",
  [REG_EDX] = "%edx",
  [REG_RDX] = "%rdx",

  [REG_SIL] = "%sil",
  [REG_SI] = "%si",
  [REG_ESI] = "%esi",
  [REG_RSI] = "%rsi",

  [REG_DIL] = "%dil",
  [REG_DI] = "%di",
  [REG_EDI] = "%edi",
  [REG_RDI] = "%rdi",

  [REG_SPL] = "%spl",
  [REG_SP] = "%sp",
  [REG_ESP] = "%esp",
  [REG_RSP] = "%rsp",

  [REG_BPL] = "%bpl",
  [REG_BP] = "%bp",
  [REG_EBP] = "%ebp",
  [REG_RBP] = "%rbp",

  [REG_R8B] = "%r8b",
  [REG_R8W] = "%r8w",
  [REG_R8D] = "%r8d",
  [REG_R8] = "%r8",

  [REG_R9B] = "%r9b",
  [REG_R9W] = "%r9w",
  [REG_R9D] = "%r9d",
  [REG_R9] = "%r9",

  [REG_R10B] = "%r10b",
  [REG_R10W] = "%r10w",
  [REG_R10D] = "%r10d",
  [REG_R10] = "%r10",

  [REG_R11B] = "%r11b",
  [REG_R11W] = "%r11w",
  [REG_R11D] = "%r11d",
  [REG_R11] = "%r11",

  [REG_R12B] = "%r12b",
  [REG_R12W] = "%r12w",
  [REG_R12D] = "%r12d",
  [REG_R12] = "%r12",

  [REG_R13B] = "%r13b",
  [REG_R13W] = "%r13w",
  [REG_R13D] = "%r13d",
  [REG_R13] = "%r13",

  [REG_R14B] = "%r14b",
  [REG_R14W] = "%r14w",
  [REG_R14D] = "%r14d",
  [REG_R14] = "%r14",

  [REG_R15B] = "%r15b",
  [REG_R15W] = "%r15w",
  [REG_R15D] = "%r15d",
  [REG_R15] = "%r15",
};


Reg_Size register_sizes[REG_COUNT] =
{
  [REG_AL] = REG_SIZE_BYTE,
  [REG_AH] = REG_SIZE_BYTE,
  [REG_AX] = REG_SIZE_WORD,
  [REG_EAX] = REG_SIZE_LONG,
  [REG_RAX] = REG_SIZE_QUAD,

  [REG_BL] = REG_SIZE_BYTE,
  [REG_BH] = REG_SIZE_BYTE,
  [REG_BX] = REG_SIZE_WORD,
  [REG_EBX] = REG_SIZE_LONG,
  [REG_RBX] = REG_SIZE_QUAD,

  [REG_CL] = REG_SIZE_BYTE,
  [REG_CH] = REG_SIZE_BYTE,
  [REG_CX] = REG_SIZE_WORD,
  [REG_ECX] = REG_SIZE_LONG,
  [REG_RCX] = REG_SIZE_QUAD,

  [REG_DL] = REG_SIZE_BYTE,
  [REG_DH] = REG_SIZE_BYTE,
  [REG_DX] = REG_SIZE_WORD,
  [REG_EDX] = REG_SIZE_LONG,
  [REG_RDX] = REG_SIZE_QUAD,

  [REG_SIL] = REG_SIZE_BYTE,
  [REG_SI] = REG_SIZE_WORD,
  [REG_ESI] = REG_SIZE_LONG,
  [REG_RSI] = REG_SIZE_QUAD,

  [REG_DIL] = REG_SIZE_BYTE,
  [REG_DI] = REG_SIZE_WORD,
  [REG_EDI] = REG_SIZE_LONG,
  [REG_RDI] = REG_SIZE_QUAD,

  [REG_SPL] = REG_SIZE_BYTE,
  [REG_SP] = REG_SIZE_WORD,
  [REG_ESP] = REG_SIZE_LONG,
  [REG_RSP] = REG_SIZE_QUAD,

  [REG_BPL] = REG_SIZE_BYTE,
  [REG_BP] = REG_SIZE_WORD,
  [REG_EBP] = REG_SIZE_LONG,
  [REG_RBP] = REG_SIZE_QUAD,

  [REG_R8B] = REG_SIZE_BYTE,
  [REG_R8W] = REG_SIZE_WORD,
  [REG_R8D] = REG_SIZE_LONG,
  [REG_R8] = REG_SIZE_QUAD,

  [REG_R9B] = REG_SIZE_BYTE,
  [REG_R9W] = REG_SIZE_WORD,
  [REG_R9D] = REG_SIZE_LONG,
  [REG_R9] = REG_SIZE_QUAD,

  [REG_R10B] = REG_SIZE_BYTE,
  [REG_R10W] = REG_SIZE_WORD,
  [REG_R10D] = REG_SIZE_LONG,
  [REG_R10] = REG_SIZE_QUAD,

  [REG_R11B] = REG_SIZE_BYTE,
  [REG_R11W] = REG_SIZE_WORD,
  [REG_R11D] = REG_SIZE_LONG,
  [REG_R11] = REG_SIZE_QUAD,

  [REG_R12B] = REG_SIZE_BYTE,
  [REG_R12W] = REG_SIZE_WORD,
  [REG_R12D] = REG_SIZE_LONG,
  [REG_R12] = REG_SIZE_QUAD,

  [REG_R13B] = REG_SIZE_BYTE,
  [REG_R13W] = REG_SIZE_WORD,
  [REG_R13D] = REG_SIZE_LONG,
  [REG_R13] = REG_SIZE_QUAD,

  [REG_R14B] = REG_SIZE_BYTE,
  [REG_R14W] = REG_SIZE_WORD,
  [REG_R14D] = REG_SIZE_LONG,
  [REG_R14] = REG_SIZE_QUAD,

  [REG_R15B] = REG_SIZE_BYTE,
  [REG_R15W] = REG_SIZE_WORD,
  [REG_R15D] = REG_SIZE_LONG,
  [REG_R15] = REG_SIZE_QUAD,
};

typedef enum
{
    SCRATCH_RBX,
    SCRATCH_R10,
    SCRATCH_R11,
    SCRATCH_R12,
    SCRATCH_R13,
    SCRATCH_R14,
    SCRATCH_R15,
    SCRATCH_COUNT
} Scratch_Register;

typedef enum
{
    LINUX_SC_EXIT = 60
} Linux_Syscall;

typedef struct X64_Memory X64_Memory;
struct X64_Memory
{
    enum X64_Memory_Type
    {
        MEM_TYPE_IMMEDIATE,
        MEM_TYPE_REGISTER,
        MEM_TYPE_OFFSET,
        MEM_TYPE_SCALED_INDEXED_BASE,
        MEM_TYPE_SCALED_INDEXED,
    } type;

    union
    {
        i32 immediate;
        Register reg;
        struct
        {
            Register reg;
            i32 offset;
        } offset;
        struct
        {
            Register base;
            Register offset_register;
            i32 scaled;
        } scaled_indexed;
    };
};

typedef struct X64_Location X64_Location;
struct X64_Location
{
    enum X64_Location_Type
    {
        LOC_REGISTER,
        LOC_MEMORY
    } type;

    union
    {
        Register reg;
        X64_Memory memory;
    };
};

typedef struct
{
    
# 371 "src/codegen_x64.h" 3 4
   _Bool 
# 371 "src/codegen_x64.h"
        inuse_table[SCRATCH_COUNT];
} Scratch_Register_Table;
# 393 "src/codegen_x64.h"
typedef struct Temp_Table_Entry Temp_Table_Entry;


typedef struct Temp_Table Temp_Table;
struct Temp_Table
{
    i32* keys;
    Scratch_Register* entries;
    i32 count;
    i32 capacity;
};




const char* scratch_name(Scratch_Register reg);

typedef enum
{
    INS_MOV,
    INS_PUSH,
    INS_POP,
    INS_ADD,
    INS_SUB,
    INS_MUL,
    INS_DIV,
    INS_CMP,
    INS_RET,
    INS_NEG,
    INS_CQO,
    INS_XOR,
    INS_CALL,
    INS_COUNT
} Instruction;

const char* instruction_names[INS_COUNT] =
{
    [INS_MOV ] = "mov",
    [INS_PUSH] = "push",
    [INS_POP] = "pop",
    [INS_ADD] = "add",
    [INS_SUB] = "sub",
    [INS_MUL] = "imul",
    [INS_DIV] = "idiv",
    [INS_CMP] = "cmp",
    [INS_RET] = "ret",
    [INS_NEG] = "neg",
    [INS_CQO] = "cqo",
    [INS_XOR] = "xor",
    [INS_CALL] = "call"
};
# 464 "src/codegen_x64.h"
void X64_emit_label(String_Builder* sb, const char* label);
void X64_emit_ret(String_Builder* sb);
void X64_emit_call(String_Builder* sb, const char* function);
void X64_emit_comment_line(String_Builder* sb, const char* comment);
void X64_emit_syscall(String_Builder* sb, Linux_Syscall syscall);
void X64_emit_exit_syscall(String_Builder* sb);
void X64_emit_start(String_Builder* sb);




void X64_emit_asciz(String_Builder* sb, const char* name, const char* value);




void X64_emit_pop_reg(String_Builder* sb, Register reg);
void X64_emit_push_reg(String_Builder* sb, Register reg);




void X64_emit_move_reg_to_reg(String_Builder* sb, Register src, Register dst);
void X64_emit_move_lit_to_reg(String_Builder* sb, i32 num, Register dst);
void X64_emit_move_loc_to_loc(String_Builder* sb, IR_Location src, IR_Location dst,
                              Scratch_Register_Table* table, Temp_Table* temp_table);
void X64_emit_move_reg_to_mem(String_Builder* sb, Register src, IR_Mem dst,
                              Scratch_Register_Table* table, Temp_Table* temp_table);
void X64_emit_move_mem_to_mem(String_Builder* sb, IR_Mem src, IR_Mem dst,
                              Scratch_Register_Table* table, Temp_Table* temp_table);
void X64_emit_move_mem_to_reg(String_Builder* sb, IR_Mem src, Register dst,
                              Scratch_Register_Table* table, Temp_Table* temp_table);




void X64_emit_cmp_lit_to_loc(String_Builder* sb, i32 lhs, IR_Location rhs,
                             Scratch_Register_Table* table, Temp_Table* temp_table);

void X64_emit_cmp_loc_to_loc(String_Builder* sb, IR_Location lhs, IR_Location rhs,
                             Scratch_Register_Table* table, Temp_Table* temp_table);

void X64_emit_cmp_reg_to_reg(String_Builder* sb, Register s_lhs, Register s_rhs, IR_Op operator);

void X64_emit_setcc(String_Builder* sb, IR_Op operator, Register result_reg);




void X64_emit_unary(String_Builder* sb, Register reg);
void X64_emit_div(String_Builder* sb, Register src, Register dst);
void X64_emit_mul(String_Builder* sb, Register src, Register dst);
void X64_emit_sub(String_Builder* sb, Register src, Register dst);
void X64_emit_add(String_Builder* sb, Register src, Register dst);

void X64_emit_xor_reg_to_reg(String_Builder* sb, Register lhs, Register rhs);




String* X64_codegen_ir(IR_Program* program_node, Allocator* allocator);
# 51 "src/main.c" 2
# 1 "src/compiler.h" 1





String* DEFAULT_EXECUTABLE_OUT_PATH = 
# 6 "src/compiler.h" 3 4
                                     ((void *)0)
# 6 "src/compiler.h"
                                         ;

typedef enum
{
    OPT_NONE = 0,
    OPT_ASSEMBLY_OUTPUT = 1 << 1,
    OPT_IR_OUTPUT = 1 << 2,
    OPT_TOK_OUTPUT = 1 << 3,
    OPT_AST_OUTPUT = 1 << 4
} Compiler_Options;

typedef struct Compiler_Arguments Compiler_Arguments;
struct Compiler_Arguments
{
    Compiler_Options options;
    String* input_file;
    String* out_path;
    String* absolute_path;
};
# 52 "src/main.c" 2
# 1 "src/runtime.h" 1
# 53 "src/main.c" 2

# 1 "src/common.c" 1
void output_error(Source_Location location, const char* type, char* format, va_list arglist)
{
    fprintf(
# 3 "src/common.c" 3 4
           stderr
# 3 "src/common.c"
                 , "\x1b[1;31m");
    fprintf(
# 4 "src/common.c" 3 4
           stderr
# 4 "src/common.c"
                 , "%s error in file %s at %d", type, location.file_name, location.line_number);
    vfprintf(
# 5 "src/common.c" 3 4
            stderr
# 5 "src/common.c"
                  , format, arglist);
    fprintf(
# 6 "src/common.c" 3 4
           stderr
# 6 "src/common.c"
                 , "\x1b[0m\n");

    exit(1);
}

void generic_error(Source_Location location, const char* format, ...)
{
    va_list arglist;
    
# 14 "src/common.c" 3 4
   __builtin_va_start(
# 14 "src/common.c"
   arglist
# 14 "src/common.c" 3 4
   ,
# 14 "src/common.c"
   format
# 14 "src/common.c" 3 4
   )
# 14 "src/common.c"
                            ;
    output_error(location, "Generic", format, arglist)

    exit(1);
}

void compiler_bug(Source_Location location, const char* format, ...)
{
    va_list arglist;
    
# 23 "src/common.c" 3 4
   __builtin_va_start(
# 23 "src/common.c"
   arglist
# 23 "src/common.c" 3 4
   ,
# 23 "src/common.c"
   format
# 23 "src/common.c" 3 4
   )
# 23 "src/common.c"
                            ;
    output_error(location, "Compiler bug", format, arglist)

    exit(1);
}

void not_implemented(Source_Location location, const char* format, ...)
{
    va_list arglist;
    
# 32 "src/common.c" 3 4
   __builtin_va_start(
# 32 "src/common.c"
   arglist
# 32 "src/common.c" 3 4
   ,
# 32 "src/common.c"
   format
# 32 "src/common.c" 3 4
   )
# 32 "src/common.c"
                            ;
    output_error(location, "Not implemented", format, arglist)

    exit(1);
}

Source_Location make_location(const char* file, i32 line)
{
    return (Source_Location)
        {
            .file_name = file,
            .line_number = line
        };
}
# 55 "src/main.c" 2
# 1 "src/lex.c" 1
void Lex_init(Lexer* lexer, String* source, String_View file_name, String_View absolute_path)
{
    lexer->start = source->str;
    lexer->current = source->str;
    lexer->line = 1;
    lexer->file_name = file_name;
    lexer->absolute_path = absolute_path;
    lexer->position_on_line = 0;
}

char* token_type_to_string(Token_Type token)
{
    switch(token)
    {
    case TOKEN_NUMBER: return "number";
    case TOKEN_PLUS: return "+";
    case TOKEN_MINUS: return "-";
    case TOKEN_STAR: return "*";
    case TOKEN_SLASH: return "/";
    case TOKEN_SEMICOLON: return ";";
    case TOKEN_COMMA: return ",";
    case TOKEN_ARROW: return "->";
    case TOKEN_BANG: return "!";
    case TOKEN_BANG_EQUAL: return "!=";
    case TOKEN_LESS: return "<";
    case TOKEN_GREATER: return ">";
    case TOKEN_LESS_EQUAL: return "<=";
    case TOKEN_GREATER_EQUAL: return ">=";
    case TOKEN_PIPE: return "|";
    case TOKEN_PIPE_PIPE: return "||";
    case TOKEN_AMPERSAND: return "&";
    case TOKEN_AMPERSAND_AMPERSAND: return "&&";
    case TOKEN_LEFT_PAREN: return "(";
    case TOKEN_RIGHT_PAREN: return ")";
    case TOKEN_LEFT_BRACE: return "{";
    case TOKEN_RIGHT_BRACE: return "}";
    case TOKEN_COLON: return ":";
    case TOKEN_COLON_COLON: return "::";
    case TOKEN_COLON_EQUAL: return ":=";
    case TOKEN_EQUAL: return "=";
    case TOKEN_EQUAL_EQUAL: return "==";
    case TOKEN_IF: return "if";
    case TOKEN_ELSE: return "else";
    case TOKEN_WHILE: return "while";
    case TOKEN_RETURN: return "return";
    case TOKEN_FALSE: return "false";
    case TOKEN_TRUE: return "true";
    case TOKEN_FOR: return "for";
    case TOKEN_IDENTIFIER: return "identifier";
    case TOKEN_STRING: return "string";
    case TOKEN_EOF: return "eof";
    case TOKEN_ERROR: return "error";
    }
    return 
# 54 "src/lex.c" 3 4
          ((void *)0)
# 54 "src/lex.c"
              ;
}

static 
# 57 "src/lex.c" 3 4
      _Bool 
# 57 "src/lex.c"
           is_digit(char c)
{
    return c >= '0' && c <= '9';
}

static 
# 62 "src/lex.c" 3 4
      _Bool 
# 62 "src/lex.c"
           is_alpha(char c)
{
    return (c >= 'a' && c <= 'z') ||
        (c >= 'A' && c <= 'Z') ||
        c == '_';
}

static 
# 69 "src/lex.c" 3 4
      _Bool 
# 69 "src/lex.c"
           Lex_is_at_end(Lexer* lexer)
{
    return *lexer->current == '\0';
}

static char Lex_advance(Lexer* lexer)
{
    lexer->current++;
    return lexer->current[-1];
}

static char Lex_peek_char(Lexer* lexer)
{
    return *lexer->current;
}


__attribute__((unused))

static char Lex_peek_next_char(Lexer* lexer)
{
    if (Lex_is_at_end(lexer)) return '\0';
    return lexer->current[1];
}


__attribute__((unused))

static 
# 97 "src/lex.c" 3 4
      _Bool 
# 97 "src/lex.c"
           Lex_match_character(Lexer* lexer, char expected)
{
    if (Lex_is_at_end(lexer)) return 
# 99 "src/lex.c" 3 4
                                    0
# 99 "src/lex.c"
                                         ;
    if (*lexer->current != expected) return 
# 100 "src/lex.c" 3 4
                                           0
# 100 "src/lex.c"
                                                ;

    lexer->current++;
    return 
# 103 "src/lex.c" 3 4
          1
# 103 "src/lex.c"
              ;
}

static Token Lex_make_token(Lexer* lexer, Token_Type type)
{
    i32 length = (i32)(lexer->current - lexer->start);
    Token token =
        {
            .type = type,
            .start = lexer->start,
            .line = lexer->line,
            .length = length,
            .position = lexer->position_on_line
        };
    lexer->position_on_line += length;
    return token;
}

static void Lex_verror_at(Lexer* lexer, char* location, char* fmt, va_list ap)
{
    (void)location;
    fprintf(
# 124 "src/lex.c" 3 4
           stderr
# 124 "src/lex.c"
                 , "\x1b[1;37m");
    i32 length = fprintf(
# 125 "src/lex.c" 3 4
                        stderr
# 125 "src/lex.c"
                              , sv_null_terminated_string(lexer->absolute_path));
    length += fprintf(
# 126 "src/lex.c" 3 4
                     stderr
# 126 "src/lex.c"
                           , ":%d:%d:\x1b[31m error: ", lexer->line, lexer->position_on_line);
    length++;

    fprintf(
# 129 "src/lex.c" 3 4
           stderr
# 129 "src/lex.c"
                 , "\x1b[0m");

    fprintf(
# 131 "src/lex.c" 3 4
           stderr
# 131 "src/lex.c"
                 , "\x1b[1;37m");
    fprintf(
# 132 "src/lex.c" 3 4
           stderr
# 132 "src/lex.c"
                 , "'%s' ", lexer->start);
    fprintf(
# 133 "src/lex.c" 3 4
           stderr
# 133 "src/lex.c"
                 , "\x1b[0m");
    vfprintf(
# 134 "src/lex.c" 3 4
            stderr
# 134 "src/lex.c"
                  , fmt, ap);
    fprintf(
# 135 "src/lex.c" 3 4
           stderr
# 135 "src/lex.c"
                 , "\n");



}

static void Lex_error_tokenf(Lexer* lexer, Token* token, char* fmt, ...)
{
    va_list(ap);
    
# 144 "src/lex.c" 3 4
   __builtin_va_start(
# 144 "src/lex.c"
   ap
# 144 "src/lex.c" 3 4
   ,
# 144 "src/lex.c"
   fmt
# 144 "src/lex.c" 3 4
   )
# 144 "src/lex.c"
                    ;
    Lex_verror_at(lexer, token->start, fmt, ap);

    
# 147 "src/lex.c" 3 4
   __builtin_va_end(
# 147 "src/lex.c"
   ap
# 147 "src/lex.c" 3 4
   )
# 147 "src/lex.c"
             ;
}

static Token Lex_error_token(Lexer* lexer, char* message)
{
    Token token =
        {
            .type = TOKEN_ERROR,
            .start = lexer->current,
            .length = (i32)strlen(message),
            .line = lexer->line,
            .position = lexer->position_on_line
        };

    Lex_error_tokenf(lexer, &token, message);

    return token;
}

static Token Lex_string(Lexer* lexer)
{
    while (Lex_peek_char(lexer) != '"' && !Lex_is_at_end(lexer))
    {
        if (Lex_peek_char(lexer) == '\n') lexer->line++;
        Lex_advance(lexer);
    }

    if (Lex_is_at_end(lexer)) return Lex_error_token(lexer, "Unterminated string.");
    Lex_advance(lexer);
    return Lex_make_token(lexer, TOKEN_STRING);
}

static void Lex_skip_whitespace(Lexer* lexer)
{
    for (;;)
    {
        char c = Lex_peek_char(lexer);
        switch(c)
        {
        case ' ':
        case '\r':
        case '\t':
        {
            Lex_advance(lexer);
        }
        break;
        case '\n':
        {
            Lex_advance(lexer);
            lexer->line++;
            lexer->position_on_line = 0;
        }
        break;
        case '/':
        {
            char next = Lex_peek_next_char(lexer);
            if (next == '/')
            {
                while (Lex_peek_char(lexer) != '\n' && !Lex_is_at_end(lexer)) Lex_advance(lexer);
            }
            else
            {
                return;
            }
        }
        break;
        default:
        {
            return;
        }
        }
    }
}

static Token_Type Lex_check_keyword(Lexer* lexer, i32 start, i32 length, const char* rest, Token_Type type) {
  if (lexer->current - lexer->start == start + length &&
      memcmp(lexer->start + start, rest, length) == 0) {
    return type;
  }

  return TOKEN_IDENTIFIER;
}

static Token_Type Lex_identifier_type(Lexer* lexer)
{
    switch (lexer->start[0]) {
    case 'i': return Lex_check_keyword(lexer, 1, 1, "f", TOKEN_IF);
    case 'e': return Lex_check_keyword(lexer, 1, 3, "lse", TOKEN_ELSE);
    case 'r': return Lex_check_keyword(lexer, 1, 5, "eturn", TOKEN_RETURN);
    case 'w': return Lex_check_keyword(lexer, 1, 4, "hile", TOKEN_WHILE);
    case 't': return Lex_check_keyword(lexer, 1, 3, "rue", TOKEN_TRUE);
    case 'f':
    {
        if (lexer->current - lexer->start > 1)
        {
            switch (lexer->start[1])
            {
            case 'a': return Lex_check_keyword(lexer, 2, 3, "lse", TOKEN_FALSE);
            case 'o': return Lex_check_keyword(lexer, 2, 2, "or", TOKEN_FOR);
            }
        }
    }

    }
    return TOKEN_IDENTIFIER;
}

static Token Lex_identifier(Lexer* lexer)
{
    while (is_alpha(Lex_peek_char(lexer)) || is_digit(Lex_peek_char(lexer))) Lex_advance(lexer);
    return Lex_make_token(lexer, Lex_identifier_type(lexer));
}

static Token Lex_number(Lexer* lexer)
{
    while (is_digit(Lex_peek_char(lexer))) Lex_advance(lexer);

    if (Lex_peek_char(lexer) == '.' && is_digit(Lex_peek_char(lexer)))
    {
        Lex_advance(lexer);
        while (is_digit(Lex_peek_char(lexer))) Lex_advance(lexer);
    }

    return Lex_make_token(lexer, TOKEN_NUMBER);
}

Token Lex_scan_token(Lexer* lexer)
{
    Lex_skip_whitespace(lexer);
    lexer->start = lexer->current;

    if (Lex_is_at_end(lexer)) return Lex_make_token(lexer, TOKEN_EOF);

    char c = Lex_advance(lexer);

    if (is_alpha(c)) return Lex_identifier(lexer);
    if (is_digit(c)) return Lex_number(lexer);

    switch(c)
    {
    case '+': return Lex_make_token(lexer, TOKEN_PLUS);
    case '-':
    {
        if (Lex_match_character(lexer, '>')) return Lex_make_token(lexer, TOKEN_ARROW);
        return Lex_make_token(lexer, TOKEN_MINUS);
    }
    case '*': return Lex_make_token(lexer, TOKEN_STAR);
    case '/': return Lex_make_token(lexer, TOKEN_SLASH);
    case '|':
    {
        if (Lex_match_character(lexer, '|')) return Lex_make_token(lexer, TOKEN_PIPE_PIPE);
        return Lex_make_token(lexer, TOKEN_PIPE);
    }
    case '&':
    {
        if (Lex_match_character(lexer, '&')) return Lex_make_token(lexer, TOKEN_AMPERSAND_AMPERSAND);
        return Lex_make_token(lexer, TOKEN_AMPERSAND);
    }

    case '!':
    {
        if (Lex_match_character(lexer, '=')) return Lex_make_token(lexer, TOKEN_BANG_EQUAL);
        return Lex_make_token(lexer, TOKEN_BANG);
    }
    case '=':
    {
        if (Lex_match_character(lexer, '=')) return Lex_make_token(lexer, TOKEN_EQUAL_EQUAL);
        return Lex_make_token(lexer, TOKEN_EQUAL);
    }
    case '<':
    {
        if (Lex_match_character(lexer, '=')) return Lex_make_token(lexer, TOKEN_LESS_EQUAL);
        return Lex_make_token(lexer, TOKEN_LESS);
    }
    case '>':
    {
        if (Lex_match_character(lexer, '=')) return Lex_make_token(lexer, TOKEN_GREATER_EQUAL);
        return Lex_make_token(lexer, TOKEN_GREATER_EQUAL);
    }

    case '(': return Lex_make_token(lexer, TOKEN_LEFT_PAREN);
    case ')': return Lex_make_token(lexer, TOKEN_RIGHT_PAREN);
    case '{': return Lex_make_token(lexer, TOKEN_LEFT_BRACE);
    case '}': return Lex_make_token(lexer, TOKEN_RIGHT_BRACE);
    case ':':
    {
        if (Lex_match_character(lexer, ':')) return Lex_make_token(lexer, TOKEN_COLON_COLON);
        if (Lex_match_character(lexer, '=')) return Lex_make_token(lexer, TOKEN_COLON_EQUAL);
        return Lex_make_token(lexer, TOKEN_COLON);
    }
    case ';': return Lex_make_token(lexer, TOKEN_SEMICOLON);
    case '"': return Lex_string(lexer);
    case ',': return Lex_make_token(lexer, TOKEN_COMMA);
    }

    return Lex_error_token(lexer, "unexpected token");
}

void token_list_init(Token_List* list, i32 initial_capacity)
{
    list->capacity = initial_capacity;
    list->tokens = malloc(sizeof(Token) * initial_capacity);
    list->count = 0;
}

void token_list_free(Token_List* list)
{
    free(list->tokens);
    free(list);
}

void token_list_maybe_expand(Token_List* list)
{
    if (list->count + 1 >= list->capacity)
    {
        list->capacity *= 2;
        list->tokens = realloc(list->tokens, list->capacity);
    }
}

void token_list_add(Token_List* list, Token token)
{
    token_list_maybe_expand(list);
    list->tokens[list->count++] = token;
}

Token_List* Lex_tokenize(String* input, String* file_name, String* absolute_path)
{
    Token_List* list = malloc(sizeof(Token_List));
    token_list_init(list, 128);

    Lexer lexer;
    Lex_init(&lexer, input, sv_create(file_name), sv_create(absolute_path));

    Token token = Lex_scan_token(&lexer);

    while (token.type != TOKEN_EOF)
    {
        token_list_add(list, token);
        token = Lex_scan_token(&lexer);
    }

    token_list_add(list, token);

    return list;
}

String* Lex_pretty_print(Token_List* list, Allocator* allocator)
{
    String_Builder sb;
    sb_init(&sb, 256);

    for (i32 i = 0; i < list->count; i++)
    {
        Token token = list->tokens[i];

        switch (token.type)
        {
        case TOKEN_NUMBER:
        {
            i32 value = strtol(token.start, 
# 407 "src/lex.c" 3 4
                                           ((void *)0)
# 407 "src/lex.c"
                                               , 10);
            sb_appendf(&sb, "NUMBER('%d')\n", value);
        }
        break;
        case TOKEN_PLUS:
        {
            sb_append(&sb, "PLUS('+')\n");
        }
        break;
        case TOKEN_MINUS:
        {
            sb_append(&sb, "MINUS('-')\n");
        }
        break;
        case TOKEN_STAR:
        {
            sb_append(&sb, "STAR('*')\n");
        }
        break;
        case TOKEN_SLASH:
        {
            sb_append(&sb, "SLASH('/')\n");
        }
        break;
        case TOKEN_ARROW:
        {
            sb_append(&sb, "ARROW('->')\n");
        }
        break;
        case TOKEN_PIPE:
        {
            sb_append(&sb, "PIPE('|')\n");
        }
        break;
        case TOKEN_PIPE_PIPE:
        {
            sb_append(&sb, "PIPE_PIPE('||')\n");
        }
        break;
        case TOKEN_AMPERSAND:
        {
            sb_append(&sb, "AMPERSAND('&')\n");
        }
        break;
        case TOKEN_AMPERSAND_AMPERSAND:
        {
            sb_append(&sb, "AMPERSAND_AMPERSAND('&&')\n");
        }
        break;
        case TOKEN_SEMICOLON:
        {
            sb_append(&sb, "SEMICOLON(';')\n");
        }
        break;
        case TOKEN_COMMA:
        {
            sb_append(&sb, "COMMA(',')\n");
        }
        break;
        case TOKEN_BANG:
        {
            sb_append(&sb, "BANG('!')\n");
        }
        break;
        case TOKEN_BANG_EQUAL:
        {
            sb_append(&sb, "BANG_EQUAL('!=')\n");
        }
        break;
        case TOKEN_LESS:
        {
            sb_append(&sb, "LESS('<')\n");
        }
        break;
        case TOKEN_LESS_EQUAL:
        {
            sb_append(&sb, "LESS_EQUAL('<=')\n");
        }
        break;
        case TOKEN_GREATER:
        {
            sb_append(&sb, "GREATER('>')\n");
        }
        break;
        case TOKEN_GREATER_EQUAL:
        {
            sb_append(&sb, "LESS_EQUAL('>=')\n");
        }
        break;
        case TOKEN_LEFT_PAREN:
        {
            sb_append(&sb, "LPAREN('(')\n");
        }
        break;
        case TOKEN_RIGHT_PAREN:
        {
            sb_append(&sb, "RPAREN(')')\n");
        }
        break;
        case TOKEN_LEFT_BRACE:
        {
            sb_append(&sb, "LBRACE('{')\n");
        }
        break;
        case TOKEN_RIGHT_BRACE:
        {
            sb_append(&sb, "RBRACE('}')\n");
        }
        break;
        case TOKEN_EQUAL:
        {
            sb_append(&sb, "EQUAL('=')\n");
        }
        break;
        case TOKEN_EQUAL_EQUAL:
        {
            sb_append(&sb, "EQUAL_EQUAL('==')\n");
        }
        break;
        case TOKEN_COLON:
        {
            sb_append(&sb, "COLON('::')\n");
        }
        break;
        case TOKEN_COLON_COLON:
        {
            sb_append(&sb, "COLON_COLON('::')\n");
        }
        break;
        case TOKEN_COLON_EQUAL:
        {
            sb_append(&sb, "COLON_EQUAL(':=')\n");
        }
        break;
        case TOKEN_IF:
        {
            sb_append(&sb, "IF('if')\n");
        }
        break;
        case TOKEN_ELSE:
        {
            sb_append(&sb, "ELSE('else')\n");
        }
        break;
        case TOKEN_WHILE:
        {
            sb_append(&sb, "WHILE('while')\n");
        }
        break;
        case TOKEN_RETURN:
        {
            sb_append(&sb, "RETURN('return')\n");
        }
        break;
        case TOKEN_FALSE:
        {
            sb_append(&sb, "FALSE('false')\n");
        }
        break;
        case TOKEN_TRUE:
        {
            sb_append(&sb, "TRUE('true')\n");
        }
        break;
        case TOKEN_FOR:
        {
            sb_append(&sb, "FOR('for')\n");
        }
        break;
        case TOKEN_IDENTIFIER:
        {
            sb_appendf(&sb, "IDENT('%.*s')\n", token.length, token.start);
        }
        break;
        case TOKEN_STRING:
        {
            sb_appendf(&sb, "STRING('%.*s')\n", token.length, token.start);
        }
        break;
        case TOKEN_EOF:
        {
            sb_append(&sb, "EOF\n");
        }
        break;
        case TOKEN_ERROR: break;
        }
    }

    return sb_get_result(&sb, allocator);
}
# 56 "src/main.c" 2
# 1 "src/ast.c" 1
void AST_node_list_add(AST_Node_List* list, AST_Node* node)
{
    if (list->count + 1 > list->capacity)
    {
        list->capacity = list->capacity == 0 ? 2 : list->capacity * 2;
        list->nodes = realloc(list->nodes, list->capacity * sizeof(AST_Node*));
    }
    list->nodes[list->count++] = node;
}

static char* AST_type_string(AST_Node_Type type)
{
    switch(type)
    {
    case AST_NODE_STATEMENT:
    return "AST statement";
    case AST_NODE_PROGRAM:
    return "AST program";
    case AST_NODE_FUN_DECL:
    return "AST function declaration";
    case AST_NODE_ARGUMENT_LIST:
    return "AST argument list";
    case AST_NODE_FUNCTION_ARGUMENT:
    return "AST function argument";
    case AST_NODE_VARIABLE:
    return "AST variable";
    case AST_NODE_CALL:
    return "AST call";
    case AST_NODE_RETURN:
    return "AST return";
    case AST_NODE_IF:
    return "AST if";
    case AST_NODE_BLOCK:
    return "AST block";
    case AST_NODE_LITERAL:
    return "AST literal";
    case AST_NODE_STRING:
    return "AST string";
    case AST_NODE_BINARY:
    return "AST binary";
    case AST_NODE_UNARY:
    return "AST unary";
    case AST_NODE_TYPE_SPECIFIER:
    return "AST type specifier";
    case AST_NODE_ERROR:
    return "AST error";
    }
    return "";
}

static void pretty_print_operator(Token_Type operator, String_Builder* builder)
{


    switch (operator)
    {
    case TOKEN_PLUS: sb_append(builder, "+"); break;
    case TOKEN_MINUS: sb_append(builder, "-"); break;
    case TOKEN_STAR: sb_append(builder, "*"); break;
    case TOKEN_SLASH: sb_append(builder, "/"); break;
    case TOKEN_EQUAL_EQUAL: sb_append(builder, "=="); break;
    case TOKEN_EQUAL: sb_append(builder, "="); break;
    case TOKEN_BANG_EQUAL: sb_append(builder, "!="); break;
    case TOKEN_PIPE: sb_append(builder, "|"); break;
    case TOKEN_PIPE_PIPE: sb_append(builder, "||"); break;
    case TOKEN_AMPERSAND: sb_append(builder, "&"); break;
    case TOKEN_AMPERSAND_AMPERSAND: sb_append(builder, "&&"); break;
    case TOKEN_LESS: sb_append(builder, "<"); break;
    case TOKEN_LESS_EQUAL: sb_append(builder, "<="); break;
    case TOKEN_GREATER: sb_append(builder, ">"); break;
    case TOKEN_GREATER_EQUAL: sb_append(builder, ">="); break;
    case TOKEN_ERROR: sb_append(builder, "ERROR"); break;
    default: compiler_bug("AST pretty printer: Unknown operator: %s", token_type_to_string(operator));
    }
}

static void pretty_print_unary(AST_Node* node, i32 indentation, String_Builder* builder)
{

    sb_indent(builder, indentation);

    sb_append(builder, "(");
    pretty_print_operator(node->unary.operator, builder);

    pretty_print_expression(node->unary.expression, indentation, builder);
    sb_append(builder, ")");
}

static void pretty_print_binary(AST_Node* binary, i32 indentation, String_Builder* builder)
{


    sb_indent(builder, indentation);
    sb_append(builder, "(");
    pretty_print_operator(binary->binary.operator, builder);
    sb_append(builder, " ");

    pretty_print_expression(binary->binary.left, 0, builder);

    sb_append(builder, " ");

    pretty_print_expression(binary->binary.right, 0, builder);
    sb_append(builder, ")");
}

static void pretty_print_literal(AST_Node* node, i32 indentation, String_Builder* builder)
{
    switch(node->literal.type)
    {
    case LIT_INT:
    {
        sb_appendf(builder, "%d", node->literal.i);
    }
    break;
    case LIT_FLOAT:
    {
        sb_appendf(builder, "%f", node->literal.f);
    }
    break;
    case LIT_STRING:
    {
        sb_appendf(builder, "%s", node->literal.s);
    }
    break;
    }
}

static void pretty_print_string(AST_Node* string, i32 indentation, String_Builder* builder)
{
    sb_appendf(builder, "%.*s", string->string->length, string->string->str);
}

static void pretty_print_call(AST_Node* call, i32 indentation, String_Builder* builder)
{
    sb_indent(builder, indentation);
    sb_appendf(builder, "(call %s ", call->fun_call.name->str);

    AST_Node_List* arguments = &call->fun_call.arguments;
    for (i32 i = 0; i < arguments->count; i++)
    {
        AST_Node* argument = arguments->nodes[i];
        pretty_print_expression(argument, 0, builder);

        if (i == arguments->count - 1)
        {
            break;
        }
        sb_append(builder, " ");
    }
    sb_append(builder, ")");
}

static void pretty_print_expression(AST_Node* node, i32 indentation, String_Builder* builder)
{
    switch(node->type)
    {
    case AST_NODE_UNARY:
    {
        pretty_print_unary(node, 0, builder);
    }
    break;
    case AST_NODE_BINARY:
    {
        pretty_print_binary(node, 0, builder);
    }
    break;
    case AST_NODE_LITERAL:
    {
        pretty_print_literal(node, 0, builder);
    }
    break;
    case AST_NODE_STRING:
    {
        pretty_print_string(node, 0, builder);
    }
    break;
    case AST_NODE_VARIABLE:
    {
        sb_appendf(builder, "%s", node->variable.variable_name->str);
    }
    break;
    case AST_NODE_CALL:
    {
        pretty_print_call(node, 0, builder);
    }
    break;
    default:
    {
        compiler_bug("AST pretty printer: Unsupported node type %s\n", AST_type_string(node->type));
        
# 190 "src/ast.c" 3 4
       ((void) sizeof ((0) ? 1 : 0), __extension__ ({ if (0) ; else __assert_fail (
# 190 "src/ast.c"
       "false"
# 190 "src/ast.c" 3 4
       , "src/ast.c", 190, __extension__ __PRETTY_FUNCTION__); }))
# 190 "src/ast.c"
                    ;
    }
    break;
    }
}

static void pretty_print_statement(AST_Node* statement, i32 indentation, String_Builder* builder)
{
    switch(statement->type)
    {
    case AST_NODE_RETURN:
    {
        sb_indent(builder, indentation);
        sb_append(builder, "(return");
        if (statement->return_statement.expression)
        {
            sb_append(builder, "\n");
            sb_indent(builder, indentation + 1);
            pretty_print_expression(statement->return_statement.expression, indentation, builder);
        }
        sb_append(builder, ")");
    }
    break;
    case AST_NODE_IF:
    {
        sb_indent(builder, indentation);
        sb_append(builder, "(if ");
        pretty_print_expression(statement->if_statement.condition, indentation, builder);
        sb_append(builder, " \n");
        pretty_print_block(statement->if_statement.then_arm, indentation, builder);
        sb_append(builder, "\n");

        if (statement->if_statement.else_arm)
        {
            sb_indent(builder, indentation);
            sb_append(builder, "(else \n");
            pretty_print_statement(statement->if_statement.else_arm, indentation + 1, builder);
            sb_append(builder, ")");
        }

        sb_append(builder, ")");
    }
    break;
    case AST_NODE_CALL:
    {
        pretty_print_call(statement, indentation, builder);
    }
    break;
    case AST_NODE_BLOCK:
    {
        pretty_print_block(statement, indentation, builder);
    }
    break;
    default: compiler_bug("Not a valid statement type %s.", AST_type_string(statement->type)); break;
    }
}

static void pretty_print_block(AST_Node* block, i32 indentation, String_Builder* builder)
{
    AST_Node_List* list = &block->block.declarations;
    for (i32 i = 0; i < list->count; i++)
    {
        AST_Node* node = list->nodes[i];
        pretty_print_statement(node, indentation + 1, builder);
    }
}

static void pretty_print_type_spec(AST_Node* type_spec, i32 indentation, String_Builder* builder)
{
    Type_Specifier spec = type_spec->type_specifier.type;
    switch(spec)
    {
    case TYPE_SPEC_INT:
    {
        sb_append(builder, "int");
    }
    break;
    case TYPE_SPEC_UNIT:
    {
        sb_append(builder, "unit");
    }
    break;
    case TYPE_SPEC_INVALID:
    {
        sb_append(builder, "invalid");
    }
    break;
    }
}

static void pretty_print_declaration(AST_Node* declaration, i32 indentation, String_Builder* builder)
{
    switch(declaration->type)
    {
    case AST_NODE_FUN_DECL:
    {
        sb_indent(builder, indentation);
        sb_appendf(builder, "(fun %s ", declaration->fun_decl.name->str);

        sb_append(builder, "[");

        AST_Node_List* argument_list = &declaration->fun_decl.arguments;
        for (i32 i = 0; i < argument_list->count; i++)
        {
            AST_Node* argument = argument_list->nodes[i];
            sb_appendf(builder, "%s : ", argument->fun_argument.name->str);
            pretty_print_type_spec(argument->fun_argument.type, indentation, builder);

            if (i < argument_list->count - 1)
            {
                sb_append(builder, ", ");
            }
        }

        sb_append(builder, "]");


        sb_append(builder, " -> ");

        if (declaration->fun_decl.return_type)
        {
            pretty_print_type_spec(declaration->fun_decl.return_type, indentation, builder);
        }
        else
        {
            sb_append(builder, "()");
        }

        AST_Node_List block = declaration->fun_decl.body->block.declarations;

        if (block.count > 0)
        {
            sb_append(builder, "\n");
        }

        pretty_print_block(declaration->fun_decl.body, indentation, builder);

        sb_append(builder, ")");
    }
    break;
    default: 
# 330 "src/ast.c" 3 4
            ((void) sizeof ((0 
# 330 "src/ast.c"
            && "Not a declaration."
# 330 "src/ast.c" 3 4
            ) ? 1 : 0), __extension__ ({ if (0 
# 330 "src/ast.c"
            && "Not a declaration."
# 330 "src/ast.c" 3 4
            ) ; else __assert_fail (
# 330 "src/ast.c"
            "false && \"Not a declaration.\""
# 330 "src/ast.c" 3 4
            , "src/ast.c", 330, __extension__ __PRETTY_FUNCTION__); }))
# 330 "src/ast.c"
                                                 ; break;
    }
}

static void pretty_print_program(AST_Node* program_node, i32 indentation, String_Builder* builder)
{
    sb_append(builder, "(");
    sb_append(builder, "program\t\n");
    indentation++;

    AST_Node_List list = program_node->program.declarations;

    for (i32 i = 0; i < list.count; i++)
    {
        AST_Node* declaration = list.nodes[i];
        pretty_print_declaration(declaration, indentation, builder);

        if (i < list.count - 1)
        {
            sb_append(builder, "\n");
        }
    }


    sb_append(builder, ")");
}

static String* pretty_print_ast(AST_Node* root, Allocator* allocator)
{
    
# 359 "src/ast.c" 3 4
   ((void) sizeof ((
# 359 "src/ast.c"
   root->type == AST_NODE_PROGRAM
# 359 "src/ast.c" 3 4
   ) ? 1 : 0), __extension__ ({ if (
# 359 "src/ast.c"
   root->type == AST_NODE_PROGRAM
# 359 "src/ast.c" 3 4
   ) ; else __assert_fail (
# 359 "src/ast.c"
   "root->type == AST_NODE_PROGRAM"
# 359 "src/ast.c" 3 4
   , "src/ast.c", 359, __extension__ __PRETTY_FUNCTION__); }))
# 359 "src/ast.c"
                                         ;
    String_Builder builder;
    sb_init(&builder, 256);
    pretty_print_program(root, 0, &builder);
    sb_append(&builder, "\n");

    return sb_get_result(&builder, allocator);
}
# 57 "src/main.c" 2
# 1 "src/parse.c" 1

static void Parser_error_at(Parser* parser, Token* token, const char* message)
{
    if (parser->panic_mode) return;
    parser->panic_mode = 
# 5 "src/parse.c" 3 4
                        1
# 5 "src/parse.c"
                            ;

    fprintf(
# 7 "src/parse.c" 3 4
           stderr
# 7 "src/parse.c"
                 , "\x1b[1;37m");
    fprintf(
# 8 "src/parse.c" 3 4
           stderr
# 8 "src/parse.c"
                 , sv_null_terminated_string(parser->absolute_path));
    fprintf(
# 9 "src/parse.c" 3 4
           stderr
# 9 "src/parse.c"
                 , ":%d:%d:\x1b[31m error: ", token->line, token->position);

    fprintf(
# 11 "src/parse.c" 3 4
           stderr
# 11 "src/parse.c"
                 , "\x1b[0m");

    fprintf(
# 13 "src/parse.c" 3 4
           stderr
# 13 "src/parse.c"
                 , "%s\n", message);
    parser->had_error = 
# 14 "src/parse.c" 3 4
                       1
# 14 "src/parse.c"
                           ;
}

void Parser_error(Parser* parser, const char* message)
{
    Parser_error_at(parser, &parser->previous, message);
}

void Parser_error_at_current(Parser* parser, const char* message)
{
    Parser_error_at(parser, &parser->current, message);
}

void Parser_advance(Parser* parser)
{
    parser->previous = parser->current;

    for (;;)
    {
        parser->current = parser->token_stream->tokens[parser->current_token++];
        if (parser->current.type != TOKEN_ERROR) break;

        char err[32];
        sprintf(err, "unknown token \x1b[1;37m'%s'\x1b[0m", parser->current.start);
        Parser_error_at(parser, &parser->current, err);
    }
}

void Parser_init(Parser* parser, String* absolute_path, Token_List* tokens, Allocator* allocator)
{
    parser->current = tokens->tokens[0];
    parser->token_stream = tokens;
    parser->current_token = 0;
    parser->had_error = 
# 47 "src/parse.c" 3 4
                       0
# 47 "src/parse.c"
                            ;
    parser->panic_mode = 
# 48 "src/parse.c" 3 4
                        0
# 48 "src/parse.c"
                             ;
    parser->absolute_path = sv_create(absolute_path);

    parser->allocator = allocator;
}

void Parser_free(Parser* parser)
{
    parser->allocator->free_all(parser->allocator);
    parser->token_stream = 
# 57 "src/parse.c" 3 4
                          ((void *)0)
# 57 "src/parse.c"
                              ;
    parser->had_error = 
# 58 "src/parse.c" 3 4
                       0
# 58 "src/parse.c"
                            ;
    parser->panic_mode = 
# 59 "src/parse.c" 3 4
                        0
# 59 "src/parse.c"
                             ;
}

static void Parser_consume(Parser* parser, Token_Type token_type, const char* message)
{
    if (parser->current.type == token_type)
    {
        Parser_advance(parser);
        return;
    }

    Parser_error_at_current(parser, message);
}

static 
# 73 "src/parse.c" 3 4
      _Bool 
# 73 "src/parse.c"
           Parser_check(Parser* parser, Token_Type type)
{
    return parser->current.type == type;
}

static 
# 78 "src/parse.c" 3 4
      _Bool 
# 78 "src/parse.c"
           Parser_match(Parser* parser, Token_Type type)
{
    if (!Parser_check(parser, type)) return 
# 80 "src/parse.c" 3 4
                                           0
# 80 "src/parse.c"
                                                ;
    Parser_advance(parser);
    return 
# 82 "src/parse.c" 3 4
          1
# 82 "src/parse.c"
              ;
}

AST_Node* Parser_add_node(AST_Node_Type node_type, AST_Node* parent, Allocator* allocator)
{
    AST_Node* node = allocator->allocate(allocator, sizeof(AST_Node));
    node->type = node_type;
    node->parent = parent;
    return node;
}

static AST_Node* Parser_precedence(Parser* parser, Precedence precedence, AST_Node* parent)
{
    Parser_advance(parser);
    Parse_Fn prefix_rule = Parser_get_rule(parser->previous.type)->prefix;
    if (prefix_rule == 
# 97 "src/parse.c" 3 4
                      ((void *)0)
# 97 "src/parse.c"
                          )
    {
        Parser_error(parser, "expected expression");
        AST_Node* error_node = Parser_add_node(AST_NODE_ERROR, parent, parser->allocator);
        return error_node;
    }

    AST_Node* left = prefix_rule(parser, 
# 104 "src/parse.c" 3 4
                                        ((void *)0)
# 104 "src/parse.c"
                                            , parent);

    while (precedence <= Parser_get_rule(parser->current.type)->precedence)
    {
        Parser_advance(parser);
        if (parser->current.type == TOKEN_EOF)
        {
            Parser_error(parser, "reached end of file. Expected an expression.");
            AST_Node* error_node = Parser_add_node(AST_NODE_ERROR, parent, parser->allocator);
            return error_node;
        }
        Parse_Fn infix_rule = Parser_get_rule(parser->previous.type)->infix;
        left = infix_rule(parser, left, parent);
    }

    return left;
}

static AST_Node* Parser_number(Parser* parser, AST_Node* previous, AST_Node* parent)
{
    i64 value = strtol(parser->previous.start, 
# 124 "src/parse.c" 3 4
                                              ((void *)0)
# 124 "src/parse.c"
                                                  , 10);
    AST_Node* number_node = Parser_add_node(AST_NODE_LITERAL, parent, parser->allocator);
    AST_Literal* lit = &number_node->literal;
    lit->i = value;
    lit->type = LIT_INT;

    return number_node;
}

static Type_Specifier Parser_check_type_specifier(Token type_token)
{
    if (type_token.length == 0) compiler_bug("Zero length type spec");

    if (type_token.start[0] == 'i')
    {
        if (type_token.length != 3)
        {
            compiler_bug("Type specifier token is invalid: %.*s", type_token.length, type_token.start);
        }

        if (type_token.start[1] == 'n' && type_token.start[2] == 't')
        {
            return TYPE_SPEC_INT;
        }
    }
    return TYPE_SPEC_INVALID;
}

static AST_Node* Parser_variable(Parser* parser, AST_Node* previous, AST_Node* parent, const char* error_message)
{
    Parser_consume(parser, TOKEN_IDENTIFIER, error_message);
    AST_Node* variable = 
# 155 "src/parse.c" 3 4
                        ((void *)0)
# 155 "src/parse.c"
                            ;
    Token identifier = parser->previous;

    if (parent->type == AST_NODE_FUN_DECL)
    {
        if (!Parser_check(parser, TOKEN_COLON))
        {
            compiler_bug("Function argument missing type %.*s", identifier.length, identifier.start);
        }
        Parser_advance(parser);


        variable = Parser_add_node(AST_NODE_FUNCTION_ARGUMENT, parent, parser->allocator);
        variable->fun_argument.name = string_allocate_empty(identifier.length, parser->allocator);
        string_set_length(variable->fun_argument.name, identifier.start, identifier.length);

        if (!Parser_check(parser, TOKEN_IDENTIFIER))
        {
            compiler_bug("Expected identifier, found: %s", token_type_to_string(parser->current.type));
        }
        Parser_advance(parser);
        Token* type = &parser->previous;
        variable->fun_argument.type = Parser_add_node(AST_NODE_TYPE_SPECIFIER, variable, parser->allocator);
        variable->fun_argument.type->type_specifier.type = Parser_check_type_specifier(*type);

    }
    else
    {
    }

    return variable;
}

static AST_Node* Parser_string(Parser* parser, AST_Node* previous, AST_Node* parent)
{
    Token string = parser->current;
    AST_Node* string_node = Parser_add_node(AST_NODE_STRING, parent, parser->allocator);
    string_node->string = string_allocate_empty(string.length, parser->allocator);
    sprintf(string_node->string->str, "%.*s", string.length, string.start);
    return string_node;
}

static AST_Node* Parser_expression(Parser* parser, AST_Node* parent)
{
    return Parser_precedence(parser, PREC_ASSIGNMENT, parent);
}

static AST_Node* Parser_block(Parser* parser, AST_Node* parent)
{
    AST_Node* block = Parser_add_node(AST_NODE_BLOCK, parent, parser->allocator);
    block->block.declarations.capacity = 0;
    block->block.declarations.count = 0;
    block->block.declarations.nodes = 
# 207 "src/parse.c" 3 4
                                     ((void *)0)
# 207 "src/parse.c"
                                         ;

    while (!Parser_check(parser, TOKEN_RIGHT_BRACE) && !Parser_check(parser, TOKEN_EOF))
    {
        AST_node_list_add(&block->block.declarations, Parser_declaration(parser, parent));
    }

    Parser_consume(parser, TOKEN_RIGHT_BRACE, "Expect '}' after block.");

    return block;
}

static AST_Node* Parser_named_variable(Parser* parser, AST_Node* previous, AST_Node* parent)
{
    if (Parser_check(parser, TOKEN_LEFT_PAREN))
    {
        return Parser_call(parser, previous, parent);
    }

    AST_Node* variable = Parser_add_node(AST_NODE_VARIABLE, parent, parser->allocator);
    variable->variable.variable_name = string_allocate_empty(parser->previous.length, parser->allocator);
    string_set_length(variable->variable.variable_name, parser->previous.start, parser->previous.length);
    return variable;
}

static AST_Node* Parser_fun_declaration(Parser* parser, Token* identifier, AST_Node* parent)
{
    AST_Node* fun_node = Parser_add_node(AST_NODE_FUN_DECL, parent, parser->allocator);

    fun_node->fun_decl.name = string_allocate_empty(identifier->length, parser->allocator);
    sprintf(fun_node->fun_decl.name->str, "%.*s", identifier->length, identifier->start);

    Parser_consume(parser, TOKEN_LEFT_PAREN, "Expect '(' after '::' in function declaration.");

    if (!Parser_check(parser, TOKEN_RIGHT_PAREN))
    {
        AST_Node_List* argument_list = &fun_node->fun_decl.arguments;
        do
        {
            AST_node_list_add(argument_list, Parser_variable(parser, 
# 246 "src/parse.c" 3 4
                                                                    ((void *)0)
# 246 "src/parse.c"
                                                                        , fun_node, "Expect parameter name in function argument list."));
        } while (Parser_match(parser, TOKEN_COMMA));


    }

    Parser_consume(parser, TOKEN_RIGHT_PAREN, "Expect ')' after parameters.");

    if (Parser_check(parser, TOKEN_ARROW))
    {

        Parser_advance(parser);
        Token type = parser->current;
        fun_node->fun_decl.return_type = Parser_add_node(AST_NODE_TYPE_SPECIFIER, fun_node, parser->allocator);
        fun_node->fun_decl.return_type->type_specifier.type = Parser_check_type_specifier(type);
        Parser_advance(parser);
    }

    Parser_consume(parser, TOKEN_LEFT_BRACE, "Expect '{' function body.");

    fun_node->fun_decl.body = Parser_block(parser, parent);

    return fun_node;
}

static AST_Node* Parser_return_statement(Parser* parser, AST_Node* parent)
{
    if (Parser_check(parser, TOKEN_SEMICOLON))
    {
        AST_Node* return_node = Parser_add_node(AST_NODE_RETURN, parent, parser->allocator);
        return_node->return_statement.expression = 
# 276 "src/parse.c" 3 4
                                                  ((void *)0)
# 276 "src/parse.c"
                                                      ;
        Parser_consume(parser, TOKEN_SEMICOLON, "Expect ';' after expression.");
        return return_node;
    }
    else
    {
        AST_Node* return_node = Parser_add_node(AST_NODE_RETURN, parent, parser->allocator);
        return_node->return_statement.expression = Parser_expression(parser, return_node);
        Parser_consume(parser, TOKEN_SEMICOLON, "Expect ';' after expression.");
        return return_node;
    }
}

static AST_Node* Parser_expression_statement(Parser* parser, AST_Node* parent)
{
    AST_Node* expression = Parser_expression(parser, parent);
    Parser_consume(parser, TOKEN_SEMICOLON, "Expect ';' after expression.");
    return expression;
}

static AST_Node* Parser_if_statement(Parser* parser, AST_Node* parent)
{
    AST_Node* if_node = Parser_add_node(AST_NODE_IF, parent, parser->allocator);

    if_node->if_statement.condition = Parser_expression(parser, if_node);

    if_node->if_statement.then_arm = Parser_statement(parser, if_node);
    if_node->if_statement.else_arm = 
# 303 "src/parse.c" 3 4
                                    ((void *)0)
# 303 "src/parse.c"
                                        ;

    if (Parser_match(parser, TOKEN_ELSE))
    {
        if_node->if_statement.else_arm = Parser_statement(parser, if_node);
    }

    return if_node;
}

static AST_Node* Parser_statement(Parser* parser, AST_Node* parent)
{
    if (Parser_match(parser, TOKEN_RETURN))
    {
        return Parser_return_statement(parser, parent);
    }
    else if (Parser_match(parser, TOKEN_IF))
    {
        return Parser_if_statement(parser, parent);
    }
    else if (Parser_match(parser, TOKEN_LEFT_BRACE))
    {
        return Parser_block(parser, parent);
    }
    else
    {
        return Parser_expression_statement(parser, parent);
    }
}

static AST_Node* Parser_const_declaration(Parser* parser, Token* identifier, AST_Node* parent)
{
    if (Parser_check(parser, TOKEN_LEFT_PAREN))
    {
        return Parser_fun_declaration(parser, identifier, parent);
    }
    return 
# 339 "src/parse.c" 3 4
          ((void *)0)
# 339 "src/parse.c"
              ;
}

static AST_Node* Parser_declaration(Parser* parser, AST_Node* parent)
{
    if (Parser_check(parser, TOKEN_IDENTIFIER))
    {
        Token identifier = parser->current;
        Parser_advance(parser);
        if (Parser_check(parser, TOKEN_COLON_COLON))
        {
            Parser_advance(parser);
            return Parser_const_declaration(parser, &identifier, parent);
        }
        else if (Parser_check(parser, TOKEN_LEFT_PAREN))
        {
            AST_Node* call_node = Parser_call(parser, 
# 355 "src/parse.c" 3 4
                                                     ((void *)0)
# 355 "src/parse.c"
                                                         , parent);
            Parser_consume(parser, TOKEN_SEMICOLON, "Expect ';' after function call.");
            return call_node;
        }
        return Parser_statement(parser, parent);
    }
    else
    {
        return Parser_statement(parser, parent);
    }
    return 
# 365 "src/parse.c" 3 4
          ((void *)0)
# 365 "src/parse.c"
              ;
}

static AST_Node* Parser_binary(Parser* parser, AST_Node* left, AST_Node* parent)
{
    Token_Type operator_type = parser->previous.type;
    Parse_Rule* rule = Parser_get_rule(operator_type);

    AST_Node* binary_expression = Parser_add_node(AST_NODE_BINARY, parent, parser->allocator);

    binary_expression->binary.left = left;
    binary_expression->binary.right = Parser_precedence(parser, rule->precedence + 1, binary_expression);

    switch (operator_type)
    {
    case TOKEN_PLUS:
    case TOKEN_MINUS:
    case TOKEN_STAR:
    case TOKEN_SLASH:
    case TOKEN_EQUAL_EQUAL:
    case TOKEN_EQUAL:
    case TOKEN_BANG_EQUAL:
    case TOKEN_PIPE:
    case TOKEN_PIPE_PIPE:
    case TOKEN_AMPERSAND:
    case TOKEN_AMPERSAND_AMPERSAND:
    case TOKEN_LESS:
    case TOKEN_LESS_EQUAL:
    case TOKEN_GREATER:
    case TOKEN_GREATER_EQUAL:
    {
        binary_expression->binary.operator = operator_type;
    }
    break;
    default:
    binary_expression->binary.operator = TOKEN_ERROR;
    }
    return binary_expression;
}

static AST_Node* Parser_unary(Parser* parser, AST_Node* rest, AST_Node* parent)
{
    Token_Type operator_type = parser->previous.type;
    AST_Node* unary_expression = Parser_add_node(AST_NODE_UNARY, parent, parser->allocator);

    unary_expression->unary.expression = Parser_precedence(parser, PREC_UNARY, parent);

    switch (operator_type)
    {
    case TOKEN_MINUS:
    {
        unary_expression->unary.operator = TOKEN_MINUS;
    }
    break;
    case TOKEN_BANG:
    {
        unary_expression->unary.operator = TOKEN_BANG;
    }
    break;
    default:
    {
        unary_expression->unary.operator = TOKEN_ERROR;
    }
    break;
    }
    return unary_expression;
}

static AST_Node* Parser_grouping(Parser* parser, AST_Node* previous, AST_Node* parent)
{
    AST_Node* grouping = Parser_expression(parser, parent);
    Parser_consume(parser, TOKEN_RIGHT_PAREN, "Expect ')' after expression.");
    return grouping;
}

static void Parser_argument_list(Parser* parser, AST_Node* previous, AST_Node* parent)
{
    if (!Parser_check(parser, TOKEN_RIGHT_PAREN))
    {
        do
        {
            AST_node_list_add(&parent->fun_call.arguments, Parser_expression(parser, parent));
            if (parent->fun_call.arguments.count == 255)
            {
                Parser_error(parser, "Can't have more than 255 arguments.");
            }
        } while (Parser_match(parser, TOKEN_COMMA));
    }
    Parser_consume(parser, TOKEN_RIGHT_PAREN, "Expect ')' after arguments.");
}

static AST_Node* Parser_call(Parser* parser, AST_Node* previous, AST_Node* parent)
{
    AST_Node* call = Parser_add_node(AST_NODE_CALL, parent, parser->allocator);
    Token prev = parser->previous;
    call->fun_call.name = string_allocate_empty(prev.length, parser->allocator);
    string_set_length(call->fun_call.name, prev.start, prev.length);
    Parser_advance(parser);
    Parser_argument_list(parser, 
# 463 "src/parse.c" 3 4
                                ((void *)0)
# 463 "src/parse.c"
                                    , call);
    return call;
}

static Parse_Rule* Parser_get_rule(Token_Type type)
{
    return &rules[type];
}


# 472 "src/parse.c" 3 4
_Bool 
# 472 "src/parse.c"
    Parser_parse(Parser* parser, 
# 472 "src/parse.c" 3 4
                                 _Bool 
# 472 "src/parse.c"
                                      print_ast, Allocator* allocator)
{
    Parser_advance(parser);

    if (!Parser_match(parser, TOKEN_EOF))
    {
        parser->root = Parser_add_node(AST_NODE_PROGRAM, 
# 478 "src/parse.c" 3 4
                                                        ((void *)0)
# 478 "src/parse.c"
                                                            , parser->allocator);
        parser->root->program.declarations.count = 0;
        parser->root->program.declarations.capacity = 0;
        parser->root->program.declarations.nodes = 
# 481 "src/parse.c" 3 4
                                                  ((void *)0)
# 481 "src/parse.c"
                                                      ;

        while (!Parser_match(parser, TOKEN_EOF))
        {
            AST_node_list_add(&parser->root->program.declarations, Parser_declaration(parser, parser->root));
        }

    }

    if (!parser->had_error && print_ast)
    {
        pretty_print_ast(parser->root, allocator);
    }

    return !parser->had_error;
}
# 58 "src/main.c" 2
# 1 "src/ir.c" 1
IR_Register IR_register_alloc(IR_Register_Table* table)
{
    for (i32 i = 0; i < table->capacity; i++)
    {
        if (!table->inuse_table[i])
        {
            table->inuse_table[i] = 
# 7 "src/ir.c" 3 4
                                   1
# 7 "src/ir.c"
                                       ;
            IR_Register reg = { .gpr_index = i};
            return reg;
        }
    }

    i32 old_capacity = table->capacity;
    table->capacity = table->capacity == 0 ? 256 : table->capacity * 2;
    table->inuse_table = realloc(table->inuse_table, sizeof(
# 15 "src/ir.c" 3 4
                                                           _Bool
# 15 "src/ir.c"
                                                               ) * table->capacity);
    for (i32 i = old_capacity; i < table->capacity; i++)
    {
        table->inuse_table[i] = 
# 18 "src/ir.c" 3 4
                               0
# 18 "src/ir.c"
                                    ;
    }
    IR_Register reg = { .gpr_index = old_capacity };
    table->inuse_table[old_capacity] = 
# 21 "src/ir.c" 3 4
                                      1
# 21 "src/ir.c"
                                          ;
    return reg;
}

static void IR_error(char* format, ...)
{
    fprintf(
# 27 "src/ir.c" 3 4
           stderr
# 27 "src/ir.c"
                 , "\x1b[1;31m");
    va_list(ap);
    
# 29 "src/ir.c" 3 4
   __builtin_va_start(
# 29 "src/ir.c"
   ap
# 29 "src/ir.c" 3 4
   ,
# 29 "src/ir.c"
   format
# 29 "src/ir.c" 3 4
   )
# 29 "src/ir.c"
                       ;
    vfprintf(
# 30 "src/ir.c" 3 4
            stderr
# 30 "src/ir.c"
                  , format, ap);
    
# 31 "src/ir.c" 3 4
   __builtin_va_end(
# 31 "src/ir.c"
   ap
# 31 "src/ir.c" 3 4
   )
# 31 "src/ir.c"
             ;
    fprintf(
# 32 "src/ir.c" 3 4
           stderr
# 32 "src/ir.c"
                 , "\x1b[0m\n");

    exit(1);
}

static char* IR_type_to_string(IR_Node_Type type)
{
    switch(type)
    {
    case IR_NODE_INSTRUCTION:
    return "instruction";
    case IR_NODE_LABEL:
    return "label";
    case IR_NODE_FUNCTION_DECL:
    return "function declaration";
    }
    return 
# 48 "src/ir.c" 3 4
          ((void *)0)
# 48 "src/ir.c"
              ;
}

static char* IR_instruction_type_to_string(IR_Instruction* instruction)
{
    switch(instruction->type)
    {
    case IR_INS_MOV:
    return "mov";
    case IR_INS_PUSH:
    return "push";
    case IR_INS_POP:
    return "pop";
    case IR_INS_JUMP:
    return "jump";
    case IR_INS_BINOP:
    return "binop";
    case IR_INS_RET:
    return "return";
    case IR_INS_CALL:
    return "call";
    case IR_INS_UNOP:
    return "unop";
    case IR_INS_COMPARE:
    return "compare";
    default: IR_error("Unknown instruction type.");
    }
    return 
# 75 "src/ir.c" 3 4
          ((void *)0)
# 75 "src/ir.c"
              ;
}

static char* IR_node_to_string(IR_Node* node)
{
    switch(node->type)
    {
    case IR_NODE_INSTRUCTION:
    {
        return IR_instruction_type_to_string(&node->instruction);
    }
    break;
    case IR_NODE_LABEL:
    {
        return node->label.label_name->str;
    }
    break;
    case IR_NODE_FUNCTION_DECL:
    {
        return node->function.name->str;
    }
    break;
    }
    return 
# 98 "src/ir.c" 3 4
          ((void *)0)
# 98 "src/ir.c"
              ;
}

String* IR_generate_label_name(IR_Program* program, Allocator* allocator)
{
    return string_createf(allocator, ".Label_%d", program->label_counter++);
}

IR_Block* IR_allocate_block(IR_Program* program)
{
    IR_Block_Array* block_array = &program->block_array;
    if (block_array->count + 1 > block_array->capacity)
    {
        block_array->capacity = block_array->capacity == 0 ? 256 : block_array->capacity * 2;
        block_array->blocks = realloc(block_array->blocks, sizeof(IR_Block) * block_array->capacity);
    }

    IR_Block* block = &block_array->blocks[block_array->count++];
    block->parent_program = program;
    block->block_address = (IR_Block_Address) { .address = block_array->count - 1 };
    block->previous = 
# 118 "src/ir.c" 3 4
                                ((void *)0)
# 118 "src/ir.c"
                                    ;
    block->next = 
# 119 "src/ir.c" 3 4
                                ((void *)0)
# 119 "src/ir.c"
                                    ;
    block->has_label = 
# 120 "src/ir.c" 3 4
                                0
# 120 "src/ir.c"
                                     ;
    block->node_array.count = 0;
    block->node_array.nodes = 
# 122 "src/ir.c" 3 4
                                ((void *)0)
# 122 "src/ir.c"
                                    ;
    block->node_array.capacity = 0;

    return block;
}

IR_Node* IR_emit_node(IR_Block* block, IR_Node_Type node_type)
{
    IR_Node_Array* node_array = &block->node_array;
    if (node_array->count + 1 > node_array->capacity)
    {
        node_array->capacity = node_array->capacity == 0 ? 256 : node_array->capacity * 2;
        node_array->nodes = realloc(node_array->nodes, sizeof(IR_Node) * node_array->capacity);
    }

    IR_Node* node = &node_array->nodes[node_array->count++];
    node->type = node_type;
    return node;
}

void IR_add_function(IR_Program* program, String* name, 
# 142 "src/ir.c" 3 4
                                                       _Bool 
# 142 "src/ir.c"
                                                            exported)
{
    IR_Function_Array* array = &program->function_array;
    if (array->count + 1 > array->capacity)
    {
        array->capacity = array->capacity == 0 ? 256 : array->capacity * 2;
        array->functions = realloc(array->functions, sizeof(IR_Function) * array->capacity);
    }

    IR_Function* function = &array->functions[array->count++];
    function->name = sv_create(name);
    function->exported = exported;
}

i32 IR_find_function(IR_Program* program, String* name)
{
    IR_Function_Array functions = program->function_array;
    for (i32 i = 0; i < functions.count; i++)
    {
        String_View fun_name = functions.functions[i].name;
        if (string_equal(name, fun_name.string))
        {
            return i;
        }
    }
    return -1;
}

String_View* IR_get_function_name(IR_Program* program, i32 index)
{
    if (index == -1) return 
# 172 "src/ir.c" 3 4
                           ((void *)0)
# 172 "src/ir.c"
                               ;
    if (program->function_array.count <= index) return 
# 173 "src/ir.c" 3 4
                                                      ((void *)0)
# 173 "src/ir.c"
                                                          ;
    return &program->function_array.functions[index].name;
}

IR_Node* IR_emit_function_decl(IR_Block* block, String* name, 
# 177 "src/ir.c" 3 4
                                                             _Bool 
# 177 "src/ir.c"
                                                                  export)
{
    IR_Node* function_decl = IR_emit_node(block, IR_NODE_FUNCTION_DECL);
    function_decl->function.export = export;
    function_decl->function.name = name;
    IR_add_function(block->parent_program, name, export);

    return function_decl;
}

IR_Label* IR_emit_label(IR_Block* block, String* label_name, Allocator* allocator)
{
    if(block->has_label)
    {
        fprintf(
# 191 "src/ir.c" 3 4
               stderr
# 191 "src/ir.c"
                     , "unable to add label to IR block. Already has a label\n");
        return 
# 192 "src/ir.c" 3 4
              ((void *)0)
# 192 "src/ir.c"
                  ;
    }

    IR_Node* label = IR_emit_node(block, IR_NODE_LABEL);
    label->label.label_name = label_name;
    return &label->label;
}

IR_Node* IR_emit_instruction(IR_Block* block, IR_Instruction_Type instruction_type)
{
    IR_Node* node = IR_emit_node(block, IR_NODE_INSTRUCTION);
    node->instruction.type = instruction_type;
    return node;
}

IR_Node* IR_emit_return(IR_Block* block, IR_Register* reg, Allocator* allocator)
{
    IR_Node* node = IR_emit_instruction(block, IR_INS_RET);
    IR_Return* ret = &node->instruction.ret;

    if (reg)
    {
        ret->return_register = *reg;
        ret->has_return_value = 
# 215 "src/ir.c" 3 4
                               1
# 215 "src/ir.c"
                                   ;
    }
    else
    {
        ret->has_return_value = 
# 219 "src/ir.c" 3 4
                               0
# 219 "src/ir.c"
                                    ;
    }

    return node;
}

IR_UnOp* IR_emit_unop(IR_Block* block, IR_Register reg, IR_Op operator, Allocator* allocator)
{
    IR_Node* node = IR_emit_instruction(block, IR_INS_UNOP);
    IR_UnOp* unop = &node->instruction.unop;

    IR_Value* value = &unop->value;
    value->type = VALUE_LOCATION;

    IR_Location* location = &value->loc;
    location->type = IR_LOCATION_REGISTER;
    location->reg = reg;

    unop->operator = operator;

    return unop;
}

IR_Push* IR_emit_push_int(IR_Block* block, i32 value, Allocator* allocator)
{
    IR_Node* node = IR_emit_instruction(block, IR_INS_PUSH);
    IR_Push* push = &node->instruction.push;

    IR_Value* IR_value = &push->value;
    IR_value->type = VALUE_INT;
    IR_value->integer = value;

    return push;
}

IR_Move* IR_emit_move_reg_to_reg(IR_Block* block, IR_Register src_reg, IR_Register dst_reg, Allocator* allocator)
{
    IR_Node* node = IR_emit_instruction(block, IR_INS_MOV);
    IR_Move* move = &node->instruction.move;

    IR_Value* src = &move->src;
    src->type = IR_LOCATION_REGISTER;
    src->loc.reg = src_reg;

    IR_Location* dst = &move->dst;
    dst->type = IR_LOCATION_REGISTER;
    dst->reg = dst_reg;

    return move;
}

IR_Move* IR_emit_move_lit_to_reg(IR_Block* block, i32 value, IR_Register reg, Allocator* allocator)
{
    IR_Node* node = IR_emit_instruction(block, IR_INS_MOV);
    IR_Move* move = &node->instruction.move;

    IR_Value* IR_src = &move->src;
    IR_src->type = VALUE_INT;
    IR_src->integer = value;

    IR_Location* dst = &move->dst;
    dst->type = IR_LOCATION_REGISTER;
    dst->reg = reg;

    return move;
}

IR_Location IR_create_location_register(IR_Register reg)
{
    IR_Location location = { .type = IR_LOCATION_REGISTER };
    location.reg = reg;
    return location;
}

IR_Value IR_create_value_location(IR_Location location)
{
    IR_Value value = {.type = VALUE_LOCATION};
    value.loc = location;
    return value;
}

IR_Value IR_create_value_register(IR_Register reg)
{
    return IR_create_value_location(IR_create_location_register(reg));
}

IR_Value IR_create_value_number(i32 number)
{
    IR_Value value = { .type = VALUE_INT };
    value.integer = number;
    return value;
}

IR_BinOp* IR_emit_binop(IR_Block* block, IR_Register left, IR_Register right, IR_Op operator, IR_Register_Table* table, Allocator* allocator)
{
    IR_Node* node = IR_emit_instruction(block, IR_INS_BINOP);
    IR_BinOp* binop = &node->instruction.binop;

    binop->left = IR_create_value_location(IR_create_location_register(left));
    binop->right = IR_create_value_location(IR_create_location_register(right));

    switch(operator)
    {
    case OP_SUB:
    {
        binop->destination = binop->left.loc.reg;
    }
    break;
    default:
    {
        binop->destination = binop->right.loc.reg;
    }
    break;
    }

    binop->operator = operator;

    return binop;
}

IR_Op IR_map_operator(Token_Type source)
{
    switch(source)
    {
    case TOKEN_PLUS:
    return OP_ADD;
    case TOKEN_MINUS:
    return OP_SUB;
    case TOKEN_STAR:
    return OP_MUL;
    case TOKEN_SLASH:
    return OP_DIV;
    case TOKEN_BANG:
    return OP_NOT;
    case TOKEN_EQUAL_EQUAL:
    return OP_EQUAL;
    case TOKEN_EQUAL:
    return OP_ASSIGN;
    case TOKEN_BANG_EQUAL:
    return OP_NOT_EQUAL;
    case TOKEN_PIPE:
    return OP_BIT_OR;
    case TOKEN_PIPE_PIPE:
    return OP_OR;
    case TOKEN_AMPERSAND:
    return OP_BIT_AND;
    case TOKEN_AMPERSAND_AMPERSAND:
    return OP_AND;
    case TOKEN_LESS:
    return OP_LESS;
    case TOKEN_LESS_EQUAL:
    return OP_LESS_EQUAL;
    case TOKEN_GREATER:
    return OP_GREATER;
    case TOKEN_GREATER_EQUAL:
    return OP_GREATER_EQUAL;
    default: IR_error("Invalid operator %s.", token_type_to_string(source)); exit(1);
    }
}

IR_Jump* IR_emit_jump(IR_Block* block, IR_Label label, IR_Jump_Type jump_type, IR_Block_Address block_address, Allocator* allocator)
{
    IR_Node* node = IR_emit_instruction(block, IR_INS_JUMP);
    IR_Jump* jump = &node->instruction.jump;

    jump->type = jump_type;
    jump->address = block_address;

    return jump;
}

IR_Compare* IR_emit_comparison(IR_Block* block, IR_Value left, IR_Location right, IR_Op operator, IR_Register_Table* table, Allocator* allocator)
{
    IR_Node* node = IR_emit_instruction(block, IR_INS_COMPARE);
    IR_Compare* compare = &node->instruction.compare;

    compare->left = left;
    compare->right = right;
    compare->operator = operator;
    compare->destination = compare->right.reg;

    return compare;
}

IR_Block* IR_get_block(IR_Program* program, IR_Block_Address address)
{
    IR_Block_Array* blocks = &program->block_array;
    if (address.address >= 0 && address.address < blocks->count)
    {
        return &blocks->blocks[address.address];
    }
    return 
# 410 "src/ir.c" 3 4
          ((void *)0)
# 410 "src/ir.c"
              ;
}

IR_Node* IR_get_node(IR_Block* block, i32 index)
{
    if (index >= 0 && index < block->node_array.count)
    {
        return &block->node_array.nodes[index];
    }
    return 
# 419 "src/ir.c" 3 4
          ((void *)0)
# 419 "src/ir.c"
              ;
}

IR_Block* IR_get_current_block(IR_Program* program)
{
    if (program->block_array.count == 0)
    {
        return 
# 426 "src/ir.c" 3 4
              ((void *)0)
# 426 "src/ir.c"
                  ;
    }

    return &program->block_array.blocks[program->block_array.count - 1];
}


IR_Register IR_translate_expression(AST_Node* node, IR_Block* block, IR_Block* end_block, Allocator* allocator, IR_Register_Table* table)
{
    switch(node->type)
    {
    case AST_NODE_LITERAL:
    {
        IR_Register reg = IR_register_alloc(table);
        AST_Literal* literal = &node->literal;
        switch(node->literal.type)
        {
        case LIT_INT:
        {
            IR_emit_move_lit_to_reg(block, literal->i, reg, allocator);
        }
        break;
        case LIT_FLOAT:
        {}
        break;
        case LIT_STRING:
        {}
        break;
        }

        return reg;
    }
    case AST_NODE_VARIABLE:
    {

    }
    break;
    case AST_NODE_BINARY:
    {
        IR_Register left_reg = IR_translate_expression(node->binary.left, block, 
# 465 "src/ir.c" 3 4
                                                                                ((void *)0)
# 465 "src/ir.c"
                                                                                    , allocator, table);
        IR_Register right_reg = IR_translate_expression(node->binary.right, block, 
# 466 "src/ir.c" 3 4
                                                                                  ((void *)0)
# 466 "src/ir.c"
                                                                                      , allocator, table);

        Token_Type operator = node->binary.operator;

        switch(operator)
        {
        case TOKEN_PLUS:
        case TOKEN_MINUS:
        case TOKEN_STAR:
        case TOKEN_SLASH:
        case TOKEN_BANG:
        case TOKEN_EQUAL:
        case TOKEN_PIPE:
        case TOKEN_AMPERSAND:
        {
            IR_BinOp* binop = IR_emit_binop(block, left_reg, right_reg, IR_map_operator(operator), table, allocator);
            return binop->destination;
        }
        case TOKEN_EQUAL_EQUAL:
        case TOKEN_PIPE_PIPE:
        case TOKEN_AMPERSAND_AMPERSAND:
        case TOKEN_LESS:
        case TOKEN_GREATER:
        case TOKEN_LESS_EQUAL:
        case TOKEN_GREATER_EQUAL:
        case TOKEN_BANG_EQUAL:
        {
            IR_Value left_val = IR_create_value_location(IR_create_location_register(left_reg));
            IR_Location right_loc = IR_create_location_register(right_reg);

            
# 496 "src/ir.c" 3 4
           _Bool 
# 496 "src/ir.c"
                left_is_zero = left_val.type == VALUE_INT && left_val.integer;

            IR_Jump_Type jump_type = JMP_ALWAYS;
            switch(operator)
            {
            case TOKEN_EQUAL_EQUAL:
            {
                if (left_is_zero)
                {
                    jump_type = JMP_ZERO;
                }
                else
                {
                    jump_type = JMP_NOT_EQUAL;
                }
            }
            break;
            case TOKEN_LESS:
            {
                jump_type = JMP_GREATER_EQUAL;

            }
            break;
            case TOKEN_GREATER:
            {
                jump_type = JMP_LESS_EQUAL;

            }
            break;
            case TOKEN_LESS_EQUAL:
            {
                jump_type = JMP_GREATER;

            }
            break;
            case TOKEN_GREATER_EQUAL:
            {
                jump_type = JMP_LESS;

            }
            break;
            case TOKEN_BANG_EQUAL:
            {
                if (left_is_zero)
                {
                    jump_type = JMP_NOT_ZERO;
                }
                else
                {
                    jump_type = JMP_EQUAL;
                }
            }
            break;
            default: IR_error("Invalid comparison operator %s", token_type_to_string(operator));
            }

            IR_Compare* compare = IR_emit_comparison(block, left_val, right_loc, IR_map_operator(operator), table, allocator);



            if (end_block)
            {
                IR_Node* node = IR_get_node(end_block, 0);
                IR_Label* end_label = &node->label;
                IR_emit_jump(block, *end_label, jump_type, end_block->block_address, allocator);
            }
            else
            {

            }

            return compare->destination;
        }
        default:
        IR_error("Unsupported operator for binary operations %s\n", token_type_to_string(operator));
        break;
        }
    }
    case AST_NODE_UNARY:
    {
        IR_Register reg = IR_translate_expression(node->unary.expression, block, 
# 576 "src/ir.c" 3 4
                                                                                ((void *)0)
# 576 "src/ir.c"
                                                                                    , allocator, table);
        Token_Type operator = node->unary.operator;
        switch(operator)
        {
        case TOKEN_MINUS:
        {
            IR_emit_unop(block, reg, OP_SUB, allocator);
        }
        break;
        case TOKEN_BANG:
        {
            IR_emit_unop(block, reg, OP_NOT, allocator);
        }
        break;
        default: IR_error("Unsupported operator for unary operations %s\n", token_type_to_string(operator));
        }
        return reg;
    }
    default:
    IR_error("Unsupported AST node: %s, %s, %d", AST_type_string(node->type), "src/ir.c", 595);
    return (IR_Register){ .gpr_index = -1};
    }
}

IR_Block* IR_translate_block(IR_Block* block, AST_Node* body, Allocator* allocator, IR_Register_Table* register_table);

IR_Block* IR_translate_statement(IR_Block* block, AST_Node* statement, Allocator* allocator, IR_Register_Table* register_table)
{
    switch(statement->type)
    {
    case AST_NODE_RETURN:
    {
        if (statement->return_statement.expression)
        {
            IR_Register reg = IR_translate_expression(statement->return_statement.expression, block, 
# 610 "src/ir.c" 3 4
                                                                                                    ((void *)0)
# 610 "src/ir.c"
                                                                                                        , allocator, register_table);
            IR_Register dst = IR_register_alloc(register_table);

            IR_emit_move_reg_to_reg(block, reg, dst, allocator);
            IR_emit_return(block, &dst, allocator);
        }
        else
        {
            IR_emit_return(block, 
# 618 "src/ir.c" 3 4
                                 ((void *)0)
# 618 "src/ir.c"
                                     , allocator);
        }
        return block;
    }
    break;
    case AST_NODE_IF:
    {
        AST_Node* ast_condition = statement->if_statement.condition;

        AST_Node* ast_then_arm = statement->if_statement.then_arm;
        if (ast_then_arm->type != AST_NODE_BLOCK)
        {
            IR_error("Then arm for if statement has to be a block, was %s", AST_type_string(ast_then_arm->type));
        }

        IR_Block* then_block = IR_allocate_block(block->parent_program);
        IR_Block* end_block = IR_allocate_block(block->parent_program);

        IR_Label* end_label = IR_emit_label(end_block, IR_generate_label_name(block->parent_program, allocator), allocator);

        IR_Register cond_register = IR_translate_expression(ast_condition, block, end_block, allocator, register_table);
        IR_Block* new_block = end_block;

        if (ast_condition->type == AST_NODE_LITERAL)
        {
            IR_emit_comparison(block, IR_create_value_number(0), IR_create_location_register(cond_register), OP_EQUAL, register_table, allocator);
            IR_emit_jump(block, *end_label, JMP_EQUAL, end_block->block_address, allocator);

            IR_translate_block(then_block, ast_then_arm, allocator, register_table);
        }
        else if (ast_condition->type == AST_NODE_BINARY)
        {
            IR_translate_block(then_block, ast_then_arm, allocator, register_table);
        }

        AST_Node* ast_else_arm = statement->if_statement.else_arm;
        if (ast_else_arm)
        {



            switch(ast_else_arm->type)
            {
            case AST_NODE_BLOCK:
            {
                new_block = IR_translate_block(end_block, ast_else_arm, allocator, register_table);
            }
            break;
            case AST_NODE_IF:
            {
                new_block = IR_translate_statement(end_block, ast_else_arm, allocator, register_table);
            }
            break;
            default: compiler_bug("Invalid statement type for else statement %s.", AST_type_string(ast_else_arm->type));
            }
        }
        return new_block;
    }
    break;
    case AST_NODE_CALL:
    {
        String* fun_name = statement->fun_call.name;
        i32 index = IR_find_function(block->parent_program, fun_name);

        if (index != -1)
        {
            IR_Node* call = IR_emit_instruction(block, IR_INS_CALL);
            call->instruction.call.function_index = index;
        }
        else
        {
            compiler_bug("Unknown function %s.", fun_name->str);
        }
    }
    break;
    case AST_NODE_LITERAL:
    case AST_NODE_BINARY:
    case AST_NODE_UNARY:
    {
        IR_translate_expression(statement, block, 
# 697 "src/ir.c" 3 4
                                                 ((void *)0)
# 697 "src/ir.c"
                                                     , allocator, register_table);
    }
    break;
    default: compiler_bug("Invalid AST node type %s.", AST_type_string(statement->type));
    }

    return block;
}

IR_Block* IR_translate_block(IR_Block* block, AST_Node* body, Allocator* allocator, IR_Register_Table* register_table)
{
    AST_Node_List list = body->block.declarations;

    IR_Block* used_block = block;

    for (i32 i = 0; i < list.count; i++)
    {
        AST_Node* node = list.nodes[i];
        used_block = IR_translate_statement(used_block, node, allocator, register_table);
    }
    return used_block;
}

void IR_translate_program(IR_Program* program, AST_Node* ast_program, Allocator* allocator, IR_Register_Table* register_table)
{
    AST_Node_List declarations = ast_program->program.declarations;

    for (i32 i = 0; i < declarations.count; i++)
    {
        AST_Node* node = declarations.nodes[i];

        switch(node->type)
        {
        case AST_NODE_FUN_DECL:
        {
            IR_Block* block = IR_allocate_block(program);
            IR_emit_function_decl(block, node->fun_decl.name, 
# 733 "src/ir.c" 3 4
                                                             1
# 733 "src/ir.c"
                                                                 );

            IR_translate_block(block, node->fun_decl.body, allocator, register_table);
        }
        break;
        case AST_NODE_LITERAL:
        case AST_NODE_BINARY:
        case AST_NODE_UNARY:
        {
            IR_Block* block = IR_get_current_block(program);

            String* name = string_allocate("main", allocator);
            IR_emit_function_decl(block, name, 
# 745 "src/ir.c" 3 4
                                              1
# 745 "src/ir.c"
                                                  );
            IR_translate_expression(node, block, 
# 746 "src/ir.c" 3 4
                                                ((void *)0)
# 746 "src/ir.c"
                                                    , allocator, register_table);
            IR_emit_instruction(block, IR_INS_RET);
        }
        break;
        default: compiler_bug("Invalid AST node type %s.", AST_type_string(node->type));
        }
    }
}

IR_Program IR_translate_ast(AST_Node* root_node, Allocator* allocator)
{
    IR_Program program =
        {
            .data_array = {0},
            .block_array = {0},
            .function_array = {0},
            .label_counter = 0
        };

    IR_Register_Table* register_table = malloc(sizeof(IR_Register_Table));
    register_table->capacity = 0;
    register_table->inuse_table = 
# 767 "src/ir.c" 3 4
                                 ((void *)0)
# 767 "src/ir.c"
                                     ;

    IR_translate_program(&program, root_node, allocator, register_table);

    return program;
}

void IR_pretty_print_register(String_Builder* sb, IR_Register* reg)
{
    switch(reg->type)
    {
    case IR_GPR:
    {
        sb_appendf(sb, "%r%d", reg->gpr_index);
    }
    break;
    case IR_SPECIAL:
    {
        switch(reg->special_register)
        {
        case SPECIAL_STACK_POINTER:
        {
            sb_append(sb, "rsp");
        }
        break;
        case SPECIAL_STACK_BASE:
        {
            sb_append(sb, "rsb");
        }
        break;
        case SPECIAL_INSTRUCTION_POINTER:
        {
            sb_append(sb, "rip");
        }
        break;
        }
    }
    break;
    }
}

void IR_pretty_print_location(String_Builder* sb, IR_Location* location)
{
    switch(location->type)
    {
    case IR_LOCATION_REGISTER:
    {
        IR_pretty_print_register(sb, &location->reg);
    }
    break;
    case IR_LOCATION_MEMORY:
    {

    }
    break;
    }
}

void IR_pretty_print_value(String_Builder* sb, IR_Value* value)
{
    switch(value->type)
    {
    case VALUE_LOCATION:
    {
        IR_pretty_print_location(sb, &value->loc);
    }
    break;
    case VALUE_INT:
    {
        sb_appendf(sb, "%d", value->integer);
    }
    break;
    case VALUE_VARIABLE:
    {
        sb_appendf(sb, "\"%s\"", value->variable.name);
    }
    break;
    }
}

void IR_pretty_print_instruction(String_Builder* sb, IR_Instruction* instruction, IR_Program* program)
{
    sb_indent(sb, 8);

    switch(instruction->type)
    {
    case IR_INS_MOV:
    {
        IR_Move* move = &instruction->move;

        IR_Value* src = &move->src;
        IR_Location* dst = &move->dst;

        IR_pretty_print_location(sb, dst);
        sb_append(sb, " := ");
        IR_pretty_print_value(sb, src);

        sb_newline(sb);
    }
    break;
    case IR_INS_PUSH:
    {
        IR_Push* push = &instruction->push;
        sb_append(sb, "push(");
        IR_pretty_print_value(sb, &push->value);
        sb_append(sb, ")");
        sb_newline(sb);
    }
    break;
    case IR_INS_POP:
    {
        IR_Pop* pop = &instruction->pop;
        sb_append(sb, "pop(");
        IR_pretty_print_value(sb, &pop->value);
        sb_append(sb, ")");
        sb_newline(sb);
    }
    break;
    case IR_INS_JUMP:
    {
        IR_Jump* jump = &instruction->jump;
        switch(jump->type)
        {
        case JMP_ALWAYS:
        {
            sb_append(sb, "jmp ");
        }
        break;
        case JMP_EQUAL:
        {
            sb_append(sb, "je ");
        }
        break;
        case JMP_ZERO:
        {
            sb_append(sb, "jz ");
        }
        break;
        case JMP_NOT_EQUAL:
        {
            sb_append(sb, "jne ");
        }
        break;
        case JMP_NOT_ZERO:
        {
            sb_append(sb, "jnz ");
        }
        break;
        case JMP_LESS:
        {
            sb_append(sb, "jl ");
        }
        break;
        case JMP_LESS_EQUAL:
        {
            sb_append(sb, "jle ");
        }
        break;
        case JMP_GREATER:
        {
            sb_append(sb, "jg ");
        }
        break;
        case JMP_GREATER_EQUAL:
        {
            sb_append(sb, "jge ");
        }
        break;
        }

        IR_Block_Address address = jump->address;
        if (program)
        {
            IR_Block* block = &program->block_array.blocks[address.address];
            IR_Node* first_node = &block->node_array.nodes[0];
            IR_Label* label = &first_node->label;
            sb_append(sb, label->label_name->str);
        }

        sb_newline(sb);
    }
    break;
    case IR_INS_BINOP:
    {
        IR_BinOp* binop = &instruction->binop;

        IR_pretty_print_register(sb, &binop->destination);
        sb_append(sb, " := ");
        IR_pretty_print_value(sb, &binop->left);

        switch(binop->operator)
        {
        case OP_ADD:
        {
            sb_append(sb, " + ");
        }
        break;
        case OP_SUB:
        {
            sb_append(sb, " - ");
        }
        break;
        case OP_MUL:
        {
            sb_append(sb, " * ");
        }
        break;
        case OP_DIV:
        {
            sb_append(sb, " / ");
        }
        break;
        case OP_NOT_EQUAL:
        {
            sb_append(sb, " != ");
        }
        break;
        case OP_EQUAL:
        {
            sb_append(sb, " == ");
        }
        break;
        case OP_ASSIGN:
        {
            sb_append(sb, " = ");
        }
        break;
        case OP_BIT_OR:
        {
            sb_append(sb, " | ");
        }
        break;
        case OP_BIT_AND:
        {
            sb_append(sb, " & ");
        }
        break;
        default: IR_error("Unsupported operator for binary operation\n");
        }
        IR_pretty_print_value(sb, &binop->right);

        sb_newline(sb);
    }
    break;
    case IR_INS_RET:
    {
        IR_Return* ret = &instruction->ret;
        sb_append(sb, "ret");
        if (ret->has_return_value)
        {
            sb_append(sb, " ");
            IR_pretty_print_register(sb, &ret->return_register);
        }

        sb_newline(sb);
    }
    break;
    case IR_INS_CALL:
    {
        IR_Call* call = &instruction->call;
        String_View name = program->function_array.functions[call->function_index].name;
        sb_appendf(sb, "call %s\n", name.string->str);
    }
    break;
    case IR_INS_UNOP:
    {
        IR_UnOp* unop = &instruction->unop;

        IR_pretty_print_value(sb, &unop->value);
        sb_append(sb, " := ");
        switch(unop->operator)
        {
        case OP_SUB:
        {
            sb_append(sb, "-");
        }
        break;
        case OP_NOT:
        {
            sb_append(sb, "!");
        }
        break;
        default: IR_error("Unsupported operator for unary operation\n");
        }
        IR_pretty_print_value(sb, &unop->value);
        sb_append(sb, "");
        sb_newline(sb);
    }
    break;
    case IR_INS_COMPARE:
    {
        IR_Compare* compare = &instruction->compare;

        IR_pretty_print_register(sb, &compare->destination);
        sb_append(sb, " := ");
        IR_pretty_print_value(sb, &compare->left);

        switch(compare->operator)
        {
        case OP_OR:
        {
            sb_append(sb, " || ");
        }
        break;
        case OP_AND:
        {
            sb_append(sb, " && ");
        }
        break;
        case OP_LESS:
        {
            sb_append(sb, " < ");
        }
        break;
        case OP_GREATER:
        {
            sb_append(sb, " > ");
        }
        break;
        case OP_LESS_EQUAL:
        {
            sb_append(sb, " <= ");
        }
        break;
        case OP_GREATER_EQUAL:
        {
            sb_append(sb, " >= ");
        }
        break;
        case OP_EQUAL:
        {
            sb_append(sb, " == ");
        }
        break;
        case OP_NOT_EQUAL:
        {
            sb_append(sb, " != ");
        }
        break;
        default: IR_error("Unsupported operator for compare operation\n");
        }
        IR_pretty_print_location(sb, &compare->right);
        sb_newline(sb);
    }
    break;
    default: IR_error("IR pretty printer: Unhandled instruction %s", IR_instruction_type_to_string(instruction));
    break;
    }
}

String* IR_pretty_print(IR_Program* program, Allocator* allocator)
{
    String_Builder sb;
    sb_init(&sb, 256);





    for (i32 i = 0; i < program->block_array.count; i++)
    {
        IR_Block* block = &program->block_array.blocks[i];

        for (i32 j = 0; j < block->node_array.count; j++)
        {
            IR_Node* node = &block->node_array.nodes[j];

            switch(node->type)
            {
            case IR_NODE_FUNCTION_DECL:
            {
                IR_Function_Decl* fun = &node->function;
                if(fun->export)
                {
                    sb_append(&sb, "export ");
                }
                sb_appendf(&sb, "fun %s()\n", fun->name->str);
            }
            break;
            case IR_NODE_LABEL:
            {
                IR_Label* label = &node->label;
                sb_appendf(&sb, "%s:", label->label_name->str);
                sb_newline(&sb);
            }
            break;
            case IR_NODE_INSTRUCTION:
            {
                IR_Instruction* instruction = &node->instruction;
                IR_pretty_print_instruction(&sb, instruction, program);
            }
            break;
            }
        }
    }

    return sb_get_result(&sb, allocator);
}
# 59 "src/main.c" 2
# 1 "src/codegen_x64.c" 1
static void scratch_table_init(Scratch_Register_Table* table)
{
    table->inuse_table[SCRATCH_RBX] = 
# 3 "src/codegen_x64.c" 3 4
                                     0
# 3 "src/codegen_x64.c"
                                          ;
    table->inuse_table[SCRATCH_R10] = 
# 4 "src/codegen_x64.c" 3 4
                                     0
# 4 "src/codegen_x64.c"
                                          ;
    table->inuse_table[SCRATCH_R11] = 
# 5 "src/codegen_x64.c" 3 4
                                     0
# 5 "src/codegen_x64.c"
                                          ;
    table->inuse_table[SCRATCH_R12] = 
# 6 "src/codegen_x64.c" 3 4
                                     0
# 6 "src/codegen_x64.c"
                                          ;
    table->inuse_table[SCRATCH_R13] = 
# 7 "src/codegen_x64.c" 3 4
                                     0
# 7 "src/codegen_x64.c"
                                          ;
    table->inuse_table[SCRATCH_R14] = 
# 8 "src/codegen_x64.c" 3 4
                                     0
# 8 "src/codegen_x64.c"
                                          ;
    table->inuse_table[SCRATCH_R15] = 
# 9 "src/codegen_x64.c" 3 4
                                     0
# 9 "src/codegen_x64.c"
                                          ;
}

static Scratch_Register scratch_alloc(Scratch_Register_Table* table)
{
    for (i32 i = 0; i < SCRATCH_COUNT; i++)
    {
        if (!table->inuse_table[i])
        {
            table->inuse_table[i] = 
# 18 "src/codegen_x64.c" 3 4
                                   1
# 18 "src/codegen_x64.c"
                                       ;
            return i;
        }
    }
    
# 22 "src/codegen_x64.c" 3 4
   ((void) sizeof ((
# 22 "src/codegen_x64.c"
   "No available scratch registers" && 
# 22 "src/codegen_x64.c" 3 4
   0) ? 1 : 0), __extension__ ({ if (
# 22 "src/codegen_x64.c"
   "No available scratch registers" && 
# 22 "src/codegen_x64.c" 3 4
   0) ; else __assert_fail (
# 22 "src/codegen_x64.c"
   "\"No available scratch registers\" && false"
# 22 "src/codegen_x64.c" 3 4
   , "src/codegen_x64.c", 22, __extension__ __PRETTY_FUNCTION__); }))
# 22 "src/codegen_x64.c"
                                                    ;
    return -1;
}

static void scratch_free(Scratch_Register_Table* table, Scratch_Register reg)
{
    table->inuse_table[reg] = 
# 28 "src/codegen_x64.c" 3 4
                             0
# 28 "src/codegen_x64.c"
                                  ;
}

static i32 hash_int(i32 a)
{
      a ^= (a << 13);
      a ^= (a >> 17);
      a ^= (a << 5);
      return a;
}

static void temp_table_init(Temp_Table* table)
{
    table->count = 0;
    table->capacity = 0;
    table->entries = 
# 43 "src/codegen_x64.c" 3 4
                     ((void *)0)
# 43 "src/codegen_x64.c"
                         ;
    table->keys = 
# 44 "src/codegen_x64.c" 3 4
                     ((void *)0)
# 44 "src/codegen_x64.c"
                         ;
}

static i32 temp_table_find_entry(i32* keys, Scratch_Register* entries, i32 capacity, i32 key)
{
    i32 index = hash_int(key) % capacity;
    i32 tombstone = -1;
    for (;;)
    {
        i32 found_key = keys[index];
        if (found_key == -1)
        {
            if (entries[index] == SCRATCH_COUNT)
            {
                return tombstone != -1 ? tombstone : index;
            }
            else
            {
                if (tombstone == -1) tombstone = index;
            }
        }
        else if (found_key == key)
        {
            return index;
        }

        index = (index + 1) % capacity;
    }
}


static void temp_table_adjust_capacity(Temp_Table* table, i32 capacity)
{
    i32 *new_keys = malloc(sizeof(i32) * capacity);
    Scratch_Register* new_entries = malloc(sizeof(Scratch_Register) * capacity);

    for (i32 i = 0; i < capacity; i++)
    {
        new_keys[i] = -1;
        new_entries[i] = SCRATCH_COUNT;
    }

    table->count = 0;
    for (i32 i = 0; i < table->capacity; i++)
    {
        i32 old_key = table->keys[i];
        Scratch_Register old_reg = table->entries[i];

        if (old_reg == SCRATCH_COUNT) continue;

        i32 index = temp_table_find_entry(new_keys, new_entries, capacity, old_key);
        new_keys[index] = table->keys[i];
        new_entries[index] = table->entries[i];
        table->count++;
    }

    table->capacity = capacity;
    table->entries = new_entries;
    table->keys = new_keys;
}

static 
# 105 "src/codegen_x64.c" 3 4
      _Bool 
# 105 "src/codegen_x64.c"
           temp_table_set(Temp_Table *table, i32 key, Scratch_Register reg)
{
    if (table->count + 1 > table->capacity * 0.75f)
    {
        i32 capacity = table->capacity < 8 ? 8 : table->capacity * 2;
        temp_table_adjust_capacity(table, capacity);
    }

    i32 index = temp_table_find_entry(table->keys, table->entries, table->capacity, key);
    
# 114 "src/codegen_x64.c" 3 4
   _Bool 
# 114 "src/codegen_x64.c"
        new_entry = table->entries[index] == SCRATCH_COUNT;
    if (new_entry && table->entries[index] == SCRATCH_COUNT) table->count++;

    table->keys[index] = key;
    table->entries[index] = reg;
    return new_entry;
}

static 
# 122 "src/codegen_x64.c" 3 4
      _Bool 
# 122 "src/codegen_x64.c"
           temp_table_get(Temp_Table* table, i32 key, Scratch_Register* reg)
{
    if (table->count == 0) return 
# 124 "src/codegen_x64.c" 3 4
                                 0
# 124 "src/codegen_x64.c"
                                      ;

    i32 index = temp_table_find_entry(table->keys, table->entries, table->capacity, key);
    if (table->entries[index] == SCRATCH_COUNT) return 
# 127 "src/codegen_x64.c" 3 4
                                                      0
# 127 "src/codegen_x64.c"
                                                           ;

    *reg = table->entries[index];
    return 
# 130 "src/codegen_x64.c" 3 4
          1
# 130 "src/codegen_x64.c"
              ;
}

static 
# 133 "src/codegen_x64.c" 3 4
      _Bool 
# 133 "src/codegen_x64.c"
           temp_table_delete(Temp_Table* table, i32 key)
{
    if (table->count == 0) return 
# 135 "src/codegen_x64.c" 3 4
                                 0
# 135 "src/codegen_x64.c"
                                      ;

    i32 index = temp_table_find_entry(table->keys, table->entries, table->capacity, key);
    if (table->entries[index] == SCRATCH_COUNT) return 
# 138 "src/codegen_x64.c" 3 4
                                                      0
# 138 "src/codegen_x64.c"
                                                           ;

    table->keys[index] = -1;
    table->entries[index] = SCRATCH_RBX;

    return 
# 143 "src/codegen_x64.c" 3 4
          1
# 143 "src/codegen_x64.c"
              ;
}

static Scratch_Register get_or_add_scratch_from_temp(Temp_Table* table, IR_Register ir_register, Scratch_Register_Table* scratch_table)
{
    i32 key = ir_register.gpr_index;
    Scratch_Register scratch_register;
    if (!temp_table_get(table, key, &scratch_register))
    {
        scratch_register = scratch_alloc(scratch_table);
        temp_table_set(table, key, scratch_register);
    }

    return scratch_register;
}

static void free_temp_scratch(Temp_Table* table, IR_Register ir_register, Scratch_Register_Table* scratch_table)
{
    i32 key = ir_register.gpr_index;
    Scratch_Register scratch_register = get_or_add_scratch_from_temp(table, ir_register, scratch_table);
    temp_table_delete(table, key);
    scratch_free(scratch_table, scratch_register);
}

static const char* instruction_name(Instruction instruction, Register dst_reg)
{




    Reg_Size size = register_sizes[dst_reg];
    switch(instruction)
    {
    case INS_MOV:
    {
        switch(size)
        {
        case REG_SIZE_BYTE: return "mov" "b";
        case REG_SIZE_WORD: return "mov" "w";
        case REG_SIZE_LONG: return "mov" "l";
        case REG_SIZE_QUAD: return "mov" "q";
        default: compiler_bug("Should not happen.");
        }
    }
    case INS_PUSH:
    {
        switch(size)
        {
        case REG_SIZE_BYTE: return "push" "b";
        case REG_SIZE_WORD: return "push" "w";
        case REG_SIZE_LONG: return "push" "l";
        case REG_SIZE_QUAD: return "push" "q";
        default: compiler_bug("Should not happen.");
        }
    }
    case INS_POP:
    {
        switch(size)
        {
        case REG_SIZE_BYTE: return "pop" "b";
        case REG_SIZE_WORD: return "pop" "w";
        case REG_SIZE_LONG: return "pop" "l";
        case REG_SIZE_QUAD: return "pop" "q";
        default: compiler_bug("Should not happen.");
        }
    }
    case INS_ADD:
    {
        switch(size)
        {
        case REG_SIZE_BYTE: return "add" "b";
        case REG_SIZE_WORD: return "add" "w";
        case REG_SIZE_LONG: return "add" "l";
        case REG_SIZE_QUAD: return "add" "q";
        default: compiler_bug("Should not happen.");
        }
    }
    case INS_SUB:
    {
        switch(size)
        {
        case REG_SIZE_BYTE: return "sub" "b";
        case REG_SIZE_WORD: return "sub" "w";
        case REG_SIZE_LONG: return "sub" "l";
        case REG_SIZE_QUAD: return "sub" "q";
        default: compiler_bug("Should not happen.");
        }
    }
    case INS_MUL:
    {
        switch(size)
        {
        case REG_SIZE_BYTE: return "imul" "b";
        case REG_SIZE_WORD: return "imul" "w";
        case REG_SIZE_LONG: return "imul" "l";
        case REG_SIZE_QUAD: return "imul" "q";
        default: compiler_bug("Should not happen.");
        }
    }
    case INS_DIV:
    {
        switch(size)
        {
        case REG_SIZE_BYTE: return "idiv" "b";
        case REG_SIZE_WORD: return "idiv" "w";
        case REG_SIZE_LONG: return "idiv" "l";
        case REG_SIZE_QUAD: return "idiv" "q";
        default: compiler_bug("Should not happen.");
        }
    }
    case INS_CMP:
    {
        switch(size)
        {
        case REG_SIZE_BYTE: return "cmp" "b";
        case REG_SIZE_WORD: return "cmp" "w";
        case REG_SIZE_LONG: return "cmp" "l";
        case REG_SIZE_QUAD: return "cmp" "q";
        default: compiler_bug("Should not happen.");
        }
    }
    case INS_RET:
    {
        return "ret";
    }
    case INS_NEG:
    {
        switch(size)
        {
        case REG_SIZE_BYTE: return "neg" "b";
        case REG_SIZE_WORD: return "neg" "w";
        case REG_SIZE_LONG: return "neg" "l";
        case REG_SIZE_QUAD: return "neg" "q";
        default: compiler_bug("Should not happen.");
        }
    }
    case INS_CQO:
    {
        return "cqo";
    }
    case INS_XOR:
    {
        switch(size)
        {
        case REG_SIZE_BYTE: return "xor" "b";
        case REG_SIZE_WORD: return "xor" "w";
        case REG_SIZE_LONG: return "xor" "l";
        case REG_SIZE_QUAD: return "xor" "q";
        default: compiler_bug("Should not happen.");
        }
    }
    case INS_CALL:
    {
        return "call";
    }
    default: compiler_bug("Invalid instruction.");

    }


    return 
# 303 "src/codegen_x64.c" 3 4
          ((void *)0)
# 303 "src/codegen_x64.c"
              ;
}

const char instruction_suffix[REG_SIZE_COUNT] =
{
    [REG_SIZE_BYTE] = 'b',
    [REG_SIZE_WORD] = 'w',
    [REG_SIZE_LONG] = 'l',
    [REG_SIZE_QUAD] = 'q',
};

static Register scratch_to_register(Scratch_Register reg)
{
    switch(reg)
    {
    case SCRATCH_RBX:
    return REG_RBX;
    case SCRATCH_R10:
    return REG_R10;
    case SCRATCH_R11:
    return REG_R11;
    case SCRATCH_R12:
    return REG_R12;
    case SCRATCH_R13:
    return REG_R13;
    case SCRATCH_R14:
    return REG_R14;
    case SCRATCH_R15:
    return REG_R15;
    default: compiler_bug("Invalid scratch register.");
    }

    
# 335 "src/codegen_x64.c" 3 4
   ((void) sizeof ((0 
# 335 "src/codegen_x64.c"
   && "Should not happend."
# 335 "src/codegen_x64.c" 3 4
   ) ? 1 : 0), __extension__ ({ if (0 
# 335 "src/codegen_x64.c"
   && "Should not happend."
# 335 "src/codegen_x64.c" 3 4
   ) ; else __assert_fail (
# 335 "src/codegen_x64.c"
   "false && \"Should not happend.\""
# 335 "src/codegen_x64.c" 3 4
   , "src/codegen_x64.c", 335, __extension__ __PRETTY_FUNCTION__); }))
# 335 "src/codegen_x64.c"
                                         ;
}

i32 label_count = 0;
i32 label_create()
{
    return label_count++;
}

String* label_name(i32 label, Allocator* allocator)
{
    return string_createf(allocator, ".L%d", label);
}

void X64_emit_label(String_Builder* sb, const char* label)
{
    sb_appendf(sb, "%s:\n", label);
}

void X64_emit_add(String_Builder* sb, Register src, Register dst)
{
    sb_indent(sb, 4);



    sb_appendf(sb, "%s     %s, %s\n", instruction_name(INS_ADD, dst), register_names[src], register_names[dst]);

}

void X64_emit_sub(String_Builder* sb, Register src, Register dst)
{
    sb_indent(sb, 4);



    sb_appendf(sb, "%s     %s, %s\n", instruction_name(INS_SUB, dst), register_names[src], register_names[dst]);

}

void X64_emit_mul(String_Builder* sb, Register src, Register dst)
{
    X64_emit_move_reg_to_reg(sb, src, REG_RAX);

    sb_indent(sb, 4);




    const char* ins = instruction_name(INS_MUL, dst);


    sb_appendf(sb, "%s    %s\n", ins, register_names[dst]);

    X64_emit_move_reg_to_reg(sb, REG_RAX, dst);
}

void X64_emit_div(String_Builder* sb, Register src, Register dst)
{
    X64_emit_move_reg_to_reg(sb, src, REG_RAX);

    sb_indent(sb, 4);





    const char* ins_cqo = instruction_name(INS_CQO, REG_RAX);
    const char* ins_div = instruction_name(INS_DIV, dst);


    sb_appendf(sb, "%s\n", ins_cqo);

    sb_indent(sb, 4);
    sb_appendf(sb, "%s    %s\n", ins_div, register_names[dst]);

    X64_emit_move_reg_to_reg(sb, REG_RAX, dst);

}

static char literal_prefix()
{



    return '$';

    return ' ';
}

void X64_emit_cmp_lit_to_loc(String_Builder* sb, i32 lhs, IR_Location rhs, Scratch_Register_Table* table, Temp_Table* temp_table)
{
    sb_indent(sb, 4);

    
# 428 "src/codegen_x64.c" 3 4
   ((void) sizeof ((
# 428 "src/codegen_x64.c"
   rhs.type == IR_LOCATION_REGISTER
# 428 "src/codegen_x64.c" 3 4
   ) ? 1 : 0), __extension__ ({ if (
# 428 "src/codegen_x64.c"
   rhs.type == IR_LOCATION_REGISTER
# 428 "src/codegen_x64.c" 3 4
   ) ; else __assert_fail (
# 428 "src/codegen_x64.c"
   "rhs.type == IR_LOCATION_REGISTER"
# 428 "src/codegen_x64.c" 3 4
   , "src/codegen_x64.c", 428, __extension__ __PRETTY_FUNCTION__); }))
# 428 "src/codegen_x64.c"
                                           ;
    Scratch_Register s_right_reg = get_or_add_scratch_from_temp(temp_table, rhs.reg, table);
    Register right_reg = scratch_to_register(s_right_reg);




    sb_appendf(sb, "%s     %c%d, %s\n", instruction_name(INS_CMP, right_reg), literal_prefix(), lhs, register_names[right_reg]);

}

void X64_emit_cmp_loc_to_loc(String_Builder* sb, IR_Location lhs, IR_Location rhs, Scratch_Register_Table* table, Temp_Table* temp_table)
{
    sb_indent(sb, 4);

    
# 443 "src/codegen_x64.c" 3 4
   ((void) sizeof ((
# 443 "src/codegen_x64.c"
   lhs.type == IR_LOCATION_REGISTER && rhs.type == IR_LOCATION_REGISTER
# 443 "src/codegen_x64.c" 3 4
   ) ? 1 : 0), __extension__ ({ if (
# 443 "src/codegen_x64.c"
   lhs.type == IR_LOCATION_REGISTER && rhs.type == IR_LOCATION_REGISTER
# 443 "src/codegen_x64.c" 3 4
   ) ; else __assert_fail (
# 443 "src/codegen_x64.c"
   "lhs.type == IR_LOCATION_REGISTER && rhs.type == IR_LOCATION_REGISTER"
# 443 "src/codegen_x64.c" 3 4
   , "src/codegen_x64.c", 443, __extension__ __PRETTY_FUNCTION__); }))
# 443 "src/codegen_x64.c"
                                                                               ;
    Scratch_Register s_left_reg = get_or_add_scratch_from_temp(temp_table, lhs.reg, table);
    Scratch_Register s_right_reg = get_or_add_scratch_from_temp(temp_table, rhs.reg, table);

    Register left_reg = scratch_to_register(s_left_reg);
    Register right_reg = scratch_to_register(s_right_reg);




    sb_appendf(sb, "%s     %s, %s\n", instruction_name(INS_CMP, right_reg), register_names[right_reg], register_names[left_reg]);

}

void X64_emit_cmp_reg_to_reg(String_Builder* sb, Register s_lhs, Register s_rhs, IR_Op operator)
{
    Register lhs = scratch_to_register(s_lhs);
    Register rhs = scratch_to_register(s_rhs);

    X64_emit_move_reg_to_reg(sb, lhs, REG_RAX);

    sb_indent(sb, 4);




    sb_appendf(sb, "%s     %s, %s\n", instruction_name(INS_CMP, REG_RAX), register_names[rhs], register_names[REG_RAX]);

}

void X64_emit_setcc(String_Builder* sb, IR_Op operator, Register result_reg)
{
    sb_indent(sb, 4);

    char* instruction = 
# 477 "src/codegen_x64.c" 3 4
                       ((void *)0)
# 477 "src/codegen_x64.c"
                           ;
    switch(operator)
    {
    case OP_NOT_EQUAL:
    {
        instruction = "setne";
    }
    break;
    case OP_EQUAL:
    {
        instruction = "sete ";
    }
    break;
    case OP_OR:
    {
        not_implemented("Binary or (||)");
    }
    break;
    case OP_AND:
    {
        not_implemented("Binary and (&&)");
    }
    break;
    case OP_LESS:
    {
        instruction = "setl ";
    }
    break;
    case OP_GREATER:
    {
        instruction = "setg ";
    }
    break;
    case OP_LESS_EQUAL:
    {
        instruction = "setle";
    }
    break;
    case OP_GREATER_EQUAL:
    {
        instruction = "setge";
    }
    break;
    default: compiler_bug("Comparison: Invalid operator.");
    }

    sb_appendf(sb, "%s   %s\n", instruction, register_names[REG_AL]);

    X64_emit_move_reg_to_reg(sb, REG_AL, result_reg);
}

void X64_emit_unary(String_Builder* sb, Register src)
{
    sb_indent(sb, 4);
    sb_appendf(sb, "%s     %s\n", instruction_name(INS_NEG, src), register_names[src]);
}

void X64_emit_move_reg_to_reg(String_Builder* sb, Register src, Register dst)
{
    sb_indent(sb, 4);



    sb_appendf(sb, "%s     %s, %s\n", instruction_name(INS_MOV, dst), register_names[src], register_names[dst]);

}

void X64_emit_move_reg_to_mem(String_Builder* sb, Register src, IR_Mem dst,
                              Scratch_Register_Table* table, Temp_Table* temp_table)
{
    not_implemented("x86: Move reg to mem");
}

void X64_emit_move_mem_to_reg(String_Builder* sb, IR_Mem src, Register dst,
                              Scratch_Register_Table* table, Temp_Table* temp_table)
{
    not_implemented("x86: Move mem to reg");
}

void X64_emit_move_mem_to_mem(String_Builder* sb, IR_Mem src, IR_Mem dst,
                              Scratch_Register_Table* table, Temp_Table* temp_table)
{
    not_implemented("x86: Move mem to mem");
}

void X64_emit_move_loc_to_loc(String_Builder* sb, IR_Location src, IR_Location dst,
                             Scratch_Register_Table* table, Temp_Table* temp_table)
{
    
# 565 "src/codegen_x64.c" 3 4
   ((void) sizeof ((
# 565 "src/codegen_x64.c"
   src.type == IR_LOCATION_REGISTER && dst.type == IR_LOCATION_REGISTER
# 565 "src/codegen_x64.c" 3 4
   ) ? 1 : 0), __extension__ ({ if (
# 565 "src/codegen_x64.c"
   src.type == IR_LOCATION_REGISTER && dst.type == IR_LOCATION_REGISTER
# 565 "src/codegen_x64.c" 3 4
   ) ; else __assert_fail (
# 565 "src/codegen_x64.c"
   "src.type == IR_LOCATION_REGISTER && dst.type == IR_LOCATION_REGISTER"
# 565 "src/codegen_x64.c" 3 4
   , "src/codegen_x64.c", 565, __extension__ __PRETTY_FUNCTION__); }))
# 565 "src/codegen_x64.c"
                                                                               ;
    if (src.type == IR_LOCATION_REGISTER)
    {
        Scratch_Register s_left_reg = get_or_add_scratch_from_temp(temp_table, src.reg, table);
        Register left_reg = scratch_to_register(s_left_reg);
        if (dst.type == IR_LOCATION_REGISTER)
        {
            Scratch_Register s_right_reg = get_or_add_scratch_from_temp(temp_table, src.reg, table);
            Register right_reg = scratch_to_register(s_right_reg);

            X64_emit_move_reg_to_reg(sb, left_reg, right_reg);
        }
        else if (dst.type == IR_LOCATION_MEMORY)
        {
            X64_emit_move_reg_to_mem(sb, left_reg, dst.mem, table, temp_table);
        }
    }
    else if (src.type == IR_LOCATION_MEMORY)
    {
        if (dst.type == IR_LOCATION_REGISTER)
        {
            Scratch_Register s_right_reg = get_or_add_scratch_from_temp(temp_table, dst.reg, table);
            Register right_reg = scratch_to_register(s_right_reg);

            X64_emit_move_mem_to_reg(sb, src.mem, right_reg, table, temp_table);
        }
        else if(dst.type == IR_LOCATION_MEMORY)
        {
            X64_emit_move_mem_to_mem(sb, src.mem, dst.mem, table, temp_table);
        }
    }
}

void X64_emit_move_lit_to_reg(String_Builder* sb, i32 num, Register dst)
{
    sb_indent(sb, 4);



    sb_appendf(sb, "%s     %c%d, %s\n", instruction_name(INS_MOV, dst), literal_prefix(), num, register_names[dst]);

}

void X64_emit_move(String_Builder* sb, IR_Move* move, IR_Program* program, Temp_Table* temp_table, Scratch_Register_Table* table)
{
    IR_Value* src = &move->src;
    IR_Location* dst = &move->dst;

    switch(src->type)
    {
    case VALUE_LOCATION:
    {
        if(dst->type == IR_LOCATION_REGISTER && src->loc.type == IR_LOCATION_REGISTER)
        {
            Scratch_Register src_reg = get_or_add_scratch_from_temp(temp_table, src->loc.reg, table);
            Scratch_Register dst_reg = get_or_add_scratch_from_temp(temp_table, dst->reg, table);
            X64_emit_move_reg_to_reg(sb, scratch_to_register(src_reg), scratch_to_register(dst_reg));
        }
    }
    break;
    case VALUE_INT:
    {
        if(dst->type == IR_LOCATION_REGISTER)
        {
            Scratch_Register reg = get_or_add_scratch_from_temp(temp_table, dst->reg, table);
            X64_emit_move_lit_to_reg(sb, src->integer, scratch_to_register(reg));
        }
    }
    break;
    case VALUE_VARIABLE:
    {

    }
    break;
    }
}

void X64_emit_instruction(String_Builder* sb, IR_Instruction* instruction, IR_Program* program, Temp_Table* temp_table, Scratch_Register_Table* table)
{
    switch(instruction->type)
    {
    case IR_INS_RET:
    {
        IR_Return* ret = &instruction->ret;
        if (ret->has_return_value)
        {
            Scratch_Register return_reg = get_or_add_scratch_from_temp(temp_table, ret->return_register, table);
            X64_emit_move_reg_to_reg(sb, scratch_to_register(return_reg), REG_RAX);
        }
        X64_emit_pop_reg(sb, REG_RBP);
        X64_emit_ret(sb);
    }
    break;
    case IR_INS_CALL:
    {
        IR_Call* call = &instruction->call;
        String_View* name = IR_get_function_name(program, call->function_index);
        X64_emit_call(sb, name->string->str);
    }
    break;
    case IR_INS_MOV:
    {
        IR_Move* move = &instruction->move;
        X64_emit_move(sb, move, program, temp_table, table);
    }
    break;
    case IR_INS_PUSH:
    {
        IR_Push* push = &instruction->push;
        IR_Value* value = &push->value;

        switch(value->type)
        {
        case VALUE_LOCATION:
        {
            Scratch_Register reg = get_or_add_scratch_from_temp(temp_table, value->loc.reg, table);
            X64_emit_push_reg(sb, scratch_to_register(reg));
        }
        break;
        case VALUE_VARIABLE:
        {

        }
        break;
        default: break;
        }
    }
    break;
    case IR_INS_POP:
    {
        IR_Pop* pop = &instruction->pop;
        IR_Value* value = &pop->value;

        switch(value->type)
        {
        case VALUE_LOCATION:
        {
            Scratch_Register reg = get_or_add_scratch_from_temp(temp_table, value->loc.reg, table);
            X64_emit_push_reg(sb, scratch_to_register(reg));
        }
        break;
        case VALUE_VARIABLE:
        {

        }
        break;
        default: break;
        }
    }
    break;
    case IR_INS_JUMP:
    {
        IR_Jump* jump = &instruction->jump;
        sb_indent(sb, 4);
        switch(jump->type)
        {
        case JMP_ALWAYS:
        {
            sb_append(sb, "jmp      ");
        }
        break;
        case JMP_EQUAL:
        {
            sb_append(sb, "je       ");
        }
        break;
        case JMP_ZERO:
        {
            sb_append(sb, "jz       ");
        }
        break;
        case JMP_NOT_EQUAL:
        {
            sb_append(sb, "jne      ");
        }
        break;
        case JMP_NOT_ZERO:
        {
            sb_append(sb, "jnz      ");
        }
        break;
        case JMP_LESS:
        {
            sb_append(sb, "jl       ");
        }
        break;
        case JMP_LESS_EQUAL:
        {
            sb_append(sb, "jle      ");
        }
        break;
        case JMP_GREATER:
        {
            sb_append(sb, "jg       ");
        }
        break;
        case JMP_GREATER_EQUAL:
        {
            sb_append(sb, "jge      ");
        }
        break;
        }

        IR_Block* block = IR_get_block(program, jump->address);
        IR_Node* node = IR_get_node(block, 0);
        IR_Label* label = &node->label;

        sb_appendf(sb, "%s\n", label->label_name->str);
    }
    break;
    case IR_INS_UNOP:
    {
        IR_UnOp* unop = &instruction->unop;
        IR_Value* value = &unop->value;

        IR_Register ir_reg = value->loc.reg;

        Scratch_Register s_reg = get_or_add_scratch_from_temp(temp_table, ir_reg, table);
        Register reg = scratch_to_register(s_reg);

        X64_emit_unary(sb, reg);
    }
    break;
    case IR_INS_BINOP:
    {
        IR_BinOp* binop = &instruction->binop;
        IR_Value* left = &binop->left;
        IR_Value* right = &binop->right;

        IR_Register ir_left_reg = left->loc.reg;
        IR_Register ir_right_reg = right->loc.reg;

        Scratch_Register s_left_reg = get_or_add_scratch_from_temp(temp_table, ir_left_reg, table);
        Scratch_Register s_right_reg = get_or_add_scratch_from_temp(temp_table, ir_right_reg, table);
        Register left_reg = scratch_to_register(s_left_reg);
        Register right_reg = scratch_to_register(s_right_reg);

        switch(binop->operator)
        {
        case OP_ADD:
        {
            X64_emit_add(sb, left_reg, right_reg);
        }
        break;
        case OP_SUB:
        {
            X64_emit_sub(sb, right_reg, left_reg);
            Register temp = right_reg;
            right_reg = left_reg;
            left_reg = temp;

            IR_Register temp_ir = ir_right_reg;
            ir_right_reg = ir_left_reg;
            ir_left_reg = temp_ir;
        }
        break;
        case OP_MUL:
        {
            X64_emit_mul(sb, left_reg, right_reg);
        }
        break;
        case OP_DIV:
        {
            X64_emit_div(sb, left_reg, right_reg);
        }
        break;
        case OP_BIT_OR:
        {}
        break;
        case OP_BIT_AND:
        {}
        break;
        case OP_ASSIGN:
        {}
        break;

        default: compiler_bug("Unsupported operator for binary operation."); break;
        }


    }
    break;
    case IR_INS_COMPARE:
    {
        IR_Compare* compare = &instruction->compare;

        switch(compare->operator)
        {
        case OP_EQUAL:
        case OP_OR:
        case OP_AND:
        case OP_LESS:
        case OP_GREATER:
        case OP_LESS_EQUAL:
        case OP_GREATER_EQUAL:
        case OP_NOT_EQUAL:
        break;
        default: compiler_bug("Unsupported operator for comparison operation."); break;
        }

        IR_Value left = compare->left;
        IR_Location right = compare->right;

        if(left.type == VALUE_INT)
        {
            X64_emit_cmp_lit_to_loc(sb, left.integer, right, table, temp_table);
        }
        else if (left.type == VALUE_LOCATION)
        {
            X64_emit_cmp_loc_to_loc(sb, left.loc, right, table, temp_table);
            free_temp_scratch(temp_table, left.loc.reg, table);
        }

        free_temp_scratch(temp_table, right.reg, table);
    }
    break;
    default: compiler_bug("Unhandled IR instruction, was %s", IR_instruction_type_to_string(instruction)); break;
    }
}

void X64_emit_ret(String_Builder* sb)
{
    sb_indent(sb, 4);
    sb_appendf(sb, "%s\n", instruction_name(INS_RET, REG_RAX));
}

void X64_emit_pop_reg(String_Builder* sb, Register reg)
{
    sb_indent(sb, 4);
    sb_appendf(sb, "%s     %s\n", instruction_name(INS_POP, reg), register_names[reg]);
}

void X64_emit_push_reg(String_Builder* sb, Register reg)
{
    sb_indent(sb, 4);
    sb_appendf(sb, "%s    %s\n", instruction_name(INS_PUSH, reg), register_names[reg]);
}

void X64_emit_asciz(String_Builder* sb, const char* name, const char* value)
{
    sb_appendf(sb, "%s:\n", name);
    sb_indent(sb, 4);
    sb_appendf(sb, ".asciz \"%s\"\n", value);
}

void X64_emit_call(String_Builder* sb, const char* function)
{
    sb_indent(sb, 4);
    sb_appendf(sb, "%s     %s\n", instruction_name(INS_CALL, REG_RAX), function);
}

void X64_emit_comment_line(String_Builder* sb, const char* comment)
{
    sb_indent(sb, 4);
    sb_appendf(sb, "# %s\n", comment);
}

void X64_emit_xor_reg_to_reg(String_Builder* sb, Register lhs, Register rhs)
{
    sb_indent(sb, 4);



    sb_appendf(sb, "%s     %s, %s\n", instruction_name(INS_XOR, rhs), register_names[lhs], register_names[rhs]);

}

void X64_emit_syscall(String_Builder* sb, Linux_Syscall syscall)
{
    X64_emit_move_lit_to_reg(sb, (i32)syscall, REG_RAX);
    sb_indent(sb, 4);
    sb_append(sb, "syscall\n");
}

void X64_emit_exit_syscall(String_Builder* sb)
{
    X64_emit_move_reg_to_reg(sb, REG_RAX, REG_RDI);
    X64_emit_move_lit_to_reg(sb, LINUX_SC_EXIT, REG_RAX);

    sb_indent(sb, 4);
    sb_append(sb, "syscall\n");
}

void X64_emit_start(String_Builder* sb)
{
    sb_append(sb, ".global _start\n");

    sb_append(sb, ".text\n");

    X64_emit_label(sb, "_start");

    X64_emit_xor_reg_to_reg(sb, REG_RBP, REG_RBP);

    X64_emit_call(sb, "main");

    X64_emit_move_reg_to_reg(sb, REG_RAX, REG_RDI);

    X64_emit_syscall(sb, LINUX_SC_EXIT);
}

String* X64_codegen_ir(IR_Program* program, Allocator* allocator)
{
    String_Builder sb;
    sb_init(&sb, 256);

    Scratch_Register_Table table;
    scratch_table_init(&table);

    Temp_Table temp_table;
    temp_table_init(&temp_table);





    for (i32 i = 0; i < program->function_array.count; i++)
    {
        IR_Function function = program->function_array.functions[i];
        if (function.exported)
        {
            String_View name = program->function_array.functions[i].name;
            sb_appendf(&sb, ".global %s\n", name.string->str);
        }
    }

    X64_emit_start(&sb);

    for (i32 i = 0; i < program->block_array.count; i++)
    {
        IR_Block* block = &program->block_array.blocks[i];

        for (i32 j = 0; j < block->node_array.count; j++)
        {
            IR_Node* node = &block->node_array.nodes[j];

            switch(node->type)
            {
            case IR_NODE_FUNCTION_DECL:
            {
                IR_Function_Decl* fun = &node->function;
                sb_appendf(&sb, "%s:\n", fun->name->str);

                X64_emit_push_reg(&sb, REG_RBP);
                X64_emit_move_reg_to_reg(&sb, REG_RSP, REG_RBP);
            }
            break;
            case IR_NODE_LABEL:
            {
                X64_emit_label(&sb, node->label.label_name->str);
            }
            break;
            case IR_NODE_INSTRUCTION:
            {
                IR_Instruction* instruction = &node->instruction;
                X64_emit_instruction(&sb, instruction, program, &temp_table, &table);
            }
            break;
            }
        }
    }

    String* assembly = sb_get_result(&sb, allocator);
    return assembly;
}
# 60 "src/main.c" 2
# 1 "src/compiler.c" 1

# 1 "src/compiler.c" 3 4
_Bool 
# 1 "src/compiler.c"
    has_flag(Compiler_Options options, int flag)
{
    return options & flag;
}


# 6 "src/compiler.c" 3 4
_Bool 
# 6 "src/compiler.c"
    is_source_file(String* string)
{
    return string_ends_with_cstr(string, ".ske");
}

static void print_help()
{
    printf("Usage: ske [options] file...\n\n");
    printf("Options\n");

    printf("  --h or -help            Display this information\n");
    printf("  -outfile <file>         Place the output into <file>\n");
    printf("  -assembly               Output assembly.\n");
    printf("  -compile                Compile and assemble, but do not link\n");
    printf("  -tokenizer              Tokenize and output tokens\n");
    printf("  -parser                 Parse and output AST\n");
    printf("  -ir                     Generate IR and output\n");
}

Compiler_Arguments parse_args(int argc, char** argv, Allocator* allocator)
{
    Compiler_Arguments arguments;
    arguments.options = OPT_NONE;
    arguments.input_file = 
# 29 "src/compiler.c" 3 4
                          ((void *)0)
# 29 "src/compiler.c"
                              ;
    arguments.out_path = 
# 30 "src/compiler.c" 3 4
                        ((void *)0)
# 30 "src/compiler.c"
                            ;

    for (i32 i = 1; i < argc; i++)
    {
        char* arg = argv[i];
        String string = string_create(arg);

        if (string.length >= 2)
        {
            if (string_equal_cstr(&string, "--t") || string_equal_cstr(&string, "-test"))
            {
                printf("Running tests...\n");


            }
            else if (string_equal_cstr(&string, "-outfile"))
            {
                if(argc < i + 1)
                {
                    printf("No output file path provided for '%s' argument. Please provide a valid argument\n", string.str);
                    break;
                }
                arguments.out_path = string_allocate(argv[i + 1], allocator);
                i++;
            }
            else if (string_equal_cstr(&string, "-assembly"))
            {
                arguments.options |= OPT_ASSEMBLY_OUTPUT;
            }
            else if (string_equal_cstr(&string, "-tokenize"))
            {
                arguments.options |= OPT_TOK_OUTPUT;
            }
            else if (string_equal_cstr(&string, "-ir"))
            {
                arguments.options |= OPT_IR_OUTPUT;
            }
            else if (string_equal_cstr(&string, "-parser"))
            {
                arguments.options |= OPT_AST_OUTPUT;
            }
            else if (string_equal_cstr(&string, "--h") || string_equal_cstr(&string, "-help"))
            {
                print_help();
            }
            else if (is_source_file(&string))
            {
                arguments.input_file = string_copy(&string, allocator);
                char buf[128];
                String full_path = { .length = 128, .str = buf};
                if (!absolute_path(&string, &full_path))
                {
                    fprintf(
# 82 "src/compiler.c" 3 4
                           stderr
# 82 "src/compiler.c"
                                 , "\x1b[1;37mInvalid input path: \x1b[0m%s\n", string.str);
                }
                else
                {
                    arguments.absolute_path = string_copy(&full_path, allocator);
                }
            }
            else
            {
                printf("Unknown argument '%s'. Try --h or -help to see available options.\n", arg);
                print_help();
                break;
            }
        }
    }

    return arguments;
}


# 101 "src/compiler.c" 3 4
_Bool 
# 101 "src/compiler.c"
    Compiler_assemble_x86_with_input_file(String* file_path, String* output_path, Allocator* allocator)
{
    char *cmd[] = {"as", "-g", "-c", file_path->str, "-o", output_path->str, 
# 103 "src/compiler.c" 3 4
                                                                            ((void *)0)
# 103 "src/compiler.c"
                                                                                };
    return run_subprocess(cmd);
}


# 107 "src/compiler.c" 3 4
_Bool 
# 107 "src/compiler.c"
    Compiler_link(String* input_file_path, String* output_file_path, Allocator* allocator)
{
    char *cmd[] = {"ld", "-o", output_file_path->str, "-dynamic-linker", "/lib64/ld-linux-x86-64.so.2", "-lc", input_file_path->str, "-lm", "-no-pie", 
# 109 "src/compiler.c" 3 4
                                                                                                                                                      ((void *)0)
# 109 "src/compiler.c"
                                                                                                                                                          };
    return run_subprocess(cmd);
}


# 113 "src/compiler.c" 3 4
_Bool 
# 113 "src/compiler.c"
    Compiler_compile(String* source, Compiler_Arguments arguments, Allocator* allocator)
{
    if(source->length == 0)
    {
        compiler_bug("Empty input\n");
        return 
# 118 "src/compiler.c" 3 4
              0
# 118 "src/compiler.c"
                   ;
    }
    String* out_path = arguments.out_path;
    Token_List* tokens = Lex_tokenize(source, arguments.input_file, arguments.absolute_path);

    if (has_flag(arguments.options, OPT_TOK_OUTPUT))
    {
        String* tok_out = Lex_pretty_print(tokens, allocator);
        if (out_path)
        {
            FILE* temp_file = fopen(out_path->str, "w");
            if (!temp_file)
            {
                fprintf(
# 131 "src/compiler.c" 3 4
                       stderr
# 131 "src/compiler.c"
                             , "Unable to open temp file: %s\n", out_path->str);
                exit(1);
            }

            string_write_to_file(tok_out, temp_file);
            fclose(temp_file);
        }
        else
        {
            fprintf(
# 140 "src/compiler.c" 3 4
                   stdout
# 140 "src/compiler.c"
                         , tok_out->str);
        }

        return 
# 143 "src/compiler.c" 3 4
              1
# 143 "src/compiler.c"
                  ;
    }

    Parser parser;
    Parser_init(&parser, arguments.absolute_path, tokens, allocator);

    
# 149 "src/compiler.c" 3 4
   _Bool 
# 149 "src/compiler.c"
        result = 
# 149 "src/compiler.c" 3 4
                 0
# 149 "src/compiler.c"
                      ;
    if (Parser_parse(&parser, 
# 150 "src/compiler.c" 3 4
                             0
# 150 "src/compiler.c"
                                  , allocator))
    {
        if (has_flag(arguments.options, OPT_AST_OUTPUT))
        {
            String* ast = pretty_print_ast(parser.root, allocator);
            if (out_path)
            {
                FILE* temp_file = fopen(out_path->str, "w");
                if (!temp_file)
                {
                    fprintf(
# 160 "src/compiler.c" 3 4
                           stderr
# 160 "src/compiler.c"
                                 , "Unable to open temp file: %s\n", out_path->str);
                    exit(1);
                }

                string_write_to_file(ast, temp_file);
                fclose(temp_file);
            }
            else
            {
                fprintf(
# 169 "src/compiler.c" 3 4
                       stdout
# 169 "src/compiler.c"
                             , ast->str);
            }
            return 
# 171 "src/compiler.c" 3 4
                  1
# 171 "src/compiler.c"
                      ;
        }
        IR_Program program = IR_translate_ast(parser.root, allocator);
        if (has_flag(arguments.options, OPT_IR_OUTPUT))
        {
            String* IR_out = IR_pretty_print(&program, allocator);
            if (out_path)
            {
                FILE* temp_file = fopen(out_path->str, "w");
                if (!temp_file)
                {
                    fprintf(
# 182 "src/compiler.c" 3 4
                           stderr
# 182 "src/compiler.c"
                                 , "Unable to open temp file: %s\n", out_path->str);
                    exit(1);
                }

                string_write_to_file(IR_out, temp_file);
                fclose(temp_file);
            }
            else
            {
                fprintf(
# 191 "src/compiler.c" 3 4
                       stdout
# 191 "src/compiler.c"
                             , IR_out->str);
            }
            return 
# 193 "src/compiler.c" 3 4
                  1
# 193 "src/compiler.c"
                      ;
        }

        String* assembly = X64_codegen_ir(&program, allocator);
        if (assembly)
        {
            if (has_flag(arguments.options, OPT_ASSEMBLY_OUTPUT))
            {
                if (out_path)
                {
                    FILE* temp_file = fopen(out_path->str, "w");
                    if (!temp_file)
                    {
                        fprintf(
# 206 "src/compiler.c" 3 4
                               stderr
# 206 "src/compiler.c"
                                     , "Unable to open temp file: %s\n", out_path->str);
                        exit(1);
                    }

                    string_write_to_file(assembly, temp_file);
                    fclose(temp_file);
                }
                else
                {

                    fwrite(assembly->str, 1, assembly->length, 
# 216 "src/compiler.c" 3 4
                                                              stdout
# 216 "src/compiler.c"
                                                                    );
                }
                return 
# 218 "src/compiler.c" 3 4
                      1
# 218 "src/compiler.c"
                          ;
            }
            else
            {
                out_path = create_temp_file(allocator);
            }

            if (out_path)
            {
                FILE* temp_file = fopen(out_path->str, "w");
                if (!temp_file)
                {
                    fprintf(
# 230 "src/compiler.c" 3 4
                           stderr
# 230 "src/compiler.c"
                                 , "Unable to open temp file: %s\n", out_path->str);
                    exit(1);
                }

                string_write_to_file(assembly, temp_file);
                fclose(temp_file);

                String* assembly_out = create_temp_file(allocator);
                result = Compiler_assemble_x86_with_input_file(out_path, assembly_out, allocator);

                if (!result)
                {
                    fprintf(
# 242 "src/compiler.c" 3 4
                           stderr
# 242 "src/compiler.c"
                                 , "Assembler failed\n");
                    exit(1);
                }

                if (!DEFAULT_EXECUTABLE_OUT_PATH)
                {
                    DEFAULT_EXECUTABLE_OUT_PATH = string_allocate("a.out", allocator);
                }

                String* executable_out = arguments.out_path ? arguments.out_path : DEFAULT_EXECUTABLE_OUT_PATH;

                result = Compiler_link(assembly_out, executable_out, allocator);

                if (!result)
                {
                    fprintf(
# 257 "src/compiler.c" 3 4
                           stderr
# 257 "src/compiler.c"
                                 , "Linking failed\n");
                    exit(1);
                }
            }
        }
    }
    else
    {
        exit(1);
    }

    Parser_free(&parser);
    token_list_free(tokens);

    return result;
}


# 274 "src/compiler.c" 3 4
_Bool 
# 274 "src/compiler.c"
    Compiler_compile_file(Compiler_Arguments arguments, Allocator* allocator)
{
    if (!arguments.input_file)
    {
        return 
# 278 "src/compiler.c" 3 4
              0
# 278 "src/compiler.c"
                   ;
    }

    FILE* file = fopen(arguments.input_file->str, "r");
    
# 282 "src/compiler.c" 3 4
   _Bool 
# 282 "src/compiler.c"
        result = 
# 282 "src/compiler.c" 3 4
                 0
# 282 "src/compiler.c"
                      ;
    if (file)
    {
        String* source = string_create_from_file_with_allocator(file, allocator);
        result = Compiler_compile(source, arguments, allocator);
        fclose(file);

    }
    return result;
}
# 61 "src/main.c" 2
# 1 "src/runtime.c" 1

void repl(Allocator* allocator)
{
    char str[1024];
    String buffer = string_create(str);
    for(;;)
    {
        printf("> ");

        if(!fgets(buffer.str, 1024, 
# 10 "src/runtime.c" 3 4
                                   stdin
# 10 "src/runtime.c"
                                        ))
        {
            printf("\n");
            break;
        }

        Compiler_Arguments args =
            {
                .options = OPT_NONE,
                .input_file = 
# 19 "src/runtime.c" 3 4
                             ((void *)0)
# 19 "src/runtime.c"
                                 ,
                .out_path = 
# 20 "src/runtime.c" 3 4
                             ((void *)0)
            
# 21 "src/runtime.c"
           };

        
# 23 "src/runtime.c" 3 4
       _Bool 
# 23 "src/runtime.c"
            result = Compiler_compile(&buffer, args, allocator);
        if (!result)
        {

            compiler_bug("Compilation failed with errors\n");
        }
    }
}
# 62 "src/main.c" 2



int main(int argc, char** argv)
{
    Arena base_allocator;
    size_t buffer_length = 1024 * 1024;
    void* base_buffer = malloc(buffer_length);
    arena_init(&base_allocator, base_buffer, buffer_length);

    Arena string_arena;
    size_t string_buffer_length = 1024 * 1024;
    void* string_buffer = malloc(string_buffer_length);
    arena_init(&string_arena, string_buffer, string_buffer_length);

    if(argc == 1)
    {
        repl((&(&base_allocator)->base_allocator));
    }
    else if(argc > 1)
    {
        Compiler_Arguments arguments = parse_args(argc, argv, (&(&string_arena)->base_allocator));

        if (arguments.input_file)
        {
            Compiler_compile_file(arguments, (&(&string_arena)->base_allocator));
        }
    }

    return 0;
}
