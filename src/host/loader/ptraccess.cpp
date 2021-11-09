#include "ptraccess.h"
#include <cstdio>

#ifdef __CUSTOM_ISBADREADPTR
#include <unistd.h>
#include <fcntl.h>

class TmpFd {
public:
	TmpFd(const char *path, int mode):
		m_raw(open(path, mode))
	{
	}
	~TmpFd()
	{
		close(m_raw);
	}
	inline ssize_t fd_write(const void *buf, size_t count) {
		return write(m_raw, buf, count);
	}
	inline int raw_fd() {
		return m_raw;
	}
private:
	int m_raw;
};

extern "C" bool IsBadReadPtr(const void *p, size_t size) {
	TmpFd fd("/dev/random", O_WRONLY);
	return (fd.fd_write(p, size) < 0);
}
#endif
