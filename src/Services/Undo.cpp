#include "Undo.h"

void UndoAdauga::doUndo(){
	repo.delete_movie(added_movie);
}

void UndoRemove::doUndo(){
	repo.push_back(removed_movie);
}

void UndoChange::doUndo(){
	repo.change_movie(new_movie, old_movie);
}
