# Mise en page CSS : différentes techniques

> * Auteur : Gwénaël LAURENT
> * Date : 21/09/2021
> * OS : Windows 10 (version 20H2)
> * VScode : version 1.60.0 (system setup)
> * Chrome : version 94.0


# 1. Techniques de mise en page
Les techniques de mise en page CSS nous permettent de prendre des éléments contenus dans une page web (balises HTML) et d'en contrôler le placement.

> Chaque technique à ses usages, ses avantages et ses inconvénients. Aucune technique n'a été conçue pour être utilisée isolément.

En schématisant grossièrement, la mise en page web actuelle utilise 4 techniques :
1. Les **```techniques standards CSS```** pour les positionnements élémentaires
2. **```Grid Layout```** pour la mise en page principale
3. **```Flexbox```** pour la mise ne page des composants internes
4. Les **```media queries```** pour le responsive design (adaptation des CSS en fonction de l'appareil)


Pour commencer, il faut bien comprendre le fonctionnement normal de l'affichage HTML : c'est ce qu'on appelle le **```flux d'affichage normal```**. Les techniques de mises en page vont modifier ce flux d'affichage de différentes manières.

> ATTENTION : pour la plupart des éléments de la page, le flux d'affichage normal crée exactement la mise en page dont vous avez besoin. C'est pourquoi **```il est très important de commencer avec un document HTML bien structuré```**.

# 2. HTML et accessibilité
Les techniques de mise en page CSS participent à la mise en forme du contenu HTML. La modification d'ordre appliquée par CSS est uniquement visuelle. **```C'est toujours le document HTML qui contrôle l'ordre utilisé par les médias non-visuels```** (tels que la parole, la navigation au clavier ou le parcours des liens). 

> Les développeurs web doivent utiliser les propriétés d'ordre et de placement uniquement pour des raisons visuelles et non pour réordonner logiquement le contenu.

Source : [Les grilles CSS et l'accessibilité](https://developer.mozilla.org/fr/docs/Web/CSS/CSS_Grid_Layout/CSS_Grid_Layout_and_Accessibility)


# 3. Plan du cours
## 3.1 Découverte du HTML et du CSS
   * Internet et le Web (document "Web0 -Internet et le web.pdf")
   * Sites web statiques en HTML5 et CSS (document "Web1- html5 css les bases.pdf")
     * Les fichiers des ex. sont dans le dossier "tp/tp0-fichiers-doc-Web1"

## 3.2 Cours avec Exercices
> Le code de départ pour les exercices se situe dans le dossier "exercices"
 
1. [Flux d'affichage normal](1-flux-normal.md)
2. [Balises Structurantes](2-balises-structurantes.md)
3. [Sélecteurs CSS](3-selecteurs-css.md)
4. [Modification du flux normal avec ```display```](4-modif-flux-display.md)
5. [Modification du flux normal avec ```float```](5-modif-flux-float.md)
6. [Positionnement CSS avec ```position```, ```z-index```, ```columns``` et ```table```](6-position-zindex-table-multicol.md)

## 3.3 Travaux pratiques
> Les sujets de TP et le code de départ se situent dans le dossier "tp"

* [TP1 Masques 1](tp/tp1-masques-css-standards/tp1-masques-css-standards.md) : "Masques de protection respiratoire" - Mise en page avec les techniques standards de CSS

## 3.4 Cours avec Exercices
> Suivez le cours en codant les exemples dans VScode. Le code de départ des exemples et exercices se situe dans le dossier "exercices"

7. [Mise en page avec ```Grid Layout```](7-grid.md)

## 3.5 Travaux pratiques
> Les sujets de TP et le code de départ se situent dans le dossier "tp"

* [TP2 Pisciculture 1](tp/tp2-pisci-vert-grid/tp2-pisci-vert-grid.md) : Mise en page avec les grilles CSS
* [TP3 Caviar 1](tp/tp3-caviar-grid/tp3-caviar-grid.md) : Mise en page avec les grilles CSS

## 3.6 Cours avec exercices
> Le code de départ pour les exercices se situe dans le dossier "exercices"

8. [Mise en page avec ```Flexbox```](8-flexbox.md)
9.  [Adaptabilité avec ```media query```](9-media-query.md)
10.  [Mise en page CSS en ```Responsive Design```](10-responsive-design.md)

## 3.7 Travaux pratiques
> Les sujets de TP et le code de départ se situent dans le dossier "tp"

* [TP4 Cours CSS](tp/tp4-CoursCSS-grid-flex-media.md/tp4-CoursCSS-grid-flex-media.md): Responsive Web Design avec Grid, Flexbox et Media query