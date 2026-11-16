---
tags: [ft_printf, claude, prompts]
---

# Prompts types

Retour : [[00 - Accueil]] · Règles : [[02 - Quand appeler Claude]]

Copie-colle, remplace ce qui est entre `[crochets]`.

## 1. Démarrage de session (à coller en premier)
```
Je travaille sur ft_printf (projet 42). J'utilise mon vault : 1 brique = 1 cycle (spec, prédire, coder, tester, nettoyer, commit).
Règles : tu es mon coach, tu n'écris pas mes fonctions du projet. Tu m'aides à comprendre (concepts, indices, relecture) et tu peux donner des exemples sur des cas voisins.
Mode : [GUIDÉ : une seule question à la fois / DIRECT : explications sans question]
Où j'en suis : [phase / brique en cours]
Objectif de la session : [ex. finir ft_putnbr et le tester]
```

## 2. Concept flou
```
Je ne comprends pas [concept, ex. pourquoi va_arg(args, int) pour un %c].
Ce que je crois comprendre : [ta version].
Explique-moi sans code de mon projet.
```

## 3. Bug
```
Brique : [nom]
Appel : [ex. ft_printf("%d", INT_MIN)]
Attendu : [sortie + retour]
Obtenu : [sortie + retour]
Ce que j'ai essayé : [2-3 choses]
Mon hypothèse : [je pense que ça vient de ___ parce que ___]
Mon code (≤ 30 lignes) :
[code]
Niveau d'aide : indice (pas la correction).
```

## 4. Challenge de design
```
Voici mon plan pour [dispatcher / structure de fichiers / passage de la va_list] en 5 lignes :
[plan]
Challenge-le : quels cas ou contraintes (norme, retours, erreurs) j'oublie ?
```

## 5. Relecture finale d'une brique
```
Ma brique [nom] passe mes tests : [liste des cas].
Fais-moi une relecture : lisibilité, cas limites oubliés, respect de la norme (25 lignes, 4 params, 5 variables).
[code]
```

## 6. Quiz de soutenance
```
Fais-moi passer un oral de peer-eval sur ft_printf, comme un évaluateur de 42.
Pose une question à la fois, attends ma réponse, puis corrige-moi.
```
Voir [[08 - Soutenance]].

## 7. Je suis cuit
```
direct
[ta question]
```
Claude bascule en mode DIRECT : explications et étapes, sans question à répondre avant d'avancer.
