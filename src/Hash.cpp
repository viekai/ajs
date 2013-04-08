#include "Hash.h"
#include <stdlib.h>

namespace TOOL
{

	#define MINSIZE 8
	#define numberof(array) (int)(sizeof(array) / sizeof((array)[0]))	
	#define EQUAL(x,y) ((x)==(y) || (*_cmpFunc)((x),(y)) == 0)
	#define PTR_NOT_EQUAL(ptr, hashVal, key) \
		((ptr) != NULL && ((ptr)->hashVal != (hashVal) || !EQUAL((key), (ptr)->key)))

	/*
	Table of prime numbers 2^n+a, 2<=n<=30.
	*/
	static const unsigned int primes[] = {
		8 + 3,
		16 + 3,
		32 + 5,
		64 + 3,
		128 + 3,
		256 + 27,
		512 + 9,
		1024 + 9,
		2048 + 5,
		4096 + 3,
		8192 + 27,
		16384 + 43,
		32768 + 3,
		65536 + 45,
		131072 + 29,
		262144 + 3,
		524288 + 21,
		1048576 + 7,
		2097152 + 17,
		4194304 + 15,
		8388608 + 9,
		16777216 + 43,
		33554432 + 35,
		67108864 + 15,
		134217728 + 29,
		268435456 + 3,
		536870912 + 11,
		1073741824 + 85,
		0
	};

	static st_index_t new_size(st_index_t size)
	{
		int i;

		st_index_t newsize;

		for (i = 0, newsize = MINSIZE; i < numberof(primes); i++, newsize <<= 1) 
		{
			if (newsize > size) 
				return primes[i];
		}
		return -1;
	}

    HashTable::HashTable(HashFunc hashFunc, CompareFunc cmpFunc, st_index_t size)
		:_hashFunc(hashFunc), _cmpFunc(cmpFunc), _numEntries(0)
    {
    	size = new_size(size);
		_numBins = size;
		_entries = static_cast<HashEntry**>(calloc(size, sizeof(HashEntry*)));
    }

    HashTable::~HashTable()
    {
    	clear();
		free(_entries);
    }

	void HashTable::clear()
	{   
	  HashEntry* entry;
	  for(int32_t i = 0; i < _numBins; i++)
	  {   
		  entry = _entries[i];
		  _entries[i] = NULL;
		  while (entry != NULL)
		  {   
		      HashEntry* next = entry->next;
		      free(entry);
		      entry = next;
		  }
	  }   
	  _numEntries = 0;
	}
  
#define ADD_DIRECT(key, value, hashVal, binPos)\
do {\
    HashEntry* newEntry;\
    if (_numEntries > ST_DEFAULT_MAX_DENSITY * _numBins) {\
		rehash();\
        (binPos) = (hashVal) % _numBins;\
    }\
    \
    newEntry = static_cast<HashEntry*>(malloc(sizeof(HashEntry)));\
    \
    newEntry->hashVal = (hashVal);\
    newEntry->key = (key);\
    newEntry->record = (value);\
    newEntry->next = _entries[(binPos)];\
    _entries[(binPos)] = newEntry;\
    _numEntries++;\
} while (0)

#define FIND_ENTRY(entry, key, hashVal, binPos) do {\
	(hashVal) = (*_hashFunc)(key);\
    (binPos) = (hashVal)%_numBins;\
    (entry) = _entries[(binPos)];\
    while(PTR_NOT_EQUAL(entry, hashVal, key)) {\
	    (entry) = (entry)->next;\
	}\
} while (0)

    int32_t HashTable::insert(st_data_t key, st_data_t value)
    {
		st_index_t hashVal, binPos;
        HashEntry* entry;

		FIND_ENTRY(entry, key, hashVal, binPos);
        if(entry == NULL)
            ADD_DIRECT(key, value, hashVal, binPos);
        else
            entry->record = value;            

        return 1; 
    }

	void HashTable::rehash()
	{
		HashEntry *entry, **newBins;
		st_index_t i, newNumBins, hashVal;

		newNumBins = new_size(_numBins+1);
		newBins = static_cast<HashEntry**>(realloc(_entries, newNumBins * sizeof(HashEntry*)));
		for (i = 0; i < newNumBins; ++i) 
			newBins[i] = NULL;
		
		for(i = 0; i < _numBins; i++)
		{
			entry = _entries[i];
			if(entry != NULL){
				hashVal = entry->hashVal % newNumBins;
				entry->next = newBins[hashVal];
				newBins[hashVal] = entry;
			}
		}

		_numBins = newNumBins;
		_entries = newBins;
	}

    st_data_t HashTable::lookup(st_data_t key)
    {
    	st_index_t hashVal, binPos;
        HashEntry* entry;

		FIND_ENTRY(entry, key, hashVal, binPos);
        if(entry == NULL)
            return 0;
        else
        	return entry->record;
    }

	bool HashTable::contains(st_data_t key)
    {
    	st_index_t hashVal, binPos;
        HashEntry* entry;

		FIND_ENTRY(entry, key, hashVal, binPos);
        if(entry == NULL)
            return false;
        else
        	return true;
    }

	int32_t HashTable::remove(st_data_t *key, st_data_t *value)
	{
		st_index_t hashVal, binPos;
		HashEntry **prev;
		HashEntry *entry;

		hashVal = (*_hashFunc)(*key);
    	binPos = hashVal%_numBins;

		for (prev = &_entries[binPos]; (entry = *prev) != 0; prev = &entry->next) 
		{
			if (EQUAL(*key, entry->key)) {
				*prev = entry->next;
				_numEntries--;
				if (value != NULL) 
					*value = entry->record;
				*key = entry->key;
				free(entry);
				return 1;
			}
		}

		if (value != NULL) *value = 0;
		return 0;
	}

	int32_t HashTable::remove(st_data_t key)
	{
		st_index_t hashVal, binPos;
		HashEntry **prev;
		HashEntry *entry;

		hashVal = (*_hashFunc)(key);
    	binPos = hashVal%_numBins;

		for (prev = &_entries[binPos]; (entry = *prev) != 0; prev = &entry->next) 
		{
			if (EQUAL(key, entry->key)) {
				*prev = entry->next;
				_numEntries--;
				free(entry);
				return 1;
			}
		}

		return 0;
	}

    void HashTable::forEach(ForeachFunc func, st_data_t args)
    {
		HashEntry* entry;
		for(int32_t i = 0; i < _numBins; i++)
		{   
		  entry = _entries[i];
		  while (entry != NULL)
		  {   
			  HashEntry* next = entry->next;
			  func(entry->record, args);
			  entry = next;
		  }
		}   
    }

#define FNV1_32A_INIT 0x811c9dc5
#define FNV_32_PRIME 0x01000193

	st_index_t strhash(st_data_t key)
	{
		register const char *string = (const char *)key;
		register st_index_t hval = FNV1_32A_INIT;

		/*
		 * FNV-1a hash each octet in the buffer
		 */
		while (*string) {
		/* xor the bottom with the current octet */
		hval ^= (unsigned int)*string++;

		/* multiply by the 32 bit FNV magic prime mod 2^32 */
		hval *= FNV_32_PRIME;
		}
		return hval;
	}

	int32_t strcompare(st_data_t key1, st_data_t key2)
	{
		char* str1 = reinterpret_cast<char*>(key1);
		char* str2 = reinterpret_cast<char*>(key2);
		return strcmp(str1, str2);
	}
}
