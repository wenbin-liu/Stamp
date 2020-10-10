///
/// @file   cap.cpp
/// @author Yinghai
/// @date   Fri Sep 12 14:25:35 2008
/// 
/// @brief  implementation of Capacitor
/// 
/// 
///

#include "cap.h"
#include "util.h"

void Capacitor::stamp(Matrix& C, Matrix& G, Matrix& B)
{
  // to be implemented
	Matrix C_dev(2,2);
	C_dev.set(0, 0, value());
	C_dev.set(0, 1, -value());
	C_dev.set(1, 0, -value());
	C_dev.set(1, 1, value());

	int node[2];
	node[0] = pnode();
	node[1] = nnode();
	matStamp(node, node, C_dev, C);
  cout<<_name<<' '<<_pnode<<' '<<_nnode<<' '<<_value<<endl;
}


