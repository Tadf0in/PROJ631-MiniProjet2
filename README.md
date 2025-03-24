# PROJ631 - Mini Projet 2
Compression par codage de Huffman

## Utilisation
Éxcuter un des fichiers .exe

Exemple :
```
.\tests\test_encode.exe
```

## Fichiers de tests :
- test_count : Compte la fréquence de chaque caractère dans le texte
- test_tree : Créer un arbre de Huffman
- test_parcours : Parcours en profondeur l'arbre de Huffman, pour assigner son encodage à chaque caractère
- test_encode : Génère le fichier compressé ainsi que le fichier de fréquences

Chaque test est effectué sur 5 textes différents :
1. Bonjour : "bonjour!!"
2. This : "this"
3. Texte simple : "this is an example of a huffman tree"
4. Extrait : Extrait du texte d'Alice au pays des merveilles
5. Alice : texte complet

## Sortie
Les fichiers générés par test_encode se trouvent dans le dossier `out/`
