
# Familiarisation avec le code du projet


## Exécution

Compilez et lancez le programme.

Allez dans le fichier tower_sim.cpp et rechercher la fonction responsable des inputs du programme.
Sur quelle touche faut-il appuyer pour ajouter un avion ?
Il faut appuyer sur la touche 'c'.
Comment faire pour quitter le programme ?
Il faut appuyer sur la touche 'x'.
A quoi sert la touche 'F' ?
A passer en mode plein écran.
Ajoutez un avion à la simulation et attendez.
Que est le comportement de l'avion ?
Il arrive et attérit sur la piste d'attérissage et roule jusqu"à une zone précise, puis il retourne
sur la piste et redécolle. 
Quelles informations s'affichent dans la console ?
DL6810 is now landing...
now servicing DL6810...
done servicing EY5350
DL6810 lift off
Ajoutez maintenant quatre avions d'un coup dans la simulation.
Que fait chacun des avions ?
Les trois premiers avions atterissent et le dernier attend qu'il y est un terminal libre pour attérir.


## Analyse du code

Listez les classes du programme à la racine du dossier src/.
Pour chacune d'entre elle, expliquez ce qu'elle représente et son rôle dans le programme.
Aircraft :
    représente l'avion et ses caractéristiques, gère les avions dans le programme et sa position
    -const std::string& get_flight_num() const; retourne le numéro de vol
    -float distance_to(const Point3D& p) const; retourne la distance entre l'avion et un point
    -void display() const override; affiche l'avion dans l'interface
    -void move() override; déplace l'avion, s'il est au sol vérifie qu'il peut décoller puis ajuste la vitesse
AirportType
    représente les zones de l'aéroport : le terminal, les pistes
Airport
    représente l'aéroport et ses lieux, permet de réserver un terminal pour les avions 
    -Tower& get_tower(); retourne la tour de l'aéroport
    -void display() const override; affiche l'aéroport sur le terminal
    -void move() override; actualise les terminaux de l'aéroport
Terminal
    représente un terminal dans l'aéroport et gère les avions qui sont liés en fonction des vols
    -bool in_use() const; retourne vrai si l'avion existe
    -bool is_servicing() const; indique si l'avion a fini ses cycles de service et est toujours en service
    -void assign_craft(const Aircraft& aircraft) ; assigne l'avion au terminal en question 
    -void start_service(const Aircraft& aircraft); si l'avion est proche du terminal, cela débute son service
    -void finish_service(); termine le service d'un avion
    -void move() override; incrémente les cycles de service
TowerSimulation
    permet d'interagir avec le programme, d'ajouter des avions
Tower
    fais le lien entre les avions et les terminaux
    -WaypointQueue get_instructions(Aircraft& aircraft); si un avion est proche d'un aéroport, cela emmène l'avion dans son terminal
    -void arrived_at_terminal(const Aircraft& aircraft); change le statut de l'avion s'il est arrivé à un terminal
Waypoint
    gère les coordonnées d'un avion et sa position

Pour les classes `Tower`, `Aircaft`, `Airport` et `Terminal`, listez leurs fonctions-membre publiques et expliquez précisément à quoi elles servent.
Réalisez ensuite un schéma entre ces difféntes classes pour illustrer comment elles intéragissent ensemble. 

Quelles classes et fonctions sont impliquées dans la génération du chemin d'un avion ? Waypoint
Quel conteneur de la librairie standard a été choisi pour représenter le chemin ?
deque
Expliquez pourquoi ce choix a été fait.


## Bidouillons !

1) Déterminez à quel endroit du code sont définies les vitesses maximales et accélération de chaque avion.
Dans la classe aircraft_type. 
Le Concorde est censé pouvoir voler plus vite que les autres avions.
Modifiez le programme pour tenir compte de cela.
on modifie la vitesse maximale de l'avion concorde au niveau de la classe Aircraft_types.

2) Identifiez quelle variable contrôle le framerate de la simulation.
Ajoutez deux nouveaux inputs au programme permettant d'augmenter ou de diminuer cette valeur.
On ajoute deux méthode increase_framerate et decrease_framerate afin de modifier cette valeur.
Essayez maintenant de mettre en pause le programme en manipulant ce framerate. Que se passe-t-il ? Fixez le problème.
On doit empêcher le framerate de devenir nul et empêcher le programme de planter.

3) Identifiez quelle variable contrôle le temps de débarquement des avions et doublez-le.

4) Lorsqu'un avion décolle, celui-ci n'est pas retiré du programme.
Faites en sorte qu'il le soit.

5) Lorsqu'un objet de type `Displayable` est créé, il faut ajouter celui-ci manuellement dans la liste des objets à afficher.
Il faut également penser à le supprimer de cette liste avant de le détruire.
Que pourriez-vous faire afin que l'ajout et la suppression de la liste soit "automatiquement gérée" lorsqu'un `Displayable` est créé ou détruit ?
Faites de même pour `DynamicObject`.

6) Le Tower a besoin de stocker pour tout `Aircraft` qui est actuellement affecté à un `Terminal` l'index de ce `Terminal` afin de pouvoir le "libérer" dès que son avion décollera. Cette affection prend actuellement la forme d'un `std::vector<std::pair<const Aircraft*, size_t>>` mais la recherche d'un avion dans ce vector prend temps linéaire (en nombre de `Terminal`s existant). C'est pas grave tant que ce nombre est petit, mais pour être préparé pour l'avenir, on aimerait bien remplacer le vector par une affectation qui reste efficace même en cas de beaucoup de `Terminal`s. Changez le code afin qu'il utilise un conteneur STL plus adapté (notamment, la fonction `find_craft_and_terminal(const Aicraft&)` ne sera plus nécessaire).


## Theorie

1) Comment a-t-on fait pour que person autre que le `Tower` peut reserver un terminal de l'aeroport?
2) En régardant le contenu de la fonction `void Aircraft::turn(Point3D direction)`,
pouvez-vous dire pourquoi on a choisi de ne pas passer une réference?
Arrivez-vous à eviter copier le `Point3D` donné?


## Bonus

Actuellement, chaque execution de la fonction `move()` represente un interval de temps fix.
Si on augmente le nombre de ces executions par seconde, on accelere du coup le temps dans la simulation.
Faites en sorte que c'est plus le cas, i. e. le changement du framerate n'aura aucune influence sur la vitesse des avions, temps de débarquement, etc.
Vu qu'on va plus pouvoir controler le passage de temps dans la simulation avec le framerate,
ajoutez deux nouveaux inputs au programme permettant d'accelerer ou ralentir la simulation (controle du temps "simulé" qui se passe entre deux executions de `move()`).
