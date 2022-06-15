#ifndef OS_H
#define OS_H

String_Array* temp_files;
#define MAX_TEMP_FILES 32

String* create_temp_file(Allocator* allocator);
void cleanup_temp_files();
bool run_subprocess(char** argv);
bool absolute_path(String* str, String* out);

#endif
