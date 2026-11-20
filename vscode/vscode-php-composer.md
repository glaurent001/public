# PHP Installer Composer

> * Auteur : Gwénaël LAURENT
> * Date : 25/07/2023
> * OS : Windows 10 (version 22H2)
> * WAMPSERVER 64 bits (x64) 3.3.0

![CC-BY-NC-SA](../img/cc-by-nc-sa-150.png) [Licence Creative Commons](https://creativecommons.org/licenses/by-nc-sa/3.0/fr/)

- [PHP Installer Composer](#php-installer-composer)
- [0. Présentation](#0-présentation)
- [1. PHP doit être dans le PATH de Windows](#1-php-doit-être-dans-le-path-de-windows)
- [2. Installer Composer](#2-installer-composer)
- [3. Utilisation succinte de composer](#3-utilisation-succinte-de-composer)

# 0. Présentation
> Inspiré du tuto de Grafikart ["Composer"](https://www.grafikart.fr/tutoriels/composer-480)

Composer est un gestionnaire de dépendance qui vous permettra de définir les différentes dépendances pour votre projet. Composer utilise un fichier **composer.json** qui contient plusieurs informations sur le projet dont la liste des librairies utilisées. Il est ensuite capable de télécharger automatiquement ces librairies (et les dépendances associées) et de générer un autoloader pour les utiliser simplement dans vos projets PHP

# 1. PHP doit être dans le PATH de Windows
Vérifiez dans un terminal que ```php.exe``` est disponible :
```shell
>php --help
'php' n’est pas reconnu en tant que commande interne
ou externe, un programme exécutable ou un fichier de commandes.
```
Si le terminal indique que php n'est pas reconnu en tant que .... il faut modifier la variable d'environnement système ```Path```.
Si la commande affiche l'aide de php, vous pouvez passer à l'installation de ```Composer```

Modification des ```variables d'environnement Windows``` :

* Affichez la fenêtre de modification des variables d'environnement système :
  * Touche Windows > recherchez "variables" > Cliquez sur "Modifier les variables d'environnement système" > Cliquez sur le bouton "Variables d'environnement" 

* Modifiez la variable d'environnement système ```Path``` : sélectionnez la variable ```Path``` > "```Modifier```" 

    Ajoutez une nouvelle valeur ```Nouveau``` (à adapter suivant la version de Wampserver que vous avez installée, ici c'est wampserver 3.3.0 avec PHP 8.0.26 actif):
    ```
    C:\wamp64\bin\php\php8.0.26
    ```

> Remarque : les modifications des variables d'environnement ne sont pas prises en compte dans les fenêtres d'invite de commandes déjà ouvertes. Il faut donc absolument en ouvrir une nouvelle pour tester les modifications.

Ouvrez une **nouvelle fenêtre** d'invite de commande et vérifiez que ```php.exe``` est disponible :
```shell
>php --help
Usage: php [options] [-f] <file> [--] [args...]
   php [options] -r <code> [--] [args...]
   php [options] [-B <begin_code>] -R <code> [-E <end_code>] [--] [args...]
   php [options] [-B <begin_code>] -F <file> [-E <end_code>] [--] [args...]
   ...
```

# 2. Installer Composer
Télécharger le Windows Installer "Composer-Setup.exe" sur le site [https://getcomposer.org/download/](https://getcomposer.org/download/)

Double cliquez sur le fichier téléchargé.
- Install for all users
- Ne pas cocher le "Developer mode"
- Choose command line PHP : C:\wamp64\bin\php\php8.0.26\php.exe (la même que dans le PATH)
- Ajouter cet emplacement dans le path

Ouvrez **un nouveau terminal** et tappez la commande suivante

```shell
>composer
   ______
  / ____/___  ____ ___  ____  ____  ________  _____
 / /   / __ \/ __ `__ \/ __ \/ __ \/ ___/ _ \/ ___/
/ /___/ /_/ / / / / / / /_/ / /_/ (__  )  __/ /
\____/\____/_/ /_/ /_/ .___/\____/____/\___/_/
                    /_/
Composer version 2.5.8 2023-06-09 17:13:21

Usage:
  command [options] [arguments]
  ...
```

> Remarque : Sur Windows, la commande est ```composer``` mais sur Linux ou Mac la commande est ```php composer.phar```

Pour mettre à jour votre version de composer :
```
composer self-update
```

# 3. Utilisation succinte de composer
tuto de Grafikart ["Composer"](https://www.grafikart.fr/tutoriels/composer-480)