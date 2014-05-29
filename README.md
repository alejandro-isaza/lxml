# lxml

lxml is a C++ wrapper for the SAX interface of [Libxml2](http://xmlsoft.org/). One of its main features is that there is no bolerplate involved. Just define your SAXHandler subclass and invoke the parser:

```cpp
#include "lxml.h"
//...
MyHandler handler;
bool result = parse(stream, filename, handler);
```

lxml also supports having separate handlers for each element in an XML document. You can have specialized handlers for different elements which improves the modularity, maintainability and reusability of the code. Each handler recursively specifies sub-handlers to deal with sub-elements.


## Usage

Just include the contents of the `src` folder in your project. Of course, you need to link with Libxml2. If you want to compile a stand-alone static library you can use `make`.
