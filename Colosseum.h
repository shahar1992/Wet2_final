//
// Created by Michal on 06/01/2018.
//

#ifndef WET2_FINAL_COLOSSEUM1_H
#define WET2_FINAL_COLOSSEUM1_H

#include "HashChains.h"
#include "TrainingGroup.h"
#include "MinHeap.h"
#include "library2.h"

class Colosseum {

    //-----------------FUNCTION OBJECTS---------------------------
    /**
     * function object to get a gladiator ID
     */
    class getGladiatorKey {
    public:
        explicit getGladiatorKey(){}
        int operator()(const Gladiator& X) const {
            return X.getID();
        }
    };

    /**
     * function object to get a Trainig group ID
     */
    class getTrainingGroupKey {
    public:
        explicit getTrainingGroupKey(){}
        int operator()(const TrainingGroup& X) const {
            return X.getID();
        }
    };

    /**
     * function object that returns 1 if the given gladiator should be before Y
     * according to the level and ID of the gladiators
     * if equal returns 0, otherwise -1
     */
    class GladiatorCompareByLevelAndID {
        int gladiator_id;
        int level;
    public:
        explicit GladiatorCompareByLevelAndID(int id, int level):
                gladiator_id(id), level(level) {}
        explicit GladiatorCompareByLevelAndID(Gladiator& X):
                gladiator_id(X.getID()), level(X.getScore()) {}
        int operator()(const Gladiator& Y) const {
            if (Y.getScore() > level || (Y.getScore() == level &&
                                         Y.getID() < gladiator_id)) return 1;
            else if (Y.getScore() == level &&
                     Y.getID() == gladiator_id) return 0;
            else return -1;
        }
    };


    //-----------Colosseum Fields--------------------------
    HashChains<TrainingGroup, getTrainingGroupKey> training_groups;
    HashChains<Gladiator, getGladiatorKey> gladiators;
    MinHeap groups_IDs;

public:
//    /**
//     * default Constructor
//     */
//    Colosseum(): training_groups(getTrainingGroupKey()),
//                 gladiators(getGladiatorKey()), groups_IDs(){};

    Colosseum(int n, int* trainingGroupsIDs):
            training_groups(getTrainingGroupKey()),
            gladiators(getGladiatorKey()), groups_IDs(n, trainingGroupsIDs){
        TrainingGroup *init_training_groups = new TrainingGroup[n];
        for(int i=0; i < n ; ++i){
            init_training_groups[i] = TrainingGroup(trainingGroupsIDs[i]);
        }
        training_groups = HashChains<TrainingGroup, getTrainingGroupKey>
                (init_training_groups, n, getTrainingGroupKey());
        delete[] init_training_groups;
    }

    ~Colosseum(){};


    //---------Library2 functions - documented in library2--------------------

    StatusType addTrainingGroup(int groupID);

    StatusType addGladiator(int gladiatorID, int score, int trainingGroup);

    StatusType trainingGroupFight(int trainingGroup1, int trainingGroup2, int k1, int k2);

    int getMinTrainingGroup();

    HashChains<TrainingGroup, getTrainingGroupKey>& getTrainingGroups() {
        return training_groups;
    }

    MinHeap& getGroupsHeap();

    void quit();

};


//class Compare {
//    Gladiator X;
//public:
//    explicit Compare(Gladiator &X) : X(X) {}
//
//    int operator()(const Gladiator &Y) const {
//        return X.compare(Y);
//    }
//};



#endif //WET2_FINAL_COLOSSEUM1_H
