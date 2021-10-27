/**
 * search_cwd - look for current working dir
 * filename: search_cwd.c
 * Return: current working dir
 */


#include "shell.h"

char *search_cwd(char *filename, char *er)
{
	DIR *dir;
	struct dirent *sd;
	char *ret;
	int len = 0;
	int i = 0;

	while (filename[len])
		len++;
	ret = malloc(sizeof(char) * (len + 3));
	dir = opendir(".");
	if (!dir)
	{
		printf("Error! Can't open directory.\n");
		exit(0);
	}
	while ((sd = readdir(dir)))
	{
		for (i = 0; sd->d_name[i] && filename[i]; i++)
		{
			if (sd->d_name[i] != filename[i])
				break;
			if (i == (len - 1) && !(sd->d_name[i + 1]))
			{
				strcpy(ret, "./");
				strcat(ret, filename);
				closedir(dir);
				if (!(access(ret, X_OK)))
					return (ret);
				else
					write(2, er, 5);
			}
		}
	}
	closedir(dir);
	return (er);
}
