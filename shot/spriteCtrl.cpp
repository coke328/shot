#include "spriteCtrl.h"

void insertion_sort(int* seq,int n) {
	int i, j, key;
	for (i = 1; i < n; i++) {
		key = seq[i];
		for (j = i - 1; j >= 0 && sprite::sprites.at(seq[j])->depth > sprite::sprites.at(key)->depth; j--) {
			seq[j + 1] = seq[j];
		}
		seq[j + 1] = key;
	}
}

void spriteCtrl::load() {
	p = new player();
	p->playerInit(200, 0);
	sprite::sprites.emplace_back(&p->head);
	sprite::sprites.emplace_back(&p->body);
	sprite::sprites.emplace_back(&p->leftleg);
	sprite::sprites.emplace_back(&p->rightleg);

	int n = sprite::sprites.size();
	sequence = new int[n];
	for (int i = 0; i < n; i++) {
		sequence[i] = i;
	}
	
	sprite::cnt = n;
	insertion_sort(sequence, n);
	
}

void spriteCtrl::spritesDraw()
{
	if (sprite::cnt != sprite::sprites.size()) {
		delete[] sequence;
		sprite::cnt = sprite::sprites.size();
		sequence = new int[sprite::cnt];
		for (int i = 0; i < sprite::cnt; i++) {
			sequence[i] = i;
		}
		for (int i = 0; i < sprite::sprites.size(); i++) {
			sprite::sprites.at(i)->setspId(i);
		}
		//std::cout << "spriteC:" << sprite::cnt << std::endl;
	}
	//std::cout << (sprite::cnt == sprite::sprites.size()) << std::endl;
	insertion_sort(sequence, sprite::cnt);
	for (int i = 0; i < sprite::cnt; i++) {
		sprite::sprites.at(sequence[i])->drawTexture();
	}
}

void spriteCtrl::spritesUnload()
{
	for (int i = 0; i < sprite::sprites.size(); i++) {
		sprite::sprites[i]->unloadTexture();
	}
	delete p;
	delete[] sequence;
}

void spriteCtrl::spritesUpdate()
{
	
	for (int i = 0; i < sprite::sprites.size(); i++) {
		sprite::sprites.at(i)->update();
	}
}
