//
// Created by edri6 on 05/01/2018.
//

#ifndef WET2_FINAL_TRAININGGROUP_H
#define WET2_FINAL_TRAININGGROUP_H

#include "SplayTree.h"
#include "Gladiator.h"

class TrainingGroup{
    /**
    * function object to get a gladiators score
    */
    class getScore {
    public:
        explicit getScore(){}
        int operator()(const Gladiator &X) const {
            return X.getScore();
        }
    };
    friend class Colosseum;

    int ID;
    SplayTree<Gladiator, getScore>* gladiators;
    bool active;


public:

    TrainingGroup(): ID(), gladiators(), active(1){};

    TrainingGroup(int id): ID(id), gladiators(), active(1){
        gladiators = new SplayTree<Gladiator, getScore>(getScore());
    };

    ~TrainingGroup(){
        delete this->gladiators;
    }

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
    SplayTree<Gladiator,getScore>* getGladiatorsTree() {
        return gladiators;
    }

    /**
     * Returns the active status of the group
     * @return
     */
    bool isGroupActive(){
        return this->active;
    }

    /**
     * the function makes the training group inactive
     */
    void shutDownGroup(){
        this->active = 0;
    }
};
#endif //WET2_FINAL_TRAININGGROUP_H
