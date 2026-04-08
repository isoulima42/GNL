*Ce projet a été réalisé dans le cadre du cursus de 42 par isoulima.*

# Get Next Line

<img src="score.png" width="150" alt="Score 105/100">

![Language](https://img.shields.io/badge/Language-C-blue)
![Norminette](https://img.shields.io/badge/Norminette-OK-brightgreen)

## Description

Get Next Line est une fonction qui permet de lire un fichier ligne par ligne à partir d'un descripteur de fichier. Le projet enseigne la gestion de mémoire, l'utilisation de variables statiques pour conserver l'état entre plusieurs appels, ainsi que la lecture bufferisée via `read()`. La fonction est capable de lire aussi bien des fichiers que l'entrée standard, quel que soit le `BUFFER_SIZE`.

---

## Instructions

### Compilation

```bash
cc -Wall -Wextra -Werror -D BUFFER_SIZE=42 get_next_line.c get_next_line_utils.c main.c
```

Le `BUFFER_SIZE` est modifiable pour tester différents comportements. Sans le flag `-D`, la valeur par défaut est 42 (définie dans `get_next_line.h`).

### Utilisation

```c
#include "get_next_line.h"
#include <stdio.h>

int main(void)
{
    int   fd = open("file.txt", O_RDONLY);
    char  *line;

    while ((line = get_next_line(fd)) != NULL)
    {
        printf("%s", line);
        free(line);
    }
    close(fd);
    return (0);
}
```

---

## Fonctionnalités

- Lecture ligne par ligne depuis un file descriptor
- Chaque ligne retournée inclut le `\n` (sauf en fin de fichier sans `\n`)
- Fonctionne sur fichiers et entrée standard
- Compatible avec n'importe quel `BUFFER_SIZE` (1, 42, 9999, 10000000...)
- Retourne `NULL` en fin de fichier ou en cas d'erreur

---

## Choix techniques

Le fonctionnement repose sur une logique de **stash** (réserve mémoire persistante via une variable statique) :

1. Au premier appel, le stash est initialisé avec `ft_strdup("")` (chaîne vide)
2. `read_to_stash` lit dans un buffer avec `read()` et concatène au stash via `stash_join` (qui utilise `ft_strjoin` + libère l'ancien stash)
3. La boucle de lecture s'arrête dès qu'un `\n` est trouvé dans le stash (via `ft_strchr`) ou que `read()` retourne 0
4. `stash_line` extrait la ligne : si un `\n` est trouvé, `ft_substr` découpe la ligne et `ft_strdup` conserve le reste ; sinon tout le stash est retourné et le pointeur mis à `NULL`
5. En cas d'erreur de `read()` ou de `malloc`, `error_free` libère proprement le buffer et le stash

**Structure du code :**
- `get_next_line.c` : 4 fonctions statiques (`error_free`, `stash_join`, `read_to_stash`, `stash_line`) + la fonction publique `get_next_line`
- `get_next_line_utils.c` : 5 fonctions utilitaires recodées (`ft_strlen`, `ft_strdup`, `ft_strchr`, `ft_strjoin`, `ft_substr`) car la libft est interdite dans ce projet

Cette approche a été choisie car elle permet de ne lire que le strict nécessaire à chaque appel sans charger le fichier entier en mémoire. La variable statique conserve l'état entre les appels sans recourir à des variables globales (interdites par le sujet).

---

## Ressources

- `man read`
- Documentation sur les file descriptors
- Documentation sur les variables statiques en C
- Gestion mémoire dynamique (`malloc`, `free`)
- Sujet officiel 42

---

## AI usage

L'IA a été utilisée uniquement pour :
- clarifier certains points du sujet
- structurer ce README

L'implémentation, la logique et la compréhension du code ont été réalisées manuellement.

---

## Auteur

42 Lausanne
Login : isoulima
