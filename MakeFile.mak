all: Makefile forces

forces: treeForces.cpp tree.cpp particle.cpp vector.cpp 
	g++ -g -Wall vector.cpp particle.cpp tree.cpp treeForces.cpp -o forces

clean:
	rm -f forces
