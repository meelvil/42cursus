---
tags: [push_swap, 42, cours, algos]
---

# 📚 Cours : les algos de push_swap

Retour : [[Plan et checklist]]

Objectif : comprendre **pourquoi** chaque algo marche, avec assez d'images mentales pour le réexpliquer à l'oral. Lis dans l'ordre : chaque partie réutilise la précédente.

---

## 1. Le jeu en une image

Deux piles (stacks). Tu ne vois **que le haut** de chaque pile. Tes seuls gestes :

```
        a            b
      ┌───┐        ┌───┐
 haut │ 3 │        │   │   sa : échange les 2 du haut
      │ 0 │        │   │   pb : haut de a → haut de b
      │ 4 │        │   │   ra : le haut passe tout en bas
 bas  │ 1 │        │   │   rra : le bas passe tout en haut
      └───┘        └───┘
```

Tu ne peux **pas** piocher au milieu. Pour atteindre un élément profond, il faut faire tourner la pile (`ra`/`rra`) : **c'est ça qui coûte des opérations**. Tout l'art du projet = éviter de faire tourner pour rien.

Analogie : une pile d'assiettes, plus une deuxième pile vide à côté. Tu peux déplacer l'assiette du dessus, ou faire tourner la pile comme un carrousel.

---

## 2. Big-O : compter les opérations

Big-O dit **comment le coût grandit quand n grandit** (n = nombre d'éléments). Ici le coût = **nombre d'opérations push_swap affichées** (pas le temps CPU).

| Classe | Se lit | n = 100 | n = 500 | Image |
|--------|--------|---------|---------|-------|
| O(n²) | « n au carré » | 10 000 | 250 000 | pour chaque élément, tu refais le tour de la pile |
| O(n√n) | « n racine de n » | 1 000 | 11 200 | pour chaque élément, tu parcours un petit morceau (√n) |
| O(n log n) | « n log n » | ~660 | ~4 500 | pour chaque élément, tu fais quelques étapes (log n) |

Règles de lecture :
- On ignore les constantes : 3n² et n² sont tous deux O(n²).
- Ces chiffres sont des **ordres de grandeur**. Les vrais nombres d'opérations ont des constantes (ex. radix ≈ 1,5 × n × log n).
- Multiplier n par 5 (100 → 500) multiplie par **25** un O(n²), mais seulement par ~**11** un O(n√n) et ~**7** un O(n log n).

C'est pour ça que le sujet demande trois classes : on voit la différence concrètement sur 500 nombres.

---

## 3. Deux outils à maîtriser avant tout algo

### 3.1 Le rang (indexation / normalisation)
Remplacer chaque valeur par sa **position dans l'ordre trié**. Les valeurs réelles (négatifs, énormes…) ne comptent plus : on travaille avec `0, 1, ..., n-1`.

```
valeurs :  42   -7   1000   5
rangs   :   2    0     3    1      ← -7 est le plus petit (0), 1000 le plus grand (3)
```

Pourquoi : les algos radix et chunks ont besoin de nombres compacts et positifs. Comment calculer : pour chaque élément, **compter combien d'éléments sont plus petits** (double boucle, O(n²) de CPU mais 0 opération push_swap : c'est gratuit pour le score).

Après cette étape, trier `a` = obtenir `0, 1, 2, ..., n-1` de haut en bas.

### 3.2 Le disorder (désordre)
Nombre entre 0 et 1 : proportion de **paires inversées** (un grand avant un petit).
- 0 → déjà trié ; 1 → trié à l'envers ; ~0.5 → mélange aléatoire.
- Sert uniquement à **choisir l'algo** dans le mode adaptive. Calculé une fois, avant tout mouvement.

---

## 4. Algo simple : tri par sélection (O(n²))

**Idée** : « trouve le plus petit, mets-le de côté, recommence ».

