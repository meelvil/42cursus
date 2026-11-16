---
tags: [ft_printf, workflow]
---

# Workflow : 1 brique = 1 cycle

Retour : [[00 - Accueil]] · Suite : [[03 - Plan et checklist]]

Chaque petite fonction (une « brique ») passe par le même cycle. Ça évite d'écrire 300 lignes d'un coup puis de ne plus savoir où est le bug.

## Le cycle (30-45 min par brique)

| # | Étape | Durée | Qui |
|---|-------|-------|-----|
| 1 | **Spec** : une phrase. Ex. « `ft_putnbr` écrit un int en décimal et retourne le nombre de caractères écrits » | 2 min | Toi |
| 2 | **Prédire** : sur papier, 4-5 entrées avec la sortie attendue **et** la valeur de retour. Au moins un cas limite (0, INT_MIN, NULL, chaîne vide) | 3 min | Toi |
| 3 | **Coder** : fonction ≤ 25 lignes, un seul rôle | 15-30 min | Toi |
| 4 | **Tester** : mini `main` isolé, comparaison avec le vrai `printf` ([[05 - Tests]]) | 5 min | Toi |
| 5 | **Nettoyer** : `norminette`, noms clairs, pas de code mort | 3 min | Toi |
| 6 | **Commit** : message court, ex. `add ft_putnbr` | 1 min | Toi |

Claude intervient **entre** ces étapes selon les règles de [[02 - Quand appeler Claude]], jamais à la place de l'étape 3.

## Règle des 20 minutes
Bloqué sur le même problème pendant 20 min sans avancer ?
1. Écris dans [[07 - Journal]] : entrée, attendu, obtenu, ce que tu as essayé.
2. Seulement ensuite, appelle Claude (modèle « Bug » dans [[06 - Prompts types]]).

Écrire le problème règle déjà environ la moitié des bugs (rubber duck).

## Rythme conseillé
- Sessions de 45-60 min, 1 à 2 briques max.
- Termine la session sur un **test qui échoue** déjà écrit : tu sais par où reprendre.
- Un commit par brique validée. Si tu casses tout, tu reviens au dernier commit.

## Structure de fichiers suggérée
```
ft_printf/
├── Makefile
├── ft_printf.h
├── ft_printf.c      # ft_printf + dispatcher
├── ft_putchar.c ... # une brique par fichier (ou regroupées, max 5 fonctions/fichier)
└── tests/main.c     # hors rendu : ne pas le pousser sur le dépôt de rendu
```

## Décision de design à prendre toi-même
Toutes les briques retournent un `int` (nombre de caractères écrits, ou -1 si `write` échoue). Pourquoi ? Parce que la valeur de retour de `ft_printf` est la **somme** de ce qu'elles écrivent.
Question à te poser : une fonction générique de conversion en base peut-elle servir pour `%u`, `%x`, `%X` et `%p` ? Quels paramètres lui faut-il ? Note ta réponse dans [[07 - Journal]] : on pourra en discuter.
