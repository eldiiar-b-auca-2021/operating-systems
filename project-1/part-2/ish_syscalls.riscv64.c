long ish_read(
		int file_descriptor,
		void *buffer,
		unsigned long buffer_size
	     )
{
	register long num __asm__("a7") = 63;

	register long arg1_or_res __asm__("a0") = (long) file_descriptor;
	register long arg2 __asm__("a1") = (long) buffer;
	register long arg3 __asm__("a2") = (long) buffer_size;

	__asm__ __volatile__ (
		"ecall"
		: "=r"(arg1_or_res)
		: "r"(num), "r"(arg1_or_res), "r"(arg2), "r"(arg3)
		: "cc", "memory"
	);

	return arg1_or_res;
}

int ish_chdir(const char *path)
{
	register long num __asm__("a7") = 49;

	register long arg1_or_res __asm__("a0") = (long) path;

	__asm__ __volatile__ (
		"ecall"
		: "=r"(arg1_or_res)
		: "r"(num), "r"(arg1_or_res)
		: "cc", "memory"
	);

	return (int) arg1_or_res;
}

void ish_exit(int status)
{
	register long num __asm__("a7") = 93;

	register long arg1_or_res __asm__("a0") = (long) status;

	__asm__ __volatile__ (
		"ecall"
		: "=r"(arg1_or_res)
		: "r"(num), "r"(arg1_or_res)
		: "cc", "memory"
	);
}

int ish_stat(const char *path, void *stat_result)
{
	register long num __asm__("a7") = 79;

	register long res __asm__("a0");
	register long arg2 __asm__("a1") = (long) path;
	register long arg3 __asm__("a2") = (long) stat_result;

	__asm__ __volatile__ (
		"li a3, 0\n\t"
		"li a0, -100\n\t"
		"ecall"
		: "=r"(res)
		: "r"(num), "r"(arg2), "r"(arg3)
		: "a3", "cc", "memory"
	);

	return (int) res;
}

int ish_open(const char *path, int flags)
{
	register long num __asm__("a7") = 56;

	register long res __asm__("a0");
	register long arg2 __asm__("a1") = (long) path;
	register long arg3 __asm__("a2") = (long) flags;

	__asm__ __volatile__ (
		"li a3, 0\n\t"
		"li a0, -100\n\t"
		"ecall"
		: "=r"(res)
		: "r"(num), "r"(arg2), "r"(arg3)
		: "a3", "cc", "memory"
	);

	return (int) res;
}

int ish_creat(const char *path, unsigned int mode)
{
	register long num __asm__("a7") = 56;

	register long res __asm__("a0");
	register long arg2 __asm__("a1") = (long) path;
	register long arg3 __asm__("a2") = (long) 0x40 | 0x1 | 0x200;
	register long arg4 __asm__("a3") = (long) mode;

	__asm__ __volatile__ (
		"li a0, -100\n\t"
		"ecall"
		: "=r"(res)
		: "r"(num), "r"(arg2), "r"(arg3), "r"(arg4)
		: "cc", "memory"
	);

	return (int) res;
}

int ish_dup2(int old_file_descriptor, int new_file_descriptor)
{
	register long num __asm__("a7") = 24;

	register long arg1_or_res __asm__("a0") = (long) old_file_descriptor;
	register long arg2 __asm__("a1") = (long) new_file_descriptor;
	register long arg3 __asm__("a2") = 0L;

	__asm__ __volatile__ (
		"ecall"
		: "=r"(arg1_or_res)
		: "r"(num), "r"(arg1_or_res), "r"(arg2), "r"(arg3)
		: "cc", "memory"
	);

	return (int) arg1_or_res;
}

int ish_close(int file_descriptor)
{
	register long num __asm__("a7") = 57;

	register long arg1_or_res __asm__("a0") = (long) file_descriptor;

	__asm__ __volatile__ (
		"ecall"
		: "=r"(arg1_or_res)
		: "r"(num), "r"(arg1_or_res)
		: "cc", "memory"
	);

	return (int) arg1_or_res;
}

int ish_fork()
{
	register long num __asm__("a7") = 220;

	register long res __asm__("a0");
	register long arg2 __asm__("a1") = 0L;
	register long arg3 __asm__("a2") = 0L;
	register long arg4 __asm__("a3") = 0L;

	__asm__ __volatile__ (
		"li a0, 0x11\n\t"
		"ori a0, a0, 0\n\t"
		"mv a4, tp\n\t"
		"addi a4, a4,-0x670\n\t"
		"ecall"
		: "=r"(res)
		: "r"(num), "r"(arg2), "r"(arg3), "r"(arg4)
		: "a4", "cc", "memory"
	);

	return (int) res;
}

int ish_execve(
		const char *path,
		char *const arguments[],
		char *const environment[]
	      )
{
	register long num __asm__("a7") = 221;

	register long arg1_or_res __asm__("a0") = (long) path;
	register long arg2 __asm__("a1") = (long) arguments;
	register long arg3 __asm__("a2") = (long) environment;

	__asm__ __volatile__ (
		"ecall"
		: "=r"(arg1_or_res)
		: "r"(num), "r"(arg1_or_res), "r"(arg2), "r"(arg3)
		: "cc", "memory"
	);

	return (int) arg1_or_res;
}

int ish_waitpid(int pid, int *status, int options)
{
	register long num __asm__("a7") = 260;

	register long arg1_or_res __asm__("a0") = (long) pid;
	register long arg2 __asm__("a1") = (long) status;
	register long arg3 __asm__("a2") = (long) options;
	register long arg4 __asm__("a3") = 0L;

	__asm__ __volatile__ (
		"ecall"
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
	register long num __asm__("a7") = 64;

	register long arg1_or_res __asm__("a0") = (long) file_descriptor;
	register long arg2 __asm__("a1") = (long) buffer;
	register long arg3 __asm__("a2") = (long) buffer_size;

	__asm__ __volatile__ (
		"ecall"
		: "=r"(arg1_or_res)
		: "r"(num), "r"(arg1_or_res), "r"(arg2), "r"(arg3)
		: "cc", "memory"
	);

	return arg1_or_res;
}
