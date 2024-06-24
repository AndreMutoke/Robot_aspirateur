<<<<<<< HEAD
# Robot_aspirateur
Le travail consiste en la conception d'un robot aspirateur, ici se trouve implementer le systeme du robot
=======
# ESP32_Project_Robot_Manage #

## Présentation

Ce projet rentre dans le cadre du cours de robotique. Le cours de robotique est un cours réservé
aux étudiants de licence 4 Réseaux et Télécommunications à la faculté des sciences informatiques
à UDBL. Il a pour but de mettre en évidence les connaissances acquises dans le cours de robotique,
d’électronique ainsi que dans le cours des systèmes embarqués (Cours de Licence 3, prérequis à
ce cours). Le projet en question consiste en la mise en place d’un robot ménager qui accomplit la
tâche d’un aspirateur. L’idée de ce projet est venue de l’observation quotidienne de notre milieu.

En effet, pour réaliser la tâche ou l’objectif cité de notre robot nous avons mis en œuvre plusieurs
notions de la connaissance parmi lesquelles : la maîtrise du langage C++, la souplesse dans
conception à l’aide des outils de base ainsi que la logique. Non seulement nos connaissances ont
été mises en œuvre, mais aussi nous avons eu en notre possession quelques matériels importants :
l’ESP32, Pilote Moteur L298, Capteur à Ultrason, Ventilateur 12 volt…
Ce projet se veut être une contribution devant résoudre un problème dans la société en ce qui
concerne le ménage en mettant en relief un aspirateur. En fait, Un aspirateur, aussi appelé
balayeuse est un appareil électroménager muni d’une pompe à air créant une dépression qui
provoque l’aspiration de poussière et de petits déchets tombés au sol. Il sert donc au nettoyage des
tapis, des parquets, sols et autres surfaces

Dans la réalisation de ce projet des difficultés n’ont pas manqué. Elles concernent particulièrement
la disponibilité d’équipements fiables et adéquats. Nous n’allons pas étaler toutes nos difficultés
dans cette section, mais nous le ferons un peu plus tard dans ce document. Ainsi, ce document a
pour but de présenter notre projet en donnant : ses objectifs, son fonctionnement, sa conception
ainsi que ses limites.

## Objectifs

Comme tout projet, notre robot possède des intérêts ou des objectifs. Pour les énumérer, nous
allons le classer dans l’ordre suivant :
- Intérêt Académique : Les cours vus sur le banc de l’école sont sanctionnés par différents travaux (Interrogations, travaux
pratiques, travaux dirigés…). Ces travaux permettent aux enseignants d’évaluer les étudiants ainsi
qu’aux étudiants de s’évaluer eux-mêmes. En réalisant ce projet, nous avons pu évaluer nos
compétences et nos capacités tant humaines qu’intellectuelles.

- Intérêt scientifique : Sur le banc de l’école, un projet est intéressant s’il relève aussi un intérêt scientifique. Ainsi
l’intérêt scientifique de notre projet se trouve dans le fait que nous avons eu à combiner plusieurs
aspects de la connaissance (programmation, électronique, mécanique…)

- Intérêt social : Le but principal d’une formation académique est de faire des étudiants des personnes aptes à
résoudre des problèmes tant simples que complexes dans leur environnement tout comme dans
leur pays. Le but de l’automatisation est de suppléer l’homme à tout travaux qui exigent beaucoup
d’énergie physique. Ainsi notre projet met en œuvre un robot qui facilite une tâche de ménage : le
balayage.

## Fonctionnement
Cette section a pour but de décrire le fonctionnement du robot ménager. Etant des ingénieurs en
formation, il convient d’utiliser un diagramme pour représenter le principe de fonctionnement du
robot en question. Pour arriver à nos fins, nous avons choisi d’utiliser le langage UML. En fait, le
Langage de Modélisation Unifié, de l'anglais Unified Modeling Language (UML), est un langage
de modélisation graphique à base de pictogrammes conçu comme une méthode normalisée de
visualisation dans les domaines du développement logiciel et en conception orientée objet.
En fait, notre robot possède trois modes de fonctionnement : le mode start, le mode manuel ainsi
que le mode automatique

- Mode Manuel
Pour expliquer le fonctionnement manuel, nous allons utiliser le diagramme de séquence qui
représente la séquence de messages entre les objets au cours d'une interaction. <br />
<img src="/home/andremutoke/Documents/PlatformIO/Projects/ESP32_Project_Robot_Manage/sequences.png"  />

