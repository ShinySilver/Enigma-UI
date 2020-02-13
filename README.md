# Enigma-UI
## Introduction générale
Un système de GUI conçu pour l'équipe ENIGMA Robotics dans le cadre de la Coupe de France de robotique. L'objectif est de concevoir un système robuste et thread-safe d'IHM pouvant faire la liaision, notamment, avec une IA. Tout est fait pour que ce code puisse être réutilisé sans trop de difficulté par les promos suivantes. Ce système de GUI a été ensuite complété par une machine à état abstraite 'IA', du code pour la communication Serial, un 'Protocol' de démo, et des actionneurs en démo. Il est totalement fonctionnel sur WinterBot.
### WinterBot?
Le WinterBot est le robot principal conçu pour la cdr2019. Il est constitué d'un Rapberry Pi avec écran tactile responsable du controle, relié en usb à des arduino nano et Teensy controllant les actionneurs et les capteurs. Ce choix de conception permet de partager efficacement le travail de conception et de test, mais demande une abstraction très précise dans le code du Raspberry Pi pour ne pas se perdre et faire du code non réutilisable.
### Introduction aux branches dev-cdr et cdr
Les modifications, si elles sont significatives, sont faites et testées dans dev-cdr avant d'être merge à cdr.
Voir les repos d'ENIgma Robotics: https://github.com/BDI-ENIB 
## Build
Les scripts quickbuild.sh et run.sh servent respectivement à build et à executer le programme dans un environnement linux sur lequel SFML doit avoir été installé. Il est possible de rendre le makefile compatible Windows avec peu de modifications, mais la cible étant une machine Linux cela n'est pas une priorité. Selon le système faisant l'execution, de petites modifications de paramétrages doivent être faites dans les macros.
## Problèmes lors de l'execution
L'interface Serial peut provoquer des plantages lorseque les actionneurs demandés ne sont pas branchés. Il convient de dans ce genre de cas de désactiver cette fonctionnalité.
## TODO:
À faire:
- Retravailler l'abstraction de l'interface Serial, et des 'Module' Serial.
- Refaire le "Protocol" de démo pour qu'il soit plus facile à appréhender par les nouveaux
