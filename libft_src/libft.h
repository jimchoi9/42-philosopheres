/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   libft.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jeakim <jeakim@student.42seoul.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/20 21:22:29 by jimchoi           #+#    #+#             */
/*   Updated: 2024/06/21 16:19:08 by jeakim           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LIBFT_H
# define LIBFT_H

# ifndef BUFFER_SIZE
#  define BUFFER_SIZE 10
# endif

# include <unistd.h>
# include <stdlib.h>
# include <stdarg.h>

typedef struct s_list
{
	void			*content;
	struct s_list	*next;
}	t_list;

typedef struct s_node
{
	int				fd;
	int				size;
	char			save[BUFFER_SIZE + 1];
	char			buf[BUFFER_SIZE + 1];
	struct s_node	*next;
}					t_node;

long long	ft_atoi(const char *str);
void		*ft_bzero(void *s, size_t n);
int			ft_isalnum(int c);
int			ft_isalpha(int c);
int			ft_isascii(int c);
int			ft_isdigit(int c);
int			ft_isprint(int c);
int			ft_toupper(int c);
int			ft_tolower(int c);
void		*ft_memcpy(void *dst, const void *src, size_t n);
void		*ft_memset(void *b, int c, size_t len);
void		*ft_memmove(void *dst, const void *src, size_t len);
void		*ft_memchr(const void *s, int c, size_t n);
int			ft_memcmp(const void *s1, const void *s2, size_t n);
char		*ft_strchr(const char *s, int c);
size_t		ft_strlcat(char *dst, const char *src, size_t size);
size_t		ft_strlcpy(char *dst, const char *src, size_t size);
size_t		ft_strlen(const char *s);
int			ft_strncmp(const char *s1, const char *s2, size_t n);
char		*ft_strnstr(const char *haystack, const char *needle, size_t len);
char		*ft_strrchr(const char *s, int c);
char		*ft_strdup(char *src);
void		*ft_calloc(size_t count, size_t size);
char		*ft_substr(char const *s, unsigned int start, size_t len);
char		*ft_strjoin(char const *s1, char const *s2);
char		*ft_strtrim(char const *s1, char const *set);
char		**ft_split(char const *s, char c);
char		*ft_itoa(int n);
char		*ft_strmapi(char const *s, char (*f)(unsigned int, char));
void		ft_striteri(char *s, void (*f)(unsigned int, char*));
void		ft_putchar_fd(char c, int fd);
void		ft_putstr_fd(char *s, int fd);
void		ft_putendl_fd(char *s, int fd);
void		ft_putnbr_fd(int n, int fd);
// char	*get_next_line(int fd);
// t_list	*find_node(t_list **head, int fd);
// char	*clear(t_list **lst, t_list *node, int fd, char *line);
// int		read_line(t_list *node, int fd);
// char	*make_line(t_list *node, char *line, int size);
// int		find_line(t_list *node);
// void	make_save(t_list *node, int size);
// int		get_strlen(char *s);
// char	*get_strchr(const char *s, int c);
t_list		*ft_lstnew(void *content);
void		ft_lstadd_front(t_list **lst, t_list *new);
int			ft_lstsize(t_list *lst);
t_list		*ft_lstlast(t_list *lst);
void		ft_lstadd_back(t_list **lst, t_list *new);
void		ft_lstdelone(t_list *lst, void (*del)(void*));
void		ft_lstclear(t_list **lst, void (*del)(void*));
void		ft_lstiter(t_list *lst, void (*f)(void *));
t_list		*ft_lstmap(t_list *lst, void *(*f)(void *), void (*del)(void *));
char		*get_next_line(int fd);
// char	*ft_strchr(const char *s, int c);
t_node		*find_node(t_node **head, int fd);
char		*clear(t_node **lst, t_node *node, int fd, char *line);
int			read_line(t_node **node, int fd);
// int		ft_strlen(char *s);
char		*make_line(t_node *node, char *line, int size);
int			find_line(t_node *node);
// void	*ft_bzero(void *s, size_t n);
void		make_save(t_node *node, int size);
int			ft_putchar_fd_p(char c, int fd);
int			ft_putstr_fd_p(char *s, int fd);
int			ft_putnbr_fd_p(long n, int fd);
int			ft_putnbr_fd_u(unsigned int n, int fd);
int			ft_putnbr_fd_hex(unsigned int n, int fd, int mode);
int			ft_putnbrstr_fd_hex(unsigned long n, int fd);
int			ft_putstr_fd_hex(void *s, int fd);
int			ft_printf_logic(const char *format, va_list ap);
int			ft_printf(const char *format, ...);

#endif