# Ressources pour Raspberry

> * Auteur : Gwénaël LAURENT
> * Date : 06/10/2021


![CC-BY-NC-SA](../img/cc-by-nc-sa-150.png) [Licence Creative Commons](https://creativecommons.org/licenses/by-nc-sa/3.0/fr/)


* [Dév. C++ à distance sur Raspberry](../vscode/vscode-remote.md)
* [Installer le broker MQTT mosquitto](../linux/5.installer_broker_mqtt_mosquitto.md)
* [Installation de LAMP sur Linux (distribution Debian Buster)](../linux/1.installer_ubuntu_20.04.2_Desktop.md)


Vérifier si NodeJS est déjà installé
```sh
node -v
```

S'il n'est pas installé, vous pouvez l'installer avec
```sh
sudo apt update
sudo apt upgrade

sudo apt install nodejs
sudo apt install npm
```

<!-- Il faut ensuite forcer la mise à jour de NodeJS :
```sh
sudo npm install -g n
sudo n lts
``` -->

Il faut ensuite forcer la mise à jour de NodeJS grâce à l'utilitaire **`nvm`**.

Installer la dernière version de nvm (nvm allows you to quickly install and use different versions of node via the command line. cf. https://github.com/nvm-sh/nvm)

```sh
curl -o- https://raw.githubusercontent.com/nvm-sh/nvm/v0.40.1/install.sh | bash
```

Redémarrer le terminal (exit puis login)

Installer la version 22 de NodeJS :
```sh
nvm install 22
```
<!-- 
# Avec la doc officielle de node

https://github.com/nodesource/distributions/blob/master/README.md

Node.js LTS (v22.x): > Using Debian, as root (N|Solid or Node.js LTS)

```sh
apt-get install -y curl
curl -fsSL https://deb.nodesource.com/setup_lts.x -o nodesource_setup.sh

en sudo
bash nodesource_setup.sh
``` -->
