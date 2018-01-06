//
// Created by Michal on 06/01/2018.
//
//#include "library2.h"
#include "Colosseum.h"


void* init(int n, int *trainingGroupsIDs){
    Colosseum* DS = new Colosseum(n, trainingGroupsIDs);
    return (void*)DS;
}

StatusType addTrainingGroup(void *DS, int trainingGroupID){
    if(DS == NULL || trainingGroupID < 0)
        return INVALID_INPUT;
    return ((Colosseum*)DS)->addTrainingGroup(trainingGroupID);
}

StatusType addGladiator(void *DS, int gladiatorID, int score, int trainingGroup){
    if(DS == NULL || gladiatorID < 0 || trainingGroup < 0 ||
            score < 0 || score > 100)
        return INVALID_INPUT;
    return ((Colosseum*)DS)->addGladiator(gladiatorID, score, trainingGroup);
}

StatusType trainingGroupFight(void *DS, int trainingGroup1, int trainingGroup2,
                              int k1, int k2){
    if(DS == NULL || trainingGroup1 < 0 || trainingGroup2 < 0 ||
            k1 <= 0 || k2 <= 0)
        return INVALID_INPUT;
    return ((Colosseum*)DS)->trainingGroupFight(trainingGroup1, trainingGroup2,
                                k1, k2);
}

//StatusType getMinTrainingGroup(void *DS, int *trainingGroup);
//
//void quit(void** DS);
