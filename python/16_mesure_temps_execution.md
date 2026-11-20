(_Cours Python : [retour sommaire](readme.md#pour-aller-plus-loin)_)
# Chap. 16 : Mesure et affichage du temps d'exécution

> * Auteur : Gwénaël LAURENT
> * Date : 16/09/2024

![CC-BY-NC-SA](../img/cc-by-nc-sa-150.png) [Licence Creative Commons](https://creativecommons.org/licenses/by-nc-sa/3.0/fr/)


- [Chap. 16 : Mesure et affichage du temps d'exécution](#chap-16--mesure-et-affichage-du-temps-dexécution)
- [1. Objectifs](#1-objectifs)
- [2. Mesure du temps avec le module `time`](#2-mesure-du-temps-avec-le-module-time)
- [3. Mesure du temps avec le module `timeit`](#3-mesure-du-temps-avec-le-module-timeit)


# 1. Objectifs
L'objectif est de créer les outils logiciels permettant d'analyser la `performance en vitesse d'exécution` d'un script python.

Il existe 2 techniques en python :
* Avec le module `time` : simple mais peu précis
* Avec le module `timeit` : plus précis, plus fiable

# 2. Mesure du temps avec le module `time`
Documentation : https://docs.python.org/fr/3.11/library/time.html#time.time

La fonction **`time.time()`** renvoie le temps en secondes depuis *epoch* sous forme de nombre à virgule flottante.\
L'*epoch* est le point de départ du temps, le 1er janvier 1970 à 00:00:00 (UTC) pour toutes les plateformes.

```py
import time

start = time.time() 

for i in range(10000):
    calcul = i**i

stop = time.time()
print(stop - start)
```

# 3. Mesure du temps avec le module `timeit`
Documentation : https://docs.python.org/fr/3.11/library/timeit.html

En Python, lorsque vous souhaitez mesurer le temps d'exécution d'un morceau de code, **il est souvent préférable d'utiliser le module `timeit`** plutôt que time pour plusieurs raisons :
* **Précision** : timeit est conçu pour mesurer le temps d'exécution avec une grande précision.
* **Gestion des variations** : En exécutant le code plusieurs fois, timeit permet de lisser les variations causées par d'autres processus en cours sur le système, ce qui donne une mesure plus stable et représentative du temps d'exécution.
* **Isolation du code** : timeit exécute le code dans un environnement isolé. Cela aide à obtenir des mesures plus précises en minimisant l'interférence externe.

La fonction **`timeit.timeit()`** renvoie le temps cumulé pour plusieurs
exécutions d'un fragment de code.\
Cette fonction accepte en entrée trois paramètres :
* `setup` permet de préciser à les modules à charger pour
  permettre l'exécution correcte de la fonction
* `stmt` (_statement_ = instruction) est le code dont on veut mesurer le temps d'exécution 
* `number` est le nombre de fois où l'instruction `stmt` sera
  exécutée. Le temps mesuré sera le temps cumulé pour toutes ces
  exécutions. 

> **Remarque** : le code Python des deux parmaètres `setup`et `stmt` est donné sous forme d'une chaîne de caractères ! 


**Exemple 1 :** Avec un fragment de code
```py
from timeit import timeit

# Code à tester sous forme de chaîne de caractères
code = '''
total = 0
for i in range(1000):
    total += i
'''

# Mesurer le temps d'exécution
temps_exec = timeit(stmt=code, number=1000)
print(f"Temps d'exécution moyen du fragment de code : {temps_exec/1000} secondes")
```

**Exemple 2 :** Avec l'appel d'une fonction
```py
from timeit import timeit

# Définition de la fonction à tester
def somme_des_carres(nb_iter):
    calcul = 0
    for i in range(nb_iter):
        calcul += i**2
    return calcul

# Code à tester
code_to_test = """
somme_des_carres(1000)
"""

# Mesurer le temps d'exécution
# La fonction timeit.timeit prend le code à tester sous forme de chaîne de caractères
# Il est nécessaire d'importer la fonction somme_des_carres dans l'espace de noms d'exécution
temps_exec = timeit(
    stmt=code_to_test, 
    setup="from __main__ import somme_des_carres", 
    number=100
)

print(
    f"Temps d'exécution moyen calculé sur 100 appels de somme_des_carres(1000) : {temps_exec/100} secondes"
)
```


