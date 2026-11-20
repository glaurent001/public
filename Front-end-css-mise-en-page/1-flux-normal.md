(_Cours CSS : [retour sommaire](readme.md#32-cours-avec-exercices)_)
# Cours CSS 1 : Flux d'affichage normal

> * Auteur : Gwénaël LAURENT
> * Date : 15/09/2021
> * OS : Windows 10 (version 20H2)
> * VScode : version 1.60.0 (system setup)
> * Chrome : version 93.0

- [Cours CSS 1 : Flux d'affichage normal](#cours-css-1--flux-daffichage-normal)
- [1. Zone d'affichage d'une balise](#1-zone-daffichage-dune-balise)
  - [1.1 Les composants d'une boîte](#11-les-composants-dune-boîte)
  - [1.2 Le modèle standard de boîte CSS](#12-le-modèle-standard-de-boîte-css)
  - [1.3 Le modèle alternatif de boîte CSS](#13-le-modèle-alternatif-de-boîte-css)
  - [1.4 Visualiser les boîtes avec F12 dans le navigateur](#14-visualiser-les-boîtes-avec-f12-dans-le-navigateur)
- [2. Balises block ou inline](#2-balises-block-ou-inline)
- [3. Positionnement des boîtes en bloc](#3-positionnement-des-boîtes-en-bloc)
- [4. Positionnement des boîtes en ligne](#4-positionnement-des-boîtes-en-ligne)
- [5. Positionnements intérieurs et extérieurs](#5-positionnements-intérieurs-et-extérieurs)
- [Exo CSS1-1](#exo-css1-1)
- [Exo CSS1-2](#exo-css1-2)

# 1. Zone d'affichage d'une balise
## 1.1 Les composants d'une boîte
Dans la terminologie CSS, **```la zone d'affichage d'une balise s'appelle une boîte```** (**box**). Les boîtes peuvent donc être de bloc (*block boxes*) ou en ligne (*inline boxes*) mais pas les deux à la fois.

Toutes les boîtes sont composées de la même façon :

![modèle de boîte](img/box-model.png)

* **```Le contenu```** : zone où sont affichés les éléments contenus par la boîte. Peut être dimensionnée en utilisant les propriétés CSS ```width``` et ```height```.
* **```La marge intérieure```** (ou remplissage) : zone vierge qui se présente comme un espacement encadrant le contenu ; sa taille peut être controllée sur chaque côté en utilisant la propriété CSS ```padding```
* **```Le cadre```** (ou bordure) : Le cadre englobe le contenu et le padding pour former une bordure. Sa taille et son style sont paramétrés par la propriété CSS ```border```
* **```La marge intérieure```** : zone vierge mais qui est cette fois située a l'extérieur de l'élément, séparant l'élément des autres éléments de la page. Sa taille peut être controllée sur chaque côté en utilisant la propriété ```margin```

## 1.2 Le modèle standard de boîte CSS
> Les navigateurs utilisent le modèle standard par défaut.

Les propriétés de largeur (```width```) et de hauteur (```height```) définissent la largeur et la hauteur du **```contenu de la boîte```**.

Exemple :
```css
.box {
    width: 350px;
    height: 150px;
    margin: 10px;
    padding: 25px;
    border: 5px solid black;
}
```
![content-box](img/content-box.png)

Hors marges extérieurs, l'espace occupé par notre boîte dans le modèle standard vaut alors 410px (350 + 25 + 25 + 5 + 5), et la hauteur, 210px (150 + 25 + 25 + 5 + 5).

## 1.3 Le modèle alternatif de boîte CSS
> Pour utiliser le modèle alternatif, il faut  définir la propriété ```box-sizing: border-box;``` sur la boîte.

Les propriétés de largeur (```width```) et de hauteur (```height```) définissent la largeur et la hauteur de **```la boîte totale```**, hors marges extérieures, en comprenant le contenu, le padding et le border. Cela revient à demander au navigateur de considérer la boîte du cadre (la "border box") comme la zone d'effet de width et height.

Exemple :
```css
.box {
    box-sizing: border-box;
    width: 350px;
    height: 150px;
    margin: 10px;
    padding: 25px;
    border: 5px solid black;
}
```
![content-box](img/border-box.png)

## 1.4 Visualiser les boîtes avec F12 dans le navigateur
Les outils de développement des navigateurs (F12) permettent de visualiser toutes les propriétés des différentes couches de la boîte (contenu, padding, border et margin). 

Dans le navigateur : F12 > clic droit sur un élément de la page > Inspecter

![inspecter modèle de boîte](img/f12-box-model.png)
> Documentation : 
> * [Le modèle de Boîte](https://developer.mozilla.org/fr/docs/Learn/CSS/Building_blocks/The_box_model)


# 2. Balises block ou inline
Sans CSS, chaque balise HTML possède son propre type de placement dans le [flux d'affichage](https://developer.mozilla.org/fr/docs/Web/CSS/CSS_Flow_Layout) :
* Les **```élément en ligne```** (**inline** elements) sont affichés dans le sens dans lequel les mots sont écrits
* Les **```éléments de bloc```** (**block** elements) sont affichés les uns après les autres, à la façon des paragraphes

![placement inline et block](img/direction-inline-et-block.png)

> Remarque : les directions sont inversées pour les langues qui ont un mode d'écriture vertical, comme le japonais.


# 3. Positionnement des boîtes en bloc
Si une boîte est définie en bloc, elle suivra alors les règles suivantes :

* La boîte s'étend en largeur pour remplir totalement l'espace offert par son conteneur. Dans la plupart des cas, la boîte devient alors aussi large que son conteneur, occupant 100% de l'espace disponible.
* La boîte occupe sa propre nouvelle ligne et créé un retour à la ligne, faisant ainsi passer les éléments suivants à la ligne d'après.
* Les propriétés de largeur (width) et de hauteur (height) sont toujours respectées.
* Les propriétés padding, margin et border — correspondantes respectivement aux écarts de remplissage interne, externe et à la bordure de la boîte — auront pour effet de repousser les autres éléments.

Les éléments tels que les titres (```<h1>```,```<h2>```, etc.) et les paragraphes (```<p>```) utilisent le mode "bloc" comme propriété de positionnement extérieur par défaut.

Les boîtes de bloc possèdent des marges qui permettent de créer une séparation entre les éléments.

> Pour visualiser l'emplacement des boîtes de bloc pendant la mise en page, on peut leur attribuer une couleur de fond temporaire

```html
<div>
    <p>Un</p>
    <p>Deux</p>
    <p>Trois</p>
</div>
```
```css
p {
    background-color: hotpink;
}
```
![marges par défaut](img/marge-defaut-p.png)

Si on définit explicitement des marges nulles sur les paragraphes, les bordures se toucheront.
```css
p {
    background-color: hotpink;
    margin: 0;
}
```
![marges nulles](img/marge-nulle.png)

La spécification indique que **```les marges verticales entre chaque éléments de bloc fusionnent```**. Dans l'exemple suivant, les paragraphes ont une marge en haut qui mesure 20 pixels et une marge en bas qui mesure 40 pixels. La taille de la marge entre les deux paragraphes est donc de 40px car la plus petite est « fusionnée » avec la plus grande.

```css
p {
    background-color: hotpink;
    margin: 20px 0 40px 0;
}
```
![marges fusionnées](img/marge-fusion.png)

Par défaut, les éléments de bloc « s'étalent » horizontalement autant qu'ils le peuvent au sein du bloc englobant. 

Même si on fixe leur largeur et qu'ils puissent tenir horizontalement à plusieurs sur la même ligne, **```les éléments de bloc se positionnent les uns au dessous des autres```**.
```css
p {
    background-color: hotpink;
    width: 30%;
}
```
![bloc en dessous](img/blocs-en-dessous.png)


# 4. Positionnement des boîtes en ligne
Si une boîte est positionnée en ligne, alors :
* La boîte ne crée pas de retour à la ligne, les autres éléments se suivent donc en ligne.
* Les propriétés de largeur (width) et de hauteur (height) ne s'appliquent pas.
* Le padding, les marges et les bordures verticales (en haut et en bas) seront appliquées mais ne provoqueront pas de déplacement des éléments alentours.
* Le padding, les marges et les bordures horizontales (à gauche et à droite) seront appliquées et provoqueront le déplacement des éléments alentours.

Les éléments ```<a>```, utilisés pour les liens, ou encore ```<span>```, ```<em>``` et ```<strong>``` sont tous des éléments qui s'affichent "en ligne" par défaut.


**Exemple 1** : observez que les paramètres width et height sont totalement ignorés. Les propriétés de margin, padding et border sont quant à elles appliquées, mais n'ont pas modifié l'espacement avec les autres éléments de la page, se superposant ainsi avec les mots environnants dans le paragraphe.

![inline box ex1](img/inline-box-ex1.png)

```css
span {
    margin: 20px;
    padding: 20px;
    width: 80px;
    height: 50px;
    background-color: lightblue;
    border: 2px solid blue;
}
```
```html
<p>I am a paragraph and this is a <span>span</span> inside that paragraph. A span is
    an inline element and so does not respect width and height.</p>
```

**Exemple 2** : Dans l'exemple suivant on a trois boîtes en ligne créées :
* entre les balises ```<p>``` et ```<strong>```
* entre les balises ```<strong>``` et ```</strong>```
* entre les balises ```</strong>``` et ```</p>```

![inline box ex1](img/inline-box-ex2.png)

```css
strong {
    font-size: 300%;
}
```
```html
<p>Before that night—<strong>a memorable night</strong>, as it was to prove—hundreds
    of millions of people had watched the rising smoke-wreaths of their fires without
    drawing any special inspiration from the fact.”</p>
```
La hauteur de la boîte de ligne est définie avec la taille de la plus grand boîte qu'elle contient. Dans cet exemple, c'est le contenu de l'élément ```<strong>``` qui détermine la hauteur de la boîte de ligne pour cette ligne


> Documentation : 
> * [Disposition de bloc et en ligne avec le flux normal](https://developer.mozilla.org/fr/docs/Web/CSS/CSS_Flow_Layout/Block_and_Inline_Layout_in_Normal_Flow)

# 5. Positionnements intérieurs et extérieurs
Les boîtes en CSS possèdent un type de **```positionnement extérieur```** (*outer display*) qui détermine si la boîte est "en ligne" ou bien "en bloc".

Cependant, les boîtes ont aussi un type de **```positionnement intérieur```** (*inner dipslay*) , qui décrit le comportement de mise en page des élements contenus dans la boîte. Par défaut, les éléments contenus dans la boîte sont affichés dans la disposition normale, ce qui signifie qu'ils se comportent exactement comme n'importe quel autre élément "en bloc" ou "en ligne" (comme décrit auparavant).

> Ce type de positionnement intérieur peut naturellement être modifié.
> 
> Ainsi, si on donne la propriété ```display: flex;``` ou ```display: grid;``` à un élément, son type de positionnement extérieur est "en bloc" (block), mais son type de positionnement intérieur est modifié en flex ou en grid. Tout élément directement enfant de cette boîte se voit alors changé en élément flex ou grid, et sera mis en page selon les règles précisées dans les spécifications correspondantes.

# Exo CSS1-1
Dans l'exemple ci-dessous, se trouvent deux boîtes. Ces deux boîtes possèdent la classe ```.box``` qui leur confère les mêmes valeurs pour les propriétés width, height, margin, border et padding. La seule différence est que la seconde boîte utilise le modèle alternatif.

![Exo CSS1-1](img/Exo-CSS1-1.png)

Pouvez-vous modifier les dimensions de la seconde boîte (en lui ajoutant le CSS dans la classe .alternate) pour lui permettre d'avoir la même hauteur et largeur finale que l'autre boîte ?

Vous trouverez le code HTML de départ dans [exercices/CSS1-1.html](exercices/CSS1-1.html)

# Exo CSS1-2
Dans l'exemple ci-dessous, vous devez ajouter les déclarations CSS pour :
* respecter les dimensions indiquées en pixels
* ajouter un espace de 5 pixels entre les textes et leur bordure

![Exo-CSS1-2](img/Exo-CSS1-2.png)

Vous trouverez le code HTML de départ dans [exercices/CSS1-2.html](exercices/CSS1-2.html)