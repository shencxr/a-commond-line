
#include"cmd.h"



unsigned char defaule_string[] = { "scxr=""09""\0""zhc=135" };
int length = 0;
cmd * cmd_head = NULL;
    

int main(int argc,char *argv[])
{
	debug("%s\n%d\n%d\n", scxr,sizeof(scxr),strlen(scxr));
	init_cmd(&cmd_head);
	char * exist_string = malloc(MAX_STR);
	memset(exist_string, 0, MAX_STR);
	
	FILE * fp = NULL;
	fp = fopen("backup.txt", "a+");
	if (fp == NULL)
	{
		printf("open error");
		system("pause");
		return 1;
	}
	fseek(fp, 0, SEEK_END);
	length = ftell(fp);
	debug("length=%d\n", length);
	if (length == 0)
	{
		debug("length == 0.....\n");
		fseek(fp, 0, SEEK_SET);
		fwrite(defaule_string, sizeof(defaule_string), 1, fp);
		fflush(fp);
		fclose(fp);
		length = sizeof(defaule_string);
		memcpy(exist_string, defaule_string, length);
	}
	else
	{
		int real_read = 0;
		debug("else.....\n");
		fseek(fp, 0, SEEK_SET);
		real_read=fread(exist_string, 1, length, fp);
		fclose(fp);
		debug("real_read=%d\n", real_read);
	}
	char user_input[MAX_CMDLINE_INPUT] = { 0 };
	printf("\tYou can input \"help\" to attain command,if you use at first time.\n");
	while (1)
	{
		int argcount = 0;
		char argvector[MAX_ARG_NUM][MAX_PER_ARG_LEN];
		memset(argvector, 0, sizeof(argvector));
		printf(BANNER);
		gets(user_input);
		char *tmp = user_input;
		int user_input_length = strlen(user_input);
		if (user_input_length == 0)
		{
			continue;
		}
		if (user_input_length > MAX_CMDLINE_INPUT)
		{
			printf("\tToo mang charaters,Please re-input.\n");
			continue;
		}
		char input_cmd_buf[MAX_CMD_LEN] = { 0 };
		int i;
		for (i = 0; *(tmp + i) != '\0'&&*(tmp + i) != ' '; i++);
		if (i > MAX_CMD_LEN)
		{
			printf("\tPlease input correct format of instruction.\n");
			continue;
		}
		for (int j = 0; j < i; j++)
		{
			*(input_cmd_buf + j) = *(tmp + j);
		}
		while(i < user_input_length)
		{
			for (; *(tmp + i) == ' '; i++);
			if (*(tmp + i) != '\0')
			{
				int _tmp;
				for (_tmp = 0; *(tmp + i + _tmp) != '\0'&&*(tmp + i + _tmp) != ' '; _tmp++);
				memcpy(argvector[argcount], tmp + i, _tmp);
				argcount++;
				i = i + _tmp;
			}
		}
		cmd * execute_of_cmd = NULL;
		cmd * tmp_cmd = cmd_head;
		seek_flag cmd_find_flag = NO_SEEK_OUT;
		if (!strcmp("quit", input_cmd_buf))
		{
			goto _exit;
		}
		do
		{
			if (tmp_cmd == NULL)
			{
				printf("\tHave no this instruction.\n");
				return 1;
			}
			if (!strcmp(input_cmd_buf, tmp_cmd->name))
			{
				cmd_find_flag = SEEK_OUT;
				execute_of_cmd = tmp_cmd;
				break;
			}
			tmp_cmd = tmp_cmd->next;
		} while (tmp_cmd != NULL);
		int re_flag = 0;
		for (int _n = 0; _n < argcount; _n++)
		{
			if (strlen(argvector[_n]) > MAX_PER_ARG_LEN)
			{
				printf("\tThe %dth arguments overlong.\n",_n+1);
				re_flag = 1;
			}
		}
		if (re_flag)
		{
			continue;
		}
		if (cmd_find_flag)
		{
			exist_string=(execute_of_cmd->f_p)(exist_string,argcount, argvector);
		}
		else
		{
			printf("\tFind no instruction,please input again after check.\n");
		}
	}

_exit:
	free(exist_string);
	return 0;
}
