
#include <iostream>
#include <string>
#include <vector>
#include <algorithm>

using namespace std;

enum TypePersonnel {
    ENSEIGNANT,
    ADMINISTRATIF
};

class Personnel {
    string nom;
    int id;
    TypePersonnel type; 

public:
    Personnel(const string& nom, int id, TypePersonnel type)
        : nom(nom), id(id), type(type) {}

    string getNom() const { return nom; }
    int getId() const { return id; }
    TypePersonnel getType() const { return type; }

    void modifierInfo(const string& newNom) {
        nom = newNom;
    }

    virtual void afficherInfo() const {
        cout << "Nom : " << nom << ", ID : " << id;
        cout << ", Type : " << (type == ENSEIGNANT ? "Enseignant" : "Administratif") << endl;
    }
};

class Enseignant : public Personnel {
public:
    Enseignant(const string& nom, int id)
        : Personnel(nom, id, ENSEIGNANT) {}
};

class Administratif : public Personnel {
public:
    Administratif(const string& nom, int id)
        : Personnel(nom, id, ADMINISTRATIF) {}
};

void ajouterPersonnel(vector<Personnel>& personnels, const string& nom, int id, int type) {
    if (type == 1 ) {
        personnels.push_back(Enseignant(nom, id));
    } else if (type == 2) {
        personnels.push_back(Administratif(nom, id));
    } else {
        cout << "Type de personnel invalide." << endl;
    }
}

void supprimerPersonnelParId(vector<Personnel>& personnels, int id) {
    personnels.erase(remove_if(personnels.begin(), personnels.end(), [id](const Personnel& p) {
        return p.getId() == id;
    }), personnels.end());
}

void afficherTousLesPersonnels(const vector<Personnel>& personnels) {
    for (const auto& p : personnels) {
        p.afficherInfo();
    }
}

Personnel* chercherPersonnelParId(const vector<Personnel>& personnels, int id) {
    for (const auto& personne : personnels) {
        if (personne.getId() == id) {
            return const_cast<Personnel*>(&personne);
        }
    }
    return nullptr; 
}

class Cours {

    string nom;
    int id;
    string departement;
    int niveau;
    Enseignant* enseignant;
    static vector<Cours> coursCollection;

public:

    Cours(const string& nom, int id, const string& departement, int niveau)
        : nom(nom), id(id), departement(departement), niveau(niveau), enseignant(nullptr) {}

    void creerCours(const string& nom, int id, const string& departement, int niveau) {
        Cours cours(nom, id, departement, niveau);
        coursCollection.push_back(cours);
    }

    void modifierCours(const string& nom, int id, const string& departement, int niveau) {
        for (auto& c : coursCollection) {
            if (c.id == id) {
                c.nom = nom;
                c.departement = departement;
                c.niveau = niveau;
            }
        }
    }

    void supprimerCours(int id) {
        coursCollection.erase(remove_if(coursCollection.begin(), coursCollection.end(), [id](const Cours& c) {
            return c.id == id;
        }), coursCollection.end());
    }

    void attribuerEnseignant(int coursId, const vector<Personnel>& personnels, int enseignantId) {
        Personnel* enseignant = chercherPersonnelParId(personnels, enseignantId);
        if (enseignant && enseignant->getType() == ENSEIGNANT) {
            for (auto& c : coursCollection) {
                if (c.id == coursId) {
                    c.enseignant = static_cast<Enseignant*>(enseignant);
                    cout << "L'enseignant " << enseignant->getNom() << " a été attribué au cours " << c.nom << endl;
                    break;
                }
            }
        } else {
            cout << "L'enseignant sélectionné n'est pas valide." << endl;
        }
    }

    void chercherCours(int id) const {
        for (const auto& c : coursCollection) {
            if (c.id == id) {
                cout << "Cours : " << c.nom << ", ID : " << c.id
                     << ", Département : " << c.departement
                     << ", Niveau : " << c.niveau;
                if (c.enseignant) {
                    cout << ", Enseignant : " << c.enseignant->getNom() << endl;
                } else {
                    cout << ", Enseignant : Aucun" << endl;
                }
            }
        }
    }

    void afficherCours() const {
        for (const auto& c : coursCollection) {
            cout << "Cours : " << c.nom << ", ID : " << c.id
                 << ", Département : " << c.departement
                 << ", Niveau : " << c.niveau;
            if (c.enseignant) {
                cout << ", Enseignant : " << c.enseignant->getNom() << endl;
            } else {
                cout << ", Enseignant : Aucun" << endl;
            }
        }
    }
};

