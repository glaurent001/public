# GIT : Installation de Git sur Windows

> * Auteur : Gwénaël LAURENT
> * Date : 02/08/2023
> * OS : Windows 10 (version 22H2)
> * VScode : version 1.80.0 (system setup)
> * Git : version 2.41.0.windows.1


![CC-BY-NC-SA](../img/cc-by-nc-sa-150.png) [Licence Creative Commons](https://creativecommons.org/licenses/by-nc-sa/3.0/fr/)

- [GIT : Installation de Git sur Windows](#git--installation-de-git-sur-windows)
- [1. Installation du logiciel **```Git```**](#1-installation-du-logiciel-git)
- [2. Paramétrage à la première utilisation de Git](#2-paramétrage-à-la-première-utilisation-de-git)



# 1. Installation du logiciel **```Git```**
Documentation [Git : Installation de Git](https://git-scm.com/book/fr/v2/D%C3%A9marrage-rapide-Installation-de-Git)

Si l'utilitaire ```git``` est déjà installé sur votre ordinateur, la commande suivante doit renvoyer la version :
```shell
>git --version
git version 2.41.0.windows.1
```

Si ```git``` n'est pas reconnu en tant que commande interne, il va falloir l'installer.

Téléchargez git pour windows sur le site [https://git-scm.com/](https://git-scm.com/)

* Double cliquez sur le fichier téléchargé : Git-2.41.0-64-bit.exe
* Emplacement par défaut : C:\Program Files\Git
* Select components : par défaut (attention toutefois à avoir coché "Git Bash Here" et "Git GUI Here")
* Start menu folder : git
* Choosing the default editor used bu Git : Use Visual Studio Code as Git's default editor
* Adjusting the name of the initial branch in new repositories : Let Git decide
* Adjusting your PATH environment : Git from the command line and also from 3-rd-party software
* Choosing the SSH executable : Use bundled OpenSSH
* Choosing HTTPS transport backend : Use the OpenSSL library
* Configuring the line ending conversions : Checkout Windows-style, commit Unix-style line endings
* Configuring the terminal emulator to use with Git Bash : Use MinTTY
* Choose the default behavior og 'git pull' : Default
* Choose a credential helper : Git Credential Manager Core
* Configuring extra options : Enable file system caching, Enable symbolic links
* Configuring experimental options : RIEN
* Cliquez sur "Install"




# 2. Paramétrage à la première utilisation de Git
Documentation [Git : Paramétrage à la première utilisation de Git](https://git-scm.com/book/fr/v2/D%C3%A9marrage-rapide-Param%C3%A9trage-%C3%A0-la-premi%C3%A8re-utilisation-de-Git)

> Vous ne devriez avoir à réaliser ces réglages qu’une seule fois ; ils persisteront lors des mises à jour. Vous pouvez aussi les changer à tout instant en relançant les mêmes commandes.

Si c'est la première fois que vous utilisez GIT sur votre ordinateur, il faut lui indiquer qui vous êtes (utilisez la même adresse mail que celle que vous utiliserez pour votre dépôt Cloud):
```sh
git config --global user.email "votre.adresse@email"
git config --global user.name "votre nom"
```

> Avec l’option --global, Git utilisera toujours ces informations pour tout ce que votre utilisateur fera sur ce système.

> Vous pouvez afficher la configuration de Git avec la commande ```git config --list```

