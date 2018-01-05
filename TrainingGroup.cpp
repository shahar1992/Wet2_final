
#include "TrainingGroup.h"

class getScore {
    int score;
public:
    explicit getScore(const Gladiator &X) : score(X.getScore()) {};
    int operator()() const {
        return score;
    }
};

class Compare {
    Gladiator X;
public:
    explicit Compare(Gladiator &X) : X(X) {}

    int operator()(const Gladiator &Y) const {
        return X.compare(Y);
    }
};


