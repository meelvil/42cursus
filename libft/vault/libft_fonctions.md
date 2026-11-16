# Libft : ce que le man attend vraiment de chaque fonction

## Pourquoi `int c` alors qu'on parle d'un caractère ?

Les fonctions de `<ctype.h>` (isalpha, toupper...) et plusieurs fonctions de `<string.h>` (strchr, memset...) prennent un `int` pour des raisons historiques : en C, un caractère lu (par exemple avec `getchar`) peut valoir `EOF` (-1), qui ne rentre pas dans un `char`. Donc on utilise un `int`, qui peut contenir soit une valeur de caractère (0 à 255), soit `EOF`.

**Pour la libft, tu dois garder exactement le même prototype que l'original** (seul le préfixe `ft_` change). Tu écris donc `int ft_isalpha(int c)`, pas `char c`. À l'intérieur, tu compares `c` directement avec `'a'`, `'Z'`, etc., ça fonctionne très bien.

Deux fonctions demandent un petit cast, détaillé plus bas :
- `strchr` / `strrchr` : `c` est converti en `char`.
- `memset` / `memchr` : `c` est converti en `unsigned char`.

Note : `strlcpy`, `strlcat` et `strnstr` viennent de BSD. Sur Linux, leur page man n'existe pas toujours (ou vient du paquet `libbsd`). Les descriptions ci-dessous suivent le comportement BSD, qui est celui attendu par la libft.

---

## 1. Fonctions de classification (`ctype`)

Toutes renvoient **une valeur non nulle (vrai)** si la condition est remplie, **0** sinon. Le sujet n'impose pas que ce soit exactement 1, mais renvoyer 1 est le plus simple.

### ft_isalpha
```c
int ft_isalpha(int c);
```
Vrai si `c` est une lettre : `'A'` à `'Z'` ou `'a'` à `'z'`. Tout le reste (chiffres, ponctuation, espaces) donne 0.

### ft_isdigit
```c
int ft_isdigit(int c);
```
Vrai si `c` est un chiffre décimal : `'0'` à `'9'`.

### ft_isalnum
```c
int ft_isalnum(int c);
```
Vrai si `c` est une lettre **ou** un chiffre, donc `isalpha(c) || isdigit(c)`. Tu peux réutiliser tes deux fonctions précédentes.

### ft_isascii
```c
int ft_isascii(int c);
```
Vrai si `c` est dans la table ASCII standard, c'est-à-dire une valeur de **0 à 127** inclus. Ce n'est pas lié aux lettres : le caractère `'\n'` (10) est ASCII aussi.

### ft_isprint
```c
int ft_isprint(int c);
```
Vrai si `c` est un caractère **imprimable**, c'est-à-dire de **32 (espace) à 126 (`~`)** inclus. Les caractères de contrôle (0 à 31) et 127 (DEL) ne sont pas imprimables.

---

## 2. Fonctions sur les chaînes (`string.h`)

### ft_strlen
```c
size_t ft_strlen(const char *s);
```
Renvoie le nombre de caractères de `s` **avant** le `'\0'` final, sans le compter. `"abc"` donne 3, `""` donne 0.

### ft_strlcpy
```c
size_t ft_strlcpy(char *dst, const char *src, size_t dstsize);
```
Copie `src` dans `dst` en n'écrivant **jamais plus de `dstsize` octets** au total (le `'\0'` compris). Elle copie au maximum `dstsize - 1` caractères, puis ajoute toujours un `'\0'` (sauf si `dstsize` vaut 0, auquel cas elle n'écrit rien).

**Valeur de retour :** toujours la longueur de `src` (`strlen(src)`), que la copie ait été tronquée ou non. Ça permet de détecter une troncature : `retour >= dstsize` signifie que `src` n'a pas tenu entièrement.

### ft_strlcat
```c
size_t ft_strlcat(char *dst, const char *src, size_t dstsize);
```
Ajoute `src` à la fin de `dst`. Attention : `dstsize` est la **taille totale du buffer `dst`**, pas la place restante. Elle écrit au maximum `dstsize - strlen(dst) - 1` caractères de `src`, puis termine par un `'\0'`.

**Valeur de retour :** la longueur qu'aurait eue la chaîne si tout avait tenu, soit `strlen(dst) + strlen(src)`. Cas particulier : si `dstsize` est inférieur ou égal à `strlen(dst)` (pas de place du tout), elle n'écrit rien et renvoie `dstsize + strlen(src)`. Dans ce calcul, on ne lit jamais `dst` au-delà de `dstsize`.

