#ifndef LEVEL_H
#define LEVEL_H

#include <vector>
#include <QString>

enum class FieldType {
    WALL,
    EMPTY,
    PLAYER,
    PLAYER_ON_GOAL,
    BOX,
    BOX_ON_GOAL,
    GOAL
};

class Level
{
public:
    Level() = delete;
    Level(int lvlNum);

    void MoveUp();
    void MoveDown();
    void MoveLeft();
    void MoveRight();

    void load(int lvlNum);
    const unsigned GetLineNumb();

    std::vector<FieldType>::iterator Begin(unsigned lineNum);
    std::vector<FieldType>::iterator End(unsigned lineNum);
private:

    std::vector<std::vector<FieldType>> gameField_;
    std::pair<unsigned, unsigned> playerPos_;
    unsigned lineNum_ = 0;
    unsigned maxColumnNum_= 0;
    unsigned goalNum_;
    unsigned boxOnGoalNum_;
    bool isPlayerOnGoal_;

    FieldType ObjAfterMoving();
    void IncrementData(const FieldType& obj);
    FieldType QCharToFieldTypeConvertion(QChar ch);
    QString GetLvlPath(int lvlNum);
};

#endif // LEVEL_H
