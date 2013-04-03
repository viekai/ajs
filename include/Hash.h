namespace TOOL
{

#define long  st_data_t;
#define uint32_t st_index_t;

typedef int32_t (*CompareFunc) (st_data_t, st_data_t);
typedef st_index_t (*HashFunc) (st_data_t);
typedef int32_t (*ForeachFunc) (st_data_t, st_dada_t args);

class HashTable
{
public:

    struct HashEntry
    {
        st_index_t hashValue;
        st_data_t  data;
        HashEntry* next;
    };

    Hash();
    ~Hash();
    int  insert(st_data_t, st_data_t);
    int  lookup(st_data_t, st_data_t);
    void forEach(ForeachFunc func, st_dada_t args);

private:
    CompareFunc* compare;
    HashFunc*    hash;
    int32_t numBins;
    HashEntry* bins;
};

}

using HashTable;
