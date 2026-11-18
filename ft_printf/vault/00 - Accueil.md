---
tags: [ft_printf, 42, accueil]
---

# 🐰 Vault ft_printf

**But** : coder `ft_printf` en comprenant chaque ligne. Claude est ton **coach** (concepts, indices, relecture), pas un générateur de code : en évaluation, c'est toi qui dois expliquer et refaire chaque ligne.

## Démarrage rapide
1. Lis [[01 - Workflow]] (5 min).
2. Ouvre [[03 - Plan et checklist]] : ta feuille de route, tu coches au fur et à mesure.
3. Bloqué ? → [[02 - Quand appeler Claude]].
4. Début de session avec Claude → colle « Démarrage de session » de [[06 - Prompts types]].
5. Fin de session → 3 lignes dans [[07 - Journal]].

## Carte du vault
- [[01 - Workflow]] : la boucle de travail (1 brique = 1 cycle)
- [[02 - Quand appeler Claude]] : à quel moment, avec quel niveau d'aide
- [[03 - Plan et checklist]] : phases, briques, cases à cocher
- [[04 - Concepts clés]] : va_list, write, bases, pièges
- [[05 - Tests]] : main comparatif + matrice de cas
- [[06 - Prompts types]] : messages prêts à copier
- [[07 - Journal]] : état d'avancement et blocages
- [[08 - Soutenance]] : préparer la peer-eval
- [[09 - Man pages décryptées]] : `man 3 stdarg` (les `va_*`), `man 2 write`, `man 3 printf`

## Le sujet en 30 secondes
> [!warning] Aide-mémoire
> Vérifie toujours sur le PDF officiel de **ta** version du sujet.

- Prototype : `int ft_printf(const char *, ...);`
- Conversions : `%c` `%s` `%p` `%d` `%i` `%u` `%x` `%X` `%%`
- Retour : nombre de caractères écrits (comme `printf`)
- Pas de gestion de buffer comme le vrai `printf` : on écrit avec `write` (celui de `<unistd.h>`)
- Rendu : `libftprintf.a` à la racine ; Makefile avec `$(NAME)`, `all`, `clean`, `fclean`, `re` ; pas de relink ; `cc -Wall -Wextra -Werror` ; lib créée avec `ar`
- Fonctions autorisées : `malloc`, `free`, `write`, `va_start`, `va_arg`, `va_copy`, `va_end`
- Norminette obligatoire
- Libft : à vérifier dans ton sujet (autorisée dans plusieurs versions)
- Bonus : évalués seulement si la partie obligatoire est parfaite (flags `-0.` + largeur, puis `#`, `+`, espace)
