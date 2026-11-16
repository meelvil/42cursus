---
tags: [ft_printf, tests]
---

# Tests

Retour : [[00 - Accueil]] · Cases à cocher : [[03 - Plan et checklist]]

## Principe
Pour chaque cas : même appel avec `printf` et `ft_printf`, on compare **la sortie** et **la valeur de retour**.

## `tests/main.c` (à adapter)
```c
#include <stdio.h>
#include <limits.h>
#include "../ft_printf.h"

#define TEST(...) do { \
	int	r1; \
	int	r2; \
	printf("[std] "); \
	r1 = printf(__VA_ARGS__); \
	printf("| ret=%d\n", r1); \
	printf("[ft ] "); \
	fflush(stdout); \
	r2 = ft_printf(__VA_ARGS__); \
	printf("| ret=%d\n", r2); \
	if (r1 != r2) \
		printf("!!! RETOUR DIFFERENT\n"); \
} while (0)

int	main(void)
{
	int	x;

	x = 42;
	TEST("hello");
	TEST("%c", 'a');
	TEST("%d", INT_MIN);
	TEST("%p", &x);
	return (0);
}
```

> [!info] Pourquoi `fflush(stdout)` ?
> `printf` passe par un buffer, `ft_printf` écrit directement avec `write`. Sans `fflush`, les sorties peuvent apparaître dans le désordre. Bonne question à te poser : que se passerait-il si `ft_printf` utilisait `printf` en interne ?

## Compilation
```bash
make
cc -Wall -Wextra tests/main.c -L. -lftprintf -o test
./test
```
Le `main` de test peut être compilé sans `-Werror` : GCC avertit sur certains formats volontairement bizarres (`NULL` avec `%s`, par exemple). C'est **ta lib** qui doit passer `-Werror`.

## Matrice de cas

| Conversion | Cas à tester |
|------------|--------------|
| texte seul | `"hello"`, `""`, `"a\nb"` |
| `%c` | `'a'`, `'0'`, `0`, `'\n'` |
| `%s` | `"hello"`, `""`, `NULL` |
| `%p` | `&x`, `NULL`, `(void *)-1`, `(void *)1`, `LONG_MAX`, `LONG_MIN`, `ULONG_MAX` (castés en pointeur) |
| `%d` `%i` | `0`, `42`, `-42`, `INT_MAX`, `INT_MIN` |
| `%u` | `0`, `42`, `UINT_MAX`, `-1` |
| `%x` `%X` | `0`, `255`, `UINT_MAX`, `-1` |
| `%%` | `"%%"`, `"100%%"`, `"%%%%"` |
| mélange | `"%c%s%d"`, `"a%db%sc"`, plusieurs conversions du même type à la suite |
| limites | `%` seul en fin de format (juste vérifier : pas de crash) |

## Mémoire
```bash
valgrind --leak-check=full ./test
# ou, à la compilation du test :
cc -g -fsanitize=address tests/main.c -L. -lftprintf -o test_asan && ./test_asan
```
Attendu : 0 erreur, 0 fuite. Rappel : sans `malloc`, il ne doit rien y avoir à fuir.

## Vérifs du Makefile
- `make` puis `make` : la 2e fois, rien n'est recompilé ni ré-archivé.
- `ar -t libftprintf.a` : liste exactement tes fichiers objets.
- `make fclean && make` : repart de zéro sans erreur.

## Norme
```bash
norminette
```
(Sur ton Ubuntu perso : `pip install norminette` si absent.)

## Testeurs communautaires
Utile **après** tes propres tests, jamais à la place. Cherche « printf tester 42 » sur GitHub, lis le README, et comprends chaque échec avant de corriger.

> [!tip] Un test qui échoue = une info
> Note-le dans [[07 - Journal]] avec l'entrée, l'attendu et l'obtenu : c'est exactement ce qu'il faudra donner à Claude si tu bloques ([[06 - Prompts types]]).
