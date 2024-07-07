#include <stdlib.h>

#include "helper.hpp"

void *aligned_malloc(size_t size, size_t alignment)
{
    void *ptr = NULL;
    if (posix_memalign(&ptr, alignment, size) != 0)
    {
        // Allocation failed
        return NULL;
    }
    return ptr;
}
