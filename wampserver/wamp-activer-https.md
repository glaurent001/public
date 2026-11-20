# Activer HTTPS sur Wampserver

> * Auteur : Gwénaël LAURENT
> * Date : 29/03/2022
> * Wampserver v3.1.9
> * Apache v2.4.39

![CC-BY-NC-SA](../img/cc-by-nc-sa-150.png) [Licence Creative Commons](https://creativecommons.org/licenses/by-nc-sa/3.0/fr/)

- [Activer HTTPS sur Wampserver](#activer-https-sur-wampserver)
- [1. Introduction](#1-introduction)
- [2. Openssl dans le path](#2-openssl-dans-le-path)
- [3. Copie de sauvegarde des fichiers de configuration](#3-copie-de-sauvegarde-des-fichiers-de-configuration)
- [4.Création d'un virtualhost en HTTP](#4création-dun-virtualhost-en-http)
- [5. Configuration principale d'Apache dans httpd.conf](#5-configuration-principale-dapache-dans-httpdconf)
- [6. Ajout du support HTTPS dans httpd-ssl.conf](#6-ajout-du-support-https-dans-httpd-sslconf)
- [7. Paramétrage ds certificats dans openssl.cnf](#7-paramétrage-ds-certificats-dans-opensslcnf)
- [8. Génération des certificats et des clés de cryptage](#8-génération-des-certificats-et-des-clés-de-cryptage)
- [9. Démarrer Wampserver](#9-démarrer-wampserver)
- [10. Configurer les navigateurs pour les certificats auto-signés](#10-configurer-les-navigateurs-pour-les-certificats-auto-signés)
- [11. Configuration de PHP pour HTTPS](#11-configuration-de-php-pour-https)
- [12. Forcer HTTPS pour un virtualhost](#12-forcer-https-pour-un-virtualhost)

# 1. Introduction
> Ce tuto est une retranscription :
> 
> * du forum de WampServer : http://forum.wampserver.com/read.php?1,119444,159026#msg-159026
> * du site : https://www.jcz.fr/certificats/

L'idée est de créer un virtualhost valide sur le port 80 et de lui ajouter l'accès en HTTPS sur le port 443.

Il faudra créer un **certificat SSL auto-signé** en identifiant votre organisation. Dans cet exemple, l'organisation est "Otomatic & Cie", organisation fictive chère à Wampserver.

Les navigateurs web utilisent des sites de confiance pour vérifier l'authenticité des certificats. Ici, nous sommes en phase de développement, notre certificat ne sera pas approuvé sur internet mais fonctionnera sur notre machine de dév.


# 2. Openssl dans le path
> OpenSSL est une boîte à outils de chiffrement comportant deux bibliothèques, libcrypto et libssl, fournissant respectivement une implémentation des algorithmes cryptographiques et du protocole de communication SSL/TLS, ainsi qu'une interface en ligne de commande, openssl. [Wikipédia](https://fr.wikipedia.org/wiki/OpenSSL)

Il faut avoir installé **openssl.exe** sur l'ordinateur. C'est le cas si vous avez installé GIT pour windows (dans ce cas il est dans``` C:\Program Files\Git\usr\bin\```).

> Si openssl n'est pas dispo sur votre ordinateur, vous pouvez télécharger et installer la version Windows à cette adresse : [Win64 OpenSSL](http://slproweb.com/products/Win32OpenSSL.html)

Il faut ajouter C:\Program Files\Git\usr\bin\ dans le path pour que les commandes openssl fonctionnent
* Touche windows > Recherchez "variables" > sélectionnez "Modifier les variables d'environnement système"
* Variables d'environnement > Variables systèmes > sélectionnez "Path" > Modifier > Nouveau : "C:\Program Files\Git\usr\bin" > OK

Ouvrez une nouvelle invite de commande, la commande suivante devrait renvoyer le numéro de version :
```cmd
openssl version
```

# 3. Copie de sauvegarde des fichiers de configuration
Pour pouvoir revenir en arrière en cas de problème, faites une copie des fichiers :
```
C:\wamp64\bin\apache\apache2.4.39\conf\httpd.conf
C:\wamp64\bin\apache\apache2.4.39\conf\openssl.cnf
C:\wamp64\bin\apache\apache2.4.39\conf\extra\httpd-ssl.conf
```

# 4.Création d'un virtualhost en HTTP
> L'idée est de créer un virtualhost valide sur le port 80. Dans la suite du tuto, on lui ajoutera l'accès HTTPS sur le port 443

* Nom du virtualHost : **securevh.local**
* Dossier : **I:/secure-virtualhost/**
* URL d'accès : **http://securevh.local/**

Créez un fichier index.html dans le dossier du virtualhost et vérifiez que le virtualhost est bien fonctionnel à l'adresse : http://securevh/

# 5. Configuration principale d'Apache dans httpd.conf
> Pour modifier la configuration d'Apache, il faut absolument **arrêter Wampserver**

Editez le fichier de configuration d'apache ```C:\wamp64\bin\apache\apache2.4.39\conf\httpd.conf```

**Charger les modules SSL :**

Décommentez (*en enlevant le # en début de ligne*) les lignes 197 et 199 pour que Apache charge automatiquement les 2 modules
```conf
LoadModule socache_shmcb_module modules/mod_socache_shmcb.so
LoadModule ssl_module modules/mod_ssl.so
```

**Prise en compte du fichier de config httpd-ssl.conf :**

Décommentez la ligne suivante (vers la fin de fichier, ligne 564)
```conf
Include conf/extra/httpd-ssl.conf
```
# 6. Ajout du support HTTPS dans httpd-ssl.conf 
Remplacez tout le contenu du fichier ```C:\wamp64\bin\apache\apache2.4.39\conf\extra\httpd-ssl.conf``` par ce qui suit.

Attention : Modifiez toutes les références à "MYSITE_" pour correspondre à votre virtualhost (lignes 29, 30 et 31)
* Define SERVERNAMEVHOSTSSL securevh.local
* Define DOCUMENTROOTVHOSTSSL I:\secure-virtualhost
* Define ADMINVHOSTSSL wampserver@otomatic.net

```conf
#
# This is the Apache server configuration file providing SSL support.
# When we also provide SSL we have to listen to the
# standard HTTP port and to the HTTPS port
#
Listen 0.0.0.0:443 https
Listen [::0]:443 https

# Where the certificates are
Define CERTIFS ${INSTALL_DIR}/bin/Certs

Protocols h2 h2c http/1.1

SSLSessionCache shmcb:${INSTALL_DIR}/tmp/ssl_gcache_data(512000)
SSLOptions +StrictRequire +StdEnvVars -ExportCertData
# SSL Protocol support:
SSLProtocol -all +TLSv1.2 +TLSv1.3
SSLCompression Off
SSLHonorCipherOrder On
# SSL Cipher Suite:
SSLCipherSuite SSL ECDHE-ECDSA-CHACHA20-POLY1305:ECDHE-ECDSA-AES256-GCM-SHA384:ECDHE-RSA-CHACHA20-POLY1305:ECDHE-RSA-AES256-GCM-SHA384
# Encryptions TLSv1.3
SSLCipherSuite TLSv1.3 TLS_CHACHA20_POLY1305_SHA256:TLS_AES_256_GCM_SHA384
SSLOpenSSLConfCmd ECDHParameters secp521r1
SSLOpenSSLConfCmd Curves sect571r1:sect571k1:secp521r1:sect409k1:sect409r1:secp384r1

##
## SSL Virtual Host Context
Define SERVERNAMEVHOSTSSL MYSITE_ServerName
Define DOCUMENTROOTVHOSTSSL MYSITE_DocumentRoot
Define ADMINVHOSTSSL MYSITE_email
<VirtualHost *:443>
	ServerName ${SERVERNAMEVHOSTSSL}
  DocumentRoot "${DOCUMENTROOTVHOSTSSL}"
  ServerAdmin ${ADMINVHOSTSSL}
	SSLEngine on
	SSLCertificateFile      "${CERTIFS}/Site/${SERVERNAMEVHOSTSSL}.crt"
	SSLCertificateKeyFile   "${CERTIFS}/Site/${SERVERNAMEVHOSTSSL}.key"
	<Directory "${DOCUMENTROOTVHOSTSSL}/">
		Options +Indexes +Includes +FollowSymLinks +MultiViews
		AllowOverride all
		Require local
	</Directory>
	CustomLog "${INSTALL_DIR}/logs/custom.log" "%t %h %{SSL_PROTOCOL}x %{SSL_CIPHER}x \"%r\" %b"
</VirtualHost>
# End of SSL Virtual Host Context - To be repeated for another SSL VirtualHost

# Do not remove these lines UnDefine
UnDefine SERVERNAMEVHOSTSSL
UnDefine DOCUMENTROOTVHOSTSSL
UnDefine ADMINVHOSTSSL
```

# 7. Paramétrage ds certificats dans openssl.cnf
Remplacez tout le contenu du fichier ```C:\wamp64\bin\apache\apache2.4.39\conf\openssl.cnf``` par ce qui suit.

```conf
#============ openssl.cnf =============#
[ca]
default_ca       = CA_default

[CA_default]
dir              = ../../../Certs
cacerts_dir      = $dir/Cacerts
certificate      = $cacerts_dir/Certificat.crt
new_certs_dir    = $dir/Newcerts
private_dir      = $cacerts_dir
private_key      = $private_dir/Certificat.key
RANDFILE         = $private_dir/Certificat.rnd
other_dir        = $dir/Other
database         = $other_dir/index.txt
serial           = $other_dir/serial.txt
default_crl_days = 14610
default_days     = 14610
default_md       = sha512
x509_extensions  = usr_cert
name_opt         = ca_default
cert_opt         = ca_default
preserve         = no
policy           = policy_match

[policy_match]
countryName            = match
stateOrProvinceName    = match
localityName           = match
organizationName       = optional
organizationalUnitName = optional
commonName             = supplied
emailAddress           = optional

[usr_cert]
basicConstraints       = CA:FALSE
nsCertType             = client
keyUsage               = nonRepudiation, digitalSignature, keyEncipherment
nsComment              = "OpenSSL Generated Certificate"
subjectKeyIdentifier   = hash
authorityKeyIdentifier = keyid,issuer

[ocsp]
basicConstraints       = CA:FALSE
subjectKeyIdentifier   = hash
authorityKeyIdentifier = keyid,issuer
keyUsage               = critical, digitalSignature
extendedKeyUsage       = critical, OCSPSigning

[req]
default_bits        = 4096
default_keyfile     = ../../../Certs/Cacerts/Certificat.pem
encrypt_key         = no
default_md          = sha512
string_mask         = utf8only
prompt              = no
utf8                = yes
distinguished_name  = req_distinguished_name
req_extensions      = v3_req
x509_extensions     = v3_ca

[req_distinguished_name]
countryName_default            = FR
stateOrProvinceName_default    = Paris
localityName_default           = Paris
0.organizationName_default     = Otomatic & Cie
organizationalUnitName_default = Wampserver
commonName                     = Common Name (eg, your website’s domain name)
commonName_max                 = 64
emailAddress_default           = otomatic@otomatic.net
emailAddress_max               = 40

[v3_req]
basicConstraints = CA:FALSE
keyUsage         = nonRepudiation, digitalSignature, keyEncipherment

[v3_ca]
# Extensions to use when signing a CA
basicConstraints       = critical, CA:true
keyUsage               = keyCertSign, cRLSign
nsCertType             = sslCA, emailCA
nsComment              = "SSL ROOT CA"
subjectKeyIdentifier   = hash
authorityKeyIdentifier = keyid:always,issuer:always
subjectAltName         = @alt_names

[alt_names]
DNS.1 = IP:127.0.0.1
DNS.2 = localhost
```



# 8. Génération des certificats et des clés de cryptage
Lancer les commandes suivantes dans terminal lancé en administrateur :
* Touches windows > Saisissez "invite"
* Pour "Invite de commandes", cliquez sur "Exécuter en tant qu'administrateur"

> **Attention** : Il ne faut jamais fermer la fenêtre de commande avant la fin complète de la procédure, sinon les variables d'environnement déclarées au début par set seraient perdues.

Création des dossiers pour le futur certificat dans ```C:\wamp64\bin\Certs``` :
```cmd
Rem Variables d'installation de Wampserver
Rem À modifier suivant votre installation
set installdir=c:\wamp64
set apachever=2.4.39
Rem
Rem Vérification et création éventuelle des dossiers
cd /D %installdir%\bin
Rem Suppression des certificats éventuellement présents
if exist Certs rmdir /S /Q Certs
if not exist Certs md Certs
cd Certs
if not exist Other md Other
if not exist Cacerts md Cacerts
if not exist Server md Server
if not exist Site md Site
Rem Informations à créer
copy nul .\Other\Index.txt
@echo 01> .\Other\Serial.txt
Rem MyPass peut être remplacé par votre propre mot de passe (4 à 20 caractères)
@echo MyPass> .\Other\Password.txt
set /P PASSWORD= <.\Other\Password.txt
Rem
cd..

```
Puis création du certificat avec openssl dans ```C:\wamp64\bin\Certs\Cacerts``` :
```cmd
Rem
Rem On est dans le dossier %installdir%\bin
Rem On va dans apache utilisé/bin
cd apache\apache%apachever%\bin
Rem Déclaration des variables - Impératif
set OPENSSL_CONF=%installdir%\bin\apache\apache%apachever%\conf\openssl.cnf
set DIRCERTS=%installdir%\bin\Certs
Rem +-+-+-+-+ Création du certificat auto-signé +-+-+-+-+
Rem 1- Génération d'un nombre aléatoire. (La graîne 1358 peut être remplacée)
openssl rand -out %DIRCERTS%/Cacerts/Certificat.rnd -base64 1358
Rem 2- Clé RSA privée.
openssl genrsa -out %DIRCERTS%/Cacerts/Certificat.key -rand %DIRCERTS%/Cacerts/Certificat.rnd 4096
Rem 3- Demande de signature.
Rem /C=FR : Pays -- /ST=Paris : État ou région -- /L=Paris : Ville
Rem /O=Otomatic & Cie : Organisation -- /CN=Otomatic & Cie : Division
openssl req -new -sha256 -key %DIRCERTS%/Cacerts/Certificat.key -out %DIRCERTS%/Cacerts/Certificat.csr -subj "/C=FR/ST=Paris/L=Paris/O=Otomatic & Cie/CN=Otomatic & Cie"
Rem 4- Certificat auto-signé.
openssl x509 -req -days 1830 -sha256 -in %DIRCERTS%/Cacerts/Certificat.csr -signkey %DIRCERTS%/Cacerts/Certificat.key -out %DIRCERTS%/Cacerts/Certificat.crt
openssl x509 -in %DIRCERTS%/Cacerts/Certificat.crt -outform der -out %DIRCERTS%/Cacerts/Certificat.der
openssl x509 -in %DIRCERTS%/Cacerts/Certificat.crt -outform pem -out %DIRCERTS%/Cacerts/Certificat.pem
Rem 5- Extraction clé publique Plaintext Block Chaining
openssl rsa -in %DIRCERTS%/Cacerts/Certificat.key -pubout -out %DIRCERTS%/Cacerts/Certificat.pbc
Rem +-+-+-+-+ Fin de la création du certificat auto-signé +-+-+-+-+

```
On associe enfin le certificat  et les clés à notre virtualhost dans ```C:\wamp64\bin\Certs\Server``` et ```C:\wamp64\bin\Certs\Site``` :

**Attention** : 
* Juste après le "Rem6", adaptez le nom de votre virtualhost
* Juste après "Rem11", vous pouvez moditifier le mot de passe par défaut du certificat client qui est "MyPass"

```cmd
Rem +-+-+-+-+ Certificats et clés serveur pour un site local +-+-+-+-+
Rem 6- ServerName du site local pour lequel on veut les clés
set SERVLOCAL=securevh.local
Rem 7- Nombre aléatoire (Graîne différente)
if exist %DIRCERTS%\Server\Server.rnd del %DIRCERTS%\Server\Server.rnd
openssl rand -out %DIRCERTS%/Server/Server.rnd -base64 1677
Rem 8- Clé RSA privée.
if exist %DIRCERTS%\Server\Server.key del %DIRCERTS%\Server\Server.key
openssl genrsa -out %DIRCERTS%\Server\Server.key -rand %DIRCERTS%\Server\Server.rnd 4096
Rem 9- Demande de signature pour certificat
Rem /C=FR : Pays -- /ST=Paris : État ou région -- /L=Paris : Ville
Rem /O=Otomatic & Cie : Organisation -- /CN=nom du site local
if exist %DIRCERTS%\Server\Server.csr del %DIRCERTS%\Server\Server.csr
openssl req -new -sha256 -key %DIRCERTS%/Server/Server.key -out %DIRCERTS%/Server/Server.csr -subj "/C=FR/ST=Paris/L=Paris/O=Otomatic & Cie/OU=Wampserver/CN=%SERVLOCAL%"
Rem 10- Demande de signature pour certificat serveur.
if exist %DIRCERTS%\Server\Server.crt del %DIRCERTS%\Server\Server.crt
openssl x509 -req -days 4383 -sha256 -in %DIRCERTS%/Server/Server.csr -CA %DIRCERTS%/Cacerts/Certificat.crt -CAkey %DIRCERTS%/Cacerts/Certificat.key -CAcreateserial -out %DIRCERTS%/Server/Server.crt
openssl x509 -outform der -in %DIRCERTS%/Server/Server.crt -out %DIRCERTS%/Server/Server.der
openssl x509 -inform DER -outform PEM -in %DIRCERTS%/Server/Server.der -out %DIRCERTS%/Server/Server.pem
openssl crl2pkcs7 -nocrl -certfile %DIRCERTS%/Cacerts/Certificat.crt -certfile %DIRCERTS%/Server/Server.crt -out %DIRCERTS%/Server/%SERVLOCAL%.p7b
if exist %DIRCERTS%\Server\%SERVLOCAL%.pfx del %DIRCERTS%\Server\%SERVLOCAL%.pfx
openssl pkcs12 -export -nodes -in %DIRCERTS%/Cacerts/Certificat.crt -inkey %DIRCERTS%/Server/Server.key-out %DIRCERTS%/Server/%SERVLOCAL%.pfx -descert -name "%SERVLOCAL%" -password pass:%PASSWORD%
Rem
Rem 11- Certificat client.
Rem Nota : Un mot de passe sera demandé sauf si option finale -password pass:MyPass
openssl pkcs12 -nodes -export -in %DIRCERTS%/Server/Server.crt -inkey %DIRCERTS%/Server/Server.key -out %DIRCERTS%/Site/%SERVLOCAL%.pfx -clcerts -descert -name "Client %SERVLOCAL% Certificate" -password pass:%PASSWORD%
Rem 12- Copies des clés
copy /Y %DIRCERTS%\Server\Server.crt %DIRCERTS%\Site\%SERVLOCAL%.crt
copy /Y %DIRCERTS%\Server\Server.key %DIRCERTS%\Site\%SERVLOCAL%.key

```

# 9. Démarrer Wampserver
Vous pouvez lancer Wampserver et vérifier que tout va bien (icône verte).

Si éventuellement l'icône est rouge, utilisez l'outil de vérification de la syntaxe httpd.conf pour trouver les erreurs.

```cmd
C:\wamp64\bin\apache\apache2.4.39\bin\httpd -t
```

Le virtaulhost doit maintenant être accessible aux adresses suivantes :
* http://securevh.local/
* https://securevh.local/ => avec un message d'alerte "Votre connexion n'est pas privée" > Paramètres avancés > Continuer vers le site securevh.local (dangereux)

Le navigateur indique que le certificat n'est pas valide. Normal, c'est un certificat auto-signé.

# 10. Configurer les navigateurs pour les certificats auto-signés
> Le navigateur Firefox est le seul qui gère lui-même les certificats, les autres utilisant les certificats de Windows.\
> Et c'est aussi le seul qui prend bien en compte les certificats auto-signés avec comme informations sur un site local https :
> * Connexion sécurisé
> * Connexion vérifiée par un émetteur de certificat non reconnu par Mozilla
> 
> Les autres navigateurs crient "au scandale" mais permettent d'accéder au site :
> * Chrome barrant en rouge https et déclarant le site non sécurisé


Sur la machine cliente du serveur web (là où on utilise le navigateur), on peut retirer le message "Votre connexion n'est pas privée" en ajoutant le certificat aux certificats de confiance.

**Certicat racine**

Pour Chrome ou Edge, il faut lancer la console Windows d'administration des certificats "certmgr.msc" :
* Clic-Droit sur "Autorités de certification racine de confiance" -> Toutes les tâches -> Importer -> Parcourir
* Sélectionnez ```C:\wamp64\bin\Certs\Cacerts\Certificat.crt```

Pour Firefox :
* Paramètres -> Vie privée et sécurité
* Certificats -> Afficher les certificats.
* Magasin "Autorités" puis Importer : ```C:\wamp64\bin\Certs\Cacerts\Certificat.crt```
* Confirmer cette AC pour identifier des sites web > OK

**certificat client ou Site avec le suffixe .pfx ou .p12**

Il contient le certificat, son intermédiaire et la clé privée.

Pour Chrome ou Edge, il faut lancer la console Windows d'administration des certificats "certmgr.msc" :
* Clic-Droit sur "Personnel" -> Toutes les tâches -> Importer -> Parcourir
* Sélectionnez ```C:\wamp64\bin\Certs\Site\securevh.local.crt```

Pour Firefox :
* Paramètres -> Vie privée et sécurité
* Certificats -> Afficher les certificats.
* Magasin "Vos certificats" puis Importer : ```C:\wamp64\bin\Certs\Site\securevh.local.pfx```
* Mot de passe : MyPass

# 11. Configuration de PHP pour HTTPS
Editer C:\wamp64\bin\php\php7.3.5\php.ini
Vérifiez que la ligne suivante (l 927) est bien décommentée (enlever le ; en début de ligne)
```
extension=openssl
```

# 12. Forcer HTTPS pour un virtualhost
Pour forcer un VirtualHost à être lancé en https, il suffit de rajouter les directives de réécriture dans sa structure <VirtualHost *:80> dans le fichier ```C:\wamp64\bin\apache\apache2.4.39\conf\extra\httpd-vhosts.conf```.

> Les 3 lignes à ajouter commencent par "Rewrite"

```conf
<VirtualHost *:80>
	ServerName securevh.local
	RewriteEngine On
	RewriteCond %{HTTPS} !=on
	RewriteRule ^ https://%{HTTP_HOST}%{REQUEST_URI} [L,R=301]
	DocumentRoot "i:/secure-virtualhost"
	<Directory  "i:/secure-virtualhost/">
		Options +Indexes +Includes +FollowSymLinks +MultiViews
		AllowOverride All
		Require local
	</Directory>
</VirtualHost>
```

Redémarrer les services de Wampserver pour que la modification soit prise en compte