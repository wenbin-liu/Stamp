///
/// @file   mut.cpp
/// @author Yinghai
/// @date   Fri Sep 12 15:06:23 2008
/// 
/// @brief  implementation of mutual inductance
/// 
/// 
///

#include "mut.h"
#include "util.h"

void Mutual::stamp(Matrix& C, Matrix& G, Matrix& B,Matrix &U)
{
  // to be implemented
	Matrix C_dev(2, 2);
	C_dev.set(0, 1, -value());
	C_dev.set(1, 0, -value());
	
	int nodes[2];
	nodes[0] = auxPosNode() - 1;
	nodes[1] = auxNegNode() - 1;

	matStamp(nodes, nodes, C_dev, C);

  cout<<_name<<' '<<_ind1<<' '<<_ind2<<' '<<_value<<endl;
}
