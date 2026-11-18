---
tags: [ft_printf, plan, checklist]
---

# Plan et checklist

Retour : [[00 - Accueil]] · Chaque brique suit [[01 - Workflow]] · Aide : [[02 - Quand appeler Claude]]

## Phase 0 : Préparation (≈ 30-45 min)
- [x] Lire le PDF du sujet en entier, une fois, sans coder
- [ ] Reformuler en 5 lignes ce que demande le projet → [[07 - Journal]]
- [x] Lire `man 3 stdarg` et `man 2 write`
- [ ] Créer le dépôt, les fichiers vides, `ft_printf.h` avec header guard
- [ ] Écrire un Makefile squelette (règles `$(NAME) all clean fclean re`, `ar rcs`)
- [ ] Créer `tests/main.c` à partir de [[05 - Tests]]
- 🤖 Facultatif : faire valider ta reformulation

## Phase 1 : Les briques
Ordre conseillé : du plus simple au plus piégeux.

| # | Brique | Sert pour | Piège principal | Fait |
|---|--------|-----------|-----------------|------|
| 1 | `ft_putchar` | `%c`, `%%` | Retourne 1 (ou -1 si `write` échoue) | [x] |
| 2 | `ft_putstr` | `%s` | `NULL` → `(null)` ; chaîne vide → 0 | [x] |
| 3 | `ft_putnbr` (int) | `%d` `%i` | `INT_MIN` ; 0 ; signe `-` compté dans le retour | [x] |
| 4 | putnbr non signé | `%u` | `-1` passé en `%u` → 4294967295 | [ ] |
| 5 | conversion en base | `%x` `%X` | 0 → `0` ; minuscules vs majuscules | [ ] |
| 6 | `ft_putptr` | `%p` | Préfixe `0x` ; cas `NULL` ; `unsigned long` | [ ] |

Pour chaque brique : Spec → Prédire → Coder → Tester → Nettoyer → Commit.
🤖 Appel : seulement selon la règle des 20 min, ou en relecture une fois la brique validée.

## Phase 2 : Le dispatcher `ft_printf`
- [ ] Parcourir le format caractère par caractère
- [ ] Texte normal → l'écrire ; `%` → lire le caractère suivant → appeler la bonne brique
- [ ] `va_start` / `va_end` au bon endroit
- [ ] Cumuler les valeurs de retour ; propager -1 en cas d'erreur
- [ ] Respecter la norme (25 lignes, 4 paramètres max) : découper en petites fonctions
- 🤖 Appel recommandé : **challenge de design** avant d'écrire (modèle « Design » dans [[06 - Prompts types]]), notamment sur comment passer la `va_list` aux sous-fonctions ([[04 - Concepts clés]])

## Phase 3 : Tests
- [ ] Matrice de [[05 - Tests]] passée : sorties **et** valeurs de retour identiques à `printf`
- [ ] `valgrind` / `-fsanitize=address` : 0 erreur, 0 fuite
- 🤖 Appel : si une différence te résiste (règle des 20 min)

## Phase 4 : Rendu
- [ ] `norminette` sur tous les fichiers : OK
- [ ] `make` deux fois de suite : la 2e fois ne recompile rien (pas de relink)
- [ ] `make re`, `make clean`, `make fclean` fonctionnent
- [ ] Compilation avec `-Wall -Wextra -Werror` sans warning
- [ ] `libftprintf.a` à la racine
- [ ] Dépôt propre (pas de `a.out`, pas de fichiers de test inutiles)
- 🤖 Appel : relecture finale (niveau 3)

## Phase 5 : Préparer l'évaluation
- [ ] Répondre à voix haute aux questions de [[08 - Soutenance]]
- [ ] Pouvoir réécrire de tête une brique simple et expliquer le dispatcher
- 🤖 Appel : quiz oral

## Phase 6 : Bonus (seulement si le mandatory est parfait)
- [ ] Flags `-`, `0`, `.` et largeur de champ
- [ ] Puis `#`, `+`, espace
- 🤖 Appel : dès le début, pour décider comment **étendre** ton dispatcher sans tout réécrire