1. Cherche le plus petit élément de `a`.
2. Fais-le monter en haut de `a` avec `ra` (s'il est dans la 1re moitié) ou `rra` (2e moitié) : **toujours le chemin le plus court**.
3. `pb`.
4. Répète jusqu'à ce que `a` soit vide (ou à 3 éléments, trivial à trier à la main).
5. `pa` tout : `b` contient les éléments du plus grand (en bas) au plus petit (en haut), donc `a` ressort trié.

```
a = [3, 1, 2]    min = 1 est en 2e position → ra rotation courte
ra → [1, 2, 3]   pb → a=[2,3] b=[1]
min = 2 déjà en haut → pb → a=[3] b=[2,1]
pb → a=[] b=[3,2,1]
pa pa pa → a=[1,2,3]
```

**Pourquoi O(n²)** : n extractions × jusqu'à n/2 rotations chacune. Simple, fiable, lent. Parfait pour un faible désordre où l'on se contente d'un algo correct.

Variantes acceptées par le sujet : insertion, bubble. La sélection est la plus facile à bien coder.

---

## 5. Algo moyen : les chunks (O(n√n))

### C'est quoi un chunk ?
**Chunk = « morceau »**. On découpe la plage des rangs `0..n-1` en tranches de taille égale :

```
n = 100, 5 chunks de 20 :
  chunk 1 : rangs  0-19   (les plus petits)
  chunk 2 : rangs 20-39
  chunk 3 : rangs 40-59
  chunk 4 : rangs 60-79
  chunk 5 : rangs 80-99   (les plus grands)
```

Le nombre de chunks vaut environ **√n** (donc ~ 5 à 8 pour 100, ~ 11 à 14 pour 500), d'où le O(n√n).

### Pourquoi ça aide
Trouver un petit élément précis dans une grande pile coûte cher (grosse rotation). Mais trouver **n'importe lequel** d'un groupe d'éléments est rapide : il y en a plein, l'un est forcément près du haut. On travaille donc par groupes.

### Phase 1 : vider `a` dans `b`, chunk par chunk
- Parcours `a` : si l'élément fait partie du **chunk en cours** → `pb`. Sinon → `ra` (on le laisse passer).
- Quand le chunk est épuisé, passe au suivant.
- Astuce courante : après un `pb`, si l'élément est dans la moitié basse du chunk, ajoute `rb` (il file au fond de `b`). Ainsi `b` est « presque trié » : petits en bas, grands en haut.

À la fin : `a` est vide (ou presque), `b` contient tout, grossièrement classé par chunks.

### Phase 2 : rapatrier dans `a` dans l'ordre
- Répète : trouve le **plus grand** de `b`, amène-le en haut avec `rb` ou `rrb` (chemin le plus court), puis `pa`.
- Comme on prend toujours le max, `a` se remplit de haut en bas : ..., 3, 2, 1... puis le plus petit en dernier au sommet : `a` est trié.

### Pourquoi O(n√n)
Phase 1 : chaque élément coûte O(1) en moyenne (un morceau l'attend près du haut). Phase 2 : dans `b`, le max est dans le chunk du dessus, donc à au plus ~√n rotations du haut. n éléments × √n = n√n.

> [!tip] Réglage
> Le nombre de chunks se règle **empiriquement** : teste 5, 6, 7, 8… sur 100 nombres, 10-14 sur 500, sur beaucoup de tirages aléatoires, garde le meilleur. C'est normal et attendu.

---

## 6. Algo complexe : le radix sort (O(n log n))

### D'où vient le nom
**Radix** = « base » (comme dans *radix 10* = base 10). Au lieu de **comparer** deux nombres entre eux, on regarde leurs **chiffres un par un**. Ici on travaille en base 2 : on regarde les **bits**.

> [!note] Analogie : trier des cartes à la main (version décimale)
> Tu as des nombres à 2 chiffres. Passe 1 : range dans 10 tas selon le chiffre des **unités**, ramasse les tas dans l'ordre. Passe 2 : même chose selon le chiffre des **dizaines**. Après la 2e passe, tout est trié, sans jamais avoir comparé deux nombres. C'est le radix **LSD** (*Least Significant Digit* : on commence par le chiffre de poids **faible**).

Nous, il n'y a que 2 tas par passe (bit = 0 ou bit = 1), et nos « tas » sont les deux piles `a` et `b`.

### Rappel : les bits
```
rang 5 = 101 en binaire
bit 0 (poids faible, à droite) = 1
bit 1                          = 0
bit 2                          = 1
```
En C, valeur du bit `i` de `x` : `(x >> i) & 1`.
Nombre de bits nécessaires : le nombre de bits de `n - 1` (ex. n = 100 → rang max 99 → 7 bits ; n = 500 → 499 → 9 bits).

### Une passe (pour le bit `i`)
Pour **chaque** élément du haut de `a` (exactement `n` fois) :
- si son bit `i` vaut **0** → `pb`
- si son bit `i` vaut **1** → `ra` (il reste dans `a`, repasse en bas)

Puis `pa` jusqu'à vider `b`.

Effet : les éléments à 0 se retrouvent **devant**, ceux à 1 **derrière**, et **l'ordre relatif précédent est conservé** dans chaque groupe (c'est la propriété de **stabilité**, le secret du radix : la passe suivante ne détruit pas le travail de la précédente).

### Exemple complet : `a = [3, 0, 4, 1, 2]` (rangs, haut → bas), 3 bits

```
Passe bit 0 :  3(011)→1 ra   0(000)→0 pb   4(100)→0 pb   1(001)→1 ra   2(010)→0 pb
               puis pa pa pa            → a = [0, 4, 2, 3, 1]
                                          (les bit0=0 devant : 0,4,2 | puis bit0=1 : 3,1)

Passe bit 1 :  0→0 pb   4→0 pb   2(010)→1 ra   3(011)→1 ra   1(001)→0 pb
               puis pa pa pa            → a = [0, 4, 1, 2, 3]

Passe bit 2 :  0→0 pb   4(100)→1 ra   1→0 pb   2→0 pb   3→0 pb
               puis pa pa pa pa         → a = [0, 1, 2, 3, 4]   ✅ trié
```

Refais-le à la main sur un autre exemple : c'est l'exercice qui fait « cliquer ».

### Coût
Chaque passe ≈ n opérations (`pb`/`ra`) + environ n/2 `pa` = **~1,5 n**. Nombre de passes = nombre de bits ≈ log₂ n. Total ≈ **1,5 n log₂ n** → **O(n log n)**. Mesures attendues : ~1000-1100 pour 100 nombres, ~6500-7000 pour 500.

Atouts : ~20 lignes de code, **aucune** logique de cas particulier, marche toujours. Limite : jamais « excellent » seul (il fait toujours le même travail, même si la pile est presque triée).

---

## 7. Algo adaptatif : choisir selon le désordre

L'idée : **pas un seul bon algo, mais le bon algo pour la situation.**

| Disorder | Régime | Algo possible | Classe exigée |
|----------|--------|---------------|---------------|
| < 0.2 | peu désordonné | sélection / insertion | O(n²) |
| 0.2 ≤ d < 0.5 | moyen | chunks | O(n√n) |
| ≥ 0.5 | très désordonné | radix | O(n log n) |

Pourquoi ces choix (à reprendre dans ton README) :
- Presque trié → peu à corriger : un algo simple suffit et évite le coût fixe du radix.
- Beaucoup de désordre → il faut un algo qui **grandit lentement** avec n : radix.
- ⚠️ Un mélange aléatoire a un disorder ≈ **0.5** : il tombe pile sur la frontière. Tes algos medium **et** complex doivent donc tous deux atteindre les cibles de benchmark.

---

## 8. Complexité pour le README (argument en une ligne chacun)

| Algo | Temps (nb d'opérations) | Espace |
|------|-------------------------|--------|
| Sélection | n extractions × ≤ n/2 rotations = O(n²) | O(n) : les 2 tableaux |
| Chunks | n éléments × ≈ √n rotations = O(n√n) | O(n) |
| Radix | log n passes × O(n) opérations = O(n log n) | O(n) |
| Adaptive | = celui du régime choisi (borne supérieure par régime) | O(n) |

---

## 9. Pour aller plus loin (optionnel)

- **Optimiser avec `rr` / `rrr`** : quand `a` et `b` doivent tourner dans le même sens, une seule opération au lieu de deux.
- **Algo de Turk** : à chaque `pb`, calculer le coût de chaque candidat et prendre le moins cher. Excellent en opérations, mais plus long à coder et à justifier.
- **Merge sort / quicksort** avec deux piles : mêmes classes que radix, plus complexes à écrire.

---

## 10. Pense-bête oral (soutenance)

- **Chunk ?** Un morceau de la plage de rangs ; on traite les éléments par groupes pour éviter les grosses rotations.
- **Radix ?** Tri chiffre par chiffre (ici bit par bit), du poids faible au poids fort, sans comparer les éléments entre eux.
- **Pourquoi le rang ?** Pour travailler avec `0..n-1` : plus de négatifs, bits en nombre fixe.
- **Pourquoi le radix marche ?** Chaque passe est **stable** : elle conserve l'ordre issu de la passe précédente.
- **Pourquoi O(n log n) ?** log n passes (un bit chacune), chacune coûte O(n) opérations.
- **Pourquoi `ra` vs `rra` ?** On prend toujours le plus court chemin pour atteindre l'élément.
- **Pourquoi adaptive ?** Un algo différent selon le désordre mesuré, avec la complexité exigée par régime.
