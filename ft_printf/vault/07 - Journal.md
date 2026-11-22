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

### 2026-11-22
- Fait :
  - `%x` / `%X` : `ft_lowerhex` / `ft_upperhex` (récursion, retours cumulés) dans `ft_puthex.c`, branchés dans `ft_format`.
  - `%p` : `ft_printadress` (`ft_printadress.c`) → `(nil)` si NULL, sinon `0x` + `ft_longhex((unsigned long)p)`. Prototype ajouté au header, fichier ajouté à `SOURCES`.
  - **Bug trouvé puis corrigé dans `ft_longhex`** : cas de base `ft_putchar(n)` au lieu de `ft_putchar(hex[n])` → le 1er chiffre hexa disparaissait (`0x61ff14` affiché `0x1ff14`) et le retour était faux. Corrigé.
  - Testé (`-Wall -Wextra -Werror`) : `&x` → `0x61ff14` (retour 8), `NULL` → `(nil)`, `0x1f` → `0x1f`. Les 3 cas sont corrects.
  - `%s` avec `NULL` affiche maintenant `(null)` ; `ft_format` a un `return (0)` final.
  - Compris : le `printf` de Windows (MinGW) affiche `0061FF14` / `00000000` pour `%p` (majuscules, 8 chiffres, pas de `0x`). Ce n'est pas la référence : l'école est sous Linux (`0x...` en minuscules, `(nil)`).
  - Compris : un pointeur non initialisé donne une valeur différente à chaque exécution (comportement indéfini), il faut tester avec `&x`.
- État actuel / à corriger :
  - **Toutes les conversions sont faites** : `%c` `%s` `%p` `%d` `%i` `%u` `%x` `%X` `%%`.
  - Pas encore comparé à `printf` sur Linux (WSL / VM / cluster 42) ; les écarts vus sous Windows viennent de la libc.
  - Propagation des erreurs : les `-1` de `write` ne sont pas gérés (le total s'additionne avec des `-1`).
  - `(unsigned long)` fait 32 bits sous Windows 64 → tronque l'adresse. OK sous Linux ; `uintptr_t` si besoin de portabilité.
  - Conversion inconnue (`%z`) : retourne 0 sans rien afficher (comportement choisi à noter dans « Décisions de design »).
  - Ménage du dépôt : `main.c` (test `%p` avec pointeur non initialisé) et `vault/test.c` à sortir vers `tests/` ; `a.exe`, `*.o`, `*.d`, `libftprintf.a` ne doivent pas être commités (`.gitignore`).
  - Norminette pas encore passée.
- Bloqué sur : rien.
- Prochaine étape :
  1. Tester sur Linux : comparer `printf` et `ft_printf` (sortie **et** valeur de retour) pour chaque conversion, y compris `INT_MIN`, `UINT_MAX`, `0`, `NULL`, chaîne vide, `%` en fin de chaîne. Noter les cas dans [[05 - Tests]].
  2. Décider et coder la gestion des erreurs `write` (`-1`).
  3. `make` / `make re` propres, vérifier que `libftprintf.a` ne se relink pas pour rien.
  4. Norminette, nettoyage du dépôt (`main`, `a.exe`, `.o`), puis commit.

## Blocages résolus (pour ne pas les refaire)
| Symptôme | Cause | Solution |
|----------|-------|----------|
| `%p` affiche `0x1ff14` au lieu de `0x61ff14` ; retour trop petit | base de `ft_longhex` : `ft_putchar(n)` au lieu de `ft_putchar(hex[n])` | écrire `hex[n]` dans le cas de base |
| `printf("%p")` donne `0061FF1F`, différent à chaque lancement | pointeur non initialisé + libc Windows (majuscules, sans `0x`) | tester avec `&x` et comparer sous Linux |
