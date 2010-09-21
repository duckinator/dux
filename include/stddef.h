#ifndef STDDEF_H
#define STDDEF_H

#ifdef __x86_64
	// 8 bytes for 64bit
	typedef unsigned long int size_t;
#else
	// 4 bytes for 32bit
	typedef unsigned int size_t;
#endif

#endif /* end of include guard: STDDEF_H */
