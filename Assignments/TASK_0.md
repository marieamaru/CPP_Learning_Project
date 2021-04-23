
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

5) Lorsqu'un objet de type Displayable est créé, il faut ajouter celui-ci manuellement dans la liste des objets à afficher. Il faut également penser à le supprimer de cette liste avant de le détruire. Que pourriez-vous faire afin que l'ajout et la suppression de la liste soit "automatiquement gérée" lorsqu'un Displayable est créé ou détruit ? Pensez-vous qu'il soit pertinent d'en faire de même pour DynamicObject ?

6) La tour de contrôle a besoin de stocker pour tout Aircraft le Terminal qui lui est actuellement attribué, afin de pouvoir le libérer une fois que l'avion décolle. Cette information est actuellement enregistrée dans un std::vector<std::pair<const Aircraft*, size_t>> (size_t représentant l'indice du terminal). Cela fait que la recherche du terminal associé à un avion est réalisée en temps linéaire, par rapport au nombre total de terminaux. Cela n'est pas grave tant que ce nombre est petit, mais pour préparer l'avenir, on aimerait bien remplacer le vector par un conteneur qui garantira des opérations efficaces, même s'il y a beaucoup de terminaux.
Modifiez le code afin d'utiliser un conteneur STL plus adapté. Normalement, à la fin, la fonction find_craft_and_terminal(const Aicraft&) ne devrait plus être nécessaire.

## Theorie

1) Comment a-t-on fait pour que person autre que le `Tower` peut reserver un terminal de l'aeroport?
2) En régardant le contenu de la fonction `void Aircraft::turn(Point3D direction)`,
pouvez-vous dire pourquoi on a choisi de ne pas passer une réference?
Arrivez-vous à eviter copier le `Point3D` donné?


## Bonus

Le temps qui s'écoule dans la simulation dépend du framerate du programme. La fonction move() n'utilise pas le vrai temps. Faites en sorte que si. Par conséquent, lorsque vous augmentez le framerate, la simulation s'exécute plus rapidement, et si vous le diminuez, celle-ci s'exécute plus lentement.

Dans la plupart des jeux ou logiciels que vous utilisez, lorsque le framerate diminue, vous ne le ressentez quasiment pas (en tout cas, tant que celui-ci ne diminue pas trop). Pour avoir ce type de résultat, les fonctions d'update prennent généralement en paramètre le temps qui s'est écoulé depuis la dernière frame, et l'utilise pour calculer le mouvement des entités.

Recherchez sur Internet comment obtenir le temps courant en C++ et arrangez-vous pour calculer le dt (delta time) qui s'écoule entre deux frames. Lorsque le programme tourne bien, celui-ci devrait être quasiment égale à 1/framerate. Cependant, si le programme se met à ramer et que la callback de glutTimerFunc est appelée en retard (oui oui, c'est possible), alors votre dt devrait être supérieur à 1/framerate.

Passez ensuite cette valeur à la fonction move des DynamicObject, et utilisez-la pour calculer les nouvelles positions de chaque avion. Vérifiez maintenant en exécutant le programme que, lorsque augmentez le framerate du programme, vous n'augmentez pas la vitesse de la simulation.

Ajoutez ensuite deux nouveaux inputs permettant d'accélérer ou de ralentir la simulation.
