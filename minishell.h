#define ECHO 0
#define ECHO_N 7
#define CD 1
#define PWD 2
#define ENV 3
#define EXPORT 4
#define UNSET 5
#define EXIT 6
#define UNKOWN 8
#define ERROR 9

#define PIPE 0
#define COMA 1
#define RIGHT 2
#define LEFT 3
#define D_RIGHT 4
#define D_LEFT 5
#define AND 6
#define OR 7



typedef struct	s_order
{
	char	*output;
	char	*input;
	int		command;
	int		sep;
	t_order	*next;
}				t_order;
