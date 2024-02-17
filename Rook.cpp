#include "Rook.h"

void Rook::setCanCastle(bool castle) {
    canCastle = castle;
}
bool Rook::getCanCastle() const {
    return !canCastle;
}