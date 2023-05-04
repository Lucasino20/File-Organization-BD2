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
>Para la inserción hacemos empleo de la función  **`insideSearch()`** usando **`binarySearch()`** lo que hace que hagamos O (log(n)) accesos a memoria secundaria. Luego, localizamos la posición donde será insertado el nuevo registro, si es que el espacio está libre, entonces insertamos, si no insertamos el registro en el  **`aux.dat`** que es nuestro espacio auxiliar. Seguido de esto actualizamos los punteros.
 ```cpp
    void insert(TRecord &record, int &accesos)
```
**Búsqueda**
>El algoritmo **`binarySearch()`**se usa para ubicar un registro en el archivo dado un valor búsqueda, esto los hacemos en O(log(n))accesos a memoria secundaria. Además, durante la búsqueda si es que un archivo fue marcado como eliminado antes se descarta en la búsqueda.
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
>Para la inserción aplicamos la función **`hash_function(key)`** sobre el key, que nos retorna una posición en el archivo Index.dat, Index.dat retorna la posición física donde insertaremos el registro en el archivo Data.dat. Luego se accede a esa posición y existen 2 posibilidades, la primera es que no exista un Bucket (conjunto de registros), en ese caso creamos uno e insertamos el registro en el nuevo bucket (tomando 2 accesos extra), el segundo caso es que ya exista un bucket, entonces revisamos si hay espacio en el bucket para insertar, caso contrario creamos un nuevo bucket, lo enlazamos e insertamos el registro en el nuevo bucket. (De esta forma la estructura crece dinámicamente, porque creamos nuevos buckets según sea necesario.
```cpp
    void insert(RecordHash<TKey> record, int &accesos)
```
**Búsqueda**
>Para llevar a cabo la búsqueda, se aplica la función  **`hash_function(key)`**  a la clave del registro. De este modo, se obtiene la ubicación del registro dentro del archivo Data.dat, y se accede a dicha ubicación en el archivo de datos. Si no se encuentra un "bucket" (pos = -1), entonces el registro no existe. Si, por otro lado, se encuentra un bucket, se carga en la memoria principal y se examina de forma secuencial junto con todos los buckets enlazados hasta dar con el registro deseado o llegar al final de la lista de buckets enlazados.
```cpp
    RecordHash<TKey> *search(TKey key, int &accesos)
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
