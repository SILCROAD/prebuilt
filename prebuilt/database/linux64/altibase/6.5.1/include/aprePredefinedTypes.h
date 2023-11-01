#ifndef _APRE_PREDEFINED_TYPES_H_
#define _APRE_PREDEFINED_TYPES_H_ 1

typedef unsigned int size_t;
typedef int ssize_t;
typedef unsigned int uint32_t;
typedef int int32_t;
#if defined(VC_WIN32) || defined(VC_WIN64) || defined(VC_WINCE)
typedef void wpthread_mutex_t;
struct dirent
{
    char d_name[MAX_PATH+1];
    size_t d_namlen;
    int d_type;
};

#else
typedef void pthread_mutex_t;
typedef unsigned int pthread_t;
typedef void pthread_attr_t;
typedef long int time_t;
struct timeval
{
    long tv_sec;
    long tv_usec;
};
struct timezone
{
    int tz_minuteswest;
    int tz_dsttime;
};

typedef int FILE;
typedef int DIR;
struct dirent
{
    long d_ino;long d_off;unsigned short d_reclen;char d_name[NAME_MAX+1];
};

struct stat
{
    unsigned long int    st_dev;
    unsigned long int    st_ino;
    unsigned int         st_mode;
    unsigned long int    st_nlink;
    unsigned int         st_uid;
    unsigned int         st_gid;
    unsigned long int    st_rdev;
    long int             st_size;
    long int             st_blksize;
    long int             st_blocks;
    long int             st_atime;
    long int             st_mtime;
    long int             st_ctime;
};
#endif /* defined(VC_WIN32) || defined(VC_WIN64) || defined(VC_WINCE) */

#endif /* _APRE_PREDEFINED_TYPES_H_ */
#ifndef _APRE_PREDEFINED_TYPES_H_
#define _APRE_PREDEFINED_TYPES_H_ 1

typedef unsigned int size_t;
typedef int ssize_t;
typedef unsigned int uint32_t;
typedef int int32_t;
#if defined(VC_WIN32) || defined(VC_WIN64) || defined(VC_WINCE)
typedef void wpthread_mutex_t;
struct dirent
{
    char d_name[MAX_PATH+1];
    size_t d_namlen;
    int d_type;
};

#else
typedef void pthread_mutex_t;
typedef unsigned int pthread_t;
typedef void pthread_attr_t;
typedef long int time_t;
struct timeval
{
    long tv_sec;
    long tv_usec;
};

typedef int FILE;
typedef int DIR;
struct dirent
{
    long d_ino;long d_off;unsigned short d_reclen;char d_name[NAME_MAX+1];
};

struct stat
{
    unsigned long int    st_dev;
    unsigned long int    st_ino;
    unsigned int         st_mode;
    unsigned long int    st_nlink;
    unsigned int         st_uid;
    unsigned int         st_gid;
    unsigned long int    st_rdev;
    long int             st_size;
    long int             st_blksize;
    long int             st_blocks;
    long int             st_atime;
    long int             st_mtime;
    long int             st_ctime;
};
#endif /* defined(VC_WIN32) || defined(VC_WIN64) || defined(VC_WINCE) */

#endif /* _APRE_PREDEFINED_TYPES_H_ */
