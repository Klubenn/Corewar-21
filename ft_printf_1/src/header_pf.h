/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   header_pf.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gtapioca <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/04 16:16:57 by gtristan          #+#    #+#             */
/*   Updated: 2020/07/24 15:57:42 by gtapioca         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PRINTF_HEADER_PF_H
# define PRINTF_HEADER_PF_H
# include <stdio.h>
# include <stdarg.h>
# include <stdlib.h>
# include <unistd.h>
# include "../../includes/libft.h"
# define RED "\x1b[31m"
# define GREEN "\x1b[32m"
# define YELLOW "\x1b[33m"
# define BLUE "\x1b[34m"
# define MAGENTA "\x1b[35m"
# define CYAN "\x1b[36m"
# define RESET "\x1b[0m"

typedef union				u_double
{
	long double				ld;
	struct
	{
		unsigned long int	mant : 64;
		unsigned int		expon : 15;
		unsigned int		sign : 1;
	}						s_parts;
}							t_double;

typedef struct				s_dnum
{
	unsigned long			num;
	struct s_dnum			*next;
	struct s_dnum			*prev;
}							t_dnum;

typedef struct				s_list_pf
{
	char					flag0[8];
	char					flag1;
	char					point;
	int						left;
	int						right;
	char					letter;
	char					*number;
	char					*print[8];
	long double				fl;
	char					*leftfl;
	char					*rightfl;
	char					*zero;
}							t_list_pf;

char						*get_result_str(void);
int							get_fd(void);
int							set_fd(int fd);
void						fd_z(va_list ap);
char						*add_char_to_output_buffer(char c);
int							ft_printf(const char *format, ...);
void						float_f(t_list_pf *list, va_list ap);
unsigned long				power(int base, int exp);
int							ft_strlen_pf(char *str);
int							numlength(long long l, int base);
char						*ft_itoa_base_u1(unsigned long long value,
		int base, int uppercase);
char						*create_string(char c, int i);
size_t						ft_putstr_pf(char *s);
int							sumlen(t_list_pf *list);
void						printnum(t_list_pf *list);
char						*ft_makestr(char *str);
void						free_struct(t_list_pf *list);
void						ft_free(char **str);
void						percent(t_list_pf *list);
void						character(t_list_pf *list, va_list ap);
size_t						ft_putstr_len_pf(char *str, size_t len);
void						string2(t_list_pf *list, char *str);
char						*hash(t_list_pf *list);
void						printnum_u2(t_list_pf *list, int sum);
void						printnum_u1(t_list_pf *list);
void						oct_hex_u(t_list_pf *list, va_list ap, int base);
void						zerocase(t_list_pf *list);
void						zerocase_u1(t_list_pf *list);
void						zerocase_u2(t_list_pf *list);
void						decimal(t_list_pf *list, va_list ap);
void						printnum_d2(t_list_pf *list, int a);
void						printnum_d1(t_list_pf *list);
int							fill_struct3(char *ch, t_list_pf *list);
void						fill_struct2(char *ch, t_list_pf *list);
int							fill_struct1(char *ch, t_list_pf *list);
int							ft_putchar_pf(char c, int n);
int							last_letter(char c);
t_list_pf					*new_list(void);
char						*ft_itoa_base_u2(unsigned long long value,
		int base, int up, int i);
char						*ft_itoa_pf(long long i, t_list_pf *list);
int							print_color(char *str);
int							parsing1(char *ch, va_list ap);
void						analysis(t_list_pf *list, va_list ap);
size_t						ft_strlen(const char *s);
int							ft_atoi(const char *str);
char						*ft_strjoin(char const *s1, char const *s2);
char						*ft_strncpy(char *dst, const char *src, size_t len);
char						*ft_strcpy(char *dst, const char *src);
void						floattostr2(t_dnum *flist, char *str, int len);
void						multiply(t_dnum *flist, unsigned long numpower);
t_dnum						*new_flist(unsigned long i, t_dnum *prevlist);
unsigned long				power(int base, int exp);
char						*ft_strcpy_pf(char *dst, const char *src);
void						print_float3(t_list_pf *list);
void						print_float2(t_list_pf *list);
void						print_float1(t_list_pf *list);
void						float_f(t_list_pf *list, va_list ap);
int							change_num(char *str, int i);
void						rounding3(t_list_pf *list, char *str, int i);
char						*rounding2(t_list_pf *list, int i, int j);
char						*rounding1(t_list_pf *list);
char						*floattostr1(t_dnum *flist);
char						*conversion(unsigned long mant, int exp, int base);
void						print_in(t_list_pf *list);
int							inf_nan(int sign, unsigned long mant,
		int exp, t_list_pf *list);
void						free_flist(t_dnum *flist);

#endif
