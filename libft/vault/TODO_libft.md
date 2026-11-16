# Libft : ce qu'il reste à faire

Coche en remplaçant `[ ]` par `[x]`.

## 1. Global (bloque la compilation)

- [ ] `libft.h` : ajouter le header 42 en haut
- [ ] `libft.h` : ajouter l'include guard (`#ifndef` / `# define` / `#endif` en bas)
- [X] `libft.h` : `ft_memcmp` renvoie `int`, pas `int *`
- [X] Ajouter `#include "libft.h"` en haut des 23 `.c` :
  - [X] ft_atoi
  - [X] ft_bzero
  - [X] ft_calloc
  - [X] ft_isalnum
  - [X] ft_isalpha
  - [X] ft_isascii
  - [X] ft_isdigit
  - [X] ft_isprint
  - [X] ft_memchr
  - [X] ft_memcmp
  - [X] ft_memcpy
  - [X] ft_memmove
  - [X] ft_memset
  - [X] ft_strchr
  - [X] ft_strdup
  - [X] ft_strlcat
  - [X] ft_strlcpy
  - [X] ft_strlen
  - [X] ft_strncmp
  - [X] ft_strnstr
  - [X] ft_strrchr
  - [X] ft_tolower
  - [X] ft_toupper

## 2. Types des compteurs (warnings de signe avec -Werror)

Les compteurs comparés à une taille doivent être des `size_t`.

- [ ] ft_bzero : `i`
- [ ] ft_memchr : `i`
- [ ] ft_memcmp : `i`
- [ ] ft_memcpy : `i`
- [ ] ft_memmove : `i` (attention, la boucle à l'envers ne peut plus utiliser `i >= 0`)
- [ ] ft_memset : `i`
- [ ] ft_strlen : `i`
- [ ] ft_strlcat : `dest_len`, `i`, `src_len`
- [ ] ft_strlcpy : `i`, `srclen`
- [ ] ft_strncmp : `i`
- [ ] ft_strnstr : `i`, `j`

## 3. Bugs de logique

- [ ] **ft_atoi** : le `i++` après le bloc du signe est hors du `if`, il saute un caractère même sans signe
- [ ] **ft_atoi** : ignorer tous les espaces blancs (`\t \n \v \f \r` + espace), pas seulement `' '`
- [ ] **ft_memchr** : pointeur interne en `unsigned char`, et `c` converti en `unsigned char` avant la comparaison
- [ ] **ft_memcmp** : le type de retour est `int` (voir section 1)
- [ ] **ft_strlcpy** : `size == 0` ne doit rien écrire (`size - 1` déborde en non signé)
- [ ] **ft_strlcpy** : `dst[size] = '\0'` écrit hors du buffer. Le `'\0'` va à l'indice où la copie s'est arrêtée
- [ ] **ft_strlcpy** : supprimer la boucle `while (dst[i])`, elle lit de la mémoire non initialisée
- [ ] **ft_strrchr** : l'indice 0 n'est jamais testé (`"abc"`, chercher `'a'` renvoie NULL). Vérifier aussi `c == '\0'`
- [ ] **ft_strnstr** : ajouter la borne `i + j < len` dans la boucle interne
- [ ] **ft_calloc** : protéger contre le dépassement de `count * size`
- [ ] **ft_memcpy** : gérer `dst` et `src` tous deux NULL

## 4. Vérifications finales

- [ ] Plus de `main` actif dans aucun `.c`
- [ ] Compile : `cc -Wall -Wextra -Werror -c ft_*.c` sans warning
- [ ] `norminette` sans erreur (attention à ft_memmove, limite des 25 lignes)
- [ ] Créer le `Makefile` (`NAME`, `all`, `clean`, `fclean`, `re`, `-Wall -Wextra -Werror`, `ar rcs libft.a`)
- [ ] Tester chaque fonction contre la version libc (cas limites : chaîne vide, `n = 0`, `c = 0`, `c > 127`)
