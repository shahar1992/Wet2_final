//
// Created by Michal on 06/01/2018.
//

#include "Colosseum.h"

StatusType Colosseum::addTrainingGroup(int trainingGroupID) {
    try{
        TrainingGroup* trainingGroup = new TrainingGroup(trainingGroupID);
        training_groups.insert(*trainingGroup);
        groups_IDs.insert(trainingGroupID);
        delete trainingGroup;
        return SUCCESS;
    }catch (std::bad_alloc& e){
        return ALLOCATION_ERROR;
    } catch (HashExceptions::ElementAlreadyExists& e){
//        delete trainingGroup;         //Need to delete the created TrainingGroup ???? HOW
        return  FAILURE;
    }
}

StatusType Colosseum::addGladiator(int gladiatorID, int score, int trainingGroup) {
    try {
        TrainingGroup* group = this->training_groups.find(trainingGroup);
        Gladiator* gladiator = new Gladiator(gladiatorID, score, trainingGroup);
        gladiators.insert(*gladiator);
        group->getGladiatorsTree()->insert
                (GladiatorCompareByLevelAndID(*gladiator), *gladiator);
        delete gladiator;
        return SUCCESS;
    } catch (HashExceptions::ElementNotFound& e){
        return FAILURE;
    } catch (HashExceptions::ElementAlreadyExists& e){
        //delete gladiator;                         //nedd to be deleted!! HOW??
        return FAILURE;
    } catch (std::bad_alloc& e){
        return ALLOCATION_ERROR;
    }
}

StatusType Colosseum::trainingGroupFight(int trainingGroup1, int trainingGroup2,
                                         int k1, int k2){
    try{
        TrainingGroup *group1 = this->training_groups.find(trainingGroup1);
        TrainingGroup *group2 = this->training_groups.find(trainingGroup2);
        if(group1->getGladiatorsTree()->size < k1 || !group1->isGroupActive() ||
                group2->getGladiatorsTree()->size <k2 || !group2->isGroupActive()
                || group1 == group2)
            return FAILURE;
        int size1 = group1->getGladiatorsTree()->getSumKLeftElements(k1);
        int size2 = group2->getGladiatorsTree()->getSumKLeftElements(k2);
        if(size1 > size2)
            group2->shutDownGroup();
        else if(size1 == size2){
            if(group1->getID() < group2->getID())
                group2 ->shutDownGroup();
            else
                group1->shutDownGroup();
        } else
            group1->shutDownGroup();
        return SUCCESS;
    } catch (HashExceptions::ElementNotFound& e){
            return FAILURE;
    } catch(std::bad_alloc& e){
        return ALLOCATION_ERROR;
    }
}

//StatusType Colosseum::getMinTrainingGroup(int *trainingGroup);
//
////void Colosseum::quit(void** DS);