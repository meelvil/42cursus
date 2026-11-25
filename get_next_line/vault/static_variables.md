# Les variables `static` en C

> Le sujet te le dit lui-même : *« A good start would be to know what a static variable is. »*
> Ce document explique le concept **en général**, avec des exemples sans rapport avec GNL. À toi de faire le pont.

---

## 1. Le problème de départ : les variables locales oublient tout

```c
void	compte(void)
{
	int	n;

	n = 0;
	n++;
	printf("%d\n", n);
}
```

Si tu appelles `compte()` 3 fois, tu affiches `1 1 1`.

Pourquoi ? Une variable locale vit sur la **stack**, dans le « cadre » (stack frame) de la fonction.
Quand la fonction se termine, le cadre est détruit : `n` n'existe plus. À l'appel suivant, un nouveau `n` est créé.

C'est exactement ce qui pose problème pour GNL : entre deux appels, **comment se souvenir de ce qu'on a déjà lu ?**

---

## 2. La solution : `static`

```c
void	compte(void)
{
	static int	n = 0;

	n++;
	printf("%d\n", n);
}
```

Trois appels → `1 2 3`.

Une variable locale `static` :

| Propriété | Variable locale normale | Variable locale `static` |
|---|---|---|
| **Visibilité (scope)** | dans la fonction | dans la fonction (**pareil**) |
| **Durée de vie** | jusqu'à la fin de la fonction | **jusqu'à la fin du programme** |
| **Emplacement mémoire** | stack | segment de données (`.data` / `.bss`), pas la stack |
| **Initialisation** | à chaque appel | **une seule fois**, avant `main` |

Retiens la phrase clé : **la visibilité reste locale, mais la durée de vie devient globale.**
Depuis l'extérieur, tu ne peux pas accéder à `n` par son nom. Mais elle continue d'exister.

---

## 3. L'initialisation : le piège classique

```c
static int	n = 0;
```

Cette ligne **n'est pas exécutée à chaque appel**. L'initialisation est faite une seule fois, à la compilation / au chargement du programme.
Ce n'est pas une instruction, c'est une « valeur de départ ».

Deux conséquences :

1. L'initialiseur doit être une **constante** : `static int n = 0;` ✅ — `static int n = foo();` ❌ (erreur de compilation).
2. Si tu ne mets pas de valeur, une variable `static` est **automatiquement mise à zéro** (`0`, `0.0`, `NULL`).
   Une variable locale normale non initialisée contient, elle, **n'importe quoi**.

```c
static char	*reste;   // vaut NULL au premier appel, garanti par la norme C
char		*autre;   // valeur indéterminée !
```

> ⚠️ Autre piège : si tu écris `static int n; n = 0;` en deux lignes, la seconde ligne **est** une instruction et s'exécute à chaque appel. Tu perds tout l'intérêt.

---

## 4. `static` avec des pointeurs et de la mémoire dynamique

Un pointeur `static` retient **une adresse** entre deux appels. Mais ce qu'il pointe peut très bien être sur le heap.

```c
char	*dernier_nom(char *nouveau)
{
	static char	*memoire;   // NULL au départ

	if (nouveau)
		memoire = nouveau;
	return (memoire);
}
```

Ce qu'il faut bien comprendre :

- La **variable pointeur** (8 octets) est static : elle survit.
- Le **bloc alloué avec `malloc`** survit aussi, mais **uniquement parce que personne ne l'a `free`**. Il n'est pas « static », il est sur le heap, et c'est ton pointeur static qui en garde l'adresse.
- Si tu écrases le pointeur static sans avoir `free` l'ancien bloc → **fuite mémoire**, car l'adresse est perdue.
- Si tu `free` le bloc mais laisses le pointeur tel quel → **dangling pointer** (pointeur vers de la mémoire libérée). Pense à le remettre à `NULL` après un `free`.

Cycle de vie typique d'un pointeur static qui gère de la mémoire :

