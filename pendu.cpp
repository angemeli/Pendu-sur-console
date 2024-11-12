#include <iostream>

using namespace std;

void draw_pendu(int nbr_tentatives); //Fonction qui dessine le pendu en fonction du nombre de tentatives
void draw_mot_masque(const char *mot, char *ptr_masque); //Fonction qui affiche le mot masqué
int longueur(const char *chaine); //Fonction qui trouve la longueur d'un mot
char convert_to_maj(char letter); //Fonction qui convertit les lettres en majuscule. Cela permet d'éviter les erreurs
bool found_letter(const char *mot, char *ptr_masque, char letter); //Fonction qui recherche et place une lettre si elle se trouve dans le mot à chercher
bool complete_word(const char *mot, char *ptr_masque); //   Fonction qui détermine si le je est terminé


int main(int argc, char const *argv[]) {
    // Mot à deviner
    const char *mot = "PENDU";
    char letter;
    int i = 0;
    int nbr_tentatives = 6;

    char mot_masque[longueur(mot) + 1];
    char *ptr_masque = mot_masque; // Pointeur vers le mot masqué
    while (i < longueur(mot)) {
        ptr_masque[i] = '_';
        i+=1;
    }
    ptr_masque[longueur(mot)] = '\0'; // Ajoute le caractère '\0' de fin de chaîne
    
    system("CLS");
    cout << "\nBienvenue dans le jeu Pendu\n";
    cout << "\nEssayez de deviner le mot masque ci-dessous. Attention, vous n'avez que 6 tentatives\n";

    // Boucle pour demander des lettres jusqu'à ce que le mot soit complet
    while (true) {
        if (nbr_tentatives == 0) {
            draw_pendu(nbr_tentatives);
            cout << "\nLe pendu est entierement dessine, vous avez perdu\n\n";
            break;
        }
        
        draw_pendu(nbr_tentatives);
        draw_mot_masque(mot, ptr_masque);
        cout << "\n\nEntrez une lettre : ";
        cin >> letter;

        letter = convert_to_maj(letter); // Convertit la lettre en majuscule, pour éviter les erreurs 

        if (found_letter(mot, ptr_masque, letter) == false) {
            system("CLS");
            draw_pendu(nbr_tentatives);
            draw_mot_masque(mot, ptr_masque);
            cout << "\n\nLa lettre "<< letter << " n'existe pas dans le mot, ou elle est deja placee\n"; // Affiche si la lettre n'est pas trouvée
            nbr_tentatives -= 1;
        }

        if (complete_word(mot, ptr_masque) == true) {
            system("CLS");
            draw_pendu(nbr_tentatives);
            draw_mot_masque(mot, ptr_masque);
            cout << "\n\nFelicitations, vous avez trouve le mot : \033[32m" << mot << "\033[37m\n";
            break;
        }
    }

    return 0;
}


void draw_pendu(int nbr_tentatives) {
    cout << "\033[31m\n";
    switch (nbr_tentatives) {
        case 5 :
            cout << "   O    " << "\n";
            break;
        case 4 :
            cout << "   O    " << "\n";
            cout << "  /  " << "\n";
            break;
        case 3 :
            cout << "   O    " << "\n";
            cout << "  / \\  " << "\n";
            break;
        case 2 :
            cout << "   O    " << "\n";
            cout << "  /|\\  " << "\n";
            break;
        case 1 :
            cout << "   O    " << "\n";
            cout << "  /|\\  " << "\n";
            cout << "  /   " << "\n";
            break;
        case 0 :
            cout << "   O    " << "\n";
            cout << "  /|\\  " << "\n";
            cout << "  / \\  " << "\n";
            break;
    }
    cout << "\033[37m";
}

void draw_mot_masque(const char *mot, char *ptr_masque) {
    cout << "\n";
    int i = 0;
    while (i < longueur(mot)) {
        cout << ptr_masque[i] << " "; // Affiche le mot masqué
        i+=1;
    }
}

int longueur(const char *chaine) {
    int i = 0;
    while (chaine[i] != '\0') {
        i+=1;
    }
    return i;
}

char convert_to_maj(char letter) {
    int n = (int)letter;

    if (n >= 97 && n <= 122) { //Si la lettre est en minuscule
        n -= 32;
        letter = (char)n;
    }

    return letter;
}

bool found_letter(const char *mot, char *ptr_masque, char letter) {
    bool found = false;
    int i = 0;
    while (i < longueur(mot)) {
        if (mot[i] == letter && ptr_masque[i] == '_') { //Vérifie que la lettre est dans le mot, et ne fait pas déjà partie du mot masqué
            ptr_masque[i] = letter;
            found = true;
            system("CLS");
        }
        i+=1;
    }

    return found;
}

bool complete_word(const char *mot, char *ptr_masque) {
    bool complete = true;
    int i = 0;
    while (i < longueur(mot)) {
        if (ptr_masque[i] == '_') {
            complete = false;
            break;
        }
        i+=1;
    }

    return complete;
}
