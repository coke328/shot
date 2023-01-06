#include "spriteCtrl.h"
std::vector<sprite*>spriteCtrl::sprites;
int spriteCtrl::activecnt;

void insertion_sort(int* seq,int n) {
	int i, j, key;
	for (i = 1; i < n; i++) {
		key = seq[i];
		for (j = i - 1; j >= 0 && spriteCtrl::sprites[seq[j]]->depth > spriteCtrl::sprites[key]->depth; j--) {
			seq[j + 1] = seq[j];
		}
		seq[j + 1] = key;
	}
}

void spriteCtrl::load() {
	p = new player();
	p->playerInit(200, 0);
	sprites.push_back(&p->head);
	sprites.push_back(&p->body);
	sprites.push_back(&p->leftleg);
	sprites.push_back(&p->rightleg);

	int n = sprites.size();
	sequence = new int[n];
	for (int i = 0; i < n; i++) {
		sequence[i] = i;
	}
	
	activecnt = n;
	insertion_sort(sequence, n);
	
}

void spriteCtrl::spritesDraw()
{
	insertion_sort(sequence, activecnt);
	for (int i = 0; i < activecnt; i++) {
		sprites[sequence[i]]->drawTexture();
	}
}

void spriteCtrl::spritesUnload()
{
	for (int i = 0; i < sprites.size(); i++) {
		sprites[i]->unloadTexture();
	}
}

void spriteCtrl::spritesUpdate()
{
	for (int i = 0; i < sprites.size(); i++) {
		sprites[i]->update();
	}
}
