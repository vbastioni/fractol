#include "fractol.h"

double			cmp_abs(const t_cmp *cmp)
{
	return (sqrt(cmp->re * cmp->re + cmp->im * cmp->im));
}

t_cmp			cmp_mult(const t_cmp *lhs, const t_cmp *rhs)
{
	t_cmp		tmp;

	tmp.re = lhs->re * rhs->re - lhs->im * rhs->im;
	tmp.im = lhs->re * rhs->im + lhs->im * rhs->re;
	return (tmp);
}

t_cmp			cmp_sub(const t_cmp *lhs, const t_cmp *rhs)
{
	t_cmp		tmp;
	
	tmp.re = lhs->re - rhs->re;
	tmp.im = lhs->im - rhs->im;	
	return (tmp);
}

t_cmp			cmp_div(const t_cmp *lhs, const t_cmp *rhs)
{
	t_cmp		tmp;

	tmp.re = ((lhs->re * rhs->re + lhs->im * rhs->im)
				/ (rhs->re * rhs->re + rhs->im * rhs->im));
	tmp.im = ((lhs->im * rhs->re - lhs->re * rhs->im)
				/ (rhs->re * rhs->re + rhs->im * rhs->im));
	return (tmp);
}

t_cmp			cmp_multr(const t_cmp *lhs, double r)
{
	t_cmp		tmp;

	tmp.re = lhs->re * r;
	tmp.im = lhs->im * r;
	return (tmp);
}
