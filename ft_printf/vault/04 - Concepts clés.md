---
tags: [ft_printf, concepts]
---

# Concepts clés

Retour : [[00 - Accueil]] · Appelle Claude quand un de ces points reste flou (niveau 1 dans [[02 - Quand appeler Claude]]).

## 1. Fonctions variadiques (`stdarg.h`)
- `va_list` : le « curseur » sur les arguments variables.
- `va_start(ap, dernier_param_fixe)` : positionne le curseur.
- `va_arg(ap, type)` : lit **un** argument du type demandé, puis avance. Un appel par conversion.
- `va_end(ap)` : à appeler avant de quitter la fonction qui a fait `va_start`.
- Si le `type` demandé ne correspond pas à ce qui a été passé, le comportement est indéfini.
- Promotions : un `char` passé à une fonction variadique arrive comme un `int`. Que demander à `va_arg` pour `%c` ?

Exemple **voisin** (pas ton projet) :
```c
#include <stdarg.h>

int	ft_sum(int count, ...)
{
	va_list	args;
	int		total;

	va_start(args, count);
	total = 0;
	while (count--)
		total += va_arg(args, int);
	va_end(args);
	return (total);
}
```

> [!warning] Passer la `va_list` à une sous-fonction
> Sur x86-64 Linux, passer `va_list` directement semble marcher. Mais le standard dit qu'après qu'une fonction appelée a fait `va_arg` dessus, la valeur dans l'appelant est **indéterminée**. La façon portable : passer un **pointeur** `va_list *`. Ça compte pour ton design du dispatcher (et pour la norme : 4 paramètres max).

## 2. `write`
- `ssize_t write(int fd, const void *buf, size_t count)` : retourne le nombre d'octets écrits, ou **-1** en cas d'erreur.
- Pas de buffer : un `write` par appel. Garde ça simple, la performance n'est pas le sujet.
- Réfléchis : que dois-tu retourner depuis ta brique si `write` échoue ?

## 3. Entiers : signé, non signé, limites
- `INT_MIN` = -2147483648. Son opposé **ne tient pas** dans un `int`. Quel type plus grand peux-tu utiliser pour le convertir avant de l'inverser ?
- `%u`, `%x`, `%X` lisent un `unsigned int` : `-1` devient 4294967295.
- `%p` lit un pointeur : à convertir en `unsigned long` pour l'afficher en hexadécimal.

## 4. Convertir un nombre en base : l'idée
Pour écrire 123 en base 10, `n % 10` donne le **dernier** chiffre (3), `n / 10` donne le reste (12). Or tu dois écrire les chiffres dans l'ordre inverse. Deux approches :
1. **Récursion** : écrire d'abord la partie `n / base`, puis le chiffre `n % base`.
2. **Tampon sur la pile** : remplir un petit tableau depuis la fin, puis écrire.

Questions pour toi :
- Quelle approche te semble plus simple à compter (valeur de retour) ? Pourquoi ?
- Combien de caractères au maximum pour un `unsigned long` en base 10 ? En base 16 ?
- Que se passe-t-il pour `n = 0` ?
- Comment choisir entre `0123456789abcdef` et `0123456789ABCDEF` ?

## 5. Pièges du comportement attendu
- `%s` avec `NULL` : glibc (Linux) affiche `(null)`.
- `%p` avec `NULL` : glibc affiche `(nil)` ; macOS affiche `0x0`. Teste sur la machine où tu seras évalué.
- `%c` avec `0` : écrit bien un octet NUL et compte 1.
- `%%` : écrit un `%`, compte 1.
- Format qui finit par un `%` seul : comportement indéfini, mais ton programme ne doit pas planter.
- Conversion inconnue (`%k`) : indéfini aussi. Décide d'un comportement et note-le dans [[07 - Journal]].

## 6. Valeur de retour
`ft_printf` retourne le total de caractères écrits. Chaque brique retourne le sien ; le dispatcher additionne. Si une brique retourne -1, que fais-tu ?

## Pour aller plus loin
`man 3 stdarg` · `man 2 write` · `man 3 printf`
