*This project has been created as part of the 42 curriculum by isoulima.*

# Get Next Line

## Description
Get Next Line a pour but d’implémenter la fonction `get_next_line`, permettant de lire un fichier ligne par ligne à partir d’un descripteur de fichier.
Le projet apprend la gestion de mémoire, l’utilisation d’une variable statique pour conserver l’état entre plusieurs appels, ainsi que la lecture bufferisée via `read()`.

L’objectif est d’obtenir une fonction robuste capable de :
- lire un flux texte progressivement
- renvoyer chaque ligne avec son éventuel '\n'
- gérer la fin de fichier proprement
- fonctionner aussi bien sur fichiers que sur entrée standard

---

## Instructions

### Compilation
Compilation classique avec BUFFER_SIZE modifiable :
cc -Wall -Wextra -Werror -D BUFFER_SIZE=42 get_next_line.c get_next_line_utils.c

Il est possible de changer BUFFER_SIZE pour tester le comportement.

---

## Exemple d’utilisation
int fd = open("file.txt", O_RDONLY);
char *line;

while ((line = get_next_line(fd)) != NULL)
{
    printf("%s", line);
    free(line);
}
close(fd);

---

## Choix techniques et algorithmiques
Le fonctionnement repose sur une logique de "stash" (réserve mémoire persistante) :
1. Lecture dans un buffer avec read()
2. Stockage des données lues dans une mémoire persistante grâce à une variable statique
3. Recherche d’un '\n'
4. Si trouvé → extraction et retour de la ligne, conservation du reste pour l’appel suivant
5. Si fin du fichier → retour de ce qu’il reste
6. Gestion stricte des malloc / free pour éviter les fuites mémoire

Contraintes importantes respectées :
- pas de variable globale
- gestion propre des erreurs
- comportement correct quelle que soit la taille du buffer

---

## Resources
- Documentation sur les file descriptors
- man read
- gestion des variables statiques en C
- gestion mémoire dynamique

### AI usage
L’IA a été utilisée uniquement pour :
- clarifier certains points du sujet
- structurer ce README
- comprendre les attentes pédagogiques

L’implémentation, la logique et la compréhension du code ont été réalisées manuellement.

---

## Auteur
42 Lausanne  
Login : isoulima
