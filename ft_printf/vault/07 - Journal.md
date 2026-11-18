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
  - Briques écrites : `ft_putchar`, `ft_putstr`, `ft_strlen`, `ft_putnbr` (compte les chiffres + signe via `count_digits`, gère `INT_MIN` grâce au `long`), `ft_putunsignednbr` (cast en `unsigned int`, en cours — pas fini).
  - `ft_printf` : seulement un squelette (`va_start` + test `ispercent`), pas encore de boucle ni de dispatch.
  - Compris que `printf` doit retourner le nombre d'octets écrits. Continué ma mental card sur le projet.
- État actuel / à corriger :
  - `ft_putunsignednbr` prend un `int` : à passer en `unsigned int` (sinon `%u` avec grande valeur faux), et finir la fonction.
  - `ft_putnbr` : le retour vient de `count_digits` et non des retours des `ft_putchar` ; les appels récursifs `ft_putnbr(nb / 10)` recalculent `total` pour rien.
  - `ft_printf.c` appelle `ispercent` (défini dans `ft_percent.c`) mais le header déclare `ft_percent` → incohérence ; `va_end` manquant.
  - Makefile : `SOURCES` ne contient que `ft_printf.c` (ajouter les briques) ; faute de frappe `fclean: cleam` ; `-include`/`re` à vérifier.
  - `main` de test restés dans `ft_putnbr.c` et `test.c` (à sortir vers `tests/`).
- Bloqué sur :
  - Le détail du retour de `printf` (octets écrits vs à écrire ?) — besoin de précisions / recherche.
  - Le lien entre les fonctions : comment les briques (`ft_putchar`, `ft_putstr`, `ft_putnbr`, etc.) communiquent entre elles et avec `ft_printf` (qui appelle qui, qui compte les octets, comment la valeur de retour remonte).
  - Ce que `ft_printf` contiendra réellement à l'intérieur d'elle-même : parcours de la chaîne, gestion de `%`, `va_list`, dispatch vers les briques, cumul du retour.
- Prochaine étape : clarifier la valeur de retour (compter les octets réellement écrits par chaque brique) et l'intégrer au test ; finir `ft_putunsignednbr` (brique 4), puis conversion en base (`%x` `%X`).

## Blocages résolus (pour ne pas les refaire)
| Symptôme | Cause | Solution |
|----------|-------|----------|
| | | |
