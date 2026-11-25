# Guide GNL : t'orienter sans te donner la solution

> Je ne te donne **pas** le code. Je te donne : un diagnostic de ton fichier actuel, une façon de découper le problème, des questions à te poser, et des tests.
> Prérequis : lire [static_variables.md](static_variables.md).

---

## 1. Diagnostic de ton `get_next_line.c` actuel

Ce que tu as fait : ouvrir un fd, appeler `read`, afficher. C'est un bon début pour *voir* ce que `read` fait. Mais voici ce qui coince, du plus important au plus mineur. **Essaie de comprendre chaque point avant de corriger.**

### 🔴 Bugs / erreurs de compréhension

1. **`malloc(sizeof(char *) * BUFFER_SIZE)`**
   - Qu'est-ce que `sizeof(char *)` ? Est-ce la taille d'un `char` ? Combien d'octets réserves-tu vs ce dont tu as besoin ?
   - As-tu prévu de la place pour un caractère spécial en fin de chaîne ?
2. **Pas de `'\0'` après `read`**
   - `read` remplit un buffer d'octets **bruts**. Elle ne met jamais de `'\0'`. Qu'est-ce que `printf("%s")` fait quand il n'en trouve pas ? (C'est un comportement indéfini : tu as peut-être déjà vu des caractères bizarres.)
3. **La valeur de retour de `read` (`r`) est ignorée**
   - `read` renvoie `> 0`, `0` ou `-1`. Que signifie chacun ? Ton code réagit-il différemment dans chaque cas ?
4. **Ta `static` ne sert à rien pour l'instant**
   - Tu fais `output = malloc(...)` à chaque appel : tu **écrases** immédiatement ce que la static contenait. Elle ne mémorise donc rien, et en plus l'ancienne mémoire est perdue (fuite).
   - Question : qu'est-ce qui devrait survivre d'un appel à l'autre ? Est-ce ce que tu renvoies, ou autre chose ?
5. **Tu renvoies la même variable que tu gardes en static**
   - Puis `main` fait `free(output)`. Si cette adresse est aussi gardée dans la static, que se passe-t-il au prochain appel ? (Pense « dangling pointer », section 4 du doc static.)

### 🟠 Respect du sujet

