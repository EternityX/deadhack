## hack

## Naming conventions
### File Names
Filenames should be all lowercase and can include underscores.

### Type Names
Type names start with a capital letter and have a capital letter for each new word and can have a '_t' suffix.
```c++
class SomeType_t { ...
```

```c++
struct SomeStruct { ...
```

### Classes, Structs and Namespace Names
```c++
class SomeClass { ...
```

### Variable Names
The names of variables (including function parameters) and data members are all lowercase, with underscores between words. Data members of classes (and structs) additionally have 'm_' prepended. For instance: local_variable, m_struct_data_member, m_class_data_member.

### Function Names
The names of functions are all lowercase, with underscores between words.

### Macro Names
Should be named with all capitals and underscores between words.
