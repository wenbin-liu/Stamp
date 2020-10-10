///
/// @file   res.cpp
/// @author Yinghai
/// @date   Fri Sep 12 14:21:15 2008
/// 
/// @brief  implementation of Resistor
/// 
/// 
///

#include "res.h"
#include "util.h"

void Resistor::stamp(Matrix& C, Matrix& G, Matrix& B,Matrix& U)
{
  // to be implemented
	Matrix G_dev(2, 2);
	G_dev.set(0, 0, 1 / value());
	G_dev.set(0, 1, -1 / value());
	G_dev.set(1, 0, -1 / value());
	G_dev.set(1, 1, 1 / value());

	int node[2];
	node[0] = pnode();
	node[1] = nnode();
	matStamp(node, node, G_dev, G);



    cout<<_name<<' '<<_pnode<<' '<<_nnode<<' '<<_value<<endl;
}
