
#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
#include <unordered_map>
#include <map>

using namespace std;

class Etudiant {
    string nom;
    int id;
    
public:
    static vector<Etudiant> etudiants;
    static int currentId;

    Etudiant(string nom) : nom(nom), id(currentId++) {}

    string getNom() const { return nom; }
    int getId() const { return id; }

    void creerEtudiant(string nom) {
        Etudiant etudiant(nom);
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
    static int currentId;
    Personnel(const string& nom, TypePersonnel type)
        : nom(nom), id(currentId++), type(type) {}

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
    Enseignant(const string& nom)
        : Personnel(nom, ENSEIGNANT) {}
};

class Administratif : public Personnel {
public:
    Administratif(const string& nom)
        : Personnel(nom, ADMINISTRATIF) {}
};

void ajouterPersonnel(vector<Personnel>& personnels, const string& nom, int type) {
    if (type == 1 ) {
        personnels.push_back(Enseignant(nom));
    } else if (type == 2) {
        personnels.push_back(Administratif(nom));
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

public:
    static vector<Cours> coursCollection;
    static int currentId;


    Cours(const string& nom, const string& departement, int niveau)
        : nom(nom), id(currentId++), departement(departement), niveau(niveau), enseignant(nullptr) {}

    void creerCours(const string& nom, const string& departement, int niveau) {
        Cours cours(nom, departement, niveau);
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
            else {
                cout << "Aucun cours trouvé avec l'ID : " << id << endl;
        }
        break;
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
    Enseignant* getEnseignant() const {
        return enseignant;
    }
};


class Inscriptions {
    // Main subscriptions map for validated students
    unordered_map<int, vector<Etudiant*>> inscriptions;

    // Pending subscriptions map for unvalidated students
    unordered_map<int, vector<Etudiant*>> pendingInscriptions;

public:
    

    const unordered_map<int, vector<Etudiant*>>& getInscriptions() const {
        return inscriptions;
    }

    Inscriptions() {}
    void inscrireEtudiant(Cours& cours, Etudiant* etudiant) {
        // Add the student to the pending subscriptions map for the course
        pendingInscriptions[cours.getId()].push_back(etudiant);
        cout << "L'étudiant " << etudiant->getNom() << " a été inscrit au cours " << cours.getNom() << ", mais l'inscription n'est pas encore validée." << endl;
    }

    void validerInscriptions(int coursId, int enseignantId, const vector<Cours>& coursCollection) {
    auto courseIt = find_if(coursCollection.begin(), coursCollection.end(),
                            [coursId](const Cours& cours) { return cours.getId() == coursId; });
    
    if (courseIt != coursCollection.end() && courseIt->getEnseignant() && courseIt->getEnseignant()->getId() == enseignantId) {

        auto it = pendingInscriptions.find(coursId);
        if (it != pendingInscriptions.end()) {
            inscriptions[coursId].insert(inscriptions[coursId].end(), it->second.begin(), it->second.end());
            pendingInscriptions.erase(it);
            cout << "Les inscriptions ont été validées pour le cours " << coursId << " par l'enseignant " << enseignantId << "." << endl;
        } else {
            cout << "Aucune inscription à valider pour le cours " << coursId << "." << endl;
        }
    } else {
        cout << "Validation échouée : enseignant non autorisé ou cours non trouvé." << endl;
    }
}

    void afficherEtudiantsIncrits(int coursId) const {
        auto it = inscriptions.find(coursId);
        if (it != inscriptions.end()) {
            cout << "Étudiants inscrits validés au cours " << coursId << " : ";
            for (const auto& etudiant : it->second) {
                cout << "Nom : " << etudiant->getNom() << ", ID : " << etudiant->getId() << " ";
            }
            cout << endl;
        } else {
            cout << "Aucun étudiant validé n'est inscrit au cours " << coursId << endl;
        }
    }
};

class Note{
    Etudiant* etudiant; 
    Cours* cours; 
    float grade; 
    vector<Note> notes;
public:
    //constructor par defaut : 
    Note(){
        etudiant = nullptr;
        cours = nullptr;
        grade = 0;
    };
     Note(Etudiant* etudiant, Cours* cours, float grade)
        : etudiant(etudiant), cours(cours), grade(grade) {}

    Etudiant* getEtudiant() const { return etudiant; }
    Cours* getCours() const { return cours; }
    float getGrade() const { return grade; }

    void setGrade(float newGrade) { grade = newGrade; }

  void ajouterNote(Etudiant* etudiant, Cours* cours, float grade, Inscriptions& inscriptions) {
    // Debug message to indicate the function is checking enrollment
    cout << "Debug: Checking if student is enrolled in course" << endl;

    // Get the list of students enrolled in the course from the inscriptions map
    const auto& courseId = cours->getId();
    auto it = inscriptions.getInscriptions().find(courseId);
    
   
    if (it != inscriptions.getInscriptions().end()) {
        const auto& enrolledStudents = it->second;
        
        auto studentIt = find(enrolledStudents.begin(), enrolledStudents.end(), etudiant);
        if (studentIt != enrolledStudents.end()) {
            cout << "-> Student found in course" << endl;

            notes.emplace_back(etudiant, cours, grade);
            cout << "Note ajoutée pour l'étudiant " << etudiant->getNom() << " dans le cours " << cours->getNom() << "." << endl;
        } else {
            
            cout << "-> Student not found in course" << endl;
            cout << "L'étudiant n'est pas inscrit dans le cours." << endl;
        }
    } else {
        cout << "-> Course not found in inscriptions map" << endl;
        cout << "Le cours n'est pas trouvé dans les inscriptions." << endl;
    }
}



    void modifierNote(Etudiant* etudiant, Cours* cours, float newGrade) {
        for (auto& note : notes) {
            if (note.getEtudiant() == etudiant && note.getCours() == cours) {
                note.setGrade(newGrade);
                cout << "Note modifiée pour l'étudiant " << etudiant->getNom() << " dans le cours " << cours->getNom() << "." << endl;
                return;
            }
        }
        cout << "Note non trouvée pour l'étudiant " << etudiant->getNom() << " dans le cours " << cours->getNom() << "." << endl;
    }

    void afficherNotesEtudiant(Etudiant* etudiant) const {
        cout << "Notes pour l'étudiant " << etudiant->getNom() << " :" << endl;
        for (const auto& note : notes) {
            if (note.getEtudiant() == etudiant) {
                cout << "Cours : " << note.getCours()->getNom() << ", Note : " << note.getGrade() << endl;
            }
        }
    }

    void afficherNotesCours(Cours* cours) const {
        cout << "Notes pour le cours " << cours->getNom() << " :" << endl;
        for (const auto& note : notes) {
            if (note.getCours() == cours) {
                cout << "Étudiant : " << note.getEtudiant()->getNom() << ", Note : " << note.getGrade() << endl;
            }
        }
    }
};

class Absence {
    Etudiant* etudiant; 
    Cours* cours;        
    int nbAbsences;      
    bool justifie;     

public:
    Absence() : etudiant(nullptr), cours(nullptr), nbAbsences(0), justifie(false) {}

    Absence(Etudiant* etudiant, Cours* cours, int nbAbsences = 0, bool justifie = false)
        : etudiant(etudiant), cours(cours), nbAbsences(nbAbsences), justifie(justifie) {}

    void afficherAbsence() const {
        cout << "Étudiant : " << etudiant->getNom() << ", Cours : " << cours->getNom()
                  << ", Absences : " << nbAbsences << ", Justifié : " << (justifie ? "Oui" : "Non") << endl;
    }

    void ajouterAbsence(Inscriptions& inscriptions) {
        
        auto inscriptionsMap = inscriptions.getInscriptions();
        if (inscriptionsMap.find(cours->getId()) != inscriptionsMap.end()) {
            const auto& inscrits = inscriptionsMap.at(cours->getId());
            if (find(inscrits.begin(), inscrits.end(), etudiant) != inscrits.end()) {
                nbAbsences++;
                cout << "Une absence a été ajoutée pour l'étudiant " << etudiant->getNom() << " dans le cours " << cours->getNom() << "." << endl;
            } else {
                cout << "Erreur : L'étudiant " << etudiant->getNom() << " n'est pas inscrit dans le cours " << cours->getNom() << "." << endl;
            }
        } else {
            cout << "Erreur : Aucun étudiant n'est inscrit dans le cours " << cours->getNom() << "." << endl;
        }
    }



     void modifierAbsence(int newNbAbsences, Inscriptions& inscriptions) {
        auto inscriptionsMap = inscriptions.getInscriptions();
        if (inscriptionsMap.find(cours->getId()) != inscriptionsMap.end()) {
            const auto& inscrits = inscriptionsMap.at(cours->getId());
            if (find(inscrits.begin(), inscrits.end(), etudiant) != inscrits.end()) {
                nbAbsences = newNbAbsences;
                cout << "Le nombre d'absences pour l'étudiant " << etudiant->getNom() << " dans le cours " << cours->getNom() << " a été modifié à " << nbAbsences << "." << endl;
            } else {
                cout << "Erreur : L'étudiant " << etudiant->getNom() << " n'est pas inscrit dans le cours " << cours->getNom() << "." << endl;
            }
        } else {
            cout << "Erreur : Aucun étudiant n'est inscrit dans le cours " << cours->getNom() << "." << endl;
        }
    }

    void setJustifie(bool newJustifie) {
        justifie = newJustifie;
       cout << "Le statut de l'absence pour l'étudiant " << etudiant->getNom() << " dans le cours " << cours->getNom() << " a été modifié à " << (justifie ? "Justifié" : "Non Justifié") << "." << endl;
    }


    Etudiant* getEtudiant() const {
        return etudiant;
    }

    Cours* getCours() const {
        return cours;
    }

    int getNbAbsences() const {
        return nbAbsences;
    }

    bool isJustifie() const {
        return justifie;
    }


     void afficherAbsencesEtudiant(const vector<Absence>& absences) const {
        cout << "Absences pour l'étudiant " << etudiant->getNom() << " dans tous les cours :" << endl;
        bool found = false;
        for (const auto& absence : absences) {
            if (absence.getEtudiant() == etudiant) {
                absence.afficherAbsence();
                found = true;
            }
        }
        if (!found) {
            cout << "Aucune absence trouvée pour l'étudiant " << etudiant->getNom() << "." <<endl;
        }
    }

    void afficherEtudiantsDansCours(const vector<Absence>& absences) const {
        cout << "Étudiants inscrits dans le cours " << cours->getNom() << " avec leurs absences respectives :" <<endl;
        bool found = false;
        for (const auto& absence : absences) {
            if (absence.getCours() == cours) {
                absence.afficherAbsence();
                found = true;
            }
        }
        if (!found) {
            cout << "Aucune absence trouvée pour le cours " << cours->getNom() << "." << endl;
        }
    }
};

class Emploi {
private:
    unordered_map<int, map<string, string>> schedule; 
    public:
        void addCourseSchedule(int courseId, const std::string& dayOfWeek, const std::string& timeSlot) {
            // Check if the course ID exists in the course vector
            if (schedule.find(courseId) == schedule.end()) {
                schedule[courseId] = map<string, string>();
            }

            schedule[courseId][dayOfWeek] = timeSlot;
            std::cout << "Emploi ajouter pour course ID " << courseId << " Jours : " << dayOfWeek << " à :  " << timeSlot << std::endl;
        }

        void removeCourseSchedule(int courseId) {
            schedule.erase(courseId);
            cout << "Emploi supprimer pour  course ID " << courseId <<endl;
        }

    void modifyCourseSchedule(int courseId, const std::string& dayOfWeek, const std::string& timeSlot) {
         auto courseScheduleIt = schedule.find(courseId);
    if (courseScheduleIt != schedule.end()) {
        auto& dayTimeMap = courseScheduleIt->second;
        if (dayTimeMap.find(dayOfWeek) != dayTimeMap.end()) {
            dayTimeMap[dayOfWeek] = timeSlot;
            std::cout << "emploi modifier pour  course ID " << courseId << " on " << dayOfWeek << " at " << timeSlot << std::endl;
        } else {
            dayTimeMap[dayOfWeek] = timeSlot;
            std::cout << "Nouveau emploi ajouter pour course ID " << courseId << " on " << dayOfWeek << " at " << timeSlot << std::endl;
        }
    } else {
        std::cout << "Course ID " << courseId << " pas d'emploi trouve" << std::endl;
    }
    }

   void displayWeeklyScheduleForStudent(const Etudiant* student, const std::vector<Cours>& coursCollection,Inscriptions& inscriptions) {
        std::cout << "Horaire d'emploi pour la semaine " << student->getNom() << " :" << std::endl;
        for (const auto& course : coursCollection) {
        int courseId = course.getId();

        const auto& inscrits = inscriptions.getInscriptions().at(courseId);
        if (std::find(inscrits.begin(), inscrits.end(), student) != inscrits.end()) {
            std::cout << "Course: " << course.getNom() << std::endl;

            auto scheduleIt = schedule.find(courseId);
            if (scheduleIt != schedule.end()) {
                for (const auto& [dayOfWeek, timeSlot] : scheduleIt->second) {
                    std::cout << "Jour : " << dayOfWeek << ", Heure: " << timeSlot << std::endl;
                }
            } else {
                std::cout << "Pas d'emploi pour se cours au moment ." << std::endl;
            }
        }
    }

}
    
};

void menuInscriptions(Inscriptions& inscriptions, const vector<Cours>& coursCollection) {
    int choix;
    int coursId;
    int enseignantId;
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

                cout << "Entrez l'ID de l'enseignant pour valider les inscriptions : ";
                cin >> enseignantId;

                inscriptions.validerInscriptions(coursId, enseignantId, coursCollection);
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


void menuNotes(vector<Etudiant>& etudiants, vector<Cours>& coursCollection, Note& notesManager,Inscriptions& inscriptions) {
    int choix;
    int etudiantId, coursId;
    float grade;

    Etudiant* etudiant = nullptr;
    Cours* cours = nullptr;
    do {
        cout << "\nMenu Notes" << endl;
        cout << "1. Ajouter une note pour un étudiant dans un cours" << endl;
        cout << "2. Modifier une note pour un étudiant dans un cours" << endl;
        cout << "3. Afficher toutes les notes d'un étudiant" << endl;
        cout << "4. Afficher toutes les notes d'un cours" << endl;
        cout << "5. Retour" << endl;
        cout << "Entrez votre choix : ";
        cin >> choix;

        switch (choix) {
            case 1:
               cout << "Entrez l'ID de l'étudiant : ";
                cin >> etudiantId;
                cout << "Entrez l'ID du cours : ";
                cin >> coursId;
                cout << "Entrez la note : ";
                cin >> grade;

                etudiant = nullptr;
                cours = nullptr;

                for (auto& e : etudiants) {
                    if (e.getId() == etudiantId) {
                        etudiant = &e;
                        break;
                    }
                }
        
                if (etudiant) {
                    cout << "Found etudiant: " << etudiant->getNom() << ", ID: " << etudiant->getId() << endl;
                } else {
                    cout << "Etudiant introuvable!" << endl;
                }

                for (auto& c : coursCollection) {
                    if (c.getId() == coursId) {
                        cours =&c;
                        break;
                    }
                }

                if (cours) {
                    cout << "Found cours: " << cours->getNom() << ", ID: " << cours->getId() << endl;
                } else {
                    cout << "Cours introuvable!" << endl;
                }

            
                if (etudiant && cours) {
                    notesManager.ajouterNote(etudiant, cours, grade, inscriptions);
                } else {
                    cout << "Erreur : étudiant ou cours introuvable." << endl;
                }
                break;

            case 2:
                cout << "Entrez l'ID de l'étudiant : ";
                cin >> etudiantId;
                cout << "Entrez l'ID du cours : ";
                cin >> coursId;
                cout << "Entrez la nouvelle note : ";
                cin >> grade;

                
                etudiant = nullptr;
                cours = nullptr;

                for (auto& e : etudiants) {
                    if (e.getId() == etudiantId) {
                        etudiant = &e;
                        break;
                    }
                }

                for (auto& c : coursCollection) {
                    if (c.getId() == coursId) {
                        cours = &c;
                        break;
                    }
                }

                if (etudiant && cours) {
                    notesManager.modifierNote(etudiant, cours, grade);
                } else {
                    cout << "Erreur : étudiant ou cours introuvable." << endl;
                }
                break;

            case 3:
                cout << "Entrez l'ID de l'étudiant : ";
                cin >> etudiantId;

                etudiant = nullptr;

               
                for (auto& e : etudiants) {
                    if (e.getId() == etudiantId) {
                        etudiant = &e;
                        break;
                    }
                }

                if (etudiant) {
                    notesManager.afficherNotesEtudiant(etudiant);
                } else {
                    cout << "Erreur : étudiant introuvable." << endl;
                }
                break;

            case 4:
                cout << "Entrez l'ID du cours : ";
                cin >> coursId;
                cours = nullptr;

                for (auto& c : coursCollection) {
                    if (c.getId() == coursId) {
                        cours = &c;
                        break;
                    }
                }

                if (cours) {
                    notesManager.afficherNotesCours(cours);
                } else {
                    cout << "Erreur : cours introuvable." << endl;
                }
                break;

            case 5:
                cout << "Retour au menu principal." << endl;
                break;

            default:
                cout << "Choix invalide, veuillez réessayer." << endl;
        }
    } while (choix != 5);
}

void menuAbsences(vector<Etudiant>& etudiants, vector<Cours>& coursCollection, vector<Absence>& absences, Inscriptions& inscriptions) {
    int choix;
    int etudiantId, coursId;
    int nbAbsences;
    bool justifie;

    Etudiant* etudiant = nullptr;
    Cours* cours = nullptr;

    do {
        cout << "\nMenu Absences" << std::endl;
        cout << "1. Ajouter une absence pour un étudiant dans un cours" << std::endl;
        cout << "2. Modifier une absence pour un étudiant dans un cours" << std::endl;
        cout << "3. Afficher toutes les absences d'un étudiant" << std::endl;
        cout << "4. Afficher les étudiants inscrits dans un cours avec leurs absences respectives" << std::endl;
        cout << "5. Retour" << std::endl;
        cout << "Entrez votre choix : ";
        cin >> choix;
        switch (choix) {
            case 1:
                cout << "Entrez l'ID de l'étudiant : ";
                cin >> etudiantId;
                cout << "Entrez l'ID du cours : ";
                cin >> coursId;
                cout << "L'absence est-elle justifiée ? (1: Oui, 0: Non) : ";
                cin >> justifie;

                etudiant = nullptr;
                cours = nullptr;

                // Trouver l'étudiant par ID
                for (auto& e : etudiants) {
                    if (e.getId() == etudiantId) {
                        etudiant = &e;
                        break;
                    }
                }

                // Trouver le cours par ID
                for (auto& c : coursCollection) {
                    if (c.getId() == coursId) {
                        cours = &c;
                        break;
                    }
                }

                if (etudiant && cours) {
                    // Vérifier si l'étudiant est inscrit dans le cours
                    const auto& inscrits = inscriptions.getInscriptions().at(cours->getId());
                    // Trouver une absence existante
                    auto it = find_if(absences.begin(), absences.end(), [etudiant, cours](const Absence& absence) {
                        return absence.getEtudiant() == etudiant && absence.getCours() == cours;
                    });

                    if (it != absences.end()) {
                        
                        it->ajouterAbsence(inscriptions);
                        it->setJustifie(justifie);
                    } else {
                        
                        if (find(inscrits.begin(), inscrits.end(), etudiant) != inscrits.end()) {
                            absences.push_back(Absence(etudiant, cours, 1, justifie));
                            cout << "Absence ajoutée pour l'étudiant " << etudiant->getNom() << " dans le cours " << cours->getNom() << "." << endl;
                        } else {
                            cout << "Erreur : L'étudiant " << etudiant->getNom() << " n'est pas inscrit dans le cours " << cours->getNom() << "." << endl;
                        }
                    }
                } else {
                    cout << "Erreur : étudiant ou cours introuvable." << endl;
                }
                break;

            case 2:
                std::cout << "Entrez l'ID de l'étudiant : ";
                std::cin >> etudiantId;
                std::cout << "Entrez l'ID du cours : ";
                std::cin >> coursId;
                std::cout << "Entrez le nouveau nombre d'absences : ";
                std::cin >> nbAbsences;
                std::cout << "L'absence est-elle justifiée ? (1: Oui, 0: Non) : ";
                std::cin >> justifie;

                etudiant = nullptr;
                cours = nullptr;

                // Trouver l'étudiant par ID
                for (auto& e : etudiants) {
                    if (e.getId() == etudiantId) {
                        etudiant = &e;
                        break;
                    }
                }

                // Trouver le cours par ID
                for (auto& c : coursCollection) {
                    if (c.getId() == coursId) {
                        cours = &c;
                        break;
                    }
                }

                if (etudiant && cours) {
                    // const auto& inscrits = inscriptions.getInscriptions().at(cours->getId());
                
                    auto it = find_if(absences.begin(), absences.end(), [etudiant, cours](const Absence& absence) {
                        return absence.getEtudiant() == etudiant && absence.getCours() == cours;
                    });

                    if (it != absences.end()) {
                        
                        it->modifierAbsence(nbAbsences, inscriptions);
                        it->setJustifie(justifie);
                    } else {
                        std::cout << "Absence non trouvée pour l'étudiant " << etudiant->getNom() << " dans le cours " << cours->getNom() << "." << std::endl;
                    }
                } else {
                    std::cout << "Erreur : étudiant ou cours introuvable." << std::endl;
                }
                break;

            case 3:
                std::cout << "Entrez l'ID de l'étudiant : ";
                std::cin >> etudiantId;

                // Trouver l'étudiant par ID
                for (auto& e : etudiants) {
                    if (e.getId() == etudiantId) {
                        etudiant = &e;
                        break;
                    }
                }

                if (etudiant) {
                    std::cout << "Absences pour l'étudiant " << etudiant->getNom() << " :" << std::endl;
                    bool found = false;
                    for (const auto& absence : absences) {
                        if (absence.getEtudiant() == etudiant) {
                            absence.afficherAbsence();
                            found = true;
                        }
                    }
                    if (!found) {
                        std::cout << "Aucune absence trouvée pour l'étudiant " << etudiant->getNom() << "." << std::endl;
                    }
                } else {
                    std::cout << "Erreur : étudiant introuvable." << std::endl;
                }
                break;

            case 4:
                std::cout << "Entrez l'ID du cours : ";
                std::cin >> coursId;

                // Trouver le cours par ID
                for (auto& c : coursCollection) {
                    if (c.getId() == coursId) {
                        cours = &c;
                        break;
                    }
                }

                if (cours) {
                    std::cout << "Étudiants inscrits dans le cours " << cours->getNom() << " avec leurs absences respectives :" << std::endl;
                    bool found = false;
                    for (const auto& absence : absences) {
                        if (absence.getCours() == cours) {
                            absence.afficherAbsence();
                            found = true;
                        }
                    }
                    if (!found) {
                        std::cout << "Aucune absence trouvée pour le cours " << cours->getNom() << "." << std::endl;
                    }
                } else {
                    std::cout << "Erreur : cours introuvable." << std::endl;
                }
                break;

            case 5:
                std::cout << "Retour au menu principal." << std::endl;
                break;

            default:
                std::cout << "Choix invalide, veuillez réessayer." << std::endl;
        }
    } while (choix != 5);
}

void menuEmploi(Emploi& emploi, const vector<Etudiant>& etudiants, const vector<Cours>& cours, Inscriptions& inscriptions) {
    int choix;
    int etudiantId;

    do {
        std::cout << "\nMenu Emploi du Temps" << std::endl;
        std::cout << "1. Ajouter un emploi du temps pour un cours" << std::endl;
        std::cout << "2. Modifier un emploi du temps pour un cours" << std::endl;
        std::cout << "3. Supprimer un emploi du temps pour un cours" << std::endl;
        std::cout << "4. Afficher l'emploi du temps d'un étudiant" << std::endl;
        std::cout << "5. Retour" << std::endl;
        std::cout << "Entrez votre choix : ";
        std::cin >> choix;

        switch (choix) {
            case 1: {
                int courseId;
                std::string dayOfWeek, timeSlot;
                std::cout << "Entrez l'ID du cours : ";
                std::cin >> courseId;
                std::cout << "Entrez le jour de la semaine (ex: Lundi) : ";
                std::cin >> dayOfWeek;
                std::cout << "Entrez l'heure de début et de fin (ex: 8h-10h) : ";
                std::cin >> timeSlot;
                emploi.addCourseSchedule(courseId, dayOfWeek, timeSlot);
                break;
            }
            case 2: {
                int courseId;
                std::string dayOfWeek, timeSlot;
                std::cout << "Entrez l'ID du cours à modifier : ";
                std::cin >> courseId;
                std::cout << "Entrez le jour de la semaine : ";
                std::cin >> dayOfWeek;
                std::cout << "Entrez la nouvelle plage horaire : ";
                std::cin >> timeSlot;
                emploi.modifyCourseSchedule(courseId, dayOfWeek, timeSlot);
                break;
            }
            case 3: {
                int courseId;
                std::cout << "Entrez l'ID du cours à supprimer : ";
                std::cin >> courseId;
                emploi.removeCourseSchedule(courseId);
                break;
            }
            case 4: {
                std::cout << "Entrez l'ID de l'étudiant : ";
                std::cin >> etudiantId;
                const Etudiant* student = nullptr;
                for (const auto& e : etudiants) {
                    if (e.getId() == etudiantId) {
                        student = &e;
                        break;
                    }
                }
                if (student) {
                    emploi.displayWeeklyScheduleForStudent(student,cours,inscriptions);
                } else {
                    std::cout << "Erreur : étudiant introuvable." << std::endl;
                }
                break;
            }
            case 5:
                std::cout << "Retour au menu principal." << std::endl;
                break;
            default:
                std::cout << "Choix invalide, veuillez réessayer." << std::endl;
        }
    } while (choix != 5);
}


vector<Cours> Cours::coursCollection;
vector<Etudiant> Etudiant::etudiants;

int Etudiant::currentId =0;
int Personnel::currentId = 1;
int Cours::currentId = 0;

int main() {
    vector<Personnel> personnels;
    Cours cours("", "", 0);

    int choix ,id,niveau;
    string nom,departement;

    Personnel* personne = nullptr; 

    Note notesManager;
    Inscriptions inscriptions;

    vector<Absence> absences;

    Emploi emploi;

    do {
        cout << "\nMenu" << endl;
        cout << "1. Menu Personnel Universitaire" << endl;
        cout << "2. Menu Cours" << endl;
        cout << "3. Menu Inscription" << endl;
        cout<<  "4. Menu Etudiant"<<endl;
        cout<<  "5. Menu Note"<<endl;
        cout<<  "6. Menu Absence"<<endl;
        cout<<  "7. Menu Emploi du temps"<<endl;
        cout << "8. Quitter" << endl;
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
                    case 1: {
                            int nombre;
                            cout << "Entrez le nombre de membres du personnel à créer : ";
                            cin >> nombre;
                            int startId = personnels.size() + 1;
                            int typePersonnel;
                            string nom;
                            for (int i = startId; i < startId + nombre; i++) {
                                cout << "Entrer les informations de membre du personnel numéro " << i << " :" << endl;
                                cout << "Sélectionnez le type de personnel (1: Enseignant, 2: Administratif) : ";
                                
                                cin >> typePersonnel;
                                cout << "Entrez le nom du membre du personnel : ";
                                
                                cin >> nom;

                                ajouterPersonnel(personnels, nom, typePersonnel);
                            }
                            break;
                        }

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
                    case 1:{
                        int nombre;
                        cout << "Entrez le nombre de cours à créer : ";
                        cin >> nombre;
                        int start = Cours::coursCollection.size() + 1;

                        for (int i = start; i < start + nombre; i++) {
                        cout << "Entrer les informations de cours numéro " << i << " :" << endl;
                            cout << "Entrez le nom du cours : ";
                            cin >> nom;
                            cout << "Entrez le département du cours : ";
                            cin >> departement;
                            cout << "Entrez le niveau du cours : ";
                            cin >> niveau;
                            cours.creerCours(nom, departement, niveau);
                        }
                        break;
                    }
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
            menuInscriptions(inscriptions, Cours::coursCollection);
        }else if(choix==4){
             int choix;

    string nom;
    int id;
    Etudiant etudiant(" ");

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
                int start = Etudiant::etudiants.size() + 1;

                for (int i = start; i < start + nombre; i++) {
                cout << "Entrer les informations de l'étudiant numéro " << i << " :" << endl;
                cout << "Entrez le nom de l'étudiant : ";
                cin >> nom;
                etudiant.creerEtudiant(nom);
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
        } else if(choix==5){
            vector<Etudiant*> etudiantsPtrs;
            vector<Cours*> coursCollectionPtrs;
            

            for (Etudiant& e : Etudiant::etudiants) {
                etudiantsPtrs.push_back(&e);
            }
            for (Cours& c : Cours::coursCollection) {
                coursCollectionPtrs.push_back(&c);
            }

            menuNotes(Etudiant::etudiants, Cours::coursCollection, notesManager,inscriptions);
            
        }
        else if(choix==6){
            menuAbsences(Etudiant::etudiants, Cours::coursCollection, absences, inscriptions);
        }
        else if(choix==7){
            menuEmploi(emploi, Etudiant::etudiants,Cours::coursCollection, inscriptions);
        }
        else if (choix == 8) {
            cout << "Au revoir !" << endl;
            break;
        } else {
            cout << "Choix invalide, veuillez réessayer." << endl;
        }
    } while (true);

    return 0;
}
