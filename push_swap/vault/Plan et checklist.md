---
tags: [push_swap, 42, plan, checklist]
---

# 🐰 Push_swap : plan et checklist

> [!warning] Aide-mémoire
> Vérifie toujours sur le PDF officiel (`push_swap.pdf`, version 1.2). Projet en **binôme** : répartissez-vous le travail et sachez tout expliquer.

## Le sujet en 30 secondes
- 2 stacks `a` et `b`, `b` vide au départ. But : trier `a` en ordre croissant (plus petit en haut) avec le **moins d'opérations** possible.
- Programme `push_swap` : args = entiers (le 1er est le haut de `a`) + flag optionnel `--simple` `--medium` `--complex` `--adaptive` (défaut) + `--bench`.
- Sortie : une opération par ligne (`\n` et rien d'autre) sur **stdout**. Erreur → `Error\n` sur **stderr**. Sans argument → rien.
- Autorisé : `read write malloc free exit`, `ft_printf` maison, libft. **Pas de variables globales.**
- Norme : 25 lignes/fonction, 4 paramètres max, 5 fonctions/fichier.
- Makefile : `$(NAME) all clean fclean re`, `cc -Wall -Wextra -Werror`, pas de relink.

## Les 11 opérations
| Op | Effet |
|----|-------|
| `sa` `sb` `ss` | échange les 2 premiers (rien si < 2 éléments) |
| `pa` `pb` | prend le haut de l'autre stack et le met sur celle-ci (rien si source vide) |
| `ra` `rb` `rr` | rotation vers le haut : le premier devient le dernier |
| `rra` `rrb` `rrr` | rotation vers le bas : le dernier devient le premier |

`ss`, `rr`, `rrr` = les deux opérations simples ensemble (une seule ligne affichée).

> Détail d'utilisation de la struct : [[Struct t_stacks]] · Cours sur les algos : [[Cours algos]]

## Pourquoi `int sa(int *tab)` ne suffit pas (et la solution en tableaux)
Garder des **tableaux d'int est un bon choix** (mémoire contiguë, cache-friendly). Le souci n'est pas le tableau, c'est la **signature** :

1. **Un `int *tab` ne connaît pas sa taille.** Or `sa` doit ne rien faire s'il y a moins de 2 éléments, et `ra`/`rra` doivent savoir où est le dernier. Il faut passer la taille.
2. **`pa`/`pb` touchent deux stacks et deux tailles à la fois** : `a` perd un élément, `b` en gagne un. Avec `int *tab` seul, impossible.
3. **Pas de globales** : tableaux et tailles doivent voyager ensemble.

Solution : une struct qui regroupe tout, passée par pointeur.

```c
typedef struct s_stacks
{
	int	*a;
	int	*b;
	int	size_a;
	int	size_b;
}	t_stacks;

void	sa(t_stacks *s);   // échange a[0] et a[1] si size_a >= 2, puis écrit "sa\n"
void	pb(t_stacks *s);   // retire le haut de a, le met en haut de b
```

- Alloue `a` **et** `b` avec la capacité `n` (nombre d'arguments) : à n'importe quel moment `size_a + size_b = n`, donc aucun realloc.
- Écris l'affichage (`write`) **et** le compteur `--bench` à l'intérieur de chaque op.

**Choix d'orientation du tableau** (à décider avec ton binôme) :

| Haut de la stack | `sa` / `pa` / `pb` | `ra` / `rra` |
|------------------|--------------------|--------------|
| `tab[0]` | décalage de tout le tableau (O(n)) | décalage (O(n)) |
| `tab[size-1]` | **O(1)** | décalage (O(n)) |

Avec le haut à la fin, il faut remplir `a` à l'envers au parsing. Pour 500 nombres le coût de simulation est négligeable : choisis ce qui est le plus lisible. (Piste avancée : buffer circulaire avec un index de tête, rotations en O(1).)

> [!note] Rappel
> La complexité demandée (O(n²), O(n√n), O(n log n)) se compte en **nombre d'opérations push_swap générées**, pas en temps CPU du décalage de tableau.

---

## Phase 0 : Préparation
- [ ] Lire le PDF en entier une fois, sans coder
- [ ] Se mettre d'accord avec le binôme sur la répartition (parsing + ops / algos)
- [ ] Décider : orientation du tableau (haut = `[0]` ou `[size-1]`)
- [ ] Créer le dépôt, `push_swap.h` avec header guard, Makefile squelette (avec libft dans `libft/`)
- [ ] Reformuler le sujet en 5 lignes → [[Journal]] (si tu en crées un)

## Phase 1 : Structure et parsing
- [ ] Définir `t_stacks` (tableaux + tailles)
- [ ] `ft_atoi` robuste : détecte l'overflow `int` (existant à adapter)
- [ ] Parser les flags (`--simple` etc., `--bench`) séparément des nombres
- [ ] Rejeter : non-entier, hors plage `int`, doublon → `Error\n` sur stderr
- [ ] Aucun argument → ne rien afficher
- [ ] Libérer la mémoire sur **tous** les chemins d'erreur

## Phase 2 : Les 11 opérations
- [ ] `sa` `sb` `ss`
- [ ] `pa` `pb`
- [ ] `ra` `rb` `rr`
- [ ] `rra` `rrb` `rrr`
- [ ] Chaque op : ne fait rien si stack trop petite/vide, sinon agit puis affiche son nom
- [ ] Petit `main` de test : appliquer des ops à la main et afficher les stacks, comparer avec l'exemple du PDF (§VI.4)

## Phase 3 : Briques utilitaires
- [ ] `is_sorted(a)`
- [ ] `compute_disorder(a)` = paires inversées / paires totales, **avant tout mouvement**
- [ ] Indexation : remplacer chaque valeur par son rang `0..n-1` (indispensable pour le radix et les négatifs)
- [ ] Compteurs d'opérations par type (pour `--bench`)

## Phase 4 : Les 4 algorithmes
- [ ] **Simple O(n²)** : sélection (push le min vers `b`, puis `pa` à la fin) ou insertion
- [ ] **Medium O(n√n)** : chunks de ≈ √n éléments
- [ ] **Complex O(n log n)** : radix LSD sur les bits des rangs (`pb` si bit = 0, sinon `ra`, puis `pa` de tout)
- [ ] **Adaptive** : disorder < 0.2 → simple ; 0.2 ≤ d < 0.5 → medium ; d ≥ 0.5 → complex
- [ ] Les flags forcent l'algo choisi **quelle que soit l'entrée** (taille 0, 1, 2, 3, déjà triée…)
- [ ] Cas particuliers : 2 et 3 éléments traités à la main (quelques ops max)

## Phase 5 : Optimisation et benchmark
Cibles du sujet (nombres aléatoires) :

| Taille | Minimum | Bon | Excellent |
|--------|---------|-----|-----------|
| 100 | < 2000 | < 1500 | < 700 |
| 500 | < 12000 | < 8000 | < 5500 |

- [ ] Fusionner en `rr` / `rrr` quand c'est possible
- [ ] Choisir `ra` ou `rra` selon le chemin le plus court
- [ ] Mode `--bench` sur **stderr** : disorder (% à 2 décimales), stratégie + complexité, total d'ops, compteur par op
- [ ] Mesurer sur beaucoup de tirages (`shuf -i 0-9999 -n 500`), pas un seul

## Phase 6 : Tests
- [ ] Entrées invalides : `one`, `2147483648`, doublon, flag inconnu, chaîne vide
- [ ] Tailles 1, 2, 3, 5, 100, 500 ; déjà trié ; trié à l'envers
- [ ] Vérification avec le checker (fourni, ou le tien en bonus) : `./push_swap $ARG | ./checker $ARG` → `OK`
- [ ] `valgrind` / `-fsanitize=address` : 0 erreur, 0 fuite
- [ ] Chaque flag testé séparément sur les mêmes entrées

## Phase 7 : README et rendu
- [ ] 1re ligne en italique : *This project has been created as part of the 42 curriculum by login1, login2*
- [ ] Sections **Description**, **Instructions**, **Resources** (avec l'usage de l'IA détaillé)
- [ ] Justification des seuils 0.2 / 0.5, techniques par régime, argument de complexité (temps + espace)
- [ ] Contributions de **chaque** membre du binôme
- [ ] `norminette` OK partout
- [ ] `make` 2 fois : pas de relink ; `re`, `clean`, `fclean` OK
- [ ] Dépôt propre (pas de `a.out` / `a.exe`)

## Phase 8 : Soutenance
- [ ] Expliquer chaque algo et sa complexité à voix haute
- [ ] Savoir réécrire de tête une op simple (`sa`, `pb`) et expliquer `t_stacks`
- [ ] Préparer une petite modification à chaud (changer un seuil, ajouter une op…)

## Phase 9 : Bonus (seulement si le mandatory est parfait, benchmarks inclus)
- [ ] `checker` : lit les ops sur stdin, les exécute, affiche `OK` / `KO` ; `Error` sur stderr (op inconnue, args invalides)
- [ ] Règle `bonus` dans le Makefile, fichiers en `_bonus.{c,h}`
