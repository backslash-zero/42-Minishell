#include "../../incs/minishell.h"

void	ft_builtinstab(t_parse *parse)
{
	parse->builtnb[0] = "echo";
	parse->builtnb[1] = "cd";
	parse->builtnb[2] = "pwd";
	parse->builtnb[3] = "export";
	parse->builtnb[4] = "unset";
	parse->builtnb[5] = "env";
	parse->builtnb[6] = "exit";
}

builtfunc_addr	builtins_func[] = {
	&builtin_echo, &builtin_cd, &builtin_pwd, &builtin_export, &builtin_unset, &builtin_env, &builtin_exit
};

int		ft_checkbuiltins(char **s, t_parse *parse)
{
	int i;
	int	good;

	i = 0;
	good = 0;
	while (i < NB_BUILINS && good != 1)
	{
		if (ft_strcmp(s[0], parse->builtnb[i]) == 0)
			good = 1;
		if (good != 1)
			i++;
	}
	if (good == 1)
	{
		if (builtins_func[i](s) == -1)
			return(0);
		return(1);
	}
	else
		return (0);
}