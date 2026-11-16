---
tags: [ft_printf, claude, regles]
---

# Quand appeler Claude

Retour : [[00 - Accueil]] · Messages prêts à copier : [[06 - Prompts types]]

## Les 2 modes (tu choisis, tu peux changer à tout moment)

| Mode | Ce que fait Claude | Pour qui / quand |
|------|--------------------|------------------|
| **GUIDÉ** (par défaut) | Explique court, puis pose **une seule question à la fois** et attend ta réponse | Quand tu veux réfléchir et comprendre le « pourquoi » |
| **DIRECT** | Explications et étapes claires, **sans question** à répondre avant d'avancer | Quand tu es fatigué, pressé ou bloqué depuis longtemps |

Mot-clé : écris `direct` (ou « je suis cuit ») et Claude bascule en DIRECT. `guidé` pour revenir.

## Échelle d'aide (monte d'un cran seulement si le précédent ne suffit pas)

| Niveau | Aide | Ce que tu reçois |
|--------|------|------------------|
| 0 | Toi seul, 15-20 min | `man 3 stdarg`, `man 2 write`, tes prédictions papier, relire le message d'erreur |
| 1 | **Concept** | Explication de l'idée (ex. comment marche `va_arg`), sans code de ton projet |
| 2 | **Indice** | Où regarder dans ton code, quelle hypothèse tester, pas la correction |
| 3 | **Relecture** | Quand ça marche : lisibilité, cas limites oubliés, norme |
| 4 | **Exemple voisin** | Un code sur un cas *proche* mais différent (ex. une somme avec `va_arg`), jamais ta fonction du projet |

## Qui fait quoi, étape par étape

| Moment | Tu fais seul | Tu m'appelles pour |
|--------|--------------|--------------------|
| Lecture du sujet | Lire le PDF, reformuler en 5 lignes | Vérifier ta reformulation (facultatif) |
| Architecture (fichiers, signatures) | Proposer ton design en 5 lignes | Que je le challenge |
| Écriture d'une brique | **Tout** | Rien, sauf concept flou (niveau 1) |
| Erreur de compilation | Lire le message, 5 min | Message incompréhensible (colle l'erreur + la ligne) |
| Bug / mauvaise sortie | Règle des 20 min ([[01 - Workflow]]) | Niveau 2, avec le modèle « Bug » |
| Erreurs norminette | Lire la règle citée | Règle pas claire |
| Concept (va_list, bases, pointeurs…) | | **N'importe quand** : c'est le meilleur usage |
| Brique ou projet fini | Tests de [[05 - Tests]] passés | Relecture (niveau 3) |
| Avant l'évaluation | | Quiz oral : [[08 - Soutenance]] |

## Ce qu'on évite
- « Écris-moi `ft_printf` » ou une brique complète : tu ne pourrais pas l'expliquer en peer-eval.
- Copier un code que tu ne peux pas réécrire de tête.
- Appeler dès la première erreur, sans avoir testé une hypothèse.

> [!tip] Réflexe
> Avant d'écrire à Claude, finis cette phrase : « Je pense que le problème vient de ___ parce que ___ ». Même fausse, elle rend l'aide beaucoup plus précise.