### ft_toupper
```c
int ft_toupper(int c);
```
Si `c` est une lettre minuscule (`'a'` à `'z'`), renvoie la majuscule correspondante. Sinon renvoie `c` **inchangé** (chiffres, majuscules, ponctuation...).

### ft_tolower
```c
int ft_tolower(int c);
```
Si `c` est une lettre majuscule (`'A'` à `'Z'`), renvoie la minuscule correspondante. Sinon renvoie `c` inchangé.

### ft_strchr
```c
char *ft_strchr(const char *s, int c);
```
Cherche la **première** occurrence du caractère `c` dans `s` et renvoie un pointeur vers cet endroit dans la chaîne (pas une copie). Renvoie `NULL` si absent. `c` est converti en `char` avant la comparaison : `(char)c`.

**Piège :** le `'\0'` final fait partie de la chaîne pour cette fonction. `ft_strchr(s, '\0')` doit renvoyer un pointeur vers le terminateur, pas `NULL`.

### ft_strrchr
```c
char *ft_strrchr(const char *s, int c);
```
Comme `strchr`, mais cherche la **dernière** occurrence (en partant de la fin). Même règle pour `c` (converti en `char`) et même piège : chercher `'\0'` renvoie un pointeur vers le terminateur.

### ft_strncmp
```c
int ft_strncmp(const char *s1, const char *s2, size_t n);
```
Compare `s1` et `s2` caractère par caractère, sur **au maximum `n` caractères**. La comparaison s'arrête dès qu'une différence est trouvée ou qu'un `'\0'` est atteint.

**Retour :** 0 si les chaînes sont égales sur les `n` premiers caractères (ou si `n` vaut 0). Sinon la différence entre les deux premiers caractères différents, **lus comme `unsigned char`** : `(unsigned char)s1[i] - (unsigned char)s2[i]`. Le signe compte (négatif si `s1` < `s2`, positif sinon), et le cast en `unsigned char` est important pour les caractères au-delà de 127.

