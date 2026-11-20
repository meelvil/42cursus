# ft_printf : guide de route

## Le problème en une phrase
`ft_printf("a%db", 5)` doit parcourir la chaîne, écrire les caractères normaux,
et à chaque `%` remplacer la lettre suivante par l'argument correspondant.
Il renvoie le **nombre total de caractères écrits**.

## Les 3 rôles (ne pas les mélanger)

| Rôle | Fichier | Question à laquelle il répond |
|---|---|---|
| La boucle | `ft_printf.c` | "Où en suis-je dans la chaîne ?" |
| Le dispatcher | `ft_format.c` | "Quelle fonction pour cette lettre ?" |
| Les écrivains | `ft_putchar.c`, `ft_putstr.c`, ... | "Comment j'écris ce type ?" |

Chaque rôle ne fait que son travail : la boucle ne connaît pas les lettres,
le dispatcher ne parcourt pas la chaîne, les écrivains ne connaissent pas `va_list`.

## Le flux

```
ft_printf(s, ...)
  va_start
  tant que s[i] :
      si s[i] != '%'  -> ft_putchar(s[i])
      sinon           -> i++, ft_format(&args, s[i])
      total += retour
  va_end
  return total
```

## Règles à ne pas oublier
- Tout renvoie un `int` : le nombre de caractères écrits. Sinon le total est perdu.
- `va_list` se passe **par pointeur** (`va_list *`) pour que l'avancée des arguments
  soit vue par la boucle.
- Dans `ft_format`, un `va_arg` par lettre, avec le bon type :

| Lettre | Type pour `va_arg` | Fonction |
|---|---|---|
| `c` | `int` | `ft_putchar` |
| `s` | `char *` | `ft_putstr` |
| `d`, `i` | `int` | `ft_putnbr` |
| `u` | `unsigned int` | `ft_putunsignednbr` |
| `x`, `X` | `unsigned int` | `ft_converthex` (à faire) |
| `p` | `void *` | `ft_putptr` (à faire) |
| `%` | aucun | `ft_putchar('%')` |

- `%` à la toute fin de la chaîne : vérifier que `s[i+1]` n'est pas `\0`.
- `%s` avec `NULL` : le vrai printf affiche `(null)`.
- Les erreurs de type ou de nombre d'arguments ne sont pas à gérer
  (comportement indéfini, seul le compilateur prévient).

## Comprendre la liste d'arguments (`va_list`)

### L'idée
Les `...` de `ft_printf` sont un nombre inconnu d'arguments. Le C ne te dit pas combien
il y en a ni de quel type : c'est **la chaîne de format qui le dit**
(un `%d` = un argument de plus, de type `int`).

### Le curseur
`va_list` se comporte comme un **curseur posé sur la liste** :
- `va_start(args, s)` pose le curseur juste après `s` (le dernier argument nommé).
- `va_arg(args, type)` **lit l'argument sous le curseur ET avance le curseur** d'un cran.
- `va_end(args)` range le tout à la fin.

Exemple : `ft_printf("%d %s", 42, "hi")`

```
liste :   42      "hi"
curseur:  ^                    après va_start
          va_arg(args, int)    -> renvoie 42, le curseur avance
                  ^
          va_arg(args, char *) -> renvoie "hi", le curseur avance
```

Conséquence : **un seul `va_arg` par `%`**, jamais deux, jamais zéro (sauf `%%`).
Si tu en lis un de trop ou de moins, tous les arguments suivants sont décalés.

### Pourquoi `va_list *` dans `ft_format`
En C, un argument de fonction est **copié**. Si `ft_format` reçoit `va_list args`,
elle avance **sa copie** du curseur : au retour dans `ft_printf`, le curseur n'a pas bougé
et le `%` suivant relit le même argument.
Avec `va_list *args`, `ft_format` avance **le vrai curseur**.

Dans `ft_format`, `args` est donc un pointeur : pour lire, on passe **le curseur lui-même**
à `va_arg`, c'est-à-dire `*args` (pas `args`).

### À quoi ressemble une branche de `ft_format`
```c
if (c == 'c')
    return (ft_putchar(va_arg(*args, int)));
```
Lis-le de l'intérieur vers l'extérieur :
1. `va_arg(*args, int)` lit l'argument et avance le curseur.
2. Sa valeur est donnée à `ft_putchar`.
3. `ft_putchar` écrit et renvoie le nombre de caractères, que `ft_format` renvoie à son tour.

Les autres lettres suivent le même moule, seul le **type** change (voir le tableau plus haut).

### Pourquoi `int` pour `%c` et pas `char`
En C, les petits types (`char`, `short`) sont promus en `int` quand ils passent par `...`.
`va_arg(*args, char)` est donc une erreur : on lit toujours un `int`.
`ft_putchar(char c)` reçoit ensuite cet `int` converti automatiquement.

### Ce que tu ne fais pas
- Pas de `va_start` / `va_end` dans `ft_format` : ils sont déjà gérés dans `ft_printf`.
- Pas de `va_list` copiée par valeur d'une fonction à l'autre.

## Ordre de travail
- [ ] 1. `ft_format` avec `c`, `s`, `d`, `i`, `u`, `%` (les fonctions existent déjà)
- [ ] 2. Prototype de `ft_format` dans `ft_printf.h`
- [ ] 3. Réécrire la boucle de `ft_printf`
- [ ] 4. Tester contre le vrai `printf` (comparer sortie ET valeur de retour)
- [ ] 5. `ft_converthex` -> brancher `x` et `X`
- [ ] 6. `ft_putptr` -> brancher `p`
- [ ] 7. Cas limites : `NULL`, `INT_MIN`, `0`, `%` final

## Pièges déjà rencontrés
- `printf("%s", ft_printf("M"))` : le retour est un `int`, il faut `%d`.
- Deux `main` dans le même dossier : ne compiler qu'un seul à la fois.

## Test de base
```c
int a = ft_printf("%c|%s|%d|%i|%u|%%\n", 'x', "abc", -42, 7, 42u);
int b =    printf("%c|%s|%d|%i|%u|%%\n", 'x', "abc", -42, 7, 42u);
printf("%d %d\n", a, b);   /* doivent être égaux */
```
