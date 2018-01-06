//
// Created by Michal on 06/01/2018.
//

#include "Colosseum.h"


int main() {
    int training_group_ids[8] = {11,15,3,8,32,6,4,7};
    Colosseum colosseum(8, training_group_ids);
    if(colosseum.addTrainingGroup(11) != FAILURE)
        std::cout << "ERROR 1 - 11 already exists" << std::endl;
    if(colosseum.addTrainingGroup(12) != SUCCESS)
        std::cout << "ERROR 2" << std::endl;
    if(colosseum.addTrainingGroup(13) != SUCCESS)
        std::cout << "ERROR 3" << std::endl;
    if(colosseum.addTrainingGroup(14) != SUCCESS)
        std::cout << "ERROR 4" << std::endl;
    if(colosseum.addTrainingGroup(0) != SUCCESS)
        std::cout << "ERROR 5" << std::endl;
    if(colosseum.addGladiator(1,5,11) != SUCCESS)
        std::cout << "ERROR 6" << std::endl;
    if(colosseum.addGladiator(1,5,11) != FAILURE)
        std::cout << "ERROR 7 - gladiator 1 already exists" << std::endl;
    if(colosseum.addGladiator(1,5,9) != FAILURE)
        std::cout << "ERROR 8 - no group 9" << std::endl;
    if(colosseum.addGladiator(2,3,11) != SUCCESS)
        std::cout << "ERROR 9" << std::endl;
    if(colosseum.addGladiator(3,4,11) != SUCCESS)
        std::cout << "ERROR 10" << std::endl;
    if(colosseum.addGladiator(4,5,11) != SUCCESS)
        std::cout << "ERROR 11" << std::endl;
    if(colosseum.addGladiator(5,6,11) != SUCCESS)
        std::cout << "ERROR 12" << std::endl;
    if(colosseum.addGladiator(6,5,12) != SUCCESS)
        std::cout << "ERROR 13" << std::endl;
    if(colosseum.addGladiator(7,3,12) != SUCCESS)
        std::cout << "ERROR 14" << std::endl;
    if(colosseum.addGladiator(8,4,12) != SUCCESS)
        std::cout << "ERROR 15" << std::endl;
    if(colosseum.addGladiator(9,5,12) != SUCCESS)
        std::cout << "ERROR 16" << std::endl;
    if(colosseum.addGladiator(10,6,12) != SUCCESS)
        std::cout << "ERROR 17" << std::endl;
    if(colosseum.trainingGroupFight(11,12,6,2) !=FAILURE)
        std::cout << "ERROR 18" << std::endl;
    if(colosseum.trainingGroupFight(11,11,2,2) !=FAILURE)
        std::cout << "ERROR 20" << std::endl;
    if(colosseum.trainingGroupFight(11,12,2,2) != SUCCESS)
        std::cout << "ERROR 21" << std::endl;





}
