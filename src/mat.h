///
/// @file   mat.h
/// @author 
/// @date   Fri Sep 12 14:06:47 2008
/// 
/// @brief  Header of the Matrix class
/// 
/// 
///

#ifndef MAT_H
#define MAT_H

#include <cstring>
#include <vector>
#include <list>


/// \class Mat 
///
/// \brief the matrix class
///
/// This is an empty class. You have to design you own Matrix class by
/// adding necessary data and public functions. \n
///
/// To facilliate the stamping process, the matrix class needs to satisfy 
/// the following condition:
/// - Dynamic allocation of the memory according to the size of the circuit.
/// - Expandable. Each time we stamp an element, the entries of the matrix may grow.
/// - Flexible and efficient. Most of the entries in the matrix would be zero and we don't need to store them. 
///
/// My advice is: Using orthogonal list data structure. \n
///
/// Currently, this class is designed as a C++ template. If you're not familliar with 
/// the concept of template. Just define a non-template class and do the same thing.
template<class T>
class Mat{
public:

  /// \brief Constructor
  /// \param nrow #rows
  /// \param ncol #columns
  ///
  /// \todo Allocate the memory with given size of the matrix
    std::vector< std::vector<T> > matData;
  Mat(int nrow, int ncol) :_row(nrow),_col(ncol) {
      matData = std::vector<std::vector<T> >(_row, std::vector<T>(_col, 0));
  }


  /// \brief Destructor
  ///
  /// \todo release the allocated memory
  ~Mat(){
    
  }
  
  /// \brief return #rows
  /// \return #rows
  int row() const {return _row;}

  /// \brief return #columns
  /// \return #columns
  int column() const {return _col;}
  void set(int r, int c, T value)
  {
      matData[r][c] = value;
  }
  T get(int r, int c)
  {
      return matData[r][c];
  }

private:
  
  /// \brief #rows
  int _row;
  /// \brief #columns
  int _col;
};

template <class T>
struct SMatNode
{
    int r;
    int c;
    T value;
};

using namespace std;

template<class T>
class SMat
{
public:
    SMat(int nrow, int ncol) :_row(nrow), _col(ncol),_rowVec(nrow,nullptr)
    {
        for (int i = 0; i < nrow; i++)
        {
            _rowVec[i] = new list<SMatNode<T> >;
        }
    }

    /// \brief return #rows
/// \return #rows
    int row() const { return _row; }

    /// \brief return #columns
    /// \return #columns
    int column() const { return _col; }
    void set(int r, int c, T value)
    {
        list<SMatNode<T> > * pHead = _rowVec[r];
        list<SMatNode<T> >::iterator iter,lastIter = pHead->begin();
        for (iter = pHead->begin(); iter != pHead->end() && (*iter).c < c; iter++)
        {
            lastIter = iter;
        }
        SMatNode<T> newNode;
        newNode.r = r;
        newNode.c = c;
        newNode.value = value;
        if (iter == pHead->end())
        {

            pHead->insert(iter, newNode);

        }
        else if((*iter).c == c)
        {
            (*iter).value = value;
        }
        else
        {
            pHead->insert(lastIter, newNode);
        }

    }
    T get(int r, int c)
    {
        list<SMatNode<T> >::iterator iter;
        list<SMatNode<T> >* pHead = _rowVec[r];
        for (iter = pHead->begin(); iter != pHead->end(); iter++)
        {
            if ((*iter).c == c)
            {
                return (*iter).value;
            }
        }
        return (T)0;
    }

    ~SMat()
    {
        for (int i = 0; i < _row; i++)
        {
            delete _rowVec[i];
        }
    }

private:
    int _row, _col;
    vector<list<SMatNode<T> >* > _rowVec;
};


//typedef Mat<double> Matrix;
typedef SMat<double> Matrix;



#endif
