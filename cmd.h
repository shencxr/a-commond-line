#ifndef _CMD_H_
#define _CMD_H_

#define _CRT_SECURE_NO_WARNINGS	1

#include<stdio.h>
#include<Windows.h>

//#define DEBUG


#ifdef DEBUG
#define debug	printf
#else
#define debug
#endif // DEBUG


#define BANNER				"altman#"
#define MAX_ARG_NUM			10//参数个数
#define MAX_PER_ARG_LEN		20//每个参数长度
#define MAX_STR				1024*1024//字符串总长度
#define MAX_CMDLINE_INPUT	256//命令行输入最多字符数
#define MAX_CMD_LEN			10//命令长度
#define MAX_DATA_NUM		100			
#define	MAX_PER_DATA_LEN	20//每个数据值得长度
#define MAX_DATA_NAME_LEN	20//每个数据名字长度
#define CMD_NUM				6

typedef struct cmd_s
{
	char * name;
	char *(*f_p)(char *,int,char (*)[MAX_PER_ARG_LEN]);
	char *helpinfo;
	struct cmd_s* next;
}cmd;

typedef enum flag
{
	SEEK_OUT		=		1,
	NO_SEEK_OUT		=		!SEEK_OUT,
}seek_flag;





extern int length;
extern cmd * cmd_head;



void init_cmd		(cmd ** head);
void bubble_sort	(char(*data_tmp_buf)[MAX_DATA_NAME_LEN + MAX_PER_DATA_LEN], int num);
char * do_printup	(char *origin_str, int argcount_in, char(*argvector_in)[MAX_PER_ARG_LEN]);
char * do_save		(char *origin_str, int argcount_in, char(*argvector_in)[MAX_PER_ARG_LEN]);
char * do_set		(char *origin_str, int argcount_in, char(*argvector_in)[MAX_PER_ARG_LEN]);
char * do_print		(char *origin_str, int argcount_in, char(*argvector_in)[MAX_PER_ARG_LEN]);
char * do_help		(char *origin_str, int argcount_in, char(*argvector_in)[MAX_PER_ARG_LEN]);





#define scxr	"scxr"
#define	print_info	"(1):print	\n(2):print name1 name2 ..."
#define	save_info	""
#define	set_info	""


#endif // !_CMD_H_

