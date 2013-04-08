#include "AJS.h"
#include <string.h>

namespace TOOL
{

#define ST_DEFAULT_MAX_DENSITY 5

typedef long  st_data_t;
typedef uint32_t st_index_t;

typedef int32_t (*CompareFunc) (st_data_t key1, st_data_t key2);
typedef st_index_t (*HashFunc) (st_data_t key);
typedef int32_t (*ForeachFunc) (st_data_t data, st_data_t args);

class HashTable
{
public:

    struct HashEntry
    {
        st_index_t hashVal;
		st_data_t  key;
        st_data_t  record;
        HashEntry* next;
    };

    HashTable(HashFunc hashFunc, CompareFunc cmpFunc, st_index_t size);
    ~HashTable();
    int32_t  insert(st_data_t key, st_data_t value);
    st_data_t  lookup(st_data_t key);
    void forEach(ForeachFunc func, st_data_t args);
	void clear();
	void rehash();
	bool contains(st_data_t key);
	int32_t remove(st_data_t *key, st_data_t *value);
	int32_t remove(st_data_t key);

private:
    CompareFunc _cmpFunc;
    HashFunc    _hashFunc;
    int32_t _numBins;
	int32_t _numEntries;
    HashEntry** _entries;
};

st_index_t strhash(st_data_t key);
int32_t strcompare(st_data_t key1, st_data_t key2);

}

using TOOL::st_data_t;
using TOOL::st_index_t;
using TOOL::strhash;
using TOOL::strcompare;
using TOOL::HashTable;
