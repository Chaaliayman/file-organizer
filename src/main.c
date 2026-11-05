#include<stdio.h>
#include<dirent.h>
#include<sys/stat.h>
#include<string.h>

int main()
{
	
	DIR *dirctory = opendir(".");
	struct dirent *entry;
	char background[512];
	char new_path[1024];
	struct stat file_info;
	int result;
	if(dirctory == NULL)
	{
		return(1);
	}
	mkdir("Images",0755);
	mkdir("Videos",0755);
	mkdir("Documents",0755);
	mkdir("Others",0755);
	
	while((entry = readdir(dirctory)) != NULL)
	{
		if(entry->d_name[0] == '.')
		{
			continue;
		}
		if(stat(entry->d_name,&file_info) == -1)
		{
			continue;
		}
		if(S_ISDIR(file_info.st_mode))
		{
			continue;
		}
		char *extension = strrchr(entry->d_name,'.');
		if(extension == NULL)
		{
			strcpy(background,"Others");
		}
		else if(strcmp(extension,".jpg") == 0 || strcmp(extension,".png") == 0|| strcmp(extension,".jpeg") == 0 || strcmp(extension,".gif") == 0)
		{
			strcpy(background,"Images");
		}
		else if(strcmp(extension,".mp4") == 0 || strcmp(extension,".avi") == 0 || strcmp(extension,".mov") ==  0 || strcmp(extension,".mkv") == 0)
		{
			strcpy(background,"Videos");
		}
		else if(strcmp(extension,".txt") == 0 || strcmp(extension,".pdf") == 0 || strcmp(extension,".xlsx") == 0 || strcmp(extension,".docx") == 0)
		{
			strcpy(background,"Documents");
		}
		else 
		{
			strcpy(background,"Others");
		}
		snprintf(new_path,sizeof(new_path),"%s/%s",background,entry->d_name);
		result = rename(entry->d_name,new_path);
		if(result != 0)
		{
			perror("rename");
		}
	}

	closedir(dirctory);
	return 0;
}
