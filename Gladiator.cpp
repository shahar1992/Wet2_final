

#include "Gladiator.h"

Gladiator::Gladiator(int gladiatorID, int score, int training_group_ID) :
        ID(gladiatorID), score(score), training_group_ID(training_group_ID) {}

Gladiator::Gladiator() : ID(), score(), training_group_ID() {};

Gladiator::Gladiator(const Gladiator &X): ID(X.getID()), score(X.getScore()),
                                  training_group_ID(X.getTrainingGroup()) {}

int Gladiator::getScore() const {
    return score;
}

void Gladiator::setScore(const int new_score) {
    score = new_score;
    return;
}

int Gladiator::getID() const {
    return ID;
}

void Gladiator::setID(const int new_ID) {
    ID = new_ID;
    return;
}

int Gladiator::getTrainingGroup() const {
    return training_group_ID;
}

void Gladiator::setTrainingGroup(int training_group_ID) {
    this->training_group_ID = training_group_ID;
}

int Gladiator::compare(const Gladiator &X) const{
    if (ID == X.getID()) return 0;
    else if (score > X.getScore()) return 1;
    else if (score < X.getScore()) return -1;
    else if (ID < X.getID()) return 1;
    else return -1;
}