# File-Organization-BD2
Proyecto de Base de Datos 2 : Organización de Archivos

## Integrantes :
    - Canto Vidal, Harold Alexis
    - Gutierrez Soto, Brhandon Luis
    - Rincón Espinoza, Alberto Domenic
    
## Objetivo : 

Analizar, implementar y experimentar soluciones a problemas de indexación en base de datos, como el Sequential File y el Extendible Hash.

## Dominio de datos :

Sequential File     -->   Cars Database

Extendible Hash     -->   Accidentes Database
  

## Sequential File
>Un Sequential File es una estructura de datos en la que los registros se almacenan uno detrás del otro en un archivo. Al usar binary search esto puede resultar en una búsqueda más rápida y eficiente en comparación con la búsqueda secuencial.

**Estructura**
```cpp
template <typename TRecord, typename TKey>
class Sequential
 {
  private:
    string fileName;
    string auxName;
    long sizeData = 0;
    long sizeAux = 0;
    const long sizeRecord = sizeof(TRecord);
  }
```        
**Inserción**
>La función **insert** recibe un registro record y un contador accesos, que se utiliza para realizar un seguimiento del número de accesos al archivo.
Primero, la función verifica si el archivo está vacío. Si es así, abre el archivo, escribe el registro en la posición 0 y cierra el archivo.
Si el archivo no está vacío, utiliza la función insideSearch para buscar la posición donde el registro debe ser insertado en el archivo.
Luego, la función abre el archivo y lee el registro en la posición encontrada. Si la posición es 0 y el registro es menor que el registro en la posición 0, la función verifica si el registro es el único registro en el archivo. Si es así, escribe el registro en la posición 0 y actualiza el índice. De lo contrario, escribe el registro en un archivo auxiliar y actualiza el índice.
Si la posición no es 0, la función verifica si el registro es el último registro en el archivo. Si es así, escribe el registro al final del archivo y actualiza el registro anterior para apuntar al nuevo registro. Si no es el último registro, la función verifica si hay un registro eliminado antes y utiliza ese espacio para insertar el registro. Si no hay espacio disponible, escribe el registro en un archivo auxiliar y actualiza el índice.
Finalmente, la función cierra el archivo y devuelve el contador accesos.
 ```cpp
    void insert(TRecord &record, int &accesos)
```
**Búsqueda**
>La función **search** que busca un registro con una clave dada en un archivo secuencial. El archivo se compone de registros TRecord que tienen una clave y un puntero al siguiente registro en el archivo (si es -1, indica que es el último registro del archivo; si es -2, indica que el registro ha sido eliminado.
La función recibe como parámetros la clave que se desea buscar y una variable de referencia accesos que se utiliza para contar la cantidad de accesos a disco que se realizan durante la búsqueda.
La búsqueda se realiza llamando a la función insideSearch, que determina la posición del registro con la clave buscada. Luego, se abre el archivo y se lee el registro correspondiente a la posición encontrada.
Si la clave del registro leído coincide con la clave buscada, se devuelve un puntero al registro. Si el puntero al siguiente registro es -2, se indica que el registro ha sido eliminado lógicamente y se devuelve un puntero nulo.
Si el puntero al siguiente registro es -1, se indica que no hay más registros en el archivo y se devuelve un puntero nulo.
Si el puntero al siguiente registro es distinto de -1 y -2, se indica que el siguiente registro está en el archivo auxiliar y se busca en él. El archivo auxiliar se abre y se lee el registro correspondiente a la posición indicada por el puntero al siguiente registro. Si la clave coincide con la buscada, se devuelve un puntero al registro. Si el puntero al siguiente registro es -2, se indica que el registro ha sido eliminado lógicamente y se devuelve un puntero nulo. Si no se encuentra el registro, se devuelve un puntero nulo.
En caso de que ocurra algún error al abrir los archivos, se muestra un mensaje de error y se devuelve un puntero nulo.
 ```cpp
   TRecord *search(TKey key, int &accesos)
```
**Búqueda por rangos**
>En la búsqueda por rangos, lo que hacemos es determinar la posición del inicio y el final dentro de los archivos  **`aux.dat`**  y **`dat.dat`** . A continuación, comprobamos la ubicación de los elementos ordenados por punteros para retornar los valores que se encuentran dentro del intervalo deseado. Es importante verificar esta ubicación debido a que algunos datos pueden haber sido movidos del archivo **`dat.dat`**  al **`aux.dat`**, pero aun así están referenciados correctamente.
 ```cpp
   vector<TRecord> search(TKey begin, TKey end)
```
**Remover**
>Para eliminar registros en los archivos **`aux.dat`** y **`dat.dat`** , se utiliza la función  **`erase()`** que busca el registro a eliminar por su clave. Para mantener la coherencia de los datos, se realiza un reordenamiento físico llamado **`refactor()`** para reorganizar la estructura y mantener la referencia de los punteros después de la eliminación. Además, esta función también nos ayuda a verificar si es posible eliminar el registro solicitado por el usuario, comprobando si el archivo está vacío o si el registro no existe.
```cpp
   bool erase(TKey key)
```
## Extendible hash
>Un extendible hash es una estructura de datos utilizada en la organización y acceso eficiente a grandes conjuntos de datos. Consiste en una tabla hash que se puede expandir dinámicamente a medida que se agregan más elementos a la estructura. Esto permite que la estructura de datos se adapte automáticamente al tamaño del conjunto de datos, lo que resulta en un mejor rendimiento y uso eficiente de la memoria.
**Estructura**
```cpp
template <typename TKey>
class ExtendibleHash
{
private:
    string fileName;
    string indexName;
    unordered_map<string, long> index;
    unordered_map<string, long> index_size;
    hash<TKey> _hash;
    long freeListBucket = -1;
    string hash_function(TKey key)
    {
        auto hash_code = _hash(key);
        string hash_code_string = bitset<HASH_HEIGHT>(hash_code).to_string();
        return hash_code_string;
    }
    void initIndex();
    void readIndex();
    void writeIndex();
    void insertInFreeList(fstream &f, int &accesos);
    void divideBucket(fstream &f, Bucket<TKey> &bucket, long pos, int &accesos);
    bool exists(TKey key, int &accesos);
    bool is_brother(string ref, string bro, long d);
 }
```
**Inserción**
>La función **insert()** recibe un registro y lo inserta en la tabla de hash. Si el registro ya existe en la tabla, se muestra un mensaje y no se realiza la inserción. Si no existe, se calcula la posición de inserción en la tabla de hash utilizando una función de hash. Se lee el bucket correspondiente a esa posición y si está lleno, se realiza una división del bucket y se redistribuyen los registros. Si después de la división el bucket sigue lleno y tiene la altura máxima permitida, se crea un bucket adicional y se agrega a la lista enlazada de buckets. Si el bucket no está lleno, se inserta el registro en ese bucket. Al finalizar, se incrementa el tamaño del índice para esa posición en la tabla de hash y se cierra el archivo de datos. La variable "accesos" es utilizada para llevar un conteo de las operaciones de lectura y escritura realizadas en el archivo de datos.
```cpp
    void insert(RecordHash<TKey> record, int &accesos)
```
**Búsqueda**
>La función **search()** toma una clave "key" como entrada y utiliza una función hash para determinar la ubicación en la tabla hash donde se deben buscar registros con esa clave. Si la tabla hash tiene registros en esa ubicación, se busca en cada "bucket" o contenedor asociado hasta encontrar el registro con la clave deseada. Si se encuentra el registro, se devuelve un puntero a ese registro. Si no se encuentra, se devuelve un puntero nulo. Además, la función mantiene un contador de "accesos" para registrar el número de operaciones de lectura realizadas en la búsqueda.
```cpp
    RecordHash<TKey> *search(TKey key, int &accesos)
```

**Busqueda por rango**
>La función **search_range()** implementa una función para buscar y retornar un vector de registros (clase RecordHash) que se encuentran en el rango definido por dos claves (parámetros key1 y key2). La búsqueda se realiza recorriendo todos los buckets (contenedores de registros) que existen en la tabla hash, utilizando una función de hash para determinar la posición inicial de búsqueda. Cada bucket se lee desde el archivo de almacenamiento y se busca en él los registros que caen dentro del rango de búsqueda. Los registros que cumplen con este criterio se agregan al vector result, que se retorna al final de la función. Además, se utiliza un conjunto visited para evitar leer dos veces el mismo bucket. Si no se puede abrir el archivo, se imprime un mensaje de error y se retorna un vector vacío
```cpp
    vector<RecordHash<TKey>> searchRange(TKey key1, TKey key2)
```
**Remover**
>Para llevar a cabo la eliminación de un registro, se procede a realizar una búsqueda y se elimina el registro del bucket correspondiente, dejando un espacio vacío. Si este es el último bucket en la lista enlazada, no hay ningún problema. En caso contrario, se debe mover el último registro del último bucket en la lista enlazada a la posición que se ha dejado vacía. De esta manera, solo es necesario revisar el último bucket de la lista, eliminándolo si está vacío o dejándolo en su estado actual si no lo está. De este modo, se respeta la naturaleza del hashing dinámico, que permite el crecimiento y reducción del tamaño de la tabla hash a medida que se agregan o eliminan registros.
```cpp
    bool erase(TKey key)
```
**Gráficas**
>Inserción

| Cuadro comparativo | | | | | |
|:-------------------:|---|---|---|---|---|
| Registros| 500| 1000| 1500| 2000|2500|
| Hash | 1605| 3510| 5801| 7854| 8048|
| Sequential | 2501| 4990| 7500| 10010|12500|

>Hemos notado que el método de hash tiene significativamente menos accesos en comparación con el método secuencial. La razón de esto es que el hashing dinámico es mucho más eficiente para agregar nuevos elementos, ya que no requiere una búsqueda secuencial como la que se necesita en el método secuencial.

<img height="400" src= Insercion.png>

>Búsqueda

| Cuadro comparativo | | | | | |
|:-------------------:|---|---|---|---|---|
| Registros |500 | 1000| 1500| 2000| 2500|
| Hash | 1| 1| 1| 1| 1|
| Sequential |9 |9 |9 | 9| 9|

>En términos de eficiencia, la técnica de hashing dinámica es superior gracias a sus búsquedas en O(1), lo que significa que solo es necesario aplicar la función de hashing y acceder a la posición deseada. Por otro lado, la técnica secuencial necesita realizar una búsqueda binaria en el archivo índice, lo que tiene una complejidad de O(lgn). Ambos métodos tienen sus ventajas, pero en general, la hashing dinámica resulta ser mejor.

<img height="400" src= Busqueda.png>

ENLACE DEL VIDEO :https://drive.google.com/file/d/1wv5Uj5qXZTPHEeBjxjxwmZX0JvowPNUd/view?usp=share_link
