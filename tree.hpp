#ifndef TREE_H
#define TREE_H
#include "vector.hpp"
#include "particle.hpp"
#include <vector>

class Tree{

	vectr center, radius;
	Tree *child[8];
	partcl *data;
public:
	Tree();
	~Tree();
	Tree( vectr point, vectr half);
	int quadrant(partcl *p);
	bool ifLeaf() const;
	void insert(partcl *point);
	void discPoints( vectr minr, vectr maxr, std::vector<partcl *> &results);
};


#endif
