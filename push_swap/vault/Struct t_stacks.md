---
tags: [push_swap, 42, struct, code]
---

# 🧱 La struct `t_stacks` : comment l'utiliser

Retour : [[Plan et checklist]] · Algos : [[Cours algos]]

## Pourquoi une struct
Un `int *tab` seul ne connaît pas sa taille, et `pa`/`pb` modifient **deux** piles et **deux** tailles à la fois. Pas de variables globales autorisées : tout doit voyager ensemble dans une struct passée par pointeur.

```c
typedef struct s_stacks
{
	int	*a;        // tableau de la pile a (malloc, n cases)
	int	*b;        // tableau de la pile b (malloc, n cases)
	int	size_a;
	int	size_b;
	int	n;         // capacité totale (utile pour bits du radix, nb de chunks)
	int	count[11]; // compteur par opération pour --bench (évite un global)
}	t_stacks;
```

- `a` et `b` sont des **pointeurs** (`int *`), pas des `int`.
- `a` et `b` ont chacun `n` cases : `size_a + size_b = n` toujours, donc **jamais de `realloc`**.
- Décision à prendre avec le binôme : le haut de la pile est en `[0]` ou en `[size-1]`. Tout le monde s'y tient.

## Règle d'or : UNE seule variable, dans `main`
On ne crée pas de nouveau `t_stacks` dans chaque fonction (chaque fonction travaillerait sur sa propre copie et rien ne serait modifié). On crée la variable une fois dans `main`, et on passe son **adresse**.

| Où | Écriture |
|----|----------|
| Dans `main` (la variable) | `t_stacks s;` puis `s.a`, `s.size_a`, et on passe `&s` |
| Dans les autres fonctions (le pointeur) | `t_stacks *s` puis `s->a`, `s->size_a` |

```c
int	main(int argc, char **argv)
{
	t_stacks	s;                       // seule variable, sur la pile (pas de malloc pour la struct)

	if (!init_stacks(&s, argc, argv))    // malloc de s.a et s.b, remplit tout
		return (write(2, "Error\n", 6), 1);
	sort(&s);                            // les algos reçoivent le pointeur
	free_stacks(&s);                     // libère s.a et s.b
	return (0);
}

void	sa(t_stacks *s)                  // modifie l'original via le pointeur
{
	int	tmp;

	if (s->size_a < 2)
		return ;
	tmp = s->a[0];
	s->a[0] = s->a[1];
	s->a[1] = tmp;
	write(1, "sa\n", 3);
}
```

## Adapter le code existant
- **`parsetab`** → `init_stacks(t_stacks *s, int argc, char **argv)` :
  - alloue `s->a` et `s->b` avec `n` cases ;
  - remplit `a`, puis `size_a = n`, `size_b = 0` ;
  - retourne 0 en cas d'erreur **après avoir libéré** ce qui était déjà alloué.
- **`ft_atoi`** : doit pouvoir signaler une erreur (overflow `int`, caractère invalide). Il faut distinguer « 0 » de « erreur » : par exemple retourner un `long`, ou passer un pointeur de statut.
- **`sa` `sb` `ss`** : à réécrire avec la signature `void sa(t_stacks *s)`.
- **`push_swap.h`** : mettre à jour les prototypes **en même temps** que les `.c`, et déclarer `t_stacks` avant les prototypes qui l'utilisent.

## Pièges
- Oublier `free_stacks` sur un chemin d'erreur → fuite mémoire (zéro tolérance au sujet).
- Passer `t_stacks s` par valeur au lieu de `t_stacks *s` : la fonction modifie une copie, rien ne change.
- Mélanger les deux orientations du tableau (haut en `[0]` vs `[size-1]`) entre `pa`/`pb` et `ra`/`rra`.
