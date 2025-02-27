/*
** EPITECH PROJECT, 2023
** Default
** File description:
** ls_flag_t
*/

#include "my.h"
#include <sys/stat.h>
#include <stdio.h>
#include <dirent.h>

static void more_ls(char *str)
{
    char *dirs[256] = {NULL};
    struct dirent *entry;
    DIR *dir;
    char tmp[my_strlen(str) + 256];

    my_strcat(tmp, str);
    dir = opendir(str);
    for (entry = readdir(dir); entry != NULL; entry = readdir(dir))
        if (entry->d_name[0] != '.') {
            my_strcpy(tmp, str);
            my_strcat(tmp, "/");
            my_strcat(tmp, entry->d_name);
            my_tabcatstr(tmp, dirs);
        }
    my_sort_tab_edit_date(dirs);
    ls_printdirs(dirs);
    closedir(dir);
}

void ls_flag_t(char **dir, int i)
{
    struct stat s;

    my_sort_tab_edit_date(dir);
    if (my_tablen(dir) > 1)
        my_printf("%s:\n", dir[i]);
    stat(dir[i], &s);
    if (S_ISDIR(s.st_mode) == 1) {
        more_ls(dir[i]);
    } else if (S_ISREG(s.st_mode) == 1) {
        ls_color(dir[i]);
    }
    if (my_tablen(dir) > 1 && dir[i + 1] != NULL)
        my_printf("\n\n");
}
