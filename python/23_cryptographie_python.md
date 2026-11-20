(_Cours Python : [retour sommaire](readme.md#pour-aller-plus-loin)_)
# Chap. 23 : Cryptographie en Python

> * Auteur : Gwénaël LAURENT
> * Date : 21/01/2025

![CC-BY-NC-SA](../img/cc-by-nc-sa-150.png) [Licence Creative Commons](https://creativecommons.org/licenses/by-nc-sa/3.0/fr/)

# 1. Présentation du module `cryptography`
Le module `cryptography` comprend à la fois des recettes de haut niveau et des interfaces de bas niveau vers des **algorithmes cryptographiques courants** tels que les chiffrements symétriques, les résumés de messages et les fonctions de dérivation de clés. 

`cryptography` dépend de la bibliothèque **OpenSSL C** pour toutes les opérations cryptographiques.

Ce module est largement utilisé et reconnu pour sa robustesse et sa sécurité. 

**Fonctionnalités principales :**
- Génération de clés publiques et privées (RSA, DSA, Elliptic Curve, etc.).
- Création et vérification de signatures numériques.
- Chiffrement et déchiffrement symétrique (AES, etc.) et asymétrique (RSA).
- Génération de hachages cryptographiques sécurisés (SHA-256, SHA-512, etc.).
- Certificats X.509 et gestion de clés.

**Sources :**
- [Description du projet sur PyPI](https://pypi.org/project/cryptography/)
- [Documentation officielle](https://cryptography.io/en/latest/)

# 2. Installation
```sh
pip install cryptography
```

# 3. Hashage (digest)

## 3.1. Empreinte d'un texte

```py
from cryptography.hazmat.primitives import hashes

# Création d'un objet pour calculer le hachage
digest = hashes.Hash(hashes.SHA256())

# Ajouter des données au hachage
digest.update(b"Message à hacher")

# Calculer le hachage final
hash_value = digest.finalize()

print(hash_value)
```

## Empreinte d'un fichier