```
NULL  ──malloc──▶  bloc A  ──(on le remplace)──▶  bloc B  ──free──▶  NULL
                      ▲                              ▲
              penser à free A avant de      ne jamais perdre l'adresse
              perdre son adresse            d'un bloc non libéré
```

---

## 5. Un tableau `static` : plusieurs « mémoires » en une

On peut aussi avoir un tableau static, par exemple pour retenir une valeur **par clé** :

```c
int	compteur_par_id(int id)
{
	static int	compteurs[1024];   // tout est à 0 au départ

	compteurs[id]++;
	return (compteurs[id]);
}
```

Chaque `id` a sa propre mémoire persistante. Garde cette idée en tête pour la partie bonus du projet (plusieurs fd en même temps).
(Attention aux bornes : un `id` négatif ou trop grand = accès hors tableau.)

---

## 6. `static` à l'extérieur d'une fonction (le *autre* sens)

Hors d'une fonction, `static` n'a **pas** le même rôle :

```c
static int	helper(int x)   // visible uniquement dans CE fichier .c
{
	return (x * 2);
}
```

Ici, `static` = **liaison interne** : la fonction (ou la variable globale) n'est pas visible depuis les autres `.c`. C'est une façon de « cacher » des détails. Ne confonds pas les deux usages.

---

## 7. Ce que `static` n'est PAS

- ❌ Ce n'est **pas** une constante (`const`). Tu peux la modifier.
- ❌ Ce n'est **pas** une variable globale : personne d'autre ne peut la nommer.
- ❌ Ce n'est **pas thread-safe** : tous les appels partagent la même variable. (Pas un sujet pour GNL, mais bon à savoir.)
- ❌ Elle ne se réinitialise pas toute seule. Si ta fonction doit « repartir de zéro » (par ex. fin de fichier), c'est **à toi** de remettre la variable à son état initial.

---

## 8. Expériences à faire toi-même (10 minutes, ça vaut tous les cours)

Crée un fichier de test à part (pas dans ton projet) et réponds **avant** de lancer :

1. Reprends `compte()` avec et sans `static`. Vérifie `1 2 3` contre `1 1 1`.
2. Affiche l'adresse `&n` d'une variable normale et d'une static à chaque appel (`%p`). Que remarques-tu ?
3. Déclare `static int x;` sans valeur et affiche-la. Puis fais la même chose avec `int y;` normal (compile avec `-Wall -Wextra` et regarde ce que le compilateur dit).
4. Écris une fonction qui renvoie `"a"`, puis `"b"`, puis `"c"`, puis `"a"`… à chaque appel, en utilisant une static.
5. Une fonction qui `malloc` une chaîne, la stocke dans un pointeur static, et la remplace à chaque appel. Lance `valgrind --leak-check=full`. Où est la fuite ? Comment la corriger ?
6. Que se passe-t-il si tu `free` le pointeur static mais ne le remets pas à `NULL`, puis rappelles la fonction ?

---

## 9. Mini-quiz d'auto-évaluation

1. Où vit une variable `static` : stack ou heap ?
2. Combien de fois `static int n = 5;` est-il « exécuté » ?
3. Une fonction `f` a `static int n`. Une autre fonction `g` peut-elle lire `n` ? Pourquoi ?
4. Si je ne `free` jamais mon pointeur static à la fin du programme, est-ce une fuite ? (Réfléchis à la différence entre « mémoire encore accessible » et « mémoire perdue ».)
5. Pourquoi une variable locale normale ne pourrait-elle pas résoudre GNL ?

---

## 10. Ressources pour aller plus loin

- `man 3 malloc`, `man 2 read`
- Cherche : *« C storage duration »*, *« C linkage internal external »*
- Outils : `valgrind`, `-fsanitize=address`
- Parle avec tes pairs : expliquer `static` à voix haute à quelqu'un est le meilleur test de compréhension.
