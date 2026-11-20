(_Cours CSS : [retour sommaire](readme.md#32-cours-avec-exercices)_)
# Cours CSS 5 : Modification du flux normal avec ```float```

> * Auteur : Gwénaël LAURENT
> * Date : 15/09/2021
> * OS : Windows 10 (version 20H2)
> * VScode : version 1.60.0 (system setup)
> * Chrome : version 93.0

- [Cours CSS 5 : Modification du flux normal avec ```float```](#cours-css-5--modification-du-flux-normal-avec-float)
- [1. Les boîtes flottantes](#1-les-boîtes-flottantes)
  - [1.1 Utilité](#11-utilité)
  - [1.2 Utilisation pour faire flotter une image](#12-utilisation-pour-faire-flotter-une-image)
  - [1.3 Dégagement des boîtes flottantes](#13-dégagement-des-boîtes-flottantes)
  - [1.4 Dégagement des boîtes flottantes : cas d'une boîte enveloppante](#14-dégagement-des-boîtes-flottantes--cas-dune-boîte-enveloppante)


# 1. Les boîtes flottantes
## 1.1 Utilité
La propriété float a été introduite pour permettre aux développeurs web d'implémenter des dispositions simples comme une image flottant dans une colonne de texte, le texte se développant autour de cette image sur la gauche ou sur la droite. 

> **L'utilisation des boîtes flottantes pour créer des mises en page complètes avec plusieurs colonnes doit être considérée comme une technique du passé**

## 1.2 Utilisation pour faire flotter une image
Commençons par l'affichage de l'image dans le flux normal.

Code HTML :
```html
<h1>Exemple simple de boîte flottante</h1>

<img class="box" src="https://mdn.mozillademos.org/files/13340/butterfly.jpg"
    alt="Un joli papillon">

<p> Lorem ipsum dolor sit amet, consectetur adipiscing elit. Nulla luctus aliquam dolor, eu lacinia lorem
    placerat vulputate. Duis felis orci, pulvinar id metus ut, rutrum luctus orci. Cras porttitor imperdiet
    nunc, at ultricies tellus laoreet sit amet. Sed auctor cursus massa at porta. Integer ligula ipsum,
    tristique sit amet orci vel, viverra egestas ligula. Curabitur vehicula tellus neque, ac ornare ex malesuada
    et. In vitae convallis lacus. Aliquam erat volutpat. Suspendisse ac imperdiet turpis. Aenean finibus
    sollicitudin eros pharetra congue. Duis ornare egestas augue ut luctus. Proin blandit quam nec lacus varius
    commodo et a urna. Ut id ornare felis, eget fermentum sapien.</p>

<p>Nam vulputate diam nec tempor bibendum. Donec luctus augue eget malesuada ultrices. Phasellus turpis est,
    posuere sit amet dapibus ut, facilisis sed est. Nam id risus quis ante semper consectetur eget aliquam
    lorem. Vivamus tristique elit dolor, sed pretium metus suscipit vel. Mauris ultricies lectus sed lobortis
    finibus. Vivamus eu urna eget velit cursus viverra quis vestibulum sem. Aliquam tincidunt eget purus in
    interdum. Cum sociis natoque penatibus et magnis dis parturient montes, nascetur ridiculus mus.</p>

```
Feuille de style :
```css
body {
    width: 90%;
    max-width: 900px;
    margin: 0 auto;
    font: .9em/1.2 Arial, Helvetica, sans-serif
}

.box {
    width: 150px;
    height: 100px;
    border-radius: 5px;
    background-color: rgb(207,232,220);
    padding: 1em;
    float: left;
    margin-right: 15px;
}
```
Evidemment, le flux normal d'affichage place la boîte d'image au-dessus du texte.

![image dans le flux normal](img/image-flux-normal.png)

Pour faire flotter l'image dans le texte ajoutez ces deux propriétés à la règle pour ```.box ```

```css
    float: left;
    margin-right: 15px;
```

![image flottante](img/image-float.png)

Tout contenu disposé après l'élément flottant dans le cours normal de la mise en page (c'est à dire disposé à la suite dans le code source) va maintenant l'envelopper en remplissant l'espace sur sa droite sur toute sa hauteur.

**ATTENTION** : L'image a été sorti du flux normal d'affichage, le texte du paragraphe l'entoure, MAIS ```la boîte du contenu du paragraphe reste sur toute la largeur du conteneur```, y compris derrière l'image.

![paragraphe sur toute la largeur](img/image-float-boite-parag.png)

Remarque : Faire flotter le contenu sur la droite a exactement le même effet, mais inversé.
```css
    float: right;
    margin-left: 15px;
```

## 1.3 Dégagement des boîtes flottantes
L'image est retirée du cours normal de l'affichage et les autres éléments se placent à côté, donc si nous voulons empêcher un élément à la suite de remonter pour se placer à côté, nous devons le dégager. Cette opération se réalise à l'aide de la propriété **```clear```**.

Modifiez le code HTML de l'exemple précedent :
* diminuez le nombre de mots du premier paragraphe
* ajoutez une classe ```stop-float``` au second paragraphe sous l'image

Ajoutez au CSS :
```css
.stop-float {
    clear: left;
}
```

![paragraphe dégagé du flottant](img/image-float-clear.png)

La propriété  clear accepte les valeurs suivantes :
* **```clear: left; ```**: l'élément est déplacé vers le bas afin de dégager les flottements à gauche.
* **```clear: right; ```**: l'élément est déplacé vers le bas afin de dégager les flottements à droite.
* **```clear: both; ```**: l'élément est déplacé vers le bas afin de dégager les flottements à gauche et à droite.

## 1.4 Dégagement des boîtes flottantes : cas d'une boîte enveloppante
La propriété clear n'est pas toujours suffisante, notamment si :
* la boîte flottante est de grande hauteur 
* la boîte flottante est enveloppée dans une autre boîte

**Exemple de mise en évidence du problème** : Modifiez votre document de sorte que le premier paragraphe et la boîte flottante soient englobés dans un élément ```<div>``` de classe wrapper.
```html
<div class="wrapper">
    <img class="box" src="https://mdn.mozillademos.org/files/13340/butterfly.jpg" alt="Un joli papillon">

    <p> Lorem ipsum dolor sit amet, consectetur adipiscing elit.
        Nulla luctus aliquam dolor, eu lacinia lorem</p>
</div>
```
Modifier le CSS pour mettre en évience le positionnement de la div :
```css
.wrapper {
    background-color: rgb(245, 136, 203);
    padding: 10px;
    color: #fff;
}
.box {
    float: left;
    /* ... */
}
```

![boîte flottante qui dépasse du conteneur](img/image-float-conteneur1.png)

Le problème ici, c'est qu'on aimerait que l'image flottante ne dépasse pas de son conteneur ```<div class="wrapper">```.

Pour faire ça, il faut ajouter ```display: flow-root;``` aux règles de la classe .wrapper.

![boîte flottante reste dans le conteneur](img/image-float-conteneur2.png)

```display: flow-root;``` fonctionne en créant ce que l'on appelle un **```block formatting context```** (BFC) (contexte de formatage de bloc). C'est comme une mini composition à l'intérieur de la page, composition dans laquelle tout est contenu ; l'élément flottant est contenu à l'intérieur de la BFC et l'arrière-plan est derrière les deux éléments.

> Documentation : 
> * [Les boîtes flottantes](https://developer.mozilla.org/fr/docs/Learn/CSS/CSS_layout/Floats)
> * [caniuse.com/flow-root](https://caniuse.com/flow-root)