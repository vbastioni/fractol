/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_activebits.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vbastion <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/04/18 11:32:03 by vbastion          #+#    #+#             */
/*   Updated: 2017/04/18 11:32:12 by vbastion         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

int		ft_activebits(int n)
{
	int	r;
	int	i;
	int	max;

	i = 0;
	r = 0;
	max = (sizeof(int) * 8);
	while (i < max)
	{
		r += (n & 1);
		n = (n >> 1);
		i++;
	}
	return (r);
}