### ft_strnstr
```c
char *ft_strnstr(const char *haystack, const char *needle, size_t len);
```
Cherche la chaîne `needle` (l'aiguille) dans `haystack` (la botte de foin), en regardant **au maximum `len` caractères** de `haystack`. Il faut que `needle` tienne **entièrement** dans ces `len` caractères pour être trouvée. La recherche s'arrête aussi au `'\0'` de `haystack`.

**Retour :** un pointeur vers le début de la première occurrence dans `haystack`. Si `needle` est vide (`""`), renvoie `haystack`. Si `needle` n'est pas trouvée, renvoie `NULL`.

### ft_strdup
```c
char *ft_strdup(const char *s1);
```
Crée une **copie** de `s1` dans de la mémoire nouvellement allouée avec `malloc` : il faut `strlen(s1) + 1` octets (le `+1` est pour le `'\0'`). Copie la chaîne, `'\0'` compris, et renvoie le pointeur. Renvoie `NULL` si `malloc` échoue. L'appelant devra faire `free` du résultat.

---

## 3. Fonctions sur la mémoire (`string.h`)

Ces fonctions travaillent sur des **octets bruts**, pas sur des chaînes : elles ne s'arrêtent **pas** au `'\0'` et ne s'intéressent qu'au nombre d'octets `n`. En général, on les code en castant les pointeurs `void *` vers `unsigned char *` pour pouvoir les parcourir.

### ft_memset
```c
void *ft_memset(void *b, int c, size_t len);
```
Remplit les `len` premiers octets de la zone mémoire `b` avec la valeur `c` (convertie en `unsigned char`). Renvoie `b` (le pointeur de départ, inchangé). Exemple : `memset(buf, 'x', 3)` met `'x'` dans les 3 premiers octets de `buf`.

### ft_bzero
```c
void ft_bzero(void *s, size_t n);
```
Met à 0 les `n` premiers octets de `s`. C'est l'équivalent de `memset(s, 0, n)`. **Ne renvoie rien** (`void`).

### ft_memcpy
```c
void *ft_memcpy(void *dst, const void *src, size_t n);
```
Copie `n` octets de `src` vers `dst`. Renvoie `dst`. Les zones **ne doivent pas se chevaucher** : si elles se chevauchent, le comportement est indéfini (c'est justement le rôle de `memmove` de gérer ce cas). Le cas `dst` et `src` tous deux `NULL` est souvent testé : renvoyer `dst` sans copier.

### ft_memmove
```c
void *ft_memmove(void *dst, const void *src, size_t len);
```
Copie `len` octets de `src` vers `dst`, **même si les zones se chevauchent**. Renvoie `dst`. La copie doit se comporter comme si elle passait par un tampon intermédiaire.

**Principe :**
- Si `dst < src` : copie du début vers la fin (sens normal).
- Si `dst > src` : copie de la fin vers le début, pour ne pas écraser des octets de `src` pas encore copiés.

### ft_memchr
```c
void *ft_memchr(const void *s, int c, size_t n);
```
Cherche la première occurrence de l'octet `c` (converti en `unsigned char`) dans les `n` premiers octets de `s`. Renvoie un pointeur vers cet octet, ou `NULL` s'il n'est pas trouvé. Contrairement à `strchr`, elle ne s'arrête pas à un `'\0'` et ne regarde jamais au-delà de `n` octets.

### ft_memcmp
```c
int ft_memcmp(const void *s1, const void *s2, size_t n);
```
Compare les `n` premiers octets de `s1` et `s2`, lus comme `unsigned char`. Renvoie 0 s'ils sont tous égaux (ou si `n` vaut 0), sinon la différence entre les deux premiers octets différents : `(unsigned char)s1[i] - (unsigned char)s2[i]`. Différence avec `strncmp` : elle **ne s'arrête pas** au `'\0'`, elle va jusqu'à `n` octets ou jusqu'à la première différence.

### ft_calloc
```c
void *ft_calloc(size_t count, size_t size);
```
Alloue de la mémoire pour `count` éléments de `size` octets chacun (donc `count * size` octets au total) et **met toute cette zone à 0**. Renvoie le pointeur, ou `NULL` si l'allocation échoue. Tu peux faire un `malloc(count * size)` puis un `ft_bzero`. Bonne pratique : si `count * size` dépasse la capacité d'un `size_t` (débordement), renvoyer `NULL` au lieu d'allouer une taille fausse.

---

## 4. Conversion

### ft_atoi
```c
int ft_atoi(const char *str);
```
Convertit le début de la chaîne `str` en entier (`int`). Les étapes, dans l'ordre :
1. **Ignorer les espaces** de début : espace, `\t`, `\n`, `\v`, `\f`, `\r`.
2. Lire **un seul** signe optionnel, `+` ou `-`. Un `-` rend le résultat négatif.
3. Lire les **chiffres** consécutifs et construire le nombre (`résultat = résultat * 10 + chiffre`).
4. S'arrêter au **premier caractère qui n'est pas un chiffre**, le reste de la chaîne est ignoré.

Si aucun chiffre n'est trouvé, renvoie 0. Il n'y a pas de gestion d'erreur : `"abc"` donne 0, `"  -42abc"` donne -42.

---

## Récapitulatif des prototypes (à copier dans `libft.h`)

```c
int		ft_isalpha(int c);
int		ft_isdigit(int c);
int		ft_isalnum(int c);
int		ft_isascii(int c);
int		ft_isprint(int c);
size_t	ft_strlen(const char *s);
void	*ft_memset(void *b, int c, size_t len);
void	ft_bzero(void *s, size_t n);
void	*ft_memcpy(void *dst, const void *src, size_t n);
void	*ft_memmove(void *dst, const void *src, size_t len);
size_t	ft_strlcpy(char *dst, const char *src, size_t dstsize);
size_t	ft_strlcat(char *dst, const char *src, size_t dstsize);
int		ft_toupper(int c);
int		ft_tolower(int c);
char	*ft_strchr(const char *s, int c);
char	*ft_strrchr(const char *s, int c);
int		ft_strncmp(const char *s1, const char *s2, size_t n);
void	*ft_memchr(const void *s, int c, size_t n);
int		ft_memcmp(const void *s1, const void *s2, size_t n);
char	*ft_strnstr(const char *haystack, const char *needle, size_t len);
int		ft_atoi(const char *str);
void	*ft_calloc(size_t count, size_t size);
char	*ft_strdup(const char *s1);
```

N'oublie pas `#include <stddef.h>` (pour `size_t`) et `#include <stdlib.h>` (pour `malloc`, utilisé par `calloc` et `strdup`).
