/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_ft.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: taemkim <taemkim@student.42seoul.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/24 17:27:00 by taemkim           #+#    #+#             */
/*   Updated: 2021/03/29 23:20:37 by taemkim          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

void	check_sign(t_pf *lst)
{
	if (lst->n < 0)
	{
		lst->len--;
		put_buf(lst, "-", 1);
	}
	else if (lst->plus && (lst->n >= 0))
	{
		lst->len--;
		put_buf(lst, "+", 1);
	}
	else if (lst->space && !lst->plus && (lst->n >= 0))
	{
		lst->len--;
		put_buf(lst, " ", 1);
	}
}

void	check_hex(t_pf *lst)
{
	if (lst->conv == 'x')
	{
		put_buf(lst, "0x", 2);
		lst->len -= 2;
	}
	if (lst->conv == 'X')
	{
		put_buf(lst, "0X", 2);
		lst->len -= 2;
	}
}

void	ft_join_all(char *str, char *sp, t_pf *lst)
{
	(lst->is_int && lst->zero) ? check_sign(lst) : 0;
	if (lst->zero && lst->conv == 'p')
	{
		put_buf(lst, "0x", 2);
		lst->len -= 2;
	}
	if (lst->sharp && lst->u && lst->zero && lst->preci_width < lst->len)
		check_hex(lst);
	if (sp && !lst->minus)
		put_buf(lst, sp, lst->sp_len);
	if (!lst->zero && lst->conv == 'p')
	{
		put_buf(lst, "0x", 2);
		lst->len -= 2;
	}
	if (lst->sharp && lst->u && !lst->zero && lst->preci_width < lst->len)
		check_hex(lst);
	if (lst->is_int && !lst->zero)
		check_sign(lst);
	put_buf(lst, str, lst->len);
	if (sp && lst->minus)
		put_buf(lst, sp, lst->sp_len);
	free(str);
	free(sp);
}

char	*ft_print_space(t_pf *lst)
{
	char	*sp_str;
	int		index;

	index = 0;
	if (lst->width < lst->len)
		return (NULL);
	if (!(sp_str = ft_calloc((lst->width - lst->len + 1), sizeof(char))))
		return (NULL);
	if (lst->preci && lst->preci_width > lst->len)
		lst->zero = 0;
	while (index < lst->width - lst->len)
	{
		if (lst->zero || (lst->conv == '%' && lst->true_zero))
			sp_str[index] = '0';
		else
			sp_str[index] = ' ';
		index++;
	}
	lst->sp_len = index;
	sp_str[index] = '\0';
	return (sp_str);
}

char	*ft_num_preci(char *str, t_pf *lst)
{
	char	*tmp;
	int		i;
	int		j;

	i = 0;
	j = 0;
	if (!lst->preci)
		return (str);
	if (lst->preci_width < lst->len)
		return (str);
	if (!(tmp = ft_calloc(lst->preci_width + lst->len + 1, sizeof(char))))
		return (NULL);
	while (i < lst->preci_width - lst->len)
	{
		tmp[i] = '0';
		i++;
	}
	while (str[j])
	{
		tmp[i + j] = str[j];
		j++;
	}
	tmp[i + j] = '\0';
	free(str);
	return (tmp);
}
