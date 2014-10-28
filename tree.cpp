#include <math.h>
#include <stdlib.h>
#include <limits.h>
#include "vector.hpp"
#include "particle.hpp"
#include "tree.hpp"

Tree::Tree()
	{
		center = vectr();
		radius = vectr();
	}

Tree::Tree( vectr point, vectr half)
	{
		int i = 0;
		center = point;
		radius = half;
		data = NULL;
		for(i = 0; i<8; i++)
			child[i] = NULL;
		
	}
	
Tree::~Tree()
{
for(int i = 0; i<8; i++)
		delete child[i];
}
int Tree::quadrant( partcl *p) 
{
			int oct = 0;
			if(p->getPosition().x >= center.x) oct |= 4;
			if(p->getPosition().y >= center.y) oct |= 2;
			if(p->getPosition().z >= center.z) oct |= 1;
			return oct;
}
bool Tree::ifLeaf() const
{

	return child[0] == NULL;
	
}

void Tree::insert(partcl *point)
{

	if(ifLeaf()) {
	//base case: we are currently at the correct leaf node and the node is empty
	//insert the point
		if( data == NULL)
		{
			data = point;
			return;
		}
		else
		{
		//we are at a non-empty leaf node
			partcl *old = data;
			data = NULL;
			
			for(int i = 0; i<8; ++i)
			{
				vectr newcenter = center;
				newcenter.x += radius.x * (i & 4 ? .5f : -.5f); //true for IV,V,VI,VII
				newcenter.y += radius.y * (i & 2 ? .5f : -.5f);//true for II, III, V, VI, VII
				newcenter.z += radius.z *(i & 1 ? .5f : -.5f);//true for odd
				child[i] = new Tree(newcenter, radius * .5f);
			}
			
		child[quadrant(old)]->insert(old);
		child[quadrant(point)]->insert(point);
			
		}
}
	else
	{
		int octant = quadrant(point); 
		child[octant]->insert(point);
	}
}

void Tree::discPoints( vectr minr,  vectr maxr, std::vector<partcl *> &results)
{
int i = 0;
	if(ifLeaf())
	{
		if(data != NULL)
		{
			vectr v = data->getPosition();
			if(v.x > maxr.x || v.y > maxr.y || v.z > maxr.z) 
				return;
			if(v.x < minr.x || v.y < minr.y || v.z < maxr.z) 
				return;
			
			results.push_back(data);
		}
	}
	else
	{
		for(i = 0; i< 8; i++)
		{
			vectr boundarymax = child[i]->center + child[i]->radius;
			vectr boundarymin = child[i]->center - child[i]->radius  ;

			if(boundarymax.x < minr.x || boundarymax.y < minr.y || boundarymax.z < minr.z ) 
				continue;
			if(boundarymin.x > maxr.x || boundarymin.y > maxr.y || boundarymin.z > maxr.z ) 
				continue;
			child[i]->discPoints(minr, maxr, results);
		
		
		}
	}
}
