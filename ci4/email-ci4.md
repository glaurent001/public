# Envoyer des mails avec CI4 et gmail

> * Auteur : Gwénaël LAURENT
> * Date : 21/02/2024
> * CodeIgniter : 4.4.6
> * PHP : 8.0.26
> * MySQL : 8.0.21


Doc CI4 : 
* https://www.codeigniter.com/user_guide/libraries/email.html

Doc pour gmail : 
* https://monayemislam.medium.com/how-to-send-an-email-via-gmail-smtp-server-using-codeigniter-4-fe7e0689a2d1
* https://www.youtube.com/watch?v=RhbRedtMlto

# 1. Paramétrer le compte gmail pour envoyer à partir de CI4
Créer un compte gmail pour envoyer des emails à partir de CI4 (cet email apparaitra comme expéditeur des messages)

Pour utiliser une adresse gmail à partir d'une application il faut :
* activer la validation en deux étapes
* créer et utiliser un mot de passe d'application (Le mot de passe d'application sera utilisé pour envoyer les mails)

Procédure :
1. Créer un compte gmail pour votre appli web
2. Dans chrome, logguez vous avec votre nouveau compte gmail
3. Allez sur la page de gmail
4. Clic sur votre icone de profil > Gérer votre compte google > Sécurité >
5. Validation en deux étapes > votre n° de téléphone > Text message > Vérif > Turn ON
6. Sécurité > Validation en deux étapes > Mots de passe des applications
7. Nom de l'appli = "xxxx" > notez le mot de passe de 16 caractères

# 2. Configurer l'envoi d'email dans CI4
Doc : [Envoyer des e-mails avec le serveur SMTP Gmail](https://support.google.com/a/answer/176600?hl=fr)

Configuration du serveur SMTP Gmail :
* serveur SMTP : smtp.gmail.com
* Ports : SSL 465 ou TLS 587

> La limite d'envoi est de 2 000 messages par jour

Modifiez /app/Config/Email.php
```php
public string $fromEmail  = 'votre-email@gmail.com'; // email d'envoi
public string $fromName   = 'Appli CI4'; // nom de l'appli
public string $protocol = 'smtp';
public string $SMTPHost = 'smtp.gmail.com';
public string $SMTPUser = 'votre-email@gmail.com'; // email d'envoi
public string $SMTPPass = 'mot-de-passe-application'; // 16 caractères
public int $SMTPPort = 587;
public int $SMTPTimeout = 60;
public string $SMTPCrypto = 'tls';
public string $mailType = 'text'; // ou html

``` 
On peut aussi envoyer en utilisant SSL :
```php
public int $SMTPPort = 465;
public string $SMTPCrypto = 'ssl';
```

# 3. Envoi d'email
Code PHP pour envoyer un mail (dans une vue ou un controleur) :
```php
$destinataire = "adresse@email.com"; // adresse du destinataire
$objet = "Envoi depuis ci4-auth"; // Objet du mail
$message = "Bravo, ça marche !"; // Message du mail

$email = \Config\Services::email();

$email->setTo($destinataire);
// $email->setFrom("example-name@gmail.com", "Mail Testing"); //set From
$email->setSubject($objet);
$email->setMessage($message);
if ($email->send()) {
    echo "Email has been Sent.";
} else {
    echo "Something went wrong !";
}
```

on peut paramétrer l'adresse de réponse (quand le destinataire répond au mail) avant d'appeler $email->send() :
```php
$email->setFrom("example-name@gmail.com", "Nom");
```
