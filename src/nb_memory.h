#ifndef NB_MEMORY
#define NB_MEMORY

#define ALLOCATOR_CAST(allocator, type) (type*)(allocator)
#define ALLOCATOR(allocator) (&(allocator)->base_allocator)

typedef struct Allocator Allocator;

typedef void* (*Allocate_Fn)(Allocator*, size_t);
typedef void (*Free_Fn)(Allocator*, void*);
typedef void (*Free_All_Fn)(Allocator*);

struct Allocator
{
    Allocate_Fn allocate;
    Free_Fn free;
    Free_All_Fn free_all;
};

bool is_power_of_two(umm x)
{
    return (x & (x - 1)) == 0;
}

umm align_forward(umm pointer, size_t align)
{
    assert(is_power_of_two(align));

    umm p = pointer;
    umm a = (umm)align;

    // a is a power of two, so this is faster than %
    umm modulo = p & (a - 1);

    if (modulo != 0)
    {
        p += a - modulo;
    }
    return p;
}

typedef struct Arena Arena;
struct Arena
{
    Allocator      base_allocator;
    unsigned char* buffer;
    size_t         buffer_length;
    size_t         previous_offset;
    size_t         current_offset;
};
#define AS_ARENA(allocator) (ALLOCATOR_CAST(allocator, Arena))

typedef struct Temporary_Arena Temporary_Arena;
struct Temporary_Arena
{
    Arena* arena;
    size_t previous_offset;
    size_t current_offset;
};

void* arena_alloc_align(Arena* arena, size_t size, size_t alignment)
{
    umm current_pointer = (umm)arena->buffer + (umm)arena->current_offset;
    umm offset = align_forward(current_pointer, alignment); // align the current offset

    offset -= (umm)arena->buffer; // relative offset

    if (offset + size <= arena->buffer_length)
    {
        void* pointer = &arena->buffer[offset];
        arena->previous_offset = offset;
        arena->current_offset = offset + size;

        memset(pointer, 0, size);
        return pointer;
    }

    return NULL;
}

#ifndef DEFAULT_ALIGNMENT
#define DEFAULT_ALIGNMENT (2 * sizeof(void*))
#endif
void* arena_alloc(Allocator* arena, size_t size)
{
    return arena_alloc_align(AS_ARENA(arena), size, DEFAULT_ALIGNMENT);
}

void* arena_resize_align(Arena* arena, void* old_memory, size_t old_size, size_t new_size, size_t alignment)
{
    unsigned char* old_mem = (unsigned char*)old_memory;

    assert(is_power_of_two(alignment));

    if (old_mem == NULL || old_size == 0)
    {
        return arena_alloc_align(arena, new_size, alignment);
    }
    else if (arena->buffer <= old_mem && old_mem <= arena->buffer + arena->buffer_length)
    {
        if (arena->buffer + arena->previous_offset == old_mem)
        {
            arena->current_offset = arena->previous_offset + new_size;
            if (new_size > old_size)
            {
                memset(&arena->buffer[arena->current_offset], 0, new_size - old_size);
            }
            return old_memory;
        }
        else
        {
            void* new_memory = arena_alloc_align(arena, new_size, alignment);
            size_t copy_size = old_size < new_size ? old_size : new_size;
            memmove(new_memory, old_memory, copy_size);
            return new_memory;
        }
    }
    else
    {
        assert(0 && "Memory is out of bounds of the buffer in this arena");
        return NULL;
    }
}

void* arena_resize(Arena* arena, void* old_memory, size_t old_size, size_t new_size)
{
    return arena_resize_align(arena, old_memory, old_size, new_size, DEFAULT_ALIGNMENT);
}

void arena_free(Allocator* allocator, void* ptr)
{
    (void)allocator;
    (void)ptr;
}

void arena_free_all(Allocator* allocator)
{
    Arena* arena = AS_ARENA(allocator);
    arena->current_offset = 0;
    arena->previous_offset = 0;
}

void arena_init(Arena* arena, void* backing_buffer, size_t backing_buffer_length)
{
    arena->base_allocator.allocate = arena_alloc;
    arena->base_allocator.free = arena_free;
    arena->base_allocator.free_all = arena_free_all;
    arena->buffer = (unsigned char*)backing_buffer;
    arena->buffer_length = backing_buffer_length;
    arena->current_offset = 0;
    arena->previous_offset = 0;
}

Temporary_Arena temp_arena_memory_begin(Arena* arena)
{
    Temporary_Arena temp;
    temp.arena = arena;
    temp.previous_offset = arena->previous_offset;
    temp.current_offset = arena->current_offset;
    return temp;
}

void temp_arena_memory_end(Temporary_Arena temp)
{
    temp.arena->previous_offset = temp.previous_offset;
    temp.arena->current_offset = temp.current_offset;
}

#endif
