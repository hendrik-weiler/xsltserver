# XSLTSERVER

This application starts a server at port 8000 and lets you write your backend
in c++ and the frontend in xsl.

### Requirements

- [conan](https://docs.conan.io/en/latest/installation.html)
- Python in cli

### Dependencies

Following libraries will be used
- [libxslt](http://xmlsoft.org/XSLT/)
- [civetweb](https://github.com/civetweb/civetweb)

### Install

This application uses conan to install its dependencies.
Create the directory ```cmake-build-debug``` change to the build folder ```cd cmake-build-debug``` and run ```conan install ..```.

### Build
Run the ```build.sh``` in the root folder. The executable will be created in ```cmake-build-debug/bin```

### Development

###### Create a xslhtml document

For example we create a path to ```/mypage.xslhtml```.
1. Create a file ```mypage.xsl``` in ```src/www```. Fill it with the data of ```src/www/index.xsl```.
2. Create files ```src/page/mypage.h``` and ```src/page/mypage.cpp```. Use ```src/page/index.h|index.cpp``` as data.
3. Change the namespace ```page_index``` to ```page_mypage```.
4. Go to the ```mypage.cpp``` file and change the route path in ```page_mypage::register_route```. Change the first parameter to ```/mypage```.
5. Go to ```/src/routes.cpp```, include the mypage.h and add in the ```registerAllRoutes``` function ```page_mypage::register_route();```.
6. Now you can rebuild the app for example with ```build.sh```. The ```/src/www``` folder will be copied to the ```cmake-build-debug/bin``` folder. Afterwards run the application and go to ```http://localhost:8000/mypage.xslhtml```.
7. You should now see the created page

###### Examples

The application comes with examples for better understanding
- Login App (/login.xslhtml)
- Todo App (/todo.xshtml)

###### Set data for the xsl file

A function signature in the c++ backend in as following ```void page_index::index(mg_connection *conn, Data& data, Request& request)```
With the data parameter you can set single key,value pairs or lists.

**Single key,value pair**
```
data.Set("Email","max.mustermann@company.com");
// in xsl <xsl:value-of select="/Data/Email"></xsl:value-of>
```

**List of key,value pairs**
```
vector<Data> list {};
vector<string> names = {"Hans","Paul","Peter","Nadine","Rolf","Natascha"};
vector<string> age = {"20","23","44","24","21","44"};
for (int i = 0; i < 6; ++i) {
    Data d{};
    d.Set("Name", names.at(i));
    d.Set("Age", age.at(i));
    list.push_back(d);
}
data.SetList("Person", list);
// in xsl <xsl:value-of select="/Data/Person[0]/Name"></xsl:value-of>
// For each loop
//  <xsl:for-each select="/Data/Person">
//        <tr>
//            <td><xsl:value-of select="Name"></xsl:value-of></td>
//            <td align="right"><xsl:value-of select="Age"></xsl:value-of></td>
//        </tr>
//  </xsl:for-each>
```

**Get xml data**
```
// output the xml data for debugging
cout << data.ToXML() << endl;
```