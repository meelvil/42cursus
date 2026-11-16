/*
** Libft tester (not pushed: lives in stuff/)
**
** Build + run, from the libft root:
**   cc -Wall -Wextra -Werror -I. stuff/main.c ft_*.c -o stuff/test
**   ./stuff/test                     -> run everything
**   ./stuff/test ft_split ft_itoa    -> only these (ft_x, x or ft_x.c work)
**   ./stuff/test -l                  -> list available tests
**
** Each test replays the mains commented in your .c files: it prints the
** call, what you got, what is expected, and OK / KO. Extra edge cases are
** checked silently (only shown when they fail). Each test runs in its own
** process, so a crash is reported as CRASH and the others keep running.
** Tip: add -fsanitize=address,undefined to catch leaks / overflows.
*/

#include <ctype.h>
#include <limits.h>
#include <stdint.h>
#include <stdio.h>
#include <string.h>
#include <sys/wait.h>
#include "libft.h"

#define GRN "\033[32m"
#define RED "\033[31m"
#define RST "\033[0m"

static int	g_ok;
static int	g_ko;
static char	*g_cur = "";

/* silent edge case: only printed when it fails */
#define T(cond) do { if (cond) g_ok++; else { g_ko++; \
	printf("  " RED "KO" RST " edge line %d: %s\n", __LINE__, #cond); } } \
	while (0)

/* ------------------------- display + compare ----------------------------- */

static void	verdict(int ok)
{
	if (ok)
		g_ok++;
	else
		g_ko++;
	printf("%s\n", ok ? GRN "OK" RST : RED "KO" RST);
}

static int	sign(long n)
{
	return ((n > 0) - (n < 0));
}

static void	chk_int(char *call, long got, long exp)
{
	printf("  %-42s -> %ld (attendu %ld)  ", call, got, exp);
	verdict(got == exp);
}

/* only zero / non-zero matters (is* functions) */
static void	chk_bool(char *call, long got, long exp)
{
	printf("  %-42s -> %ld (attendu %ld)  ", call, got, exp);
	verdict(!!got == !!exp);
}

/* only the sign matters (cmp functions) */
static void	chk_cmp(char *call, long got, long exp)
{
	printf("  %-42s -> %ld (attendu %ld, meme signe)  ", call, got, exp);
	verdict(sign(got) == sign(exp));
}

static void	chk_chr(char *call, int got, int exp)
{
	printf("  %-42s -> '%c' (attendu '%c')  ", call, got, exp);
	verdict(got == exp);
}

static void	chk_str(char *call, char *got, char *exp, int do_free)
{
	printf("  %-42s -> \"%s\" (attendu \"%s\")  ", call,
		got ? got : "(null)", exp ? exp : "(null)");
	verdict((!got && !exp) || (got && exp && strcmp(got, exp) == 0));
	if (do_free)
		free(got);
}

/* pointers compared by address, shown as offset from base */
static void	chk_ptr(char *call, char *got, char *exp, char *base)
{
	printf("  %-42s -> ", call);
	if (got)
		printf("base+%ld", (long)(got - base));
	else
		printf("NULL");
	if (exp)
		printf(" (attendu base+%ld)  ", (long)(exp - base));
	else
		printf(" (attendu NULL)  ");
	verdict(got == exp);
}

/* print n bytes, non printable shown as \xx */
static void	show_mem(char *s, size_t n)
{
	size_t	i;

	i = 0;
	while (i < n)
	{
		if (isprint((unsigned char)s[i]))
			putchar(s[i]);
		else
			printf("\\%d", (unsigned char)s[i]);
		i++;
	}
}

static void	chk_mem(char *call, char *got, char *exp, size_t n)
{
	printf("  %s\n    -> \"", call);
	show_mem(got, n);
	printf("\"\n    attendu \"");
	show_mem(exp, n);
	printf("\"  ");
	verdict(memcmp(got, exp, n) == 0);
}

#define I(call, exp) chk_int(#call, (long)(call), (long)(exp))
#define B(call, exp) chk_bool(#call, (long)(call), (long)(exp))
#define CMP(call, exp) chk_cmp(#call, (long)(call), (long)(exp))
#define C(call, exp) chk_chr(#call, (call), (exp))
#define S(call, exp) chk_str(#call, (call), (exp), 0)
#define SF(call, exp) chk_str(#call, (call), (exp), 1)
#define P(call, exp, base) chk_ptr(#call, (call), (exp), (base))

/* ----------------------------- helpers ----------------------------------- */

static char	up_i(unsigned int i, char c)
{
	(void)i;
	return ((char)toupper(c));
}

static char	plus_i(unsigned int i, char c)
{
	return (c + (char)i);
}

static void	up_ptr(unsigned int i, char *c)
{
	(void)i;
	*c = (char)toupper(*c);
}

static void	del_free(void *p)
{
	free(p);
}

static void	del_none(void *p)
{
	(void)p;
}

static void	*dup_up(void *p)
{
	char	*s;
	size_t	i;

	s = ft_strdup((char *)p);
	i = 0;
	while (s && s[i])
	{
		s[i] = (char)toupper(s[i]);
		i++;
	}
	return (s);
}

static void	up_content(void *p)
{
	char	*s;

	s = (char *)p;
	while (*s)
	{
		*s = (char)toupper(*s);
		s++;
	}
}

/* what a *_fd function wrote, read back through a pipe */
static char	g_buf[256];

static char	*cap_end(int *p)
{
	ssize_t	n;

	close(p[1]);
	n = read(p[0], g_buf, sizeof(g_buf) - 1);
	(void)n;
	close(p[0]);
	return (g_buf);
}

static char	*cap_str(void (*f)(char *, int), char *arg)
{
	int	p[2];

	memset(g_buf, 0, sizeof(g_buf));
	if (pipe(p) == -1)
		return (g_buf);
	f(arg, p[1]);
	return (cap_end(p));
}

static char	*cap_chr(char c)
{
	int	p[2];

	memset(g_buf, 0, sizeof(g_buf));
	if (pipe(p) == -1)
		return (g_buf);
	ft_putchar_fd(c, p[1]);
	return (cap_end(p));
}

static char	*cap_nbr(int n)
{
	int	p[2];

	memset(g_buf, 0, sizeof(g_buf));
	if (pipe(p) == -1)
		return (g_buf);
	ft_putnbr_fd(n, p[1]);
	return (cap_end(p));
}

/* ------------------------------ part 1 ----------------------------------- */

static void	t_isalpha(void)
{
	int	c;

	B(ft_isalpha('M'), 1);
	B(ft_isalpha('1'), 0);
	c = -1;
	while (++c < 256)
		T(!!ft_isalpha(c) == !!isalpha(c));
}

static void	t_isdigit(void)
{
	int	c;

	B(ft_isdigit('1'), 1);
	B(ft_isdigit('M'), 0);
	c = -1;
	while (++c < 256)
		T(!!ft_isdigit(c) == !!isdigit(c));
}

static void	t_isalnum(void)
{
	int	c;

	B(ft_isalnum('1'), 1);
	B(ft_isalnum('M'), 1);
	B(ft_isalnum('-'), 0);
	c = -1;
	while (++c < 256)
		T(!!ft_isalnum(c) == !!isalnum(c));
}

static void	t_isascii(void)
{
	int	c;

	B(ft_isascii('\n'), 1);
	B(ft_isascii(200), 0);
	c = -1;
	while (++c < 256)
		T(!!ft_isascii(c) == !!isascii(c));
}

static void	t_isprint(void)
{
	int	c;

	B(ft_isprint('M'), 1);
	B(ft_isprint('\n'), 0);
	c = -1;
	while (++c < 256)
		T(!!ft_isprint(c) == !!isprint(c));
}

static void	t_strlen(void)
{
	I(ft_strlen("Melvil"), 6);
	T(ft_strlen("") == 0);
	T(ft_strlen("with\0hidden") == 4);
}

static void	t_memset(void)
{
	char	input[] = "12345 / Cette phrase commencera par 5 'a'";
	char	exp[] = "aaaaa / Cette phrase commencera par 5 'a'";
	char	a[10];
	char	b[10];

	ft_memset(input, 'a', 5);
	chk_mem("ft_memset(input, 'a', 5)", input, exp, sizeof(exp));
	memset(a, 'x', 10);
	memset(b, 'x', 10);
	ft_memset(a, 256 + 'B', 3);
	memset(b, 256 + 'B', 3);
	T(memcmp(a, b, 10) == 0);
	T(ft_memset(a, 0, 0) == a);
}

static void	t_bzero(void)
{
	char	input[] = "12345 / Cette phrase commencera par 5 '0'";
	char	exp[] = "\0\0\0\0\0 / Cette phrase commencera par 5 '0'";

	ft_bzero(input, 5);
	chk_mem("ft_bzero(input, 5)", input, exp, sizeof(exp));
	ft_bzero(input, 0);
	T(memcmp(input, exp, sizeof(exp)) == 0);
}

static void	t_memcpy(void)
{
	char	buf[] = "aaavil";
	char	*output;

	output = ft_memcpy(buf, "Mel", 3);
	S(output, "Melvil");
	T(output == buf);
	T(ft_memcpy(buf, "zzz", 0) == buf);
}

static void	t_memmove(void)
{
	char	buf[] = "aaavil";
	char	a[20];
	char	b[20];
	char	*output;

	output = ft_memmove(buf, "Mel", 3);
	S(output, "Melvil");
	memset(a, 0, 20);
	memset(b, 0, 20);
	strcpy(a, "0123456789");
	strcpy(b, "0123456789");
	T(ft_memmove(a + 2, a, 6) == a + 2);
	memmove(b + 2, b, 6);
	T(memcmp(a, b, 20) == 0);
	ft_memmove(a, a + 3, 6);
	memmove(b, b + 3, 6);
	T(memcmp(a, b, 20) == 0);
}

static void	t_strlcpy(void)
{
	char	test[50] = "Hello ";
	char	src[50] = "Mister";
	char	d[10];

	I(ft_strlcpy(test, src, 2), 6);
	chk_mem("test apres ft_strlcpy(test, src, 2)", test, "M\0llo ", 6);
	memset(d, 'x', 10);
	T(ft_strlcpy(d, "hello", 10) == 5 && strcmp(d, "hello") == 0);
	memset(d, 'x', 10);
	T(ft_strlcpy(d, "hello world", 6) == 11 && strcmp(d, "hello") == 0);
	memset(d, 'x', 10);
	T(ft_strlcpy(d, "hello", 0) == 5 && d[0] == 'x');
}

static void	t_strlcat(void)
{
	char	dest[15] = "Hey";
	char	d[20];

	I(ft_strlcat(dest, "oMelvil", 2), 9);
	S(dest, "Hey");
	strcpy(d, "abc");
	T(ft_strlcat(d, "def", 20) == 6 && strcmp(d, "abcdef") == 0);
	strcpy(d, "abc");
	T(ft_strlcat(d, "defghi", 6) == 9 && strcmp(d, "abcde") == 0);
	T(ft_strlcat(d, "def", 0) == 3);
	d[0] = '\0';
	T(ft_strlcat(d, "xyz", 20) == 3 && strcmp(d, "xyz") == 0);
}

static void	t_toupper(void)
{
	int	c;

	C(ft_toupper('m'), 'M');
	c = -1;
	while (++c < 256)
		T(ft_toupper(c) == toupper(c));
}

static void	t_tolower(void)
{
	int	c;

	C(ft_tolower('M'), 'm');
	c = -1;
	while (++c < 256)
		T(ft_tolower(c) == tolower(c));
}

static void	t_strchr(void)
{
	char	*str;

	str = "Hello World";
	P(ft_strchr(str, '\0'), strchr(str, '\0'), str);
	P(ft_strchr(str, 'o'), strchr(str, 'o'), str);
	P(ft_strchr(str, 'z'), strchr(str, 'z'), str);
	T(ft_strchr(str, 'o' + 256) == strchr(str, 'o' + 256));
	T(ft_strchr("", 'a') == NULL);
}

static void	t_strrchr(void)
{
	char	*str;

	str = "Hello World";
	P(ft_strrchr(str, 'H'), strrchr(str, 'H'), str);
	P(ft_strrchr(str, 'o'), strrchr(str, 'o'), str);
	P(ft_strrchr(str, 'z'), strrchr(str, 'z'), str);
	T(ft_strrchr(str, '\0') == strrchr(str, '\0'));
}

static void	t_strncmp(void)
{
	CMP(ft_strncmp("Melvil", "Melviil", 5), strncmp("Melvil", "Melviil", 5));
	CMP(ft_strncmp("Melvil", "Melviil", 6), strncmp("Melvil", "Melviil", 6));
	T(sign(ft_strncmp("abc", "xyz", 0)) == 0);
	T(sign(ft_strncmp("", "", 5)) == 0);
	T(sign(ft_strncmp("a\200", "a\0", 2)) == sign(strncmp("a\200", "a\0", 2)));
}

static void	t_memchr(void)
{
	char	*str;

	str = "Hello World";
	P(ft_memchr(str, 'o', 5), memchr(str, 'o', 5), str);
	P(ft_memchr(str, 'W', 5), memchr(str, 'W', 5), str);
	P(ft_memchr(str, 'W', 11), memchr(str, 'W', 11), str);
	T(ft_memchr(str, 'H', 0) == NULL);
	T(ft_memchr("a\0b", 'b', 3) == memchr("a\0b", 'b', 3));
}

static void	t_memcmp(void)
{
	CMP(ft_memcmp("Melvil", "Meelvil", 5), memcmp("Melvil", "Meelvil", 5));
	CMP(ft_memcmp("Melvil", "Melvil", 6), memcmp("Melvil", "Melvil", 6));
	T(sign(ft_memcmp("abc", "xyz", 0)) == 0);
	T(sign(ft_memcmp("a\0b", "a\0c", 3)) == sign(memcmp("a\0b", "a\0c", 3)));
	T(sign(ft_memcmp("\200", "\0", 1)) == sign(memcmp("\200", "\0", 1)));
}

static void	t_strnstr(void)
{
	char	*s;

	s = "Hello World";
	S(ft_strnstr("Hello World", "World", 15), "World");
	S(ft_strnstr("Hello World", "World", 10), NULL);
	S(ft_strnstr("Hello World", "", 5), "Hello World");
	T(ft_strnstr(s, "hello", 4) == NULL);
	T(ft_strnstr("", "a", 5) == NULL);
	T(ft_strnstr("aaabc", "abc", 5) == &"aaabc"[2]);
}

static void	t_atoi(void)
{
	char	*tab[] = {"0", "42", "-42", "+42", "   \t\n12abc", "--1", "+-1",
		"abc", "", "2147483647", "-2147483648", " \v\f\r 7", "0042", NULL};
	int		i;

	I(ft_atoi("  +123"), 123);
	I(ft_atoi("-2147483648"), INT_MIN);
	I(ft_atoi("2147483647"), INT_MAX);
	i = -1;
	while (tab[++i])
		T(ft_atoi(tab[i]) == atoi(tab[i]));
}

static void	t_calloc(void)
{
	char	*wafpaf;
	char	*z;

	wafpaf = ft_calloc(7, sizeof(char));
	I(strlen(wafpaf), 0);
	z = calloc(7, sizeof(char));
	T(memcmp(wafpaf, z, 7) == 0);
	free(wafpaf);
	free(z);
	wafpaf = ft_calloc(5, sizeof(int));
	T(wafpaf && wafpaf[0] == 0 && wafpaf[19] == 0);
	free(wafpaf);
	wafpaf = ft_calloc(0, 0);
	T(wafpaf != NULL);
	free(wafpaf);
	T(ft_calloc(SIZE_MAX, 2) == NULL);
}

static void	t_strdup(void)
{
	char	*d;
	char	src[] = "Melvil";

	SF(ft_strdup("Melvil"), "Melvil");
	d = ft_strdup(src);
	T(d != NULL && d != src);
	free(d);
	d = ft_strdup("");
	T(d != NULL && d[0] == '\0');
	free(d);
}

/* ------------------------------ part 2 ----------------------------------- */

static void	t_substr(void)
{
	char	*r;

	SF(ft_substr("Hello World", 0, 5), "Hello");
	SF(ft_substr("Hello World", 6, 100), "World");
	SF(ft_substr("Hello", 10, 3), "");
	r = ft_substr("hello", 0, 0);
	T(r && strcmp(r, "") == 0);
	free(r);
	r = ft_substr("hello", 5, 3);
	T(r && strcmp(r, "") == 0);
	free(r);
	r = ft_substr("hello", 0, SIZE_MAX);
	T(r && strcmp(r, "hello") == 0);
	free(r);
}

static void	t_strjoin(void)
{
	char	*r;

	SF(ft_strjoin("Hello", " World"), "Hello World");
	SF(ft_strjoin("", "abc"), "abc");
	SF(ft_strjoin("", ""), "");
	r = ft_strjoin("abc", "");
	T(r && strcmp(r, "abc") == 0);
	free(r);
}

static void	t_strtrim(void)
{
	char	*r;

	SF(ft_strtrim(" x Hello x World x ", " x"), "Hello x World");
	SF(ft_strtrim("xxxx", "x"), "");
	SF(ft_strtrim("hello", ""), "hello");
	r = ft_strtrim("", "abc");
	T(r && strcmp(r, "") == 0);
	free(r);
	r = ft_strtrim("abcHELLOcba", "abc");
	T(r && strcmp(r, "HELLO") == 0);
	free(r);
}

/* shows the split result and checks it against exp */
static void	check_split(char *s, char c, char **exp)
{
	char	**r;
	int		i;
	int		ok;

	r = ft_split(s, c);
	printf("  ft_split(\"%s\", '%c')\n    -> ", s, c);
	ok = (r != NULL);
	i = 0;
	while (r && r[i])
	{
		printf("[%s] ", r[i]);
		ok = ok && exp[i] && strcmp(r[i], exp[i]) == 0;
		i++;
	}
	ok = ok && exp[i] == NULL;
	printf("\n    attendu ");
	i = -1;
	while (exp[++i])
		printf("[%s] ", exp[i]);
	printf(" %d mot(s)  ", i);
	verdict(ok);
	i = 0;
	while (r && r[i])
		free(r[i++]);
	free(r);
}

static void	t_split(void)
{
	char	*a[] = {"Hello", "World", "42", NULL};
	char	*b[] = {"abc", NULL};
	char	*c[] = {NULL};
	char	*d[] = {"a", "b", NULL};

	check_split("Hello World 42", ' ', a);
	check_split("   Hello   World  42   ", ' ', a);
	check_split("abc", ' ', b);
	check_split("", ' ', c);
	check_split("     ", ' ', c);
	check_split(",,a,,b,,", ',', d);
}

static void	t_itoa(void)
{
	SF(ft_itoa(-2147483648), "-2147483648");
	SF(ft_itoa(2147483647), "2147483647");
	SF(ft_itoa(0), "0");
	SF(ft_itoa(-42), "-42");
	SF(ft_itoa(1000), "1000");
	SF(ft_itoa(5), "5");
}

static void	t_strmapi(void)
{
	char	*r;

	SF(ft_strmapi("hello world", up_i), "HELLO WORLD");
	SF(ft_strmapi("aaaa", plus_i), "abcd");
	r = ft_strmapi("", up_i);
	T(r && strcmp(r, "") == 0);
	free(r);
}

static void	t_striteri(void)
{
	char	output[] = "Hello World";
	char	e[] = "";

	ft_striteri(output, up_ptr);
	S(output, "HELLO WORLD");
	ft_striteri(e, up_ptr);
	T(strcmp(e, "") == 0);
}

static void	t_putchar_fd(void)
{
	S(cap_chr('M'), "M");
	T(strcmp(cap_chr('\n'), "\n") == 0);
}

static void	t_putstr_fd(void)
{
	chk_str("ft_putstr_fd(\"Hello World\", fd)",
		cap_str(ft_putstr_fd, "Hello World"), "Hello World", 0);
	T(strcmp(cap_str(ft_putstr_fd, ""), "") == 0);
}

static void	t_putendl_fd(void)
{
	chk_str("ft_putendl_fd(\"Hello\", fd)",
		cap_str(ft_putendl_fd, "Hello"), "Hello\n", 0);
	chk_str("ft_putendl_fd(\"World\", fd)",
		cap_str(ft_putendl_fd, "World"), "World\n", 0);
	T(strcmp(cap_str(ft_putendl_fd, ""), "\n") == 0);
}

static void	t_putnbr_fd(void)
{
	chk_str("ft_putnbr_fd(14, fd)", cap_nbr(14), "14", 0);
	chk_str("ft_putnbr_fd(-2147483648, fd)", cap_nbr(INT_MIN),
		"-2147483648", 0);
	T(strcmp(cap_nbr(0), "0") == 0);
	T(strcmp(cap_nbr(-42), "-42") == 0);
	T(strcmp(cap_nbr(INT_MAX), "2147483647") == 0);
}

/* ------------------------------- bonus ----------------------------------- */

static void	t_lstnew(void)
{
	t_list	*new;

	new = ft_lstnew((void *)"Hello World");
	S((char *)(new->content), "Hello World");
	T(new->next == NULL);
	free(new);
	new = ft_lstnew(NULL);
	T(new && new->content == NULL && new->next == NULL);
	free(new);
}

static void	t_lstadd_front(void)
{
	t_list	*lst;
	t_list	*new;
	t_list	*new2;

	lst = NULL;
	new = ft_lstnew((void *)"Hello World");
	ft_lstadd_front(&lst, new);
	S((char *)(lst->content), "Hello World");
	T(lst == new && lst->next == NULL);
	new2 = ft_lstnew((void *)"Hi");
	ft_lstadd_front(&lst, new2);
	S((char *)(lst->content), "Hi");
	T(lst == new2 && lst->next == new);
	free(new);
	free(new2);
}

static void	t_lstsize(void)
{
	t_list	*node;
	t_list	*one;
	t_list	*two;
	t_list	*three;
	t_list	*four;

	node = NULL;
	one = ft_lstnew((char *)"Hello World");
	two = ft_lstnew((char *)"Hi there");
	three = ft_lstnew((char *)"What's up");
	four = ft_lstnew((char *)"Good evening");
	ft_lstadd_front(&node, four);
	ft_lstadd_front(&node, three);
	ft_lstadd_front(&node, two);
	ft_lstadd_front(&node, one);
	I(ft_lstsize(node), 4);
	I(ft_lstsize(NULL), 0);
	free(one);
	free(two);
	free(three);
	free(four);
}

static void	t_lstlast(void)
{
	t_list	*node;
	t_list	*one;
	t_list	*two;
	t_list	*three;
	t_list	*four;

	node = NULL;
	one = ft_lstnew((char *)"Hello World");
	two = ft_lstnew((char *)"Hi there");
	three = ft_lstnew((char *)"What's up");
	four = ft_lstnew((char *)"Good evening");
	ft_lstadd_front(&node, four);
	ft_lstadd_front(&node, three);
	ft_lstadd_front(&node, two);
	ft_lstadd_front(&node, one);
	S((char *)ft_lstlast(node)->content, "Good evening");
	T(ft_lstlast(node) == four);
	T(ft_lstlast(NULL) == NULL);
	free(one);
	free(two);
	free(three);
	free(four);
}

static void	t_lstadd_back(void)
{
	t_list	*node;
	t_list	*one;
	t_list	*two;
	t_list	*three;
	t_list	*four;
	t_list	*five;

	node = NULL;
	one = ft_lstnew((char *)"Hello World");
	two = ft_lstnew((char *)"Hi there");
	three = ft_lstnew((char *)"What's up");
	four = ft_lstnew((char *)"Good evening");
	five = ft_lstnew((char *)"Have a good day");
	ft_lstadd_front(&node, four);
	ft_lstadd_front(&node, three);
	ft_lstadd_front(&node, two);
	ft_lstadd_front(&node, one);
	ft_lstadd_back(&node, five);
	S((char *)ft_lstlast(node)->content, "Have a good day");
	I(ft_lstsize(node), 5);
	free(one);
	free(two);
	free(three);
	free(four);
	free(five);
	node = NULL;
	ft_lstadd_back(&node, ft_lstnew("x"));
	T(node && node->next == NULL);
	free(node);
}

static void	t_lstdelone(void)
{
	t_list	*node;
	t_list	*one;
	t_list	*two;
	t_list	*three;

	node = NULL;
	one = ft_lstnew((char *)ft_strdup("Hello World"));
	two = ft_lstnew((char *)ft_strdup("Hi there"));
	three = ft_lstnew((char *)ft_strdup("What's up"));
	ft_lstadd_back(&node, one);
	ft_lstadd_back(&node, two);
	ft_lstadd_back(&node, three);
	I(ft_lstsize(node), 3);
	ft_lstdelone(three, del_free);
	two->next = NULL;
	I(ft_lstsize(node), 2);
	ft_lstclear(&node, del_free);
	node = ft_lstnew("static");
	ft_lstdelone(node, del_none);
	T(1);
}

static void	t_lstclear(void)
{
	t_list	*node;
	t_list	*one;
	t_list	*two;
	t_list	*three;

	node = NULL;
	one = ft_lstnew((char *)ft_strdup("Hello World"));
	two = ft_lstnew((char *)ft_strdup("Hi there"));
	three = ft_lstnew((char *)ft_strdup("What's up"));
	ft_lstadd_back(&node, one);
	ft_lstadd_back(&node, two);
	ft_lstadd_back(&node, three);
	I(ft_lstsize(node), 3);
	ft_lstclear(&node, del_free);
	I(ft_lstsize(node), 0);
	T(node == NULL);
	ft_lstclear(&node, del_free);
	T(node == NULL);
}

static void	t_lstiter(void)
{
	t_list	*node;

	node = ft_lstnew((char *)ft_strdup("hello world"));
	S((char *)(node->content), "hello world");
	ft_lstiter(node, up_content);
	S((char *)(node->content), "HELLO WORLD");
	ft_lstiter(NULL, up_content);
	ft_lstclear(&node, del_free);
}

static void	t_lstmap(void)
{
	t_list	*lst;
	t_list	*mapped;
	t_list	*tmp;

	lst = NULL;
	ft_lstadd_back(&lst, ft_lstnew((void *)"hello"));
	ft_lstadd_back(&lst, ft_lstnew((void *)"world"));
	ft_lstadd_back(&lst, ft_lstnew((void *)"42"));
	mapped = ft_lstmap(lst, dup_up, del_free);
	I(ft_lstsize(mapped), 3);
	tmp = mapped;
	S((char *)tmp->content, "HELLO");
	tmp = tmp->next;
	S((char *)tmp->content, "WORLD");
	tmp = tmp->next;
	S((char *)tmp->content, "42");
	T(strcmp(lst->content, "hello") == 0);
	ft_lstclear(&mapped, del_free);
	while (lst)
	{
		tmp = lst;
		lst = lst->next;
		free(tmp);
	}
	T(ft_lstmap(NULL, dup_up, del_free) == NULL);
}

/* ------------------------------- driver ---------------------------------- */

typedef struct s_test
{
	char	*name;
	void	(*f)(void);
}	t_test;

#define E(n) {#n, t_##n}

static t_test	g_tests[] = {
	E(isalpha), E(isdigit), E(isalnum), E(isascii), E(isprint), E(strlen),
	E(memset), E(bzero), E(memcpy), E(memmove), E(strlcpy), E(strlcat),
	E(toupper), E(tolower), E(strchr), E(strrchr), E(strncmp), E(memchr),
	E(memcmp), E(strnstr), E(atoi), E(calloc), E(strdup),
	E(substr), E(strjoin), E(strtrim), E(split), E(itoa), E(strmapi),
	E(striteri), E(putchar_fd), E(putstr_fd), E(putendl_fd), E(putnbr_fd),
	E(lstnew), E(lstadd_front), E(lstsize), E(lstlast), E(lstadd_back),
	E(lstdelone), E(lstclear), E(lstiter), E(lstmap),
	{NULL, NULL}
};

static int	g_tot_ok;
static int	g_tot_ko;
static int	g_tot_crash;

/* run one test in a child; it reports its counters through a pipe */
static void	run(t_test *t)
{
	int		p[2];
	int		res[2];
	int		st;
	pid_t	pid;

	printf("== ft_%s\n", t->name);
	if (pipe(p) == -1)
		return ;
	pid = fork();
	if (pid == 0)
	{
		close(p[0]);
		g_cur = t->name;
		t->f();
		res[0] = g_ok;
		res[1] = g_ko;
		if (write(p[1], res, sizeof(res)) < 0)
			_exit(2);
		_exit(0);
	}
	close(p[1]);
	waitpid(pid, &st, 0);
	if (read(p[0], res, sizeof(res)) != (ssize_t)sizeof(res))
		res[0] = res[1] = 0;
	close(p[0]);
	g_tot_ok += res[0];
	g_tot_ko += res[1];
	if (WIFSIGNALED(st) || WEXITSTATUS(st) != 0)
	{
		g_tot_crash++;
		printf("  " RED "CRASH" RST " (signal %d)\n", WTERMSIG(st));
	}
}

/* "ft_split", "split" and "ft_split.c" all match */
static int	match(char *arg, char *name)
{
	size_t	len;

	if (strncmp(arg, "ft_", 3) == 0)
		arg += 3;
	len = strlen(arg);
	if (len > 2 && strcmp(arg + len - 2, ".c") == 0)
		len -= 2;
	return (strlen(name) == len && strncmp(arg, name, len) == 0);
}

int	main(int argc, char **argv)
{
	int	i;
	int	j;
	int	found;

	setvbuf(stdout, NULL, _IONBF, 0);
	if (argc == 2 && strcmp(argv[1], "-l") == 0)
	{
		i = -1;
		while (g_tests[++i].name)
			printf("ft_%s\n", g_tests[i].name);
		return (0);
	}
	if (argc == 1)
	{
		i = -1;
		while (g_tests[++i].name)
			run(&g_tests[i]);
	}
	j = 0;
	while (++j < argc)
	{
		found = 0;
		i = -1;
		while (g_tests[++i].name)
			if (match(argv[j], g_tests[i].name) && ++found)
				run(&g_tests[i]);
		if (!found)
			printf("unknown test: %s (try -l)\n", argv[j]);
	}
	printf("\n" GRN "%d OK" RST ", " RED "%d KO" RST ", %d crash\n",
		g_tot_ok, g_tot_ko, g_tot_crash);
	return (g_tot_ko != 0 || g_tot_crash != 0);
}