- Mode Automatisé
Pour expliquer le fonctionnement automatique, nous allons utiliser le diagramme d’activité qui
fournit une vue du comportement de notre système en décrivant sa séquence d'actions. La page
suivante illustre le diagramme en question.

## Schémas du robot
Dans la documentation d’un système, nous retrouvons des éléments indispensables parmi
lesquels nous pouvons citer : la schématisation. Au fait, la schématisation consiste à expliquer,
souvent par un dessin, un concept, un objet complexe quitte à le rendre plus simple que ce qu'il
n'est en réalité.

- ESP32
ESP32 est une série de microcontrôleurs de type système sur une puce (SoC) d'Espressif Systems,
basé sur l'architecture Xtensa LX6 de Tensilica (en), intégrant la gestion du Wi-Fi et du Bluetooth
(jusqu'à LE 5.0 et 5.11) en mode double, et un DSP. C'est une évolution d'ESP8266. Le principal
outil de développement est ESP-IDF, logiciel libre développé par Espressif, écrit en C et utilisant
le système temps réel FreeRTOS. Il intègre un nombre important de bibliothèques et on retrouve
dans son écosystème des bibliothèques tierce libres pour différents types de périphériques liés à
l'embarqué et au temps réel.

- Pilote Moteur L298
Le L298N est un double pilote à pont complet. C'est un circuit monolithique intégré, un driver
pont complet, double, fort courant et tension élevée, conçu pour accepter des niveaux logiques
TTL standards et pour piloter des charges inductives telles que des relais, solénoïdes, moteurs DC
et pas à pas. Deux entrées d'activation sont disponibles pour activer ou désactiver le composant
indépendamment des signaux d'entrée. Les émetteurs des transistors inférieurs de chaque pont sont
connectés ensemble et la borne externe correspondante peut être utilisée pour le raccordement
d'une résistance de détection externe. Une entrée d'alimentation supplémentaire est prévue pour
que la logique fonctionne avec une tension inférieure. Il est utilisé dans des applications telles que
les moteurs DC à double balais et les moteurs pas à pas.

- Capteur à Ultrason
Un capteur à ultrasons émet à intervalles réguliers de courtes impulsions sonores à haute fréquence.
Ces impulsions se propagent dans l’air à la vitesse du son. Lorsqu’elles rencontrent un objet, elles
se réfléchissent et reviennent sous forme d’écho au capteur. Celui-ci calcule alors la distance le
séparant de la cible sur la base du temps écoulé entre l’émission du signal et la réception de l’écho.

- Ventilateur 12 volt
Pour réaliser un aspirateur, nous avons eu principalement besoin d’un ventilateur 12 v. Un
ventilateur 12 volts est un dispositif qui fonctionne avec une tension de 12 volts

### Aspect mobilité
Dans la conception d’un robot, l’aspect mobilité est très important. Pour rendre mobile notre robot,
nous avons utilisé les éléments suivants :
 - Moteur a engrenage DC 3-6v pour voiture Arduino
 - Les pneus correspondants à ces engrenages

## Dimensionnement électrique
Bilan de puissance
Ventilateur : I = 0,88 A ; U = 12 V ;
Pneu(moteur) : U = 6 V ; P = 1,2 W ;
Capteur Ultrason : I = 2 mA ; U = 5 V
Shied motor: U = 5 à 35; I = 36 mA; P = 1,26 W
Servomotor:
ESP32: 5V
Pt = 0,88 x 12 + 1,2 + 2 x 5 x 10 ^ -3 + 1,26 + 5 x 0,2 = 13,23 W
Une batterie délivre 3,7V. Nous avons trois batteries, ce qui fera 3,7x3 = 11,1 v et I = 2600mA,
Donc la puissance sera :
P = 11,1 x 2600 x 10 ^-3 = 28,86 W


## Dependencies
Pour ce qui concerne les dépendances,nous pouvons citer :
- DabbleESP32, téléchargeable sur le lien : https://github.com/STEMpedia/DabbleESP32
- ESP32Servo, téléchargeable sur le lien : https://github.com/madhephaestus/ESP32ServoServer

## LICENSE
The part contains my code is released under BSD 2-Clause License. Regarding other libraries used in this project, please follow the respective Licenses.
>>>>>>> 5ff61f6 (Initialisation git)
