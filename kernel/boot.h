#ifndef BOOT_BOOT_H
#define BOOT_BOOT_H

#define STACK_SIZE	1024	/* Minimum number of bytes for stack */

#ifndef __ASSEMBLY__

#ifndef _VA_LIST
typedef __builtin_va_list va_list;
#define _VA_LIST
#endif
#define va_start(ap, param) __builtin_va_start(ap, param)
#define va_end(ap)          __builtin_va_end(ap)
#define va_arg(ap, type)    __builtin_va_arg(ap, type)

typedef __signed__ char __s8;
typedef unsigned char __u8;

typedef __signed__ short __s16;
typedef unsigned short __u16;

typedef __signed__ int __s32;
typedef unsigned int __u32;

__extension__ typedef __signed__ long long __s64;
__extension__ typedef unsigned long long __u64;

typedef __s8  s8;
typedef __u8  u8;
typedef __s16 s16;
typedef __u16 u16;
typedef __s32 s32;
typedef __u32 u32;
typedef __s64 s64;
typedef __u64 u64;


/* bioscall.c */
struct biosregs {
	union {
		struct {
			u32 edi;
			u32 esi;
			u32 ebp;
			u32 _esp;
			u32 ebx;
			u32 edx;
			u32 ecx;
			u32 eax;
			u32 _fsgs;
			u32 _dses;
			u32 eflags;
		};
		struct {
			u16 di, hdi;
			u16 si, hsi;
			u16 bp, hbp;
			u16 _sp, _hsp;
			u16 bx, hbx;
			u16 dx, hdx;
			u16 cx, hcx;
			u16 ax, hax;
			u16 gs, fs;
			u16 es, ds;
			u16 flags, hflags;
		};
		struct {
			u8 dil, dih, edi2, edi3;
			u8 sil, sih, esi2, esi3;
			u8 bpl, bph, ebp2, ebp3;
			u8 _spl, _sph, _esp2, _esp3;
			u8 bl, bh, ebx2, ebx3;
			u8 dl, dh, edx2, edx3;
			u8 cl, ch, ecx2, ecx3;
			u8 al, ah, eax2, eax3;
		};
	};
};

/* Basic port I/O */
static inline void outb(u8 v, u16 port)
{
	asm volatile("outb %0,%1" : : "a" (v), "dN" (port));
}
static inline u8 inb(u16 port)
{
	u8 v;
	asm volatile("inb %1,%0" : "=a" (v) : "dN" (port));
	return v;
}

static inline u16 ds(void)
{
	u16 seg;
	asm("movw %%ds,%0" : "=rm" (seg));
	return seg;
}

struct gdt_ptr {
	u16 len;
	u32 ptr;
};

// /* printf.c */
// int sprintf(char *buf, const char *fmt, ...);
// int vsprintf(char *buf, const char *fmt, va_list args);
// int printf(const char *fmt, ...);


/* string.c */
// int strcmp(const char *str1, const char *str2);
// int strncmp(const char *cs, const char *ct, size_t count);
// size_t strnlen(const char *s, size_t maxlen);
// unsigned int atou(const char *s);
// unsigned long long simple_strtoull(const char *cp, char **endp, unsigned int base);
// size_t strlen(const char *s);
// char *strchr(const char *s, int c);

// /* tty.c */
// void puts(const char *);
// void putchar(int);
// int getchar(void);
// void kbd_flush(void);
// int getchar_timeout(void);

/* pm.c */
static void enable_a20_fast(void);
void go_to_protected_mode(void);
static inline void io_delay(void)
{
	const u16 DELAY_PORT = 0x80;
	asm volatile("outb %%al,%0" : : "dN" (DELAY_PORT));
}

#endif /* __ASSEMBLY__ */

#endif /* BOOT_BOOT_H */
