# CodeIgniter 4 : Query Builder

> * Auteur : Gwénaël LAURENT
> * Date : 04/04/2022
> * CodeIgniter : 4.x

# SELECT ALL (liste)
Pour les SELECT ALL dans une API REST :
* La requête doit utiliser la méthode **HTTP GET**
* Méthode du contrôleur REST : **index()**
* Exemple d'URL : http://conteneurs.local/REST/conteneur/
* On retourne la liste des enregistrements

Documentation : https://codeigniter4.github.io/userguide/database/query_builder.html#selecting-data

Exemple de codage dans le Model :
```php
protected $table = 'conteneur';
protected $primaryKey = 'Id';
protected $returnType = 'array';

/** Lire tous les enregistrements 
 * @return array    On retourne toutes les lignes de la table (un tableau de tableaux)
 */
public function getAll()
{
    // 1ère possibilité qui permet de choisir les colonnes 
    return $this->select('Id, AddrEmplacement')
                ->findAll();
    // ou 2ème possibilité
    // return $this->findAll();
}
```

# SELECT ID (détail)
Pour les SELECT ID dans une API REST :
* La requête doit utiliser la méthode **HTTP GET**
* Méthode du contrôleur REST : **show($prmId = null)**
* Exemple d'URL : http://conteneurs.local/REST/conteneur/60
* On retourne le détail d'un enregistrement

Documentation : https://codeigniter4.github.io/userguide/database/query_builder.html#selecting-data

Exemple de codage dans le Model :
```php
/** Lire un enregistrement
 * @param int $prmId    ID de la ligne
 * @return array    On retourne les données d'une ligne de la table (un tableau)
 */
public function getDetail($prmId)
{
    // 1ère possibilité qui permet de choisir les colonnes
    return $this->select('Id, AddrEmplacement')
                ->where(['Id' => $prmId])
                ->findAll(); 
    // ou 2ème possibilité
    // return $this->where(['Id' => $prmId])->findAll();
}
```

# INSERT
Pour les INSERT dans une API REST :
* La requête doit utiliser la méthode **HTTP POST**
* Méthode du contrôleur REST : **create()**
* Exemple d'URL : http://conteneurs.local/REST/conteneur/
* Les données à mettre à jour sont envoyées :
  * soit comme des données de formulaire POST, dans ce cas on les récupère en PHP avec ```$this->request->getPost('dto');```
  * soit comme des données RAW (pratique pour du JSON envoyé en AJAX), dans ce cas on les récupère avec  ```$raw_data = $this->request->getRawInput();```
* On retourne l'ID du nouvel enregistrement avec un code HTTP 201 (```$this->codes['created'])```), ou un code HTTP 400 en cas d'erreur (```$this->codes['invalid_data'])```)

Documentation : https://codeigniter4.github.io/userguide/database/query_builder.html#inserting-data

Exemple de codage dans le Model :
```php
/** Ajout d'un nouvel d'un enregistrement 
 * @param array $prmData    Tableau associatif contenant les données 
 *                          Ex : $prmData = ['AddrEmplacement' => "coucou", 'RefSigfox' => '00FFAABB']
 * @return int    On retourne l'ID du nouvel enregistrement
 */
public function createConteneur($prmData)
{
    //nom des colonnes qui peuvent être modifiées par cette requête (obligatoire avec INSERT, UPDATE)
    $this->allowedFields = ['AddrEmplacement', 'RefSigfox'];
    $this->insert($prmData); //une seule ligne à la fois, sinon insertBatch()
    $retour['lastInsertId'] = $this->insertID('Id');
    return $retour;
}
```

# UPDATE
Pour les UPDATE dans une API REST :
* La requête doit utiliser la méthode **HTTP PUT** (ou PATCH)
* Méthode du contrôleur REST : **update($prmId = null)**
* Exemple d'URL : http://conteneurs.local/REST/conteneur/60
* Les données à mettre à jour sont envoyées :
  * soit comme des données de formulaire POST, dans ce cas on les récupère en PHP avec ```$this->request->getPost('dto');```
  * soit comme des données RAW (pratique pour du JSON envoyé en AJAX), dans ce cas on les récupère avec  ```$raw_data = $this->request->getRawInput();```
* On retourne un code HTTP 200 si la mise à jour est effectuée, ou un code HTTP 404 en cas d'erreur, ou 400 s'il manque les données ou l'ID

Documentation : https://codeigniter4.github.io/userguide/database/query_builder.html#updating-data

Exemple de codage dans le Model :
```php
/** Mise à jour des données d'un enregistrement 
 * @param int $prmId    ID de la ligne à mettre à jour
 * @param array $prmData    Tableau associatif contenant les données 
 *                          Ex : $prmData = ['AddrEmplacement' => "coucou", 'RefSigfox' => '00FFAABB']
 * @return array    Eventuellement on retourne la ligne modifiée
 */
public function updateConteneur($prmId, $prmData)
{
    //nom des colonnes qui peuvent être modifiées par cette requête (obligatoire avec INSERT, UPDATE)
    $this->allowedFields = ['AddrEmplacement', 'RefSigfox'];

    // Première possibilité
    $this->set($prmData);
    $this->where('Id', $prmId);
    $this->update();

    // deuxième possibilité
    // $this->update($prmData, ['Id' => $prmId]);

    // on peut éventuellement retourner les valeurs mises à jour dans la BDD
    return $this->getDetail($prmId);
}
```

# DELETE
Pour les DELETE dans une API REST :
* La requête doit utiliser la méthode **HTTP DELETE**
* Méthode du contrôleur REST : **delete($prmId = null)**
* Exemple d'URL : http://conteneurs.local/REST/conteneur/60
* On retourne un code HTTP 200 si la suppression  est effectuée, ou un code HTTP 400 en cas d'erreur

Documentation : https://codeigniter4.github.io/userguide/database/query_builder.html#deleting-data

Exemple de codage dans le Model :

```php
/** Supprimer un enregistrement 
 * @param int $prmId    ID de la ligne à supprimer
 * @return boolean    Si la suppression est effective ou l'ID n'existe pas dans la table
 */
public function deleteConteneur($prmId)
{
    $retour = $this->delete(['Id' => $prmId]);
    return $retour;
    }
```