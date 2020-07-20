#ifndef PARSING_H
# define PARSING_H


typedef struct	s_newstr
{
	char 	*str;
	int		len;
	int		open;
	int		expand;
	char	quote;
}				t_newstr;

typedef struct 	s_parsing_tool
{
	int		size;
	char 	*input;
	char 	**arg;
	int		open;
	char	quote;

}				t_parsing_tool;



char	**parsing(char *input);
int		ft_split_args(t_parsing_tool *tool);
int		size_arg_tool(t_parsing_tool *tool);
void	switcher_quote(t_parsing_tool *tool, char c);
char	*ft_addsubstr(int i, int j, t_parsing_tool *tool);
void	switcher_quote(t_parsing_tool *tool, char c);
int		test_empty_quote(char c, char d);
// char	*ft_clean_input(char *str, t_parsing_tool *tool);
// int		new_input_len(char *str, t_parsing_tool *tool);
// void 	ft_copy_new_input(char *str, char *output, t_parsing_tool *tool);
char	*clean_substring(char *str);
void	init_tool(t_parsing_tool *tool);
int		append_string_to_arg(int *i, int *j, int *n, t_parsing_tool *tool);
int		append_semicolon(int *i, int j, int *n, t_parsing_tool *tool);
int		is_quote(char c);
int		is_space(char c);
int		is_semic(char c);
int		is_dollar(char c);
int		is_equal(char c);
int		expand_env(t_parsing_tool *tool);
int		replace_var(t_parsing_tool *tool, int i, char *var, char *env_name);
int		insert_env_var(t_parsing_tool *tool, int i);
char	*get_var_name(t_parsing_tool *tool, int i);
char	*parsing_variable(char *str);

#endif