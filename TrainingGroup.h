//
// Created by edri6 on 05/01/2018.
//

#ifndef WET2_FINAL_TRAININGGROUP_H
#define WET2_FINAL_TRAININGGROUP_H

#include "SplayTree.h"
#include "Gladiator.h"

template<class GetScore>
class TrainingGroup{
    int ID;
    SplayTree<Gladiator, GetScore> gladiators;

public:


    TrainingGroup<GetScore>():ID(), gladiators(){};

    TrainingGroup<GetScore>(int id): ID(id), gladiators(){};

    TrainingGroup<GetScore>(const TrainingGroup<GetScore> &group):
            ID(group.getID()), gladiators(group.getGladiatorTree()){};

    /**
     * Insert a new Gladiator with given id and score.
     * @param gladiator_id
     * @param score
     */
    //void addGladiator(int gladiator_id, int score);

    /**
     * Returns the training group's ID.
     * @return ID.
     */
    int getID() const{
        return ID;
    }

    /**
     * Returns the gladiators Tree of the group
     * @return gladiators
     */
    SplayTree<Gladiator,GetScore> getGladiatorTree() const{
        return gladiators;
    };

};


#endif //WET2_FINAL_TRAININGGROUP_H
