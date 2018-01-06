
#include "TrainingGroup.h"


TrainingGroup::TrainingGroup() : ID(), gladiators() {};

TrainingGroup::TrainingGroup(int id) : ID(id), gladiators() {};

TrainingGroup::TrainingGroup(const TrainingGroup &group) :
        ID(group.getID()), gladiators(group.getGladiatorTree()) {};

class Compare {
    Gladiator X;
public:
    explicit Compare(Gladiator &X) : X(X) {}

    int operator()(const Gladiator &Y) const {
        return X.compare(Y);
    }
};

int TrainingGroup::getID() const{
    return ID;
}

SplayTree<Gladiator,GetScore> TrainingGroup::getGladiatorTree() const{
    return gladiators;
};
