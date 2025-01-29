#include <stdio.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <dirent.h>
#include <stdlib.h>
#include <string.h>
#include <errno.h>

// Kompiler med:
// gcc -Wall list_files.c -o list_files

long get_file_size(const char *filename) {
    struct stat st;
    if (stat(filename, &st) == -1) {
        return -1; // Feil hvis programmet ikke klarer å kalkulere filstørrelse
    }
    return st.st_size;
}

int main() {
    DIR *dir;
    struct dirent *entry;
    long total_files = 0, total_folders = 0;
    long total_file_size = 0;

    dir = opendir(".");
    if (dir == NULL) {
        perror("Failed to open directory");
        return EXIT_FAILURE;
    }

    while ((entry = readdir(dir)) != NULL) {
        // Hopp over skjulte filer '.' og '..'
        if (strcmp(entry->d_name, ".") == 0 || strcmp(entry->d_name, "..") == 0) {
            continue;
        }

        if (entry->d_type == DT_REG) { // Vanlige filer
            total_files++;
            long size = get_file_size(entry->d_name);
            if (size != -1) {
                total_file_size += size;
            }
        } else if (entry->d_type == DT_DIR) { // Filbane / mappe
            total_folders++;
        }
    }

    closedir(dir);

    printf("Total files: %ld\n", total_files);
    printf("Total folders: %ld\n", total_folders);
    printf("Total file size: %.2f MB\n", (total_file_size / 1024.0) / 1024);
    return EXIT_SUCCESS;
}


