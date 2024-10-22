long ish_read(
		int file_descriptor,
		void *buffer,
		unsigned long buffer_size
	     )
{
	long result;

	__asm__ __volatile__ (
			"syscall"
			: "=a"(result)
			: "a"(0), "D"(file_descriptor), "S"(buffer), "d"(buffer_size)
			: "rcx", "r11", "cc", "memory"
			);

	return result;
}

int ish_chdir(const char *path)
{
	int result;

	__asm__ __volatile__ (
			"syscall"
			: "=a"(result)
			: "a"(80), "D"(path)
			: "rcx", "r11", "cc", "memory"
			);	
	return result;
}

void ish_exit(int status)
{
	int result;

	__asm__ __volatile__ (
			"syscall"
			: "=a"(result)
			: "a"(60), "D"(status)
			:"rcx", "r11", "cc", "memory"
			);
}

int ish_stat(const char *path, void *stat_result)
{
	int result;

	__asm__ __volatile__ (
			"syscall"
			: "=a"(result)
			: "a"(4), "D"(path), "S"(stat_result)
			:"rcx", "r11", "cc", "memory"
			);

	return result;
}

int ish_open(const char *path, int flags)
{
	int result;

	__asm__ __volatile__ (
			"syscall"
			: "=a"(result)
			: "a"(2), "D"(path), "S"(flags)
			:"rcx", "r11", "cc", "memory"
			);

	return result;
}

int ish_creat(const char *path, unsigned int mode)
{
	int result;

	__asm__ __volatile__ (
			"syscall"
			: "=a"(result)
			: "a"(85), "D"(path), "S"(mode)
			:"rcx", "r11", "cc", "memory"
			);

	return result;
}

int ish_dup2(int old_file_descriptor, int new_file_descriptor)
{
	int result;

	__asm__ __volatile__ (
			"syscall"
			: "=a"(result)
			: "a"(33), "D"(old_file_descriptor), "S"(new_file_descriptor)
			:"rcx", "r11", "cc", "memory"
			);

	return result;
}

int ish_close(int file_descriptor)
{
	int result;

	__asm__ __volatile__ (
			"syscall"
			: "=a"(result)
			: "a"(3), "D"(file_descriptor)
			:"rcx", "r11", "cc", "memory"
			);

	return result;
}

int ish_fork()
{
	int result;
	
	__asm__ __volatile__ (
			"syscall"
			: "=a"(result)
			: "a"(57)
			:"rcx", "r11", "cc", "memory"
			);

	return result;
}

int ish_execve(
		const char *path,
		char *const arguments[],
		char *const environment[]
	      )
{
	int result;

	__asm__ __volatile__ (
			"syscall"
			: "=a"(result)
			: "a"(59), "D"(path), "S"(arguments), "d"(environment)
			:"rcx", "r11", "cc", "memory"
			);

	return result;

}

int ish_waitpid(int pid, int *status, int options)
{
	int  result;

	register long arg4 __asm__("r10") = 0L;
	__asm__ __volatile__ (
			"mov $0, %%rax\n\t"
			"syscall"
			: "=a"(result)
			: "a"(61), "D"(pid), "S"(status), "d"(options), "r"(arg4)
			: "rcx", "r11", "cc", "memory"
			);

	return result;
}

long ish_write(
		int file_descriptor,
		const void *buffer,
		unsigned long buffer_size
	      )
{
	long result;
		
	__asm__ __volatile__ (
			"syscall"
			: "=a"(result)
			: "a"(1), "D"(file_descriptor), "S"(buffer), "d"(buffer_size)
			:"rcx", "r11", "cc", "memory"
			);

	return result;
}
