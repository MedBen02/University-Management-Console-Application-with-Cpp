#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
#include <unordered_map>

using namespace std;

class Etudiant {
    string nom;
    int id;
    
public:
    static vector<Etudiant> etudiants;

    Etudiant(string nom, int id) : nom(nom), id(id) {}

    string getNom() const { return nom; }
    int getId() const { return id; }

    void creerEtudiant(string nom, int id) {
        Etudiant etudiant(nom, id);
        etudiants.push_back(etudiant);
    }

    void modifierNom(int id, const string& newNom) {
        for (auto& etudiant : etudiants) {
            if (etudiant.id == id) {
                etudiant.nom = newNom;
            }
        }
    }

    void supprimerEtudiant(int id) {
        for (auto it = etudiants.begin(); it != etudiants.end(); ++it) {
            if (it->id == id) {
                etudiants.erase(it);
                break;
            }
        }
    }

    void chercherEtudiant(int id) const {
        for (const auto& etudiant : etudiants) {
            if (etudiant.id == id) {
                cout << "Nom : " << etudiant.nom << ", ID : " << etudiant.id << endl;
            }
        }
    }

    void afficherEtudiants() const {
        for (const auto& etudiant : etudiants) {
            cout << "Nom : " << etudiant.nom << ", ID : " << etudiant.id << endl;
        }
    }

    ~Etudiant() {}
};

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
    vector<Etudiant*> inscrits;

public:
    static vector<Cours> coursCollection;

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

     void inscrireEtudiant(Etudiant* etudiant) {
        inscrits.push_back(etudiant);
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
            else {
                cout << "Aucun cours trouvé avec l'ID : " << id << endl;
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
    int getId() const {
        return id;
    }
    string getNom() const {
        return nom;
    }
};


class Inscriptions {
    

    unordered_map<int, vector<Etudiant*>> inscriptions;

    public:
   

    void inscrireEtudiant(Cours& cours, Etudiant* etudiant) {
        cours.inscrireEtudiant(etudiant);
        inscriptions[cours.getId()].push_back(etudiant);
        cout << "L'étudiant " << etudiant->getNom() << " a été inscrit au cours " << cours.getNom() << endl;
    }

    

    void validerInscriptions(int coursId) {
        auto it = inscriptions.find(coursId);
        if (it != inscriptions.end()) {
            cout << "Valider les inscriptions pour le cours " << coursId << endl;
        } else {
            cout << "Aucune inscription trouvée pour le cours " << coursId << endl;
        }
    }

    // Méthode pour afficher les étudiants inscrits à un cours
    void afficherEtudiantsIncrits(int coursId) const {
        auto it = inscriptions.find(coursId);
        if (it != inscriptions.end()) {
            cout << "Étudiants inscrits au cours " << coursId << " : ";
            for (const auto& etudiant : it->second) {
                cout << etudiant->getNom() << " ";
                cout << etudiant->getId() << " ";
            }
            cout << endl;
        } else {
            cout << "Aucun étudiant n'est inscrit au cours " << coursId << endl;
        }
    }
};



void menuInscriptions(Inscriptions& inscriptions, const vector<Cours>& coursCollection) {
    int choix;
    int coursId;
    int etudiantId;

    do {
        cout << "\nMenu Inscriptions" << endl;
        cout << "1. Inscrire un étudiant à un cours" << endl;
        cout << "2. Valider les inscriptions d'un cours" << endl;
        cout << "3. Afficher les étudiants inscrits à un cours" << endl;
        cout << "4. Retour" << endl;
        cout << "Entrez votre choix : ";
        cin >> choix;

        switch (choix) {
            case 1:
                cout << "Entrez l'ID du cours : ";
                cin >> coursId;
                cout << "Entrez l'ID de l'étudiant à inscrire : ";
                cin >> etudiantId;
                inscriptions.inscrireEtudiant(const_cast<Cours&>(coursCollection[coursId]), &Etudiant::etudiants[etudiantId]);
                break;
            case 2:
                cout << "Entrez l'ID du cours à valider : ";
                cin >> coursId;
                inscriptions.validerInscriptions(coursId);
                break;
            case 3:
                cout << "Entrez l'ID du cours pour afficher les étudiants inscrits : ";
                cin >> coursId;
                inscriptions.afficherEtudiantsIncrits(coursId);
                break;
            case 4:
                cout << "Retour au menu principal." << endl;
                break;
            default:
                cout << "Choix invalide, veuillez réessayer." << endl;
        }
    } while (choix != 4);
}

vector<Cours> Cours::coursCollection;
vector<Etudiant> Etudiant::etudiants;

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
        cout << "3. Menu Inscription" << endl;
        cout<<  "4. Menu Etudiant"<<endl;
        cout << "5. Quitter" << endl;
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
            Inscriptions inscriptions; // Make the coursCollection member accessible
            menuInscriptions(inscriptions, Cours::coursCollection);
        }else if(choix==4){
             int choix;
    string nom;
    int id;
    Etudiant etudiant("", 0);
    
    do {
        cout << "\nMenu" << endl;
        cout << "1. Creer des etudiants" << endl;
        cout << "2. Modifier le nom d'un étudiant" << endl;
        cout << "3. Supprimer un étudiant" << endl;
        cout << "4. Chercher un étudiant" << endl;
        cout << "5. Afficher tous les étudiants" << endl;
        cout << "6. Quitter" << endl;
        cout << "Entrez votre choix : ";
        cin >> choix;

        switch (choix) {
            case 1: {
                int nombre;
                cout << "Entrez le nombre d'etudiants à créer : ";
                cin >> nombre;
                for (int i = 0; i < nombre; i++) {
                    cout << " ID de l'etudiant " << i + 1 << ": "<<endl;
                    id=i+1;
                    cout << "Entrez le nom de l'étudiant " << i + 1 << ": "<<endl;
                    cin >> nom;
                    etudiant.creerEtudiant(nom, id);
                }
                break;
            }
            case 2:
                cout << "Entrez ID de l'étudiant à modifier : "<<endl;
                cin >> id;
                cout << "Entrez le nouveau nom : "<<endl;
                cin >> nom;
                etudiant.modifierNom(id, nom);
                break;
            case 3:
                cout << "Entrez ID de l'étudiant à supprimer : ";
                cin >> id;
                etudiant.supprimerEtudiant(id);
                break;
            case 4:
                cout << "Entrez ID de l'étudiant à chercher : ";
                cin >> id;
                etudiant.chercherEtudiant(id);
                break;
            case 5:
                cout << "Tous les étudiants : " << endl;
                etudiant.afficherEtudiants();
                break;
            case 6:
                cout << "Au revoir!" << endl;
                break;
            default:
                cout << "Choix invalide, veuillez réessayer." << endl;
        }
    } while (choix != 6);
        } 
        
        else if (choix == 5) {
            cout << "Au revoir !" << endl;
            break;
        } else {
            cout << "Choix invalide, veuillez réessayer." << endl;
        }
    } while (true);

    return 0;
}
