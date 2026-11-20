---
tags: [ft_printf, journal]
---

# Journal

Retour : [[00 - Accueil]] · Feuille de route : [[03 - Plan et checklist]]

## Modèle d'entrée de fin de session
```
### AAAA-MM-JJ
- Fait : 
- Bloqué sur : 
- Prochaine étape (test à écrire / brique à faire) : 
```

## Ma reformulation du sujet (5 lignes)
-

## Décisions de design
- Fonction générique de conversion en base ? Paramètres : 
- Comment je passe la `va_list` aux sous-fonctions : 
- Comportement choisi pour une conversion inconnue : 

## Entrées

### 2026-11-16
- Fait : création du vault, début du projet.
- Bloqué sur : rien.
- Prochaine étape : Phase 0 de [[03 - Plan et checklist]].

### 2026-11-18
- Fait :
  - Phase 0 : sujet lu, `man 3 stdarg` et `man 2 write` lus ; Makefile squelette créé (`libftprintf.a`, `-MMD`).
  - Briques écrites : `ft_putchar`, `ft_putstr`, `ft_strlen`, `ft_putnbr` (compte les chiffres + signe via `count_digits`, gère `INT_MIN` grâce au `long`), `ft_putunsignednbr` (terminée et testée).
  - `ft_printf` : seulement un squelette (`va_start` + test `ispercent`), pas encore de boucle ni de dispatch.
  - Compris que `printf` doit retourner le nombre d'octets écrits. Continué ma mental card sur le projet.
- État actuel / à corriger :
  - `ft_putunsignednbr` : terminée. Signature `unsigned int` (header à jour), `count_digits` en `unsigned int`, casts et test `n >= 0` retirés, `main` commenté. Testé (compilation `-Wall -Wextra -Werror`) : `-1` → `4294967295` retour 10 ; `0` → retour 1 ; `42` → retour 2. Brique 4 validée.
  - `ft_putunsignednbr` **refaite** : plus de `count_digits`, la récursion cumule directement les retours (`return (f(n / 10) + f(n % 10))`, cas de base `return (ft_putchar(n + '0'))`). Le retour reflète maintenant les octets réellement écrits.
  - **Bug trouvé puis corrigé dans `ft_putnbr`** : `count_digits` était recalculé après `nb = -nb`, donc le `-` n'était pas compté (`ft_putnbr(-42)` retournait 2 au lieu de 3). Maintenant `count_digits(n)` est appelé sur le `n` d'origine → OK.
  - **`ft_putnbr` refaite et validée** : écrit le `-` (retour gardé, `-1` propagé), puis délègue la valeur absolue (`long nb = -nb`, cast en `unsigned int`) à `ft_putunsignednbr` et additionne. Plus de `count_digits` ni de récursion. Piège évité : caster `nb` (positif) et non `n` (resté négatif). Testé : `0`→1, `-1`→2, `42`→2, `-42`→3, `INT_MIN`→11, `INT_MAX`→10. Brique 3 validée.
  - `ft_printf.c` appelle `ispercent` (défini dans `ft_percent.c`) mais le header déclare `ft_percent` → incohérence ; `va_end` manquant.
  - Makefile : `SOURCES` ne contient que `ft_printf.c` (ajouter les briques) ; faute de frappe `fclean: cleam` ; `-include`/`re` à vérifier.
  - `main` de test restés dans `ft_putnbr.c` et `test.c` (à sortir vers `tests/`).
- Bloqué sur :
  - Le détail du retour de `printf` (octets écrits vs à écrire ?) — besoin de précisions / recherche.
  - Le lien entre les fonctions : comment les briques (`ft_putchar`, `ft_putstr`, `ft_putnbr`, etc.) communiquent entre elles et avec `ft_printf` (qui appelle qui, qui compte les octets, comment la valeur de retour remonte).
  - Ce que `ft_printf` contiendra réellement à l'intérieur d'elle-même : parcours de la chaîne, gestion de `%`, `va_list`, dispatch vers les briques, cumul du retour.
- Prochaine étape : retirer les `main`/`<stdio.h>`/`<limits.h>` de `ft_putnbr.c` et `ft_putunsignednbr.c`, ajouter les cas ci-dessus à la matrice de [[05 - Tests]] ; puis brique 5 : conversion en base (`%x` `%X`).

### 2026-11-21
- Fait :
  - `ft_printf` : boucle sur la chaîne + dispatch via `ft_format(&args, c)` (la `va_list` est passée par pointeur). `ft_percent.c` supprimé.
  - `ft_format` branché pour `%c` `%s` `%d` `%i` `%u` `%%`. `ft_printf` fonctionne sur les cas simples.
  - `%%` corrigé : `ft_format` appelle directement `ft_putchar('%')` (plus de `va_arg` consommé à tort) ; `ft_putpercent.c` supprimé et retiré de `ft_printf.h`.
- État actuel / à corriger :
  - `%p` affiche `To DO` ; `%x` / `%X` appellent `ft_putunsignednbr` (base 10) → conversion en base 16 pas encore faite (brique 5).
  - `ft_format` n'a pas de `return` final (conversion inconnue = comportement indéfini).
  - Gestion d'erreur : les retours `-1` de `write` ne sont pas propagés dans `ft_printf` / `ft_putunsignednbr` (le total s'additionne avec des `-1`).
  - `%s` avec `NULL` n'affiche rien (le vrai `printf` affiche `(null)`).
  - `main` de test encore dans `ft_printf.c` (à sortir vers `test.c`).
- Bloqué sur : rien. Je reprends moi-même la suite.
- Prochaine étape : fonction générique base (`%x` `%X`), puis `%p`, puis propagation des erreurs ; ajouter les cas à [[05 - Tests]].

## Blocages résolus (pour ne pas les refaire)
| Symptôme | Cause | Solution |
|----------|-------|----------|
| | | |
