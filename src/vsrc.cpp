///
/// @file   vsrc.cpp
/// @author Yinghai
/// @date   Fri Sep 12 14:53:40 2008
/// 
/// @brief  implementation of voltage source
/// 
/// 
///


#include "vsrc.h"
#include "util.h"

void Vsrc::stamp(Matrix& C, Matrix& G, Matrix& B,Matrix& U)
{
  // to be implemented
	// The current direction of the voltage source seems to be wrong.So I changed it.
	Matrix G_dev(3,3), B_dev(3,1);
	G_dev.set(0, 2, 1);
	G_dev.set(2, 0, -1);
	G_dev.set(1, 2, -1);
	G_dev.set(2, 1, 1);

	B_dev.set(2, 0, 1);

	int nodes[3];
	nodes[0] = pnode() - 1;
	nodes[1] = nnode() - 1;
	nodes[2] = auxNode() - 1;

	int nodesSrc[1];
	nodesSrc[0] = srcNode();

	matStamp(nodes, nodes, G_dev, G);
	matStamp(nodes, nodesSrc, B_dev, B);
	U.set(srcNode(), 0, value());

	
  cout<<_name<<' '<<_pnode<<' '<<_nnode<<' '<<_value<<endl;
}
void Vsrc::setSrcNode(int k)
{
	_srcNode = k;
}
int Vsrc::srcNode() const
{
	return _srcNode;
}