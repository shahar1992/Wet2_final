//
// Created by edri6 on 05/01/2018.
//

#ifndef WET2_FINAL_TRAININGGROUP_H
#define WET2_FINAL_TRAININGGROUP_H

#include "SplayTree.h"
#include "Gladiator.h"
#include "SplayTree.h"

class GetScore {
    int score;
public:
    explicit GetScore(const Gladiator &X) : score(X.getScore()) {};

    int operator()() const {
        return score;
    }
};

class TrainingGroup {


    int ID;
    SplayTree<Gladiator, GetScore> gladiators;

public:

    TrainingGroup();

    TrainingGroup(int id);

    TrainingGroup(const TrainingGroup &group);

    /**
     * Insert a new Gladiator with given id and score.
     * @param gladiator_id
     * @param score
     */
    void addGladiator(int gladiator_id, int score);

    /**
     * Returns the training group's ID.
     * @return ID.
     */
    int getID() const;

    SplayTree<Gladiator,GetScore> getGladiatorTree()const;

};


#endif //WET2_FINAL_TRAININGGROUP_H
