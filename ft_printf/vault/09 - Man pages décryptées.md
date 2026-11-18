---
tags: [ft_printf, man, stdarg, write, printf]
---

# Man pages décryptées

Retour : [[00 - Accueil]] · Concepts : [[04 - Concepts clés]]

Les trois pages à connaître : `man 3 stdarg`, `man 2 write`, `man 3 printf`.

## 0. Lire un man sans se perdre

**Les numéros de section** : `1` = commandes shell, `2` = appels système, `3` = fonctions de bibliothèque.
- `write` est un appel système : section **2**. Sans le numéro, `man write` ouvre la *commande* shell `write` (envoyer un message à un utilisateur), pas la fonction C.
- `stdarg` et `printf` sont en section **3**.

Si les pages manquent sur ton Ubuntu : `sudo apt install manpages-dev`.

**Dans une page** : `/mot` cherche, `n` va au résultat suivant, `q` quitte.
Les parties utiles, dans l'ordre :
1. **SYNOPSIS** : le `#include` à mettre et le prototype exact.
2. **DESCRIPTION** : ce que fait la fonction, argument par argument.
3. **RETURN VALUE** : ce qu'elle retourne, y compris en cas d'erreur.
4. **NOTES / BUGS** : les pièges.

## 1. `man 3 stdarg` : les `va_*`

Il faut `#include <stdarg.h>`. La page définit un type et quatre macros.

### Le type `va_list`
Un objet qui représente « où j'en suis » dans la liste des arguments variables. Tu le déclares toi-même dans ta fonction : `va_list args;`. Il ne contient rien d'utile tant que `va_start` n'a pas été appelé.

### Les 4 macros

