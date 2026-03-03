#include "runner.h"
#include "stb_ds.h"

Runner* Runner_create(DataWin* dataWin, VMContext* vm) {
    Runner* runner = malloc(sizeof(Runner));
    runner->dataWin = dataWin;
    runner->vmContext = vm;
    runner->frameCount = 0;

    // You may be asking "why are we setting the arrays to null?"
    // Well, if we don't forcefully initialize them as null, ASan will NOT like it!
    runner->instances = nullptr;

    // GameMaker always starts the game in the first room
    Room* firstRoom = &dataWin->room.rooms[0];
    runner->currentRoom = firstRoom;

    return runner;
}

void Runner_free(Runner* runner) {
    free(runner);
}