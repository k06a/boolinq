boolinq 2.0
=======

C++ header-only Ranges and LINQ template library

Just imagine LINQ support for STL/Qt collections :)

Get source code here: **[boolinq.h](https://github.com/k06a/boolinq/blob/master/include/boolinq/boolinq.h)**

###How it looks like?

####Example with integers

```
int src[] = {1,2,3,4,5,6,7,8};
auto dst = from(src).where( [](int a){return a%2 == 1;})    // 1,3,5,7
                    .select([](int a){return a*2;})         // 2,6,10,14
                    .where( [](int a){return a>2 && a<12;}) // 6,10
                    .toVector();

// dst type: std::vector<int>
// dst items: 6,10
```

####Example with structs

```
struct Man
{
    std::string name;
    int age;
};

Man src[] =
{
    {"Kevin",14},
    {"Anton",18},
    {"Agata",17},
    {"Terra",20},
    {"Layer",15},
};

auto dst = from(src).where(  [](const Man & man){return man.age < 18;})
                    .orderBy([](const Man & man){return man.age;})
                    .select( [](const Man & man){return man.name;})
                    .toVector();

// dst type: std::vector<std::string>
// dst items: "Kevin", "Layer", "Agata"
```

####Interesting example

```
struct Message
{
    std::string PhoneA;
    std::string PhoneB;
    std::string Text;
};

Message messages[] =
{
    {"Anton","Troll","Hello, friend!"},
    {"Denis","Wride","OLOLO"},
    {"Anton","Papay","WTF?"},
    {"Denis","Maloy","How r u?"},
    {"Denis","Wride","Param-pareram!"},
};

int DenisUniqueContactCount =
    from(messages).where(   [](const Message & msg){return msg.PhoneA == "Denis";})
                  .distinct([](const Message & msg){return msg.PhoneB;})
                  .count();

// DenisUniqueContactCount == 2    
```

###Containers supported?

- C++: Native arrays, pairs of pointers
- STL: list, stack, queue, vector, deque, set, map, any compatible ....
- Qt: QList, QVector, QSet, QMap.

###Operators supported?

####Today:

- cast<T>()
- take(int)
- skip(int)
- concat(range)
- where(lambda)
- select(lambda)
- reverse()
- orderBy()
- orderBy(lambda)
- groupBy(lambda)
- distinct()
- distinct(lambda)
- for_each(lambda)
- all()
- all(lambda)
- any()
- any(lambda)
- sum()
- sum(lambda)
- avg()
- avg(lambda)
- min()
- min(lambda)
- max()
- max(lambda)
- count()
- count(lambda)
- contains(value)
- elementAt(int)
- toSet()
- toList()
- toDeque()
- toVector()
- toContainer<T>()

####Custom:

- bytes()
- bytes<ByteOrder>()
- unbytes<T>()
- unbytes<T,ByteOrder>()
- bits()
- bits<BitOrder>()
- bits<BitOrder,ByteOrder>()
- unbits()
- unbits<BitOrder>()
- unbits<T>()
- unbits<T,BitOrder>()
- unbits<T,BitOrder,ByteOrder>()

####Coming soon:

- selectMany(lambda)

####May be will be:

- gz()
- ungz()
- leftJoin
- rightJoin
- crossJoin
- fullJoin
