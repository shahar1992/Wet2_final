//
// Created by Michal on 06/01/2018.
//

#include "Colosseum.h"

void setNewMinInMinHeap(Colosseum* colosseum);

StatusType Colosseum::addTrainingGroup(int trainingGroupID) {
    try {
        TrainingGroup trainingGroup(trainingGroupID);
        HelpDynamicHashFunc helpFunc;
        training_groups.insert(trainingGroup, helpFunc);
        groups_IDs.insert(trainingGroupID);
        helpFunc(trainingGroup);
        return SUCCESS;
    } catch (std::bad_alloc &e) {
        return ALLOCATION_ERROR;
    } catch (HashExceptions::ElementAlreadyExists &e) {
        return FAILURE;
    }
}

StatusType Colosseum::addGladiator(int gladiatorID, int score, int trainingGroup) {
    try {
        TrainingGroup *group = this->training_groups.find(trainingGroup);
        Gladiator gladiator(gladiatorID, score, trainingGroup);
        gladiators.insert(gladiator, HelpDynamicHashFunc());
        group->getGladiatorsTree()->insert
                (GladiatorCompareByLevelAndID(gladiator), gladiator);
        return SUCCESS;
    } catch (HashExceptions::ElementNotFound &e) {
        return FAILURE;
    } catch (HashExceptions::ElementAlreadyExists &e) {
        return FAILURE;
    } catch (std::bad_alloc &e) {
        return ALLOCATION_ERROR;
    }
}

StatusType Colosseum::trainingGroupFight(int trainingGroup1, int trainingGroup2,
                                         int k1, int k2) {
    try {
        TrainingGroup *group1 = this->training_groups.find(trainingGroup1);
        TrainingGroup *group2 = this->training_groups.find(trainingGroup2);
        if (group1->getGladiatorsTree()->size < k1 ||
            !group1->isGroupActive() ||
            group2->getGladiatorsTree()->size < k2 ||
            !group2->isGroupActive() ||
            trainingGroup1 == trainingGroup2)
            return FAILURE;
        int size1 = group1->getGladiatorsTree()->getSumKLeftElements(k1);
        int size2 = group2->getGladiatorsTree()->getSumKLeftElements(k2);
        if (size1 > size2)
            group2->shutDownGroup();
        else if (size1 == size2) {
            if (group1->getID() < group2->getID())
                group2->shutDownGroup();
            else
                group1->shutDownGroup();
        } else
            group1->shutDownGroup();
        setNewMinInMinHeap(this);
        return SUCCESS;
    } catch (HashExceptions::ElementNotFound &e) {
        return FAILURE;
    } catch (std::bad_alloc &e) {
        return ALLOCATION_ERROR;
    }
}

MinHeap& Colosseum::getGroupsHeap(){
    return this->groups_IDs;
}

void setNewMinInMinHeap(Colosseum* colosseum){
    while (1) {
        int min_id = colosseum->getMinTrainingGroup();
        if (!colosseum->getTrainingGroups().find(min_id)->isGroupActive()) {
            colosseum->getGroupsHeap().delMin();
        } else break;
    }
}

int Colosseum::getMinTrainingGroup() {
    return  groups_IDs.findMIn();
}