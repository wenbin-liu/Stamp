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

void Isrc::stamp(Matrix& C, Matrix& G, Matrix& B,Matrix &U)
{
	
	int srcNum = srcNode();
	Matrix B_dev(2, 1);
	// the direction is wrong
	B_dev.set(0, 0, 1);
	B_dev.set(1, 0, -1);
	int node[2],nodeSrc[1];
	node[0] = pnode() - 1;
	node[1] = nnode() - 1;
	nodeSrc[0] = srcNum;
	matStamp(node, nodeSrc, B_dev, B);
	U.set(srcNum, 0, value());
  // to be implemented
  cout<<_name<<' '<<_pnode<<' '<<_nnode<<' '<<_value<<endl;
}
void Isrc::setSrcNode(int k)
{
	_srcNode = k;
}
int Isrc::srcNode() const
{
	return _srcNode;
}