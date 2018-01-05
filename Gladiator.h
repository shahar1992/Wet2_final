
#ifndef WET2_FINAL_GLADIATORS_H
#define WET2_FINAL_GLADIATORS_H


class Gladiator {
    int ID;
    int score;
    int training_group_ID;
public:
    /**
 * Constructor
 */
    Gladiator(int gladiatorID, int score,int training_group_ID);

    /**
     * default constructor
     */
    Gladiator();

    Gladiator(const Gladiator& X);

    /**
     * Function that returns the score of the gladiator
     * @return score
     */
    int getScore() const;

    void setScore(const int new_score);

    /**
     * Function that returns the ID of the gladiator
     * @return gladiator_id
     */
    int getID() const;

    void setID(const int new_ID);

    /**
     * Returns a pointer to the trainer of the gladiator
     * @return Trainer
     */
    int getTrainingGroup() const;

    /**
     * Function that sets the trainer for a gladiator
     * @return Trainer
     */
    void setTrainingGroup(int Training_group_ID);

    /**
     * Comapring the current Gladiator with the given one.
     * @param X The given gladiator.
     * @return positive number if current gladiator comes first, negative number
     * if given gladiator fomes first, and 0 if equals.
     */
    int compare(const Gladiator& X) const;

};


#endif //WET2_FINAL_GLADIATORS_H