#include "gtest/gtest.h"
#include "Pool.h"

TEST(Pool, Allocate)
{
    Pool<int> pool;
    int* obj = pool.Allocate();
    *obj = 25;
    int* obj2 = pool.Allocate();
    ASSERT_NE(obj, obj2);
    *obj2 = 1;
}

TEST(Pool, Reuse)
{
    Pool<int> pool;
    int* obj = pool.Allocate();
    *obj = 25;
    int* obj2 = pool.Allocate();
    *obj2 = 1;
    pool.Free(obj);

    int* obj3 = pool.Allocate();
    ASSERT_NE(obj2, obj3);
    ASSERT_EQ(obj, obj3);

    int* obj4 = pool.Allocate();
    ASSERT_NE(obj, obj4);
    ASSERT_NE(obj3, obj4);
    ASSERT_NE(obj2, obj4);  
    
}

TEST(Pool, AllocateMany)
{
    int* ids[1000];
    Pool<int> pool;
    int* obj;
    for (int i = 0; i < 1000; ++i)
    {
        ids[i] = pool.Allocate();
    }
    pool.Free(ids[500]);
    obj = pool.Allocate();
    ASSERT_EQ(obj, ids[500]);         
}