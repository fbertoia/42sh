#include "sh21.h"

char *get_history_at(int nb, int *j)
{
	const t_list	*list = get_ft_shell()->history;
	int	len = ft_lstsize((t_list*)list);
	t_list *ptr;

	char *iota;

	nb += nb < 0 ? len + 1 : 0;
	if (nb <= 0 || nb > len)
		return (NULL);
	iota = ft_itoa(nb);
	*j += ft_strlen(iota);
	ft_strdel(&iota);
	ptr = (t_list*)list;
	while (len != nb && len > 0)
	{
		ptr = ptr->next;
		len--;
	}
	return (ft_strdup(((t_ft_hist_entry*)(ptr->content))->command));
}

char *cmp_history(char *str, int *j)
{
	char *tmp;
	char *ret;

	while (str[*j] && ft_isalpha(str[*j]))
		*j += 1;
	tmp = ft_strndup(str, *j);
	ret = search_history_nav(get_ft_shell(), tmp, 1);
	ft_printf("tmp = %s.       |     ret = %s\n", tmp, ret);
	ft_strdel(&tmp);
	return (ft_strdup(ret));
}

void replace_bang(char **str, int *i, int *j, char *bang)
{
	char *ret;

	ret = ft_strnew(ft_strlen(*str) + ft_strlen(bang));
	ft_strncpy(ret, *str, *i);
	ft_strcat(ret, bang);
	ft_strcat(ret, *str + *i + *j + 1);
	ft_strdel(str);
	*str = ret;
}

int case_bang(char **str, int *i)
{
	int		j;
	char	*bang;

	j = 1;
	if (!(*str)[*i + j])
		bang = NULL;
	else if ((*str)[*i + j] == '!')
		bang = ft_strdup(((t_ft_hist_entry*)(get_ft_shell()->
			history->content))->command);
	else if (ft_isdigit((*str)[*i + j]) || (*str)[ *i + j] == '-')
		bang = get_history_at(ft_atoi((*str) + *i + j), &j);
	else
		bang = cmp_history(*str + *i + j, &j);
	if (!bang)
		return (0);
	replace_bang(str, i, &j, bang);
	*i += ft_strlen(bang);
	ft_strdel(&bang);
	return (1);
}

int case_backslash_bang(char *str, int *i, char c)
{
	int ret;

	*i += 1;
	ret = str[*i] == c;
	if (str[*i])
		*i += 1;
	return (ret);
}

void case_quote_bang(char *str, int *i)
{
	*i += 1;
	while (str[*i] && (str[*i] != '\'' || case_backslash_bang(str, i, str[*i])))
		*i += 1;
}

int case_dquote_bang(char **str, int *i)
{
	int ret;

	ret = 1;
	*i += 1;
	while ((*str)[*i] && ((*str)[*i] != '"'))
	{
		if ((*str)[*i] == '!')
			ret = case_bang(str, i);
		*i += 1;
	}
	return (ret);
}

int bang(char **str)
{
	int i;
	int ret;

	ret = 1;
	i =0;
	while ((*str)[i])
	{
		if ((*str)[i] == '\\')
			case_backslash_bang(*str, &i, (*str)[i]);
		else if ((*str)[i] == '\'')
			case_quote_bang(*str, &i);
		else if ((*str)[i] == '\"')
			ret = case_dquote_bang(str, &i);
		else if ((*str)[i] == '!')
			ret = case_bang(str, &i);
		else
			i++;
		if (!ret)
		{
			ft_strdel(str);
			break;
		}
		ft_printf("str = %s\n", *str);
	}
	return (ret);
}