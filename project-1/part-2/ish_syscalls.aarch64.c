long ish_read(
		int file_descriptor,
		void *buffer,
		unsigned long buffer_size
	     )
{
	register long num __asm__("w8") = 63;

	register long arg1_or_res  __asm__("x0") = (long) file_descriptor;
	register long arg2 __asm__("x1") = (long) buffer;
	register long arg3 __asm__("x2") = (long) buffer_size;

	__asm__ __volatile__ (
			"svc #0"
			: "=r"(arg1_or_res)
			: "r"(num), "r"(arg1_or_res), "r"(arg2), "r"(arg3)
			: "cc", "memory"
			);

	return arg1_or_res;
}

int ish_chdir(const char *path)
{
	register long num __asm__("w8") = 49;

	register long arg1_or_res  __asm__("x0") = (long) path;

	__asm__ __volatile__ (
			"svc #0"
			: "=r"(arg1_or_res)
			: "r"(num), "r"(arg1_or_res)
			: "cc", "memory"
			);

	return (int)arg1_or_res;
}

void ish_exit(int status)
{
	register long num __asm__("w8") = 93;

	register long arg1_or_res  __asm__("x0") = (long) status;

	__asm__ __volatile__ (
			"svc #0"
			: "=r"(arg1_or_res)
			: "r"(num), "r"(arg1_or_res)
			: "cc", "memory"
			);
}

int ish_stat(const char *path, void *stat_result)
{
	register long num __asm__("w8") = 79;

	register long res  __asm__("x0");
	register long arg2 __asm__("x1") = (long) path;
	register long arg3 __asm__("x2") = (long) stat_result;

	__asm__ __volatile__ (
			"mov w3, #0x0\n\t"
			"mov w0, #0xffffff9c\n\t"
			"sxtw x0, w0\n\t"
			"sxtw x3, w3\n\t"
			"svc #0"
			: "=r"(res)
			: "r"(num), "r"(arg2), "r"(arg3)
			: "x3", "cc", "memory"
			);

	return (int) res;
}

int ish_open(const char *path, int flags)
{
	register long num __asm__("w8") = 56;

	register long res  __asm__("x0");
	register long arg2 __asm__("x1") = (long) path;
	register long arg3 __asm__("x2") = (long) flags;

	__asm__ __volatile__ (
			"mov x3, #0x0\n\t"
			"mov x0, #0xffffffffffffff9c\n\t"
			"svc #0"
			: "=r"(res)
			: "r"(num), "r"(arg2), "r"(arg3)
			: "x3", "cc", "memory"
			);

	return (int) res;
}

int ish_creat(const char *path, unsigned int mode)
{
	register long num __asm__("w8") = 56;

	register long res  __asm__("x0");
	register long arg2 __asm__("x1") = (long) path;
	register long arg3 __asm__("x2") = (long) 0x0001 | 0x0200 | 0x0400;
	register long arg4 __asm__("x3") = (long) mode;

	__asm__ __volatile__ (
			"mov x0, #0xffffffffffffff9c\n\t"
			"svc #0"
			: "=r"(res)
			: "r"(num), "r"(arg2), "r"(arg4), "r"(arg3)
			: "cc", "memory"
			);

	return (int) res;
}

int ish_dup2(int old_file_descriptor, int new_file_descriptor)
{
	register long num __asm__("w8") = 24;

	register long arg1_or_res __asm__("x0") = (long) old_file_descriptor;
	register long arg2 __asm__("x1") = (long) new_file_descriptor;
	register long arg3 __asm__("x2") = 0L;

	__asm__ __volatile__ (
			"svc #0"
			: "=r"(arg1_or_res)
			: "r"(num), "r"(arg1_or_res), "r"(arg2), "r"(arg3)
			: "x3", "cc", "memory"
			);

	return (int) arg1_or_res;
}

int ish_close(int file_descriptor)
{
	register long num __asm__("w8") = 57;

	register long arg1_or_res  __asm__("x0") = (long) file_descriptor;

	__asm__ __volatile__ (
			"svc #0"
			: "=r"(arg1_or_res)
			: "r"(num), "r"(arg1_or_res)
			: "cc", "memory"
			);

	return (int) arg1_or_res;

}

int ish_fork()
{
	register long num __asm__("w8") = 220;

	register long res __asm__("x0");
	register long arg2 __asm__("x1") = 0L;
	register long arg3 __asm__("x2") = 0L;
	register long arg4 __asm__("x3") = 0L;

	__asm__ __volatile__ (
			"mov x0, #0x11\n\t"
			"movk x0, #0x120, lsl #16\n\t"
			"mrs x4, tpidr_el0\n\t"
			"sub x4, x4, #0x670\n\t"
			"svc #0"
			: "=r"(res)
			: "r"(num), "r"(arg2), "r"(arg3), "r"(arg4)
			: "x4", "cc", "memory"
			);

	return (int) res;
}

int ish_execve(
		const char *path,
		char *const arguments[],
		char *const environment[]
	      )
{
	register long num __asm__("w8") = 221;

	register long arg1_or_res  __asm__("x0") = (long) path;
	register long arg2 __asm__("x1") = (long) arguments;
	register long arg3 __asm__("x2") = (long) environment;

	__asm__ __volatile__ (
			"svc #0"
			: "=r"(arg1_or_res)
			: "r"(num), "r"(arg1_or_res), "r"(arg2), "r"(arg3)
			: "cc", "memory"
			);

	return (int) arg1_or_res;

}

int ish_waitpid(int pid, int *status, int options)
{
	register long num __asm__("w8") = 260;

	register long arg1_or_res  __asm__("x0") = (long) pid;
	register long arg2 __asm__("x1") = (long) status;
	register long arg3 __asm__("x2") = (long) options;
	register long arg4 __asm__("x3") = 0L;

	__asm__ __volatile__ (
			"svc #0"
			: "=r"(arg1_or_res)
			: "r"(num), "r"(arg1_or_res), "r"(arg2), "r"(arg3), "r"(arg4)
			: "cc", "memory"
			);

	return (int) arg1_or_res;
}

long ish_write(
		int file_descriptor,
		const void *buffer,
		unsigned long buffer_size
	      )
{
	register long num __asm__("w8") = 64;

	register long arg1_or_res  __asm__("x0") = (long) file_descriptor;
	register long arg2 __asm__("x1") = (long) buffer;
	register long arg3 __asm__("x2") = (long) buffer_size;

	__asm__ __volatile__ (
			"svc #0"
			: "=r"(arg1_or_res)
			: "r"(num), "r"(arg1_or_res), "r"(arg2), "r"(arg3)
			: "cc", "memory"
			);

	return arg1_or_res;
}
