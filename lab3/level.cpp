#include "level.h"
#include <stdexcept>
#include <QFile>
#include <QTextStream>
#include <iostream>

FieldType Level::QCharToFieldTypeConvertion(QChar ch) {
    switch(ch.toLatin1()) {
        case '#':
            return FieldType::WALL;
        case '@'  :
            return FieldType::PLAYER;
        case '+':
            return FieldType::PLAYER_ON_GOAL;
        case 'o':
            return FieldType::BOX;
        case '*':
            return FieldType::BOX_ON_GOAL;
        case '.':
            return FieldType::GOAL;
        case ' ':
            return FieldType::EMPTY;
        default:
            throw std::invalid_argument("Invalid game field");
        }
}

QString Level::GetLvlPath(int lvlNum)
{
    QString path = "C:/Users/Pepega/Documents/Qt/Lab3/Levels/";
    path += QString::number(lvlNum);
    path += ".txt";
    return path;
}

Level::Level(int lvlNum)
{
    load(lvlNum);
}


FieldType Level::ObjAfterMoving()
{
    if(isPlayerOnGoal_) {
        isPlayerOnGoal_ = false;
        return FieldType::GOAL;
    }
    return FieldType::EMPTY;
}

void Level::MoveUp()
{
    unsigned x = playerPos_.first;
    unsigned y = playerPos_.second;
    //    std::cout << x << " " << y << " || ";
    switch(gameField_[x - 1][y]) {
    case FieldType::EMPTY:
            gameField_[x][y] = ObjAfterMoving();
            gameField_[x - 1][y] = FieldType::PLAYER;
            playerPos_.first = x - 1;
            playerPos_.second = y;
            break;
    case FieldType::GOAL:
            gameField_[x][y] = ObjAfterMoving();
            gameField_[x-1][y] = FieldType::PLAYER_ON_GOAL;
            isPlayerOnGoal_ = true;
            playerPos_.first = x - 1;
            playerPos_.second = y;
            break;
    case FieldType::BOX:
            switch(gameField_[x - 2][y]) {
            case FieldType::EMPTY:
                gameField_[x - 2][y] = FieldType::BOX;
                gameField_[x - 1][y] = FieldType::PLAYER;
                gameField_[x][y] = ObjAfterMoving();
                playerPos_.first = x - 1;
                playerPos_.second = y;
                break;
            case FieldType::GOAL:
                gameField_[x - 2][y] = FieldType::BOX_ON_GOAL;
                gameField_[x - 1][y] = FieldType::PLAYER;
                gameField_[x][y] = ObjAfterMoving();
                ++boxOnGoalNum_;
                playerPos_.first = x - 1;
                playerPos_.second = y;
                break;
            }
            break;
    case FieldType::BOX_ON_GOAL:
            switch(gameField_[x - 2][y]) {
            case FieldType::EMPTY:
                gameField_[x - 2][y] = FieldType::BOX;
                gameField_[x - 1][y] = FieldType::PLAYER_ON_GOAL;
                gameField_[x][y] = ObjAfterMoving();
                --boxOnGoalNum_;
                isPlayerOnGoal_ = true;
                playerPos_.first = x - 1;
                playerPos_.second = y;
                break;
            case FieldType::GOAL:
                gameField_[x - 2][y] = FieldType::BOX_ON_GOAL;
                gameField_[x - 1][y] = FieldType::PLAYER_ON_GOAL;
                gameField_[x][y] = ObjAfterMoving();
                isPlayerOnGoal_ = true;
                playerPos_.first = x - 1;
                playerPos_.second = y;
                break;
            }
            break;
        }
}


