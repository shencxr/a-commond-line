
#include"cmd.h"

cmd print	=
{
	.name = "print",
	.next = NULL,
	.f_p = do_print,
	.helpinfo="print\n\t - print values of all data variables\nprint name ...\n\t- print value of data variable 'name'",
};
cmd set		=
{
	.name = "set",
	.next = NULL,
	.f_p = do_set,
	.helpinfo = "setenv name value ...\n\t- set data variable 'name' to 'value ...'\nsetenv name\n\t- delete data variable 'name'",
};
cmd printup =
{
	.name = "printup",
	.next = NULL,
	.f_p = do_printup,
	.helpinfo = "print\n\t - print values of all data variables in alphabetical ascending order\nprint name ...\n\t- print value of data variable 'name' in alphabetical ascending order",
};
cmd save	=
{
	.name = "save",
	.next = NULL,
	.f_p = do_save,
	.helpinfo = "save\n\t - save data variables to persistent storage",
};
cmd help	=
{
	.name = "help",
	.next = NULL,
	.f_p = do_help,
	.helpinfo="help [command ...]\n\r- show help information(for 'command')\n'help' prints online help for the monitor commands.\n\nWithout arguments, it prints a short usage message for all commands.\n\nTo get detailed help information for specific commands you can type\n'help' with one or more command names as arguments.",
};
cmd quit =
{
	.name = "quit",
	.next = NULL,
	.f_p = NULL,
	.helpinfo = "quit\n\t - exit program.",
};

/*
void quicksort(char(*data_tmp_buf)[MAX_DATA_NAME_LEN + MAX_PER_DATA_LEN],int numleft,int numright)
{
int p, q, flag;
p = numleft;
q = numright;
flag = numleft;
while (p != q)
{
while (*(*(data_tmp_buf + q)) >= *(*(data_tmp_buf + flag)) && q > p)
{
q--;
}
while (*(*(data_tmp_buf + p)) <= *(*(data_tmp_buf + flag)) && q > p)
{
p++;
}
if (p != q)
{
char *__tmp = malloc(MAX_DATA_NAME_LEN + MAX_PER_DATA_LEN);
memset(__tmp, 0, MAX_DATA_NAME_LEN + MAX_PER_DATA_LEN);
strcpy(__tmp, *(data_tmp_buf + q));
strcpy(*(data_tmp_buf + q), *(data_tmp_buf + p));
strcpy(*(data_tmp_buf + p), __tmp);
free(__tmp);
}
}
char *___tmp = malloc(MAX_DATA_NAME_LEN + MAX_PER_DATA_LEN);
memset(___tmp, 0, MAX_DATA_NAME_LEN + MAX_PER_DATA_LEN);
strcpy(___tmp, *(data_tmp_buf + flag));
strcpy(*(data_tmp_buf + flag), *(data_tmp_buf + p));
strcpy(*(data_tmp_buf + p), ___tmp);
free(___tmp);
quicksort(data_tmp_buf, numleft, q - 1);
quicksort(data_tmp_buf, q + 1, numright);
}
*/	   

void init_cmd(cmd ** head)
{
	*head = &print;
	print.next = &set;
	set.next = &save;
	save.next = &printup;
	printup.next = &help;
	help.next = &quit;
}

void bubble_sort(char(*data_tmp_buf)[MAX_DATA_NAME_LEN + MAX_PER_DATA_LEN], int num)		
{
	for (int u = num-1; u >0; u--)
	{
		for (int v = 0; v < u; v++)
		{
			if (*(*(data_tmp_buf + v)) > *(*(data_tmp_buf + v + 1)))
			{
				char *__tmp = malloc(MAX_DATA_NAME_LEN + MAX_PER_DATA_LEN);
				memset(__tmp, 0, MAX_DATA_NAME_LEN + MAX_PER_DATA_LEN);
				strcpy(__tmp, *(data_tmp_buf + v));
				strcpy(*(data_tmp_buf + v), *(data_tmp_buf + v+1));
				strcpy(*(data_tmp_buf + v+1), __tmp);
				free(__tmp);
			}
		}
	}
}

