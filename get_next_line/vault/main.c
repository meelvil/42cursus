/* Fichier de test uniquement : ne pas le rendre. */

#include <stdio.h>
#include <string.h>
#include "get_next_line.h"

#define GREEN "\033[32m"
#define RED "\033[31m"
#define RESET "\033[0m"
#define W 24
#define STA "________________________________________\
_______________________________________\n"
#define SEP "|__________________________|\
__________________________|__________________________|\n"

static void	print_line(char *test, const char *got, const char *want, int ok)
{
	printf("| %-*s | %-*s | %-*s |", W, test, W, got, W, want);
	if (ok)
		printf(GREEN " [OK]" RESET "\n");
	else
		printf(RED " [KO]" RESET "\n");
	printf(SEP);
}

static void	test_len(char *test, char *s, int want)
{
	char	a[16];
	char	b[16];
	int		got;

	got = ft_strlen(s);
	sprintf(a, "%d", got);
	sprintf(b, "%d", want);
	print_line(test, a, b, got == want);
}

/* got vient d'un malloc : il est libere ici. */
static void	test_str(char *test, char *got, const char *want)
{
	int			ok;
	const char	*a;
	const char	*b;

	if (!got || !want)
		ok = (!got && !want);
	else
		ok = (strcmp(got, want) == 0);
	a = got;
	if (!a)
		a = "(null)";
	b = want;
	if (!b)
		b = "(null)";
	print_line(test, a, b, ok);
	free(got);
}

/* got pointe dans la chaine d'origine : pas de free. */
static void	test_chr(char *test, char *got, char *want)
{
	const char	*a;
	const char	*b;

	a = got;
	if (!a)
		a = "(null)";
	b = want;
	if (!b)
		b = "(null)";
	print_line(test, a, b, got == want);
}

static void	title(char *name)
{
	printf("\n%s\n", name);
	printf(STA);
	printf("| %-*s | %-*s | %-*s |\n", W, "test", W, "obtenu", W, "attendu");
	printf(SEP);
}

int	main(void)
{
	char	s[] = "Bonjour";
	char	line[] = "ab\ncd";
	char	empty[] = "";

	title("ft_strchr");
	test_chr("\"Bonjour\", 'B'", ft_strchr(s, 'B'), s);
	test_chr("\"Bonjour\", 'o' (1er)", ft_strchr(s, 'o'), s + 1);
	test_chr("\"Bonjour\", 'r'", ft_strchr(s, 'r'), s + 6);
	test_chr("\"Bonjour\", 'z'", ft_strchr(s, 'z'), NULL);
	/* +1 : on saute le \n pour ne pas casser le tableau. */
	if (ft_strchr(line, '\n') == line + 2)
		test_chr("\"ab\\ncd\", '\\n' (+1)", ft_strchr(line, '\n') + 1,
			line + 3);
	else
		print_line("\"ab\\ncd\", '\\n'", "mauvaise adresse", "index 2", 0);
	test_chr("\"\", 'a'", ft_strchr(empty, 'a'), NULL);
	test_chr("NULL, 'a'", ft_strchr(NULL, 'a'), NULL);

	title("ft_strlen");
	test_len("\"Melvil\"", "Melvil", 6);
	test_len("\"\"", "", 0);
	test_len("NULL", NULL, 0);

	title("ft_substr");
	test_str("\"Bonjour\", 0, 3", ft_substr("Bonjour", 0, 3), "Bon");
	test_str("\"Bonjour\", 3, 4", ft_substr("Bonjour", 3, 4), "jour");
	test_str("\"Bonjour\", 3, 100", ft_substr("Bonjour", 3, 100), "jour");
	test_str("\"Bonjour\", 2, 0", ft_substr("Bonjour", 2, 0), "");
	test_str("\"Bonjour\", 7, 3", ft_substr("Bonjour", 7, 3), "");
	test_str("\"Bonjour\", 50, 3", ft_substr("Bonjour", 50, 3), "");
	test_str("NULL, 0, 3", ft_substr(NULL, 0, 3), NULL);

	/* s1 est libere par ft_strjoin : strdup ou NULL, jamais "texte". */
	title("ft_strjoin");
	test_str("\"abc\" + \"de\"", ft_strjoin(strdup("abc"), "de"), "abcde");
	test_str("\"\" + \"de\"", ft_strjoin(strdup(""), "de"), "de");
	test_str("\"abc\" + \"\"", ft_strjoin(strdup("abc"), ""), "abc");
	test_str("NULL + \"de\"", ft_strjoin(NULL, "de"), "de");
	test_str("\"abc\" + NULL", ft_strjoin(strdup("abc"), NULL), "abc");
	test_str("NULL + NULL", ft_strjoin(NULL, NULL), NULL);
	return (0);
}
