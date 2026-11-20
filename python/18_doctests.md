(_Cours Python : [retour sommaire](readme.md#pour-aller-plus-loin)_)
# Chap. 18 : Les Doctests en Python

> * Auteur : Gwénaël LAURENT
> * Date : 25/09/2024

![CC-BY-NC-SA](../img/cc-by-nc-sa-150.png) [Licence Creative Commons](https://creativecommons.org/licenses/by-nc-sa/3.0/fr/)

- [Chap. 18 : Les Doctests en Python](#chap-18--les-doctests-en-python)
- [1. Introduction aux Doctests](#1-introduction-aux-doctests)
- [2. Activer les doctests](#2-activer-les-doctests)
  - [2.1. Écriture des Doctests](#21-écriture-des-doctests)
  - [2.2. Exécution des Doctests](#22-exécution-des-doctests)
  - [2.3. Exemple de résultat des doctests](#23-exemple-de-résultat-des-doctests)
- [3. Limites des Doctests](#3-limites-des-doctests)


# 1. Introduction aux Doctests
Les *doctests*  sont un outil intégré à Python permettant d'écrire des **tests simples directement dans la docstring d'une fonction** ou d'une méthode. Cela permet de vérifier que le code se comporte comme prévu en testant des exemples de résultats dans la documentation.

Pourquoi utiliser les Doctests ?
- **Facilité d'utilisation**  : Les doctests sont simples à mettre en place et ne nécessitent pas de structure complexe.
 
- **Documentation dynamique**  : Ils permettent d'associer des exemples de code directement dans la documentation, facilitant ainsi la compréhension pour les développeurs.
 
- **Vérification automatique**  : Les doctests vérifient que les exemples donnés dans la documentation fonctionnent réellement, assurant que celle-ci est toujours à jour.

# 2. Activer les doctests
## 2.1. Écriture des Doctests
Les doctests sont insérés dans les **docstrings  des fonctions**.

La syntaxe des doctests simule une session interactive Python où l’on peut entrer des commandes et observer les résultats attendus.

Exemple d'utilisation :


```python
def somme(a, b):
    """
    Cette fonction retourne la somme de deux nombres.
    
    Exemple d'utilisation:
    >>> somme(3, 5)
    8
    >>> somme(-1, 1)
    0
    >>> somme(0, 0)
    0
    """
    return a + b
```


## 2.2. Exécution des Doctests

En fin de fichier, dans le programme principal, on insére le code pour exécuter tous les doctests présents dans le fichier.


```python
if __name__ == "__main__":
    import doctest
    doctest.testmod(
        optionflags=doctest.NORMALIZE_WHITESPACE | doctest.ELLIPSIS, verbose=True
    )
```

> **IMPORTANT** : l'activation des doctests se fait seulement si `__name__ == "__main__"`, c'est à dire seulement si le fichier est lancé en tant que script.\
> Les doctests ne s'activeront pas si le fichier est chargé comme module.

Explication des paramètres de la fonction `doctest.testmod()`

* **optionflags** : Permet de définir des options pour modifier le comportement des tests.
  * _**doctest.ELLIPSIS**_ : autorise l’utilisation de `...` dans les résultats pour ignorer certaines parties du texte.
  * _**doctest.NORMALIZE_WHITESPACE**_ : ignore les différences de formatage d'espaces dans les résultats (espaces multiples, lignes vides).
* **verbose** : Si verbose=True, affiche chaque test en détail, avec les résultats et les erreurs



<!-- Exécution via la ligne de commande :
```bash
python -m doctest votre_script.py
``` -->

## 2.3. Exemple de résultat des doctests

```
Trying:
    somme(3, 5)
Expecting:
    8
ok
Trying:
    somme(-1, 1)
Expecting:
    0
ok
Trying:
    somme(0, 0)
Expecting:
    0
ok
1 items had no tests:
    __main__
1 items passed all tests:
   3 tests in __main__.somme
3 tests in 2 items.
3 passed and 0 failed.
Test passed.
```

# 3. Limites des Doctests
 
- **Pas adapté aux tests complexes**  : Les doctests ne sont pas idéaux pour des tests plus sophistiqués impliquant des bases de données, des réseaux ou des tests sur des structures de données complexes.
 
- **Sortie stricte**  : Les doctests comparent les résultats avec les sorties exactes, ce qui peut poser problème avec des variations mineures (ex : formatage, espaces).

