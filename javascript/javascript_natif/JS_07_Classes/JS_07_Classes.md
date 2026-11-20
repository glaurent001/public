# Les classes en JavaScript

> * Auteur : Alain BRASSART
> * Date de publication : 27/04/2021
> * Mise à jour : 24/05/2023
> * OS: Windows 10 (version 22H2)
> * VS Code : version 1.78.1 (system setup)
> * Chrome : version 113.0.5672.93

![CC-BY-NC-SA](/img/cc-by-nc-sa-150.png) [Licence Creative Commons](https://creativecommons.org/licenses/by-nc-sa/3.0/fr/)

## Sommaire

  - [1. Introduction](#1-introduction)
  - [2. Quelques rappels sur les classes](#2-quelques-rappels-sur-les-classes)
  - [3. Déclaration  et instanciation d'une classe](#3-déclaration-et-instanciation-dune-classe)
    - [3.1 Déclaration d'une classe](#31-déclaration-dune-classe-)
    - [3.2 Instanciation, création d'un objet](#32-instanciation-création-dun-objet-)
  - [Activité \: codage d'une classe pour l'application de calcul de l'IMC](#activité-codage-dune-classe-pour-lapplication-de-calcul-de-limc)
  - [4. Classes dérivées et héritage](#4-classes-dérivées-et-héritage)
  - [Activité \: implémentation de l'héritage par classes pour gérer les professeurs et les élèves](#activité-implémentation-de-lhéritage-par-classes-pour-gérer-les-professeurs-et-les-élèves)
  - [Références MDN](#références-mdn)
  - [Exercice](#exercice)


## 1. Introduction

Les classes ont été introduites récemment en JavaScript (avec ECMAScript 2015) pour fournir une syntaxe plus simple pour créer des objets et manipuler l'héritage. En réalité l'objectif était de masquer l'héritage prototypal du langage pour les développeurs habitués aux langages objets basés sur les classes.

Il faut bien comprendre que malgré cette évolution, le JavaScript reste un langage objet basé sur les prototypes et que toute classe est convertie au final en un objet prototype.

## 2. Quelques rappels sur les classes

Une classe est une entité qui va servir à créer des objets de même type. Elle va généralement être composée de propriétés (on parle aussi d'attributs dans d'autres langages) et de méthodes dont vont hériter les objets qui seront créés à partir de celle-ci.

Une classe va également posséder un constructeur qui sera appelé systématiquement lors de la création d'un objet pour permettre notamment d'initialiser les propriétés de cet objet.

Dans les langages objet basés sur les classes :

* tous les objets sont créés en instanciant des classes

* une classe contient toutes les définitions des propriétés et des méthodes dont va disposer l'objet. La possibilité de rajouter ou de supprimer des membres à un objet n'existe pas.

* l'héritage se fait au niveau des classes, en définissant une classe mère et des classes filles qui seront des spécialisations (ou des extensions) de la classe mère.

## 3. Déclaration  et instanciation d'une classe 

### 3.1 Déclaration d'une classe :

Pour déclarer une classe en JavaScript, on utilise le mot clé ```class``` suivi du nom de la classe et d'une paire d'accolades.

Exemple : déclaration de la classe Personne

```javascript
class Personne {

}
```

On ajoute ensuite dans cette classe la méthode ```constructor()```. Cette méthode est reconnue par JavaScript comme étant le constructeur de la classe, elle servira notamment à créer les objets et à initialiser leurs propriétés grâce au passage de paramètres.

Exemple : codage du constructeur de la classe ```Personne```

```javascript
class Personne {
    constructor(prmNom, prmPrenom, prmAge) {
        this.nom = prmNom;
        this.prenom = prmPrenom;
        this.age = prmAge;
    }
}
```
> A noter que contrairement au cas des langage objet basés sur les classes (comme C++ ou Java), les propriétés ne sont pas définies à part comme des attributs mais directement dans le constructeur en utilisant le mot clé ```this``` pour désigner l'objet courant.

Il reste alors à ajouter les méthodes auxquelles les objets devront pouvoir avoir accés.

Exemple : ajout de la méthode ```decrire()``` dans la classe ```Personne```

```javascript
class Personne {
    constructor(prmNom, prmPrenom, prmAge) {
        this.nom = prmNom;
        this.prenom = prmPrenom;
        this.age = prmAge;
    }

    decrire() {
        let description;
        description = this.prenom + " " + this.nom + " est agé de " + this.age + " ans; 
        return description;
    }
}
```

### 3.2 Instanciation, création d'un objet :

Après avoir défini complétement la classe, on l'instancie pour créer un objet. Pour cela : 

* on déclare une variable à laquelle on affecte l'objet créé à partir de la classe

* on utilise le mot clé ```new``` suivi du nom de la classe pour faire l'instanciation

* on passe en paramètre les valeurs avec lesquelles les propriétés de l'objet seront initialisées.

Exemple : instanciation de la classe ```Personne```

```javascript
let objPersonne = new Personne('Dupond', 'Jean', 30);
```
A partir de cet instant, toutes les méthodes définies dans la classe sont accessibles pour l'objet qui a été créé à partir de cette classe.

Exemple : utilisation de la méthode ```decrire()``` avec l'objet ```objPersonne```

```javascript
console.log(objPersonne.decrire());
```

## Activité \: codage d'une classe pour l'application de calcul de l'IMC

Créer une nouvelle version de l'application de calcul d'IMC en utilisant une classe ```Patient``` pour créer les objets qui représentent un patient. Cette classe sera définie avec les mêmes propriétés et méthodes que celles définies pour les objets de la version précédente.

Tester la classe en créant 2 patients et en affichant pour chacun d'entr'eux :

* leur description
* leur IMC
* leur état de corpulence

conformément à l'exemple donné pour la version précédente.

## 4. Classes dérivées et héritage

Pour créer une classe dérivée qui va hériter des propriétés et des méthodes d'une autre classe, on doit utiliser le mot clé ```extends```

Exemple : création d'une classe ```Professeur``` qui hérite de la classe ```Personne```

```javascript
class Professeur extends Personne {

}
```
>Dans le cas de cet exemple, on dit que la classe ```Professeur``` est une classe dérivée de la classe ```Personne``` ou encore que la classe ```Personne``` est la classe mère de la classe ```Professeur```

Dans le constructeur de la classe dérivée, il faut utiliser le mot clé ```super``` pour appeler le constructeur de la classe mère.

Exemple : codage du constructeur de la classe ```Professeur```

```javascript
class Professeur extends Personne {
    constructor(prmNom, prmPrenom, prmAge, prmMatiere) {
        super(prmNom, prmPrenom, prmAge);  // appel du constructeur de la classe Personne
        this.matiere = prmMatiere;
    }
}
```
> Dans cet exemple, lorsqu'on créée un objet de la classe ```Professeur```, les propriétés ```nom```, ```prenom``` et ```age``` sont initialisés par le constructeur de la classe ```Personne```, la propriété ```matiere``` spécifique à la classe ```Professeur``` est initialisée directement par le constructeur de cette classe.

> **Attention :** ```super()``` doit être utilisé avant le mot clé ```this```

## Activité \: implémentation de l'héritage par classes pour gérer les professeurs et les élèves

Créer une nouvelle version de l'application qui permet de créer des objets représentant des professeurs ou des élèves en utilisant l'héritage par classe. 

* nom du dossier racine : **Heritage_Classe**
* nom du fichier js : **heritage_classe.js**  

Pour cette version, on implémentera :

* la classe ```Professeur``` à partir de laquelle seront créés les objets représentant les professeurs

* la classe ```Eleve``` à partir de laquelle seront créés les objets représentant les élèves

Ces deux classes seront dérivées de la classe ```Personne``` qui sera chargée d'initialiser les propriétés communes aux professeurs et aux élèves.

Coder les instructions javascript qui permettent de définir :

* la classe ```Personne``` telle qu'elle a été définie dans le cours

* la classe ```Professeur``` en reprenant l'exemple du cours et en ajoutant la méthode ```decrire_plus()``` telle qu'elle a été implémentée dans la version précédente (cf. héritage par prototype)

* la classe ```Eleve``` selon les mêmes modalités que la classe ```Professeur```

Ajouter les instructions qui permettent de créer un objet de chaque type (```Professeur``` et ```Eleve```) à partir de ces classes et de tester les méthodes ```decrire()``` et ```decrire_plus()``` sur chacun de ces objets.

## Références MDN

* Les classes en JavaScript :<br>
<https://developer.mozilla.org/fr/docs/Web/JavaScript/Reference/Classes>

## Exercice

Dans cet exercice, il s'agit de reprendre l'application vue dans le chapitre sur les objets et qui permet de créer des objets représentant les personnages d'un jeu. L'objectif sera d'en faire une nouvelle version dans laquelle ces objets seront créés en utilisant les classes.

Créer un nouveau projet correspondant à cette nouvelle version et coder les instructions qui permettent de: 

* définir correctement les classes nécessaires à la création des personnages
* créer des objets représentant un personnage de chaque catégorie 
* tester les méthodes associées à chacun de ces objets 