void Level::MoveDown()
{
    unsigned x = playerPos_.first;
    unsigned y = playerPos_.second;
    //    std::cout << x << " " << y << " || ";
    switch(gameField_[x + 1][y]) {
    case FieldType::EMPTY:
        gameField_[x][y] = ObjAfterMoving();
        gameField_[x + 1][y] = FieldType::PLAYER;
        playerPos_.first = x + 1;
        playerPos_.second = y;
        break;
    case FieldType::GOAL:
        gameField_[x][y] = ObjAfterMoving();
        gameField_[x+1][y] = FieldType::PLAYER_ON_GOAL;
        isPlayerOnGoal_ = true;
        playerPos_.first = x + 1;
        playerPos_.second = y;
        break;
    case FieldType::BOX:
        switch(gameField_[x + 2][y]) {
        case FieldType::EMPTY:
            gameField_[x + 2][y] = FieldType::BOX;
            gameField_[x + 1][y] = FieldType::PLAYER;
            gameField_[x][y] = ObjAfterMoving();
            playerPos_.first = x + 1;
            playerPos_.second = y;
            break;
        case FieldType::GOAL:
            gameField_[x + 2][y] = FieldType::BOX_ON_GOAL;
            gameField_[x + 1][y] = FieldType::PLAYER;
            gameField_[x][y] = ObjAfterMoving();
            ++boxOnGoalNum_;
            playerPos_.first = x + 1;
            playerPos_.second = y;
            break;
        }
        break;
    case FieldType::BOX_ON_GOAL:
        switch(gameField_[x + 2][y]) {
        case FieldType::EMPTY:
            gameField_[x + 2][y] = FieldType::BOX;
            gameField_[x + 1][y] = FieldType::PLAYER_ON_GOAL;
            gameField_[x][y] = ObjAfterMoving();
            --boxOnGoalNum_;
            isPlayerOnGoal_ = true;
            playerPos_.first = x + 1;
            playerPos_.second = y;
            break;
        case FieldType::GOAL:
            gameField_[x + 2][y] = FieldType::BOX_ON_GOAL;
            gameField_[x + 1][y] = FieldType::PLAYER_ON_GOAL;
            gameField_[x][y] = ObjAfterMoving();
            isPlayerOnGoal_ = true;
            playerPos_.first = x + 1;
            playerPos_.second = y;
            break;
        }
        break;
    }
}

void Level::MoveLeft()
{
    unsigned x = playerPos_.first;
    unsigned y = playerPos_.second;
    //    std::cout << x << " " << y << " || ";
    switch(gameField_[x][y - 1]) {
    case FieldType::EMPTY:
        gameField_[x][y] = ObjAfterMoving();
        gameField_[x][y - 1] = FieldType::PLAYER;
        playerPos_.first = x;
        playerPos_.second = y - 1;
        break;
    case FieldType::GOAL:
        gameField_[x][y] = ObjAfterMoving();
        gameField_[x][y-1] = FieldType::PLAYER_ON_GOAL;
        isPlayerOnGoal_ = true;
        playerPos_.first = x;
        playerPos_.second = y - 1;
        break;
    case FieldType::BOX:
        switch(gameField_[x][y - 2]) {
        case FieldType::EMPTY:
            gameField_[x][y-2] = FieldType::BOX;
            gameField_[x][y-1] = FieldType::PLAYER;
            gameField_[x][y] = ObjAfterMoving();
            playerPos_.first = x;
            playerPos_.second = y - 1;
            break;
        case FieldType::GOAL:
            gameField_[x][y-2] = FieldType::BOX_ON_GOAL;
            gameField_[x][y-1] = FieldType::PLAYER;
            gameField_[x][y] = ObjAfterMoving();
            ++boxOnGoalNum_;
            playerPos_.first = x;
            playerPos_.second = y - 1;
            break;
        }
        break;
    case FieldType::BOX_ON_GOAL:
        switch(gameField_[x][y-2]) {
        case FieldType::EMPTY:
            gameField_[x][y-2] = FieldType::BOX;
            gameField_[x][y-1] = FieldType::PLAYER_ON_GOAL;
            gameField_[x][y] = ObjAfterMoving();
            --boxOnGoalNum_;
            isPlayerOnGoal_ = true;
            playerPos_.first = x;
            playerPos_.second = y - 1;
            break;
        case FieldType::GOAL:
            gameField_[x][y-2] = FieldType::BOX_ON_GOAL;
            gameField_[x][y-1] = FieldType::PLAYER_ON_GOAL;
            gameField_[x][y] = ObjAfterMoving();
            isPlayerOnGoal_ = true;
            playerPos_.first = x;
            playerPos_.second = y-1;
            break;
        }
        break;
    }
}