6. **`printf` n'est pas autorisé.** Fonctions externes permises : `read`, `malloc`, `free`. Rien d'autre dans les fichiers à rendre. (Pour tes tests dans un `main` séparé, tu peux utiliser ce que tu veux, mais ce `main` n'est pas rendu.)
7. **`main` dans `get_next_line.c`** : à sortir dans un fichier de test à part (`main_test.c`), que tu ne rendras pas. Sinon conflit à l'évaluation.
8. **Includes inutiles** (`stdio.h`, `fcntl.h`) dans le `.c` rendu : à enlever une fois le `main` sorti.
9. **`get_next_line_utils.c` est vide** : tu en auras besoin (le sujet dit explicitement d'y mettre tes helpers). Mais attention aux contraintes Norme : 25 lignes max par fonction, 5 fonctions max par fichier, 4 paramètres max, etc.
10. **Validation d'entrée** : que doit renvoyer ta fonction si `fd < 0` ? Si `BUFFER_SIZE <= 0` ? Si `read` échoue ?

### 🟡 Ton fichier de test

11. `fd.txt` contient des fins de ligne **`\r\n`** (Windows) : `Melvil\r\nHello\r\nWorld`. Ton programme verra donc un `\r` avant chaque `\n`. Pour des tests propres : `sed -i 's/\r$//' fd.txt` (ou recrée le fichier).
12. Bonne chose : il ne finit **pas** par `\n`, c'est un cas que le sujet cite explicitement. Garde-le !

---

## 2. Comment penser le problème (sans code)

### Étape A : comprendre `read`

Fais d'abord des petits tests :

- Que renvoie `read` si `BUFFER_SIZE` est plus grand que le fichier ? Plus petit ?
- Si tu rappelles `read` sur le même fd, reprend-elle au début ou « là où elle s'est arrêtée » ? (Le fd garde un curseur en interne.)
- Quel est le lien entre la taille lue et la fin d'une ligne ? Une ligne tient-elle forcément dans **un** `read` ? Un `read` contient-il forcément **une seule** ligne ?

> 💡 Les deux dernières questions sont le cœur du projet. Prends du papier, fais un schéma avec `BUFFER_SIZE = 4` et le texte `Melvil\nHello\nWorld`, et découpe-le en morceaux de 4 caractères.

### Étape B : le dilemme de la « sur-lecture »

Avec `BUFFER_SIZE = 4`, le premier `read` te donne `Melv`. Le deuxième `il\nH`. Tu as trouvé ton `\n`, tu peux renvoyer `Melvil\n`… mais **le `H` a déjà été lu**, et le fd ne reculera pas.

Questions :
- Où ranges-tu ce `H` pour le prochain appel ?
- Cette information doit-elle survivre entre deux appels ? → C'est **là** que `static` entre en jeu.
- Que contient-elle au tout premier appel ? (`NULL` ? chaîne vide ? Réfléchis à ce qui rend ton code le plus simple.)

### Étape C : découper en petites fonctions

Le projet est beaucoup plus simple si tu ne fais pas tout dans `get_next_line`. Suggestion de **responsabilités** (les noms et signatures sont à toi) :

| Besoin | Question à te poser |
|---|---|
| Savoir si le texte mémorisé contient un `\n` | Que renvoies-tu s'il n'y en a pas ? |
| Coller deux morceaux de texte ensemble | Qui `free` l'ancien morceau ? Comment éviter une fuite ? |
| Extraire « une ligne » du texte mémorisé | Faut-il inclure le `\n` ? (Relis le sujet.) Et si on est en fin de fichier ? |
| Garder « ce qui reste après la ligne » | Où le stockes-tu ? Que se passe-t-il s'il ne reste rien ? |
| Mesurer une chaîne / copier | Tu as déjà ça dans ta libft… mais tu ne peux pas l'utiliser directement ici : à toi de voir comment gérer ça. |

Le flux global, en mots :

```
1. Vérifier les entrées (fd valide, BUFFER_SIZE valide)
2. Tant que la mémoire n'a pas de '\n' ET que read n'a pas fini :
       lire un morceau, le rajouter à la mémoire
3. Si la mémoire est vide / erreur → renvoyer NULL (et tout nettoyer)
4. Extraire la ligne à renvoyer
5. Mettre à jour la mémoire avec ce qui reste
6. Renvoyer la ligne
```

À toi de traduire chaque étape en C. Si une étape te bloque, c'est une bonne question à poser à un pair.

---

## 3. Cas limites : ta checklist avant de rendre

Teste **chacun** de ces cas (écris-les en fichiers) :

- [ ] Fichier vide
- [ ] Fichier avec une seule ligne sans `\n`
- [ ] Fichier avec une seule ligne avec `\n`
- [ ] Fichier qui finit par `\n`, et un autre qui n'y finit pas
- [ ] Lignes vides consécutives (`\n\n\n`)
- [ ] Une ligne beaucoup plus longue que `BUFFER_SIZE`
- [ ] `BUFFER_SIZE = 1`
- [ ] `BUFFER_SIZE = 9999` et même `10000000`
- [ ] Lecture depuis l'entrée standard (`fd = 0`), termine avec `Ctrl+D`
- [ ] `fd` invalide (`-1`, ou fd fermé)
- [ ] Appeler GNL **après** qu'il ait renvoyé `NULL` : doit renvoyer `NULL` à nouveau, sans crash
- [ ] Fichier binaire / contenant des `\0` (au moins ne pas crasher)

### Compilation à tester

```bash
cc -Wall -Wextra -Werror -D BUFFER_SIZE=1   get_next_line.c get_next_line_utils.c main_test.c
cc -Wall -Wextra -Werror -D BUFFER_SIZE=42  ...
cc -Wall -Wextra -Werror -D BUFFER_SIZE=9999 ...
cc -Wall -Wextra -Werror                    ...   # sans le flag : ta valeur par défaut du .h
```

### Détection des fuites et erreurs mémoire

```bash
valgrind --leak-check=full --show-leak-kinds=all ./a.out
cc -g -fsanitize=address ...
```

Le sujet interdit toute fuite : **n'oublie pas le cas où tu arrêtes de lire avant la fin du fichier**… mais regarde bien ce qui est ta responsabilité et ce qui est celle de l'appelant.

---

## 4. Erreurs classiques à anticiper

1. Oublier le `'\0'` en fin de chaîne après `malloc` / `read`.
2. `malloc(taille)` sans `+ 1`.
3. Perdre un pointeur avant de l'avoir `free`.
4. `free` un bloc et continuer à utiliser le pointeur.
5. Oublier de gérer `read` qui renvoie `-1` (et de nettoyer la static dans ce cas).
6. Boucler à l'infini quand `read` renvoie `0` sans que ta condition d'arrêt le voie.
7. Réutiliser un buffer sans le remettre propre.
8. Déclarer un gros buffer en local (`char buf[BUFFER_SIZE]`) : et si `BUFFER_SIZE` vaut 10 000 000 ? (Stack overflow.) Réfléchis à `malloc` à la place.

---

## 5. Le bonus (seulement quand le mandatory est parfait)

Le sujet bonus demande de gérer **plusieurs fd en parallèle** avec **une seule variable static**.
Relis la section 5 de [static_variables.md](static_variables.md) (tableau static) et pose-toi la question : *qu'est-ce qui devrait servir d'index ?* Et quelle est la limite d'un fd sur ton système (`ulimit -n`) ?
Fichiers : `get_next_line_bonus.c`, `get_next_line_utils_bonus.c`, `get_next_line_bonus.h`.

---

## 6. Plan de travail conseillé

1. Sortir le `main` dans `main_test.c`, nettoyer `fd.txt` (`\r`).
2. Faire les petites expériences sur `read` (étape A) avec des `write(1, ...)`.
3. Faire sur papier le schéma du découpage par morceaux (étape B).
4. Écrire les helpers un par un, **les tester seuls** avant de les brancher.
5. Assembler dans `get_next_line`, d'abord avec `BUFFER_SIZE` grand, puis `1`.
6. valgrind + checklist des cas limites.
7. `norminette` à chaque étape, pas à la fin.
8. Défense : sois capable d'expliquer à voix haute **pourquoi** ta static est là et **ce qu'elle contient** à chaque instant.

---

## 7. Quand tu es bloqué

- Écris sur papier l'état de ta static **avant** et **après** chaque appel, sur un exemple de 3 lignes. 90 % des blocages se résolvent là.
- Utilise `printf` / `write` temporairement pour afficher la static à chaque étape (et retire-les ensuite).
- Parle à un pair, explique-lui ton schéma. Le sujet le recommande explicitement.
- Si tu reviens me voir : montre-moi **ton** code et **ton** raisonnement, et dis-moi exactement ce que tu attendais vs ce que tu as obtenu. Je te relirai et te poserai des questions plutôt que de te donner la réponse.