char * do_printup(char *origin_str, int argcount_in, char(*argvector_in)[MAX_PER_ARG_LEN])	
{
	char(*data_tmp_buf)[MAX_DATA_NAME_LEN + MAX_PER_DATA_LEN] = malloc(sizeof(char[MAX_DATA_NUM][MAX_DATA_NAME_LEN + MAX_PER_DATA_LEN]));
	memset(data_tmp_buf, 0, sizeof(char[MAX_DATA_NUM][MAX_DATA_NAME_LEN + MAX_PER_DATA_LEN]));
	char * up_str = malloc(MAX_STR);
	memset(up_str, 0, MAX_STR);
	char *tmp_str = origin_str;
	int j, n;
	for ( j = 0, n = 0 ;j < length;n++)
	{
		if (*(tmp_str + j) == '\0')
		{
			break;
		}
		int _m = strlen(tmp_str + j) + 1;
		memcpy(*(data_tmp_buf + n), tmp_str + j, _m);
		j = j + _m;
	}
	/*
	printf("%d\n", n);
	
	for (int o = 0; o < n; o++)
	{
		printf("%s\n", *(data_tmp_buf + o));
	}
	*/
	bubble_sort(data_tmp_buf, n);
	/*
	printf("\n");
	for (int o = 0; o < n; o++)
	{
		printf("%s\n", *(data_tmp_buf + o));
	}
	*/
	int _length = 0;
	for (int o = 0; o < n; o++)
	{
		memcpy(up_str + _length, *(data_tmp_buf + o), strlen(*(data_tmp_buf + o)) + 1);
		_length = _length + strlen(*(data_tmp_buf + o)) + 1;
	}
	/*
	if (_length != length)
	{
		printf("\t\tllllllll\n");
	}
	*/
	
	free(data_tmp_buf);
	free(origin_str);
	up_str = do_print(up_str, argcount_in, argvector_in);
	return up_str;
}

char * do_save(char *origin_str, int argcount_in, char(*argvector_in)[MAX_PER_ARG_LEN])		
{
	char *write_buf = origin_str;
	int real_write_size = 0;
	FILE * _fp = NULL;
	_fp = fopen("backup.txt", "w+");
	if (_fp == NULL)
	{
		printf("\tOpen file failed.\n");
		return origin_str;
	}
	real_write_size=fwrite(write_buf, 1, length, _fp);
	fflush(_fp);
	fclose(_fp);
	debug("%d\n", real_write_size);
	if (real_write_size != length)
	{
		printf("\tSave failed.\n");
		return origin_str;
	}
	else
	{
		printf("\tSave success.\n");
		return origin_str;
	}
}

char * do_set(char *origin_str, int argcount_in, char(*argvector_in)[MAX_PER_ARG_LEN])		
{
	char * return_str = malloc(MAX_STR);
	memset(return_str, 0, MAX_STR);
	char *set_str = origin_str;
	if (argcount_in == 0)
	{
		printf("\tinputting format error.\n");
		free(return_str);
		return origin_str;
	}
	else
	{
		int	m = 0;
		int	name_length = 0;
		char data_name_buf[MAX_DATA_NAME_LEN];
		for (m = 0; m < length; m++)
		{
			memset(data_name_buf, 0, MAX_DATA_NAME_LEN);
			for (name_length = 0; *(set_str + m + name_length) != '='&&*(set_str + m + name_length) != '\0'; name_length++);
			memcpy(data_name_buf, set_str + m, name_length);
			if (!strcmp(data_name_buf, *argvector_in))
			{
				break;
			}
			m = m + strlen(set_str + m);
		}
		if (m >= length)
		{
			if (argcount_in == 1)
			{
				printf("\tHave no this data or Can not add a empty data.\n");
				free(return_str);
				return origin_str;
			}
			else if (argcount_in == 2)
			{
				memcpy(return_str, origin_str, length);
				memcpy(return_str + length, *(argvector_in), strlen(*argvector_in));
				memset(return_str + length + strlen(*argvector_in), '=', 1);
				memcpy(return_str + length + strlen(*argvector_in) + 1, *(argvector_in + 1), strlen(*(argvector_in + 1)));
				free(origin_str);
				length = length + strlen(*argvector_in) + 1 + strlen(*(argvector_in + 1))+1;
				debug("length=%d\n", length);
				return return_str;
			}
			else
			{
				printf("\tPer data just allow to have a value.\n");
				free(return_str);
				return origin_str;
			}
		}
		if (argcount_in == 1)
		{
			//printf("aaa");
			int delete_str_len = strlen(origin_str + m);
			memcpy(return_str, origin_str + m, m);
			memcpy(return_str + m, (origin_str + m + delete_str_len) + 1, (length - m - delete_str_len));
			length = length - delete_str_len-1;
			free(origin_str);
			return return_str;
		}
		else if(argcount_in == 2)
		{
			int amend_str_len = strlen(origin_str + m)+1;
			memcpy(return_str, origin_str, m);
			memcpy(return_str + m, (origin_str + m + amend_str_len), (length - m - amend_str_len));
			memcpy(return_str + m + (length - m - amend_str_len), origin_str + m, name_length + 1);
			memcpy(return_str + m + (length - m - amend_str_len) + name_length + 1, *(argvector_in + argcount_in-1), strlen(*(argvector_in + argcount_in-1)));
			free(origin_str);
			length = m + (length - m - amend_str_len) + name_length + 1 + strlen(*(argvector_in + argcount_in - 1)) + 1;
			return return_str;
		}
		else
		{
			printf("\tInputting format error.\n");
			free(return_str);
			return origin_str;
		}
	}

}

