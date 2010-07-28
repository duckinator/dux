#ifndef BEEF_H
#define BEEF_H
/*  beef.h - header for using the beef bootloader */
 
/*
   Copyright (C) 2010 Nick Markwell

   Permission is hereby granted, free of charge, to any person obtaining a copy
   of this software and associated documentation files (the "Software"), to deal
   in the Software without restriction, including without limitation the rights
   to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
   copies of the Software, and to permit persons to whom the Software is
   furnished to do so, subject to the following conditions:

   The above copyright notice and this permission notice shall be included in
   all copies or substantial portions of the Software.

   THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
   IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
   FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
   AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
   LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
   OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
   THE SOFTWARE.
 */

#define BEEF_BOOTLOADER_MAGIC 0xbadbeef5

/* I'm adding this in case nixeagle decides to use it later */
typedef struct beef_info
{
	unsigned long mem_lower;
	unsigned long mem_upper;
	unsigned long boot_device;
	unsigned long cmdline;
	unsigned long mmap_addr;
} beef_info_t;

#ifndef MULTIBOOT_H // This is the same as multiboot. Yay compatibility :D

/* memory map */
typedef struct memory_map
{
	unsigned long size;
	unsigned long base_addr_low;
	unsigned long base_addr_high;
	unsigned long length_low;
	unsigned long length_high;
	unsigned long type;
} memory_map_t;

#endif

#endif
