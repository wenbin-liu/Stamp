///
/// @file   ind.cpp
/// @author Yinghai
/// @date   Fri Sep 12 14:32:59 2008
/// 
/// @brief  implementation of inductor
/// 
/// 
///

#include "ind.h"
#include "util.h"

void Inductor::stamp(Matrix& C, Matrix& G, Matrix& B,Matrix& U)
{
  // to be implemented
	Matrix C_dev(3,3), G_dev(3,3);
	C_dev.set(2, 2, value());
	
	G_dev.set(0, 2, 1);
	G_dev.set(2, 0, -1);
	G_dev.set(1, 2, -1);
	G_dev.set(2, 1, 1);
	int node[3];
	node[0] = pnode() - 1;
	node[1] = nnode() - 1;
	node[2] = auxNode() - 1;
	matStamp(node, node, G_dev, G);
	matStamp(node, node, C_dev, C);


  cout<<_name<<' '<<_pnode<<' '<<_nnode<<' '<<_value<<endl;
}
