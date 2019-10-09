#  BaseRegex
>基于NFA的最基本功能正则表达式引擎

## 功能
目前只实现了最基本的 **'*'** (重复)，**'|'** (或)，以及 **'()'** 。

优先级为 () > * > |


## Example

code1
```cpp
BaseRegex regex("\\(\\)");
cout<<boolalpha<<regex.match("()")<<endl;
cout<<boolalpha<<regex.match("(")<<endl;
```
result
```
true
false
```
code2
```cpp
BaseRegex r1("hello|world");
cout<<boolalpha<<regex.match("hello")<<endl;
cout<<boolalpha<<regex.match("world")<<endl;
```

result
```
true
true
```
code3 
```cpp
BaseRegex regex("(hello*)world|nice!");

cout<<boolalpha<<regex.match("helloworld")<<endl;
cout<<boolalpha<<regex.match("hellohelloworld")<<endl;
cout<<boolalpha<<regex.match("nice!")<<endl;
cout<<boolalpha<<regex.match("world")<<endl;
cout<<boolalpha<<regex.match("worl")<<endl;

```

result
```
true
true
true
true
false
```
