///
/// @file   isrc.cpp
/// @author Yinghai
/// @date   Fri Sep 12 14:45:16 2008
/// 
/// @brief  implementation of current source
/// 
/// 
///

#include "isrc.h"
#include "util.h"

void Isrc::stamp(Matrix& C, Matrix& G, Matrix& B)
{
	Matrix B_dev(1, 2);
	B_dev.set(0, 0, -value());
	B_dev.set(0, 1, value());
	int node[2];
	node[0] = pnode();
	node[1] = nnode();
	matStamp(node, node, B_dev, B);
  // to be implemented
  cout<<_name<<' '<<_pnode<<' '<<_nnode<<' '<<_value<<endl;
}
