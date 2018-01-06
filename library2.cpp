
#include "Colosseum.h"


void* init(int n, int *trainingGroupsIDs){
    try{
        Colosseum* DS = new Colosseum(n, trainingGroupsIDs);
        return (void*)DS;
    } catch(std::bad_alloc& e){
        return NULL;
    }

}

StatusType addTrainingGroup(void *DS, int trainingGroupID){
    if(!DS || trainingGroupID < 0)
        return INVALID_INPUT;
    return ((Colosseum*)DS)->addTrainingGroup(trainingGroupID);
}

StatusType addGladiator(void *DS, int gladiatorID, int score, int trainingGroup){
    if(!DS || gladiatorID < 0 || trainingGroup < 0 ||
            score < 0 || score > 100)
        return INVALID_INPUT;
    return ((Colosseum*)DS)->addGladiator(gladiatorID, score, trainingGroup);
}

StatusType trainingGroupFight(void *DS, int trainingGroup1, int trainingGroup2,
                              int k1, int k2){
    if(!DS || trainingGroup1 < 0 || trainingGroup2 < 0 || k1 <= 0 || k2 <= 0)
        return INVALID_INPUT;
    return ((Colosseum*)DS)->trainingGroupFight(trainingGroup1, trainingGroup2,
                                k1, k2);
}

StatusType getMinTrainingGroup(void *DS, int *trainingGroup){
    if(!DS || !trainingGroup) return INVALID_INPUT;
    try {
        *trainingGroup = ((Colosseum*)DS)->getMinTrainingGroup();
    }
    catch (...){
        return FAILURE;
    }
    return SUCCESS;
}

void quit(void** DS){
    if (!DS) return;
    delete (Colosseum*)*DS;
    *DS = NULL;
}
