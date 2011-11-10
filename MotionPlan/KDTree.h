#ifndef MOTIONPLAN_ASTAR_KDTREE_H_
#define MOTIONPLAN_ASTAR_KDTREE_H_

#include <vector>
#include "MathConstants.h"

#include "Rectangle.h"
#include "Point.h"



namespace AStar
{

template<typename CoordType>
class KDTree
{
private:


    class KDTreeNode
    {
    private:

        bool _leaf;
        KDTreeNode* _left;
        KDTreeNode* _right;
        std::vector<int> _childIds;
        std::vector<Rectangle<CoordType>> _childAreas;

        Rectangle<CoordType> _area;
        Rectangle<CoordType>* _areaMax;

        Rectangle<CoordType> _areaLeft;
        Rectangle<CoordType> _areaRight;


    protected:
        void AddRecursivly(Rectangle<CoordType>& rect, int id)
        {
            if (_areaLeft.IsNeighbor(&rect,0))
            {
                _left->Add(rect, id);
            }
            //its possibler that 1 rect will be in 2 leafs
            if (_areaRight.IsNeighbor(&rect,0))
            {
                _right->Add(rect, id);
            }
        }

        KDTreeNode* GetKDTreeNodeRecursivly(const Point<CoordType>& point)
        {
            KDTreeNode* result = this;
            while (!result->_leaf)
            {
                result = result->GetNode(point);                
            }
            return result;
        }

        inline KDTreeNode* GetNode(const Point<CoordType>& point)
        {
            KDTreeNode* result = this;
            if (!_leaf)
            {
                if (_areaLeft->On(point))
                {
                    result = _left;
                }
                else
                {
                    result = _right;
                }
            }
            return result;
        }                

        bool On(Rectangle<CoordType> rect)
        {
            return _area.IsNeighbor(&rect,0);
        }

        bool On(Point<CoordType> point)
        {
            return _area.IsInside(point);
        }

    public:


        KDTreeNode(Rectangle<CoordType>* areaMax)
        {
            _areaMax = areaMax;
            _area = Rectangle<CoordType>(Point<CoordType>::Zero(), Point<CoordType>::Zero() );
            _left=NULL;
            _right=NULL;
            _leaf=true;
        }

        ~KDTreeNode()
        {
            if (_left!=NULL)
            {
                delete _left;
            }
            if (_right!=NULL)
            {
                delete _right;
            }
        }    

        void Add(Rectangle<CoordType> rect, int id)
        {
            //if (!_leaf)
            //{
            //    AddRecursivly(rect, id);
            //}
            //else
            //{
                _childAreas.push_back(rect);
                _childIds.push_back(id);
                _area = _area.GetUnion(&rect);
                if (_areaMax!= NULL)
                {
                    _area = _area.GetIntersection(_areaMax,0); 
                }
            //    if (_childIds.size() > BULK_SIZE)
            //    {
            //        Split();
            //    }
            //}
        }
        
        int GetId(const Point<CoordType>& point)
        {
            int result;
            KDTreeNode* node = GetKDTreeNodeRecursivly(point);
            int count = node->_childIds.size();
            for (int i = 0; i < count; ++i)
            {
                if (node->_childAreas[i].IsInside(point))
                {
                    result = node->_childIds[i];
                    break;
                }
            }
            return result;
        }

        void Build()
        {
            //already done
            if (_left!=NULL || _right != NULL)
                return;
            //too small
            if (_childIds.size() <= BULK_SIZE)
                return;

            Point<CoordType> size = _area.GetSize();
            Point<CoordType> leftEndPoint = _area.GetRightBottomPoint();
            Point<CoordType> rightStartPoint = _area.GetLeftTopPoint();
            //split vertical
            if (size.X>size.Y)
            {
                leftEndPoint.X = _area.GetCenter().X;
                rightStartPoint.X = _area.GetCenter().X;
            }
            else
            {
                leftEndPoint.Y = _area.GetCenter().Y;
                rightStartPoint.Y = _area.GetCenter().Y;
            }

            _areaLeft= Rectangle<CoordType>( _area.GetLeftTopPoint(),leftEndPoint);
            _left = new KDTreeNode(_areaLeft);

            _areaRight = Rectangle<CoordType>( rightStartPoint, _area.GetRightBottomPoint());
            _right = new KDTreeNode(&_areaRight);

            _leaf = false;
            int count = _childIds.size();
            for (int i = 0; i < count; ++i)
            {
                AddRecursivly(_childAreas[i], _childIds[i]);
            }
            _left->Build();
            _right->Build();

            _childIds.clear();
            _childAreas.clear();
        }

    };

protected:
    KDTreeNode* _root;

public:
    static const int BULK_SIZE = 3;
    KDTree()
    {
        _root = new KDTreeNode(NULL);
    }
    ~KDTree()
    {
        delete _root;
    }
    
    void Add(Rectangle<CoordType> rect, int id)
    {
        _root->Add(rect, id);
    }
    int GetId(const Point<CoordType>& point)
    {
        _root->GetId(point);
    }
    void Build()
    {
        _root->Build();
    }


};

#include "KDTree.inl"
}

#endif //MOTIONPLAN_ASTAR_KDTREE_H_