| Macro | Syntaxe | Rôle | Piège |
|-------|---------|------|-------|
| `va_start` | `va_start(ap, last)` | Initialise `ap`, doit être appelé **en premier** | `last` = nom du **dernier paramètre fixe** de ta fonction (pour `ft_printf(const char *format, ...)`, c'est `format`) |
| `va_arg` | `va_arg(ap, type)` | Donne l'argument suivant, **converti en `type`**, puis avance d'un cran | Un `type` qui ne correspond pas à ce qui a été passé = comportement indéfini |
| `va_end` | `va_end(ap)` | Termine l'utilisation de `ap` | Chaque `va_start` doit avoir son `va_end` **dans la même fonction** |
| `va_copy` | `va_copy(dest, src)` | Fait une copie du curseur dans son état actuel | Chaque `va_copy` demande aussi son `va_end`. Tu n'en as normalement pas besoin pour le mandatory |

### Le cycle de vie
```
va_list args;                 ← tu déclares
va_start(args, last);         ← initialise (en 1er)
x = va_arg(args, int);        ← lit le 1er argument variable
y = va_arg(args, char *);     ← lit le 2e
va_end(args);                 ← ferme
```
Chaque `va_arg` **consomme** un argument. Tu ne peux pas « relire » le même : un appel par conversion.

### Ce que la fonction ne sait pas
Une fonction variadique ne sait **ni combien d'arguments, ni de quel type** on lui a passé. C'est toi qui dois le savoir. Dans `ft_printf`, c'est la **chaîne de format** qui te le dit : `%d` annonce un `int`, `%s` annonce un `char *`. Si le format dit `%d` mais que l'appelant a passé un pointeur, personne ne te prévient : tu lis n'importe quoi.

### Quel `type` donner à `va_arg` ?

| Conversion | `type` pour `va_arg` | Pourquoi |
|------------|----------------------|----------|
| `%c` | `int` | Un `char` passé à `...` est **promu en `int`** (promotion d'arguments par défaut) |
| `%s` | `char *` | Pointeur sur la chaîne |
| `%p` | `void *` | Pointeur générique |
| `%d`, `%i` | `int` | |
| `%u`, `%x`, `%X` | `unsigned int` | |

Les promotions par défaut : `char` et `short` deviennent `int`, `float` devient `double`. Demander `va_arg(args, char)` est donc une erreur : le compilateur t'avertira.

### Passer la `va_list` à une autre fonction
Le man le dit en clair : si tu passes `ap` à une fonction qui fait `va_arg`, la valeur de `ap` est **indéfinie** au retour. Cas d'usage typique : ton dispatcher appelle une fonction qui lit l'argument. Façon sûre : passer un **pointeur** sur la `va_list`.

Exemple **voisin** (pas ton projet) :
```c
#include <stdarg.h>

static int	ft_add_two(va_list *args)
{
	int	a;
	int	b;

	a = va_arg(*args, int);
	b = va_arg(*args, int);
	return (a + b);
}

int	ft_sum_pairs(int pairs, ...)
{
	va_list	args;
	int		total;

	va_start(args, pairs);
	total = 0;
	while (pairs--)
		total += ft_add_two(&args);
	va_end(args);
	return (total);
}
```
Ici `ft_add_two` reçoit `&args` : les deux `va_arg` avancent bien **le même curseur**, et `ft_sum_pairs` peut continuer à l'utiliser ensuite.

### Trois expériences à faire (10 min)
1. Copie `ft_sum` de [[04 - Concepts clés]], appelle-la avec `ft_sum(3, 1, 2)` (il manque un argument) : observe le résultat. C'est ça, un comportement indéfini.
2. Remplace `int` par `char` dans le `va_arg` et compile avec `-Wall -Wextra` : lis l'avertissement.
3. Oublie `va_end` : compile avec `-Wall -Wextra -Werror`. Vois ce qui se passe, puis cherche dans le man pourquoi il le faut quand même.

## 2. `man 2 write`

Il faut `#include <unistd.h>`.

```c
ssize_t write(int fd, const void *buf, size_t count);
```

> [!info] `ssize_t write(...)` n'est **pas** une autre fonction
> C'est **la** fonction `write` de `<unistd.h>`, écrite avec ses types. `ssize_t` est le **type de retour** (un entier signé, pour pouvoir valoir `-1`). `size_t` est le type du troisième paramètre (un entier non signé). Dans ta tête, tu peux lire : `write(fd, adresse, taille)`.

### Les trois arguments
Ton `write(n, c, size)` est la bonne idée. Voici le détail :

| Argument | Type | Signification | Pour ft_printf |
|----------|------|---------------|----------------|
| `fd` | `int` | Descripteur de fichier : `0` entrée, `1` sortie standard, `2` sortie d'erreur | `1` |
| `buf` | `const void *` | **L'adresse** des octets à écrire | Pour un seul caractère `c` : `&c`, pas `c` |
| `count` | `size_t` | Nombre d'octets à écrire | `1` pour un caractère ; la longueur pour une chaîne |

Le point qui piège le plus : `buf` est une **adresse**. Un `char c` n'est pas une adresse, donc il faut `&c`. Une chaîne `char *s` en est déjà une, donc on passe `s`.

Exemple : `write(1, &c, 1)` écrit l'octet contenu dans `c` sur la sortie standard.

### La valeur de retour
- Succès : le **nombre d'octets réellement écrits**.
- Erreur : **`-1`**.
- Le man précise qu'un `write` peut écrire **moins** que `count`. Pour ce projet, tu peux considérer qu'un retour différent de `count` est un échec, mais c'est bon à savoir.

C'est exactement ce que doivent retourner tes briques : le nombre de caractères écrits, ou `-1` ([[04 - Concepts clés]], section 2).

## 3. `man 3 printf`

La page décrit toute la famille (`printf`, `fprintf`, `sprintf`…). Pour toi, seules deux parties comptent.

### Les conversions de ton sujet

| Conversion | Argument lu | Ce que ça affiche |
|------------|-------------|-------------------|
| `%c` | `int`, converti en `unsigned char` | Un caractère |
| `%s` | `char *` | La chaîne jusqu'au `'\0'` |
| `%p` | `void *` | L'adresse en hexadécimal, avec `0x` devant |
| `%d`, `%i` | `int` | Décimal signé |
| `%u` | `unsigned int` | Décimal non signé |
| `%x`, `%X` | `unsigned int` | Hexadécimal : minuscules `abcdef` pour `x`, majuscules pour `X` |
| `%%` | aucun | Un `%` |

Notes :
- `%d` et `%i` sont identiques **en sortie**. Ils ne diffèrent que dans `scanf`.
- Le man décrit `%p` comme équivalent à `%#lx` (hexadécimal avec préfixe).

### RETURN VALUE
Le nombre de caractères affichés. Une valeur **négative** en cas d'erreur d'écriture. C'est le contrat de ta fonction.

### Ce que le man ne te dit pas (comportement de glibc)
- `%s` avec `NULL` : affiche `(null)`.
- `%p` avec `NULL` : affiche `(nil)`, alors que `%#lx` donnerait `0`.
- Ce sont des comportements de la bibliothèque, pas des garanties du standard. Les tester sur ta machine d'évaluation reste la bonne pratique ([[05 - Tests]]).

## Pour t'entraîner à lire un man
Avant de me demander, essaie de répondre avec la page ouverte :
- Quel `#include` faut-il pour chacune des trois pages ?
- Que devient `ap` après `va_end` ?
- Que retourne `write` si le disque est plein ?

Si une réponse reste floue après 10 minutes, c'est un bon moment pour m'appeler (niveau 1 de [[02 - Quand appeler Claude]]).