vector<Cours> Cours::coursCollection;
int main() {
    vector<Personnel> personnels;
    Cours cours("", 0, "", 0);

    int choix ,id,niveau;
    string nom,departement;

    Personnel* personne = nullptr; 

    do {
        cout << "\nMenu" << endl;
        cout << "1. Menu Personnel Universitaire" << endl;
        cout << "2. Menu Cours" << endl;
        cout << "3. Quitter" << endl;
        cout << "Entrez votre choix : ";
        cin >> choix;

        if (choix == 1) {
            int choixPersonnel;
            do {
                cout << "\nMenu Personnel Universitaire" << endl;
                cout << "1. Créer un membre du personnel" << endl;
                cout << "2. Modifier un membre du personnel" << endl;
                cout << "3. Supprimer un membre du personnel" << endl;
                cout << "4. Chercher un membre du personnel" << endl;
                cout << "5. Afficher tous les membres du personnel" << endl;
                cout << "6. Retour" << endl;
                cout << "Entrez votre choix : ";
                cin >> choixPersonnel;

                switch (choixPersonnel) {
                    case 1:
                        int nombre;
                        cout << "Entrez le nombre de membres du personnel à créer : ";
                        cin >> nombre;
                        for (int i = 0; i < nombre; i++) {
                            cout << "Sélectionnez le type de personnel (1: Enseignant, 2: Administratif) : ";
                            int typePersonnel;
                            cin >> typePersonnel;
                            cout << "Entrez le nom du membre du personnel : ";
                            cin >> nom;
                            cout << "Entrez l'ID du membre du personnel : ";
                            cin >> id;
                            ajouterPersonnel(personnels, nom, id, typePersonnel);
                        }
                        break;
                    case 2:
                        cout << "Entrez l'ID du membre du personnel à modifier : ";
                        cin >> id;
                        cout << "Entrez le nouveau nom : ";
                        cin >> nom;
                        personne = chercherPersonnelParId(personnels, id);
                        if (personne) {
                            personne->modifierInfo(nom);
                        } else {
                            cout << "Aucun membre du personnel trouvé avec l'ID : " << id << endl;
                        }
                        break;
                    case 3:
                        cout << "Entrez l'ID du membre du personnel à supprimer : ";
                        cin >> id;
                        supprimerPersonnelParId(personnels, id);
                        break;
                    case 4:
                        cout << "Entrez l'ID du membre du personnel à chercher : ";
                        cin >> id;
                        personne = chercherPersonnelParId(personnels, id);
                        if (personne) {
                            personne->afficherInfo();
                        } else {
                            cout << "Aucun membre du personnel trouvé avec l'ID : " << id << endl;
                        }
                        break;
                    case 5:
                        cout << "Liste de tous les membres du personnel :" << endl;
                        afficherTousLesPersonnels(personnels);
                        break;
                    case 6:
                        cout << "Retour au menu principal." << endl;
                        break;
                    default:
                        cout << "Choix invalide, veuillez réessayer." << endl;
                }
            } while (choixPersonnel != 6);
        } else if (choix == 2) {
            int choixCours;
            do {
                cout << "\nMenu Cours" << endl;
                cout << "1. Créer des cours" << endl;
                cout << "2. Modifier un cours" << endl;
                cout << "3. Supprimer un cours" << endl;
                cout << "4. Attribuer un enseignant à un cours" << endl;
                cout << "5. Chercher un cours" << endl;
                cout << "6. Afficher tous les cours" << endl;
                cout << "7. Retour" << endl;
                cout << "Entrez votre choix : ";
                cin >> choixCours;

                switch (choixCours) {
                    case 1:
                        int nombre;
                        cout << "Entrez le nombre de cours à créer : ";
                        cin >> nombre;
                        for (int i = 0; i < nombre; i++) {
                            cout << "Entrez le nom du cours : ";
                            cin >> nom;
                            cout << "Entrez l'ID du cours : ";
                            cin >> id;
                            cout << "Entrez le département du cours : ";
                            cin >> departement;
                            cout << "Entrez le niveau du cours : ";
                            cin >> niveau;
                            cours.creerCours(nom, id, departement, niveau);
                        }
                        break;
                    case 2:
                        cout << "Entrez l'ID du cours à modifier : ";
                        cin >> id;
                        cout << "Entrez le nouveau nom : ";
                        cin >> nom;
                        cout << "Entrez le nouveau département : ";
                        cin >> departement;
                        cout << "Entrez le nouveau niveau : ";
                        cin >> niveau;
                        cours.modifierCours(nom, id, departement, niveau);
                        break;
                    case 3:
                        cout << "Entrez l'ID du cours à supprimer : ";
                        cin >> id;
                        cours.supprimerCours(id);
                        break;
                    case 4:
                        cout << "Entrez l'ID du cours : ";
                        cin >> id;
                        cout << "Entrez l'ID de l'enseignant à attribuer : ";
                        int enseignantId;
                        cin >> enseignantId;
                        cours.attribuerEnseignant(id, personnels, enseignantId);
                        break;
                    case 5:
                        cout << "Entrez l'ID du cours à chercher : ";
                        cin >> id;
                        cours.chercherCours(id);
                        break;
                    case 6:
                        cout << "Liste de tous les cours :" << endl;
                        cours.afficherCours();
                        break;
                    case 7:
                        cout << "Retour au menu principal." << endl;
                        break;
                    default:
                        cout << "Choix invalide, veuillez réessayer." << endl;
                }
            } while (choixCours != 7);
        } else if (choix == 3) {
            cout << "Au revoir !" << endl;
            break;
        } else {
            cout << "Choix invalide, veuillez réessayer." << endl;
        }
    } while (true);

    return 0;
}