char * do_print(char *origin_str,int argcount_in,char (*argvector_in)[MAX_PER_ARG_LEN])		
{
	char *print_str = origin_str;
	if (argcount_in == 0)
	{
		for (int j = 0; j < MAX_STR; j++)
		{
			if (*(print_str + j) != '\0')
			{
				printf("%c", *(print_str + j));
			}
			else
			{
				if (*(print_str + j + 1) == '\0')
				{
					printf("\n");
					break;
				}
				
				printf("\n");
				continue;
			}
		}
		return origin_str;
	}
	else
	{
		seek_flag data_find_flag;
		for (int j = 0; j < argcount_in; j++)
		{	
			data_find_flag= NO_SEEK_OUT;
			char data_name_buf[MAX_DATA_NAME_LEN];
			for (int m=0;m<length;m++)
			{
				memset(data_name_buf, 0, MAX_DATA_NAME_LEN);
				int _m;
				for (_m = 0; *(print_str + m + _m) != '='&&*(print_str + m + _m) != '\0'; _m++);
				memcpy(data_name_buf, print_str + m, _m);
				if (!strcmp(data_name_buf, *(argvector_in + j)))
				{
					printf("%s\n", print_str + m);
					data_find_flag = SEEK_OUT;
					break;
				}
				m = m + strlen(print_str + m) ;
			}
			if (!data_find_flag)
			{
				printf("\tFind no the %dth data.\n",j+1);
				continue;
			}
		}
		return origin_str;
	}
}

char * do_help(char *origin_str, int argcount_in, char(*argvector_in)[MAX_PER_ARG_LEN])
{
	/*
	char command[6][20] = { {"help"},{"print"},{ "printup" },{ "set" },{ "save" },{ "quit" } };
	memset(command, 0, sizeof(command));
	printf("%s\n", *(command+1));
	for (int x = 0; x < 6; x++)
	{
		printf("%s\n", *(command + x));
	}
	printf("%d\n", sizeof(command));
	*/
	if (argcount_in == 0)
	{		
		printf("help	- print online help.\n");
		printf("print	- print data variables.\n");
		printf("printup	- print data variables in alphabetical ascending order.\n");
		printf("set	- set data variables.\n");
		printf("save	- save data variables to persistent storage.\n");
		printf("quit	- exit program.\n");
		return origin_str;
	}
	else
	{
		seek_flag data_find_flag;
		cmd* _tmp_cmd = cmd_head;
		for (int x = 0; x < argcount_in; x++)
		{
			_tmp_cmd = cmd_head;
			data_find_flag= NO_SEEK_OUT;
			for (; _tmp_cmd != NULL; _tmp_cmd = _tmp_cmd->next)
			{
				if (!strcmp(*(argvector_in + x), _tmp_cmd->name))
				{
					printf("%s\n", _tmp_cmd->helpinfo);
					data_find_flag= SEEK_OUT;
					break;
				}
			}
			if(!data_find_flag)
			{
				printf("\tFind no the %dth command.\n",x+1);
				continue;
			}
		}
	}
	//printf("\tHelping info has not been writen.\n");
	return origin_str;
}


