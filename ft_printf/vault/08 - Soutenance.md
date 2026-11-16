---
tags: [ft_printf, soutenance, peer-eval]
---

# Préparer la soutenance

Retour : [[00 - Accueil]] · Quiz avec Claude : [[06 - Prompts types]] (modèle 6)

Réponds **à voix haute, avec tes mots**, sans regarder ton code. Si tu bloques, c'est un signal : retourne à [[04 - Concepts clés]].

## Questions probables
1. Que fait `ft_printf` en une phrase ? Que retourne-t-elle ?
2. Comment fonctionne `va_list` ? Que font `va_start`, `va_arg`, `va_end` ?
3. Pourquoi lis-tu un `int` avec `va_arg` pour `%c` ?
4. Pourquoi utiliser `write` et pas `printf` ?
5. Comment gères-tu `INT_MIN` ? Pourquoi ça pose problème ?
6. Pourquoi `%x` et `%u` lisent-ils un `unsigned int`, et `%p` un pointeur ?
7. Comment convertis-tu un nombre en base 16 ? Récursion ou tampon ? Pourquoi ce choix ?
8. Que se passe-t-il pour `%s` avec `NULL` ? Et `%p` avec `NULL` ?
9. Comment ton Makefile évite-t-il le relink ?
10. Comment as-tu vérifié l'absence de fuites mémoire ?
11. Que se passe-t-il si `write` échoue ?
12. Montre-moi comment tu ajouterais une nouvelle conversion.

## Exercice final
Choisis une brique au hasard et réécris-la de tête sur papier en 10 minutes. Puis compare avec ton code.

## Checklist avant l'éval
- [ ] Je sais expliquer chaque fichier et chaque fonction
- [ ] Je peux dire pourquoi j'ai fait chaque choix de [[07 - Journal]]
- [ ] Le dépôt est propre et compile depuis zéro