void Level::MoveRight()
{
    unsigned x = playerPos_.first;
    unsigned y = playerPos_.second;
    //    std::cout << x << " " << y << " || ";
    switch(gameField_[x][y + 1]) {
    case FieldType::EMPTY:
        gameField_[x][y] = ObjAfterMoving();
        gameField_[x][y + 1] = FieldType::PLAYER;
        playerPos_.first = x;
        playerPos_.second = y + 1;
        break;
    case FieldType::GOAL:
        gameField_[x][y] = ObjAfterMoving();
        gameField_[x][y+1] = FieldType::PLAYER_ON_GOAL;
        isPlayerOnGoal_ = true;
        playerPos_.first = x;
        playerPos_.second = y + 1;
        break;
    case FieldType::BOX:
        switch(gameField_[x][y + 2]) {
        case FieldType::EMPTY:
            gameField_[x][y+2] = FieldType::BOX;
            gameField_[x][y+1] = FieldType::PLAYER;
            gameField_[x][y] = ObjAfterMoving();
            playerPos_.first = x;
            playerPos_.second = y + 1;
            break;
        case FieldType::GOAL:
            gameField_[x][y+2] = FieldType::BOX_ON_GOAL;
            gameField_[x][y+1] = FieldType::PLAYER;
            gameField_[x][y] = ObjAfterMoving();
            ++boxOnGoalNum_;
            playerPos_.first = x;
            playerPos_.second = y + 1;
            break;
        }
        break;
    case FieldType::BOX_ON_GOAL:
        switch(gameField_[x][y+2]) {
        case FieldType::EMPTY:
            gameField_[x][y+2] = FieldType::BOX;
            gameField_[x][y+1] = FieldType::PLAYER_ON_GOAL;
            gameField_[x][y] = ObjAfterMoving();
            --boxOnGoalNum_;
            isPlayerOnGoal_ = true;
            playerPos_.first = x;
            playerPos_.second = y + 1;
            break;
        case FieldType::GOAL:
            gameField_[x][y+2] = FieldType::BOX_ON_GOAL;
            gameField_[x][y+1] = FieldType::PLAYER_ON_GOAL;
            gameField_[x][y] = ObjAfterMoving();
            isPlayerOnGoal_ = true;
            playerPos_.first = x;
            playerPos_.second = y+1;
            break;
        }
        break;
    }
}

void Level::load(int lvlNum)
{
    gameField_.clear();

    QString path = GetLvlPath(lvlNum);
    QFile lvlFile(path);

    if(lvlFile.open(QIODevice::ReadOnly| QIODevice::Text)) {
            QString str;

            QTextStream stream(&lvlFile);
            do {
                str = stream.readLine();
                std::vector<FieldType> tmpGameField;
                unsigned tmpMaxColumnNum = 0;
                for(size_t j = 0; j < str.size(); ++j) {
                    FieldType obj = QCharToFieldTypeConvertion(str[j]);

                    IncrementData(obj);
                    if(obj == FieldType::PLAYER || obj == FieldType::PLAYER_ON_GOAL) {
                        playerPos_.first = lineNum_;
                        playerPos_.second = j;
                    }
                    tmpGameField.push_back(obj);
                    ++tmpMaxColumnNum;
                }
                gameField_.push_back(tmpGameField);
                if(tmpMaxColumnNum > maxColumnNum_) {
                    maxColumnNum_ = tmpMaxColumnNum;
                }

                ++lineNum_;
            }while(!str.isNull());

            for(size_t i = 0; i < lineNum_; ++i) {
                while(gameField_[i].size() < maxColumnNum_) {
                    gameField_[i].push_back(FieldType::EMPTY);
                }
            }
    }

    lvlFile.close();
}

const unsigned int Level::GetLineNumb()
{
    return lineNum_;
}

std::vector<FieldType>::iterator Level::Begin(unsigned lineNum)
{
    return gameField_[lineNum].begin();
}

std::vector<FieldType>::iterator Level::End(unsigned lineNum)
{
    return gameField_[lineNum].end();
}

void Level::IncrementData(const FieldType& obj)
{
    switch(obj) {
    case FieldType::BOX_ON_GOAL:
            ++boxOnGoalNum_;
            break;
    case FieldType::GOAL:
            ++goalNum_;
            break;
    case FieldType::PLAYER_ON_GOAL:
            isPlayerOnGoal_ = true;
            break;
    case FieldType::PLAYER:
            isPlayerOnGoal_ = false;
    }
}
