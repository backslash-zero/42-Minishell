#ifndef PARSING_H
# define PARSING_H

typedef struct 	s_parsing_tool
{
	int		size;
	char 	*input;
	char 	**arg;
	int		open;
	int		expand;
	char	quote;

}				t_parsing_tool;

char	**parsing(char *input);
char	**ft_split_args(t_parsing_tool *tool);
int		size_arg_tool(t_parsing_tool *tool);
void	switcher_quote(t_parsing_tool *tool, char c);
char	*ft_addsubstr(char const *s_copy, char *ptr, t_parsing_tool *tool);
char	*ft_clean_input(char *str, t_parsing_tool *tool);
void	switcher_quote(t_parsing_tool *tool, char c);
int		test_empty_quote(char c, char d);
int		test_quote(char c);
int		new_input_len(char *str, t_parsing_tool *tool);
void 	ft_copy_new_input(char *str, char *output, t_parsing_tool *tool);
void	init_tool(t_parsing_tool *tool);

#endif