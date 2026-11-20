# Résumé de la configuration de VScode en BTS CIEL

> * Auteur : Gwénaël LAURENT
> * Date : 13/09/2024
> * OS : Windows 10
> * VScode : version 1.90.2

# 1. Logiciels à installer
* Microsoft Visual Studio Code (VScode)
* NodeJS

cf [Installation de VScode](vscode-install.md)

# 2. Extensions VScode à installer

> Attention : certaines extensions nécessite d'installer des logiciels supplémentaires sur le PC

**Liste des extensions :**
* Auto Rename Tag (Jun Han)
* Black Formatter (Microsoft)
* C/C++ (Microsoft) + [install compilateur](vscode-cpp.md)
* C++ Helper (amir)
* ESLint (Microsoft) + [install serveur eslint et config](vscode-js.md)
* Excel to Markdown table (Sebastian Holmqvist)
* HTML to CSS autocompletion (solnurkarim)
* HTMLHint (HTMLHin)
* IBGenerator (ProfesseurIssou)
* Insert Unicode (brunnerh)
* Jupyter (Microsoft) - pack comprenant : 
  * Jupyter (Microsoft)
  * Jupyter Cell Tags (Microsoft)
  * Jupyter Keymap (Microsoft)
  * Jupyter Notebook Renderers (Microsoft)
  * Jupyter Slide Show (Microsoft)
* Live Server (Ritwick Dey)
* Markdown All in One (Yu Zhang)
* Markdown PDF (yzane)
* Material Icon Theme (Philipp Kief)
* PHP Debug (Xdebug) + [install PHP](vscode-php.md)
* PHP Intelephense (Ben Mewburn) + [config](vscode-php.md)
* PlatformIO IDE (PlatformIO) + [install des plateformes](vscode-platformio.md)
* Prettier - Code formatter (Prettier)
* Python (Microsoft) - pack comprenant : + [install interpréteur](vscode-python.md)
  * Python (Microsoft)
  * Pylance (Microsoft)
  * Python Debugger (Microsoft)
* Pylint (Microsoft)
* Remote Development (Microsoft) - pack comprenant : 
  * Dev Containers, 
  * Remote SSH, 
  * Remote - SSH: Editing Configuration Files, 
  * Remote - Tunnels,
  * Remote Development (Microsoft)
  * Remote Explorer,
  * WSL
* Surround (Mehmet Yatkı)
* VSMqtt (rpdswtk)


**Script d'installation de toutes les extensions :**

Vous pouvez installer toutes les extensions citées précédemment en ligne de commande.\
Après avoir installé VScode, ouvrez un terminal `cmd` et exécutez :
```cmd
code --install-extension amiralizadeh9480.cpp-helper --force
code --install-extension bmewburn.vscode-intelephense-client --force
code --install-extension brunnerh.insert-unicode --force
code --install-extension csholmq.excel-to-markdown-table --force
code --install-extension dbaeumer.vscode-eslint --force
code --install-extension esbenp.prettier-vscode --force
code --install-extension formulahendry.auto-rename-tag --force
code --install-extension htmlhint.vscode-htmlhint --force
code --install-extension ms-python.debugpy --force
code --install-extension ms-python.pylint --force
code --install-extension ms-python.python --force
code --install-extension ms-python.vscode-pylance --force
code --install-extension ms-python.black-formatter
code --install-extension ms-toolsai.jupyter --force
code --install-extension ms-toolsai.jupyter-keymap --force
code --install-extension ms-toolsai.jupyter-renderers --force
code --install-extension ms-toolsai.vscode-jupyter-cell-tags --force
code --install-extension ms-toolsai.vscode-jupyter-slideshow --force
code --install-extension ms-vscode-remote.remote-containers --force
code --install-extension ms-vscode-remote.remote-ssh --force
code --install-extension ms-vscode-remote.remote-ssh-edit --force
code --install-extension ms-vscode-remote.remote-wsl --force
code --install-extension ms-vscode-remote.vscode-remote-extensionpack --force
code --install-extension ms-vscode.cpptools --force
code --install-extension ms-vscode.hexeditor --force
code --install-extension ms-vscode.remote-explorer --force
code --install-extension ms-vscode.remote-server --force
code --install-extension pkief.material-icon-theme --force
code --install-extension platformio.platformio-ide --force
code --install-extension professeurissou.ibgenerator --force
code --install-extension ritwickdey.liveserver --force
code --install-extension rpdswtk.vsmqtt --force
code --install-extension solnurkarim.html-to-css-autocompletion --force
code --install-extension xdebug.php-debug --force
code --install-extension yatki.vscode-surround --force
code --install-extension yzane.markdown-pdf --force
code --install-extension yzhang.markdown-all-in-one --force
```
> Remarque : Si l'extension est déjà installée, elle sera automatiquement mise à jour si besoin.

> Remarque : Pour lister les extensions installées sur votre machine, vous pouvez utiliser la commande ```code --list-extensions```
<!-- 
```
code --list-extensions
```
```
code --install-extension amiralizadeh9480.cpp-helper --force
code --install-extension bmewburn.vscode-intelephense-client --force
code --install-extension brunnerh.insert-unicode --force
code --install-extension csholmq.excel-to-markdown-table --force
code --install-extension dbaeumer.vscode-eslint --force
code --install-extension esbenp.prettier-vscode --force
code --install-extension formulahendry.auto-rename-tag --force
code --install-extension htmlhint.vscode-htmlhint --force
	code --install-extension james-yu.latex-workshop --force
code --install-extension ms-python.debugpy --force
code --install-extension ms-python.pylint --force
code --install-extension ms-python.python --force
code --install-extension ms-python.vscode-pylance --force
code --install-extension ms-toolsai.jupyter --force
code --install-extension ms-toolsai.jupyter-keymap --force
code --install-extension ms-toolsai.jupyter-renderers --force
code --install-extension ms-toolsai.vscode-jupyter-cell-tags --force
code --install-extension ms-toolsai.vscode-jupyter-slideshow --force
code --install-extension ms-vscode-remote.remote-containers --force
code --install-extension ms-vscode-remote.remote-ssh --force
code --install-extension ms-vscode-remote.remote-ssh-edit --force
code --install-extension ms-vscode-remote.remote-wsl --force
code --install-extension ms-vscode-remote.vscode-remote-extensionpack --force
code --install-extension ms-vscode.cpptools --force
code --install-extension ms-vscode.hexeditor --force
code --install-extension ms-vscode.remote-explorer --force
code --install-extension ms-vscode.remote-server --force
code --install-extension pkief.material-icon-theme --force
code --install-extension platformio.platformio-ide --force
code --install-extension professeurissou.ibgenerator --force
code --install-extension ritwickdey.liveserver --force
code --install-extension rpdswtk.vsmqtt --force
	code --install-extension softheroes.jsobfuscator --force
code --install-extension solnurkarim.html-to-css-autocompletion --force
code --install-extension xdebug.php-debug --force
code --install-extension yatki.vscode-surround --force
code --install-extension yzane.markdown-pdf --force
code --install-extension yzhang.markdown-all-in-one --force
``` -->