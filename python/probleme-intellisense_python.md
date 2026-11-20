# Problème d'intellisense en  Python dans VScode

> * Auteur : Gwénaël LAURENT
> * Date : 14/09/2024
> * VScode v1.90.2

# Problème
**Sur les PC en CIEL** avec VScode 1.90.2 (install ciel 07/2024), l'extension Python ne doit pas dépasser **`ms-python.python@2024.12.3`** sinon pylance ne fonctionne pas (pas d'intellisense en python).

Il faut gérer les extensions en attendant la prochaine maj de VScode sur tous les PC ...

# Gestion des extensions VScode
## 1-Ne pas mettre à jour l'extension Python
## 2-Si l'intellisense python ne marche plus
C'est que l'extension python a été mise à jour.

En attendant la prochaine maj de VScode sur tous les PC ...
1. Fermer VScode
2. Dans un terminal windows, copier/coller lescommandes suivantes :

```cmd
code --uninstall-extension ms-python.pylint --force
code --uninstall-extension ms-python.black-formatter
code --uninstall-extension ms-python.python --force
code --install-extension ms-python.python@2024.12.3 --force
code --install-extension ms-python.black-formatter
code --install-extension ms-python.pylint --force
```

<!-- Vérification des versions d'extensions avec ```code --list-extensions --show-versions```

```cmd
ms-python.debugpy@2024.8.0
ms-python.python@2024.12.3
ms-python.vscode-pylance@2024.8.2
``` -->

3. Re-lancer Vscode


