/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   libft.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: atorma <atorma@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/16 17:37:08 by atorma            #+#    #+#             */
/*   Updated: 2024/07/26 17:18:56 by lopoka           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LIBFT_H
# define LIBFT_H
# include <stdlib.h>
# include <unistd.h>
# include <limits.h>

# ifndef BUFFER_SIZE
#  define BUFFER_SIZE 32
# endif

typedef struct s_list
{
	void			*content;
	struct s_list	*next;
}	t_list;

typedef struct t_write_state
{
	int		fd;
	ssize_t	bytes_written;
	ssize_t	ret_val;
}	t_write_state;

void		free_array(char	**arr);
int			ft_strcmp(char *s1, char *s2);
int			ft_atoi_base(char *str, char *base);
char		*read_file(int fd, int buf_size, int *out_size);
char		*ft_strpbrk(char *s1, const char *s2);
char		*ft_strtok(char *s, const char *delim);
char		*ft_strtok_r(char *s, const char *delim, char **saveptr);
char		*ft_strtok_strict(char *s, const char *delim);
void		ft_write(struct t_write_state *ws, char *buf, size_t buf_size);
void		print_char(struct t_write_state *ws, int c);
void		print_string(struct t_write_state *ws, char *str);
void		print_integer(struct t_write_state *ws, int n);
void		print_unsigned(struct t_write_state *ws, unsigned int n);
void		print_ptr(struct t_write_state *ws, unsigned long long ptr);
void		print_hex(struct t_write_state *ws, unsigned int n, int is_lower);
void		hex_uint(struct t_write_state *ws, unsigned int n, int is_lower);
void		print_hex_ptr(struct t_write_state *ws, unsigned long long n);
int			ft_printf(const char *f, ...);
int			ft_printf_fd(int fd, const char *f, ...);
int			ft_isalpha(int c);
int			ft_isdigit(int c);
int			ft_isalnum(int c);
int			ft_isascii(int c);
int			ft_isprint(int c);
size_t		ft_strlen(const char *str);
void		*ft_memset(void *b, int c, size_t len);
void		ft_bzero(void *s, size_t n);
void		*ft_memcpy(void *dst, const void *src, size_t n);
void		*ft_memmove(void *dst, const void *src, size_t len);
size_t		ft_strlcpy(char *dst, const char *src, size_t dstsize);
size_t		ft_strlcat(char *dst, const char *src, size_t dstsize);
int			ft_strncmp(const char *s1, const char *s2, size_t n);
int			ft_toupper(int c);
int			ft_tolower(int c);
char		*ft_strchr(const char *s, int c);
char		*ft_strrchr(const char *s, int c);
void		*ft_memchr(const void *s, int c, size_t n);
int			ft_memcmp(const void *s1, const void *s2, size_t n);
char		*ft_strnstr(const char *haystack, const char *needle, size_t len);
int			ft_atoi(const char *str);
long long	ft_atoi_ll(const char *str);
void		*ft_calloc(size_t count, size_t size);
char		*ft_strdup(const char *s1);
char		**ft_split(char const *s, char c);
char		*ft_strtrim(char const *s1, char const *set);
char		*ft_substr(char const *s, unsigned int start, size_t len);
char		*ft_strjoin(char const *s1, char const *s2);
size_t		ft_count_words(char const *s, char c);
char		**ft_split(char const *s, char c);
char		*ft_itoa(int n);
char		*ft_strmapi(char const *s, char (*f)(unsigned int, char));
void		ft_striteri(char *s, void (*f)(unsigned int, char*));
void		ft_putchar_fd(char c, int fd);
void		ft_putstr_fd(char *s, int fd);
void		ft_putendl_fd(char *s, int fd);
void		ft_putnbr_fd(int n, int fd);
char		*get_next_line(int fd);
t_list		*ft_lstnew(void *content);
void		ft_lstadd_front(t_list **lst, t_list *new);
void		ft_lstadd_back(t_list **lst, t_list *new);
int			ft_lstsize(t_list *lst);
void		ft_lstdelone(t_list *lst, void (*del)(void *));
void		ft_lstclear(t_list **lst, void (*del)(void *));
void		ft_lstiter(t_list *lst, void (*f)(void *));
t_list		*ft_lstlast(t_list *lst);
t_list		*ft_lstmap(t_list *lst, void *(*f)(void *), void (*del)(void *));
#endif
