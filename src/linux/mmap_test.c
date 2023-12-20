// 测试linux mmap使用
// docs: https://github.com/danbev/learning-linux-kernel/blob/master/mmap.c
// compile && run: clang mmap_test.c -o test.bin && ./test.bin

#include <stdio.h>
#include <string.h>
#include <sys/mman.h>
#include <unistd.h>


int main()
{
    // man page: https://man7.org/linux/man-pages/man2/getpagesize.2.html
    size_t pagesize = getpagesize();
    printf("System page size: %zu bytes\n", pagesize);

    // man page: https://man7.org/linux/man-pages/man3/sysconf.3.html
    // get configuration information at run time
    size_t sc_pagesize = (size_t)sysconf(_SC_PAGESIZE);
    printf("_SC_PAGESIZE: %zu bytes\n", sc_pagesize);

    // man page: https://man7.org/linux/man-pages/man2/mmap.2.html
    //  void *mmap(void *addr, size_t length, int prot, int flags,
                //   int fd, off_t offset);
    char *mem_area = mmap(NULL,     // let the kernel choose the address
                          pagesize, // length of the mapping
                          PROT_READ | PROT_WRITE,
                          MAP_ANONYMOUS | MAP_PRIVATE,
                          -1, // since this is an anonymous mapping fd is ignored
                          0); // likewise the offset should be zero in this case.

    if (mem_area == MAP_FAILED)
    {
        perror("Could not mmap");
        return 1;
    }

    // 复制数据到mmap分配的空间
    strcpy(mem_area, "Something...");
    // 设置空间属性
    mprotect(mem_area, pagesize, PROT_EXEC);

    printf("mem_area address: %p\n", &mem_area);
    printf("mem_area content: %s\n", mem_area);

    // 删除该空间
    // https://man7.org/linux/man-pages/man2/mmap.2.html#:~:text=synonym%20MAP_ANON).-,munmap(),-The%20munmap()%20system
    int unmap_result = munmap(mem_area, pagesize);
    if (unmap_result != 0)
    {
        perror("Could not munmap");
        return 1;
    }

    return 0;
}