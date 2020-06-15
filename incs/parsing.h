#ifndef PARSING_H
# define PARSING_H

typedef struct 	s_parsing_tool
{
	int		size;
	char 	*input;
	char 	**arg;
	int		open;
	char	quote;
}				t_parsing_tool;

char	**parsing(char *input);
char	**ft_split_args(t_parsing_tool *tool);
int		size_arg_tool(t_parsing_tool *tool);
void	check_quote(t_parsing_tool *tool, char c);
char	*ft_addsubstr(char const *s_copy, char *ptr, t_parsing_tool *tool);

#endif