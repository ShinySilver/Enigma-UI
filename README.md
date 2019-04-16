# Enigma-UI
## Introduction générale
Un système de GUI conçu pour l'équipe ENIGMA Robotics dans le cadre de la Coupe de France de robotique. L'objectif est de concevoir un système robuste et thread-safe d'IHM pouvant faire la liaision, notamment, avec une IA. Tout est fait pour que ce code puisse être réutilisé sans trop de difficulté par les promos suivantes.
## Introduction aux branches dev-cdr et cdr
L'objectif est de fusionner l'interface avec le système d'IA et de communication serial de l'équipe ENIgma Robotics. Les modifications, si elles sont significatives, sont faites et testées dans dev-cdr avant d'être merge à cdr.
Voir les repos d'ENIgma Robotics: https://github.com/BDI-ENIB 
## Build
Les scripts quickbuild.sh et run.sh servent respectivement à build et à executer le programme dans un environnement linux sur lequel SFML doit avoir été installé. Il est possible de rendre le makefile compatible Windows avec peu de modifications, mais la cible étant une machine Linux cela n'est pas une priorité.
