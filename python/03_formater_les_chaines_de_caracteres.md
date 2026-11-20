(_Cours Python : [retour sommaire](readme.md#les-bases-du-langage-python)_)
# Chap. 3 : Formater des chaînes de caractères

> * Auteur : David Cassagne - https://courspython.com/
> * Adaptation : Gwénaël LAURENT
> * Date : 01/09/2024

![CC-BY-NC-SA](../img/cc-by-nc-sa-150.png) [Licence Creative Commons](https://creativecommons.org/licenses/by-nc-sa/3.0/fr/)

- [Chap. 3 : Formater des chaînes de caractères](#chap-3--formater-des-chaînes-de-caractères)
- [1. Présentation](#1-présentation)
- [2. Utilisation des f-strings](#2-utilisation-des-f-strings)
- [3. Spécifier le format](#3-spécifier-le-format)
  - [3.1. Nombre de caractères pour afficher un entier](#31-nombre-de-caractères-pour-afficher-un-entier)
  - [3.2. Alignement](#32-alignement)
  - [3.3. Formatage d’un nombre à virgule (float)](#33-formatage-dun-nombre-à-virgule-float)
  - [3.4. Écriture scientifique](#34-écriture-scientifique)


# 1. Présentation
Le formattage des chaines de cractères permet d'insérer des expressions (le contenu de variables) à l'intérieur d'une chaine de caractères. Cela permet aussi de choisir le format d'affichage des nombres (nombre de chiffres après la virgule par exemple.)

En Python, il existe plusieurs techniques pour formater des chaînes de caractères, mais la technique la plus recommandée actuellement est l'utilisation des **f-strings** (formatted string literals), introduite dans Python 3.6. Les f-strings sont appréciées pour leur simplicité, leur lisibilité et leurs performances.


# 2. Utilisation des f-strings
**Syntaxe :** Une f-string est une chaîne de caractères préfixée par la lettre `f` ou `F`, et les expressions Python à évaluer sont placées entre des accolades `{}` à l'intérieur de la chaîne.

**Exemple :**
```py
nom = "Alice"
age = 30
message = f"Je m'appelle {nom} et j'ai {age} ans."
print(message)
```
Résultat après exécution :
```
Je m'appelle Alice et j'ai 30 ans.
```

Voir aussi : [Les chaines de caractères formatées (f-strings)](https://docs.python.org/fr/3/tutorial/inputoutput.html#formatted-string-literals)

# 3. Spécifier le format
Si on souhaite préciser un format pour la chaîne produite, on utilise **`:`** suivi des paramètres de formatage.

## 3.1. Nombre de caractères pour afficher un entier
Par exemple, il est possible d’indiquer un nombre entier qui précise la largeur à utiliser pour afficher la valeur transmise. Il y aura ainsi au sein de la chaîne produite un nombre de caractères fixé pour afficher la valeur. Si la valeur à une longueur trop petite, des espaces seront ajoutés pour arriver à la largeur voulue.

```py
>>> a = 5
>>> b = 8
>>> print(f"Les valeurs sont {a:10} et {b:10}")
Les valeurs sont          5 et          8
```

Ici les valeurs de a et b sont affichées en occupant 10 caractères chacune.

Pour bien comprendre cela, nous allons générer la chaîne de caractères correspondante et vérifier que sa longueur est bien 10.

```py
>>> t = f"{a:10}"
>>> type(t)
<class 'str'>
```

Nous voyons donc que l’instruction f"{a:10}" a bien renvoyé une chaîne de caractères.

```py
>>> len(t)
10
```

Ceci confirme que la chaîne contenue dans t est constituée de 10 caractères.

## 3.2. Alignement
Il est possible d’aligner à gauche en utilisant le signe inférieur **`<`**.

```py
>>> print(f"Les valeurs sont {a:<10} et {b:<10}")
Les valeurs sont 5          et 8
```

Pour centrer, on utilise le caractère **`^`**.

```py
>>> print(f"Les valeurs sont {a:^10} et {b:^10}")
Les valeurs sont     5      et     8     
```

## 3.3. Formatage d’un nombre à virgule (float)
Si on veut fixer la précision lors de l’affichage d’un nombre, on indique **`.`** puis on précise le nombre de chiffres après la virgule suivi du caractère `f`.

Il est possible d’indiquer **`:X.Yf`** où X précise la longueur de la chaîne de caractères produite et Y le nombre de chiffres après la virgule.

```py
>>> c = 123.12345
>>> print(f"La valeur est {c}")
La valeur est 123.12345
>>> print(f"La valeur formatée est {c:10.2f}")
La valeur formatée est     123.12
```

Si on n’indique pas de valeur pour X entre les deux-points **`:`** et le point **`.`**, la longueur de la chaîne s’adapte au nombre de caractères à afficher. On utilise alors seulement Y pour préciser le nombre de chiffres après la virgule en indiquant **`:.Yf`**.

```py
>>> print(f"La valeur formatée est {c:.2f}")
La valeur formatée est 123.12
```

Il est également possible d’aligner à gauche ou de centrer avec les caractères `<` et `^` comme précédemment.

```py
>>> print(f"Les valeurs sont {c:<10.2f} et {c:^10.2f} avec alignement")
Les valeurs sont 123.12     et   123.12   avec alignement
```

Pour aller plus loin, vous pouvez par exemple consulter le site suivant : https://he-arc.github.io/livre-python/fstrings/index.html.

## 3.4. Écriture scientifique
Pour les nombres très grands ou très petits, l'écriture formatée permet d'afficher un nombre en notation scientifique (sous forme de puissance de 10) avec la lettre e :

```py
>>> print(f"{1000000000:e}")
1.000000e+09
```

Il est également possible de définir le nombre de chiffres après la virgule. Dans l'exemple ci-dessous, on affiche un nombre avec aucun, 3 et 6 chiffres après la virgule :

```py
>>> print(f"{1000000000:.0e}")  
1e+09
>>> print(f"{1000000000:.3e}") 
1.000e+09
>>> print(f"{1234567890:.6e}") 
1.234568e+09
```


Voir aussi : 
* [Guide de référence pour le Mini-langage de spécification de format](https://docs.python.org/fr/3/library/string.html#formatspec)
* [f-strings par Thibaut Piquerez](https://he-arc.github.io/livre-python/fstrings/index.html)