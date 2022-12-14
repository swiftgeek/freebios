#ifndef I386_STDDEF_H
#define I386_STDDEF_H

typedef long ptrdiff_t;
typedef unsigned long size_t;
typedef long ssize_t;

typedef int wchar_t;
typedef unsigned int wint_t;

#define NULL 0

#define offsetof(TYPE, MEMBER) ((size_t) &((TYPE *)0)->MEMBER)

#endif /* I386_STDDEF_H */
