(_Cours Python : [retour sommaire](readme.md#pour-aller-plus-loin)_)
# Chap. 24 : Les ensembles `set` et `frozenset`

> * Auteur : Gwénaël LAURENT
> * Date : 12/02/2025

![CC-BY-NC-SA](../img/cc-by-nc-sa-150.png) [Licence Creative Commons](https://creativecommons.org/licenses/by-nc-sa/3.0/fr/)

- [Chap. 24 : Les ensembles `set` et `frozenset`](#chap-24--les-ensembles-set-et-frozenset)
- [1. Présentation générale des ensembles](#1-présentation-générale-des-ensembles)
- [2. Les ensembles `set`](#2-les-ensembles-set)
- [3. Les ensembles `fozenset`](#3-les-ensembles-fozenset)


# 1. Présentation générale des ensembles

Un ensemble (objet set) est une **collection non triée** d'objets **distincts**. Les utilisations classiques sont le test d'appartenance, la déduplication d'une séquence ou le calcul d'opérations mathématiques telles que l'intersection, l'union, la différence, ou la différence symétrique.

Comme pour les autres collections, les ensembles gèrent `x in set`, `len(set)`, et `for x in set`. En tant que collection non triée, les ensembles n'enregistrent pas la position des éléments ou leur ordre d'insertion. En conséquence, les ensembles n'autorisent ni l'indexation, ni le découpage, ou tout autre comportement de séquence.

**Un ensemble ne peut contenir que des objets "hachables"** : La plupart des types immuables natifs de Python sont hachables, mais les conteneurs mutables (comme les listes ou les dictionnaires) ne le sont pas ; les conteneurs immuables (comme les n-uplets ou les ensembles figés) ne sont hachables que si leurs éléments sont hachables.

Documentation : https://docs.python.org/fr/3.12/library/stdtypes.html#set-types-set-frozenset

# 2. Les ensembles `set`

> Le type `set` est **mutable** — son contenu peut changer en utilisant des méthodes comme add() et remove()

Création d'un ensemble vide :
```py
mon_ensemble = set()
```

Création d'un ensemble avec des données (string):
```py
mon_ensemble = {'jack', 'black'}
ou
mon_ensemble = set(['jack', 'black'])
```
Si on fournit une string seule, le chaine est décomposée en un ensemble de caractères :
```py
>>> set("aei")
{'a', 'e', 'i'}
```

Ajout d'un élément dans l'ensemble :
```py
mon_ensemble.add('john')
```

Tester si un élément appartient à l'ensemble :
```py
if 'john' in mon_ensemble :
    print("john fait partie de l'ensemble")
```

Un ensemble ne peut comporter que des éléments distincts. Si on fournit une collection avec des doublons à un ensemble set, seule une occurence de chaque élément sera ajoutée :
```py
mon_ensemble = set(['jack', 'black', 'jack'])
print(len(mon_ensemble))
print(mon_ensemble)
```
Résultat après exécution :
```sh
2
{'jack', 'black'}
```

Un ensemble ne peut comporter que des éléments distincts. Si on essaye d'ajouter un élément déjà présent, il ne sera pas ajouté :
```py
mon_ensemble = {'jack', 'black'}
mon_ensemble.add("john")
print(len(mon_ensemble))
mon_ensemble.add("john")
print(len(mon_ensemble))
print(mon_ensemble)
```
Résultat à l'exécution :
```sh
3
3
{'john', 'jack', 'black'}
```

On peut rapidement trouver les éléments communs à deux ensembles en utilisation l'intersection des ensembles :
```py
>>> set("aei") & set("azerty")
{'a', 'e'}
```

# 3. Les ensembles `fozenset`

> Le type `frozenset` est **immuable** et hachable — son contenu ne peut être modifié après sa création, il peut ainsi être utilisé comme clé de dictionnaire ou élément d'un autre ensemble.


Création d'un frozenset avec des données :
```py
mon_ensemble = frozenset({'jack', 'black'})
ou
mon_ensemble = frozenset(['jack', 'black'])
```

Si on fournit une string seule, le chaine est décomposée en un ensemble de caractères :
```py
>>> frozenset("aei")
frozenset({'a', 'e', 'i'})
```

Tester si un élément appartient à l'ensemble :
```py
mon_ensemble = frozenset(['jack', 'black', 'john'])
if 'john' in mon_ensemble :
    print("john fait partie de l'ensemble")
```

Un ensemble ne peut comporter que des éléments distincts. Si on fournit une collection avec des doublons à un frozenset, seule une occurence de chaque élément sera ajoutée :
```py
mon_ensemble = frozenset(['jack', 'black', 'jack'])
print(len(mon_ensemble))
print(mon_ensemble)
```
Résultat après exécution :
```sh
2
frozenset({'jack', 'black'})
```

On peut rapidement trouver les éléments communs à deux ensembles en utilisation l'intersection des ensembles :
```py
>>> frozenset("aei") & frozenset("azerty")
frozenset({'a', 'e'})
```