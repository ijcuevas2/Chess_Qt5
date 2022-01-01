//
// Created by ismael on 9/29/21.
//

#include "../headers/ChessPieces/ChessPiece.h"
#include "../headers/ChessMovementMediator.h"
#include <cmath>

ChessPiece::ChessPiece(PlayerID playerId, PieceType pieceType) : QObject(), QGraphicsPixmapItem() {
    this->playerId = playerId;
    this->pieceType = pieceType;
    this->setChessPieceImagePath();
    this->setPos(4.0, 4.0);
}

int ChessPiece::actualDistance(int source, int dest) {
    return source - dest;
}

int ChessPiece::absoluteDistance(int source, int dest) {
    return std::abs(actualDistance(source, dest));
}

PieceType ChessPiece::getPieceType() {
    return this->pieceType;
}

PlayerID ChessPiece::getPlayerId() {
    return playerId;
}

// REFACTOR THIS FUNCTION
int ChessPiece::stepTowardSourceSpaceHelper(int value) {
    if (value == 0) {
        return 0;
    }

    if (value < 0) {
        return -1;
    }

    return 1;
}

void ChessPiece::stepTowardSourceSpace(int & xDistance, int & yDistance) {
    int xStep = stepTowardSourceSpaceHelper(xDistance);
    int yStep = stepTowardSourceSpaceHelper(yDistance);

    xDistance += xStep;
    yDistance += yStep;
}

bool ChessPiece::isPieceBlockingPath(Coordinates coordinates) {
    if (pieceType != PieceType::KNIGHT) {
        int xDistance = actualDistance(coordinates.sourceX, coordinates.destX);
        int yDistance = actualDistance(coordinates.sourceY, coordinates.destY);
        stepTowardSourceSpace(xDistance, yDistance);
        while (xDistance != 0 || yDistance != 0) {
            int xStepIndex = coordinates.sourceX + xDistance;
            int yStepIndex = coordinates.sourceY + yDistance;
            bool isBoardIndexOccupiedValue = ChessMovementMediator::isBoardIndexOccupied(xStepIndex, yStepIndex);
            if (isBoardIndexOccupiedValue) {
                return false;
            }

            stepTowardSourceSpace(xDistance, yDistance);
        }
    }
}

bool ChessPiece::canMove(Coordinates coordinates) {
    if (coordinates.sourceX < 0 || coordinates.sourceX > 7) {
        return false;
    }

    if (coordinates.sourceY < 0 || coordinates.sourceY > 7) {
        return false;
    }

    if (coordinates.destX < 0 || coordinates.destX > 7) {
        return false;
    }

    if (coordinates.destY < 0 || coordinates.destY > 7) {
        return false;
    }

    return true;
}
